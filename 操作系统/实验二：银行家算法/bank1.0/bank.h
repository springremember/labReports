using namespace std;

int bank(int *Available,int **Allocation,int **Max,int **need,int m,int n)
{
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
		printAll(Max,Allocation,need,Available,m,n);
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
					int count=0;
					if (spring)
					{
						for(int i=0;i<m;i++)
						{
							Available[i]=Available[i]+requeset[i];
							Allocation[requesetProcess][i]=Allocation[requesetProcess][i]-requeset[i];
							need[requesetProcess][i]=need[requesetProcess][i]+requeset[i];
						}
					}
					else
					{
						for(int i=0;i<n;i++)
						{
							for (int j = 0; j < m; ++j)
							{
								count=count+need[i][j];
							}
							if (count==0)
							{
								for(int k=0;k<m;k++)
								{
									Available[k]=Available[k]+Allocation[i][k];
									Allocation[i][k]=0;
								}
							}
							count=0;
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