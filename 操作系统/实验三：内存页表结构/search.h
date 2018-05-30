/*************************************************************************
    > File Name: search.h
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年11月28日 星期二 10时12分04秒
 ************************************************************************/

#include<iostream>
using namespace std;

int search(pageStruct* ps,int memorySize)
{
	int pageAddress;
	int p;
	int d;
	int address;
	cout<<"请输入逻辑地址：";
	cin>>pageAddress;
	p=int(pageAddress/(memorySize*1024));	
	if(ps[p].block==-1)
		cout<<"无效的逻辑地址"<<endl;
	else
	{
		d=(pageAddress % (memorySize*1024));
		address=ps[p].block*1024*memorySize+d;
		cout<<"逻辑地址"<<pageAddress<<"对应的块号为:"<<address<<endl;
	}
}
