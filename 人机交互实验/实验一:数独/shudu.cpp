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

int Initial_State [ 10 ] [ 10 ] ;      //ԭ������
int Copy_State [10] [10];				//��ʾ����
point Final_State[10][10];

void gametip();

bool get_Initial_State( int i , int j  )  //�����ڣ� i , j ��λ�ô����Դ洢������,�ҵ����򷵻�true�����򷵻�false
{
    if( i > 9 || j > 9 )
        return true;

    for( int k = 1 ; k <= 9 ; ++k )
    {
        bool can = true;                // can �������ڼ�¼����k�ܷ���� ( i , j ) ��
        for( int m = 1 ; m < i ; ++m )
            if( Initial_State[m][j] == k )  // ���ͬһ���Ƿ���ֹ�����k
            {
                can = false ;
                break ;
            }
        if ( can )
            for( int n = 1 ; n < j ; ++n )
                if( Initial_State[i][n] == k )  // ���ͬһ���Ƿ���ֹ�����k
                {
                    can = false ;
                    break;
                }
        if( can )
        {
            int up1 = ( i/3 ) * 3 + 3 ; // (i,j)�������ڵ�3��3С����i���������
            int up2 = ( j/3 ) *3 + 3;  // (i,j)�������ڵ�3��3С������j���������

            if( i % 3 == 0 )    //���������������Ĵ���
                up1 = i ;
            if( j % 3 == 0 )
                up2 = j ;

            for( int p = up1-2 ; p <= up1 ; ++p  )  /* �����3��3��С�������Ƿ������ͬһ������ */
            {
                if( can == false )  /* �������ѭ�� */
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
                if( get_Initial_State( i  , j +1 ) )  /* ��ͬһ�е���һλ�ÿ�ʼ���� */
                    return true ;
            }
            else
            {
                if( i < 9 )
                {
                    if( get_Initial_State( i + 1 , 1 ) )    /* ����һ�еĵ�һ���ո�ʼ���� */
                        return true ;
                }
                else
                    return true ;  /* i >= 9  && j >= 9  , �������� */

            }
            Initial_State[i][j] = 0 ;  /* �ؼ���һ�����Ҳ������Ҫ�ظ�ԭ״��������������������Ӱ�� */
        }
    }
    return false ;  /*  1��9�����Թ������У��򷵻صݹ����һ�� */
}

void start()       //��������ԭʼ����
{
	int k;
    srand ( unsigned ( time (NULL) ) );  /* ����random_shuffle����������� */
    for( int i = 1  ; i <= 9 ; ++i )
        for( int j = 1 ; j <= 9 ; ++j )
            Initial_State[i][j] = 0 ;
    for(k=0;k<10;k++)
        Initial_State[1][k] = k ;

    random_shuffle( &( Initial_State[1][1]) , &( Initial_State[1][10])  ) ;  /* ��һ��������в��� */

    get_Initial_State( 2 , 1 ) ;  /* �ӵڶ��п�ʼ���� */
}

void copy()          //���ɿ�������
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


int build()      //�ڿӺ�����num����27ʧ�ܣ�ԭ��δ֪��
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

void happy()     //��Ϸͨ������ 
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
	cout<<"                             |              ��ϲ�㣡ͨ����Ϸ��             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |          1.̫���ˣ����������Ѷ�           |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                2.������ѡ��                 |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                 3.�˳���Ϸ                  |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             |                                             |"<<endl;
	cout<<"                             ==============================================="<<endl; 

	int happy;
	char chappy; 
	cout<<"��ѡ��������Ĺ��ܣ�"; 
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
					cout<<"����������������룡"<<endl;
					break;	
			}
		}
	
}

void show()         //����ʾ����
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
				cout<<"              ����˵��             "<<i;
				break;
			case 3:
				cout<<"             1.��������            "<<i;
				break;
			case 4:
				cout<<"             2.��Ϸ��ʾ            "<<i;
				break;
			case 5:
				cout<<"             3.������            "<<i;
				break;
			case 6:
				cout<<"            4.������ѡ��           "<<i;
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
	cout<<"                ���������ѡ��������Ĺ���:"; 
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
				cout<<"            ������ѡ���ܣ�"; 
				break;
		}
	}
}

void entry()         //���뺯�� 
{
	cout<<"                 ����������:"; 
	int hang;
	char chang; 
	while(1)
	{
		chang=getchar();
		getchar();
		hang=int(chang);
		hang=hang-48;
		if(hang<1 || hang>9)
			cout<<"                  ����������";
		else
			break;
	}	
	cout<<"                 ����������:"; 
	int  lie;
	char clie;
	while(1)
	{
		clie=getchar();
		getchar();
		lie=int(clie);
		lie=lie-48;
		if(hang<1 || hang>9)
			cout<<"                  ����������";
		else
			break;	
	}	
	cout<<"                 �������������:"; 
	int  shuzi;
	char cshuzi;
	while(1)
	{
		cshuzi=getchar();
		getchar();
		shuzi=int(cshuzi);
		shuzi=shuzi-48;
		if(shuzi<1 || shuzi>9)
			cout<<"                  ����������";
		else
			break;	
	}		
	if(Final_State[hang][lie].flag==0 ||  Final_State[hang][lie].flag==11)
		{
			cout<<"��������Ŀ�����ĵط���գ�"<<endl;
			entry();
		}
	else
		Final_State[hang][lie].flag=shuzi;
	show();
}

void error()       //������ 
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
				cout<<"              ����˵��             "<<i;
				break;
			case 3:
				cout<<"             1.��������            "<<i;
				break;
			case 4:
				cout<<"             2.��Ϸ��ʾ            "<<i;
				break;
			case 5:
				cout<<"             3.������            "<<i;
				break;
			case 6:
				cout<<"            4.������ѡ��           "<<i;
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
	cout<<"                ���������ѡ��������Ĺ��ܣ�";
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
				cout<<"            ������ѡ���ܣ�"; 
				break;
		}
	}
}

void gametip()      //��Ϸ��ʾ���� 
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

void simple()        //���Ѷ� 
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

void middle()        //�е��Ѷ� 
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

void hard()     //���Ѷ� 
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

void tips()      //��Ϸ˵��
{
	system("cls");
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"         ******************************************************************  "<<endl;
	cout<<"         <<<<                          ������Ϸ����                    >>>>  "<<endl;
    cout<<"         <<<<                                                          >>>>  "<<endl;
	cout<<"         <<<<  ������Ϸ��9x9�ķ����ڽ��У���Ϊ3x3��С���񣬱���Ϊ������>>>>  "<<endl;
    cout<<"         <<<<  ������Ϸ��Ŀ���Ǹ������й���                          >>>>  "<<endl;
	cout<<"         <<<<  ��1��9֮������������ո�һ������ֻ������һ�����֣�    >>>>  "<<endl;
    cout<<"         <<<<             1. ÿ��������ÿһ��ֻ�ܳ���һ�Ρ�            >>>>  "<<endl;
    cout<<"         <<<<             2. ÿ��������ÿһ��ֻ�ܳ���һ�Ρ�            >>>>  "<<endl;
	cout<<"         <<<<             3. ÿ��������ÿһ��ֻ�ܳ���һ�Ρ�            >>>>  "<<endl;
    cout<<"         <<<<                                                          >>>>  "<<endl;
	cout<<"         <<<<                                                          >>>>  "<<endl;
    cout<<"         ==================================================================  "<<endl;
	cout<<"                �밴��������ص������档";
	char xyz;
	cin>>xyz;
	getchar();
	maintop();
}


void gamechoose()      //�Ѷ�ѡ����� 
{
	system("cls");
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"                ***********************************************************                "<<endl;
	cout<<"                <<<<                    ��ѡ���Ѷ�                     >>>>                "<<endl;
    cout<<"                <<<<                                                   >>>>                "<<endl;
	cout<<"                <<<<                     1.��                        >>>>                "<<endl;
    cout<<"                <<<<                     2.�е�                        >>>>                "<<endl;
    cout<<"                <<<<                     3.����                        >>>>                "<<endl;
	cout<<"                <<<<                   4.����������                    >>>>                "<<endl;
    cout<<"                <<<<                                                   >>>>                "<<endl;
    cout<<"                ===========================================================                "<<endl;
	cout<<"                ���������ѡ��������Ĺ��ܣ�";
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
			cout<<"ѡ�����������ѡ��"<<endl;
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
	cout<<"                <<<<                 ��ӭʹ��������Ϸ                  >>>>                "<<endl;
    cout<<"                <<<<                                                   >>>>                "<<endl;
	cout<<"                <<<<                    1.��ʼ��Ϸ                     >>>>                "<<endl;
    cout<<"                <<<<                    2.��Ϸ˵��                     >>>>                "<<endl;
    cout<<"                <<<<                    3.�˳���Ϸ                     >>>>                "<<endl;
    cout<<"                <<<<                                                   >>>>                "<<endl;
    cout<<"                ===========================================================                "<<endl;
	char cchoose;
	int choose;
	cout<<"                 ����������ѡ��:";
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
			cout<<"                ѡ���������������:";
		}

	}
}    



 int main()
{
    start( ) ;
	copy();
	cout<<"���Դ��룡����"<<endl;
	maintop();
    return 0 ;
}




