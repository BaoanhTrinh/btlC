#ifndef _QLSV_H_
#define _QLSV_H_
#endif

//--------------------DATA----------------------------------
string TOP_TABLE[7] = {"STT","LOP","MA SV","HO TEN","NGAY SINH","GT","DIEM"};
int SIZE_TABLE[8] = {0,6,20,35,65,80,90,100};
string MENU_SELECTION[3]={"IN THONG TIN THEO ID","IN DANH SACH SV","Thoat"};
sinhvien arr_sv[5000];

//--------------PROTOTYPES-----------------------------

void menuPrint(int x,int y);
void printText(int x,int y,int size[], string data[]);
void drawTableRow(int x, int y);
void drawTop(int x,int y);
void printTT(int x,int y,int size[],sinhvien sv,int vt,int stt);
void inID();
void inDanhSach();
void separatePage();
void (*actionMenuPrint[])()={&inID,&inDanhSach};
//-----------------FUNCTIONS-----------------------------
void menuPrint()
{
	XoaManHinh();
	hideCur();
	drawMenu(DX+ 3, DY ,MENU_SELECTION,3,0);
	int arrow=0,action,size=3;
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
				
				(*actionMenuPrint[arrow])();
		}
		arrow = (arrow + size*10) % size;
		drawMenu(DX+ 3, DY ,MENU_SELECTION,3,arrow);
	}
}
void printText(int x,int y,int size[], string data[])
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,15);
	for (int i=0;i<7;i++)
	{
		int l = size[i+1]-size[i];
		GoTo(x + size[i] + l/2- data[i].length()/2,y+1); 
		cout << data[i];
	}
}
void drawTableRow(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,6);
	// ke ngang
	GoTo(x,y);
	for (int i=0;i< SIZE_TABLE[7];i++) printf("%c",196);
	GoTo(x,y+2);
	for (int i=0;i< SIZE_TABLE[7];i++) printf("%c",196);
	// ke doc
	for (int i=0;i<8;i++)
	{
		GoTo(x + SIZE_TABLE[i],y+1); printf("%c",179);
		GoTo(x + SIZE_TABLE[i],y);printf("%c",194);
		GoTo(x + SIZE_TABLE[i],y+2); printf("%c",193);
	}
	// cac goc
	GoTo(x,y);printf("%c",218);
	GoTo(x+SIZE_TABLE[7],y); printf("%c",191);
	GoTo(x,y+2);printf("%c",192);
	GoTo(x+SIZE_TABLE[7],y+2); printf("%c",217);
	
}
void drawTop(int x,int y)
{
	drawTableRow(x, y);
	printText(x,y,SIZE_TABLE,TOP_TABLE);
}

void printTT(int x,int y,int size[],sinhvien sv,int vt,int stt)
{
	y +=vt*2;
	drawTableRow(x,y);
	string thongTin[7];
	thongTin[0]= convertIntToString(stt,3);
	thongTin[2]= sv.maSV;
	thongTin[1]= sv.maLop;
	thongTin[3]= sv.hoTen;
	thongTin[4]= sv.ngaySinh;
	thongTin[5]= sv.gioiTinh == 1 ? "NAM" : "NU";
	thongTin[6] = ftos(sv.diem);
	printText(x,y,size,thongTin);
	
}
void inID()
{
	showCur();
	XoaManHinh();
	int kt=0;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string ID;
	fflush(stdin);
	draw(20,10,40,3,"Nhap ID cua sinh vien:",0);
	draw(65,10,40,3,"",1);
	GoTo(75,11);
	cin>>ID;
	for (cauTruc *i=dataSinhVien;i!=NULL;i=i->next)
	{
		if (i->data.maSV == ID)
		{
			XoaManHinh();	
			printTT(5,5,SIZE_TABLE,i->data,1,0);
			drawTop(5,2);
			kt=1;
			char ch = getch();
			XoaManHinh();
			break;
		}		
	}
	if (kt==0) {
		SetConsoleTextAttribute(hConsole,12);
		GoTo(75,11);cout<<"ID khong ton tai!";
		char ch=getch();
		XoaManHinh();
	}
	hideCur();
}
int numberStudents()
{
	int num=0;
	for (cauTruc *i=dataSinhVien;i!=NULL;i=i->next)
		num++;
	return num;
}
//void printFromstt(int arr[],int stt,int size)
//{
//	for (int i = stt;i<stt+size;i++)
//	{
//		printTT(5,5,SIZE_TABLE,arr_sv[i],i);
//	}
//}
void inDanhSach()
{
	int stt = 1,maxPage;
	int currentPage = 1, size =-1;
	int dem=1;
	int ch =0;
	while (size <=0)
	{
			showCur();
			draw(DX+WIDTH+3,DY+HEIGHT,WIDTH,HEIGHT,"Size page:          ",0);
			GoTo(DX+WIDTH+20,DY+HEIGHT+1);
			fflush(stdin);
			cin>>size;
	}
	int sum=1;
	if (dataSinhVien!=NULL)
	{
		for (cauTruc *i=dataSinhVien;i!=NULL;i=i->next)
		{ 
			arr_sv[sum] = i->data;
			sum = sum+1;
		}
	}
	sum--;
	int rest = sum%size;	
	if (rest==0)
	{
		maxPage = sum / size ;
	}
	else
		maxPage = sum / size +1;
	
	system("cls");
	GoTo(43,3);cout<<"DANH SACH SINH VIEN";
	drawTop(5,10);
	GoTo(50,5); cout<<currentPage<<"/"<<maxPage;
	if (maxPage > 1)
		{
			GoTo(56,5);printf("%c",175);
		}
	hideCur();
	for (int i = 1;i<=size;i++)
	{
		printTT(5,10,SIZE_TABLE,arr_sv[stt],i,stt);
		stt++;
	}
	
	fflush(stdin);
	while (ch!=KEY_ESC)
	{
		ch = getCode(); 
		if (ch == ARROW_RIGHT && currentPage < maxPage)
		{
			system("cls");
			GoTo(43,3);cout<<"DANH SACH SINH VIEN";
			drawTop(5,10);
			currentPage++;
			GoTo(45,5); printf("%c",174);
			GoTo(50,5); cout<<currentPage<<"/"<<maxPage;
			if (currentPage != maxPage)
			{
				GoTo(56,5);printf("%c",175);
			}
			if (currentPage==maxPage)
			{
				
				int temp=stt;
				for (int i = 1;i<=rest;i++)
				{
					printTT(5,10,SIZE_TABLE,arr_sv[stt],i,stt);
					stt++;
				}	
				stt= temp+size;
			}
			else
			{
				for (int i = 1;i<=size;i++)
				{
					printTT(5,10,SIZE_TABLE,arr_sv[stt],i,stt);
					stt++;
				}
			}
			
		}
		if (ch == ARROW_LEFT && currentPage>1)
		{
			system("cls");
			GoTo(43,3);cout<<"DANH SACH SINH VIEN";
			drawTop(5,10);
			currentPage--;
			stt -=2*size;
			for (int i = 1;i<=size;i++)
			{
				printTT(5,10,SIZE_TABLE,arr_sv[stt],i,stt);
				stt++;
			}
				
			if (currentPage!=1)
			{
				GoTo(45,5); printf("%c",174);
			}
			GoTo(50,5); cout<<currentPage<<"/"<<maxPage;
			GoTo(56,5);printf("%c",175);
		}
	}	
	XoaManHinh();
}
//void inDanhSach_old()
//{
//	int count = 1,maxPage;
//	int currentPage = 1, size =-1;
//	int dem=1;
//	char ch ='\0';
//	while (size <=0)
//	{
//			showCur();
//			draw(DX+WIDTH+3,DY+HEIGHT,WIDTH,HEIGHT,"Size page:          ",0);
//			GoTo(DX+WIDTH+20,DY+HEIGHT+1);
//			fflush(stdin);
//			cin>>size;
//	}
//	int sum = numberStudents();
//	if (sum%size==0)
//	{
//		maxPage = sum / size ;
//	}
//	else
//		maxPage = sum / size +1;
//	system("cls");
//	HANDLE hConsole;
//	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hConsole, 7);
//	GoTo(45,3);cout<<"DANH SACH SINH VIEN";
//	drawTop(5,5);
//	SetConsoleTextAttribute(hConsole, 14);
//	GoTo(47,30); cout<<currentPage<<"/"<<maxPage;
//	if (maxPage > 1)
//		{
//			GoTo(56,30);printf("%c",175);
//		}
//	
//	hideCur();
//	convertToDoubleLinkedList();
//	struct Node *j = head;
//	if (j!=NULL)
//	{
//			// first page
//			for (j= head;j!= NULL;j=j->next)
//			{
//				printTT(5,5,SIZE_TABLE,j->data,count++,dem++);	
//				if (dem>size ) break;
//			}
//			if (dem>size) j= j->next;
//		
//			char ch ='\0';
//			while (1)
//			{
//				
//				SetConsoleTextAttribute(hConsole,12);
//				GoTo(45,3);cout<<"DANH SACH SINH VIEN";
//				fflush(stdin);
//				ch = getCode();
//				while (!((ch == KEY_ESC)||(ch == ARROW_RIGHT)|| (ch == ARROW_LEFT))) ch = getCode();
//				if (ch == KEY_ESC) {
//					XoaManHinh();
//					return;
//				}
//				else if (ch == ARROW_RIGHT)
//				{
//					//if (j->next!=NULL) j=j->next;
//					dem=1;
//					if ( currentPage < maxPage )
//					{
//						XoaManHinh();
//						currentPage ++;
//						SetConsoleTextAttribute(hConsole, 14);
//						GoTo(45,30); printf("%c",174);
//						GoTo(47,30); cout<<currentPage<<"/"<<maxPage;
//						if (currentPage != maxPage)
//						{
//							GoTo(56,30);printf("%c",175);
//						}
//						
//						for (;j!= NULL;j=j->next)
//						{
//							printTT(5,5,SIZE_TABLE,j->data,count++,dem++);	
//							if (dem > size ) break;
//						}
//						if (j == NULL) j=tail;
//						else j= j->next;
//					}
//				}
//				else if (currentPage > 1)
//				{
//					dem = 1;
//					XoaManHinh();
//					currentPage --;
//					SetConsoleTextAttribute(hConsole, 14);
//					if (currentPage!=1)
//					{
//						GoTo(45,30); printf("%c",174);
//					}
//					GoTo(47,30); cout<<currentPage<<"/"<<maxPage;
//					GoTo(56,30);printf("%c",175);
//					if (count % size == 1) 
//					{
//						for (int i=0;i<size;i++) j = j->prev;
//					}
//					else
//					{
//						for (int i=0;i <sum%size ;i++) j = j->prev;
//					}
//					for (int i=0;i<size;i++) 
//					{
//						j = j->prev;
//						if (j==NULL) 
//						{
//							j = head;
//							break;
//						}
//					}
//					
//					if (count % size == 1)
//						count = count - 2*size;
//					else
//						count = count - sum % size - size;
//					if (count != 1) j =j->next;
//			
//					// count = STT
//					for (;j!= NULL;j=j->next)
//					{
//						printTT(5,5,SIZE_TABLE,j->data,count++,dem++);	
//						if (dem > size ) break;
//					}
//					if (j == NULL) j=tail;
//					else j= j->next;
//					
//				}
//			}
//	}
//}
