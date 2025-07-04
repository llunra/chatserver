/*
muduo网络库给用户提供了两个主要的类
TcpServer:用于编写服务器程序
TcpClient:用于编写客户端程序

epoll + 线程池
好处：能把网络I/O的代码和业务代码区分开
                        用户的连接和断开 用户的可读写事件
*/

#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<iostream>
#include<functional>
#include<string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
/*
引入标准库 std::placeholders 命名空间中的占位符
在使用 std::bind() 绑定函数对象时，你可以用 _1, _2 表示“将来传入的参数”
将 onConnection 方法和当前对象 this 绑定在一起，并告诉 Muduo：
“将来你把一个 TcpConnectionPtr 类型的参数传进来，就能调用我这个对象的 onConnection 方法”。
*/

//基于muduo网络库开发服务程序
//1.组合TcpServer对象
//2.创建EventLoop事件循环对象的指针
//3.明确TcpServer构造函数需要什么函数，输出ChatServer的
//4.在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数
//5.设置合适的服务端线程数量，muduo库会自己分配I/O线程和worker线程
class ChatServer{
    public:
        ChatServer(EventLoop* loop,//事件循环
                const InetAddress& listenAddr,//IP + Port
                const string& nameArg)//服务器的名字
        :_server(loop,listenAddr,nameArg),_loop(loop)
        {
            //给服务器注册用户连接的创建和断开回调
            _server.setConnectionCallback(std::bind(&ChatServer::onConnection,this,_1));

            //给服务器注册用户读写事件回调
            _server.setMessageCallback(std::bind(&ChatServer::onMesssage,this,_1,_2,_3));

            //设置服务器端的线程数量 一个I/O线程 三个worker线程
            _server.setThreadNum(4);
        }
        //开启事件循环
        void start(){
            _server.start();
        }
    private:

        //专门处理用户的连接创建和断开 epoll listenfd accept
        void onConnection(const TcpConnectionPtr &conn){  
            if(conn->connected()){
                cout<<conn->peerAddress().toIpPort()<<" "<<conn->localAddress().toIpPort()<<"state:online"<<endl;
            }
            else{
                cout<<conn->peerAddress().toIpPort()<<" "<<conn->localAddress().toIpPort()<<"state:offline"<<endl;
                conn->shutdown();//类似于linux的close(fd)
                //_loop->quit();
            }
        }
        //专门处理用户的读写事件
        void onMesssage(const TcpConnectionPtr &conn,//连接
                        Buffer *buffer,//缓冲区
                        Timestamp time)//接受到数据的时间信息
        {
            string buf = buffer->retrieveAllAsString();//把接受的数据全部放入字符串中
            cout<<"recv data:"<<buf<<"time:"<<time.toString()<<endl;
            conn->send(buf);
        }

        TcpServer _server;//1
        EventLoop *_loop;//2 epoll
};

int main(){
    EventLoop loop;
    InetAddress addr("192.168.234.128",6000);
    ChatServer server(&loop,addr,"ChatServer");

    server.start();//listenfd eopll_ctl -> epoll
    loop.loop();//epoll_wait以阻塞方式等待新用户连接，已连接用户的读写事件
    return 0;
}
