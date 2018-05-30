#include<iostream>
#include<cmath>
#include <vector>
#include"class.h"
#include"showPageStruct.h"
#include "addProcess.h"
#include"showProcess.h"
#include "deleteProcess.h"
#include"search.h"

using namespace std;

int main()
{
	int memorySum=10240;
	// cout<<"请输入内存总大小(单位kb)："<<endl;
	// cin>>memorySum;
	
	int memorySize;
	cout<<"请输入页面块大小(单位kb):"<<endl;
	cin>>memorySize;

	int memoryCounter;
	memoryCounter=ceil(memorySum/memorySize);

	pageStruct *ps=new pageStruct[memoryCounter];

	vector<processStart> v;

	int* memoryBlock=new int[memoryCounter];

	for(int i=0;i<memoryCounter;i++)
	{
		ps[i].page=i;
		ps[i].block=-1;
		ps[i].next=-1;
	}



	for(int i=0;i<memoryCounter;i++)
	{
		memoryBlock[i]=-1;
	}

	int choose;
	int end=0;
	while(1)
	{
		cout<<endl;
		cout<<"欢迎使用内存管理系统！"<<endl;
		cout<<"1.查看当前内存页表"<<endl;
		cout<<"2.查看当前进程内存占用情况"<<endl;
		cout<<"3.新增进程"<<endl;
		cout<<"4.删除进程并释放内存"<<endl;
		cout<<"5.根据逻辑地址输出物理地址"<<endl;
		cout<<"6.退出内存管理系统"<<endl;
		cout<<"请根据编号进行选择：";
		cin>>choose;
		cout<<endl;
		switch(choose)
		{
		case 1:
			showPageStruct(ps,memoryCounter);
			break;
		case 2:
			showProcess(v);
			break;
		case 3:
			addProcess(v,ps,memoryCounter,memorySize,memoryBlock);
			break;
		case 4:
			deleteProcess(v,ps,memoryBlock);
			break;
		case 5:
			search(ps,memorySize);
			break;
		case 6:
			end=1;
			break;
		default:
			cout<<"错误的输入，请重新选择功能！"<<endl;
			break;
		}
		if (end==1)
			break;
	}
	return 0;
}
