#ifndef _QLSV_H_
#define _QLSV_H_
#include "search.h"
#endif

void statistic();
void MenuStatistic()
{
	MENU_SEARCH[1] ="Thong Ke";
	actionMenuSearch[1]=  &statistic;
	MenuSearch();	
}
void _thongKeSinhVienTheoLop(int count)
{
	for (int i=0;i<count;i++)
	{
		for(int j = 0; j< SIZE_LOP; j++) 
			if (thongKeLop[j].maLop == res[i].maLop) 
			 	thongKeLop[j].soSV++;
		thongKeLop[SIZE_LOP].soSV++;//sum
	}
}
int cmp(string s1,string s2)
{
	for (int i=0;i<s1.length();i++)
		if (s1[i]!=s2[i]) return 0;
	return 1;
}
void xoaSV()
{
	showCur();
	XoaManHinh();
	int kt=0,position=-1;
	char opt;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string ID;
	fflush(stdin);
	cout<<"Nhap ma lop:";
	cin>>ID;
	int pos=-1;
	ID = upperCase(ID);	
	for (cauTruc *i=dataSinhVien;i!=NULL;i=i->next)
		{
			pos++;
			
			if (cmp(i->data.maLop,ID))
			{
					pos++;
					dataSinhVien = DelAt(dataSinhVien,pos);
//					writeFileAll(dataSinhVien);
			}		
		}
		hideCur();
	cout<<"Deleted!";
	writeFileAll(dataSinhVien);
}

void drawCol(int x,int y,int height)
{
	for (int i=0;i<=height;i++)
	{
			GoTo(x+i,y);printf("%c", 219);
	}

	
}
void _thongKeTheoLop(int count)
{
	system("cls");
	GoTo(0,3);
	for(int i= 0; i<= 90; i++) cout << " ";
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	
	GoTo(47, 3); cout <<"THONG KE SINH VIEN THEO LOP";
	for(int i= 0; i< SIZE_LOP; i++ ) {
		thongKeLop[i].maLop = DANH_SACH_LOP[i];
		thongKeLop[i].tenLop = DANH_SACH_TEN_LOP[i];
		thongKeLop[i].soSV  = 0;
	}
	thongKeLop[SIZE_LOP].maLop = "";
	thongKeLop[SIZE_LOP].soSV = 0;
	thongKeLop[SIZE_LOP].tenLop = "Tong:     ";
	_thongKeSinhVienTheoLop(count);
//	rawBangThongKeTheoLop(25, 5, SHOW_TOP_THONG_KE_LOP);
	int dem = 1;
	for (int i= 0; i< SIZE_LOP; i++){
		GoTo(5,25+i*2);cout<<thongKeLop[i].maLop;
		drawCol(20,25+i*2,thongKeLop[i].soSV);
		cout<<thongKeLop[i].soSV;
			
	}
//	SetConsoleTextAttribute(hConsole, 10);
//	GoTo(25+SIZE_THONG_KE_THEO_LOP[1], 5 + (dem-1)*2+1 ); 		printf("%c", ' ');
//	GoTo(25+SIZE_THONG_KE_THEO_LOP[1], 5 + (dem-1)*2 ); 		printf("%c", 193);
//	GoTo(25+SIZE_THONG_KE_THEO_LOP[1], 5 + (dem-1)*2+2 ); 		printf("%c", 196);
	int ch = getch();
		system("cls");
}
void statistic()
{
	int count =0;
	char infix[80],postfix[80];
	int i=0;
	_Stack S;
	_init(&S);
	int x,y;
	int j=0;
	for (i=0;i<opt.length();i++)
		infix[j++] = opt[i];
	infix[j]='\0';
	InfixtoPostfix(infix,postfix);
	for (cauTruc *i=dataSinhVien;i!=NULL;i=i->next)
	{
		_init(&S);
		int k=0,n=strlen(postfix);
		
		while (k<n)
		{
				if ((postfix[k]<='f')&&(postfix[k]>='a'))
				{
//					cout<<i->data.maLop<<"= "<<svsv.maLop<<endl;
//					cout<<postfix[k];
//					cout<< checkByKey(i->data,svsv,postfix[k]);
					_Push(&S, checkByKey(i->data,svsv,postfix[k]));
				}
				else if ((postfix[k]=='&')||(postfix[k]=='|')||(postfix[k]=='~')||(postfix[k]=='^'))
				{
					if (postfix[k]=='&')
					{
						
						x = _Pop(&S);
						y = _Pop(&S);	
						_Push(&S,x*y);	
						
					}
					else if (postfix[k]=='|')
					{
						x = _Pop(&S);
						y = _Pop(&S);
						_Push(&S,x>y?x:y);
					}
					else if (postfix[k]=='~')
					{
						
						x = _Pop(&S);
						_Push(&S,1-x);
					}
					else
					{
						x = _Pop(&S);
						y = _Pop(&S);
						_Push(&S,abs(x-y));
					}
				}
			k++;
//			for (int index=0;index<=S.TOP;index++)
//				cout<<S._DATA[index];
//			cout<<endl;
		}
		if (S._DATA[S.TOP]==1)
		{
			res[count] =i->data;count=count+1;	
		}
	}
	if (count>0)
	{
		
		_thongKeTheoLop(count);
			
	}	
	else
		cout<<"Khong co sinh vien thoa man!";
}
