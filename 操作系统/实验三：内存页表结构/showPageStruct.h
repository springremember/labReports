using namespace std;

int showPageStruct(pageStruct* ps,int memoryCounter)
{
	cout<<"页号"<<'\t'<<'\t'<<'\t'<<"块号"<<endl;
	for(int i=0;i<memoryCounter;i++)
	{
		if(ps[i].block==-1)
			continue;
		else
			cout<<ps[i].page<<'\t'<<'\t'<<'\t'<<ps[i].block<<endl;
	}
	return 0;
};