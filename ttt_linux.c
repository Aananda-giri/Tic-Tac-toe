#include<stdio.h>
//#include<curses.h>
#include<stdlib.h>  //for system("clear");
#include <unistd.h>
#include <termios.h>
#include <ctype.h> //for toupper
char v[9],v1[20];
int va,vb,b;
int n[9],cu[9],a[1][3],ndb[5],cn1=9;		//cd:-Current Data//cdc:-current data complement//cn1:-no.of digits in cdc
int cdc[9]={1,2,3,4,5,6,7,8,9};
int *ptr=&cdc[0];
int cd[9],cn=0,cm,i,r,j;															//cd stores data as: 1,2,3,...,9
int *ptr1=&r;
char VC,VU;	//move1='A',user='A',													//But every function returns data as: 0,1,2,...,8
struct move{
	int weapon;
	int turn,s1;
	char tool;
};
struct move m;
int doubleplay();
int AIval();
void board();
void check();
int random_space();
void del(int);
int database();
int helpdata();							//Database for help menu
void helpdata1(int);
int logic();
void options();
void howto();











// ############################################################
// ################ getch & getche for linux ##################


char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
 }

// ############################################################








int main()
{
	
int mode,s1;
FILE *fp;
char name[30];


m.turn=3;
m.tool='X';
if(m.tool=='X')				{ VU='X'; VC='O'; }
else if(m.tool=='O')		{ VU='O'; VC='X'; }


beginning:
system("clear");
fp=fopen("error.txt","a");
printf("\n\t\tPlease select the mode:\n\t");
printf("\n\t\t\t1. Play with Computer\n\n\t\t\t2. Multiplayer\n\n\t\t\t3. options\n\n\t\t\t4. How to play\t");
scanf("%d",&mode);

switch(mode){


case(2): { mode=doubleplay(); }
case(1): if(m.turn==2)goto start1; else goto start;
case(3):	options();break;
case(4):	howto();break;

}
if(m.turn==2){board();goto start1;}
start:
m.s1=0; //Switch to select turn
printf("\n\nStarts here:");



for(i=0;i<9;i++) { v[i] = ' ';cd[i]=0;cdc[i]=i+1;}
cn=0;cn1=9;

do{
	
board();
askval:
printf("Your move:");
scanf("%d", &cm );
--cm;
if( v[cm]== ' ') { v[cm] = VU;board();cn++;cd[cn-1]=cm+1;/*for(i=0;i<cn;i++){printf("cd[%d]:%d\t",i,cd[i]);}getch(); */}
else {printf("Sorry boss, but space already filled with%c",v[cm]);getch();system("clear");board();goto askval;}
	if(cn>4) {check();if(r!=2) break;} 



cmove:
cm=database();

if((cm!=0) && (v[cm-1]==' ') ) {v[cm-1] = VC;board();cn++;cd[cn-1]=cm;/*printf("Database:");getch();*/}
else
 {cm=logic();
		if (v[cm]==' '){v[cm] = VC;board();cn++;cd[cn-1]=cm+1;/*printf("Logic:");getch();*/}
		
//randomize:
		else
			{cm=random_space();
 			if (v[cm-1]==' ')	{ v[cm-1] = VC;board();cn=cn+1;cd[cn-1]=cm;/*printf("Randomized:");getch();*/ }	  
			 else				{ printf("\nSorry some errors occured in generating random numbers.\n\n\tPlease reboot the program. ");fwrite( cd,1,9,fp );getch();exit(0); }
 			}
if(cn>4) {check(); if(r!=2) break;} 
}}while(1);
fclose(fp);

if(r==1) printf("Hurrey!! you've won");
else if(r==0) printf("Game have been drawn.\nI must say you play great.");
else if(r==-1) printf("Wow, I won.\nPlease try again");
getch();

fflush(stdin);
printf("\n\n\n\t\t1. Restart\n\t\t2. Doubleplayer\n\t\t3. Main menu\n\t\t4. Exit\n\n\t");
scanf("%d",&i);
if(i==1) { if ( m.turn==1 || ( m.turn==3 && s1==1 )) goto start;else goto start1; }
if(i==2) doubleplay();
if(i==3) {system("clear");goto beginning;}
if(i==4) exit(0);



start1:
for(i=0;i<9;i++) { v[i] = ' ';cd[i]=0;cdc[i]=i+1;}
cn=0;cn1=9;r=2;
if ( m.turn==1 || ((m.s1==1)&&(m.turn!=2))) 	{m.s1=0;goto start;}
m.s1=1; //Switch to select turn

 board(); 			
 goto cmove; 
}





// Two players mode.
int doubleplay()
{cn=0;
if(toupper(m.tool)=='X')			{ VU='X'; VC='O'; }
else { VU='O'; VC='X'; }
restart:
	system("clear");
for(i=0;i<9;i++) { v[i] = ' ';cd[i]=0;cdc[i]=i+1;}
cn=0;cn1=9;
r=2;
do{

askval1:
	board();
printf("Player 1 move:");
scanf("%d",&cm);
--cm;cd[cn]=cm+1;
if( v[cm]== ' ') { v[cm] = 'X';board();cn=cn+1; }
else {printf("Sorry but space already filled");getch();system("clear");board();goto askval1;}

if(cn>4) 	{check();if(r!=2) break;} 

askval2:
printf("player 2 move:");
scanf("%d",&cm);
--cm;cd[cn]=cm+1;
if( v[cm]== ' ') { v[cm] = 'O';board();cn=cn+1; }
else {printf("Sorry but space already filled");getch();system("clear");board();goto askval2;}

if(cn>4) 	{ check();if(r!=2) break; }

}while(1);

if(r==1) printf("\n\n\n\n\n\n\n\t/////////////////////////// ***** WOW Player 1 have won *****\\\\\\\\\\\\\\\\\\\\\\\\\n\n");
else if(r==-1) printf("\n\n\n\n\n\n\n\t/////////////////////////// ***** WOW Player 2 have won *****\\\\\\\\\\\\\\\\\\\\\\\\\n\n");
else if(r==0) printf("\n\n\n\n\n\n\n\t/////////////////////////// ***** WOW Game have been drawn *****\\\\\\\\\\\\\\\\\\\\\\\\\n\n");
else printf("Sorry, !!!!ERROR!!!!!!!Occured%d",i);
getch();
printf("\n\n\n\t\t1. Restart\n\t\t2. Play with computer\n\t\t3. Main menu\n\t\t4. Exit\n\n\t");
scanf("%d",&i);
if(i==1) goto restart;
if(i==2) return(1);
if(i==3) {system("clear");main();}
if(i==4) exit(0);

}

void board()
{system("clear");
	printf("\n\n");
	printf("\t\t\t\t\t     |     |      \n");
	printf("\t\t\t\t\t  %c  |  %c  |  %c   \n",v[6],v[7],v[8]);
	printf("\t\t\t\t\t_____|_____|_____\n");
	printf("\t\t\t\t\t     |     |      \n");
	printf("\t\t\t\t\t  %c  |  %c  |  %c   \n",v[3],v[4],v[5]);
	printf("\t\t\t\t\t_____|_____|_____\n");
	printf("\t\t\t\t\t     |     |      \n");
	printf("\t\t\t\t\t  %c  |  %c  |  %c   \n", v[0] , v[1] , v[2] );
	printf("\t\t\t\t\t     |     |      \n\n");
}

//return -1 if AI wins
//return 0 if match draws
//return 1 if human wins
//returns 2 if game is not over


void board1()		//Board Model for Help menu
{
	printf("\n\n");
	printf("\t\t%d.\t     |     |      \t%d.\t     |     |      \n",va,vb);
	printf("\t\t\t  %c  |  %c  |  %c   \t\t  %c  |  %c  |  %c   \n", v1[7] , v1[8] , v1[9] , v1[17] , v1[18] , v1[19] );
	printf("\t\t\t_____|_____|_____\t\t_____|_____|_____\n");
	printf("\t\t\t     |     |      \t\t     |     |      \n");
	printf("\t\t\t  %c  |  %c  |  %c   \t\t  %c  |  %c  |  %c   \n", v1[4] , v1[5] , v1[6] , v1[14] , v1[15] , v1[16] );
	printf("\t\t\t_____|_____|_____\t\t_____|_____|_____\n");
	printf("\t\t\t     |     |      \t\t     |     |      \n");
	printf("\t\t\t  %c  |  %c  |  %c   \t\t  %c  |  %c  |  %c   \n", v1[1] , v1[2] , v1[3] , v1[11] , v1[12] , v1[13] );
	printf("\t\t\t     |     |      \n\n");
}

void check()
{	if(toupper(m.tool)=='X')			{ VU='X'; VC='O'; }
	else 		{ VU='O'; VC='X'; }
 
 	*ptr1=2;
     if( v[0] == v[1] && v[1] == v[2] &&v[0]!=' ' ) { if ( v[0] == VU ) *ptr1=1; else if(v[0] == VC) *ptr1=-1; }
else if( v[3] == v[4] && v[4] == v[5] &&v[3]!=' ' ) { if ( v[3] == VU ) *ptr1=1; else if(v[3] == VC) *ptr1=-1; }
else if( v[6] == v[7] && v[7] == v[8] &&v[6]!=' ' ) { if ( v[6] == VU ) *ptr1=1; else if(v[6] == VC) *ptr1=-1; }
else if( v[0] == v[3] && v[3] == v[6] &&v[0]!=' ' ) { if ( v[0] == VU ) *ptr1=1; else if(v[0] == VC) *ptr1=-1; }
else if( v[1] == v[4] && v[4] == v[7] &&v[1]!=' ' ) { if ( v[1] == VU ) *ptr1=1; else if(v[1] == VC) *ptr1=-1; }
else if( v[2] == v[5] && v[5] == v[8] &&v[2]!=' ' ) { if ( v[2] == VU ) *ptr1=1; else if(v[2] == VC) *ptr1=-1; }
else if( v[0] == v[4] && v[4] == v[8] &&v[0]!=' ' ) { if ( v[0] == VU ) *ptr1=1; else if(v[0] == VC) *ptr1=-1; }
else if( v[2] == v[4] && v[4] == v[6] &&v[2]!=' ' ) { if ( v[2] == VU ) *ptr1=1; else if(v[2] == VC) *ptr1=-1; }
else if( cn>=9 ) *ptr1=0;
}



// Returns database value for condition of forced submission
int database(){
int data;
int ndb[5]={4,4,2,4,4};
int db1[9][9]={{1,5,9,8},{2,5,8,9},{3,5,7,4},{4,5,6,3},{5,3,7,1},{6,5,4,1},{7,5,3,6},{8,5,2,1},{9,5,1,2}};
int db2[8][9]={{1,2,7,4,5},{1,3,7,4,9},{1,4,3,2,5},{1,5,9},{1,6,7,4,5},{1,7,3,2,9},{1,8,7,4,5},{1,9,3,2,7}};


for(i=0;i<9;i++){
r=1;
for(j=0;j<cn;j++){
{
if(m.s1==0) {if( cd[j]==db1[i][j]  ) r=r*1;else r=0;}
else if(m.s1==1) {if( cd[j]==db2[i][j]  ) r=r*1;else r=0;}

}

if( (j==cn-1) && (r==1) && m.s1==0) {return(db1[i][cn]);/*else return(logic());Not Working*/}
else if( (j==cn-1) && (r==1) && m.s1==1) return(db2[i][cn]);


}

//return:db[cn] 
//return(data);
}//printf("j=%d,r=%d, m.s1=%d,db2[0][0]=%d ",j,r,m.s1,db2[0][0]);getch();
if( (j==0) && (r==1) && (m.s1==1)) return(db2[0][0]);
return(0);}


//Database for help menu
int helpdata()
{
int data;
int db1[9][9]={{1,4,3,2,5},{2,5,8,9},{3,5,7,4},{4,5,6,3},{5,3,7,1},{6,5,4,1},{7,5,3,6},{8,5,2,1},{9,5,1,2}};
int db2[8][9]={{1,2,7,4,5},{1,3,7,4,9},{1,4,3,2,5},{1,5,9},{1,6,7,4,5},{1,7,3,2,9},{1,8,7,4,5},{1,9,3,2,7}};


for(i=0;i<9;i++){
r=1;
for(j=0;j<cn;j++){
{
if(b==0) {if( cd[j]==db1[i][j]  ) r=r*1;else r=0;}
else if(b==1) {if( cd[j]==db2[i][j]  ) r=r*1;else r=0;}

}

if( (j==cn-1) && (r==1) ) {return(db1[i][cn]);}
else if( (j==cn-1) && (r==1) ) return(db2[i][cn]);

}

}
if( (j==0) && (r==1) ) return(db2[0][0]);
}


// Returns basic Logical value.
int logic()
{char C;
	if(toupper(m.tool)=='X')			{ VU='X'; VC='O'; }
	else 		{ VU='O'; VC='X'; }
	
	

	
logic1:		for(i=0;i<2;i++){
	if(i==0) C = VC;
	else C = VU;
	
if(v[0]==' ' && (((v[1]==v[2])&& (v[1]==C )) || ((v[3]==v[6])&& (v[3]==C )) || ((v[4]==v[8])&&(v[4]==C))))  return(0);
	else if(v[1]==' ' && ( ((v[0]==v[2])&& (v[0]==C )) || ((v[4]==v[7])&& (v[4]==C ))) ) return(1);
	else if(v[2]==' ' && ( ((v[0]==v[1])&& (v[0]==C )) || ((v[5]==v[8])&& (v[5]==C )) || ((v[4]==v[6])&&(v[4]==C ))) ) return(2);
	else if(v[3]==' ' && ( ((v[0]==v[6])&& (v[0]==C )) || ((v[4]==v[5])&& (v[4]==C ))) ) return(3);
	else if(v[4]==' ' && ( ((v[0]==v[8])&& (v[0]==C )) || ((v[2]==v[6])&& (v[2]==C )) || ((v[1]==v[7])&&(v[1]==C )) || ((v[3]==v[5])&&(v[3]==C ))) )return(4);
	else if(v[5]==' ' && ( ((v[3]==v[4])&& (v[3]==C )) || ((v[2]==v[8])&& (v[2]==C ))) ) return(5);
	else if(v[6]==' ' && ( ((v[7]==v[8])&& (v[7]==C )) || ((v[3]==v[0])&& (v[3]==C )) || ((v[2]==v[4])&&(v[2]==C ))) ) return(6);
	else if(v[7]==' ' && ( ((v[6]==v[8])&& (v[6]==C )) || ((v[4]==v[1])&& (v[4]==C )) )) return(7);
	else if(v[8]==' ' && ( ((v[2]==v[5])&& (v[2]==C ))) || ((v[6]==v[7])&& (v[6]==C )) || ((v[0]==v[4])&& (v[0]==C  ))) return(8);

}

logic2:
		for(i=0;i<2;i++){
		if(i==0) C = VC;
	else C = VU;	
	if ( (v[0]==v[2]) && (v[2]==v[6]) && (v[6]==' ') &&( v[1]==v[3]) && (v[1]==C) ) return(0);
	if ( (v[0]==v[2]) && (v[2]==v[8]) && (v[8]==' ') && (v[1]==v[5]) && (v[1]==C) ) return(2);
	if ( (v[0]==v[6]) && (v[6]==v[8]) && (v[8]==' ') && (v[7]==v[5]) && (v[5]==C) ) return(8);
	if ( (v[2]==v[6]) && (v[6]==v[8]) && (v[8]==' ') && (v[3]==v[7]) && (v[7]==C) ) return(6);

	
	
	
	
//	return(random_space()); //Random selects unfilled space randomly.
		}}
	
	

// Selects unfilled space randomly.
int random_space()
{
int i,n,substract=0;

//Compatible for only one value deletation at a time loop is started
loop:
for(i=0;i<cn1;i++){for(j=0;j<cn;j++){					//cdc:-current database complement
if(*(ptr+i)==cd[j]) {del(i);cn1=cn1-1;goto loop;/*printf("cdc[%d]:=%d\tcd[%d]:%d\n",j,cdc[j],j,cd[j]);getch();*/}
}}
substract=substract+1;substract;



i=rand()%(cn1);

return(cdc[i]);

}

//Input position of number & delete that position
void del(int i)
{
int j,n;

for(j=i;j<=cn1-1;j++)
*(ptr+j)=*(ptr+j+1);

*(ptr+j)=0;
}
 
void options()
{
int o,o1;
	char tol;
	system("clear");
tools:
printf("\n\t\t\t 1. Tools:	\tX/O \n\n\t\t\t 2. Turn: \t(1'st/2'nd/alternate)\t");
scanf("%d",&o);
swtch:
switch(o){
case(1):{
		printf("\n\n\n\t\tPlease select:   'X' OR  'O'  (1/2)");
		scanf("%d",&o1);	
		if(o1==1) 			m.tool='X';
		else if( o1==2)	m.tool='O';
		else printf("Invalid option.");
		break;}
case(2):{
		system("clear");
		printf("Turn:\n\t\t\t1. First\n\t\t\t2. Second\n\t\t\t3. Alternate\t");
		scanf("%d",&m.turn);
		
	break;
}}}
 
void howto()
{int a;

for(i=0;i<9;i++) { v[i] = ' ';cd[i]=0;cdc[i]=i+1;}
cn=0;cn1=9;
char y;
system("clear");
printf("\n   How to play Tic Tac Toe (Alu Cross):\n") ;
printf("\n\t1. Players have to play by one move at a time alternatively\n\n\t");
printf("2. Whoever makes three moves in a row (horizontal/virtical/dioganally) simply wins\n");
printf("\n\tFor example:\n\n");getch();

for(i=0;i<20;i++){v1[i]=' ';}
va=1;vb=2;

v1[7]=v1[8]=v1[9]=v1[13]=v1[16]=v1[19]='X';
v1[4]=v1[5]=v1[11]=v1[15]='O';
board1();
printf("\n\n\t\t\t\tPlayer 'X' Won in cases: 1 & 2.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
getch();
for(i=0;i<20;i++){v1[i]=' ';}
va=3;vb=4;
v1[2]=v1[3]=v1[4]=v1[14]=v1[17]=v1[18]='X';
v1[3]=v1[5]=v1[7]=v1[13]=v1[15]=v1[17]='O';
board1();
printf("\n\n\t\t\t\tPlayer 'O' Won in cases: 3 & 4.\n\n");
printf("\n   Want to learn some tricks:?(y/n)");
y=getch();
here:
if(toupper(y)=='Y')
	{
	printf("\n\n\t1. Winning or Drawing when Playing First \n\t2. Winning or Drawing when Playing Second\t");
	scanf("%d",&i);
	printf("\n\nYou are 'X'");
Cases:	
		switch(i){
			case(1):{
			printf("\n\n\t\t1. always start with a corner.\n\t");getch();
					 printf("\t\tIf opponent makes any move except center victory is yours.\n\n\tFor example:\n");getch();
					 helpdata1(1);getch();helpdata1(2);getch();helpdata1(3);getch();
					printf("\t\tIf opponent makes second move in center,There is still hope \n\n\tFor example:\n");getch();
					helpdata1(4);getch();i=2;goto Cases;
				
				break;}
			case(2):{
					printf("\n\n\t\tIf opponent starts with center always place your move in corner not in middle and play defencively\n\n");
					printf("\t\tIf opponent starts with any corner, always place your move in center \n\n\tFor example:\n.");getch();
					helpdata1(5);
					printf("\t\tIf opponent starts with anywhere  except corners and center, always place your second move in center(try to make XOX positiion) \n\n\tFor example:\n");getch();
					helpdata1(6);getch();i=2;goto Cases;
				break;}
		}}
	
main();
getch();

}

void helpdata1(int n)
{
	for(i=0;i<9;i++)v[i]=' ';
	if(n<=4){ VC='X';VU='O';}
	else { VC='O';VU='X';}
	int i,j;
	int data[6][9]={{1,3,7,4,9},{1,2,7,4,9},{1,6,7,4,9},{1,5,9,7,3},{1,5,9,8,2},{2,5,8,9,1,3}};
	for(i=0;i<6;i++){
		
	if(i%2==0)v[data[n-1][i-1]-1] = VC;
	else v[data[n-1][i-1]-1] = VU;
	board();
	}
}
