
#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define disk1 8
#define disk2 16
#define disk3 24
#define disk4 32
#define disk5 40
#define disk6 48
#define start '1'
#define help '2'
#define hiscore '3'
#define quit '4'
#define easy '1'
#define medium '2'
#define hard '3'
#define extreme '4'
#define ctrl '1'
#define back '0'
#define YELLOW 54
#define PALE_YELLOW 62
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define GRAY 56
#define WHITE 63
#define PURPLE 15
#define GREEN 50
#define ORANGE 60

//Structure to be used for a single disk
typedef struct _disk{
	int length;
	int color;
}DISK;

//A pole is represented by a linked list
typedef struct _pole{
	DISK disk;
	struct _pole * next;
}POLE;

//Global variables
POLE *pole1, *pole2, *pole3;

void erase(int, int, int, int);
void drawBox(int, int, int, int);
void drawPole();
int play(int);
int write_pixel(int, int, int);
void initializePoles(int);
void header(int, int);
void header2(int, int);

//Initializes the poles depending on the difficulty with a predefined color for a disk
void initializePoles(int difficulty){
	int i=0, j;
	POLE * ptr = pole1;
	for(i=0; i<=difficulty; i++){
		POLE *temp = (POLE*)malloc(sizeof(POLE));
		temp->next = NULL;
		switch(i){
			case 0:
				temp->disk = (DISK) {disk1, YELLOW};
				break;
			case 1:
				temp->disk = (DISK) {disk2, PURPLE};
				break;
			case 2:
				temp->disk = (DISK) {disk3, ROYAL_BLUE};
				break;
			case 3:
				temp->disk = (DISK) {disk4, PALE_YELLOW};
				break;
			case 4:
				temp->disk = (DISK) {disk5, GREEN};
				break;
			case 5:
				temp->disk = (DISK) {disk6, ORANGE};
				break;
		}

		if(pole1==NULL){
			pole1 = temp;
			ptr = pole1;
		}else{
			while(ptr->next!=NULL) ptr = ptr->next;
			ptr->next = temp;
		}
	}		
}

void header(int x, int y){
	write_text("TOWER OF HANOI!",90,40,WHITE,1);
	write_text("1 - Start",100,90,PURPLE,0);
	write_text("2 - Help",100,110,GREEN,0);
	write_text("3 - High Scores",100,130,ORANGE,0);
	write_text("4 - Quit",100,150,ROYAL_BLUE,0);
}

void header2(int x, int y){
	write_text("Choose Difficulty!",80,40,WHITE,1);
	write_text("1 - Easy",20,100,ORANGE,0); 
	write_text("2 - Medium",20,120,PURPLE,0);
	write_text("3 - Hard",200,100,YELLOW,0); 
	write_text("4 - Extreme",200,120,GREEN,0);
	write_text("0 - Back",120,140,PALE_YELLOW,0);
}

void header3(int x, int y){
	write_text("Instructions",100,20,WHITE,1);
	write_text("The goal of the puzzle is to move",10,40,WHITE,0);
	write_text("all the disks from the leftmost",10,50,WHITE,0);
	write_text("pole to the rightmost pole,",10,60,WHITE,0);
	write_text("adhering to the following rules: ",10,70,WHITE,0);
	write_text("1. Move only one disk at a time",10,90,WHITE,0);
	write_text("2. Only the uppermost disk can be",10,110,WHITE,0);
	write_text("moved in a turn",10,120,WHITE,0);
	write_text("3. A larger disk may not be placed",10,140,WHITE,0);
	write_text("on top of a smaller disk",10,150,WHITE,0);
	write_text("0 - Back",10,180,WHITE,0);
	write_text("1 - Controls",180,180,WHITE,0);
}

void controls(int x, int y){
	write_text("Controls",120,20,WHITE,1);
	write_text("1 to 3 - The player must choose a", 10, 40,WHITE,0);
	write_text("pole from where the disk will be", 10, 50,WHITE,0);
	write_text("picked",10,60,WHITE,0);
	write_text("1 to 3 - The player must choose a",10,80,WHITE,0);
	write_text("pole to where the disk will be",10,90,WHITE,0);
	write_text("placed", 10, 100,WHITE,0);
	write_text("0 - Back",10,180,WHITE,0);
}

//Function to be used to draw a  single box
//Starts from a given center up to both sides
void drawBox(int y, int x, int center, int color){
	int i=0, j=0;
	for(i=center; i>(center-x); i--){
		for(j=y; j<(y+20); j++){
			write_pixel(i, j, color);
		}
	}
	for(i=center; i<(center+x); i++){
		for(j=y; j<(y+20); j++){
			write_pixel(i, j, color);
		}
	}
}

int play(int difficulty){
	char keypress = 1;
	char str[5], score[5];
	pole1 = NULL;
	pole2 = NULL;
	pole3 = NULL;
	int i=0, moveCount = 0, count=0, lengthCheck=0, poleNum=0, poleDest=0, flag=1, y=0, paint1=0, paint2=0, paint3=0, inHeight = 0;
	initializePoles(difficulty);
	POLE *ptr1 = pole1;
	POLE *ptr2 = pole2;
	POLE *ptr3 = pole3;
	POLE *temp;
	inHeight = 120;
	write_text("q - quit",10,180,WHITE,0);
	write_text("Moves done: ",100,180,WHITE,0);
	
	while(1){
		flag = 1;
		ptr1 = pole1;
		ptr2 = pole2;
		ptr3 = pole3;
		erase(0,0,330,121);
		drawPole();
		erase(200,180,10,10);
		sprintf(score, "%d", moveCount);
		write_text(score,200,180,WHITE,0);
		write_text("1", 55, 125, WHITE,0);
		write_text("2", 165, 125, WHITE,0);
		write_text("3", 265, 125, WHITE,0);

		paint1 = inHeight;
		paint2 = inHeight;
		paint3 = inHeight;

		//counts for the y position of the disks
		while(ptr1!=NULL){
			paint1-=20;
			ptr1 = ptr1->next;
		}
		while(ptr2!=NULL){
			paint2-=20;
			ptr2 = ptr2->next;
		}
		while(ptr3!=NULL){
			paint3-=20;
			ptr3 = ptr3->next;
		}


		ptr1 = pole1;
		ptr2 = pole2;
		ptr3 = pole3;
		//drawing of the disks per pole
		y = paint1;
		while(ptr1!=NULL){
			drawBox(y, ptr1->disk.length, 55, ptr1->disk.color);
			ptr1 = ptr1->next;
			y+=20;
		}

		y = paint2;
		while(ptr2!=NULL){
			drawBox(y, ptr2->disk.length, 165, ptr2->disk.color);
			ptr2 = ptr2->next;
			y+=20;
		}

		y = paint3;
		while(ptr3!=NULL){
			drawBox(y, ptr3->disk.length, 275, ptr3->disk.color);
			ptr3 = ptr3->next;
			y+=20;
		}

		if(count==(difficulty+1)){
			erase(0,0,400,220);
			write_text("YOU WIN!",120,40,WHITE,1);
			write_text("Press enter to continue...",35,60,WHITE,1);
			for(i=0; i<20; i++){
				drawBox(100, 8, 35, 2);
				drawBox(120, 16, 35, 3);
				drawBox(140, 24, 35, 4);
				drawBox(100, 8, 270, 10);
				drawBox(120, 16, 270, 37);
				drawBox(140, 24, 270, 40);
				drawBox(100, 8, 150, 16);
				drawBox(120, 16, 150, 61);
				drawBox(140, 24, 150, 1);
				drawBox(100, 8, 35, 10);
				drawBox(120, 16, 35, 40);
				drawBox(140, 24, 35, 4);
				drawBox(100, 8, 270, 2);
				drawBox(120, 16, 270, 37);
				drawBox(140, 24, 270, 3);
				drawBox(100, 8, 150, 18);
				drawBox(120, 16, 150, 46);
				drawBox(140, 24, 150, 4);
				drawBox(100, 8, 35, 37);
				drawBox(120, 16, 35, 3);
				drawBox(140, 24, 35, 40);
				drawBox(100, 8, 270, 4);
				drawBox(120, 16, 270, 2);
				drawBox(140, 24, 270, 10);
				drawBox(100, 8, 150, 4);
				drawBox(120, 16, 150, 27);
				drawBox(140, 24, 150, 60);
			}
			(char)getch();
			return 0;
		}
	
		
		while(1){
			erase(0,135,250,30);
			write_text("Pick a pole from disk no: ", 20, 140, WHITE, 0);
			keypress = (char)getch();
			sprintf(str, "%d", keypress-48);
			write_text(str,260,140,WHITE,0);
			write_text(" ",10,190,BLACK,0);
			(char)getch();
			erase(1,135,290,30);

			poleNum = (keypress - '0');
			if(keypress == 'q') return 0;
			if(poleNum==1){
				if(pole1!=NULL){
					lengthCheck = pole1->disk.length;
					break;
				}
				else continue;
			}else if(poleNum==2){
				if(pole2!=NULL){
					lengthCheck = pole2->disk.length;
					break;
				}
				else continue;
			}
			else if(poleNum==3){
				if(pole3!=NULL){
					lengthCheck = pole3->disk.length;
					break;
				}
				else continue;
			}else{
				erase(1,135,250,30);
				write_text("Invalid pole!", 20, 140, WHITE, 0);
				write_text("Press enter to continue...", 20, 148, WHITE, 0);
				(char)getch();
				erase(1,135,290,30);
			}

		}
		while(1){
			erase(1,135,250,30);
			write_text("Place disk to pole no: ", 20, 140, WHITE, 0);
			keypress = (char)getch();
				
			if(keypress == 'q') return 0;	

			sprintf(str, "%d", keypress-48);
			write_text(str,260,140,WHITE,0);
			write_text(" ",10,190,BLACK,0);
			(char)getch();
			erase(1,135,270,30);

			//converts the input char into integer
			poleDest = (keypress - '0');
			if(poleNum == poleDest){
				flag = 0;
				break;
			}
			if(poleDest==1){
				if(pole1!=NULL){
					if(pole1->disk.length > lengthCheck) break;
					else{
						erase(1,135,250,30); 
						write_text("Not a valid move!", 20, 140, WHITE, 0); 
						write_text("Press enter to continue...", 20, 148, WHITE, 0);
						(char)getch();
						erase(1,135,250,30);
					}						
				}
				else break;
			}else if(poleDest==2){
				if(pole2!=NULL){
					if(pole2->disk.length > lengthCheck) break;
					else{
						erase(1,135,280,30);
						write_text("Not a valid move!", 20, 140, WHITE, 0);
						write_text("Press enter to continue...", 20, 148, WHITE, 0);
						(char)getch();
						erase(1,135,250,30);	
					} 
				}
				else break;
			}
			else if(poleDest==3){
				if(pole3!=NULL){
					if(pole3->disk.length > lengthCheck) break;
					else{
						erase(1,135,280,30);
						write_text("Not a valid move!", 20, 140, WHITE, 0);
						write_text("Press enter to continue...", 20, 148, WHITE, 0);
						(char)getch();
						erase(1,135,250,30);
					}	
				}
				else break;
			}else{
				erase(1,135,280,30);
				write_text("Invalid Pole!	", 20, 140, WHITE, 0);
				write_text("Press enter to continue...", 20, 148, WHITE, 0);
				(char)getch();
				erase(1,135,280,30);
			}
		}
		//Moving of disk from one pole to another
		if(flag){
			switch(poleNum){
				case 1:
					temp = pole1;
					pole1 = pole1->next;
					switch(poleDest){
						case 2:
							temp->next = pole2;
							pole2 = temp;
							break;
						case 3:
							temp->next = pole3;
							pole3 = temp;
							break;
					}
					break;
				case 2:
					temp = pole2;
					pole2 = pole2->next;
					switch(poleDest){
						case 1:
							temp->next = pole1;
							pole1 = temp;
							break;
						case 3:
							temp->next = pole3;
							pole3 = temp;
							break;
					}
					break;
				case 3:
					temp = pole3;
					pole3 = pole3->next;
					switch(poleDest){
						case 1:
							temp->next = pole1;
							pole1 = temp;
							break;
						case 2:
							temp->next = pole2;
							pole2 = temp;
							break;
					}
					break;
			}
		}

		ptr3 = pole3; count=0;
		while(ptr3!=NULL){
			count++; ptr3 = ptr3->next;
		}
		moveCount++;
	}	
}

//Draws all the pole at once per call
void drawPole(){
	int i, j, k;
	for(i=50; i<60; i++){
		for(j=0; j<120; j++){
			write_pixel(i,j,GRAY);
		}
	}
	for(i=160; i<170; i++){
		for(j=0; j<120; j++){
			write_pixel(i,j,GRAY);
		}
	}
	for(i=270; i<280; i++){
		for(j=0; j<120; j++){
			write_pixel(i,j,GRAY);
		}
	}
}

int main(){
	int i = 0;
	set_graphics(VGA_320X200X256);
	char keypress = start;
	char keypress2 = easy;

	do{
		erase(1, 1, 400, 220);
		header(8,5);
		drawBox(5, 165, 150, GRAY);
		drawBox(60, 8, 35, 2);
		drawBox(80, 16, 35, 3);
		drawBox(100, 24, 35, 4);
		drawBox(60, 8, 280, 10);
		drawBox(80, 16, 280, 37);
		drawBox(100, 24, 280, 40);
		drawBox(170, 165, 150, GRAY);

		keypress = (char)getch();
		erase(1,1,400,220);

		if(keypress==start){
			do{
				erase(1,1,400,220);
				header2(8,5);
				drawBox(5, 165, 150, GRAY);
				drawBox(170, 165, 150, GRAY);
				keypress2 = (char)getch();
				erase(1,1,400,220);

				switch(keypress2){
					erase(1,1,400,220);
					case easy:
						play(2);
						break;
					case medium:
						play(3);
						break;
					case hard:
						play(4);
						break;
					case extreme:
						play(5);
						break;
					default:
						break;
				}
			}while(keypress2 != back);
		}else if(keypress==help){
			do{
				erase(1,1,400,200);
				header3(8,5);
				keypress2 = (char)getch();
				erase(1,1,400,200);

				if(keypress2==ctrl){
					do{
						erase(1,1,400,200);
						controls(8,5);
						keypress2 = (char)getch();
						erase(1,1,400,200);
					}while(keypress2!=back);
				}
			}while(keypress2!=back);
		}else if(keypress==hiscore){
			do{
				write_text("High Scores",80,20,WHITE,1);
			}while(keypress2!=back);
		}else if(keypress == quit){
			set_graphics(VGA_TEXT80X25X16);
			clrscr();
			exit(1);
		}
	}while(keypress != quit);

	return 0;
}

//Draws a black rectangle to cover a portion of the board
void erase(int x, int y, int w, int h){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}