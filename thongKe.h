#ifndef _QLSV_H_
#define _QLSV_H_
#include "search.h"
#endif

string MENU_THONG_KE[3] = {"Theo lop", 
							"KQ hoc tap",
							"Thoat"};
int SIZE_THONG_KE_THEO_LOP[4] = {0, 20, 70, 90};
string SHOW_TOP_THONG_KE_LOP[3] = {"Ma lop", "Ten lop", "So sinh vien" };
int SIZE_THONG_KE_THEO_KQ[12] = {0, 15, 22, 29, 36, 43, 50, 57, 64, 71, 77, 84};
string SHOW_TOP_THONG_KE_KQ[6] = {"Ma lop", "Xuat sac", "Gioi", "Kha", "Trung binh", "Yeu" };
string SHOW_TOP_THONG_KE_KQ_TRUONG2[12] = {"", "SL", "%","SL", "%","SL", "%","SL", "%","SL", "%"};

void thongKeTheoLop();
void thongKeTheoKQ();
float g;
struct thongketheolop
{
	string maLop;
	string tenLop;
	int soSV;
} thongKeLop[100];
struct thongketheokq
{
	string maLop;
	int gioi;
	int suatxac;
	int kha;
	int trungbinh;
	int yeu;
	int tong;
}thongKeKQ[100];

void (*actionMenuThongKe[])() = {&thongKeTheoLop,&thongKeTheoKQ};

void MenuThongKe()
{
	XoaManHinh();
	int action, arrow = 0;
	int size = 3;
	drawMenu(DX+ 3, DY , MENU_THONG_KE, size, 0);
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
				  } // thoat 
	  			(*actionMenuThongKe[arrow])();
  		}
		arrow = (arrow + size*10)%size;
		drawMenu(DX + 3, DY , MENU_THONG_KE, size, arrow);
	}
}
void rawTextDemoTheoLop(int x,int y,int size[], string data[])
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	
	for(int i = 0; i<3; i++)
	{
		int length = (size[i+1] - size[i]+1);
		GoTo(x+ size[i] + length/2- data[i].length()/2, y+1);
		cout << data[i];
	}
}
void rawBangThongKeTheoLop(int x, int y, string data[])
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	GoTo(x, y);
	for(int i= 0; i< SIZE_THONG_KE_THEO_LOP[3]; i++) printf("%c", 196);
	GoTo(x, y+2);
	for(int i= 0; i< SIZE_THONG_KE_THEO_LOP[3]; i++) printf("%c", 196);

	for(int i= 0; i< 4; i++) {
		GoTo(x+SIZE_THONG_KE_THEO_LOP[i], y+1);	printf("%c", 179);
		GoTo(x+SIZE_THONG_KE_THEO_LOP[i], y); 	printf("%c", 194);
		GoTo(x+SIZE_THONG_KE_THEO_LOP[i], y+2);	printf("%c", 193);
	}
	GoTo(x, y); printf("%c",218);
	GoTo(x+SIZE_THONG_KE_THEO_LOP[3], y); printf("%c",191);
	GoTo(x, y+2); printf("%c",192);
	GoTo(x+SIZE_THONG_KE_THEO_LOP[3], y+2); printf("%c",217);
	rawTextDemoTheoLop(x,y,SIZE_THONG_KE_THEO_LOP, SHOW_TOP_THONG_KE_LOP);
	
}

void rawSVThongKeTheoLop(int x, int y, int size[], thongketheolop data, int vt)
{
	y += vt*2;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	GoTo(x, y+2);
	for(int i= 0; i<SIZE_THONG_KE_THEO_LOP[3]; i++) printf("%c", 196);

	for(int i= 0; i< 4; i++) {
		GoTo(x+SIZE_THONG_KE_THEO_LOP[i], y+1);	printf("%c", 179);
		GoTo(x+SIZE_THONG_KE_THEO_LOP[i], y); 		printf("%c", 197);
		GoTo(x+SIZE_THONG_KE_THEO_LOP[i], y+2);	printf("%c", 193);
	}
	GoTo(x, y); printf("%c",195);
	GoTo(x+SIZE_THONG_KE_THEO_LOP[3], y); printf("%c",180);
	GoTo(x, y+2); printf("%c",192);
	GoTo(x+SIZE_THONG_KE_THEO_LOP[3], y+2); printf("%c",217);
	
	
	string bang[3];
	bang[0] = data.maLop ;
	bang[1] = data.tenLop;
	bang[2] = coverIntToString(data.soSV, 3);
	rawTextDemoTheoLop(x,y,size, bang);
}

void thongKeSinhVienTheoLop()
{
	for (cauTruc*i = dataSinhVien; i != NULL; i = i->next)
	{
		for(int j = 0; j< SIZE_LOP; j++) 
			if (thongKeLop[j].maLop == i->data.maLop) 
			 	thongKeLop[j].soSV++;
		thongKeLop[SIZE_LOP].soSV++;//sum
	}
}

void thongKeTheoLop()
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
	thongKeSinhVienTheoLop();
	
	rawBangThongKeTheoLop(25, 5, SHOW_TOP_THONG_KE_LOP);
	int dem = 1;
	for (int i= 0; i<= SIZE_LOP; i++){
		rawSVThongKeTheoLop(25, 5, SIZE_THONG_KE_THEO_LOP,thongKeLop[i], dem++);	
	}
	SetConsoleTextAttribute(hConsole, 10);
	GoTo(25+SIZE_THONG_KE_THEO_LOP[1], 5 + (dem-1)*2+1 ); 		printf("%c", ' ');
	GoTo(25+SIZE_THONG_KE_THEO_LOP[1], 5 + (dem-1)*2 ); 		printf("%c", 193);
	GoTo(25+SIZE_THONG_KE_THEO_LOP[1], 5 + (dem-1)*2+2 ); 		printf("%c", 196);
	int ch = getch();
		system("cls");
}
//---------------------------------------------------------------------------------------------------



void rawTextDemoTheoKQ(int x,int y,int size[], string data[])
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	
	int vttr = 1;
	int vtsau =0;
	for(int i = 0; i<6; i++)
	{
		int length = (size[vttr] - size[vtsau]+1);
		GoTo(x+ size[vtsau] + length/2- data[i].length()/2, y+1);
		cout << data[i];
		if (i > 0) vtsau +=2;
		else vtsau +=1;
		vttr+=2;
	}
}

void rawTextTheoKQ (int x, int y, int size[], string data[])
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	
	for(int i = 0; i<11; i++)
	{
		int length = (size[i+1] - size[i]+1);
		GoTo(x+ size[i] + length/2- data[i].length()/2, y+1);
		cout << data[i];
	}
}
void rawBangThongKeTheoKQ(int x, int y, string data[])
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	GoTo(x, y);
	for(int i= 0; i< SIZE_THONG_KE_THEO_KQ[11]; i++) printf("%c", 196);
	GoTo(x, y+2);
	for(int i= 0; i< SIZE_THONG_KE_THEO_KQ[11]; i++) printf("%c", 196);
	GoTo(x, y+4);
	for(int i= 0; i< SIZE_THONG_KE_THEO_KQ[11]; i++) printf("%c", 196);
	for(int i= 0; i< 12; i++) {
		GoTo(x+SIZE_THONG_KE_THEO_KQ[i], y+1);	printf("%c", 179);
		if (i-2 < 0 || (i-2)%2==1 )
		{	
			GoTo(x+SIZE_THONG_KE_THEO_KQ[i], y); 		printf("%c", 194);
			GoTo(x+SIZE_THONG_KE_THEO_KQ[i], y+2);	printf("%c", 197);
			
		}else {
			GoTo(x+SIZE_THONG_KE_THEO_KQ[i], y+2);	printf("%c", 194);
		}
		
		GoTo(x+SIZE_THONG_KE_THEO_KQ[i], y+3);	printf("%c", 179);
		GoTo(x+SIZE_THONG_KE_THEO_KQ[i], y+4);	printf("%c", 193);
	}
	GoTo(x, y); printf("%c",218);
	GoTo(x+SIZE_THONG_KE_THEO_KQ[11], y); printf("%c",191);
	//
	GoTo(x, y+2); printf("%c", 179);
	for(int L = 1; L < SIZE_THONG_KE_THEO_KQ[1]; L++){
		GoTo(x+L, y+2) ;printf(" ");
	}
	//
	GoTo(x + SIZE_THONG_KE_THEO_KQ[1], y+2); printf("%c", 195);
	GoTo(x+SIZE_THONG_KE_THEO_KQ[11], y+2); printf("%c",180);
	rawTextDemoTheoKQ(x,y,SIZE_THONG_KE_THEO_KQ, SHOW_TOP_THONG_KE_KQ);
	rawTextTheoKQ(x, y+2, SIZE_THONG_KE_THEO_KQ, SHOW_TOP_THONG_KE_KQ_TRUONG2);
}

void rawSVThongKeTheoKQ(int x, int y, int size[], thongketheokq data, int vt)
{
	y += vt*2;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	GoTo(x, y+2);
	for(int i= 0; i<SIZE_THONG_KE_THEO_KQ[11]; i++) printf("%c", 196);

	for(int i= 0; i< 12; i++) {
		GoTo(x+SIZE_THONG_KE_THEO_KQ[i], y+1);	printf("%c", 179);
		GoTo(x+SIZE_THONG_KE_THEO_KQ[i], y); 		printf("%c", 197);
		GoTo(x+SIZE_THONG_KE_THEO_KQ[i], y+2);	printf("%c", 193);
	}
	GoTo(x, y); printf("%c",195);
	GoTo(x+SIZE_THONG_KE_THEO_KQ[11], y); printf("%c",180);
	GoTo(x, y+2); printf("%c",192);
	GoTo(x+SIZE_THONG_KE_THEO_KQ[11], y+2); printf("%c",217);
	
	
	string bang[11];
	bang[0] = data.maLop ;


	if (data.tong == 0) 
		for(int i= 1; i <= 10; i++) bang[i] = coverIntToString(0, 1);
	else{
		
		bang[1] = coverIntToString(data.suatxac, 3);
		bang[2] = ftos((float)data.suatxac/data.tong);
		bang[3] = coverIntToString(data.gioi, 3);
		bang[4] = ftos((float)data.gioi/data.tong);
		bang[5] = coverIntToString(data.kha, 3);
		bang[6] = ftos((float)data.kha/data.tong);
		bang[7] = coverIntToString(data.trungbinh, 3);
		bang[8] = ftos((float)data.trungbinh/data.tong);
		bang[9] = coverIntToString(data.yeu, 3);
		bang[10] = ftos((float)data.yeu/data.tong);
	}
	
	rawTextTheoKQ(x,y,size, bang);
}

void thongKeSinhVienTheoKQ()
{
	for (cauTruc*i = dataSinhVien; i != NULL; i = i->next)
	{
		for(int j = 0; j< SIZE_LOP; j++) 
			if (thongKeKQ[j].maLop == i->data.maLop)
			{
				thongKeKQ[j].tong++;
				float diem = i->data.diem;
				if (diem >= 9 ) thongKeKQ[j].suatxac++;
				else if (diem >= 8) thongKeKQ[j].gioi++;
				else if(diem >= 7) thongKeKQ[j].kha++;
				else if(diem >= 5) thongKeKQ[j].trungbinh++;
				else thongKeKQ[j].yeu++;
			}
	}
	
	for(int i = 0 ; i < SIZE_LOP; i++)
	{
		thongKeKQ[SIZE_LOP].tong += thongKeKQ[i].tong;
		thongKeKQ[SIZE_LOP].suatxac+= thongKeKQ[i].suatxac;
		thongKeKQ[SIZE_LOP].gioi += thongKeKQ[i].gioi;
		thongKeKQ[SIZE_LOP].kha += thongKeKQ[i].kha;
		thongKeKQ[SIZE_LOP].trungbinh += thongKeKQ[i].trungbinh;
		thongKeKQ[SIZE_LOP].yeu += thongKeKQ[i].yeu;
	}
	
}
void thongKeTheoKQ()
{
	system("cls");
	GoTo(0,3);
	for(int i= 0; i<= 90; i++) cout << " ";
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	
	GoTo(47, 3); cout <<"THONG KE SINH VIEN THEO KET QUA";
	
	
	
	for(int i= 0; i<= SIZE_LOP; i++ ) {
		if (i < SIZE_LOP)thongKeKQ[i].maLop = DANH_SACH_LOP[i];
		else thongKeKQ[i].maLop = "Tong";
		thongKeKQ[i].gioi = 0;
		thongKeKQ[i].suatxac = 0;
		thongKeKQ[i].kha  = 0;
		thongKeKQ[i].trungbinh = 0;
		thongKeKQ[i].yeu = 0;
		thongKeKQ[i].tong = 0;
	}
	thongKeSinhVienTheoKQ();
	
	cout<<"Nhap%";cin>>g;
	cout<<"\nThong ke Gioi \n";
	for(int j = 0; j< SIZE_LOP; j++) 
		{
			float tg = float(thongKeKQ[j].gioi)/thongKeKQ[j].tong;
//			cout<<tg-g<<endl;
			if (tg-g >=0 )
			
			{
				switch(j)
				{
					case 0:
						cout<<"CNTT1";
						break;
										case 1:
						cout<<"CNTT2";
						break;
										case 2:
						cout<<"BDATTT";
						break;
										case 3:
						cout<<"ANHTTT";
						break;
				}
			}
		}
	rawBangThongKeTheoKQ(15, 5, SHOW_TOP_THONG_KE_KQ);
	int dem = 2;
	for (int i= 0; i<=SIZE_LOP; i++){
		rawSVThongKeTheoKQ(15, 5, SIZE_THONG_KE_THEO_KQ,thongKeKQ[i], dem++);	
	}

	int ch = getch();
	system("cls");
}
