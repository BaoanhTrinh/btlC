#ifndef _QLSV_H_
#define _QLSV_H_
#include "lib.h"
#endif

#include <iostream>
#include <future>
#include <thread>
#include <Windows.h>
void logo()
{				
    GoTo(30,3);cout<<"`.-::--`                 .+syyyyyhhhhhhhhhhhhhhhhhhhhhhhhhhdddddddo` .--::-.`" ;              
    GoTo(30,4);cout<<"`::::::::.               /yyyyyyyyhhhhhhhhhhhhhhhhhhhhhhhhhhdddddh: `:::::::::."   ;            
    GoTo(30,4);cout<<"::::::::::-             +yyyyyyyyyhhhhhhhhhhhhhhhhhhhhhhhhhhddddy. .::::::::::::`" ;            
    GoTo(30,5);cout<<".///////////:`          .:::::::::::::::////+hhhhhhhs//////////// `://////////////."  ;         
    GoTo(30,6);cout<<"`//////////////`        --------------`      -hhhhhhh+            .////////:////////:" ;         
    GoTo(30,7);cout<<":++++++:-+++++++.     `/++++++-/++++++/      -hhhhhhh+           -++++++++-  :+++++++/`"  ;       
   	GoTo(30,8);cout<<".ooooooo` -ooooooo-   .+oooooo- .ooooooo-     -hhhhhhh+         `/ooooooo+.    -oooooooo-"   ;     
   	GoTo(30,9);cout<<"+oooooo/   -ooooooo- .ooooooo-   /ooooooo     -hhhhhhh+        .oooooooo+`      .oooooooo/`" ;    
  	GoTo(30,10);cout<<":sssssss`    -sssssss/sssssss-    `sssssss/    -hhhhhhh+       /ssssssss/         `:///////:"  ;   
 	GoTo(30,11);cout<<"`syyyyyy/      -yyyyyyyyyyyys.      /yyyyyyy`   -hhhhhhh+     `oyyyyyyyy- -::::://////////////:"  ;  
 	GoTo(30,12);cout<<"+hhhhhhy`       .yhhhhhhhhhy.       `yhhhhhho   -hhhhhhh+    -yhhhhhhhs. +yyyhhhhhhhhhhhhhhhhhds`";
	GoTo(30,13);cout<<"-hhhhhhh:         .yhhhhhhhy.         /hhhhhhh-  -hhhhhhh+   +hhhhhhhho``syyyyhhhhhhhhhhhhhhhhhddh-";
	GoTo(30,14);cout<<"+sssssso           `+yhhhy/`          `ssssssso  .ooooooo: `oyyyyyyyy/ `ooooooooossssssssssssssssss:";
}
void loadingBar() 
{ 
	// 0 - black background, 
	// A - Green Foreground 
	GoTo(100,20);
	system("color 0A"); 

	// Initialize char for printing 
	// loading bar 
	char a = 177, b = 219; 

	printf("\n\n\n\n"); 
	printf("\n\n\n\n\t\t\t\t\tLoading...\n\n"); 
	printf("\t\t\t\t\t"); 

	// Print initial loading bar 
	for (int i = 0; i < 26; i++) 
		printf("%c", a); 

	// Set the cursor again starting 
	// point of loading bar 
	printf("\r"); 
	printf("\t\t\t\t\t"); 

	// Print loading bar progress 
	for (int i = 0; i < 26; i++) { 
		printf("%c", b); 
		// Sleep for 1 second 
		Sleep(500); 
	} 
} 




