//LEIS
//MILESTONE1
#include<stdio.h>
#include<stdlib.h>

#define disk1 5
#define disk2 11
#define disk3 16
#define disk4 21
#define disk5 26
#define disk6 31

typedef struct _disk{
	int length;
}DISK;

typedef struct _pole{
	DISK disk;
	struct _pole * next;
}POLE;

//Global variables
POLE *pole1, *pole2, *pole3;

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

void drawPole(int poleNum){
	int i,j, len=0;
	POLE *ptr;

	switch(poleNum){
		case 1:
			ptr = pole1;
			while(ptr!=NULL){
				len++; ptr = ptr->next;
			}
			break;
		case 2:
			ptr = pole2;
			while(ptr!=NULL){
				len++; ptr = ptr->next;
			}
			break;
		case 3:
			ptr = pole3;
			while(ptr!=NULL){
				len++; ptr = ptr->next;
			}
			break;
	}
	for(i=0; i<(16-(len*2))	; i++){
		if(i==0){
			printf("\t\t\t  -");
		}else{
			printf("\t\t\t | |");
		}
		printf("\n");
	}
}

void drawBox(int length){
	int i=0, j=0, k=0, l;
	for(i=0; i<3; i++){
		switch(length){
			case disk1:
				for(l=0; l<23; l++) printf(" ");
				break;
			case disk2:
				for(l=0; l<20; l++) printf(" ");
				break;
			case disk3:
				for(l=0; l<18; l++) printf(" ");
				break;
			case disk4:
				for(l=0; l<16; l++) printf(" ");
				break;
			case disk5:
				for(l=0; l<13; l++) printf(" ");
				break;
			case disk6:
				for(l=0; l<10; l++) printf(" ");
				break;
		}
		if(i==0 || i==2){
			for(j=0; j<length; j++){
				j==0?printf(" -"):printf("-");
			}
		}else{
			printf("|");
			for(k=0; k<length; k++) printf(" ");
			printf("|");
		}
		printf("\n");
	}
}

int play(int difficulty){
	pole1 = NULL;
	pole2 = NULL;
	pole3 = NULL;
	int i, count=0, lengthCheck=0, poleNum=0, poleDest=0, flag=1;
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

		drawPole(1);
		while(ptr1!=NULL){
			drawBox(ptr1->disk.length);
			ptr1 = ptr1->next;
		}
		printf("\t\t\tPOLE 1\n\n");

		drawPole(2);
		while(ptr2!=NULL){
			drawBox(ptr2->disk.length);
			ptr2 = ptr2->next;
		}
		printf("\t\t\tPOLE 2\n\n");

		drawPole(3);
		while(ptr3!=NULL){
			drawBox(ptr3->disk.length);
			ptr3 = ptr3->next;
		}
		printf("\t\t\tPOLE 3\n\n");

		if(count==(difficulty+1)){
			printf("\n\nYOU WIN \n\n");
			return 0;
		}
	
		while(1){
			printf("Enter pole number to pick disk: ");
			scanf("%d", &poleNum);
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
				printf("Invalid pole!\n");
			}

		}
		while(1){
			printf("Enter pole number to place disk: ");
			scanf("%d", &poleDest);
			if(poleNum == poleDest){
				flag = 0;
				break;
			}
			if(poleDest==1){
				if(pole1!=NULL){
					if(pole1->disk.length > lengthCheck) break;
					else printf("Not a valid move\n");
					
				}
				else break;
			}else if(poleDest==2){
				if(pole2!=NULL){
					if(pole2->disk.length > lengthCheck) break;
					else printf("Not a valid move\n");
				}
				else break;
			}
			else if(poleDest==3){
				if(pole3!=NULL){
					if(pole3->disk.length > lengthCheck) break;
					else printf("Not a valid move\n");
				}
				else break;
			}else{
				printf("Invalid pole!\n");
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

int main(){
	int choice;
	while(1){
		printf("WELCOME TO TOWER OF HANOI\n1. PLAY\n2. EXIT\nEnter choice:");
		scanf("%d", &choice);

		if(choice==1){
			printf("Pick Difficulty\n1. Easy\n2. Medium\n3. Difficult\n4. Extreme\nEnter choice:");
			scanf("%d", &choice);
			switch(choice){
				case 1:
					play(2);
					break;
				case 2:
					play(3);
					break;
				case 3:
					play(4);
					break;
				case 4:
					play(5);
					break;
			}
		}else{
			return 0;
		}
	}
	return 0;
}