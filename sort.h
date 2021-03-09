#ifndef _QLSV_H_
#define _QLSV_H_

#endif 

using namespace std;
//----------------------DATA---------------------------
string MENU_SORT[4] = { "Thuat toan sx","Khoa sx","Sap xep","Thoat"};
string MENU_TYPE_SORT[5] ={"Sap xep chon","Sap xep chen","Sap xep nhanh","Sap xep noi bot","Thoat"};
string MENU_PRIORITY_SORT[5]={"","","","",""};
string MENU_ORDER_SORT[5]={"","","","",""};
string MENU_KEY_SORT[6] = {"Ma lop","Ma sinh vien","Ho va ten", "Ngay sinh", "Diem TB", "Thoat"};
int valFuncSort = -1;
int valKeySort = -1;
int order[5];
char priority[5];

//------------------------PROTOTYPES----------------
void menuSort();
void funtionSort();
void keySort();
void orderSort();

void selectionSort(int key);
void insertionSort(int key);
void quickSort(int key);
void bubbleSort(int key);
void sort(int func, int key);

int cmpClass(sinhvien s1,sinhvien s2);
int cmpID(sinhvien s1,sinhvien s2);
int cmpName(sinhvien s1,sinhvien s2);
int cmpDate(sinhvien s1,sinhvien s2);
int cmpMark(sinhvien s1,sinhvien s2);

void runSort();
void (*actionMenuSort[])() = {&funtionSort, &keySort,&runSort};
int (*actionPriorOrderSort[])(sinhvien, sinhvien)={&cmpClass,
													&cmpID,
													&cmpName,
													&cmpDate,
													&cmpMark};
//--------------------FUNCTIONS-----------------------
int cmpClass(sinhvien s1,sinhvien s2)
{
	if (order[0]==0)// chieu A-Z : nho den lon
	{
			if (s1.maLop < s2.maLop) return -1;
			else if (s1.maLop > s2.maLop) return 1;
	}
	else
	{
		if (s1.maLop < s2.maLop) return 1;
		else if (s1.maLop > s2.maLop) return -1;
	}
	return 0;
}
int cmpID(sinhvien s1,sinhvien s2)
{
	if (order[1]==0)
	{
			if (s1.maSV > s2.maSV) return 1; 
			else if(s1.maSV < s2.maSV) return -1;
	}
	else
	{
			if (s1.maSV > s2.maSV) return -1; 
			else if(s1.maSV < s2.maSV) return 1;
	}

	return 0;
}
int cmpName(sinhvien s1,sinhvien s2)
{
	string ten1 = convertName(s1.hoTen);
	string ten2 = convertName(s2.hoTen);
	if (order[2]==0)
	{
			if (ten1 >ten2) return 1;
			else if (ten1 < ten2) return -1;
	}
	else
	{
			if (ten1 >ten2) return -1;
			else if (ten1 < ten2) return 1;
	}

	return 0;
}
int cmpDate(sinhvien s1,sinhvien s2)
{
	string ngay1 = convertDateOfBirth(s1.ngaySinh);
	string ngay2 = convertDateOfBirth(s2.ngaySinh);
	if (order[3]==0)
	{
			if (ngay1 > ngay2) return 1;
			else if (ngay1 < ngay2) return -1;
	}
	else
	{
			if (ngay1 > ngay2) return -1;
			else if (ngay1 < ngay2) return 1;
	}
	return 0;
}
int cmpMark(sinhvien s1,sinhvien s2)
{
	if (order[4]==0)
	{
			if (s1.diem > s2.diem) return 1;
			else if (s1.diem < s2.diem) return -1;
	}
	else
	{
			if (s1.diem < s2.diem) return 1;
			else if (s1.diem > s2.diem) return -1;
	}

	return 0;
}
int compareSinhVien(sinhvien s1, sinhvien s2,char prior[])
{
	int i=0;
	int stt=0;// thu tu thuc hien so sanh
	while (1)
	{
		int temp = int(prior[i]-'0');
		if (temp==stt) 
		{
			if ((*actionPriorOrderSort[i])(s1,s2)==0) stt++;
			else return (*actionPriorOrderSort[i])(s1,s2);
		}
		else i++;
		if (i>=5) i=0;
		if (stt>4) return 0;
	}			
}
void menuSort()
{
	XoaManHinh();
	int size = 4;
	drawMenu(INPUT_X,INPUT_Y,MENU_SORT,size,0);
	int action, arrow =0;
	fflush(stdin);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,12);
	GoTo(40,0);cout<<"***************************";
	GoTo(40,1);cout<<"SAP XEP DANH SACH SINH VIEN";
	GoTo(40,2);cout<<"***************************";
	while ((action = getCode()) != KEY_ESC)
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
				(*actionMenuSort[arrow])();
				
					
		}
		arrow = (arrow + size*10) % size;
		drawMenu(INPUT_X,INPUT_Y,MENU_SORT,size,arrow);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole,12);
		GoTo(40,0);cout<<"***************************";
		GoTo(40,1);cout<<"SAP XEP DANH SACH SINH VIEN";
		GoTo(40,2);cout<<"***************************";
	}	
}
void funtionSort()
{
	int size=5;
	drawMenu(INPUT_X + WIDTH + 2,INPUT_Y ,MENU_TYPE_SORT,size,0);
	int action, arrow =0;
	fflush(stdin);
	while ((action = getCode()) != KEY_ESC)
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
				if (arrow != size-1)
				{
					MENU_SORT[0]=MENU_TYPE_SORT[arrow];
					valFuncSort = arrow;
				}	
				XoaManHinh();
				return;			
		}
		arrow = (arrow + size*10) % size;
		drawMenu(INPUT_X + WIDTH + 2,INPUT_Y ,MENU_TYPE_SORT,size,arrow);
		fflush(stdin);
	}	
}
void keySort()
{
	int size = 6;
	int GAP = 20;
	drawMenu(INPUT_X + WIDTH + 2,INPUT_Y +HEIGHT ,MENU_KEY_SORT,size,0);
	GoTo(INPUT_X + 2*WIDTH +15,INPUT_Y);cout<<"PRIORITY : 0-4";
	GoTo(INPUT_X + 3*WIDTH +10,INPUT_Y);cout<<"ORDER 0/1: A-Z/Z-A";
	drawMenu(INPUT_X + 2*WIDTH +2,INPUT_Y +HEIGHT ,MENU_PRIORITY_SORT,size-1,-1);
	drawMenu(INPUT_X + 3*WIDTH + 2,INPUT_Y +HEIGHT ,MENU_ORDER_SORT,size-1,-1);
	int action, arrow =0;
	fflush(stdin);
	while ((action = getCode()) != KEY_ESC)
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
				if (arrow != size-1)
				{
					valKeySort = arrow;
					//MENU_SORT[1]=MENU_KEY_SORT[arrow];
					showCur();
					GoTo(INPUT_X + 2*WIDTH +19,INPUT_Y+HEIGHT*(arrow+1)+1);cin>>priority[arrow];
					GoTo(INPUT_X + 3*WIDTH +19,INPUT_Y+HEIGHT*(arrow+1)+1);cin>>order[arrow];
					MENU_ORDER_SORT[arrow]= (order[arrow]==0?"0":"1");
					MENU_PRIORITY_SORT[arrow] =priority[arrow] ;
					hideCur();
				}
				else 
				{
						XoaManHinh();	
						return;
				}
			
		}
		arrow = (arrow + size*10) % size;
		drawMenu(INPUT_X + WIDTH + 2,INPUT_Y+HEIGHT ,MENU_KEY_SORT,size,arrow);
		GoTo(INPUT_X + 2*WIDTH +15,INPUT_Y);cout<<"PRIORITY : 0-4";
		GoTo(INPUT_X + 3*WIDTH +10,INPUT_Y);cout<<"ORDER 0/1: A-Z/Z-A";
		drawMenu(INPUT_X + 2*WIDTH +2,INPUT_Y +HEIGHT ,MENU_PRIORITY_SORT,size-1,-1);
		drawMenu(INPUT_X + 3*WIDTH + 2,INPUT_Y +HEIGHT ,MENU_ORDER_SORT,size-1,-1);
		fflush(stdin);
	}

}

void selectionSort(int key)
{
	for (cauTruc *i = dataSinhVien;i->next!=NULL;i=i->next)
	{
		cauTruc *temp = i;
		for (cauTruc *j =i->next;j!=NULL;j=j->next)
			if (compareSinhVien(temp->data,j->data,priority) == 1) temp = j;
		swapStudent(i,temp);
	}
}
void insertionSort(int key)
{
	if (dataSinhVien == NULL) return;
		
	for(cauTruc *i = dataSinhVien; i->next != NULL;)
	{
		//book ok= true;
		cauTruc *temp =i->next; 
		//th1
		if (compareSinhVien(temp->data, i->data,priority) == 1)
		{
			i=i->next;
		}
		else
		{
			for(cauTruc *j = dataSinhVien; j!=i->next; j= j->next)
			{
	
				if (compareSinhVien(temp->data, j->data, priority) != 1)
				{
			
					i->next = i->next->next;
					swapStudent(temp , j);  
	
					temp->next = j->next; //next node moi la next j 
					j->next =temp;		
					// thoat khoi vong chen
					//ok = false;
					break;
				}
			}
			//if (ok) i=i->next;	
		}
		if (i == NULL) break;
	}
}
void quickSort(cauTruc* &head,cauTruc* &tail,int key)
{
		if (head==tail) return;
		cauTruc *tag = tail;
		//List 1
		cauTruc *firstHead = NULL;
		cauTruc *firstTail =NULL;
		//List2
		cauTruc *secondHead = tag;
		cauTruc *secondTail =tag;
		
		for (cauTruc* i=head;i!=tail;i=i->next)
		{
			if (compareSinhVien(tag->data,i->data,priority)==1)
			{
				if (firstTail==NULL)
				{
					firstHead =i;
					firstTail =i;
				}
				else
				{
					firstTail->next =i;
					firstTail=i;
				}
			}
			else 
			{
				secondTail->next = i;
				secondTail=i;
			
			}
		}
		if (firstHead!=NULL) quickSort(firstHead,firstTail,key);
		quickSort(secondHead,secondTail,key);
		
		if (firstHead!=NULL)
		{
			head= firstHead;
			firstTail->next= secondHead;
		}
		else head = secondHead;
		tail= secondTail;
		tail->next =NULL;
}
void runQuickSort(int key)
{
	cauTruc *tail = dataSinhVien;
	while (tail->next!=NULL) tail =tail->next;	
	quickSort(dataSinhVien,tail,key);
}
void bubbleSort(int key)
{
	for (cauTruc *i=dataSinhVien;i->next!=NULL;i=i->next)
	{
		for (cauTruc *j=i->next;j!=NULL;j=j->next)
			if (compareSinhVien(j->data,i->data,priority)!=1)
				swapStudent(j,i);
	}			
}
void sort(int func, int key)
{
	switch (func)
	{
		case 0: {
			selectionSort(key);
			break;
		}
		case 1:{
			insertionSort(key);
			break;
		}
		case 2:{
			runQuickSort(key);
			break;
		}
		case 3:{
			bubbleSort(key);
			break;
		}
	}
}
void runSort()
{
	int ch;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,14);
	if (valKeySort == -1 || valFuncSort == -1)
	{
		GoTo(DX+6,DY+HEIGHT*2+1);cout<<"Please choose key sort & function sort !";
	}
	else {
		readFile();
		sort(valFuncSort,valKeySort);
		writeFileAll(dataSinhVien);
		GoTo(DX+6,DY+HEIGHT*2+1);cout<<"Sorted!";
	}
	ch= getch();
	GoTo(DX+6,DY+HEIGHT*2+1);cout<<"                                                          ";
}
