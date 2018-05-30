#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void show(string xyz)
{
	int flag=0;
	if(xyz.size()!=0)
	{
		if(xyz[0]>='a' && xyz[0]<='z' || xyz[0]>='A' && xyz[0]<='Z')
		{
			if(xyz=="begin" || xyz=="if" || xyz=="then" || xyz=="end" )
				cout<<"3	"<<xyz<<endl;
			else
				cout<<"1	"<<xyz<<endl; 
		}
		else
		{
			for(int i=0;i<xyz.size();i++)
			{
				if(xyz[0]>='a' && xyz[0]<='z' || xyz[0]>='A' && xyz[0]<='Z')
				{
					flag=1;
					break;
				}
			}	
			if(flag==1)
				cout<<"´Ê·¨´íÎó£¡"<<endl;
			else
				cout<<"2	"<<xyz<<endl;
		}
	}
}

void deal(string in)
{
	std::string word;
	word="";
	for(int i=0;i<in.size();i++)
	{
		if(in[i]>='a' && in[i]<='z' || in[i]>='A' && in[i]<='Z' || in[i]>='0' && in[i]<='9')
			word=word+in[i];
		else if(in[i]=='+' || in[i]=='-' || in[i]=='*' || in[i]=='/' || in[i]=='>' || in[i]=='<')
				{
					show(word);
					word="";
					cout<<"4	"<<in[i]<<endl;
				}
			else if(in[i]==':')
				{
					if(in[i+1]=='=')
					{
						show(word);
						word="";
						cout<<"4	:="<<endl;
						i=i+1;
					}
					else
						cout<<"´Ê·¨´íÎó£¡"<<endl;
				}
				else if(in[i]==';' || in[i]=='#')
				{
					show(word);
					word="";
					cout<<"5	"<<in[i]<<endl;
				}
					else if(in[i]==' ' || in[i]=='\n' || in[i]=='\t')
					{
						show(word);
						word="";
					}
						else
						{
							show(word);
							word="";
							cout<<"´Ê·¨´íÎó£¡"<<endl; 
						}
	}
}



int main()
{
	char *filePath="test.txt";
	ifstream file;
	file.open(filePath,ios::in);
	if(!file.is_open())
		return 0;
	std::string strLine;
	while(getline(file,strLine))
	{
		if(strLine.empty())
			continue;
		deal(strLine);
	}
}
