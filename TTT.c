#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
char v[9];
int n[9],cu[9],a[1][3],ndb[5],cn1=9;		//cd:-Current Data//cdc:-current data complement//cn1:-no.of digits in cdc
int cdc[9]={1,2,3,4,5,6,7,8,9};
int *ptr=&cdc[0];
int cd[9],cn=0,cm,i,r,j;															//cd stores data as: 1,2,3,...,9
int *ptr1=&r;
char move1='A',user='A',VC,VU;														//But every function returns data as: 0,1,2,...,8
typedef struct{
	int weapon;
	int turn,s1;
	char tool;
}move;
move m;
int doubleplay();
int AIval();
void board();
void check();
int random();
void del(int);
int database();
int logic();
void options();
void howto();
int main()
{
	
	int mode,s1;
FILE *fp;
char name[30];

//doubleplay();

//printf("Hell Bitch0%d,1%d,2%");
//printf("\nPlease enter your Name:\n");
//gets(name);
m.turn=3;
m.tool='X';
if(m.tool=='X')				{ VU='X'; VC='O'; }
else if(m.tool=='O')		{ VU='O'; VC='X'; }
/*for (i=0;i<5;i++){

board();
}
//printf("\nPc -> O\t %s -> X\n",name);
*/

//scanf("%c %c %c",&v[0][0],&v[0][1],&v[0][2]);
//printf("\n////////Your Turn/////////\n");
//c=check();
//printf("%d",c);
beginning:

fp=fopen("error.txt","a");
printf("\n\t\tPlease select the mode:\n\t");
printf("\n\t\t\t1. Play with Computer\n\n\t\t\t2. Multiplayer\n\n\t\t\t3. options\n\n\t\t\t4. How to play");
scanf("%d",&mode);

switch(mode){


case(2): { mode=doubleplay(); }
case(1): if(m.turn==2)goto start1; else goto start;
//if(mode==2)  		  if(mode==1)					//else 						goto beginning;
case(3):	options();
case(4):	howto();

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
else {printf("Sorry boss, but space already filled with%c",v[cm]);getch();system("cls");board();goto askval;}
	if(cn>4) {check();if(r!=2) break;} 



cmove:
cm=database();
			//printf("Returned:%d",cm);getch();
			//printf("Returned:%d,v[cm-1]=%d",cm,v[cm-1]);getch();
if((cm!=0) && (v[cm-1]==' ') ) {v[cm-1] = VC;board();cn++;cd[cn-1]=cm;printf("Database:");getch();}
else
 {cm=logic();
		if (v[cm]==' '){v[cm] = VC;board();cn++;cd[cn-1]=cm+1;printf("Logic:");getch();}
		
//randomize:		{cm=random();{if(cm>9||cm<1) goto randomize;}v[cm-1] = VC;board();cn++;cd[cn-1]=cm;}
		else
			{cm=random();
 			if (v[cm-1]==' ')	{ v[cm-1] = VC;board();cn=cn+1;cd[cn-1]=cm;printf("Randomized:");getch(); }	  
			 else				{ printf("\nSorry some errors occured in generating random numbers.\n\n\tPlease reboot the program. ");fwrite( cd,1,9,fp );getch();exit(0); }
 			}
if(cn>4) {check(); if(r!=2) break;} 
}}while(1);
fclose(fp);

if(r==1) printf("Hurrey!! Boss you've won");
else if(r==0) printf("Game have been drawn.\nI must say you play great.");
else if(r==-1) printf("Wow, I won.\nPlease try again");
getch();

fflush(stdin);
printf("\n\n\n\t\t1. Restart\n\t\t2. Doubleplayer\n\t\t3. Main menu\n\t\t4. Exit\n\n\t");
scanf("%d",&i);
if(i==1) { if ( m.turn==1 || ( m.turn==3 && s1==1 )) goto start;else goto start1; }
if(i==2) doubleplay();
if(i==3) {system("cls");goto beginning;}
if(i==4) exit(0);


/*printf("\n\n cn=%d ",cn);
for(i=0;i<9;i++){printf("\n%d",cd[i]);
}
printf("cn=%d",cn);
for(i=0;i<9;i++){printf("cdc[%d]:%d\t",i,cdc[i]);
}*/




start1:
m.s1=1; //Switch to select turn
for(i=0;i<9;i++) { v[i] = ' ';cd[i]=0;cdc[i]=i+1;}
cn=0;cn1=9;r=2;

 if (m.turn==1) 	goto start;
 board(); 			//Apperently no else needed
 goto cmove; 
}





// Two players mode.
int doubleplay()
{cn=0;
if(toupper(m.tool)=='X')			{ VU='X'; VC='O'; }
else { VU='O'; VC='X'; }
restart:
	system("cls");
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
else {printf("Sorry but space already filled");getch();system("cls");board();goto askval1;}

if(cn>4) 	{check();if(r!=2) break;} 

askval2:
printf("player 2 move:");
scanf("%d",&cm);
--cm;cd[cn]=cm+1;
if( v[cm]== ' ') { v[cm] = 'O';board();cn=cn+1; }
else {printf("Sorry but space already filled");getch();system("cls");board();goto askval2;}

if(cn>4) 	{ check();if(r!=2) break; }

}while(1);

if(r==1) printf("\n\n\n\n\n\n\n\t/////////////////////////// ***** Player 1 have won *****\\\\\\\\\\\\\\\\\\\\\\\\\n\n");
else if(r==-1) printf("Player 2 have won.");
else if(r==0) printf("Game have been drawn.");
else printf("Sorry, !!!!ERROR!!!!!!!Occured%d",i);
getch();
printf("\n\n\t\t1. Restart\n\t\t2.Play with Computer\n\t\t3.Exit\n\n\t");
scanf("%d",&i);
if(i==1)goto restart;
else if(i==2) return(1);
else if(i==3) exit(0);
}

void board()
{system("cls");
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

/*int AIval(){
	printf("AI Here:");
for(i=0;i<1;i++){for(j=0;j<9;j++)if(database(i,j)==cd[j]&&cd[j+1]=='\0')return(database(i,j+1));
}
scanf("%d");
return(i);}
*/

// Returns database value for condition of forced submission
int database(){
int data;
int ndb[5]={4,4,2,4,4};
int db1[9][9]={{1,5,9,8},{2,5,8,9},{3,5,7,4},{4,5,6,3},{5,3,7,1},{6,5,4,1},{7,5,3,6},{8,5,2,1},{9,5,1,2}};
int db2[5][9]={{1,2,7,4,5}};

//printf("database Here:\n");for(i=0;i<5;i++){for(j=0;j<4;j++){printf("%d",db1[i][j]);}printf("\n");}
for(i=0;i<9;i++){
r=1;
for(j=0;j<cn;j++){
{
if(m.s1==0) {if( cd[j]==db1[i][j]  ) r=r*1;else r=0;}
else if(m.s1==1) {if( cd[j]==db2[i][j]  ) r=r*1;else r=0;}

}
/*if( j!=cn && db1[i][cn]!='\0' );*/
//printf("j=%d,cn=%d,r=%d,m.s1=%d,db1[i][cn]=%d",j,cn,r,m.s1,db1[i][cn]);
if( (j==cn-1) && (r==1) && m.s1==0) {return(db1[i][cn]);/*else return(logic());Not Working*/}
else if( (j==cn-1) && (r==1) && m.s1==1) return(db2[i][cn]);

//else printf("r equal to zerocn:%d  j:%d  Return:%d  cd[j]:%d",cn,j,db1[i][cn]),cd[j];getch();
}

//return:db[cn] 
//return(data);
}//printf("j=%d,r=%d, m.s1=%d,db2[0][0]=%d ",j,r,m.s1,db2[0][0]);getch();
if( (j==0) && (r==1) && (m.s1==1)) return(db2[0][0]);
return(0);}


// Returns basic Logical value.
int logic()
{char C;
	if(toupper(m.tool)=='X')			{ VU='X'; VC='O'; }
	else 		{ VU='O'; VC='X'; }
	
	

	/*if(v[0]==' '){if( ((v[1]==v[2])&&v[1]!=' ') || ((v[3]==v[6])&&v[3]!=' ') || ((v[4]==v[8])&&v[4]!=' ') ) return(0);}
	if(v[1]==' '){if( ((v[0]==v[2])&&v[0]!=' ') || ((v[4]==v[7])&&v[4]!=' ') ) return(1);}
	if(v[2]==' '){if( ((v[0]==v[1])&&v[0]!=' ') || ((v[5]==v[8])&&v[5]!=' ') || ((v[4]==v[6])&&v[4]!=' ') ) return(2);}
	if(v[3]==' '){if( ((v[0]==v[6])&&v[0]!=' ') || ((v[4]==v[5])&&v[4]!=' ') ) return(3);}
	if(v[4]==' '){if( ((v[0]==v[8])&&v[0]!=' ') || ((v[2]==v[6])&&v[2]!=' ') || ((v[1]==v[7])&&v[1]!=' ') || ((v[3]==v[5])&&v[3]!=' ') ) return(4);}
	if(v[5]==' '){if( ((v[3]==v[4])&&v[3]!=' ') || ((v[2]==v[8])&&v[2]!=' ') ) return(5);}
	if(v[6]==' '){if( ((v[7]==v[8])&&v[7]!=' ') || ((v[3]==v[0])&&v[3]!=' ') || ((v[2]==v[4])&&v[2]!=' ') ) return(6);}
	if(v[7]==' '){if( ((v[6]==v[8])&&v[6]!=' ') || ((v[4]==v[1])&&v[4]!=' ') ) return(7);}
	if(v[8]==' '){if( ((v[2]==v[5])&&v[2]!=' ') || ((v[6]==v[7])&&v[6]!=' ') || ((v[0]==v[4])&&v[0]!=' ') ) return(8);}
	*/
	
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

/*
	if(v[0]==' '){if( ((v[1]==v[2])&& (v[1]==C ))) || ((v[3]==v[6])&& (v[3]==C )) || ((v[4]==v[8])&&(v[4]==C)))  return(0);}
	if(v[1]==' '){if( ((v[0]==v[2])&& (v[0]==C )) || ((v[4]==v[7])&& (v[4]==C )) ) return(1);}
	if(v[2]==' '){if( ((v[0]==v[1])&& (v[0]==C )) || ((v[5]==v[8])&& (v[5]==C )) || ((v[4]==v[6])&&(v[4]==C )) ) ;return(2);}
	if(v[3]==' '){if( ((v[0]==v[6])&& (v[0]==C )) || ((v[4]==v[5])&& (v[4]==C )) ) return(3);}
	if(v[4]==' '){if( ((v[0]==v[8])&& (v[0]==C )) || ((v[2]==v[6])&& (v[2]==C )) || ((v[1]==v[7])&&(v[1]==C )) || ((v[3]==v[5])&&(v[3]==C )) )return(4);}
	if(v[5]==' '){if( ((v[3]==v[4])&& (v[3]==C )) || ((v[2]==v[8])&& (v[2]==C )) ) return(5);}
	if(v[6]==' '){if( ((v[7]==v[8])&& (v[7]==C )) || ((v[3]==v[0])&& (v[3]==C )) || ((v[2]==v[4])&&(v[2]==C )) ) return(6);}
	if(v[7]==' '){if( ((v[6]==v[8])&& (v[6]==C )) || ((v[4]==v[1])&& (v[4]==C )) ) return(7);}
	if(v[8]==' '){if( ((v[2]==v[5])&& (v[2]==C )) || ((v[6]==v[7])&& (v[6]==C )) || ((v[0]==v[4])&& (v[0]==C  ))) return(8);}*/
}

logic2:
		for(i=0;i<2;i++){
		if(i==0) C = VC;
	else C = VU;	
	if ( (v[0]==v[2]) && (v[2]==v[6]) && (v[6]==' ') &&( v[1]==v[3]) && (v[1]==C) ) return(0);
	if ( (v[0]==v[2]) && (v[2]==v[8]) && (v[8]==' ') && (v[1]==v[5]) && (v[1]==C) ) return(2);
	if ( (v[0]==v[6]) && (v[6]==v[8]) && (v[8]==' ') && (v[7]==v[5]) && (v[5]==C) ) return(8);
	if ( (v[2]==v[6]) && (v[6]==v[8]) && (v[8]==' ') && (v[3]==v[7]) && (v[7]==C) ) return(6);

	
	
	
	
//	return(random()); //Random selects unfilled space randomly.
		}}
	
	

// Selects unfilled space randomly.
	int random()
{
int i,n,substract=0;
//int cd[9]= {1,2,5,4,6},j;
//cn=5;

//Compatible for only one value deletation at a time loop is started
loop:
for(i=0;i<cn1;i++){for(j=0;j<cn;j++){					//cdc:-current database complement
//for(i=0;i<9;i++){for(j=0;j<9;j++){					//cdc:-current database complement
//if(cdc[i]==cd[j]) {del(i);cn1=cn1-1;/*printf("cdc[%d]:=%d\tcd[%d]:%d\n",j,cdc[j],j,cd[j]);getch();*/break;}
if(*(ptr+i)==cd[j]) {del(i);cn1=cn1-1;goto loop;/*printf("cdc[%d]:=%d\tcd[%d]:%d\n",j,cdc[j],j,cd[j]);getch();*/}
}}
substract=substract+1;substract;
//for(i=0;i<4;i++){printf("cdc[%d]:%d\n\tcn1:%d",i,cdc[i],cn1);


i=rand()%(cn1);
//printf("cn=%d,i=%d,Returned:%d",cn,i,cdc[i]);

////printf("\nCDC:\t");
////for(n=0;cdc[n]!='\0';n++);
////for(j=0;j<9;j++) printf("%d\t",cdc[j]);getch();


return(cdc[i]);

}

//Input position of number & delete that position
void del(int i)
{
int j,n;
////printf("del:%d",i);getch();
//for(n=0;cdc[n]!='\0';n++);
for(j=i;j<=cn1-1;j++)
*(ptr+j)=*(ptr+j+1);
//cdc[j]=cdc[j+1];//n=n-1;
//*(ptr+j)=*(ptr+j+1);
//printf("n:%d,j:%d",cn1,j);getch();
// cdc[j]=0;
//*(ptr+j)=0;
*(ptr+j)=0;
}
 
void options()
{
int o,o1;
	char tol;
	system("cls");
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
		system("cls");
		printf("Turn:\n\t\t\t1. First\n\t\t\t2. Second\n\t\t\t3. Alternate");
		scanf("%d",&m.turn);
		
	break;
}}}
 
void howto()
{v[0]=1;
system("cls");
board();
printf("\n\nHow to play Tic Tac Toe (Alu Cross):") ;
printf("\n\t1. Players have to play by one move at a time alternatively\n\t");
printf("2. Whoever makes three moves in a row (horizontal/virtical/dioganal) simply wins\n");
printf("\n\n\tFor example:\n\n");


getch();
}
