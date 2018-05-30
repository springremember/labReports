/*************************************************************************
    > File Name: LRU.h
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年12月02日 星期六 21时57分50秒
 ************************************************************************/

#include<vector>
using namespace std;

float LRU(vector<int> process,int limit,int amount)
{
	vector<int> v;
	int counter=0;
	int flag;
	int visit;
	for (int i = 0; i < amount; ++i)
	{
		// cout<<"页面号："<<process[i]<<'\t'<<'\t';
		if(v.size()<limit)
		{
			v.push_back(process[i]);
			// show(v);
		}
		else
		{
			flag=0;
			visit=-1;
			for (int j = 0; j < v.size(); ++j)
			{
				if (process[i]==v[j])
				{
					flag=1;
					visit=j;
					break;
				}
			}
			if (flag==0)
			{
				v[0]=process[i];
			}
			else
			{
				getVisitTop(v,visit);
				counter++;
			}
			// show(v);
		}
		// cout<<endl;
	}
	// cout<<endl;
	// cout<<"置换次数："<<counter<<endl;
	float xyz=counter/(float)amount;
	cout<<"缺页率："<<xyz*100<<"%"<<endl;
	return xyz;
}