using namespace std;

//读取文件的数据,并赋值给一维数组
void openFile(const char *filePath,int *p,int num)
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