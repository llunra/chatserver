#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"
// USER表的数据操作类
class UserModel{
    public:
    //User表的增加方法
    bool insert(User &user);
    //根据主键（用户号码）查询用户信息
    User query(int id);
    //更新用户的状态信息
    bool updateState(User user);
};

#endif