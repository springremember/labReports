/*************************************************************************
    > File Name: first.h
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年12月02日 星期六 21时48分37秒
 ************************************************************************/

#include<iostream>
#include <vector>
#include <queue>
using namespace std;

float first(vector<int> process,int limit,int amount)
{
	vector<int> v;
	int flag=0;
	int counter=0;	
	queue<int> q;
	for (int i = 0; i < amount; ++i)
	{
		// cout<<"页面号："<<process[i]<<'\t'<<'\t';
		if (q.size()<limit)
		{
			q.push(v.size());
			v.push_back(process[i]);
			// show(v);
		}
		else
		{
			flag=0;
			for (int j = 0; j < v.size(); ++j)
			{
				if (process[i]==v[j])
				{
					flag=1;
					break;
				}
			}
			if (flag==0)
			{
				v[q.front()]=process[i];
				q.push(q.front());
				q.pop();
				counter++;
				// show(v);
			}

		}
		// cout<<endl;
	}
	// cout<<endl;
	// cout<<"置换次数："<<counter<<endl;
	float xyz=counter/(float)amount;
	cout<<"缺页率："<<xyz*100<<"%"<<'\t'<<'\t';
	return xyz;
}