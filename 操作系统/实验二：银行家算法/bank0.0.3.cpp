/*************************************************************************
    > File Name: bank1.0.cpp
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年11月04日 星期六 15时30分08秒
 ************************************************************************/

#include<iostream>
#include <fstream>  
#include <string>
using namespace std;

//读取文件的数据,并赋值给一维数组
void openFile(const char *filePath,int *p,int num)
{
	ifstream file;  
	file.open(filePath,ios::in);  
	
	if(!file.is_open())
		cout<<"文件不存在，读取错误。"<<endl;
	std::string strLine;
	for (int i = 0; i < num; ++i)
	{
		getline(file,strLine);
		p[i]=std::stoi(strLine);
	}
}

//读取文件数据，并赋值给二维数组
void openFilePlus(const char *filePath,int **p,int n,int m)
{
	ifstream file;  
	file.open(filePath,ios::in);  
	
	if(!file.is_open())
		cout<<"文件不存在，读取错误。"<<endl;
	std::string strLine;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			getline(file,strLine);
			p[i][j]=std::stoi(strLine);
		}
	}	
}

int safety(int *Available,int **Max,int **Allocation,int **need,int m,int n)
{
	int *order=new int(n);
	int *Work=new int(m);
	int *Finish=new int(n);
	int **workLoad=new int*[n];
	for (int i = 0; i < n; ++i)
	{
		workLoad[i]=new int(m);
	}
	for (int i=0;i<m;++i)
	{
		Work[i]=Available[i];
	}
	for (int i=0;i<n;++i)
	{
		Finish[i]=0;
	}
	int counter=0;
	while(1)
		{
			int choose;
			choose=-1;
			int ready;
			ready=0;
			for(int i=0;i<n;i++)
			{
				if(Finish[i]==0)
				{
					for(int j=0;j<m;j++)
					{
						if(need[i][j]>Work[j])
							ready=-1;
					}
					if(ready==-1)
					{
						ready=0;
					}
					else
					{
						choose=i;
						break;
					}
				}
			}
			if(choose==-1)
			{
				break;
			}
			order[counter]=choose;
			counter++;
			for(int i=0;i<m;i++)
			{
				Work[i]=Work[i]+Allocation[choose][i];
				workLoad[choose][i]=Work[i];
			}
			Finish[choose]=1;
		}
		int flag=0;
		for(int i=0;i<n;i++)
		{
			if(Finish[i]==0)
			{
				flag=1;
			}
		}
		if(flag)
		{
			cout<<"不安全的序列,已经撤销资源分配"<<endl;
			return 1;
		}
		else
		{
			cout<<'\t'<<"Work"<<'\t'<<'\t'<<"Need"<<'\t'<<'\t'<<"Allocation"<<'\t'<<"Work+Allocation"<<'\t'<<"Finish"<<endl;
			cout<<'\t'<<"A  B  C"<<'\t'<<'\t'<<"A  B  C"<<'\t'<<'\t'<<"A  B  C"<<'\t'<<'\t'<<"A  B  C"<<endl;
			for (int i = 0; i < n; ++i)
			{
				cout<<"P"<<i<<'\t';
			for(int j=0;j<m;j++)
			{
				cout<<workLoad[i][j]<<"  ";
			}
			cout<<'\t';
			for(int j=0;j<m;j++)
			{
				cout<<need[i][j]<<"  ";
			}
			cout<<'\t';
			for(int j=0;j<m;j++)
			{
				cout<<Allocation[i][j]<<"  ";
			}
			cout<<'\t';
			for(int j=0;j<m;j++)
			{
				cout<<workLoad[i][j]+Allocation[i][j]<<"  ";
			}
			cout<<'\t';
			cout<<Finish[i]<<endl;
			cout<<endl;
			}
			cout<<"安全状态"<<endl; 
			cout<<"安全序列为：";
			for (int i = 0; i < n; ++i)
			{
				cout<<order[i]<<'\t';
			}
			cout<<endl;
		}
	return 0;
 } 


int main()
{
	int m=3;
	int n=5;
	//读取Available文件，为Available数组赋值。
	int *Available=new int(m);
	openFile("Available.txt",Available,m);

	//读取Max文件，为Max数组赋值
	int **Max=new int*[n];
	for (int i = 0; i < n; ++i)
	{
		Max[i]=new int(m);
	}
	openFilePlus("Max.txt",Max,n,m);

	//读取Allocation文件，为Allocation数组赋值
	int **Allocation=new int*[n];
	for (int i = 0; i < n; ++i)
	{
		Allocation[i]=new int(m);
	}
	openFilePlus("Allocation.txt",Allocation,n,m);

	//读取need文件，为need数组赋值
	int **need=new int*[n];
	for (int i = 0; i < n; ++i)
	{
		need[i]=new int(m);
	}
	openFilePlus("need.txt",need,n,m);

	//声明请求的变量
	int requesetProcess;
	int *requeset=new int(m);

	//循环所需的提示变量
	int flag1;
	int flag2;
	int flag3;
	int spring;

	while(1)
	{
		cout<<endl;
		cout<<endl;
		cout<<'\t'<<"MAX"<<'\t'<<'\t'<<"Allocation"<<'\t'<<"Need"<<'\t'<<'\t'<<"Available"<<endl;
		cout<<'\t'<<"A  B  C"<<'\t'<<'\t'<<"A  B  C"<<'\t'<<'\t'<<"A  B  C"<<'\t'<<'\t'<<"A  B  C"<<endl;
		for(int i=0;i<n;i++)
		{
			cout<<"P"<<i<<'\t';
			for(int j=0;j<m;j++)
			{
				cout<<Max[i][j]<<"  ";
			}
			cout<<'\t';
			for(int j=0;j<m;j++)
			{
				cout<<Allocation[i][j]<<"  ";
			}
			cout<<'\t';
			for(int j=0;j<m;j++)
			{
				cout<<need[i][j]<<"  ";
			}
			cout<<'\t';
			if(i==0)
			{
				for(int j=0;j<m;j++)
				{
					cout<<Available[j]<<"  ";
				}			
			}
			cout<<endl;
		}


		//循环运行函数
		while(1)
		{
			//将提示变量赋值为0
			flag1=0;
			flag2=0;
			flag3=0;
			cout<<"请输入请求进程的序号："<<endl;
			cin>>requesetProcess;
			for (int i = 0; i < m; ++i)
			{
				cout<<"请输入该进程第"<<i<<"个资源的请求量："<<endl;
				cin>>requeset[i];
			}

			//银行家算法第一步
			//如果存在请求大于Need，flag1=1，出错。
			for (int i = 0; i < m; ++i)
			{
				if (requeset[i]>need[requesetProcess][i])
				{
					flag1=1;
				}
			}
			//判断flag1是否为1，如果是1，为flag2，flag3赋值为1，也就是跳过下面所有语句
			if (flag1==1)
			{
				flag2=1;
				flag3=1;
				cout<<"所需要资源超过他宣布的最大值"<<endl;
			}

			//如果flag1=0，开始银行家算法第二步
			if (flag1==0)
			{
				for (int i = 0; i < m; ++i)
				{
					if (requeset[i]>Available[i])
					{
						flag2=1;
					}
				}
				if (flag2==1)
				{
					flag3=1;
					cout<<"超过系统所能分配的资源"<<endl;
				}
		
				if(flag2==0)
				{
					for(int i=0;i<m;i++)
					{
						Available[i]=Available[i]-requeset[i];
						Allocation[requesetProcess][i]=Allocation[requesetProcess][i]+requeset[i];
						need[requesetProcess][i]=need[requesetProcess][i]-requeset[i];
					}
					//安全性算法 
					spring=safety(Available,Max,Allocation,need,m,n);
					if (spring)
					{
						for(int i=0;i<m;i++)
						{
							Available[i]=Available[i]+requeset[i];
							Allocation[requesetProcess][i]=Allocation[requesetProcess][i]-requeset[i];
							need[requesetProcess][i]=need[requesetProcess][i]+requeset[i];
						}
					}
					break;
					
				}
		
			}
			

			//判断流程

		}
	}
	return 0;
}

