#ifndef _QLSV_H_
#define _QLSV_H_
#include "lib.h"
#include "json.h"
#endif

int WIDTH_INPUT = 35;

string MENU_CIN[9] = {"Ma lop", "Ma sinh vien", "Ho va ten", "Ngay sinh", "Diem trung binh","Gioi tinh", "Luu","Reset", "Thoat"};
string MENU_CIN_DEMO[8] = {"None", "None", "None", "00/00/0000", "0.00", "None","Luu", "Thoat"};
string MENU_CIN_SHOW[8] = {"None", "None", "None", "00/00/0000", "0.00","None", "Luu", "Thoat"};
void inputClass();
void inputSv();
void inputName();
void inputDate();
void inputPoint();
void inputSex();
void inputSave();
void inputReset();
sinhvien svXuLy;
void (*actionMenuInput[])() = {&inputClass, &inputSv, &inputName, &inputDate, &inputPoint, &inputSex, &inputSave, &inputReset};
void rawFontInput(int x, int y, string data[], int size, int chon)
{

	for(int i= 0 ; i< size; i++)
	{
		int k = 0;
		if (chon == i) k = 1;
		draw(x, y + i*HEIGHT, WIDTH_INPUT ,HEIGHT, data[i], k);
	}
	
}

void nhapThongTin()
{
	svXuLy = sv;
	system("cls");
	drawMenu(INPUT_X, INPUT_Y, MENU_CIN, 9, 0);
	rawFontInput(INPUT_X+WIDTH+3, INPUT_Y,MENU_CIN_DEMO,  6, -1);
	int action, arrow = 0;
	int size = 9;
	
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	
	
	//
	GoTo(0,3);
	for(int i= 0; i<= 90; i++) cout << " ";
	GoTo(15, 3); cout <<"THEM THONG TIN SINH VIEN";
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
	  			if (arrow == size-1) {
				  	system("cls");
					return; // thoat 
				}
	  			(*actionMenuInput[arrow])();
	  		
  		}
		arrow = (arrow + size*10)%size;
		drawMenu(INPUT_X,INPUT_Y,MENU_CIN, size, arrow);
		SetConsoleTextAttribute(hConsole, 14);
		
		GoTo(0,3);
		for(int i= 0; i<= 90; i++) cout << " ";
		GoTo(15, 3); cout <<"THEM THONG TIN SINH VIEN";
	}
	
	
}
void delInput(int x, int y)
{
	GoTo(x, y);
	for(int i= 1; i< WIDTH_INPUT-3; i++)printf(" ");
}
string inputRaw(int x, int y)
{
	delInput(x+1, y);
	GoTo(x+2,y);
	string temp;
	showCur();
	
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	fflush(stdin);
	getline(cin,temp);

	hideCur();
	delInput(x+1, y);
	return temp;
}

void inputClass()
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

	svXuLy.maLop = sv_class;
}

bool checkChungMaSinhVien(string key)
{
	for(cauTruc* i= dataSinhVien; i != NULL; i= i->next)
	{
		if(i->data.maSV == key) return 1;
	}
	return 0;
}
void inputSv()
{
	string svSv ;
	while(1)
	{		
		svSv = inputRaw(INPUT_X +WIDTH +3, INPUT_Y +1*HEIGHT +1);
		string error;
		if (svSv.length() == 8)
		{
			if (checkChungMaSinhVien(svSv) == 0)  break;
			else error = "MSV ton tai";
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
		cout << "                ";
	}
	svXuLy.maSV = svSv;
	draw(INPUT_X +WIDTH +3, INPUT_Y + 1*HEIGHT, WIDTH_INPUT ,HEIGHT, svSv, -1);
	
}
void inputName()
{
	string svName = inputRaw(INPUT_X +WIDTH +3, INPUT_Y + 2*HEIGHT +1);
	svName = chuanHoaTen(svName);
	draw(INPUT_X +WIDTH +3, INPUT_Y + 2*HEIGHT, WIDTH_INPUT ,HEIGHT, svName, -1);
	svXuLy.hoTen = svName;
}
void inputDate()
{
	showCur();
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
	svXuLy.ngaySinh = SDate;
	hideCur();
}
void inputPoint()  // nhap diem 
{
	int x = INPUT_X +WIDTH +3;
	int y = INPUT_Y +4*HEIGHT +1;
	float svPoint = -1;
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
		if (svPoint != -1 && ok) break;
		
		SetConsoleTextAttribute(hConsole, 71);  // In loi bao sai 
		GoTo(x+2, y);
		cout << "Nhap sai diem";
		int pause = getch();
		cout << "             ";
		SetConsoleTextAttribute(hConsole, 15);
	 }
	hideCur();
	draw(INPUT_X +WIDTH +3, INPUT_Y + 4*HEIGHT, WIDTH_INPUT ,HEIGHT, floatToString(svPoint), -1);
	svXuLy.diem = svPoint;
}
void inputSex()
{
	string svSex ="";
	while (!(svSex=="NAM" || svSex=="NU"))
	{
			delInput(INPUT_X +WIDTH +10, INPUT_Y + 5*HEIGHT +1);
			svSex= inputRaw(INPUT_X +WIDTH +10, INPUT_Y + 5*HEIGHT +1);
			svSex = upperCase(svSex);
	}
	draw(INPUT_X +WIDTH +3, INPUT_Y + 5*HEIGHT, WIDTH_INPUT ,HEIGHT, svSex, -1);
	svXuLy.gioiTinh = (svSex=="NAM"?1:0);
}
void inputSave()
{
//	if (svXuLy.hoTen == sv.hoTen
//		||  svXuLy.maLop == sv.maLop
//		||  svXuLy.maSV == sv.maSV
//		||  svXuLy.ngaySinh == sv.ngaySinh) {
//			return;
//		} // du lieu ma chua nhap het thi thoat
	addSinhVien(svXuLy, &dataSinhVien);
	writeFile(svXuLy);
//	cout << ++dem;
	inputReset();
}

void inputReset()
{
	//resetInput(&svXuly);
	svXuLy = sv;
	delInput(INPUT_X+WIDTH +3, INPUT_Y); // xoa du lieu 
	delMenu(INPUT_X+WIDTH+3, INPUT_Y, INPUT_X+WIDTH+3 + WIDTH_INPUT, INPUT_Y+HEIGHT*7); // Xoa khung
	rawFontInput(INPUT_X+WIDTH+3, INPUT_Y,MENU_CIN_DEMO,  6, -1);
	
}
