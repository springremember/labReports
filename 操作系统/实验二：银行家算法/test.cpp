/*************************************************************************
    > File Name: test.cpp
    > Author: spring
    > Mail: 1143515591@qq.com 
    > Created Time: 2017年11月07日 星期二 08时57分06秒
 ************************************************************************/


#include <iostream>  
#include <fstream>  
#include <string>  
  
using namespace std;  
  
void openFile(char *filePath,int *p,int num)
{
  	ifstream file;  
  	file.open(filePath,ios::in);  
  
  	if(!file.is_open())
  		cout<<"文件不存在，读取错误。"<<endl;
    std::string strLine;  
    for (int i = 0; i < num; ++i)
    {
    	getline(file,strLine);
    	p[i]=std::stoi(strLine);
    }
 
}

int main()  
{  
	int *p=new int(3);
	openFile("test.txt",p,3);
	for (int i = 0; i < 3; ++i)
	{
		cout<<p[i]<<endl;
	}
    return 0;
}  