#ifndef _QLSV_H_
#define _QLSV_H_
#include "getTT.h"
#include "lib.h"
#endif 
string MENU_SEARCH[3] = {"Tuy chon", 
							"Tim kiem", 
							"Thoat"};
string MENU_OPTION_SEARCH[8] = {"a) Ma lop  ", 
								"b) Ma  SV  ", 
								"c) Ho  ten ", 
								"d)Ngay sinh", 
								"e)  DiemTB ",
								"f)     GT  ",
								"And,or,xor,not",
								"Save"};
string MENU_INPUT_SEARCH[7]= {"","","","","","",""};
void inClass();
void inSv();
void inName();
void inDate();
void inPoint();
void inSex();
void inOption();
void (*actionMenuSearchInput[])() = {&inClass, &inSv, &inName, &inDate, &inPoint, &inSex, &inOption};
void optionSearch();
void runSearch();
string opt="";
void (*actionMenuSearch[])() = {&optionSearch,&runSearch};
typedef struct _sinhvien{
	string  maLop, hoTen, ngaySinh1,ngaysinh2,maSV;
	float diem1,diem2;
	int gioiTinh;	
};
_sinhvien svsv;


sinhvien res[10000];

void khoitao()
{
	svsv.diem1 =0.0;
	svsv.diem2=10.0;
	svsv.hoTen = "";
	svsv.gioiTinh =0;
	svsv.maLop = "";
	svsv.maSV ="";
	svsv.ngaySinh1 ="1/1/1900";
	svsv.ngaysinh2 ="31/12/2000";
}
void MenuSearch()
{
	XoaManHinh();
	int action, arrow = 0;
	int size = 3;
	drawMenu(INPUT_X +3, INPUT_Y, MENU_SEARCH, size, 0);
	while ((action = getCode()) != KEY_ESC )  // chon 
    { 
      switch (action) 
      	{ 
   		    case ARROW_UP: 
				arrow--;
      	   		break; 
    	    case ARROW_DOWN: 
				arrow++;
       			break; 
 			case '\r': 
	  			arrow = (arrow + size*10)%size;
	  			if (arrow == size-1) 
				  {
				  	XoaManHinh();
				  	return;
				  }
	  			(*actionMenuSearch[arrow])();
  		}
		arrow = (arrow + size*10)%size;
		drawMenu(INPUT_X+3, INPUT_Y, MENU_SEARCH, size, arrow);
	}
}

void optionSearch()
{
	XoaManHinh();
	khoitao();
	int action, arrow =0;
	int size = 8;
	int size_input =7;
	drawMenu(INPUT_X , INPUT_Y , MENU_OPTION_SEARCH, size, arrow);
	drawMenu(INPUT_X + WIDTH +3, INPUT_Y , MENU_INPUT_SEARCH, size_input, arrow);
	GoTo(INPUT_X + WIDTH*2 +4, INPUT_Y+HEIGHT*3+1);cout<<">>";
	draw(INPUT_X + WIDTH*2 +6, INPUT_Y+HEIGHT*3,WIDTH,HEIGHT,"",-1);
	GoTo(INPUT_X + WIDTH*2 +4, INPUT_Y+HEIGHT*4+1);cout<<">>";
	draw(INPUT_X + WIDTH*2 +6, INPUT_Y+HEIGHT*4,WIDTH,HEIGHT,"",-1);
	GoTo(INPUT_X + WIDTH +5, INPUT_Y+HEIGHT*7+1);cout<<"And &,Or |,Not ~";
	
	while ((action = getCode()) != KEY_ESC )  // chon 
    { 
      switch (action) 
      	{ 
   		    case ARROW_UP: 
				arrow--;
      	   		break; 
    	    case ARROW_DOWN: 
				arrow++;
       			break; 
 			case '\r': 
	  			arrow = (arrow + size*10)%size;
	  			if (arrow == size-1)
				{
					XoaManHinh();
					return;
				}
				(*actionMenuSearchInput[arrow])();
	  			
  		}
		arrow = (arrow + size*10)%size;
		drawMenu(INPUT_X , INPUT_Y , MENU_OPTION_SEARCH, size, arrow);
		drawMenu(INPUT_X + WIDTH +3, INPUT_Y , MENU_INPUT_SEARCH, size_input,arrow);
		GoTo(INPUT_X + WIDTH +5, INPUT_Y+HEIGHT*7+1);cout<<"And &,Or |,Xor ^,Not ~";
		GoTo(INPUT_X + WIDTH*2 +4, INPUT_Y+HEIGHT*3+1);cout<<">>";
		draw(INPUT_X + WIDTH*2 +6, INPUT_Y+HEIGHT*3,WIDTH,HEIGHT,"",-1);
		GoTo(INPUT_X + WIDTH*2 +4, INPUT_Y+HEIGHT*4+1);cout<<">>";
		draw(INPUT_X + WIDTH*2 +6, INPUT_Y+HEIGHT*4,WIDTH,HEIGHT,"",-1);
		
	}	
}
void inClass()
{
	string sv_class;
	while(1)
	{
	
		sv_class = inputRaw(INPUT_X +WIDTH +3, INPUT_Y +0*HEIGHT +1);
		string error = "Lop khong ton tai!";
	
		sv_class = upperCase(sv_class);
		

		for (int i= 0; i< SIZE_LOP; i++) 
			if (sv_class == DANH_SACH_LOP[i]) error = "";
		if (error == "") break;
		
		GoTo(INPUT_X + WIDTH +4, INPUT_Y +0*HEIGHT +1);
	
		// setMau; 
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 71);
	
		
		cout << error;
		int ch = getch();
		GoTo(INPUT_X + WIDTH +4, INPUT_Y +0*HEIGHT +1);
		SetConsoleTextAttribute(hConsole, 15);
		cout << "                ";
	}

	draw(INPUT_X + WIDTH + 3, INPUT_Y, WIDTH_INPUT, HEIGHT, sv_class, -1);

	svsv.maLop = sv_class;
}
void inSv()
{
	string svSv ;
	while(1)
	{		
		svSv = inputRaw(INPUT_X +WIDTH +3, INPUT_Y +1*HEIGHT +1);
		string error;
		if (svSv.length() == 8)
		{
			if (checkChungMaSinhVien(svSv) != 0)  break;
			else error = "MSV ko ton tai";
		}
		else error =  "Ma sinh vien sai";
		
		GoTo(INPUT_X + WIDTH +4, INPUT_Y +1*HEIGHT +1);
	
		// setMau; 
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 71);
	
		
		cout << error;
		int ch = getch();
		GoTo(INPUT_X + WIDTH +4, INPUT_Y +1*HEIGHT +1);
		SetConsoleTextAttribute(hConsole, 15);
		cout <<"                ";
	}
	svsv.maSV = svSv;
	draw(INPUT_X +WIDTH +3, INPUT_Y + 1*HEIGHT, WIDTH ,HEIGHT, svSv, -1);
}
void inName()
{
	string svName = inputRaw(INPUT_X +WIDTH +3, INPUT_Y + 2*HEIGHT +1);
	svName = lowerCase(svName);
	draw(INPUT_X +WIDTH +3, INPUT_Y + 2*HEIGHT, WIDTH_INPUT ,HEIGHT, svName, -1);
	svsv.hoTen = svName;
}
void inDate()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	int yy = INPUT_Y + 3*HEIGHT+1;
	int xx = INPUT_X + WIDTH +3 + WIDTH_INPUT/2 - 10/2; 
	int Da, Mo, Ya;
	string SDate;
	while(1)
	{
		GoTo(xx,yy);
		printf("  /  /         ");
		
		
		
		string SDa, SMo, SYa;
		
		GoTo(xx, yy); 
		int okNgay = scanf("%d", &Da);
		SDa= coverIntToString(Da, 2);
		
		GoTo(xx, yy); cout << SDa << "/  /    ";
	//	cin.ignore();
		GoTo(xx+3, yy); 
		int okThang = scanf("%d", &Mo);
		SMo = coverIntToString(Mo, 2);
		
		GoTo(xx+3, yy); cout << SMo << "/    ";
	//	cin.ignore();
		GoTo(xx+6, yy); 
		int okNam = scanf("%d", &Ya);
		SYa = coverIntToString(Ya, 4);
		GoTo(xx+6, yy); cout << SYa;
		
		SDate = SDa + "/" + SMo + "/" + SYa;
		GoTo(xx, yy); 
		SetConsoleTextAttribute(hConsole, 8); 
		
		SDate = setDate(Da, Mo, Ya);
		if (SDate != "" && okNgay && okThang && okNam) break;
		
		fflush(stdin);
		SetConsoleTextAttribute(hConsole, 71);
		cout << "Nhap sai ngay!!";
		int ch= getch();
		
	}
	SetConsoleTextAttribute(hConsole, 10);
	cout << SDate;
	svsv.ngaySinh1 = SDate;
	
	GoTo(INPUT_X + WIDTH*2 +4, INPUT_Y+HEIGHT*3+1);cout<<">>";
	draw(INPUT_X + WIDTH*2 +6, INPUT_Y+HEIGHT*3,WIDTH,HEIGHT,"",1);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	yy = INPUT_Y + 3*HEIGHT+1;
	xx = INPUT_X + WIDTH*2 +6 + WIDTH_INPUT/2 - 10/2; 
	while(1)
	{
	
		GoTo(xx,yy);
		printf("  /  /         ");
		string SDa, SMo, SYa;
		
		GoTo(xx, yy); 
		int okNgay = scanf("%d", &Da);
		SDa= coverIntToString(Da, 2);
		
		GoTo(xx, yy); cout << SDa << "/  /    ";
	//	cin.ignore();
		GoTo(xx+3, yy); 
		int okThang = scanf("%d", &Mo);
		SMo = coverIntToString(Mo, 2);
		
		GoTo(xx+3, yy); cout << SMo << "/    ";
	//	cin.ignore();
		GoTo(xx+6, yy); 
		int okNam = scanf("%d", &Ya);
		SYa = coverIntToString(Ya, 4);
		GoTo(xx+6, yy); cout << SYa;
		
		SDate = SDa + "/" + SMo + "/" + SYa;
		GoTo(xx, yy); 
		SetConsoleTextAttribute(hConsole, 8); 
		
		SDate = setDate(Da, Mo, Ya);
		if (SDate != "" && okNgay && okThang && okNam) break;
		
		fflush(stdin);
		SetConsoleTextAttribute(hConsole, 71);
		cout << "Nhap sai ngay!!";
		int ch= getch();
		
		
	}
	SetConsoleTextAttribute(hConsole, 10);
	cout << SDate;
	svsv.ngaysinh2 = SDate;
	hideCur();
}
int cmpBirthday(_sinhvien s1,sinhvien s2)
{
	string ngay1 = convertDateOfBirth(s1.ngaySinh1);
	string ngay2 = convertDateOfBirth(s1.ngaysinh2);
	string ngay = convertDateOfBirth(s2.ngaySinh);
	if ((ngay1<=ngay)&&(ngay2>=ngay)) return 1;
	return 0;
}
void inPoint()
{
	inputPoint();
	int x = INPUT_X +WIDTH*2 +6;
	int y = INPUT_Y +4*HEIGHT +1;
	float svPoint = -1;
	GoTo(INPUT_X + WIDTH*2 +4, INPUT_Y+HEIGHT*4+1);cout<<">>";
	draw(INPUT_X + WIDTH*2 +6, INPUT_Y+HEIGHT*4,WIDTH,HEIGHT,"",1);
	while(1)
	{
 		delInput(x+1, y);
		GoTo(x+2,y);
	
		showCur();
		
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 15);
	///	cin.ignore();
		float temp;
		fflush(stdin);
		int ok = scanf("%f", &temp);
	
		svPoint = chuanHoaPoint(temp);
		delInput(x+1, y);
		if (svPoint != -1 && ok && (svPoint>= svXuLy.diem)) break;
		
		SetConsoleTextAttribute(hConsole, 71);  // In loi bao sai 
		GoTo(x+2, y);
		cout << "Nhap sai diem";
		int pause = getch();
		cout << "             ";
		SetConsoleTextAttribute(hConsole, 15);
	 }
	hideCur();
	draw(INPUT_X +WIDTH*2 +6, INPUT_Y + 4*HEIGHT, WIDTH_INPUT ,HEIGHT, floatToString(svPoint), -1);
	svsv.diem2 = svPoint;
	svsv.diem1 = svXuLy.diem;
}
void inSex()
{
	string svSex ="";
	while (!(svSex=="NAM" || svSex=="NU"))
	{
			delInput(INPUT_X +WIDTH +10, INPUT_Y + 5*HEIGHT +1);
			svSex= inputRaw(INPUT_X +WIDTH +10, INPUT_Y + 5*HEIGHT +1);
			svSex = upperCase(svSex);
	}
	draw(INPUT_X +WIDTH +3, INPUT_Y + 5*HEIGHT, WIDTH_INPUT ,HEIGHT, svSex, -1);
	svsv.gioiTinh = (svSex=="NAM"?1:0);
}
int checkOption(string opt)
{
	string opt_new="";
	for (int i =0;i<opt.length();i++)
		if (opt[i]!=' ')
			opt_new += opt[i];
//	for (int i=0;i<opt_new.length();i++)
//		if ((opt_new[i]!='&') && (opt_new[i]!='|') && (opt_new[i]!='~'))
//			if (opt_new[i] <'a' || opt_new[i]>'f')
//				return 0;
	int d=0;
	for (int i=0;i<opt_new.length();i++)
	{
		if (opt_new[i]=='(') d++;
		else if (opt_new[i]==')') d--;
	}
	if (d==0) return 1;
	return 0;			
}
void inOption()
{
	fflush(stdin);
	opt = inputRaw(INPUT_X +WIDTH +3, INPUT_Y + 6*HEIGHT +1);
	while (checkOption(opt)==0)
	{
		delInput(INPUT_X +WIDTH +3, INPUT_Y + 6*HEIGHT +1);
		opt = inputRaw(INPUT_X +WIDTH +3, INPUT_Y + 6*HEIGHT +1);
	}
	draw(INPUT_X +WIDTH +3, INPUT_Y + 6*HEIGHT, WIDTH_INPUT ,HEIGHT, opt, -1);
}
int checkByKey(sinhvien sv1,_sinhvien sv2,char c)
{
	switch(c)
	{
		case 'a':
			return (sv1.maLop==sv2.maLop) ;
		case 'b':
			return (sv1.maSV==sv2.maSV) ;
		case 'c':
			return checkName(sv2.hoTen,sv1.hoTen);
		case 'd':
			return cmpBirthday(sv2,sv1);
		case 'e':
			return ((sv1.diem<=sv2.diem2)&&(sv1.diem>=sv2.diem1));
		case 'f':
			return (sv1.gioiTinh==sv2.gioiTinh) ;
			
	}
}
void runSearch()
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
		for (int i=0;i<count;i++)
			printTT(5,20,SIZE_TABLE,res[i],i,i);
	}	
	else
	{
		GoTo(INPUT_X, INPUT_Y+HEIGHT*5);
		cout<<"Khong co sinh vien thoa man!";
	}
		
}

