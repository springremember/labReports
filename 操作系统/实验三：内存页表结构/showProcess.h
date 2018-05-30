#include <iostream>

using namespace std;

int showProcess(vector<processStart >& v)
{
	cout<<"进程编号"<<'\t'<<"进程大小"<<'\t'<<"进程起始页号"<<endl;
	for (int i = 0; i < v.size(); ++i)
	{
		cout<<v[i].id<<'\t'<<'\t'<<v[i].size<<'\t'<<'\t'<<v[i].start<<endl;
	}
	return 0;
}