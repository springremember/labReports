#include <iostream>
#include <limits.h>
#include <vector>
#include<cstdlib>
#include<ctime>

#include "show.h"
#include "select.h"
#include "best.h"

#include <queue>
#include "first.h"

#include "getVisitTop.h"
#include "LRU.h"

using namespace std;




int main()
{
	int many=30;

	int limit=4;   //可分配块数
	int amount=100; //访问次数
	float sum1=0;
	float sum2=0;
	float sum3=0;

	cout<<"最佳置换算法"<<'\t'<<'\t';
	cout<<"先入先出页面置换算法"<<'\t';
	cout<<"LRU置换算法"<<endl;
	vector<int> process;
	for (int i = 0; i < many; ++i)
	{
		for(int j=0;j<amount;j++)
		{
			process.push_back(rand()%10);
		}
		sum1=sum1+best(process,limit,amount);
		sum2=sum2+first(process,limit,amount);
		sum3=sum3+LRU(process,limit,amount);
		process.clear();
	}
	cout<<"平均缺页率："<<(sum1/many)*100<<"%"<<'\t';
	cout<<"平均缺页率："<<(sum2/many)*100<<"%"<<'\t';
	cout<<"平均缺页率："<<(sum3/many)*100<<"%"<<endl;
	// cout<<"最佳置换算法"<<endl;
	// best(process,limit,amount);
	// cout<<"先入先出页面置换算法"<<endl;
	// first(process,limit,amount);
	// cout<<endl;
	// cout<<"LRU置换算法"<<endl;
	// LRU(process,limit,amount);
	// cout<<endl;
	return 0; 
}