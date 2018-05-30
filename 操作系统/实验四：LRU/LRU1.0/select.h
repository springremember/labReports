/*************************************************************************
    > File Name: select.h
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年12月02日 星期六 21时32分12秒
 ************************************************************************/
#include <vector>

using namespace std;

int select(vector<int> process,vector<int> v,int start,int amount)
{
	//choose即被置换的页面，先设置为0，起始
	int choose=0;
	int best; //best用于保存这个起始值，下一次遇到的间隔，下面为其赋值
	for (int i = start; i < amount; ++i)
	{
		if (process[i]==v[choose])
		{
			best=i-start;
			break;
		}
		if (i==amount-1)
		{
			return 0;
		}
	}
	for (int i = 1; i < v.size(); ++i)
	{
		for (int j = start; j < 20; ++j)
		{
			if (process[j]==v[i])
			{
				if ((j-start)>best)
				{
					best=j-start;
					choose=i;
					break;
				}
				else
					break;
			}
			//即下一个页面号不会再出现
			if (j==amount-1)
			{
				return i;
			}
		}
	}
	return choose;
}

