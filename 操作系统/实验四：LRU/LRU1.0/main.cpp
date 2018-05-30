#include <iostream>
#include <limits.h>
#include <vector>
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

	int limit=3;   //可分配块数
	int amount=20; //访问次数

	vector<int> process={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};


	cout<<"最佳置换算法"<<endl;
	best(process,limit,amount);
	cout<<endl;
	cout<<"先入先出页面置换算法"<<endl;
	first(process,limit,amount);
	cout<<endl;
	cout<<"LRU置换算法"<<endl;
	LRU(process,limit,amount);
	cout<<endl;
	return 0; 
}