/*
	# 程序最初于 Jun 12, 2022 由 chen2438 提交在 github.com/chen2438/zstu-study/
	# 当前版本 upd12 v1.9 release1.3
	# 提交时间 2022.6.23 15:42
	# 遵循 GNU General Public License v3.0 协议
*/

#pragma GCC optimize(2)//开启O(2)优化
//#define debug
#include "dev.h"

int main(){
	#ifndef debug
	ShowMenu();//人机交互主界面
	#endif

	#ifdef debug
	for(int i=0;i<10;i++)ImportTest("dev(1e6).in");//测试
	#endif

	return 0;
}