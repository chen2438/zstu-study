#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<ctime>
#include<fstream>
#include<vector>
#include<algorithm>
#include<windows.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
const int MAX_OF_DEV=1e6+7;//定义存储数据上限
using namespace std;

struct device{
	//按顺序为 存储序列号、设备编号、设备名称、领用人、所属部门、数量、购买时间、价格
	int num;
	string id,nme,rcp,dpt,sum,tme,prc;
};

vector<device> dev;

void ShowMenu();
void ImportDev();
void ReturnMenu();
void SaveDev(string file, vector<device> save);
void ViewDev();
void QueryDev();
void DeletDev();
void SortDev();

void ShowMenu(){//人机交互主界面
	putchar('\n');
	cout<<"*********************\n";
	cout<<"*  0-退出系统       *\n";
	cout<<"*  1-信息导入与添加 *\n";
	cout<<"*  2-信息浏览       *\n";
	cout<<"*  3-信息查询       *\n";
	cout<<"*  4-删除设备       *\n";
	cout<<"*  5-信息排序       *\n";
	cout<<"*  6-其他功能       *\n";
	cout<<"*********************\n";
	cout<<"->请选择操作:";
	int op;cin>>op;
	while(!(op>=0 and op<=7)){
		cout<<"输入有误!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	switch(op){
		case 0: exit(0);break;
		case 1: ImportDev();break;
		case 2: ViewDev();break;
		case 3: QueryDev();break;
		case 4: DeletDev();break;
		case 5: SortDev();break;
		//default: {};
	}
}

void ReturnMenu(){
	cout<<"操作完成, 1 秒后返回初始界面.\n";
	Sleep(1000);
	ShowMenu();
}

void PutDev(device T){//打印设备信息
	cout<<"存储序列号："<<T.num;
	cout<<" 设备编号："<<T.id;
	cout<<" 设备名称："<<T.nme;
	cout<<" 领用人："<<T.rcp;
	cout<<" 所属部门："<<T.dpt;
	cout<<" 数量："<<T.sum;
	cout<<" 购买时间："<<T.tme;
	cout<<" 价格："<<T.prc<<endl;
}

void SaveDev(string file, vector<device> save){//保存设备信息
	clock_t st=clock();
	ofstream ofs;
	ofs.open(file,ios::out | ios::trunc);
	if(!ofs.is_open()) {cout<<"写入文件打开失败！"<<endl; exit(0);}
	int len=save.size();
	FOR(i,0,len-1){
		save[i].num=i+1;
		auto T=save[i];
		ofs<<T.num<<" "<<T.id<<" "<<T.nme<<" "<<T.rcp<<" "<<T.dpt<<\
			" "<<T.sum<<" "<<T.tme<<" "<<T.prc<<'\n';
	}
	ofs.close();
	clock_t ed=clock();
	cout<<file<<" 已保存更改, 耗时 "<<ed-st<<" 毫秒\n";
	cout<<file<<" 内目前有 "<<save.size()<<" 条记录\n";
}

void ImportDev(){//导入或添加设备
	putchar('\n');
	cout<<"*******************\n";
	cout<<"*   1-从文件导入   *\n";
	cout<<"*   2-添加单个信息 *\n";
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
		ifs.open("dev(1e3).in", ios::in);
		//1e3 10ms 1e4 72ms 1e5 696ms 1e6 6766ms
		if(!ifs.is_open()) {cout<<"读取文件打开失败\n"; exit(0);}
		device T;
		int len=dev.size();
		while(ifs>>T.id>>T.nme>>T.rcp>>T.dpt>>T.sum>>T.tme>>T.prc){
			T.num=(len++)+1;
			dev.push_back(T);
		}
		ifs.close();
	}
	if(op==2){
		device T;
		T.num=dev.size()+1;
		cout<<"请输入设备编号:"; cin>>T.id;
		cout<<"请输入设备名称:"; cin>>T.nme;
		cout<<"请输入领用人:"; cin>>T.rcp;
		cout<<"请输入所属部门:"; cin>>T.dpt;
		cout<<"请输入数量:"; cin>>T.sum;
		cout<<"请输入购买时间:"; cin>>T.tme;
		cout<<"请输入价格:"; cin>>T.prc;
		dev.push_back(T);
	}
	SaveDev("dev.out",dev);
	ReturnMenu();
}

void ViewDev(){//浏览设备信息
	putchar('\n');
	cout<<"已存储信息如下:(需优化格式)\n";
	for(auto T:dev)
		PutDev(T);
	ReturnMenu();
}

void QueryDev(){//查询设备信息
	putchar('\n');
	cout<<"*******************\n";
	cout<<"*  1-按设备名称查找 *\n";
	cout<<"*  2-按所属部门查找 *\n";
	cout<<"*  3-全域查找      *\n";
	cout<<"*******************\n";
	cout<<"->请选择操作:";
	int op;cin>>op;
	while(!(op>=1 and op<=3)){
		cout<<"输入有误!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	clock_t st;
	int amt=0;
	vector<device> res;
	if(op==1){
		cout<<"请输入设备名称:";
		string nme;cin>>nme;
		st=clock();
		for(auto T:dev)
			if(T.nme==nme) {res.push_back(T); amt++;}
	}
	if(op==2){
		cout<<"请输入所属部门名称:";
		string dpt;cin>>dpt;
		st=clock();
		for(auto T:dev)
			if(T.dpt==dpt) {res.push_back(T); amt++;}
	}
	if(op==3){
		cout<<"请输入关键字:";
		string x;cin>>x;
		st=clock();
		for(auto T:dev){
			if(T.id==x or T.nme==x or T.rcp==x or T.dpt==x \
				or T.sum==x or T.tme==x or T.prc==x){
				res.push_back(T); amt++;
			}
		}
	}
	clock_t ed=clock();
	if(amt>0){
		cout<<"查询到 "<<amt<<" 条记录, 耗时 "<<ed-st<<" 毫秒\n";
		putchar('\n');
		cout<<"*******************\n";
		cout<<"*  1-打印到屏幕    *\n";
		cout<<"*  2-保存到文件    *\n";
		cout<<"*******************\n";
		cout<<"->请选择操作:";
		int op;cin>>op;
		while(!(op>=1 and op<=2)){
			cout<<"输入有误!\n";
			cout<<"->请选择操作:";
			cin>>op;
		}
		if(op==1) {for(auto T:res) PutDev(T);}
		if(op==2) {SaveDev("query.out",res);}
	}
	else cout<<"无法查询到此设备.\n";
	ReturnMenu();
}

void DeletDev(){//删除设备信息
	putchar('\n');
	cout<<"请输入待删除数据的序列号\n";
	int num;cin>>num;
	while(!(num>=1 and num<=(int)dev.size())){
		cout<<"非法序列号，请重新输入:";
		cin>>num;
	}
	dev.erase(dev.begin()+num-1);
	SaveDev("dev.out",dev);
	ReturnMenu();
}

bool CmpStr(string x1,string x2){//对string以数字大小排序,而非字典序
	if(x1==x2) return false;
	else if(x1.length()!=x2.length()) return x1.length()<x2.length();
	else return x1<x2;
}

void sort(vector<device>::iterator st, vector<device>::iterator ed,int op){
    switch(op){
		case 1: sort(st,ed,[](device x,device y){return CmpStr(x.id,y.id);});break;
		case 2: sort(st,ed,[](device x,device y){return CmpStr(x.sum,y.sum);});break;
		case 3: sort(st,ed,[](device x,device y){return CmpStr(x.tme,y.tme);});break;
		case 4: sort(st,ed,[](device x,device y){return CmpStr(x.prc,y.prc);});break;
		case 5: sort(st,ed,[](device x,device y){return !CmpStr(x.id,y.id);});break;
		case 6: sort(st,ed,[](device x,device y){return !CmpStr(x.sum,y.sum);});break;
		case 7: sort(st,ed,[](device x,device y){return !CmpStr(x.tme,y.tme);});break;
		case 8: sort(st,ed,[](device x,device y){return !CmpStr(x.prc,y.prc);});break;
	}
}

void SortDev(){//排序设备信息
	putchar('\n');
	cout<<"*******************\n";
	cout<<"*  1-按设备编号升序 *\n";
	cout<<"*  2-按设备数量升序 *\n";
	cout<<"*  3-按购买时间升序 *\n";
	cout<<"*  4-按设备价格升序 *\n";
	cout<<"*  5-按设备编号降序 *\n";
	cout<<"*  6-按设备数量降序 *\n";
	cout<<"*  7-按购买时间降序 *\n";
	cout<<"*  8-按设备价格降序 *\n";
	cout<<"*******************\n";
	cout<<"->请选择操作:";
	int op;cin>>op;
	while(!(op>=1 and op<=8)){
		cout<<"非法输入!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	clock_t st=clock();
	sort(dev.begin(),dev.end(),op);
	clock_t ed=clock();
	cout<<"排序完成, 耗时 "<<ed-st<<" 毫秒\n";
	SaveDev("dev.out",dev);
	cout<<"是否浏览数据?(y/n)\n";
	char c;
	cin>>c;
	while(!(c=='y' or c=='n')){
		cout<<"非法输入，请重新输入:";
		cin>>c;
	}
	if(c=='y') ViewDev();
	if(c=='n') ReturnMenu();
}