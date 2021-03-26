#include "getTT.h"
#include "inDS.h"
#include "sort.h"
#include "updateData.h"
#include "thongKe.h"
#include "search.h"
#include "Untitled1.h"
#include "first_stage.h"
void menuUpdate();
void menuPrint();
void menuSort();
void MenuSearch();
void MenuThongKe();
void (*actionMenu[])() = {  &menuUpdate, 
							&menuPrint, 
							&menuSort, 
							&MenuSearch, 
							&MenuThongKe};
void run()
{
	system("cls");
	hideCur();
	int action, arrow = 0;
	
	int size = 6;

	
	drawMenu(DX, DY, MENU_MAIN, size, arrow);
	
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	GoTo(55, 3); cout <<"QUAN LY SINH VIEN";
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
	  			if (arrow == size-1) return; // thoat 
	  			(*actionMenu[arrow])();
	  		
  		}
		arrow = (arrow + size*10)%size;
		drawMenu(DX, DY, MENU_MAIN, size, arrow);
	
	
		SetConsoleTextAttribute(hConsole, 14);
		GoTo(0,3);
		for(int i= 0; i<= 90; i++) cout << " ";
		GoTo(55, 3); cout <<"QUAN LY SINH VIEN";
		
	}
	
}

int main() {
	resizeConsole(3000,3000);
	logo();
	loadingBar(); 
	readFile();
	run();
	return 0;
}
