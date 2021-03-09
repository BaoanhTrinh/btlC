#ifndef _QLSV_H_
#define _QLSV_H_
#include "lib.h"
#include "json.h"
#include "getTT.h"
#include "inDS.h"
#endif


string MENU_UPDATE[4] = { "Them","Sua","Xoa","Thoat"};
string key;
void suaThongTin();
void xoaThongTin();
void showData();
void inputLuu();
void giaodien();
void (*actionMenuUpdate[])() = {&nhapThongTin,&suaThongTin,&xoaThongTin};
void (*actionMenuFix[])() = {&inputClass, &inputSv, &inputName, &inputDate, &inputPoint, &inputSex, &inputLuu, &inputReset};
void menuUpdate()
{
	XoaManHinh();
	hideCur();
	drawMenu(DX,DY,MENU_UPDATE,4,0);
	int arrow=0,action,size=4;
	while ((action=getCode())!=KEY_ESC)
	{
		switch(action)
		{
			case ARROW_UP:
				arrow--;
				break;
			case ARROW_DOWN:
				arrow++;
				break;
			case KEY_ENTER:
				arrow = (arrow + size*10) % size;
				if (arrow == size-1)
				{
					XoaManHinh();
					return;
				}
				
				(*actionMenuUpdate[arrow])();
		}
		arrow = (arrow + size*10) % size;
		drawMenu(DX,DY,MENU_UPDATE,4,arrow);
	}
}

void xoaThongTin()
{
	showCur();
	XoaManHinh();
	int kt=0,position=-1;
	char opt;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string ID;
	fflush(stdin);
	while(1)
	{
		draw(20,10,40,3,"Nhap ID cua sinh vien:",0);
		draw(65,10,40,3,"",1);
		GoTo(75,11);
		cin>>ID;
		for (cauTruc *i=dataSinhVien;i!=NULL;i=i->next)
		{
			position++;
			if (i->data.maSV == ID)
			{
				XoaManHinh();
//				printTT(5,5,SIZE_TABLE,i->data,1,0);
//				drawTop(5,3);
				MENU_CIN_DEMO[0] = i->data.maLop;
				MENU_CIN_DEMO[1] = i->data.maSV;
				MENU_CIN_DEMO[2] = i->data.hoTen;
				MENU_CIN_DEMO[3] = i->data.ngaySinh;
				MENU_CIN_DEMO[4] = ftos(i->data.diem);
				MENU_CIN_DEMO[5] = i->data.gioiTinh == 1?"NAM":"NU";
				drawMenu(INPUT_X, INPUT_Y, MENU_CIN, 6, 0);
				rawFontInput(INPUT_X+WIDTH+3, INPUT_Y,MENU_CIN_DEMO,  6, -1);
				kt=1;
				fflush(stdin);
				GoTo(40,30);cout<<"Ban chac chan muon xoa ? (Y/N) :";cin>>opt;
				if (opt=='Y'||opt=='y') 
				{
					dataSinhVien = DelAt(dataSinhVien,position);
					writeFileAll(dataSinhVien);
					cout<<"Deleted!";
					opt  = getch();
				}
				XoaManHinh();
				return;
			}		
		}
		if (kt==0) {
			SetConsoleTextAttribute(hConsole,12);
			GoTo(75,11);cout<<"ID khong ton tai!";
			char ch = getch();
			GoTo(75,11);cout<<"                    ";
			if (ch == KEY_ESC)
				XoaManHinh();
		}
		hideCur();
	}
}
void inputLuu()
{
	if (svXuLy.hoTen != sv.hoTen
		||  svXuLy.maLop != sv.maLop
		||  svXuLy.maSV != sv.maSV
		||  svXuLy.ngaySinh != sv.ngaySinh
		|| 	svXuLy.gioiTinh !=svXuLy.gioiTinh
		||	svXuLy.diem !=svXuLy.diem) {
			for (cauTruc *i=dataSinhVien;i!=NULL;i=i->next)
			{
				if (i->data.maSV == key)
				{
					i->data = svXuLy;
					break;
				}		
			}
			writeFileAll(dataSinhVien);
			return;
		}
	GoTo(INPUT_X +WIDTH +3, INPUT_Y + 6*HEIGHT+3);cout<<"Save!";
}
void giaodien()
{
	
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
	GoTo(8, 3); cout <<"SUA THONG TIN SINH VIEN";
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
	  			(*actionMenuFix[arrow])();
	  		
  		}
		arrow = (arrow + size*10)%size;
		drawMenu(INPUT_X,INPUT_Y,MENU_CIN, size, arrow);
		SetConsoleTextAttribute(hConsole, 14);
		
		GoTo(0,3);
		for(int i= 0; i<= 90; i++) cout << " ";
		GoTo(8, 3); cout <<"SUA THONG TIN SINH VIEN";
	}
	

}
void suaThongTin()
{
	showCur();
	XoaManHinh();
	int kt=0;
	char ch ;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string ID;
	fflush(stdin);
	while(1)
	{
		draw(20,10,40,3,"Nhap ID cua sinh vien:",0);
		draw(65,10,40,3,"",1);
		GoTo(75,11);
		cin>>ID;
		key = ID;
		for (cauTruc *i=dataSinhVien;i!=NULL;i=i->next)
		{
			
			if (i->data.maSV == ID)
			{
				XoaManHinh();
				MENU_CIN_DEMO[0] = i->data.maLop;
				MENU_CIN_DEMO[1] = i->data.maSV;
				MENU_CIN_DEMO[2] = i->data.hoTen;
				MENU_CIN_DEMO[3] = i->data.ngaySinh;
				MENU_CIN_DEMO[4] = ftos(i->data.diem);
				MENU_CIN_DEMO[5] = i->data.gioiTinh == 1?"NAM":"NU";
				svXuLy = i->data;
				giaodien();
				XoaManHinh();
				return;
			}		
		}
		if (kt==0) {
			SetConsoleTextAttribute(hConsole,12);
			GoTo(75,11);cout<<"ID khong ton tai!";
			ch = getch();
			GoTo(75,11);cout<<"                    ";
			if (ch == KEY_ESC)
				XoaManHinh();
		}
		hideCur();
	}
}

