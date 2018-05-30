#include<iostream>
#include<windows.h>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include <ctime>
using namespace std;

class point
{
	public:
		int value;
		int flag;
		
		point()
		{
			value=0;
			flag=0;
		}
};

void gamechoose();
void error();
int maintop();
void entry();

int Initial_State [ 10 ] [ 10 ] ;      //原本矩阵
int Copy_State [10] [10];				//显示矩阵
point Final_State[10][10];

void gametip();

bool get_Initial_State( int i , int j  )  //搜索第（ i , j ）位置处可以存储的数字,找到解则返回true，否则返回false
{
    if( i > 9 || j > 9 )
        return true;

    for( int k = 1 ; k <= 9 ; ++k )
    {
        bool can = true;                // can 变量用于记录数字k能否放在 ( i , j ) 处
        for( int m = 1 ; m < i ; ++m )
            if( Initial_State[m][j] == k )  // 检查同一列是否出现过数字k
            {
                can = false ;
                break ;
            }
        if ( can )
            for( int n = 1 ; n < j ; ++n )
                if( Initial_State[i][n] == k )  // 检查同一行是否出现过数字k
                {
                    can = false ;
                    break;
                }
        if( can )
        {
            int up1 = ( i/3 ) * 3 + 3 ; // (i,j)方格所在的3×3小方格i坐标的上限
            int up2 = ( j/3 ) *3 + 3;  // (i,j)方格所在的3×3小方格在j坐标的上限

            if( i % 3 == 0 )    //这是针对特殊情况的处理
                up1 = i ;
            if( j % 3 == 0 )
                up2 = j ;

            for( int p = up1-2 ; p <= up1 ; ++p  )  /* 检查在3×3的小方格中是否出现了同一个数字 */
            {
                if( can == false )  /* 跳出外层循环 */
                    break ;
                for( int q = up2-2 ; q <= up2 ; ++q )
                    if( Initial_State[p][q] == k )
                    {
                        can = false ;
                        break ;
                    }
            }
        }
        if( can )
        {
            Initial_State[i][j] = k ;
            if( j<9 )
            {
                if( get_Initial_State( i  , j +1 ) )  /* 到同一行的下一位置开始搜索 */
                    return true ;
            }
            else
            {
                if( i < 9 )
                {
                    if( get_Initial_State( i + 1 , 1 ) )    /* 到下一行的第一个空格开始搜索 */
                        return true ;
                }
                else
                    return true ;  /* i >= 9  && j >= 9  , 搜索结束 */

            }
            Initial_State[i][j] = 0 ;  /* 关键这一步：找不到解就要回复原状，否则会对下面的搜索造成影响 */
        }
    }
    return false ;  /*  1到9都尝试过都不行，则返回递归的上一步 */
}

void start()       //用于生成原始矩阵
{
	int k;
    srand ( unsigned ( time (NULL) ) );  /* 产生random_shuffle的随机数种子 */
    for( int i = 1  ; i <= 9 ; ++i )
        for( int j = 1 ; j <= 9 ; ++j )
            Initial_State[i][j] = 0 ;
    for(k=0;k<10;k++)
        Initial_State[1][k] = k ;

    random_shuffle( &( Initial_State[1][1]) , &( Initial_State[1][10])  ) ;  /* 第一行随机排列产生 */

    get_Initial_State( 2 , 1 ) ;  /* 从第二行开始搜索 */
}

void copy()          //生成拷贝矩阵
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			Copy_State[i][j]=Initial_State[i][j];
			Final_State[i][j].value=Initial_State[i][j]; 
		}	
	}
}


int build()      //挖坑函数，num超过27失败，原因未知。
{
	int i;
	int j;
	i=(int)(rand()%9)+1;
	j=(int)(rand()%9)+1;
	if(Copy_State[i][j]==10)
	{
		build();
	}
	else
	{
		vector <int> a;
		for(int m=0;m<10;m++)
		{
			if(Copy_State[i][m]==10)
				a.push_back(m);
		}
		vector <int> b;
		for(int n=0;n<10;n++)
		{
			if(Copy_State[n][j]==10)
				b.push_back(n);
		}
		if(a.size()==0 || b.size()==0)
		{
			Copy_State[i][j]=10;
		}
		else
		{
			for(int x=0;x<a.size();x++)
			{
				for(int y=0;y<b.size();y++)
				{
					if(Copy_State[b[y]][a[x]]==10)
					{
						build();
						return 0;
					}
					else
						continue;
				}
			}
			Copy_State[i][j]=10;
		}
	}
	return 0;
}

void recopy()
{
		for( int i = 1 ; i <= 9 ; ++ i )
	{
		for( int j = 1 ; j <= 9 ; ++j )
		{
		
			if(Copy_State [i][j]==10)
				Final_State[i][j].flag=10;
			else
				Final_State[i][j].flag=0;
		}

	}
	
}

void happy()     //游戏通过界面 
{ 
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"                             ***********************************************"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |              恭喜你！通过游戏。             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |          1.太简单了？试试其他难度           |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                2.返回主选单                 |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                 3.退出游戏                  |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             ==============================================="<<endl; 

	int happy;
	char chappy; 
	cout<<"请选择您所需的功能："; 
	while(1)
		{
			chappy=getchar();
			getchar();
			happy=int(chappy)-48;
			switch(happy)
			{
				case 1:
					gamechoose();
					break;
				case 2:
					maintop();
					break;
				case 3:
					exit(0);
					break; 
				default:
					cout<<"输入错误，请重新输入！"<<endl;
					break;	
			}
		}
	
}

void show()         //主显示函数
{
	system("cls");
	int count=0;
	for(int m=1;m<10;m++)
	{
		for(int n=1;n<10;n++)
		{
			if(Final_State[m][n].flag!=10)
				count++;
		}
	}
	if(count==81)
		happy();
		
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout<<"                                      1   2   3   4   5   6   7   8   9  "<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	cout<<"                                    -------------------------------------"<<endl;
	for( int i = 1 ; i <= 9 ; ++ i )
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		switch(i)
		{
			case 2:
				cout<<"              按键说明             "<<i;
				break;
			case 3:
				cout<<"             1.填入数字            "<<i;
				break;
			case 4:
				cout<<"             2.游戏提示            "<<i;
				break;
			case 5:
				cout<<"             3.检查错误            "<<i;
				break;
			case 6:
				cout<<"            4.返回主选单           "<<i;
				break;
			default:
				cout<<"                                   "<<i;	 
		}
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		cout<<"|";
		for( int j = 1 ; j <= 9 ; ++j )
			if(Final_State [i][j].flag==10)
			{
					cout<<" "<<" "<<" "<<"|";
			}
			else
			{
				if(Final_State [i][j].flag==0) 
					cout<<" "<<Final_State [i][j].value<<" "<<"|" ;
				else
				{
					if(Final_State[i][j].flag==11)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						cout<<" "<<Final_State[i][j].value<<" ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
						cout<<"|";
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						cout<<" "<<Final_State[i][j].flag<<" ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
						cout<<"|";
					}
				}

			}
		cout<<endl;
	cout<<"                                    -------------------------------------"<<endl;
	}
	cout<<"                请根据数字选择您所需的功能:"; 
	int xyz;
	char cxyz;
	while(1)
	{
		cxyz=getchar();
		getchar();
		xyz=int(cxyz)-48;
		switch(xyz)
		{
			case 1:
				entry(); 
				break;
			case 2:
				gametip();
				break;
			case 3:
				error();
				break;
			case 4:
				maintop();
				break;
			case 5:
				maintop();
			default:
				cout<<"            请重新选择功能："; 
				break;
		}
	}
}

void entry()         //输入函数 
{
	cout<<"                 请先输入行:"; 
	int hang;
	char chang; 
	while(1)
	{
		chang=getchar();
		getchar();
		hang=int(chang);
		hang=hang-48;
		if(hang<1 || hang>9)
			cout<<"                  请重新输入";
		else
			break;
	}	
	cout<<"                 请再输入列:"; 
	int  lie;
	char clie;
	while(1)
	{
		clie=getchar();
		getchar();
		lie=int(clie);
		lie=lie-48;
		if(hang<1 || hang>9)
			cout<<"                  请重新输入";
		else
			break;	
	}	
	cout<<"                 请最后输入数字:"; 
	int  shuzi;
	char cshuzi;
	while(1)
	{
		cshuzi=getchar();
		getchar();
		shuzi=int(cshuzi);
		shuzi=shuzi-48;
		if(shuzi<1 || shuzi>9)
			cout<<"                  请重新输入";
		else
			break;	
	}		
	if(Final_State[hang][lie].flag==0 ||  Final_State[hang][lie].flag==11)
		{
			cout<<"不能在题目给出的地方填空！"<<endl;
			entry();
		}
	else
		Final_State[hang][lie].flag=shuzi;
	show();
}

void error()       //纠错函数 
{
	system("cls");
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout<<"                                      1   2   3   4   5   6   7   8   9  "<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	cout<<"                                    -------------------------------------"<<endl;
	for( int i = 1 ; i <= 9 ; ++ i )
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		switch(i)
		{
			case 2:
				cout<<"              按键说明             "<<i;
				break;
			case 3:
				cout<<"             1.填入数字            "<<i;
				break;
			case 4:
				cout<<"             2.游戏提示            "<<i;
				break;
			case 5:
				cout<<"             3.检查错误            "<<i;
				break;
			case 6:
				cout<<"            4.返回主选单           "<<i;
				break;
			default:
				cout<<"                                   "<<i;	 
		}
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		cout<<"|";
		for( int j = 1 ; j <= 9 ; ++j )
			if(Final_State [i][j].flag==10)
			{
					cout<<" "<<" "<<" "<<"|";
			}
			else
			{
				if(Final_State [i][j].flag==0) 
					cout<<" "<<Final_State [i][j].value<<" "<<"|" ;
				else
				{
					if(Final_State[i][j].flag==Final_State[i][j].value)
					{ 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					cout<<" "<<Final_State[i][j].value<<" ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
					cout<<"|";
					} 
					else
					{
					
						if(Final_State[i][j].flag==11)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout<<" "<<Final_State[i][j].value<<" ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
							cout<<"|";
						}
						else
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout<<" "<<Final_State[i][j].flag<<" ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
							cout<<"|";
							
						} 
					}
				}
			}
		cout<<endl;
	cout<<"                                    -------------------------------------"<<endl;
	}
	cout<<"                请根据数字选择您所需的功能：";
	int xyz;
	char cxyz;
	while(1)
	{
		cxyz=getchar();
		getchar();
		xyz=int(cxyz)-48;
		switch(xyz)
		{
			case 1:
				entry(); 
				break;
			case 2:
				gametip();
				break;
			case 3:
				error();
				break;
			case 4:
				maintop();
				break;
			default:
				cout<<"            请重新选择功能："; 
				break;
		}
	}
}

void gametip()      //游戏提示功能 
{
	for(int i=1;i<10;i++)
	{
		for(int j=1;j<10;j++)
		{
			if(Final_State[i][j].flag==10)
				{
					Final_State[i][j].flag=11;
					show();
				}
		}
	}
}

void simple()        //简单难度 
{
	system("cls");
	start();
	copy();
	int count=15;
	for(int i=1;i<=15;i++)
		build();
	recopy();
	show();
}

void middle()        //中等难度 
{
	system("cls");
	start();
	copy();
	int count=15;
	for(int i=1;i<=20;i++)
		build();
	recopy();
	show();
}

void hard()     //高难度 
{
	system("cls");
	start();
	copy();
	int count=15;
	for(int i=1;i<=25;i++)
		build();
	recopy();
	show();	
}

void tips()      //游戏说明
{
	system("cls");
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"         ******************************************************************  "<<endl;
	cout<<"         <<<<                          数独游戏规则                    >>>>  "<<endl;
    cout<<"         <<<<                                                          >>>>  "<<endl;
	cout<<"         <<<<  数独游戏在9x9的方格内进行，分为3x3的小方格，被称为“区”>>>>  "<<endl;
    cout<<"         <<<<  数独游戏的目的是根据下列规则：                          >>>>  "<<endl;
	cout<<"         <<<<  用1至9之间的数字填满空格，一个格子只能填入一个数字：    >>>>  "<<endl;
    cout<<"         <<<<             1. 每个数字在每一行只能出现一次。            >>>>  "<<endl;
    cout<<"         <<<<             2. 每个数字在每一列只能出现一次。            >>>>  "<<endl;
	cout<<"         <<<<             3. 每个数字在每一区只能出现一次。            >>>>  "<<endl;
    cout<<"         <<<<                                                          >>>>  "<<endl;
	cout<<"         <<<<                                                          >>>>  "<<endl;
    cout<<"         ==================================================================  "<<endl;
	cout<<"                请按下任意键回到主界面。";
	char xyz;
	cin>>xyz;
	getchar();
	maintop();
}


void gamechoose()      //难度选择界面 
{
	system("cls");
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"                ***********************************************************                "<<endl;
	cout<<"                <<<<                    请选择难度                     >>>>                "<<endl;
    cout<<"                <<<<                                                   >>>>                "<<endl;
	cout<<"                <<<<                     1.简单                        >>>>                "<<endl;
    cout<<"                <<<<                     2.中等                        >>>>                "<<endl;
    cout<<"                <<<<                     3.困难                        >>>>                "<<endl;
	cout<<"                <<<<                   4.返回主界面                    >>>>                "<<endl;
    cout<<"                <<<<                                                   >>>>                "<<endl;
    cout<<"                ===========================================================                "<<endl;
	cout<<"                请根据数字选择您所需的功能：";
	int chance;
	char cchance;
	while(1)
	{
		cchance=getchar();
		getchar();
		chance=int(cchance);
		chance=chance-48;
		switch(chance)
		{
		case 1:
			simple();
			break;
		case 2:
			middle();
			break;
		case 3:
			hard();
			break;
		case 4:
			maintop();
			break;
		default:
			cout<<"选择错误，请重新选择："<<endl;
		}
	}
}

int maintop()
{
	system("cls");
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"                ***********************************************************                "<<endl;
	cout<<"                <<<<                 欢迎使用数独游戏                  >>>>                "<<endl;
    cout<<"                <<<<                                                   >>>>                "<<endl;
	cout<<"                <<<<                    1.开始游戏                     >>>>                "<<endl;
    cout<<"                <<<<                    2.游戏说明                     >>>>                "<<endl;
    cout<<"                <<<<                    3.退出游戏                     >>>>                "<<endl;
    cout<<"                <<<<                                                   >>>>                "<<endl;
    cout<<"                ===========================================================                "<<endl;
	char cchoose;
	int choose;
	cout<<"                 请输入您的选择:";
	while(1)
	{
		cchoose=getchar();
		getchar();
		choose=int(cchoose);
		choose=choose-48;
		switch(choose)
		{
		case 1:
			gamechoose();
			break;
		case 2:
			tips();
			break;
		case 3:
			exit(0);
			break;
		default:
			cout<<"                选择错误，请重新输入:";
		}

	}
}    



 int main()
{
    start( ) ;
	copy();
	cout<<"测试代码！！！"<<endl;
	maintop();
    return 0 ;
}




