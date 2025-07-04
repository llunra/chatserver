#ifndef PUBLIC_H
#define PUBLIC_H

/*
server 和 client 的公共文件
*/

enum EnMsgType{
    LOGIN_MSG = 1,       //登录消息
    LOGIN_MSG_ACK = 11,  //登录相应消息
    LOGINOUT_MSG = 12,   //登录退出
    
    REG_MSG = 2,         //注册消息
    REG_MSG_ACK = 21,    //注册相应消息

    ONE_CHAT_MSG = 3,        //聊天消息

    ADD_FRIEND_MSG = 4,     //添加好友消息

    CREATE_GROUP_MSG = 5,   //创建群组
    ADD_GROUP_MSG = 51,     //加入群组
    GROUP_CHAT_MSG = 52,    //群聊天

    
};

#endif