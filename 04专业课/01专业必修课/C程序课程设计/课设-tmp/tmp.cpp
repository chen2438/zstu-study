#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;

string int2str2(int num){
    string str2;
    str2=to_string(num);
    return str2;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    //clock_t st=clock();
    //freopen("input.txt","r",stdin);
    freopen("dev(1e2).in","w",stdout);
    int id,prc,amt;
    string ids,prcs,nme,rcp,dpt,amts,dat;
    srand(time(0));
    int n=2e5;
    FOR(i,1,n){
        id=rand()%100000+1;
        ids=int2str2(id);
        int lenids=ids.size();
        if(lenids<7){
            FOR(i,1,7-lenids) ids="0"+ids;
        }
        prc=rand()%10000+1000;
        amt=rand()%500+10;
        nme=rcp=dpt="";
        FOR(i,1,7){
            int rs=rand()%24;
            char c=rs+'a';
            nme+=c;
        }
        FOR(i,1,7){
            int rs=rand()%24;
            char c=rs+'a';
            rcp+=c;
        }
        FOR(i,1,7){
            int rs=rand()%24;
            char c=rs+'a';
            dpt+=c;
        }
        dat="";
        dat+=int2str2(rand()%70+1950)+"."+int2str2(rand()%12+1)+"."+int2str2(rand()%29+1);
        cout<<ids<<" "<<nme<<" "<<rcp<<" "<<dpt<<" "<<amt<<" "<<dat<<" "<<prc<<endl;

    }
    //fclose(stdout);
    clock_t ed=clock();
    //cout<<ed-st;
    return 0;
}