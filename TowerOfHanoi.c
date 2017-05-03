
#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define disk1 10
#define disk2 20
#define disk3 30
#define disk4 40
#define disk5 50
#define disk6 60
#define start '1'
#define quit '2'
#define easy '1'
#define medium '2'
#define hard '3'
#define extreme '4'
#define back '5'
#define YELLOW 54
#define PALE_YELLOW 62
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define GRAY 56
#define WHITE 63

typedef struct _disk{
	int length;
}DISK;

typedef struct _pole{
	DISK disk;
	struct _pole * next;
}POLE;

//Global variables
POLE *pole1, *pole2, *pole3;

void erase(int, int, int, int);

void initializePoles(int difficulty){
	int i=0, j;
	POLE * ptr = pole1;
	for(i=0; i<=difficulty; i++){
		POLE *temp = (POLE*)malloc(sizeof(POLE));
		temp->next = NULL;
		switch(i){
			case 0:
				temp->disk = (DISK) {disk1};
				break;
			case 1:
				temp->disk = (DISK) {disk2};
				break;
			case 2:
				temp->disk = (DISK) {disk3};
				break;
			case 3:
				temp->disk = (DISK) {disk4};
				break;
			case 4:
				temp->disk = (DISK) {disk5};
				break;
			case 5:
				temp->disk = (DISK) {disk6};
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

header(int x, int y){
	write_text("TOWER OF HANOI!",120,40,WHITE,1); //title

	//menu options
	write_text("1 - Start",40,160,WHITE,0); 
	write_text("2 - Quit",200,160,WHITE,0);
}

header2(int x, int y){
	write_text("Choose Difficulty!",120,40,WHITE,1); //title

	//menu options
	write_text("1 - Easy",20,120,WHITE,0); 
	write_text("2 - Medium",20,140,WHITE,0);
	write_text("3 - Hard",200,120,WHITE,0); 
	write_text("4 - Extreme",200,140,WHITE,0);
	write_text("5 - Back",100,160,WHITE,0);
}

void drawBox(int y, int x, int center){
	int i=0, j=0;
	for(i=center; i>(center-x); i--){
		for(j=y; j<(y+20); j++){
			write_pixel(i, j, YELLOW);
		}
	}
	for(i=center; i<(center+x); i++){
		for(j=y; j<(y+20); j++){
			write_pixel(i, j, YELLOW);
		}
	}
}

int play(int difficulty){
	char keypress = 1;
	pole1 = NULL;
	pole2 = NULL;
	pole3 = NULL;
	int i, count=0, lengthCheck=0, poleNum=0, poleDest=0, flag=1, y=0;
	initializePoles(difficulty);
	POLE *ptr1 = pole1;
	POLE *ptr2 = pole2;
	POLE *ptr3 = pole3;
	POLE *temp;

	while(1){
		flag = 1;
		ptr1 = pole1;
		ptr2 = pole2;
		ptr3 = pole3;
		erase(1,1,120,220);
		drawPole();

		y = 0;
		while(ptr1!=NULL){
			drawBox(y, ptr1->disk.length, 50);
			ptr1 = ptr1->next;
			y+=20;
		}

		y = 0;
		while(ptr2!=NULL){
			drawBox(y, ptr2->disk.length, 160);
			ptr2 = ptr2->next;
			y+=20;
		}

		y = 0;
		while(ptr3!=NULL){
			drawBox(y, ptr3->disk.length, 270);
			ptr3 = ptr3->next;
			y+=20;
		}

		if(count==(difficulty+1)){
			erase(1,1,400,220);
			write_text("YOU WIN!",120,40,WHITE,1);
			return 0;
		}
	
		
		while(1){
			erase(1,121,400,220);
			write_text("Pick a pole from disk no.: ", 20, 140, WHITE, 0);
			keypress = (char)getch();
			erase(1,121,400,220);

			poleNum = (keypress - '0');
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
				erase(1,121,400,220);
				write_text("Invalid pole! ", 20, 140, WHITE, 0);
				erase(1,121,400,220);
				//printf("Invalid pole!\n");
			}

		}
		while(1){
			erase(1,121,400,220);
			write_text("Place disk to pole no.: ", 20, 140, WHITE, 0);
			keypress = (char)getch();
			erase(1,121,400,220);

			poleDest = (keypress - '0');
			//printf("Enter pole number to place disk: ");
			//scanf("%d", &poleDest);
			if(poleNum == poleDest){
				flag = 0;
				break;
			}
			if(poleDest==1){
				if(pole1!=NULL){
					if(pole1->disk.length > lengthCheck) break;
					else{
						erase(1,121,400,220); 
						write_text("Not a valid move! ", 20, 140, WHITE, 0); 
						erase(1,121,400,220);
					}	
						//printf("Not a valid move\n");
					
				}
				else break;
			}else if(poleDest==2){
				if(pole2!=NULL){
					if(pole2->disk.length > lengthCheck) break;
					else{
						erase(1,121,400,220);
						write_text("Not a valid move! ", 20, 140, WHITE, 0);
						erase(1,121,400,220);	
					} 
						//printf("Not a valid move\n");
				}
				else break;
			}
			else if(poleDest==3){
				if(pole3!=NULL){
					if(pole3->disk.length > lengthCheck) break;
					else{
						erase(1,121,400,220);
						write_text("Not a valid move! ", 20, 140, WHITE, 0);
						erase(1,121,400,220);
					}	
					//printf("Not a valid move\n");
				}
				else break;
			}else{
				erase(1,121,400,220);
				write_text("Invalid Pole! ", 20, 140, WHITE, 0);
				erase(1,121,400,220);
				//printf("Invalid pole!\n");
			}
		}
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
	}	
}

drawPole(){
	int i, j, k;
	for(i=40; i<60; i++){
		for(j=0; j<120; j++){
			write_pixel(i,j,GRAY);
		}
	}
	for(i=150; i<170; i++){
		for(j=0; j<120; j++){
			write_pixel(i,j,GRAY);
		}
	}
	for(i=260; i<280; i++){
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

		keypress = (char)getch();
		erase(1,1,400,220);

		if(keypress==start){
			do{
				erase(1,1,400,220);
				header2(8,5);
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
		}else{

		}
	}while(keypress != quit);

	return 0;
}

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle 
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}