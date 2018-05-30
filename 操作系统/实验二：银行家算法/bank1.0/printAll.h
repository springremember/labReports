using namespace std;

int printAll(int **Max,int **Allocation,int **need,int *Available,int m,int n)
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

}
