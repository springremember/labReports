using namespace std;

//读取文件数据，并赋值给二维数组
void openFilePlus(const char *filePath,int **p,int n,int m)
{
	ifstream file;  
	file.open(filePath,ios::in);  
	
	if(!file.is_open())
		cout<<"文件不存在，读取错误。"<<endl;
	std::string strLine;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			getline(file,strLine);
			p[i][j]=std::stoi(strLine);
		}
	}	
}