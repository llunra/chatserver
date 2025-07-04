cmake_minimum_required(VERSION 3.0)# 要求cmake版本
project(main)# 声明项目名

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置头文件的搜索路径
# include_directories()

# 配置库文件的搜索路径
# link_directories()

#设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)

#设置可执行文件最终存储的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


# 把.指定路径下的所有源文件名字放入变量名SRC_LIST里面
# 如果我们需要编译多个源文件，可以用aux_source_directory(dir var)
# 如果所有的源文件中，有我们不需要的文件，此时我们可以使用set命令去新建变量来存放需要的源文件
# eg:set(SRC_LIST ./main.cpp ./test.cpp)
# aux_source_directory(. SRC_LIST)

#表示生成可执行文件server，由SRC_LIST变量所定义的源文件编译而来
add_executable(server ${SRC_LIST})
# 表示server这个目标程序，需要链接muduo_net muduo_base pthread这三个库文件
target_link_libraries(server muduo_net muduo_base pthread)