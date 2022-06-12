#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<fstream>
#include<vector>
/*#include<ctime>
#include<chrono>
#include<thread>*/
#include<windows.h>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
const int MAX_OF_DEV=1e5+7;

struct device{
	//按顺序为 设备编号、设备名称、领用人、所属部门、数量、购买时间、价格
	string id,nme,rcp,dpt,sum,tme,prc;
	//char id[100],nme[100],rcp[100],dpt[100],sum[100],tme[100],prc[100];
};
vector<device> dev;

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

int SaveDev(){
	ofstream ofs;
	ofs.open("dev.out",ios::out | ios::trunc);
	if (!ofs.is_open()){
		cout<<"写入文件打开失败！"<<endl;
	}
	for(auto T:dev){
		ofs<<T.id<<" "<<T.nme<<" "<<T.rcp<<" "<<T.dpt<<\
			" "<<T.sum<<" "<<T.tme<<" "<<T.prc<<endl;
	}
	ofs.close();
	return 0;
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
		ifs.open("dev.in", ios::in);
		if (!ifs.is_open()){
			cout<<"文件打开失败\n";exit(0);
		}
		device T;
		while(ifs>>T.id>>T.nme>>T.rcp>>T.dpt>>T.sum>>T.tme>>T.prc){
			dev.push_back(T);
		}
		ifs.close();
	}
	if(op==2){
		device T;
		cout<<"请输入设备编号：";
		cin>>T.id;
		cout<<"请输入设备名称：";
		cin>>T.nme;
		cout<<"请输入领用人：";
		cin>>T.rcp;
		cout<<"请输入所属部门：";
		cin>>T.dpt;
		cout<<"请输入数量：";
		cin>>T.sum;
		cout<<"请输入购买时间：";
		cin>>T.tme;
		cout<<"请输入价格：";
		cin>>T.prc;
		dev.push_back(T);
	}
	SaveDev();
	cout<<"导入成功! 已保存至 dev.out, 2秒后返回初始界面.\n";
	Sleep(2000);
	UI();
	return 0;
}

signed main(){
	UI();

	return 0;
}