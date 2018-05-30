/*************************************************************************
    > File Name: show.h
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年12月02日 星期六 21时30分59秒
 ************************************************************************/
#include <vector>

using namespace std;

int show(vector<int> v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		cout<<v[i]<<'\t';
	}
	return 0;
}