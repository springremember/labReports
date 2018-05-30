/*************************************************************************
    > File Name: bank1.0.cpp
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年11月04日 星期六 15时30分08秒
 ************************************************************************/

#include<iostream>
#include <fstream>  
#include <string>
#include"openFile.h"
#include"openFilePlus.h"
#include"safety.h"
#include"printAll.h"
#include"bank.h"
#include"bankFor.h"
using namespace std;

void getDate(int* Available,int** Allocation,int** Max,int** need,int m,int n)
{
	openFile("Available.txt",Available,m);
	openFilePlus("Max.txt",Max,n,m);
	openFilePlus("Allocation.txt",Allocation,n,m);
	openFilePlus("need.txt",need,n,m);
}

int main(void)
{
	int m=3;
	int n=5;
	//读取Available文件，为Available数组赋值。
	int *Available=new int(m);

	//读取Max文件，为Max数组赋值
	int **Max=new int*[n];
	for (int i = 0; i < n; ++i)
	{
		Max[i]=new int(m);
	}

	//读取Allocation文件，为Allocation数组赋值
	int **Allocation=new int*[n];
	for (int i = 0; i < n; ++i)
	{
		Allocation[i]=new int(m);
	}

	//读取need文件，为need数组赋值
	int **need=new int*[n];
	for (int i = 0; i < n; ++i)
	{
		need[i]=new int(m);
	}
	int xyz;
	while(1)
	{
		cout<<"请选择功能："<<endl;
		cout<<"1.银行家算法"<<endl;
		cout<<"2.直接分配法"<<endl;
		cout<<"其他输入直接退出"<<endl;
		cin>>xyz;
		if(xyz==1)
		{
			getDate(Available,Allocation,Max,need,m,n);
			bank(Available,Allocation,Max,need,m,n);
		}
		else if(xyz==2)
		{
			getDate(Available,Allocation,Max,need,m,n);
			bankFor(Available,Allocation,Max,need,m,n);
		}
		else
		{
			break;
		}
	}
	return 0;
}

