/*  	 char.c   */
/*       by Ted Huntington   */

/*  This program creates characters that */
/*  will be used in interactive graphic adventures  */

#include "graphics.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "process.h"
#include "math.h"
#include "time.h"
#include "fcntl.h"
#include "2020.h"

/*Globals*/
unsigned size;    	/*  size of bit image */
void *brushbuff;	/*  pointer to buffer*/
unsigned csize;    	/*  size of cursor bit image */
void *cbuff;	/*  pointer to cursor buffer*/
int lcolor,lc,oldcolor;	/*  line color */
int pattern;		/*  fill pattern  */
int border;		/*  border color*/
int brush,mcolor;
int p1;			/*  1st point for circle or line*/
int p2;			/*  2nd point for circle or line*/
char upat1[8] =  {0x18, 0x3c,0x7e,0xff,0xff,0x7e,0x3c,0x18};
char upat2[8] =  {0x00, 0xf7,0xf7,0xf7,0x00,0xfe,0xfe,0xfe};
char upat3[8] =  {0xee, 0xee,0xee,0xee,0xe0,0xee,0xee,0x0e};
char PATH[256];
char LPATH[] = {0x5c,'\0'};
char cursor[2] = {0xdb, 0x00};
int x1,y1,x2,y2;        /*point coordinates*/
int lstyle;		/*line style*/
int style,direction,tsize;    /*text descriptions*/
int ex,ex2;			/*exit flags*/
int savd;			/*picture saved?*/
int midx,midy;		/*midpoint for circle*/
int radx,rady;		/*radii for ellipse*/
int skin[8];             /*characters attributes*/
char name[30],name2[30],name3[30];
char names[5][11] = {"Pat","Lee","Chris","Jan","Phil"};
int rep;    /*repeat load file- error*/
int qflg;
int univ,cursx,cursy;

struct action         /*actions*/
   {
   int name;  /*0-color,1-brush,2-lstyle,3-point,*/
	      /*4-line,5-circle,6-rect,7-fill,8-text*/
   int a[5];   /*x1-color-brush,y1-style,x2-rad-direct-tsize,y2-strlen*/
   char str[SLEN];  /*string*/
   };
int cur;   /*current act*/

struct action act[NUMMOVE];
int bcrx[12];  /*beg cursor*/
int mcur[12];  /*max cur index*/
int crx,cry;
int curnum[12],cnt,lnum,fact[12],siz[12];
int bald;		/*bald flag*/

main()
{
int g_driver, g_mode, g_error;

int count;		/*  pause counter */
int locolor;		/*  local color */
int lb;			/*  brush number */
float hypot;
char ch1,ch2;		/*key*/
int ich,ich1,ich2;		/*int-<char*/
char tstr[SLEN];
char tstr2[SLEN];
int lobrush;		/*local brush*/
char nm[256];		/*local name*/
char tfil[256],lfname[256];



/*detect graphics */
detectgraph(&g_driver, &g_mode);
if (g_driver < 0)
   {
   printf("No graphics hardware detected!\n");
   exit(1);
   }
g_mode = VGAMED;    /*   VGAMED  = 640x350 2 page   */
		    /*   VGAHI   = 640x480 1 page   */
		    /*   EGAHI	 = 640x350 2 page   */

/*initialize graphics  */
initgraph(&g_driver, &g_mode, "");
g_error = graphresult();

if (g_error < 0)
   {
   printf("initgraph error: %s.\n", grapherrormsg(g_error));
   exit(1);
   }
if (registerbgifont(gothic_font) <0) exit(1);
if (registerbgifont(triplex_font) <0) exit(1);
if (registerbgifont(small_font) <0) exit(1);
if (registerbgifont(sansserif_font) <0) exit(1);
ex2=0;
cur=0;
brush=0;
x1=y1=100;       /*set current coord*/
lcolor=0;
savd=0;
ex=0;
lnum=0;
for(cnt=0;cnt<12;cnt++) curnum[cnt]=0;
curnum[0]=1;
setactivepage(0);
setvisualpage(1);
setusercharsize(1,1,1,1);
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
setcolor(15);
setfillstyle(SOLID_FILL, 15);
bar(0,0,640,300);   /*white top */
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
load_file("char0.pic");  /*char0.pic*/
lcolor=0;
draw_it();
/*setcolor(15);
setfillstyle(SOLID_FILL, 15);
draw_rex();*/
randomize();		/*activate random number generator*/


rep=0;
qflg=0;
mcur[0]=1; mcur[1]=3; mcur[2]=0; mcur[3]=4; mcur[4]=4; mcur[5]=3;
mcur[6]=2; mcur[7]=1; mcur[8]=1; mcur[9]=5; mcur[10]=1; mcur[11]=5;
siz[0]=36; siz[1]=68; siz[2]=8; siz[3]=36; siz[4]=36; siz[5]=52;
siz[6]=36; siz[7]=36; siz[8]=36; siz[9]=36; siz[10]=52; siz[11]=36;
fact[0]=56;  fact[1]=96; fact[2]=8; fact[3]=64; fact[4]=64; fact[5]=80;
fact[6]=64;  fact[7]=64; fact[8]=64; fact[9]=64; fact[10]=80; fact[11]=64;
bcrx[0]=462; bcrx[1]=230; bcrx[2]=54; bcrx[3]=269; bcrx[4]=269; bcrx[5]=293;
bcrx[6]=253; bcrx[7]=253; bcrx[8]=501; bcrx[9]=285; bcrx[10]=69; bcrx[11]=285;
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
setvisualpage(0);

crx=518; cry=46; curnum[lnum]=1;
/*wbox();
doline0();*/
lnum++;  /*added after taking out 2 lines above*/

crx=422; cry=78; curnum[lnum]=2;
wbox();
doline1();   /*will do rand*/
lnum++; /*name*/
if (univ!=3)
  {
  if (univ!=2)
    doname();
  if (univ==0)
    {
    setactivepage(1);
    load_file("char1.pic");
    setfillstyle(SOLID_FILL, 15);
    bar(0,0,640,300);   /*white top */
    setfillstyle(SOLID_FILL, 0);
    bar(0,301,640,350);   /*black bottom */
    draw_it();
    setfillstyle(SOLID_FILL, 0);
    bar(0,301,640,350);   /*black bottom */
    setvisualpage(1);
 /*   crx=269; cry=62;*/
    for (cnt=0;cnt<9;cnt++)
      {
      curnum[lnum]=skin[lnum-3]; crx=bcrx[lnum]+skin[lnum-3]*fact[lnum];
      cry=62+cnt*32;
      if (cnt>4) cry=cry-32;
      if (cnt==7) cry=cry-8;
      if (cnt==8) cry=cry-16;
      wbox();
      doline();
      }
    }
  }

getcwd(PATH,512);
strcat(PATH,LPATH);

if (univ==2)   /*default character*/
  {
  strcpy(tfil,PATH);
  strcpy(lfname,name);
  lfname[8]=0;
  strcat(tfil,lfname);
  strcpy(nm,tfil);
  strcpy(tfil,PATH);
  strcat(tfil,"DEF");
  save_traits(tfil);	/*save traits for 2020 to load*/
/*  if (bald==1)
    {skin[2]=3;
    bald=0;}*/
  }
else
   if (univ==1)   /*old character*/
      {
      strcpy(tfil,PATH);
      strcpy(lfname,name);
      lfname[8]=0;
      strcat(tfil,lfname);
      strcpy(name2,tfil);
      strcpy(name3,tfil);
      strcat(name3,".PIC");
      load_file(name3);
      load_traits(name2);	/*load traits to save for 2020 to load*/
      strcpy(tfil,PATH);
      strcat(tfil,"DEF");
      save_traits(tfil);	/*save traits for 2020 to load*/
      strcpy(nm,PATH);
      strcat(nm,"DEF.PIC");
      save_file(nm);
      closegraph();
      exit(0);
      }
   else
      if (univ==0)   /*new character*/
	 {
/*	 strcpy(name,"test");*/
	 strcpy(tfil,PATH);
	 strcat(tfil,name);
	 strcpy(name2,tfil);
	 strcat(name2,".PIC");
/*	 strcpy(name2,"test.pic");
	 printf("\nEnter the name for this character:");
	 gets(name);
	 strcpy(tfil,PATH);
	 strcat(tfil,name);
	 strcpy(name2,tfil);
	 strcat(name2,".PIC");
	 printf("\nSkin color: (0-tan 1-brown 2-yellow 3-pink 4-red) ");
	 ch1=getche();
	 skin[0]=ch1-48;
	 if (skin[0]<0 || skin[0]>4) skin[0]=random(5);
	 printf("\nHair color: (0-black 1-brown 2-yellow 3-white 4-red/orange) ");
	 ch1=getche();
	 skin[1]=ch1-48;
	 if(skin[1]<0 || skin[1]>4) skin[1]=random(5);
	 printf("\nHair length: (0-short 1-medium 2-long 3-bald) ");
	 ch1=getche();
	 skin[2]=ch1-48;
	 if(skin[2]<0 || skin[2]>3) skin[2]=random(4);
	 printf("\nEye color: (0-blue 1-green 2-brown) ");
	 ch1=getche();
	 skin[3]=ch1-48;
	 if(skin[3]<0 || skin[3]>2) skin[3]=random(3);
	 printf("\nMoustache? (y)es or (n)o ");
	 ch1=getche();
	 if (ch1!=78 && ch1!=110)
	   skin[4]=1;
	 else
	   skin[4]=0;
	 printf("\nBeard? (y)es or (n)o ");
	 ch1=getche();
	 if (ch1!=78 && ch1!=110)
	   skin[5]=1;
	 else
	   skin[5]=0;
	 printf("\nColor shirt:  0-aqua 1-purple 2-green 3-brown 4-red 5-gray ");
	 ch1=getche();
	 skin[6]=ch1-48;
	 if (skin[6]<0 || skin[6]>5)
	   skin[6]=random(6);
	 printf("\nPants or Dress?  0-dress 1-pants ");
	 ch1=getche();
	 skin[7]=ch1-48;
	 if (skin[7]<0 || skin[7]>1)
	   skin[7]=random(2);
	 printf("\nColor pants/dress:  0-gray 1-blue 2-green 3-pink 4-brown 5-black ");
	 ch1=getche();
	 skin[8]=ch1-48;
	 if (skin[8]<0 || skin[8]>5)
	   skin[8]=random(6); */

	 setactivepage(0);
	 setfillstyle(SOLID_FILL, 15);
	 bar(0,0,640,32);   /*white top */
	 draw_char();
	 strcpy(nm,name2);
	 save_file(nm);
	 strcpy(nm,PATH);
	 strcat(nm,"DEF.PIC");
	 save_file(nm);
	 strcpy(nm,PATH);
	 strcat(nm,"DEF");
	 save_traits(nm);	/*save traits for 2020 to load*/
	 strcpy(nm,PATH);
	 strcat(nm,name);
	 save_traits(nm);	/*save traits for later loading*/
	 closegraph();
	 exit(0);
	 }
      else
	{
	if (univ==3)   /*same character*/
	  {
	  closegraph();
	  exit(0);
	  }
      else ex=0;   /*not valid-stay in loop*/
   }
cur=0;
brush=0;
x1=y1=100;       /*set current coord*/
ex2=0;
lcolor=0;
savd=0;
ex=0;
if (univ==0) setactivepage(0);
else setactivepage(1);
setusercharsize(1,1,1,1);
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
setcolor(15);
setfillstyle(SOLID_FILL, 15);

oldcolor=lcolor;
lcolor=15;
setlinestyle(0,ULIN1,1);
setfillstyle(SOLID_FILL, 15);
bar(0,0,640,32);   /*white top */
lcolor=oldcolor;

draw_char();
if (cur>0) draw_it();
strcpy(tfil,PATH);
strcat(tfil,"DEF.PIC");
save_file(tfil);

closegraph();
exit(0);
}                              /*end main*/

doname()
{
int ex;
char ch,key[2],command[37];

  ex=0;
  setcolor(15);
  setfillstyle(SOLID_FILL,0);
  settextstyle(0,0,2);
  outtextxy(56,112,"Name:");
  cursx=160;  cursy=112;
  draw_cursor();
  strcpy(command,"");
  while (ex!=1)
  {
    ch = getch();
    key[0]=ch;  key[1]=0;
    if (ch == 0)  getch();
    switch (ch)
      {
      case 8:			/*  backspace*/
	if (cursx>175)
	  {
	  setfillstyle(SOLID_FILL,0);
	  bar(cursx-16,cursy,cursx+16,cursy+16);
	  command[strlen(command)-1]=0;
          cursx=cursx-16;
	  draw_cursor();
	  }
	break;
      case 13:			/* '<cr>'  carriage return*/
	strcpy(name,command);	/*save old command*/
	ex=1;
	break;
      default:		/*alpha or other symbol*/
	if (cursx<592)     /*608*/
	  {
	  setcolor(15);
	  setfillstyle(SOLID_FILL,0);
	  settextstyle(0,0,2);
	  bar(cursx,cursy,cursx+16,cursy+16);  /*blackout cursor*/
	  outtextxy(cursx,cursy,key);
	  cursx=cursx+16;
	  strcat(command,key);
	  draw_cursor();
	  }
	break;
      }                            /*end switch*/
   }                           /*end while*/
}

draw_cursor()
{
setcolor(15);
outtextxy(cursx,cursy,cursor);
}


doline0()
{
char ch1,ch2;

ex=0;
while(ex!=1)
 {
 ch1=getch();
 if (ch1==0)
  {
  ch2=getch();                                      /*left*/
  if (ch2==75)  {  if (curnum[lnum]==0)  {bbox(); curnum[lnum]=mcur[lnum];
					crx=crx+mcur[lnum]*fact[lnum];wbox();}
		   else {bbox(); curnum[lnum]--; crx=crx-fact[lnum]; wbox();}}
  else
    {                                             /*right*/
    if (ch2==77)  {if (curnum[lnum]==mcur[lnum]) {bbox(); curnum[lnum]=0;
						crx=bcrx[lnum]; wbox();}
		   else {bbox(); curnum[lnum]++; crx=crx+fact[lnum]; wbox();}}
    }
  }
 else
  {
  if (ch1==13)  { if (curnum[lnum]==0) {system("tapimv2>out.out");
		  system("vmp>out.out");system("audiomat>out.out");}
		   ex=1;lnum++; }
  }
 }
}

doline1()
{
char ch1,ch2;

ex=0;
while(ex!=1)
 {
ch1=getch();
if (ch1==0)
  {
  ch2=getch();                                      /*left*/
  if (ch2==75)  {  if (curnum[lnum]==0)  {bbox(); curnum[lnum]=mcur[lnum];
					crx=crx+mcur[lnum]*fact[lnum];wbox();}
		   else {bbox(); curnum[lnum]--; crx=crx-fact[lnum]; wbox();}}
  else
    {                                             /*right*/
    if (ch2==77)  {if (curnum[lnum]==mcur[lnum]) {bbox(); curnum[lnum]=0;
						crx=bcrx[lnum]; wbox();}
		   else {bbox(); curnum[lnum]++; crx=crx+fact[lnum]; wbox();}}
    }
  }
else
  {
  if (ch1==13)  { ex=1;
		  switch(curnum[lnum])
		  {  case 0: donew(); break;
		     case 1: doold(); break;
		     case 2: doran(); break;
		     case 3: dosam(); break;
		  }
		  lnum++;
		}
  }
 }
}

doline()
{
char ch1,ch2;

ex=0;
while(ex!=1)
 {
ch1=getch();
if (ch1==0)
  {
  ch2=getch();                                      /*left*/
  if (ch2==75)  {  if (curnum[lnum]==0)  {bbox(); curnum[lnum]=mcur[lnum];
					crx=crx+mcur[lnum]*fact[lnum];wbox();}
		   else {bbox(); curnum[lnum]--; crx=crx-fact[lnum]; wbox();}}
  else
    {                                             /*right*/
    if (ch2==77)  {if (curnum[lnum]==mcur[lnum]) {bbox(); curnum[lnum]=0;
						crx=bcrx[lnum]; wbox();}
		   else {bbox(); curnum[lnum]++; crx=crx+fact[lnum]; wbox();}}
    }
  }
else
  {
  if (ch1==13)  { skin[lnum-3]=curnum[lnum]; if (lnum==7||lnum==8||lnum==10)
		  skin[lnum-3]=!curnum[lnum]; lnum++; ex=1;}
  }
 }
}

bbox()
{
setcolor(0);
rectangle(crx,cry,crx+siz[lnum],cry+20);
}

wbox()
{
setcolor(5);
rectangle(crx,cry,crx+siz[lnum],cry+20);
}

donew()
{
randall();
univ=0;
}

doold()
{
univ=1;
}

doran()
{
univ=2;
randall();
strcpy(name,names[random(5)]);
}

dosam()
{
univ=3;
}

draw_cbrush(int lbrush,int col)
{
setfillstyle(SOLID_FILL, 15);      /*clear current brush area*/
bar(CURX-9,CURY,CURX+9,CURY+18);
switch (lbrush)
  {
  case 0:
     putpixel(CURX,CURY,7);    /*brush 0*/
     csize = imagesize(CURX,CURY,CURX,CURY);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX,CURY,cbuff);
     putpixel(CURX,CURY,col);    /*brush 0*/
     size = imagesize(CURX,CURY,CURX,CURY);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX,CURY,brushbuff);
     break;
  }
}

randall()
{
  skin[0]=random(5);
  skin[1]=random(5);
  skin[2]=random(4);
  if (skin[2]==3)
    {
    bald=1;
    skin[2]=0;
    }
  else bald=0;
  skin[3]=random(3);
  skin[4]=random(2);
  skin[5]=random(2);
  skin[6]=random(6);
  skin[7]=random(2);
  skin[8]=random(6);
}


floodwfill(int sx, int sy, int lb, int lc1,int lc2)    /*flood fill shape with white*/
{
mofillxy(sx,sy,lb,lc1,lc2,0,-1,-1);
mofillxy(sx, sy-1, lb, lc1, lc2, 0, -1, 1);
mofillxy(sx, sy, lb, lc1, lc2, 0, 1, -1);
mofillxy(sx, sy+1, lb, lc1, lc2, 0, 1, 1);
}

mofillxy(int sx,int sy,int lb,int lc1,int lc2,int lcf,int xd,int yd)
{
if (getpixel(sx,sy)!=lb && (sx>-1) &&  (sy>-1) && (sx<640) && (sy<301))
  {
  mofillx(sx, sy, lb, lc1, lc2,lcf,xd,yd);
  mofillxy(sx,sy+yd,lb,lc1,lc2,lcf,xd,yd);
  }
}

mofillx(int sx,int sy, int lb, int lc1, int lc2, int lcf, int xd, int yd)
{
int lc3;

if (getpixel(sx,sy)!=lb && (sx>-1) &&  (sy>-1) && (sx<640) && (sy<301))
  {
  if (lcf==1) lc3=lc1;
  else lc3=lc2;
  putpixel(sx,sy,lc3);
  mofillx(sx+xd,sy,lb,lc1,lc2,(lcf==0),xd,yd);
  }
}

mofilly(int sx,int sy, int lb, int lc1, int lc2, int lcf, int xd, int yd)
{
int lc3;

if (getpixel(sx,sy)!=lb && (sx>-1) &&  (sy>-1) && (sx<640) && (sy<301))
  {
  if (lcf==1) lc3=lc1;
  else lc3=lc2;
  putpixel(sx,sy,lc3);
  mofillx(sx,sy+yd,lb,lc1,lc2,(lcf==0),xd,yd);
  }
}

save_file(char lname[30])
{
FILE *fptr;

if ( (fptr=fopen(lname,"wb"))==NULL)
   {printf("Can't open file %s",lname);  getch();}
else
   {
   fwrite(act,sizeof(act[0]),cur,fptr);
   ex=1;
   }
fclose(fptr);
}

save_traits(char lname[30])
{
int outhandle, bytes;
char lnm2[30];
FILE *fptr;

strcpy(lnm2,lname);
strcat(lnm2,".TXT");
if ( (outhandle = open(lnm2,O_CREAT)) < 0)
   {printf("Can't open file %s",lnm2);  getch();}
else
   {
   bytes=11;
   write(outhandle,name,bytes);    /*character name*/
   }
close(outhandle);
strcpy(lnm2,lname);
strcat(lnm2,".TRT");
if ( (fptr=fopen(lnm2,"wb"))==NULL)
   {printf("Can't open file %s",lnm2);  getch();}
else
   fwrite(skin,sizeof(skin[0]),8,fptr);
fclose(fptr);
ex=1;
}

load_file(char lname[11])
{
FILE *fptr;
int a;

a=0;
if ( (fptr=fopen(lname,"rb"))==NULL)
   {printf("Can't open file %s",lname); getch(); }
else
   {
   rep=1;   /*got file*/
   while( fread(&act[a],sizeof(act[a]),1,fptr)==1)
      a++;
   cur=a;
   ex=1;
   }
savd=cur;	/*don't ask for saving each time no work is done*/
fclose(fptr);
}

load_traits(char lname[])
{
#define BUFF1 11
#define BUFF2 8
char buff[BUFF1];
char buffs[BUFF2];
int inhandle;
char lnm2[30];
FILE *fptr;
int a;

a=0;
strcpy(lnm2,lname);
strcat(lnm2,".TXT");
if ( (inhandle=open(lnm2,O_RDONLY))<0)
   {printf("Can't open file %s",lnm2); getch(); }
else
   read(inhandle,name,BUFF1);
close(inhandle);
strcpy(lnm2,lname);
strcat(lnm2,".TRT");
if ( (fptr=fopen(lnm2,"rb"))==NULL)
   {printf("Can't open file %s",lnm2); getch(); }
else
   {
   while( fread(&skin[a],sizeof(skin[a]),1,fptr)==1 && a<8)
      a++;
   }
fclose(fptr);
}

draw_char()	/*draw and save character*/
{
int c,j,k;
int lcolor2,lcolor3,lcolor4,ecolor;
int bald;
j=0;  cur=0;

if (skin[2]==3)  bald=1;
else  bald=0;
for(k=0;k<8;k++)    /*draw all 8 frames of 1 character*/
{
j=k*F;
if (bald==1) skin[2]=3;
switch(skin[1])                      /*hair color*/
   {
   case 0:
      lcolor=0;
      break;
   case 1:
      lcolor=6;      /*brown*/
      break;
   case 2:
      lcolor=14;
      break;
   case 3:
      lcolor=15;
      break;
   case 4:
      lcolor=12;		/*orange*/
      break;
   }      /*end switch*/
   if ((lcolor==6 || lcolor==14)&&(skin[2]!=3))
     {
	act[cur].name=2;
	act[cur].a[0]=4;
	cur++;
	act[cur].name=0;
	act[cur].a[0]=lcolor;       /*brown-6  yellow-14*/
	cur++;
	act[cur].name=4;
	act[cur].a[0]=SCHX+j;
	act[cur].a[1]=SCHY;
	act[cur].a[2]=ECHX+j;
	act[cur].a[3]=SCHY;
	cur++;
	act[cur].name=4;
	act[cur].a[0]=SCHX+j+2;
	act[cur].a[1]=SCHY+1;
	act[cur].a[2]=ECHX+j;
	act[cur].a[3]=SCHY+1;
	cur++;
	if (skin[2]!=0)
	  {
	  if (k!=4 && k!=5)
	    {
	    act[cur].name=4;
	    act[cur].a[0]=ECHX+j-1;
	    act[cur].a[1]=SCHY+2;
	    act[cur].a[2]=ECHX+j-1;
	    act[cur].a[3]=SCHY+skin[2]*HF+1;
	    cur++;
	    act[cur].name=4;
	    act[cur].a[0]=ECHX+j;
	    act[cur].a[1]=SCHY;
	    act[cur].a[2]=ECHX+j;
	    act[cur].a[3]=SCHY+skin[2]*HF+2;
	    cur++;
	    act[cur].name=4;
	    act[cur].a[0]=ECHX+j+1;
	    act[cur].a[1]=SCHY+2;
	    act[cur].a[2]=ECHX+j+1;
	    act[cur].a[3]=SCHY+skin[2]*HF+1;
	    cur++;
	    }
	  if (k==4 || k==5 ||k==6 ||k==7)
	    {
	    act[cur].name=4;                 /*left side hair*/
	    act[cur].a[0]=SCHX+j;
	    act[cur].a[1]=SCHY+2;
	    act[cur].a[2]=SCHX+j;
	    act[cur].a[3]=SCHY+skin[2]*HF+1;
	    cur++;
	    act[cur].name=4;
	    act[cur].a[0]=SCHX+j+1;
	    act[cur].a[1]=SCHY;
	    act[cur].a[2]=SCHX+j+1;
	    act[cur].a[3]=SCHY+skin[2]*HF+2;
	    cur++;
	    act[cur].name=4;
	    act[cur].a[0]=SCHX+j+2;
	    act[cur].a[1]=SCHY+2;
	    act[cur].a[2]=SCHX+j+2;
	    act[cur].a[3]=SCHY+skin[2]*HF+1;
	    cur++;
	    }
	  }
	act[cur].name=2;
	act[cur].a[0]=0;
	cur++;
      }        /* end big if*/
    if ((lcolor==0 || lcolor==15 || lcolor==12)&&(skin[2]!=3))
      {
	act[cur].name=0;
	act[cur].a[0]=lcolor;     /*black or white or orange/red*/
	cur++;
	act[cur].name=10;
	act[cur].a[1]=SCHY;
	act[cur].a[2]=ECHX+j-1;
	act[cur].a[3]=SCHY+1;
	if (k==2 || k==3 || k==6 || k==7)
	  act[cur].a[0]=SCHX+j+2;     /*black*/
	else
	  act[cur].a[0]=SCHX+j+1;     /*black*/
	cur++;
	if (skin[2]!=0)
	   {
	   if (k!=4 && k!=5)               /*hair on right side*/
	     {
	     act[cur].name=10;
	     act[cur].a[1]=SCHY+1;
	     act[cur].a[3]=SCHY+skin[2]*HF;
	     act[cur].a[0]=ECHX+j+2;
	     act[cur].a[2]=ECHX+j-1;
	     cur++;
	     }
	   if (k==2||k==3||k==6||k==7||k==4||k==5)/*left side hair*/
	     {
	     act[cur].name=10;
	     act[cur].a[1]=SCHY+1;
	     act[cur].a[3]=SCHY+skin[2]*HF;
	     act[cur].a[0]=SCHX+j;
	     if (skin[2]!=0)         /*long/medium hair needs 1 more*/
	       act[cur].a[2]=SCHX+j+3;      /*2 or 3*/
	     else
	       act[cur].a[2]=SCHX+j+2;      /*2 or 3*/
	     cur++;
	     }
	   }
      }    /*end 2nd big if*/
   if (skin[1]!=0)               		/*blackout*/
      {
      act[cur].name=0;
      act[cur].a[0]=0;
      cur++;
      act[cur].name=10;
      act[cur].a[0]=SCHX+j-1;
      act[cur].a[1]=SCHY-2;
      act[cur].a[2]=SCHX+j-2;
      act[cur].a[3]=ENDBODY;
      cur++;
      act[cur].name=10;
      act[cur].a[0]=ECHX+j+3;
      act[cur].a[1]=SCHY-2;
      act[cur].a[2]=ECHX+j+4;
      act[cur].a[3]=ENDBODY;
      cur++;
      act[cur].name=10;
      act[cur].a[0]=SCHX+j-1;
      act[cur].a[1]=SCHY-1;
      act[cur].a[2]=ECHX+j+3;
      act[cur].a[3]=SCHY-1;
      cur++;
      act[cur].name=10;
      act[cur].a[0]=SCHX+j;
      act[cur].a[1]=(skin[2]!=3)*skin[2]*HF+3+(skin[2]==0||skin[2]==3)*15;
      act[cur].a[2]=ECHX+j+2;
      act[cur].a[3]=ENDBODY;
      cur++;
      if ((skin[2]==0 ||skin[2]==3)&& (k==0||k==1))
	{
        act[cur].name=10;
	act[cur].a[0]=ECHX+j;
	act[cur].a[1]=SCHY;
	act[cur].a[2]=ECHX+j+2;
	act[cur].a[3]=ENDBODY;
	cur++;
	}
      if ((skin[2]==0||skin[2]==3) && (k==4||k==5))
	{
        act[cur].name=10;
	act[cur].a[0]=SCHX+j;
	act[cur].a[1]=SCHY;
	act[cur].a[2]=SCHX+j;
	act[cur].a[3]=ENDBODY;
	cur++;
	}
      if (k==0||k==1||skin[2]==0||skin[2]==3)
	{
        act[cur].name=10;
	act[cur].a[0]=SCHX+j;
	act[cur].a[1]=SCHY;
	act[cur].a[2]=SCHX+j;
	act[cur].a[3]=NOSEY-1;
	cur++;
        act[cur].name=10;
	act[cur].a[0]=SCHX+j;
	act[cur].a[1]=NOSEY+2;
	act[cur].a[2]=SCHX+j;
	act[cur].a[3]=ENDBODY;
	cur++;
        act[cur].name=10;
	act[cur].a[0]=SCHX+j+1;
	act[cur].a[1]=BSHIRTY-2;
	act[cur].a[2]=SCHX+j+3;
	act[cur].a[3]=ENDBODY;
	cur++;
	}
      if (k==4||k==5||skin[2]==0||skin[2]==3)
	{
        act[cur].name=10;
	act[cur].a[0]=ECHX+j+1;
	act[cur].a[1]=SCHY;
	act[cur].a[2]=ECHX+j+2;
	act[cur].a[3]=NOSEY-1;
	cur++;
        act[cur].name=10;
	act[cur].a[0]=ECHX+j+1;
	act[cur].a[1]=NOSEY+2;
	act[cur].a[2]=ECHX+j+2;
	act[cur].a[3]=ENDBODY;
	cur++;
        act[cur].name=10;
	act[cur].a[0]=ECHX+j-1;
	act[cur].a[1]=BSHIRTY-2;
	act[cur].a[2]=ECHX+j+1;
	act[cur].a[3]=ENDBODY;
	cur++;
	}
      act[cur].name=10;
      act[cur].a[0]=SCHX+j+4;
      act[cur].a[1]=BSHIRTY-2;
      act[cur].a[2]=SCHX+j+5;
      act[cur].a[3]=BSHIRTY-1;
      cur++;
      act[cur].name=10;
      act[cur].a[0]=ECHX+j-4;
      act[cur].a[1]=BSHIRTY-2;
      act[cur].a[2]=ECHX+j-2;
      act[cur].a[3]=BSHIRTY-1;
      cur++;
      }
   switch(skin[0])      	/*draw face,nose, and neck*/
      {
      case 0:
	 lcolor2=12;                  /*orange*/
	 break;
      case 1:
	 lcolor2=6;                          /*brown*/
	 break;
      case 2:
	 lcolor2=14;			/*yellow*/
	 break;
      case 3:
	 lcolor2=13;		/*pink*/
	 break;
      case 4:
	 lcolor2=4; 		/*red*/
	 break;
      }  /*end switch*/
   if (lcolor2==12 || lcolor2==13 || lcolor2==4)    /*shaded faces*/
     {
     act[cur].name=2;
     act[cur].a[0]=4;
     cur++;
     act[cur].name=0;
     act[cur].a[0]=lcolor2;
     cur++;
     if (k==0 || k==1 || k==6 || k==7)
	for(c=2*(skin[2]!=3);c<FCHY-1;c=c+2)       /*face*/
	   {
	   act[cur].name=4;
	   act[cur].a[0]=SCHX+j;
	   act[cur].a[1]=SCHY+c;
	   act[cur].a[2]=ECHX+j-1;
	   act[cur].a[3]=SCHY+c;
	   cur++;
	   act[cur].name=4;
	   act[cur].a[0]=SCHX+j+2;
	   act[cur].a[1]=SCHY+c+1;
	   act[cur].a[2]=ECHX+j-2;
	   act[cur].a[3]=SCHY+c+1;
	   cur++;
	   }
	else
	 for(c=2*(skin[2]!=3);c<FCHY-1;c=c+2)
	   {
	   act[cur].name=4;
	   act[cur].a[0]=SCHX+j;
	   act[cur].a[1]=SCHY+c;
	   act[cur].a[2]=ECHX+j;
	   act[cur].a[3]=SCHY+c;
	   cur++;
	   act[cur].name=4;
	   act[cur].a[0]=SCHX+j+2;
	   act[cur].a[1]=SCHY+c+1;
	   act[cur].a[2]=ECHX+j+1;
	   act[cur].a[3]=SCHY+c+1;
	   cur++;
	   }
	 if(skin[2]==3)skin[2]=0;	/*switch bald to short hair*/
	 if (k!=4 && k!=5)              /*nose*/
	   {
           act[cur].name=4;
	   act[cur].a[0]=SCHX+j-1;
	   act[cur].a[1]=NOSEY;
	   act[cur].a[2]=SCHX+j+1;
	   act[cur].a[3]=NOSEY;
	   cur++;
	   act[cur].name=4;
	   act[cur].a[0]=SCHX+j;
	   act[cur].a[1]=NOSEY+1;
	   act[cur].a[2]=SCHX+j+1;
	   act[cur].a[3]=NOSEY+1;
	   cur++;
	   }
	 if (k==4 || k==5)			/*nose*/
	   {
           act[cur].name=4;
	   act[cur].a[0]=ECHX+j-1;
	   act[cur].a[1]=NOSEY;
	   act[cur].a[2]=ECHX+j+2;
	   act[cur].a[3]=NOSEY;
	   cur++;
	   act[cur].name=4;
	   act[cur].a[0]=ECHX+j;
	   act[cur].a[1]=NOSEY+1;
	   act[cur].a[2]=ECHX+j+2;
	   act[cur].a[3]=NOSEY+1;
	   cur++;
	   }
	 if (skin[2]==0 && (k==6 || k==7))	/*ear*/
	   {
           act[cur].name=4;
	   act[cur].a[0]=ECHX+j-1;
	   act[cur].a[1]=NOSEY;
	   act[cur].a[2]=ECHX+j+1;
	   act[cur].a[3]=NOSEY;
	   cur++;
	   act[cur].name=4;
	   act[cur].a[0]=ECHX+j-2;
	   act[cur].a[1]=NOSEY+1;
	   act[cur].a[2]=ECHX+j;
	   act[cur].a[3]=NOSEY+1;
	   cur++;
	   }
	 act[cur].name=0;
	 act[cur].a[0]=lcolor2;
	 cur++;
	 act[cur].name=10;                      /*neck*/
	 act[cur].a[0]=ECHX+j-6;
	 act[cur].a[1]=FCHY+1;
	 act[cur].a[2]=ECHX+j-4;
	 act[cur].a[3]=FCHY+2;
	 cur++;
	 act[cur].name=2;
	 act[cur].a[0]=0;
	 cur++;
   }   /*end big if*/
   if (lcolor2==6 || lcolor2==14)	/*solid face*/
     {
     act[cur].name=0;
     act[cur].a[0]=lcolor2;
     cur++;
     if (k==2||k==3||k==4 || k==5)
	{
	act[cur].name=10;    	/*face*/
	act[cur].a[0]=SCHX+j+1+1*(skin[2]==1);   /*1 or 2*/
	act[cur].a[1]=SCHY+2*(skin[2]!=3);
	act[cur].a[2]=ECHX+j+1;
	act[cur].a[3]=FCHY;
	cur++;
	}
     else
	{
	act[cur].name=10;    	/*face*/
	act[cur].a[0]=SCHX+j+1;
	act[cur].a[1]=SCHY+2*(skin[2]!=3);
	act[cur].a[2]=ECHX+j-(skin[2]!=0&&skin[2]!=3)*2;
	act[cur].a[3]=FCHY;
	cur++;
	}
     if (skin[2]==3)  skin[2]=0;	/*switch bald and short hair*/
     if (k==0||k==1 || ((k==2||k==3||k==6||k==7)&&(skin[2]==0)))
	{
	act[cur].name=4;		/*nose*/
	act[cur].a[0]=SCHX+j-2;
	act[cur].a[1]=NOSEY;
	act[cur].a[2]=SCHX+j+1;
	act[cur].a[3]=NOSEY;
	cur++;
	act[cur].name=4;		/*nose*/
	act[cur].a[0]=SCHX+j-2;
	act[cur].a[1]=NOSEY+1;
	act[cur].a[2]=SCHX+j+1;
	act[cur].a[3]=NOSEY+1;
	cur++;
	}
     if (skin[2]==0 && (k==6||k==7))
	{
	act[cur].name=10;		/*ear*/
	act[cur].a[0]=ECHX+j-1;
	act[cur].a[1]=NOSEY;
	act[cur].a[2]=ECHX+j+2;
	act[cur].a[3]=NOSEY+1;
	cur++;
	}
     else
	if (k==4||k==5||(skin[2]==0&&(k==2||k==3||k==4||k==5)))
	   {
           act[cur].name=10;		/*ear*/
	   act[cur].a[0]=ECHX+j-1;
	   act[cur].a[1]=NOSEY;
	   act[cur].a[2]=ECHX+j+3;
	   act[cur].a[3]=NOSEY+1;
	   cur++;
	   }
	 act[cur].name=10;		/*neck*/
	 act[cur].a[0]=ECHX+j-6;
	 act[cur].a[1]=FCHY+1;
	 act[cur].a[2]=ECHX+j-4;
	 act[cur].a[3]=FCHY+2;
	 cur++;
     }  /*end 2nd big if*/
   if(k!=2 && k!=3)
   {
   switch(skin[3])		/*eye color*/
      {
      case 0:    	/*blue*/
	 ecolor=9;
	 break;
      case 1:		/*green*/
	 ecolor=11;
	 break;
      case 2:		/*brown or black*/
	 ecolor=0;
	 break;
      }	/*end switch*/
   act[cur].name=0;
   act[cur].a[0]=ecolor;
   cur++;
   if (k==0 || k==1)
     {
     act[cur].name=3;
     act[cur].a[0]=EYEX+j;
     act[cur].a[1]=EYEY;
     cur++;
     }
   if (k==4 || k==5)
     {
     act[cur].name=3;
     act[cur].a[0]=EYEX+j+5;
     act[cur].a[1]=EYEY;
     cur++;
     }
   if (k==6 || k==7)
      {
      act[cur].name=3;
      act[cur].a[0]=EYEX+j;
      act[cur].a[1]=EYEY;
      cur++;
      act[cur].name=3;
      act[cur].a[0]=EYEX+j+5;
      act[cur].a[1]=EYEY;
      cur++;
      }
   act[cur].name=0;
   act[cur].a[0]=0;
   cur++;
   if(k==0 || k==1)
     {
     act[cur].name=4;		/*mouth*/
     act[cur].a[0]=SCHX+j+1;
     act[cur].a[1]=FCHY-4;
     act[cur].a[2]=SCHX+j+3;
     act[cur].a[3]=FCHY-4;
     cur++;
     }
   if(k==4 || k==5)
     {
     act[cur].name=4;		/*mouth*/
     act[cur].a[0]=ECHX+j-2;
     act[cur].a[1]=FCHY-4;
     act[cur].a[2]=ECHX+j;
     act[cur].a[3]=FCHY-4;
     cur++;
     }
   if(k==6 || k==7)
     {
     act[cur].name=4;		/*mouth*/
     act[cur].a[0]=SCHX+j+4;
     act[cur].a[1]=FCHY-4;
     act[cur].a[2]=SCHX+j+7;
     act[cur].a[3]=FCHY-4;
     cur++;
     }
   act[cur].name=0;
   act[cur].a[0]=lcolor;        /*facial features*/
   cur++;
   if (k!=4 && k!=5)
     {
     act[cur].name=4;		/*brow*/
     act[cur].a[0]=SCHX+j+1;
     act[cur].a[1]=SCHY+3;
     act[cur].a[2]=SCHX+j+4;
     act[cur].a[3]=SCHY+3;
     cur++;
     }
   if (k==4 || k==5 || k==6 || k==7)
     {
     act[cur].name=4;		/*brow*/
     act[cur].a[0]=ECHX+j-5;
     act[cur].a[1]=SCHY+3;
     act[cur].a[2]=ECHX+j-2;
     act[cur].a[3]=SCHY+3;
     cur++;
     }
   if (skin[4]==1)
      {
      if(k==0 || k==1)
        {
	act[cur].name=4;		/*moustassche*/
	act[cur].a[0]=SCHX+j+1;
	act[cur].a[1]=FCHY-6;
	act[cur].a[2]=SCHX+j+6;
	act[cur].a[3]=FCHY-6;
	cur++;
	}
      if(k==4 || k==5)
        {
	act[cur].name=4;		/*moustassche*/
	act[cur].a[0]=ECHX+j-5;
	act[cur].a[1]=FCHY-6;
	act[cur].a[2]=ECHX+j;
	act[cur].a[3]=FCHY-6;
	cur++;
	}
      if(k==6 || k==7)
        {
	act[cur].name=4;		/*moustassche*/
	act[cur].a[0]=SCHX+j+3;
	act[cur].a[1]=FCHY-6;
	act[cur].a[2]=SCHX+j+8;
	act[cur].a[3]=FCHY-6;
	cur++;
	}
      }
   if (skin[5]==1)
      {
      if (k==0 || k==1)
	{
	act[cur].name=4;		/*beard*/
	act[cur].a[0]=SCHX+j+7;
	act[cur].a[1]=FCHY-6;
	act[cur].a[2]=SCHX+j+7;
	act[cur].a[3]=FCHY-2;
	cur++;
	act[cur].name=4;		/*beard*/
	act[cur].a[0]=SCHX+j+1;
	act[cur].a[1]=FCHY;
	act[cur].a[2]=SCHX+j+7;
	act[cur].a[3]=FCHY;
	cur++;
	act[cur].name=10;		/*beard*/
	act[cur].a[0]=SCHX+j+1;
	act[cur].a[1]=FCHY-1;
	act[cur].a[2]=SCHX+j+7;
	act[cur].a[3]=FCHY-2;
	cur++;
	}
      if (k==4 || k==5)
	{
	act[cur].name=4;		/*beard*/
	act[cur].a[0]=ECHX+j-6;
	act[cur].a[1]=FCHY-6;
	act[cur].a[2]=ECHX+j-6;
	act[cur].a[3]=FCHY-2;
	cur++;
	act[cur].name=4;		/*beard*/
	act[cur].a[0]=ECHX+j-6;
	act[cur].a[1]=FCHY;
	act[cur].a[2]=ECHX+j;
	act[cur].a[3]=FCHY;
	cur++;
	act[cur].name=10;		/*beard*/
	act[cur].a[0]=ECHX+j-6;
	act[cur].a[1]=FCHY-1;
	act[cur].a[2]=ECHX+j;
	act[cur].a[3]=FCHY-2;
	cur++;
	}
      if (k==6 || k==7)
	{
        act[cur].name=4;		/*beard*/
	act[cur].a[0]=ECHX+j-1;
	act[cur].a[1]=FCHY-6;
	act[cur].a[2]=ECHX+j-1;
	act[cur].a[3]=FCHY-2;
	cur++;
        act[cur].name=4;		/*beard*/
	act[cur].a[0]=SCHX+j+1;
	act[cur].a[1]=FCHY-6;
	act[cur].a[2]=SCHX+j+1;
	act[cur].a[3]=FCHY-2;
	cur++;
        act[cur].name=4;		/*beard*/
	act[cur].a[0]=SCHX+j+1;
	act[cur].a[1]=FCHY;
	act[cur].a[2]=ECHX+j-1;
	act[cur].a[3]=FCHY;
	cur++;
	act[cur].name=10;		/*beard*/
	act[cur].a[0]=SCHX+j+1;
	act[cur].a[1]=FCHY-1;
	act[cur].a[2]=ECHX+j-1;
	act[cur].a[3]=FCHY-2;
	cur++;
	}
      }
   }   /*end if*/
   switch(skin[6])                               /*shirt*/
      {
      case 0:
	lcolor3=3;
	break;
      case 1:
	lcolor3=5;
	break;
      case 2:
	lcolor3=10;
	break;
      case 3:
	lcolor3=6;
	break;
      case 4:
	lcolor3=4;
	break;
      case 5:
	lcolor3=8;
	break;
      }         /*end switch*/
      act[cur].name=0;
      act[cur].a[0]=lcolor3;
      cur++;
      act[cur].name=10;     	/*shirt*/
      act[cur].a[0]=BSHIRTX+j;
      act[cur].a[1]=BSHIRTY;
      act[cur].a[2]=ESHIRTX+j;
      act[cur].a[3]=ESHIRTY;
      cur++;
      if (k==2 || k==3)                 /*back hair -bleah*/
	{
	if (lcolor==6 || lcolor==14)
	  {
          if (skin[2]!=0)
	    {
	    act[cur].name=0;
	    act[cur].a[0]=15;			/*white out*/
	    cur++;
	    act[cur].name=10;
	    act[cur].a[0]=SCHX+j;
	    act[cur].a[1]=SCHY+1;
	    act[cur].a[2]=ECHX+j+2;
	    act[cur].a[3]=SCHY+skin[2]*HF;
	    cur++;
	    act[cur].name=2;
	    act[cur].a[0]=4;
	    cur++;
	    act[cur].name=0;
	    act[cur].a[0]=lcolor;
	    cur++;
	    for(c=1;c<skin[2]*HF;c=c+2)
	      {
	      act[cur].name=4;             /*back hair*/
	      act[cur].a[0]=SCHX+j-2;
	      act[cur].a[1]=SCHY+c;
	      act[cur].a[2]=ECHX+j+1;
	      act[cur].a[3]=SCHY+c;
	      cur++;
              act[cur].name=4;             /*back hair*/
	      act[cur].a[0]=SCHX+j;
	      act[cur].a[1]=SCHY+c+1;
	      act[cur].a[2]=ECHX+j+1;
	      act[cur].a[3]=SCHY+c+1;
	      cur++;
	      }
            act[cur].name=4;             /*back hair*/
	    act[cur].a[0]=SCHX+j-2;
	    act[cur].a[1]=SCHY+c;
	    act[cur].a[2]=ECHX+j+1;
	    act[cur].a[3]=SCHY+c;
	    cur++;
	    act[cur].name=2;
	    act[cur].a[0]=0;
	    cur++;
	    }
	  }
	  else
            if (skin[2]!=0)
	      {
	      act[cur].name=0;
	      act[cur].a[0]=lcolor;
	      cur++;
	      act[cur].name=10;
	      act[cur].a[0]=SCHX+j;
	      act[cur].a[1]=SCHY+1;
	      act[cur].a[2]=ECHX+j+1;
	      act[cur].a[3]=SCHY+skin[2]*HF;
	      cur++;
	      }
      }  /*end if*/
      switch(skin[8])				/*pants*/
      {
      case 0:
	lcolor4=8;
	break;
      case 1:
	lcolor4=1;
	break;
      case 2:
	lcolor4=2;
	break;
      case 3:
	lcolor4=13;
	break;
      case 4:
	lcolor4=6;
	break;
      case 5:
	lcolor4=0;
	break;
      }         /*end switch*/
      act[cur].name=0;
      act[cur].a[0]=lcolor4;
      cur++;
      if (skin[7]==1)    			 /*pants*/
	 {
         act[cur].name=10;
	 act[cur].a[0]=BSHIRTX+j;
	 act[cur].a[1]=ESHIRTY+3;
	 act[cur].a[2]=ESHIRTX+j;
	 act[cur].a[3]=EPANTSY;
	 cur++;
	 act[cur].name=0;               /*black lines*/
	 act[cur].a[0]=0;
	 cur++;
	 act[cur].name=4;
	 act[cur].a[0]=BSHIRTX+j+3;
	 act[cur].a[1]=ESHIRTY+14;
	 act[cur].a[2]=BSHIRTX+j+3;
	 act[cur].a[3]=EPANTSY+2;
	 cur++;
	 }
      else					/*dress*/
	 {
	 act[cur].name=10;
	 act[cur].a[0]=BSHIRTX+j;
	 act[cur].a[1]=ESHIRTY+3;
	 act[cur].a[2]=ESHIRTX+j;
	 act[cur].a[3]=(EPANTSY-ESHIRTY)/2+11;
	 cur++;
         act[cur].name=10;
	 act[cur].a[0]=BSHIRTX+j-1;
	 act[cur].a[1]=ESHIRTY+15;
	 act[cur].a[2]=ESHIRTX+j+1;
	 act[cur].a[3]=(EPANTSY-ESHIRTY)/2+11;
	 cur++;
         act[cur].name=10;
	 act[cur].a[0]=BSHIRTX+j-2;
	 act[cur].a[1]=(EPANTSY-ESHIRTY)/2+12;
	 act[cur].a[2]=ESHIRTX+j+2;
	 act[cur].a[3]=EPANTSY;
	 cur++;
	 act[cur].name=0;
	 act[cur].a[0]=0;
	 cur++;
	 act[cur].name=4;
	 act[cur].a[0]=BSHIRTX+j+3;
	 act[cur].a[1]=EPANTSY+1;
	 act[cur].a[2]=BSHIRTX+j+3;
	 act[cur].a[3]=EPANTSY+2;
	 cur++;
	 }
      act[cur].name=0;
      act[cur].a[0]=8;
      cur++;
      act[cur].name=10;      			/*belt*/
      act[cur].a[0]=BSHIRTX+j;
      act[cur].a[1]=ESHIRTY+1;
      act[cur].a[2]=ESHIRTX+j;
      act[cur].a[3]=ESHIRTY+2;
      cur++;
      act[cur].name=0;
      act[cur].a[0]=lcolor3;		/*arm*/
      cur++;
      if (k==0 || k==1 || k==4 || k==5)
	{
	act[cur].name=10;
	act[cur].a[0]=BSHIRTX+j+2;
	act[cur].a[1]=ESHIRTY+1;
	act[cur].a[2]=ESHIRTX+j-2;
	act[cur].a[3]=ESHIRTY+6;
	cur++;
	}
      else
	{
        act[cur].name=10;
	act[cur].a[0]=BSHIRTX-1+j;
	act[cur].a[1]=(skin[2]!=0)*-15+(skin[2]==0)*BSHIRTY+skin[2]*HF+(skin[2]==1)*2;
	act[cur].a[2]=BSHIRTX+j;
	act[cur].a[3]=ESHIRTY+6;
	cur++;
        act[cur].name=10;
	act[cur].a[0]=ESHIRTX+j;
	act[cur].a[1]=(skin[2]!=0)*-15+(skin[2]==0)*BSHIRTY+skin[2]*HF+(skin[2]==1)*2;
	act[cur].a[2]=ESHIRTX+j+1;
	act[cur].a[3]=ESHIRTY+6;
	cur++;
	}
      act[cur].name=0;
      if (lcolor4==lcolor2||lcolor3==lcolor2) act[cur].a[0]=15;
      else
	act[cur].a[0]=lcolor2;			/*hand*/
      if (lcolor3==15 && act[cur].a[0]==15)  act[cur].a[0]=lcolor2;
      cur++;
      if (k==0 || k==1 || k==4 || k==5)
	{
        act[cur].name=10;
	act[cur].a[0]=BSHIRTX+j+2;
	act[cur].a[1]=ESHIRTY+7;
	act[cur].a[2]=ESHIRTX+j-2;
	act[cur].a[3]=ESHIRTY+10;
	cur++;
	}
      else
	{
        act[cur].name=10;
	act[cur].a[0]=BSHIRTX+j-1;
	act[cur].a[1]=ESHIRTY+7;
	act[cur].a[2]=BSHIRTX+j;
	act[cur].a[3]=ESHIRTY+10;
	cur++;
        act[cur].name=10;
	act[cur].a[0]=ESHIRTX+j;
	act[cur].a[1]=ESHIRTY+7;
	act[cur].a[2]=ESHIRTX+j+1;
	act[cur].a[3]=ESHIRTY+10;
	cur++;
	}
      act[cur].name=0;				/*ankle1*/
      act[cur].a[0]=lcolor2;
      cur++;
      act[cur].name=10;
      act[cur].a[0]=BSHIRTX+j;
      act[cur].a[1]=EPANTSY+1;
      act[cur].a[2]=BSHIRTX+j+2;
      act[cur].a[3]=EPANTSY+4;
      cur++;
      act[cur].name=10;  		/*ankle2*/
      act[cur].a[0]=BSHIRTX+j+4;
      act[cur].a[1]=EPANTSY+1;
      act[cur].a[2]=BSHIRTX+j+6;
      act[cur].a[3]=EPANTSY+4;
      cur++;
      act[cur].name=0;
      act[cur].a[0]=8;
      cur++;
      switch(k)
	{
	case 0:
	  act[cur].name=10;              /*shoe1*/
	  act[cur].a[0]=BSHIRTX+j-4;
	  act[cur].a[1]=EPANTSY+3;
	  act[cur].a[2]=ESHIRTX+j-3;
	  act[cur].a[3]=EPANTSY+4;
	  cur++;
	  act[cur].name=10;              /*shoe2*/
	  act[cur].a[0]=BSHIRTX+j-1;
	  act[cur].a[1]=EPANTSY+5;
	  act[cur].a[2]=ESHIRTX+j;
	  act[cur].a[3]=EPANTSY+6;
	  cur++;
	  break;
	case 1:
	  act[cur].name=10;              /*shoe1*/
	  act[cur].a[0]=BSHIRTX+j-1;
	  act[cur].a[1]=EPANTSY+3;
	  act[cur].a[2]=ESHIRTX+j;
	  act[cur].a[3]=EPANTSY+4;
	  cur++;
	  act[cur].name=10;              /*shoe2*/
	  act[cur].a[0]=BSHIRTX+j-4;
	  act[cur].a[1]=EPANTSY+5;
	  act[cur].a[2]=ESHIRTX+j-3;
	  act[cur].a[3]=EPANTSY+6;
	  cur++;
	  break;
	case 2:
	  act[cur].name=10;              /*shoe1*/
	  act[cur].a[0]=ESHIRTX+j-3;
	  act[cur].a[1]=EPANTSY+5;
	  act[cur].a[2]=ESHIRTX+j+1;
	  act[cur].a[3]=EPANTSY+6;
	  cur++;
	  act[cur].name=10;              /*shoe2*/
	  act[cur].a[0]=ESHIRTX+j-3;
	  act[cur].a[1]=EPANTSY+3;
	  act[cur].a[2]=ESHIRTX+j-7;
	  act[cur].a[3]=EPANTSY+4;
	  cur++;
	  break;
	case 3:
	  act[cur].name=10;              /*shoe1*/
	  act[cur].a[0]=ESHIRTX+j-3;
	  act[cur].a[1]=EPANTSY+3;
	  act[cur].a[2]=ESHIRTX+j+1;
	  act[cur].a[3]=EPANTSY+4;
	  cur++;
	  act[cur].name=10;              /*shoe2*/
	  act[cur].a[0]=ESHIRTX+j-3;
	  act[cur].a[1]=EPANTSY+5;
	  act[cur].a[2]=ESHIRTX+j-7;
	  act[cur].a[3]=EPANTSY+6;
	  cur++;
	  break;
	case 4:
	  act[cur].name=10;              /*shoe1*/
	  act[cur].a[0]=BSHIRTX+j;
	  act[cur].a[1]=EPANTSY+3;
	  act[cur].a[2]=ESHIRTX+j+2;
	  act[cur].a[3]=EPANTSY+4;
	  cur++;
	  act[cur].name=10;              /*shoe2*/
	  act[cur].a[0]=BSHIRTX+j+3;
	  act[cur].a[1]=EPANTSY+5;
	  act[cur].a[2]=ESHIRTX+j+4;
	  act[cur].a[3]=EPANTSY+6;
	  cur++;
	  break;
	case 5:
	  act[cur].name=10;              /*shoe1*/
	  act[cur].a[0]=BSHIRTX+j+3;
	  act[cur].a[1]=EPANTSY+3;
	  act[cur].a[2]=ESHIRTX+j+4;
	  act[cur].a[3]=EPANTSY+4;
	  cur++;
	  act[cur].name=10;              /*shoe2*/
	  act[cur].a[0]=BSHIRTX+j;
	  act[cur].a[1]=EPANTSY+5;
	  act[cur].a[2]=ESHIRTX+j+2;
	  act[cur].a[3]=EPANTSY+6;
	  cur++;
	  break;
	case 6:
	  act[cur].name=10;              /*shoe1*/
	  act[cur].a[0]=ESHIRTX+j-3;
	  act[cur].a[1]=EPANTSY+5;
	  act[cur].a[2]=ESHIRTX+j+1;
	  act[cur].a[3]=EPANTSY+6;
	  cur++;
	  act[cur].name=10;              /*shoe2*/
	  act[cur].a[0]=ESHIRTX+j-3;
	  act[cur].a[1]=EPANTSY+3;
	  act[cur].a[2]=ESHIRTX+j-7;
	  act[cur].a[3]=EPANTSY+4;
	  cur++;
	  break;
	case 7:
	  act[cur].name=10;              /*shoe1*/
	  act[cur].a[0]=ESHIRTX+j-3;
	  act[cur].a[1]=EPANTSY+3;
	  act[cur].a[2]=ESHIRTX+j+1;
	  act[cur].a[3]=EPANTSY+4;
	  cur++;
	  act[cur].name=10;              /*shoe2*/
	  act[cur].a[0]=ESHIRTX+j-3;
	  act[cur].a[1]=EPANTSY+5;
	  act[cur].a[2]=ESHIRTX+j-7;
	  act[cur].a[3]=EPANTSY+6;
	  cur++;
	  break;
	}
      }  /*end for loop*/
}

draw_it()
{
int c,radius,a1,a2,b1,b2;

brush=0;
lcolor=0;
setcolor(lcolor);
setlinestyle(0,ULIN1,1);
draw_cbrush(brush,lcolor);        /*get current color and size brush*/
for (c=0;c<cur;c++)
   {
   switch (act[c].name)
      {
      case 0:
	lcolor=act[c].a[0];
	setcolor(lcolor);
	setfillstyle(1,lcolor);
	draw_cbrush(brush,lcolor);    /*get current color and size brush*/
	break;
      case 1:
	brush=act[c].a[0];
	draw_cbrush(brush,lcolor);    /*get current color and size brush*/
	break;
      case 2:
	lstyle=act[c].a[0];
	setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	break;
      case 3:
	a1=act[c].a[0];
	b1=act[c].a[1];
	putimage(a1,b1,brushbuff,COPY_PUT);
	break;
      case 4:
	setfillstyle(1,lcolor);
	setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	a1=act[c].a[0];
	b1=act[c].a[1];
	a2=act[c].a[2];
	b2=act[c].a[3];
	line(a1,b1,a2,b2);
	break;
      case 5:
        setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	a1=act[c].a[0];
	b1=act[c].a[1];
	radius=act[c].a[2];
	circle(a1,b1,radius);
	break;
      case 6:
        setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	a1=act[c].a[0];
	b1=act[c].a[1];
	a2=act[c].a[2];
	b2=act[c].a[3];
	rectangle(a1,b1,a2,b2);
	break;
      case 7:
	a1=act[c].a[0];
	b1=act[c].a[1];
	border=act[c].a[2];
	pattern=act[c].a[3];
	mcolor=act[c].a[4];
	if (pattern == 12)
	      setfillpattern(upat1,lcolor);
	   else
	      if (pattern == 13)
		 setfillpattern(upat2,lcolor);
	      else
                 if (pattern == 14)
		   setfillpattern(upat3,lcolor);
		 else
		   setfillstyle(pattern,lcolor);
	if (pattern !=15)
	     floodfill(a1,b1,border);
	   else
	     floodwfill(a1,b1,border,lcolor,mcolor);
	break;
      case 8:
	a1=act[c].a[0];
	b1=act[c].a[1];
	style=act[c].a[2];
	direction=act[c].a[3];
	tsize=act[c].a[4];
	settextstyle(style,direction,tsize);
	setusercharsize(tsize+1,1,tsize+1,1);
	outtextxy(a1,b1,act[c].str);
	break;
      case 9:
        setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	a1=act[c].a[0];
	b1=act[c].a[1];
	radx=act[c].a[2];
	rady=act[c].a[3];
	ellipse(a1,b1,SANG,EANG,radx,rady);
	break;
      case 10:
        setfillstyle(1,lcolor);
	a1=act[c].a[0];
	b1=act[c].a[1];
	a2=act[c].a[2];
	b2=act[c].a[3];
	bar(a1,b1,a2,b2);
	break;
      }     	/*end switch*/
   }		/*end for*/
}   /*end draw_it*/
