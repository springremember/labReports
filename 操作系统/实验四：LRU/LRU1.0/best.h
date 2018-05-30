/*************************************************************************
    > File Name: best.h
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年12月02日 星期六 21时35分07秒
 ************************************************************************/

#include<iostream>
using namespace std;

float best(vector<int> &process,int limit,int amount)
{
	vector<int> v;
	int choose=-1;
	int flag=0;
	int counter=0;
	for (int i = 0; i < amount; ++i)
	{
		// cout<<"页面号为:"<<process[i]<<'\t';
		if (v.size()<limit)
		{
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
				choose=select(process,v,i,amount);
				v[choose]=process[i];
				// show(v);
				counter++;
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