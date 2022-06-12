#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<fstream>
#include<vector>
#include<algorithm>
#include<windows.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
const int MAX_OF_DEV=1e5+7;
using namespace std;

struct device{
	//按顺序为 存储序列号、设备编号、设备名称、领用人、所属部门、数量、购买时间、价格
	int num;
	string id,nme,rcp,dpt,sum,tme,prc;
	//char id[100],nme[100],rcp[100],dpt[100],sum[100],tme[100],prc[100];
};

vector<device> dev;

void ImportDev();
void SaveDev();
void ViewDev();
void QueryDev();
void DeletDev();
void SortDev();

void UI(){
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

void PutDev(device T){
	cout<<"存储序列号："<<T.num;
	cout<<" 设备编号："<<T.id;
	cout<<" 设备名称："<<T.nme;
	cout<<" 领用人："<<T.rcp;
	cout<<" 所属部门："<<T.dpt;
	cout<<" 数量："<<T.sum;
	cout<<" 购买时间："<<T.tme;
	cout<<" 价格："<<T.prc<<endl;
}

void SaveDev(){
	ofstream ofs;
	ofs.open("dev.out",ios::out | ios::trunc);
	if(!ofs.is_open()){
		cout<<"写入文件打开失败！"<<endl;exit(0);
	}
	FOR(i,0,(int)dev.size()-1){
		dev[i].num=i+1;
		auto T=dev[i];
		ofs<<T.num<<" "<<T.id<<" "<<T.nme<<" "<<T.rcp<<" "<<T.dpt<<\
			" "<<T.sum<<" "<<T.tme<<" "<<T.prc<<endl;
	}
	ofs.close();
}

void ImportDev(){
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
		ifs.open("dev.in", ios::in);
		if (!ifs.is_open()){
			cout<<"读取文件打开失败\n";exit(0);
		}
		device T;
		while(ifs>>T.id>>T.nme>>T.rcp>>T.dpt>>T.sum>>T.tme>>T.prc){
			T.num=dev.size()+1;
			dev.push_back(T);
		}
		ifs.close();
	}
	if(op==2){
		device T;
		T.num=dev.size()+1;
		cout<<"请输入设备编号:";
		cin>>T.id;
		cout<<"请输入设备名称:";
		cin>>T.nme;
		cout<<"请输入领用人:";
		cin>>T.rcp;
		cout<<"请输入所属部门:";
		cin>>T.dpt;
		cout<<"请输入数量:";
		cin>>T.sum;
		cout<<"请输入购买时间:";
		cin>>T.tme;
		cout<<"请输入价格:";
		cin>>T.prc;
		dev.push_back(T);
	}
	SaveDev();
	cout<<"导入成功! 已保存至 dev.out, 2秒后返回初始界面.\n";
	Sleep(2000);
	UI();
}

void ViewDev(){
	putchar('\n');
	cout<<"已存储信息如下:(需优化格式)\n";
	for(auto T:dev)
		PutDev(T);
	cout<<"读取信息完成, 2s后返回初始界面\n";
	Sleep(2000);
	UI();
}

void QueryDev(){
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
	int has=0;
	if(op==1){
		cout<<"请输入设备名称:";
		string nme;cin>>nme;
		for(auto T:dev)
			if(T.nme==nme) {PutDev(T); has=1;}
	}
	if(op==2){
		cout<<"请输入所属部门名称:";
		string dpt;cin>>dpt;
		for(auto T:dev)
			if(T.dpt==dpt) {PutDev(T); has=1;}
	}
	if(op==3){
		cout<<"请输入关键字:";
		string x;cin>>x;
		for(auto T:dev){
			if(T.id==x or T.nme==x or T.rcp==x or T.dpt==x \
				or T.sum==x or T.tme==x or T.prc==x){
				PutDev(T); has=1;
			}
		}
	}
	if(has) cout<<"查询完成, 2秒后返回初始界面\n";
	else cout<<"无法查询到此设备, 2秒后返回初始界面\n";
	Sleep(2000);
	UI();
}

void DeletDev(){
	putchar('\n');
	cout<<"已存储信息如下:(需优化格式)\n";
	for(auto T:dev)
		PutDev(T);
	cout<<"请输入待删除数据的序列号\n";
	int num;cin>>num;
	while(!(num>=1 and num<=(int)dev.size())){
		cout<<"非法序列号，请重新输入:";
		cin>>num;
	}
	dev.erase(dev.begin()+num-1);
	SaveDev();
	cout<<"删除成功! 已保存更改, 2秒后返回初始界面\n";
	Sleep(2000);
	UI();
}

bool CmpStr(string x1,string x2){
	if(x1==x2) return false;
	else if(x1.length()!=x2.length()) return x1.length()<x2.length();
	else return x1<x2;
}

bool cmp1(device x,device y) {return CmpStr(x.id,y.id);}
bool cmp2(device x,device y) {return CmpStr(x.sum,y.sum);}
bool cmp3(device x,device y) {return CmpStr(x.tme,y.tme);}
bool cmp4(device x,device y) {return CmpStr(x.prc,y.prc);}
bool cmp5(device x,device y) {return !CmpStr(x.id,y.id);}
bool cmp6(device x,device y) {return !CmpStr(x.sum,y.sum);}
bool cmp7(device x,device y) {return !CmpStr(x.tme,y.tme);}
bool cmp8(device x,device y) {return !CmpStr(x.prc,y.prc);}

void SortDev(){
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
	switch(op){
		case 1: sort(dev.begin(),dev.end(),cmp1);break;
		case 2: sort(dev.begin(),dev.end(),cmp2);break;
		case 3: sort(dev.begin(),dev.end(),cmp3);break;
		case 4: sort(dev.begin(),dev.end(),cmp4);break;
		case 5: sort(dev.begin(),dev.end(),cmp5);break;
		case 6: sort(dev.begin(),dev.end(),cmp6);break;
		case 7: sort(dev.begin(),dev.end(),cmp7);break;
		case 8: sort(dev.begin(),dev.end(),cmp8);break;
	}
	SaveDev();
	cout<<"排序成功!\n";
	ViewDev();
}

signed main(){
	UI();
	return 0;
}