#include<iostream>
using namespace std;

int deleteit(int start,pageStruct *ps,int* memoryBlock)
{
	int now=start;
	int temp;
	while(1)
	{
		if(ps[now].next==-2)
		{
			memoryBlock[ps[now].block]=-1;
			ps[now].block=-1;
			break;
		}
		memoryBlock[ps[now].block]=-1;
		ps[now].block=-1;
		temp=ps[now].next;
		ps[now].next=-1;
		now=temp;
	}
	return 0;
}

int deleteProcess(vector<processStart>& v,pageStruct *ps,int* memoryBlock)
{
	int start=0;
	int deleteid;
	cout<<"请输入要释放进程的序号:"<<endl;
	cin>>deleteid;
	for(int i=0;i<v.size();i++)
	{
		if(v[i].id==deleteid)
		{
			start=v[i].start;
			v.erase(v.begin()+i);
			break;
		}
	}
	deleteit(start,ps,memoryBlock);
}
