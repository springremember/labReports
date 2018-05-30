#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class process
{
	public:
		int ID;
		int arriveTime;
		int runTime;
		char state;
		int startTime;
		int priority;
		int runedTime;
		int finish_time;
		
		process()
		{
			state='R';
			runedTime=0;
		}
};

int FCFS(process* pro,int *p,int pnum)
{
	int finish_time=0;
	for(int i=0;i<pnum;i++)
	{
		if(finish_time<pro[p[i]].arriveTime)
		{
			finish_time=pro[p[i]].arriveTime;
			finish_time=finish_time+pro[p[i]].runTime;
			pro[p[i]].startTime=pro[p[i]].arriveTime;
			pro[p[i]].state='C';
		}
		else
		{
			pro[p[i]].startTime=finish_time;
			pro[p[i]].state='C';
			finish_time=finish_time+pro[p[i]].runTime;
		}
	}
	for (int i = 0; i < pnum; ++i)
	{
		pro[p[i]].finish_time=pro[p[i]].startTime+pro[p[i]].runTime;
	}
	cout<<"完成时间："<<finish_time<<endl; 
	return 0;
}

int PSA(process* pro2,int *p,int pnum)
{
	int temp;
	int arriveCount=1;
	int finishTime;
	int nowProcess=0;
	int workTime=pro2[p[0]].arriveTime;
	finishTime=pro2[p[0]].arriveTime+pro2[p[0]].runTime;
	cout<<"运行顺序："<<nowProcess+1<<"->";

	while(1)
	{

		if (arriveCount==pnum)
		{
			break;
		}

		if (pro2[p[arriveCount]].arriveTime<finishTime)
		{
			workTime=pro2[p[arriveCount]].arriveTime;
			if (pro2[p[arriveCount]].priority>pro2[p[nowProcess]].priority)
			{
				pro2[p[nowProcess]].runedTime=finishTime-pro2[p[arriveCount]].arriveTime;
				pro2[p[nowProcess]].runedTime=pro2[p[nowProcess]].runTime-pro2[p[nowProcess]].runedTime;
				finishTime=pro2[p[arriveCount]].arriveTime+pro2[p[arriveCount]].runTime;
				nowProcess=arriveCount;
				cout<<nowProcess+1<<"->";
				arriveCount++;
			}
			else
			{
				arriveCount++;
			}
		}
		else
		{
			workTime=finishTime;
			pro2[p[nowProcess]].finish_time=workTime;
			pro2[p[nowProcess]].state='C';
			temp=-1;
			for (int i = 0; i < arriveCount; ++i)
			{
				if (pro2[p[i]].state=='R')
				{
					temp=i;
					break;
				}
			}
			if (temp!=-1)
			{
				for (int i = 0; i < arriveCount; ++i)
				{
					if (pro2[p[i]].state=='R' && pro2[p[temp]].priority<pro2[p[i]].priority)
					{
						temp=i;
					}
				}
			}
			if (temp==-1)
			{
				finishTime=9999999;
			}
			else
			{
				nowProcess=temp;
				cout<<nowProcess+1<<"->";
				finishTime=workTime+pro2[p[nowProcess]].runTime-pro2[p[nowProcess]].runedTime;
			}
		}
	}
	pro2[p[nowProcess]].finish_time=finishTime;
	pro2[p[nowProcess]].state='C';
	workTime=finishTime;
	nowProcess=-1;

	while(1)
	{
		nowProcess=-1;
		for (int i = 0; i < pnum; ++i)
		{
			if (pro2[p[i]].state=='R')
			{
				nowProcess=i;
			}
		}
		if (nowProcess==-1)
		{
			break;
		}
		for (int i = 0; i < pnum; ++i)
		{
			if (pro2[p[i]].state=='R' && pro2[p[i]].priority>pro2[p[nowProcess]].priority)
			{
				nowProcess=i;
			}
		}
		cout<<nowProcess+1<<"->";
		workTime=workTime+pro2[p[nowProcess]].runTime-pro2[p[nowProcess]].runedTime;
		pro2[p[nowProcess]].state='C';
		pro2[p[nowProcess]].finish_time=workTime;
	}
	cout<<"结束"<<endl;
	cout<<"完成时间："<<workTime;
	return 0;
}

int main(int argc, char const *argv[])
{
	//由运行时间随机生成一个数，用于做种子 
	cout<<"请输入进程数："<<endl;
	int pnum;
	cin>>pnum;
	srand((unsigned)time(0));
	int num=rand()%10+1;
	//为ID赋值 

	process *spring=new process[pnum];
	process *spring2=new process[pnum];
	cout<<"下面是两种算法比较"<<endl;
	//按顺序生成ID
	for(int m=0;m<pnum;m++)
	{
		spring[m].ID=m;
		spring2[m].ID=m;
	}
	//随机生成到达时间
	int j;
	for(int i=0;i<pnum;i++)
	{
		srand(i+num);
		j=rand()%200+1;
		spring[i].arriveTime=j;
		spring2[i].arriveTime=j;
	}
	//随机生成优先级
		for(int i=0;i<pnum;i++)
	{
		srand(34-i-num);
		j=rand()%100+1;
		spring[i].priority=j;
		spring2[i].priority=j;
	}
	//随机生成运行时间
		for(int i=0;i<pnum;i++)
	{
		srand(11+i-num);
		j=rand()%100+1;
		spring[i].runTime=j;
		spring2[i].runTime=j;
	}
	
	//以上为进程类赋值
	
	//p[i]按到达顺序保存序号
	int *p=new int(pnum);
	for(int i=0;i<pnum;i++)
	{
		p[i]=i;
	} 


	int temp;
	for(int i=0;i<pnum;i++)
	{
		for(int m=pnum-1;m>i;m--)
		{
			if(spring[p[m]].arriveTime<spring[p[m-1]].arriveTime)
			{
				temp=p[m];
				p[m]=p[m-1];
				p[m-1]=temp;
			}
		}
	}

	cout<<"请选择程序功能："<<endl;
	cout<<"1.先来先服务算法"<<endl;
	cout<<"2.优先级算法"<<endl;
	cout<<"3.两种算法同步比较"<<endl;
	int chooseFor;
	cin>>chooseFor;

	if (chooseFor==1)
		{
			int sum=0;
			cout<<"以下是先来先服务算法的结果："<<endl;
			FCFS(spring,p,pnum);
			cout<<"作业	提交时间	运行时间	开始时间	完成时间	周转时间："<<endl;
			for(int i=0;i<pnum;i++)
			{
				cout<<i+1<<'\t'<<spring[p[i]].arriveTime<<'\t'<<'\t'<<spring[p[i]].runTime<<'\t'<<'\t'<<spring[p[i]].startTime
				<<'\t'<<'\t'<<spring[p[i]].finish_time<<'\t'<<'\t'<<spring[p[i]].finish_time-spring[p[i]].arriveTime<<endl;
			}
			for (int i = 0; i < pnum; ++i)
			{
				sum=sum+spring[p[i]].finish_time-spring[p[i]].arriveTime;
			}
			cout<<"平均周转时间："<<sum/pnum<<endl;
		}

	if (chooseFor==2)
	{
		cout<<endl;
		cout<<"以下是优先度算法的结果："<<endl;
		PSA(spring2,p,pnum);
		cout<<'\n'<<"作业	提交时间	运行时间	完成时间	优先级	 	周转时间："<<endl;
		for(int i=0;i<pnum;i++)
		{
			cout<<i+1<<'\t'<<spring2[p[i]].arriveTime<<'\t'<<'\t'<<spring2[p[i]].runTime<<'\t'<<'\t'<<spring2[p[i]].finish_time<<'\t'<<'\t'<<spring2[p[i]].priority<<'\t'<<'\t'<<spring2[p[i]].finish_time-spring2[p[i]].arriveTime<<endl;
		}
		int sum=0;
		for (int i = 0; i < pnum; ++i)
		{
			sum=sum+spring2[p[i]].finish_time-spring2[p[i]].arriveTime;
		}
		cout<<"平均周转时间："<<sum/pnum<<endl;
	}

	if (chooseFor==3)
	{
		int sum=0;
		cout<<"以下是先来先服务算法的结果："<<endl;
		FCFS(spring,p,pnum);
		cout<<"作业	提交时间	运行时间	开始时间	完成时间	周转时间："<<endl;
		for(int i=0;i<pnum;i++)
		{
			cout<<i+1<<'\t'<<spring[p[i]].arriveTime<<'\t'<<'\t'<<spring[p[i]].runTime<<'\t'<<'\t'<<spring[p[i]].startTime
			<<'\t'<<'\t'<<spring[p[i]].finish_time<<'\t'<<'\t'<<spring[p[i]].finish_time-spring[p[i]].arriveTime<<endl;
		}
		for (int i = 0; i < pnum; ++i)
		{
			sum=sum+spring[p[i]].finish_time-spring[p[i]].arriveTime;
		}
		cout<<"平均周转时间："<<sum/pnum<<endl;



		cout<<endl;
		cout<<endl;
		cout<<"以下是优先度算法的结果："<<endl;
		PSA(spring2,p,pnum);
		cout<<'\n'<<"作业	提交时间	运行时间	完成时间	优先级		周转时间："<<endl;
		for(int i=0;i<pnum;i++)
		{
			cout<<i+1<<'\t'<<spring2[p[i]].arriveTime<<'\t'<<'\t'<<spring2[p[i]].runTime<<'\t'<<'\t'<<spring2[p[i]].finish_time<<'\t'<<'\t'<<spring2[p[i]].priority<<'\t'<<'\t'<<spring2[p[i]].finish_time-spring2[p[i]].arriveTime<<endl;
		}
		sum=0;
		for (int i = 0; i < pnum; ++i)
		{
			sum=sum+spring2[p[i]].finish_time-spring2[p[i]].arriveTime;
		}
		cout<<"平均周转时间："<<sum/pnum<<endl;
	}

	return 0;
}