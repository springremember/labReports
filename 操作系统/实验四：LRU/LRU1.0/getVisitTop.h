/*************************************************************************
    > File Name: getVisitTop.h
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年12月02日 星期六 21时56分42秒
 ************************************************************************/

#include <vector>
using namespace std;

int getVisitTop(vector<int>& v,int visit)
{
	int temp=v[visit];
	for (int i = visit; i < v.size()-1; ++i)
	{
		v[i]=v[i+1];
	}
	v[v.size()-1]=temp;;
	return 0;
}