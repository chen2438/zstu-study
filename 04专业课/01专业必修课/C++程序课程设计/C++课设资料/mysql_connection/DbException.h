#include<exception>
_Pragma("once")
using namespace std;
class DbExcepiton: public exception
{
public:
    DbExcepiton(const char* msg):err_msg(msg){}
    const char* what() const throw(){return err_msg;}
private:
    const char* err_msg;
};
