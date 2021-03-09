#ifndef _QLSV_H_
#define _QLSV_H_

#endif
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

//============================================= data ===================================================================
const char* FILEIN ="data.json";
int HEIGHT = 3;
int WIDTH = 35;
const int DX = 45;
const int DY = 5;
int INPUT_X = 10;
int INPUT_Y = 5;
const int KEY_ESC = 27;
const int ARROW_UP =72; 
const int ARROW_DOWN = 80; 
const int ARROW_LEFT = 75; 
const int ARROW_RIGHT = 77;
const int KEY_ENTER = 13;

string DANH_SACH_LOP[]={"CNTT1","CNTT2","BDATTT","ANHTTT"};
string DANH_SACH_TEN_LOP[] = {"Cong nghe thong tin 1",
						   "Cong nghe thong tin 2",
						   "Bao dam an toan thong tin",
						   "An ninh he thong thong tin"};
int SIZE_LOP = 4;
string MENU_MAIN[6] ={"Cap nhat ho so",
					  "In thong tin",
					  "Sap xep",
					  "Tim kiem",
					  "Thong ke",
					  "Thoat"};
						
int dayPerMonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
typedef struct sinhvien{
	string  maLop, hoTen, ngaySinh,maSV;
	float diem;
	int gioiTinh;	
};
struct Node{
		sinhvien data;
		struct Node* next;
		struct Node* prev;
};		
struct Node *head=NULL,*tail=NULL;

typedef struct cauTruc{
	sinhvien data;
	cauTruc *next;
};
typedef cauTruc *dataRoot;
dataRoot dataSinhVien;
sinhvien sv;


// ===================================== prototype =====================================================================
int checkUserPass(string user,string pass);
void addUserPass(string user, string pass);
void initData();
void xuatTT(int x,int y,cauTruc *i);
void DisableResizeWindow();
void DisableCtrButton(bool Close, bool Min, bool Max);
void GoTo(SHORT x, SHORT y);
void hideCur();
void showCur();

void draw(int x, int y, int w,int h,string s,int in);
void drawMenu(int x, int y, string data[],int sizeMenu, int chon);
void delMenu(int x,int y, int hx, int hy);
void XoaManHinh();

float convert_to_float(string tmp);
string ftos(float num);
string convertIntToString(int x, int srt);
int checkDate(int day, int month, int year);
string setDate(int day, int month, int year);
float chuanHoaDiem(float diem);

void addSinhVien(sinhvien sv, dataRoot *pSV);
string lowerCase(string s);
string upperCase(string s);
string chuanHoaTen(string name);
string convertName(string name);
string convertDateOfBirth(string date);
int compareSinhVien(sinhvien s1, sinhvien s2,int key);
void swapStudent(cauTruc* &i,cauTruc* &j);

int getCode();




//============================================== functions =================================================================

void initData()
{
	sv.diem = -1;
	sv.gioiTinh = -1;
	sv.hoTen ="None" ;
	sv.maLop = "None" ;
	sv.maSV = "None";
	sv.ngaySinh ="00/00/0000";
	dataSinhVien = NULL;
}
void xuatTT(int x,int y,cauTruc *i)
{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole,14);
				GoTo(x,y-2);cout<<"================PREVIEW================";
				GoTo(x,y-1);cout<<"Thong tin sinh vien co ID "<< i->data.maSV<<" la:";
				GoTo(x,y);  cout<<"1.Ma sinh vien   :"<<i->data.maSV;
				GoTo(x,y+1);cout<<"2.Lop            :"<<i->data.maLop;
				if (i->data.maLop.length()==5) GoTo(x+23,y+1);cout<<" ";
				GoTo(x,y+2);cout<<"3.Ho va ten      :"<<i->data.hoTen<<"       ";
				GoTo(x,y+3);cout<<"4.Ngay sinh      :"<<i->data.ngaySinh;
				GoTo(x,y+4);cout<<"5.Gioi tinh      :"<<(i->data.gioiTinh == 1?"NAM":"NU ");
				GoTo(x,y+5);cout<<"6.Diem TB        :"<<i->data.diem;
				
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void DisableCtrButton(bool Close, bool Min, bool Max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);
    
    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}
void GoTo(SHORT x, SHORT y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = x;
	Position.Y = y;
	SetConsoleCursorPosition(handle,Position);
}
void hideCur()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10; // size of pointer
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(handle,&ConCurInf);
}
void showCur()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10; // size of pointer
	ConCurInf.bVisible = TRUE;
	SetConsoleCursorInfo(handle,&ConCurInf);
}
void draw(int x, int y, int w,int h,string s,int in)
{
	/*  dong ngang : 205
		dong thang dung: 186
		0 BLACK     8 GRAY
		1 BLUE		9 LIGHT BLUE
		2 GREEN		10 LIGHT GREEN
		3 AQUA		11 LIGHT AQUA
		4 RED		12 LIGHT  RED
		5 PURPLE    13 LIGHT PURPLE
		6 YELLOW    14 LIGHT YELLOW
		7 WHITE     15 BRIGHT WHITE
		*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// mau cua khung 
	int color = 10;
	if (in == 1) color=12;
	SetConsoleTextAttribute(hConsole, color);
	
	// ve 4 goc cua khung
	GoTo(x,y); printf("%c",201);
	GoTo(x+w-1,y+h-1);printf("%c",188);
	GoTo(x,y+h-1);printf("%c",200);
	GoTo(x+w-1,y);printf("%c",187);
	
	//ve  2 dong ke ngang
	for(int i= x+1;i<x+w-1;i++)
	{
		GoTo(i,y);printf("%c",205);
		GoTo(i,y+h-1);printf("%c",205);
	}
	// ve 2 dong ke doc
	for (int i=y+1;i<y+h-1;i++)
	{
		GoTo(x,i);printf("%c",186);
		GoTo(x+w-1,i);printf("%c",186);
	}
	int pos = w/2-int(s.length())/2;
	// mau text
	if (in == 1) color = 12;
	else color = 10;
	SetConsoleTextAttribute(hConsole,color);
	GoTo(x+pos,y+h/2);
	cout << s <<"\n";
}

void drawMenu(int x, int y, string data[],int sizeMenu, int chon)
{
	for(int i=0 ; i<sizeMenu ;i++)
	{
		int k= 0;
		if (chon == i) k=1;
		draw(x,y+i*HEIGHT,WIDTH,HEIGHT,data[i],k);
	}
}
void delMenu(int x,int y, int hx, int hy)
{
	//HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i=x;i<= hx;i++)
		for (int j=y;j<=hy;j++)
		{
			GoTo(i,j);printf(" ");
		}
}
void XoaManHinh()
{
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;
  
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  if (!FillConsoleOutputCharacter(hStdOut,(TCHAR) ' ',cellCount,homeCoords,&count)) return;
  if (!FillConsoleOutputAttribute(hStdOut,csbi.wAttributes,cellCount,homeCoords,&count)) return;
}
string floatToString(float num)
{
	ostringstream buff;
	buff <<  fixed << setprecision(2) << num;
	return buff.str();
}
float chuanHoaPoint(float point)
{
	if (point < 0 || point> 10 ) return -1;
	return point;
}
float chuanHoaDiem(float diem)
{
	if (diem < 0 || diem >10)
		return -1;
	return diem;
}
void addSinhVien(sinhvien sv, dataRoot *ctSV)
{
	cauTruc *temp = new cauTruc;
	temp->data = sv;
	temp->next = NULL;
	if ((*ctSV) == NULL) {		
		*ctSV  = temp;
	}
	else {
		cauTruc *i;
		for (i = (*ctSV); i->next != NULL; i = i->next);
		i->next = temp;	
	}
}
string coverIntToString(int x, int srt) // x la so can chuyen  , srt la do dai xau can co
{
	string ans = ""; // khoi tao kq la rong
	while(x)  // tach tuong so ra
	{
		ans = char(x%10+'0') + ans; // chuyen thanh char ep vao ans
		x/=10;
	}
	while(ans.length() < srt) ans = "0" + ans; // neu ma day so chua du srt ky ty thi them so 0 vao dau
	ans = ans.substr(0, srt); // neu thua thi lay dung srt ky tu
	return ans;
}
float convert_to_float(string tmp)
{
	float res = stof(tmp);
	return res;
}
string ftos(float num)
{
	ostringstream buff;
	buff << fixed <<setprecision(2) << num;
	return buff.str();
}
string convertIntToString(int x, int len) //srt do dai xau can co
{
	string temp="";
	while (x)
	{
		temp = char(x%10 +'0') + temp;
		x/=10;
	}
	while (temp.length()<len) temp = '0' + temp;
	temp = temp.substr(0,len);
	return temp;
}
int checkDate(int day, int month, int year)
{
	if (year % 400 == 0|| (year%4 ==0 && year %100 !=0)) dayPerMonth[2]++;
	if (year < 1900|| year > 2020 ) return 0 ;
	if (month < 0 || month > 12) return 0;
	if (day <0 || day > dayPerMonth[month]) return 0;
	return 1;
}
string setDate(int day, int month, int year)
{
	if (checkDate(day,month,year) == 1)
	{
		string ngay = convertIntToString(day,2);
		string thang = convertIntToString(month,2);
		string nam = convertIntToString(year,4);
		return ngay+"/"+thang+"/"+nam;
	}
	else return "";
}	
string lowerCase(string s)
{
	string temp="";
	for (int i= 0;i <s.length();i++)
		temp += (char)tolower(s[i]);
	return temp;
}
string upperCase(string s)
{
	string temp="";
	for (int i= 0;i <s.length();i++)
		temp += (char)toupper(s[i]);
	return temp;
}
string chuanHoaTen(string name)
{
	name = lowerCase(name);
	string res = " ";
	for (int i=0;i<name.length();i++)
	{
		if (res[res.length()-1] != ' ')
			res += (char)tolower(name[i]);
		else
		{
			if (name[i] == ' ') continue;
			res += (char)toupper(name[i]);
		}
	}
	if (res[res.length()-1] == ' ') 
		res.erase(res.length()-1, 1);
	res.erase(0,1);
	return res;
}					  
string convertName(string name)
{
	string res="";
	int i= name.length()-1;
	while (name[i]!=' ')
	{
		res = name[i]+res;
		i--; 
	}
	res = res +' ';
	for (int j= 0;j< i ;j++)
		res = res + name[j];
	return res;
}
string convertDateOfBirth(string date)
{
	int l = date.length();
	string res ="",tmp="";
	for (int i = l-1;i>=0;i--)
	{
		if (date[i]!='/')  tmp = date[i]+tmp;
		else {
			res = res +tmp;
			tmp="";
		}
	}
	res = res+tmp;
	return res;
	 
}


void swapStudent(cauTruc* &i,cauTruc* &j)
{
	sinhvien temp = i->data;
	i->data = j->data;
	j->data = temp;
}
int getCode()
{
	char ch = getch();
	if (ch == 0 || ch == 224) 
       ch = 256 + getch(); 
	return ch;
}
struct Node* NewNode(sinhvien data)
{
	struct Node* newNode = new Node;
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}
void push(sinhvien data)
{
	struct Node* newNode = NewNode(data);
	if (head==NULL)
	{
		head = newNode;
		tail = newNode;
		return;
	}
	tail->next = newNode;
	newNode->prev = tail;
	tail = newNode;
}
void convertToDoubleLinkedList()
{
	for (cauTruc *i=dataSinhVien;i!=NULL;i=i->next)
	{
		push(i->data);
	}
}
dataRoot DelHead(dataRoot head){
    if(head == NULL){
        printf("\nCha co gi de xoa het!");
    }else{
        head = head->next;
    }
    return head;
}
dataRoot DelTail(dataRoot head){
    if (head == NULL || head->next == NULL){
         return DelHead(head);
    }
    dataRoot p = head;
    while(p->next->next != NULL){
        p = p->next;
    }
    p->next = p->next->next;
   
    return head;
}
dataRoot DelAt(dataRoot head, int position){
    if(position == 0 || head == NULL || head->next == NULL){
        head = DelHead(head); 
    }else{
        int k = 1;
        dataRoot p = head;
        while(p->next->next != NULL && k != position){
            p = p->next;
            ++k;
        }
 
        if(k != position){
        }else{
            p->next = p->next->next;
        }
    }
    return head;
}
#define MAX 200

struct Stack
{
	float DATA[MAX];
	int TOP;
};
struct _Stack
{
	int _DATA[MAX];
	int TOP;
};
void init(Stack *S)
{
	S->TOP = -1;
}
void _init(_Stack *S)
{
	S->TOP = -1;
}
int isEmpty(Stack *S)
{
	return S->TOP == -1 ? 1 : 0;
}
int _isEmpty(_Stack *S)
{
	return S->TOP == -1 ? 1 : 0;
}
void Push(struct Stack* S, float item)
{
	if (S->TOP == (MAX - 1))
	{
		printf("\nStack is full");
	}
	else
	{
		++S->TOP;
		S->DATA[S->TOP] = item;
	}
}
void _Push(struct _Stack* S,int item)
{
	if (S->TOP == (MAX - 1))
	{
		printf("\nStack is full");
	}
	else
	{
		++S->TOP;
		S->_DATA[S->TOP] = item;
	}
}
int top(Stack *S)
{
	return (S->DATA[S->TOP]);
}
int _top(_Stack *S)
{
	return (S->_DATA[S->TOP]);
}
float Pop(struct Stack* S)
{
	float ret = -1;
	if (S->TOP == -1)
		printf("\nStack is empty");
	else
	{
		ret = S->DATA[S->TOP];
		--S->TOP;
	}
	return ret;
}
int _Pop(struct _Stack* S)
{
	int ret = -1;
	if (S->TOP == -1)
		printf("\nStack is empty");
	else
	{
		ret = S->_DATA[S->TOP];
		S->TOP=S->TOP-1;
	}
	return ret;
}
int Precedence(char x)
{
	if (x == '(')
		return 0;
	if (x == '|' )
		return 1 ;
	if (x == '&' || x == '~' )
		return 2;
	return 3;
}
void InfixtoPostfix(char infix[], char postfix[])
{
	Stack S;
	char x, token;
	int i = 0, j = 0;    // i - index of infix, j - index of postfix
	init(&S);
	for (i = 0; infix[i] != '\0'; i++)
	{
		token = infix[i];
		if (isalpha(token))
			postfix[j++] = token;
		else
			if (token == '(')
				Push(&S, '(');
			else
				if (token == ')')
					while ((x = Pop(&S)) != '(')
						postfix[j++] = x;
				else
				{
					while (Precedence(token) <= Precedence(top(&S)) && !isEmpty(&S))
					{
						x = Pop(&S);
						postfix[j++] = x;
					}
					Push(&S, token);
				}
	}

	while (!isEmpty(&S))
	{
		x = Pop(&S);
		postfix[j++] = x;
	}

	postfix[j] = '\0';
}
int checkName(string s1,string s2)
{
	s2 = lowerCase(s2);
	const char* str1 = s1.c_str();
	const char* str2 = s2.c_str();
	if (strstr(str2,str1)==NULL) return 0;// ko tim thay
	return 1;
}

