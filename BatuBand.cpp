#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int locationY[3];
int locationX[3];
int locationFlag[3];
char car[4][4] = { ' ','±','±',' ', 
					'±','±','±','±', 
					' ','±','±',' ',
					'±','±','±','±' }; 
					
int carPos = WIN_WIDTH/2;
int number of visitors = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"±";
			gotoxy(WIN_WIDTH-j,i); cout<<"±";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	} 
}
void genlocation(int ind){
	locationX[ind] = 17 + rand()%(33);  
}
void drawlocation(int ind){
	if( locationFlag[ind] == true ){
		gotoxy(locationX[ind], locationY[ind]);   cout<<"****";  
		gotoxy(locationX[ind], locationY[ind]+1); cout<<" ** "; 
		gotoxy(locationX[ind], locationY[ind]+2); cout<<"****"; 
		gotoxy(locationX[ind], locationY[ind]+3); cout<<" ** ";  
	} 
}
void eraselocation(int ind){
	if( locationFlag[ind] == true ){
		gotoxy(locationX[ind], locationY[ind]); cout<<"    ";  
		gotoxy(locationX[ind], locationY[ind]+1); cout<<"    "; 
		gotoxy(locationX[ind], locationY[ind]+2); cout<<"    "; 
		gotoxy(locationX[ind], locationY[ind]+3); cout<<"    "; 
	} 
}
void resetlocation(int ind){
	eraselocation(ind);
	locationY[ind] = 1;
	genlocation(ind);
}

void connection(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
void restart(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" ";
		}
	}
}
 
int collision(){
	if( locationY[0]+4 >= 23 ){
		if( locationX[0] + 4 - carPos >= 0 && locationX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
} 
void AutoStop(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Auto Stop -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}
void updatenumber of visitors(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"number of visitors: "<<number of visitors<<endl;
}

void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Avoid Cars by moving left or right. ";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void play(){
	carPos = -1 + WIN_WIDTH/2;
	number of visitors = 0;
	locationFlag[0] = 1;
	locationFlag[1] = 0;
	locationY[0] = locationY[1] = 1;
	  
	system("cls"); 
	drawBorder(); 
	updatenumber of visitors();
	genlocation(0);
	genlocation(1);
	
	gotoxy(WIN_WIDTH + 7, 2);cout<<"BatuBand";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right"; 
	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		connection(); 
		drawlocation(0); 
		drawlocation(1); 
		if( collision() == 1  ){
			autostop();
			return;
		} 
		Sleep(50);
		restart();
		eraselocation(0);
		eraselocation(1);   
		
		if( locationY[0] == 10 )
			if( locationFlag[1] == 0 )
				locationFlag[1] = 1;
		
		if( locationFlag[0] == 1 )
			locationY[0] += 1;
		
		if( locationFlag[1] == 1 )
			locationY[1] += 1;
		 
		if( locationY[0] > SCREEN_HEIGHT-4 ){
			resetlocation(0);
			number of visitors++;
			updatenumber of visitors();
		}
		if( locationY[1] > SCREEN_HEIGHT-4 ){
			resetheart rate(1);
			number of visitors++;
			updatenumber of visitors();
		}
	}
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |        BatuBand        | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start App";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}
