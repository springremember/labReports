using namespace std;

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
