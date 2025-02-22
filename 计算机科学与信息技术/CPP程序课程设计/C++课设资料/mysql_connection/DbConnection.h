_Pragma("once")
#include "mysql.h"
class DbConnection{
public:
    DbConnection(const char* host, const char* username, const char* password, const char* database); //���������ݿ������
    ~DbConnection();  //�ر������ݿ������
    //�����ݿⷢ��select�����ѯ�ɹ������ؽ������ʧ�ܣ��׳��쳣
    MYSQL_RES executeQuery(const char* sql);
     //�����ݿⷢ��insert��update��delete���ִ�гɹ������ز��롢���»�ɾ���ļ�¼����ʧ�ܣ��׳��쳣
    int executeSQL(const char* sql);
private:
    MYSQL connection;  //MySQL�����ݿ�����
};
