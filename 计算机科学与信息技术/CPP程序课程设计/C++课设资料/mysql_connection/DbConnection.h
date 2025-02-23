_Pragma("once")
#include "mysql.h"
class DbConnection{
public:
    DbConnection(const char* host, const char* username, const char* password, const char* database); //创建与数据库的连接
    ~DbConnection();  //关闭与数据库的连接
    //向数据库发送select命令，查询成功，返回结果集，失败，抛出异常
    MYSQL_RES executeQuery(const char* sql);
     //向数据库发送insert、update或delete命令，执行成功，返回插入、更新或删除的记录数，失败，抛出异常
    int executeSQL(const char* sql);
private:
    MYSQL connection;  //MySQL的数据库连接
};
