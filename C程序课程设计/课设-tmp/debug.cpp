#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<fstream>
#include<ctime>
#include<chrono>
#include<thread>

using namespace std;
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
const int MAX_OF_DEV=1e5+7;

struct DEV{
	//按顺序为 设备编号、设备名称、领用人、所属部门、数量、购买时间、价格
	string id,nme,rcp,dpt,sum,tme,prc;
	//int ID,SUM,PRC
}dev[MAX_OF_DEV];

int ImportDev();

int UI(){
	cout<<"*******************\n";
	cout<<"*    0-退出系统    *\n";
	cout<<"*    1-信息导入    *\n";
	cout<<"*    2-信息浏览    *\n";
	cout<<"*    3-信息查询    *\n";
	cout<<"*    4-添加设备    *\n";
	cout<<"*    5-删除设备    *\n";
	cout<<"*    6-信息排序    *\n";
	cout<<"*    7-其他功能    *\n";
	cout<<"*******************\n";
	cout<<"->请选择操作:";
	int op;cin>>op;
	while(!(op>=0 and op<=7)){
		cout<<"输入有误!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	if(op==0){
		exit(0);
	}
	if(op==1){
		ImportDev();
	}
	return op;
}

int ImportDev(){
	cout<<"*******************\n";
	cout<<"*   1-从文件导入    *\n";
	cout<<"*   2-单个信息导入  *\n";
	cout<<"*******************\n";
	cout<<"->请选择操作:";
	int op;cin>>op;
	while(!(op>=1 and op<=2)){
		cout<<"输入有误!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	if(op==1){
		ifstream ifs;
		ifs.open("/Users/nanmener/Documents/GitHub/zstu-study/C程序课程设计/课设-tmp/dev.in", ios::in);
		if (!ifs.is_open()){
			cout<<"打开失败\n";exit(0);
		}
		int i=0;
		while (ifs>>dev[i].id>>dev[i].nme>>dev[i].rcp>>\
			dev[i].dpt>>dev[i].sum>>dev[i].tme>>dev[i].prc){
			cout<<dev[i].id<<endl;
		}
		ifs.close();
		cout<<"导入成功! 3秒后返回初始界面\n";
		this_thread::sleep_for(std::chrono::milliseconds(3000));
	}
	return 0;
}

signed main(){
	UI();

	return 0;
}