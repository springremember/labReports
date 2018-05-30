#include<iostream>
#include <cmath>
#include<vector>
#include <ctime>

using namespace std;

//用于随机寻找一个物理块保存信息，并返回找到的物理块号。
int setMemoryBlock(int* memoryBlock,int memoryCounter)
{
	// for (int i = 0; i < memoryCounter; ++i)
	// {
	// 	if (memoryBlock[i]==-1)
	// 	{
	// 		memoryBlock[i]=1;
	// 		return i;
	// 	}
	// }
	// return -1;
	srand((unsigned)time(0));
	int randnum;
	while(1)
	{
		randnum=rand()%memoryCounter;
		if (memoryBlock[randnum]==-1)
		{
			memoryBlock[randnum]=1;
			return randnum;
			break;
		}
	}
	return -1;
}


//第一层循环是进程所需块数，第二层循环用于找一个空闲页号，并调用setMemoryBlock函数设置物理块号。
int changeMemory(pageStruct* ps,int memoryCounter,int tempCounter,int* memoryBlock)
{
	for (int i = 0; i < tempCounter-1; ++i)
	{

		for (int j = 0; j < memoryCounter; ++j)
		{
			if (ps[j].block==-1)
			{
				ps[j].block=setMemoryBlock(memoryBlock,memoryCounter);
				for (int k = j+1; k < memoryCounter; ++k)
				{
					if (ps[k].block==-1)
					{
						ps[j].next=k;
						break;
					}
				}
				break;
			}
		}
	}
	for (int i = 0; i < memoryCounter; ++i)
	{
		if (ps[i].block==-1)
		{
			ps[i].block=setMemoryBlock(memoryBlock,memoryCounter);
			ps[i].next=-2;
			break;
		}
	}
	return 0;
}

//添加进程函数，在用户输入进程大小后，查找到页表，找到第一个空闲页号。并使用这个页号调用进程新增函数。
int  addProcess(vector<processStart >& v,pageStruct *ps,int memoryCounter,int memorySize,int* memoryBlock)
{
	int tempCounter;
	processStart temp;
	temp.id=v.size();
	cout<<"该进程编号为"<<v.size()<<endl;
	cout<<"请输入进程占用内存大小:";
	cin>>temp.size;
	tempCounter=ceil((double)temp.size/memorySize);
	int start;
	for (int i = 0; i < memoryCounter; ++i)
	{
		if (ps[i].block==-1)
		{
			start=i;
			break;
		}
	}
	temp.start=start;
	v.push_back(temp);

	changeMemory(ps,memoryCounter,tempCounter,memoryBlock);
	return 0;
}