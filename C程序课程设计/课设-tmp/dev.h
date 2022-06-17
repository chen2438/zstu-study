#pragma GCC optimize(2)
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

using namespace std;

struct device{
	//按顺序为 存储序列号、设备编号、设备名称、领用人、所属部门、数量、购买时间、价格
	int num;
	string id,nme,rcp,dpt,sum,tme,prc;
};

const string obj[10]={"存储序列号","设备编号","设备名称","领用人","所属部门","数量","购买时间","价格"};
//const string InFile="dev(1e1).in";
vector<device> dev;
vector<vector<device>> backup;

void ShowMenu();
void ImportDev();
void ReturnMenu();
void SaveDev(string file,vector<device> save,string obj);
void ViewDev();
void QueryDev();
void DeletDev();
bool CmpStr(string x1,string x2);
bool CmpStr(string x1,string x2,string x3);
bool CmpTme(string x1,string x2);
bool CmpTme(string x1,string x2,string x3);
void sort(vector<device>::iterator st, vector<device>::iterator ed,int op);
void SortDev();
void FilterDev();
void UndoDev();

void ShowMenu(){//人机交互主界面
	putchar('\n');
	cout<<"*********************\n";
	cout<<"*  0-退出系统       *\n";
	cout<<"*  1-信息导入与添加 *\n";
	cout<<"*  2-信息浏览       *\n";
	cout<<"*  3-信息查询       *\n";
	cout<<"*  4-删除设备       *\n";
	cout<<"*  5-信息排序       *\n";
	cout<<"*  6-信息筛选       *\n";
	cout<<"*  7-撤销操作       *\n";
	cout<<"*********************\n";
	cout<<"->请选择操作:";
	string op;cin>>op;
	while(!CmpStr("0",op,"7")){
		cout<<"输入有误!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	switch(atoi(op.c_str())){
		case 0: exit(0);break;
		case 1: ImportDev();break;
		case 2: ViewDev();break;
		case 3: QueryDev();break;
		case 4: DeletDev();break;
		case 5: SortDev();break;
		case 6: FilterDev();break;
		case 7: UndoDev();break;
	}
}

void ReturnMenu(){
	cout<<"操作完成, 1 秒后返回初始界面.\n";
	Sleep(1000);
	ShowMenu();
}

void PutDev(device T){//打印设备信息
	//cout.setf(ios::left);
    //cout.width(20);
	cout<<obj[0]+"："<<T.num;
	cout<<" "+obj[1]+"："<<T.id;
	cout<<" "+obj[2]+"："<<T.nme;
	cout<<" "+obj[3]+"："<<T.rcp;
	cout<<" "+obj[4]+"："<<T.dpt;
	cout<<" "+obj[5]+"："<<T.sum;
	cout<<" "+obj[6]+"："<<T.tme;
	cout<<" "+obj[7]+"："<<T.prc<<endl;
	//cout.unsetf(ios::left);
}

void SaveDev(string file,vector<device> save,string obj){//保存设备信息
	clock_t st=clock();
	if(obj=="dev"){
		backup.push_back(save);
		if(backup.size()==3) backup.erase(backup.begin());
	}
	ofstream ofs;
	ofs.open(file,ios::out | ios::trunc);
	if(!ofs.is_open()) {cout<<"写入文件打开失败！"<<endl; exit(0);}
	int len=save.size();
	#define T save[i]
	FOR(i,0,len-1){
		save[i].num=i+1;
		//auto T=save[i];
		ofs<<T.num<<' '<<T.id<<' '<<T.nme<<' '<<T.rcp<<' '<<T.dpt<<\
			' '<<T.sum<<' '<<T.tme<<' '<<T.prc<<'\n';
	}
	#undef T
	ofs.close();
	if(obj=="dev") dev=save;
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
	string op;cin>>op;
	while(!CmpStr("1",op,"2")){
		cout<<"输入有误!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	if(op=="1"){
		cout<<"请输入文件名:";
		string InFile;cin>>InFile;
		clock_t st=clock();
		ifstream ifs;
		ifs.open(InFile, ios::in);
		//1e3 10ms 1e4 72ms 1e5 696ms 1e6 6766ms
		if(!ifs.is_open()) {cout<<"读取文件打开失败\n"; exit(0);}
		device T;
		while(ifs>>T.id>>T.nme>>T.rcp>>T.dpt>>T.sum>>T.tme>>T.prc){
			dev.push_back(T);
		}
		ifs.close();
		clock_t ed=clock();
		cout<<"读取完成, 耗时 "<<ed-st<<" 毫秒\n";
	}
	if(op=="2"){
		device T;
		T.num=dev.size()+1;
		cout<<"请输入"+obj[1]+":"; cin>>T.id;
		cout<<"请输入"+obj[2]+":"; cin>>T.nme;
		cout<<"请输入"+obj[3]+":"; cin>>T.rcp;
		cout<<"请输入"+obj[4]+":"; cin>>T.dpt;
		cout<<"请输入"+obj[5]+":"; cin>>T.sum;
		cout<<"请输入"+obj[6]+":"; cin>>T.tme;
		cout<<"请输入"+obj[7]+":"; cin>>T.prc;
		dev.push_back(T);
	}
	SaveDev("dev.out",dev,"dev");
	ReturnMenu();
}

void ViewDev(){//信息浏览
	putchar('\n');
	cout<<"已存储信息如下:\n";
	for(auto T:dev)
		PutDev(T);
	ReturnMenu();
}

void QueryDev(){//信息查询
	putchar('\n');
	cout<<"*******************\n";
	cout<<"*  1-按设备名称查找 *\n";
	cout<<"*  2-按所属部门查找 *\n";
	cout<<"*  3-全域查找      *\n";
	cout<<"*******************\n";
	cout<<"->请选择操作:";
	string op;cin>>op;
	while(!CmpStr("1",op,"3")){
		cout<<"输入有误!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	clock_t st=clock();
	vector<device> res;
	if(op=="1"){
		cout<<"请输入设备名称:";
		string nme;cin>>nme;
		st=clock();
		for(auto T:dev) if(T.nme==nme) res.push_back(T);
	}
	if(op=="2"){
		cout<<"请输入所属部门名称:";
		string dpt;cin>>dpt;
		st=clock();
		for(auto T:dev) if(T.dpt==dpt) res.push_back(T);
	}
	if(op=="3"){
		cout<<"请输入关键字:";
		string x;cin>>x;
		st=clock();
		for(auto T:dev){
			if(T.id==x or T.nme==x or T.rcp==x or T.dpt==x \
				or T.sum==x or T.tme==x or T.prc==x){
				res.push_back(T);
			}
		}
	}
	clock_t ed=clock();
	if(res.size()>0){
		cout<<"查询到 "<<res.size()<<" 条记录, 耗时 "<<ed-st<<" 毫秒\n";
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
		if(op==2) {SaveDev("query.out",res,"res");}
	}
	else cout<<"无法查询到此设备.\n";
	ReturnMenu();
}

void DeletDev(){//信息删除
	putchar('\n');
	cout<<"*******************\n";
	cout<<"*  1-按序列号删除  *\n";
	cout<<"*  2-全部删除      *\n";
	cout<<"*******************\n";
	cout<<"->请选择操作:";
	string op;cin>>op;
	while(!CmpStr("1",op,"2")){
		cout<<"输入有误!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	if(op=="1"){
		cout<<"请输入待删除数据的序列号:";
		string num;cin>>num;
		while(!CmpStr("1",num,to_string((int)dev.size()))){
			cout<<"非法序列号，请重新输入:";
			cin>>num;
		}
		dev.erase(dev.begin()+atoi(num.c_str())-1);
	}
	if(op=="2"){
		dev.clear();
		cout<<"已清空数据\n";
	}
	SaveDev("dev.out",dev,"dev");
	ReturnMenu();
}

bool CmpStr(string x1,string x2){//对string以数字大小排序,而非字典序
	if(x1==x2) return false;
	else if(x1.length()!=x2.length()) return x1.length()<x2.length();
	else return x1<x2;
}

bool CmpStr(string x1,string x2,string x3){//判断区间
	if(x1==x2 or x2==x3) return true;
	else return (CmpStr(x1,x2) and CmpStr(x2,x3));
}

bool CmpTme(string x1,string x2){//对购买时间排序
    string year1(x1.begin(),x1.begin()+4),year2(x2.begin(),x2.begin()+4);
    if(year1!=year2) return CmpStr(year1,year2);
    int p1=0,p2=0;
    FOR(i,5,7) if(x1[i]=='.'){p1=i;break;}
    FOR(i,5,7) if(x2[i]=='.'){p2=i;break;}
    string month1(x1.begin()+5,x1.begin()+p1),month2(x2.begin()+5,x2.begin()+p2);
    if(month1!=month2) return CmpStr(month1,month2);
    string day1=x1.substr(p1+1),day2=x2.substr(p2+1);
    return CmpStr(day1,day2);
}

bool CmpTme(string x1,string x2,string x3){//判断区间
	if(x1==x2 or x2==x3) return true;
	else return (CmpTme(x1,x2) and CmpTme(x2,x3));
}

void sort(vector<device>::iterator st, vector<device>::iterator ed,int op){
    switch(op){
		case 1: sort(st,ed,[](device x,device y){return CmpStr(x.id,y.id);});break;
		case 2: sort(st,ed,[](device x,device y){return CmpStr(x.sum,y.sum);});break;
		case 3: sort(st,ed,[](device x,device y){return CmpTme(x.tme,y.tme);});break;
		case 4: sort(st,ed,[](device x,device y){return CmpStr(x.prc,y.prc);});break;
		case 5: sort(st,ed,[](device x,device y){return !CmpStr(x.id,y.id);});break;
		case 6: sort(st,ed,[](device x,device y){return !CmpStr(x.sum,y.sum);});break;
		case 7: sort(st,ed,[](device x,device y){return !CmpTme(x.tme,y.tme);});break;
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
	string op;cin>>op;
	while(!CmpStr("1",op,"8")){
		cout<<"非法输入!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	clock_t st=clock();
	sort(dev.begin(),dev.end(),atoi(op.c_str()));
	clock_t ed=clock();
	cout<<"排序完成, 耗时 "<<ed-st<<" 毫秒\n";
	SaveDev("dev.out",dev,"dev");
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

void FilterDev(){//筛选设备信息
	putchar('\n');
	cout<<"*******************\n";
	cout<<"*  1-按设备数量筛选 *\n";
	cout<<"*  2-按购买时间筛选 *\n";
	cout<<"*  3-按价格筛选    *\n";
	cout<<"*******************\n";
	cout<<"->请选择操作:";
	string op;cin>>op;
	while(!CmpStr("1",op,"3")){
		cout<<"输入有误!\n";
		cout<<"->请选择操作:";
		cin>>op;
	}
	vector<device> res;
	string l,r;
	clock_t st=clock();
	if(op=="1"){
		cout<<"请输入筛选范围(例:666 2333):";
		cin>>l>>r;
		st=clock();
		for(auto T:dev) if(CmpStr(l,T.sum,r)) res.push_back(T);
	}
	if(op=="2"){
		cout<<"请输入筛选范围(例:2042.1.1 2077.12.31):";
		cin>>l>>r;
		st=clock();
		for(auto T:dev) if(CmpTme(l,T.tme,r)) res.push_back(T);
	}
	if(op=="3"){
		cout<<"请输入筛选范围(例:6666 23333):";
		cin>>l>>r;
		st=clock();
		for(auto T:dev) if(CmpStr(l,T.prc,r)) res.push_back(T);
	}
	clock_t ed=clock();
	if(res.size()>0){
		cout<<"筛选到 "<<res.size()<<" 条记录, 耗时 "<<ed-st<<" 毫秒\n";
		putchar('\n');
		cout<<"*******************\n";
		cout<<"*  1-打印到屏幕    *\n";
		cout<<"*  2-保存到文件    *\n";
		cout<<"*******************\n";
		cout<<"->请选择操作:";
		string op;cin>>op;
		while(!CmpStr("1",op,"2")){
			cout<<"输入有误!\n";
			cout<<"->请选择操作:";
			cin>>op;
		}
		if(op=="1") {for(auto T:res) PutDev(T);}
		if(op=="2") {SaveDev("filter.out",res,"res");}
	}
	else cout<<"无法查询到此设备.\n";
	ReturnMenu();
}

void UndoDev(){//撤销操作
	putchar('\n');
	if(backup.size()==1) dev.clear();
	else if(backup.size()==2) swap(dev,backup[0]);
	cout<<"已撤销上次操作\n";
	SaveDev("dev.out",dev,"dev");
	ReturnMenu();
}