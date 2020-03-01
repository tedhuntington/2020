/*  2020.c   */
/*       by Ted Huntington   */
/*  This program runs the interactive graphic adventure.... */
/*  			2 0 2 0   !!!			    */

#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "process.h"
#include "math.h"
#include "time.h"
#include "alloc.h"
#include "string.h"
#include "graphics.h"
#include "fcntl.h"
#include "dos.h"
#include "ctype.h"
#include "2020.h"

/*structures*/
struct action         /*actions*/
   {
   int name;  /*0-color,1-brush,2-lstyle,3-point,*/
	      /*4-line,5-circle,6-rect,7-fill,8-text*/
   int a[5];   /*x1-color-brush,y1-style,x2-rad-direct-tsize,y2-strlen*/
   char str[SLEN];  /*string*/
   };
struct daction         /*dynamic actions*/
   {
   int name;
   int a[5];
   char str[SLEN];
   struct daction *next;
   };
struct daction *act1,*act2;   /*pic draw actions-begin link, temp link*/
struct daction *act3;   /*temp2 link*/
int cur,chrcur;   /*current act*/

struct doors		/*door structs*/
  {
  int a[4];	/*x1,y1,x2,y2*/
  int vis;	/*0-yes, 1-no*/
  int next;	/*next room*/
  };
struct doors door[NUMDOR];
struct objects
  {
  char name[LENOBJ];
  int p[4];
  int loc;
  };
struct objects obj[NUMOBJ];
struct objects mobj[NUMMOBJ];
struct date today;
struct time utime,mtime,dtime;
struct words
  {
  char nm[15];   /*15*/
  };
struct words cword[80];
struct words word[] = {"quit","look","save","restore","get","drop",
	"time","exit","start","shower","watch","turn","put","switch",
	"read","salt","pepper","inven","inventory","take","inv","open",
	"close","shut","push","scope","pull","press","enter","date",
	"mean","think","hello","hi","good","bad","bye","goodbye","stop","go",
	"","","","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","the","a","an","un","","","","","",
	"","","","","","","","who","what","where","why","when","how","is",
	"are","am","have","yes","no","maybe","","","","","","","",
	"i","you","me","us","we","her","him","them","it","god","this","that","","","","",
	"all","any","away","into","over","front","back","left","right","on","around",
	"under","in","at","through","thru","out","off","backward","forward",
	"inside","outside","to","too","also","with","without","and","or",
	"up","down","of","above","behind","game","rug","statue",
	"fireplace","grate","wall","floor","telescope","love","city",
	"water","ocean","traffic","road","highway","bed","waterbed","desk",
	"engineer","teacher","student","self","ceo"};

struct event
   {
   struct time beg;     /*begin time for event*/
   struct time end;	/*end time for event*/
   int loc;		/*location # of event*/
   int obnum;		/*object number that appears-disappears*/
   };
struct event eve[NUMEVE];

/*Globals*/
unsigned size;    	/*  size of bit image */
void *brushbuff;	/*  pointer to buffer*/
unsigned csize;    	/*  size of cursor bit image */
void *cbuff;	/*  pointer to cursor buffer*/
unsigned sizeman;	/*size of character image*/
unsigned sizeheli;
unsigned sizecar;
unsigned sizeroad;
unsigned sizespike;
unsigned sizeline;	/*size of line fills*/
void *man[8];		/*pointers to character image*/
void *robot[8];
void *screen[7+NUMMOBJ];           /*pointers to background for images*/
void *screen3[2];           /*pointers to background for images*/
void *heli[5];		/*pointers to heli images*/
void *car[NUMCAR];           /*pointers to car images*/
void *road[NUMROAD];
void *spike[NUMSPIKE];
void *lines3[17];        /*17 - robot background lines*/
void *lines[170];	/*170 background lines  17-char  48-heli */
char upat1[8] =  {0x18, 0x3c,0x7e,0xff,0xff,0x7e,0x3c,0x18};
char upat2[8] =  {0x00, 0xf7,0xf7,0xf7,0x00,0xfe,0xfe,0xfe};
char upat3[8] =  {0xee, 0xee,0xee,0xee,0xe0,0xee,0xee,0x0e};
char cursor[2] = {0xdb, 0x00};
char PATH[] = {0x5c,'2','0','2','0',0x5c,'\0'};
char PATHC[] = {0x5c,'2','0','2','0',0x5c,'\0'};
char PATHL[] = {0x5c,'2','0','2','0',0x5c,'\0'};
char PATHO[] = {0x5c,'2','0','2','0',0x5c,'\0'};
char strtim[17];	/*string for time*/
char command[COMLEN];	/*string for user input*/
char it[300];		/*string for computer*/
char precom[COMLEN];	/*previous command*/
char des[DESC1][DESC2];	/*current location description*/
char name[30];
int lcolor,lc,oldcolor;	/*  line color */
int pattern,border,brush,redraw;/*  fill pattern  */
int onemo;		/* just erase extra*/
int p1,p2,midx,midy;			/*  1st point for circle or line*/
int lstyle,style,direction,tsize;    /*text descriptions*/
int ex,ex2;			/*exit flags*/
int radx,rady;		/*radii for ellipse*/
int x1,y1,x2,y2;        /*character coordinates*/
int x3,y3,x4,y4;       /*robot coords*/
int carx[NUMCAR];   /*car coord*/
int roadx[NUMROAD],spikex[NUMSPIKE];
int skin[8],skin3[8];
int numimg,numimg2,numimg3,numimg4;
int page;		/*current graphics page*/
int lflag;		/*load character flag*/
int pntx[4],pnty[4];	/*boundary points for picture*/
int hitflag;		/*boundary hit flag*/
int dx, dy;		/*change in x1 and y1*/
int dx2,dy2;
int mode;		/*character direct 0-dn 1-lt 2-up 4-rt*/
int mode3;
int curloc,curloc3;		/*location number you and robot*/
int curobj;		/*current object*/
int newloc;		/*new location number*/
int doorflag;		/*hit door*/
int speed;		/*speed of game action*/
int cursx,cursy,precur;	/*cursor coords*/
int numwd;              /*number of words in database*/
int wdflag;		/*how many words in an input sentence*/
int retsen;		/*return sentence flag*/
int slot,channel;	/*tv variables*/
int onepic;		/*flag for one picture*/
int telpic;		/*telescope picture*/
int qflg;		/* quit flag*/
int spec[NUMSPEC];  	/*special flags  (0-tv,1-sh,ba,2-timr,3-commas,4-carscene)*/
			/*5-movement 6-regular putout 7-phone 8-mom 9-package
			10-17=delivered,18-trash,19-stock,20-robot,21-car
			door unlocked,22-got out of car at 57,23-(0 earth
			1 moon, 2-port1, 5-elev1,) 24-#ofitems ret*/
int sent[10];   	/*sentence in numbers*/

int cash,cash0;
int del,inv;  /*delay #of inv items*/
int c2,c3;
int moonindx,shipindx;  /*moon index*/

main()
{
int g_driver, g_mode, g_error;
int b,c,count;		/*  pause counter */
int locolor;		/*  local color */
unsigned lcnt;  /*long counter*/
int lb;			/*  brush number */
float hypot;
char ch,ch1,ch2,key[2];		/*key*/
int ich,ich1,ich2;		/*int-<char*/
char tstr[SLEN],tstr2[SLEN];
int lobrush;		/*local brush*/

/*run character maker*/
system("CHAR.EXE");
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
getdate(&today);  	/*get today's date*/
today.da_year=2020;	/*set tomarrow's date*/

gettime(&utime);       /*get user's time*/  /*set my time*/
mtime.ti_hour=6;  mtime.ti_min=0;  mtime.ti_sec=0; mtime.ti_hund=0;
page=0;
desc();    /*load descriptions*/
setvisualpage(!page);
setactivepage(page);

  init_var();
  load_file();        /*load title picture*/
  setfillstyle(SOLID_FILL, 15);
  bar(0,0,640,300);   /*white top */
  setfillstyle(SOLID_FILL, 0);
  bar(0,301,640,350);   /*black bottom */
  draw_it();		/*draw title picture*/
  setvisualpage(page);     /*show title*/
  load_obj();		/*load objects*/
  load_mobj();          /*load moving objects*/
  load_events(eve);	/*load events*/
  setactivepage(!page);    /*flip to page 1*/
  setfillstyle(SOLID_FILL, 15);
  bar(0,0,640,32);   /*white top */
  alloc_lines();
  alloc_lines3();      /*allocate memory for char lines*/
  lflag=2;     /*flag=ted*/
  load_traits("TED");
  for(c=0;c<=8;c++)
    skin3[c]=skin[c];
  load_file(); 		/*load ted character*/
  lflag=0;
  draw_it();	/*draw ted on page 1*/
  getrobot();	/*get image of ted*/
  setfillstyle(SOLID_FILL, 0);
  bar(0,0,640,300);   /*black top */
  for (c=0;c<4;c++)
    {
    lflag=3;     /*flag=object(heli)*/
    curobj=c+24;
    load_file();   /*load heli*/
    draw_it();	/*draw heli on page 1*/
    lflag=0;
    }
  alloc_lines2();      /*allocate memory for heli lines*/
  getheli();	/*get image of heli*/
  for(c=0;c<NUMMOBJ;c++)			/*draw objects*/
  {
  draw_mo(c);
  if (c<NUMCAR)
    getcar(c);
  if (c>=NUMCAR && c<NUMCAR+NUMROAD)
    getroad(c-NUMCAR);
  if (c>=NUMCAR+NUMROAD)
    getspike(c-NUMCAR-NUMROAD);
  }

  setactivepage(page);     /*flip back to page 0*/
  x1=x2=x3=x4=TITX;       /*set current coord*/
  y1=y2=y3=y4=TITY;
  getlines3();
  putimage(x3,y3,robot[6],COPY_PUT);	/*draw ted on page 0*/
  putlines3();
  draw_heli();
  setactivepage(!page);  /*page 1 active*/
  load_file();        /*load title picture*/
  setfillstyle(SOLID_FILL, 15);
  bar(0,0,640,300);   /*white top */
  setfillstyle(SOLID_FILL, 0);
  bar(0,301,640,350);   /*black bottom */
  draw_it();		/*draw title picture*/
  putimage(x3,y3,robot[6],COPY_PUT);	/*draw ted on page 0*/
  putlines3();

  while (kbhit()==0)    /*while no key press*/
    {
    for(c=0;c<4;c++)
      {
      obj[c+24].p[0]=obj[c+24].p[0]-SPEEDH;  /*move heli to left*/
      if (obj[c+24].p[0]<=0) obj[c+24].p[0]=638;
      }
    draw_heli();
    setvisualpage(!page);
    delay(0);   delay(del);
    setactivepage(page);
    erase_heli();
    for(c=0;c<4;c++)
      {
      obj[c+24].p[0]=obj[c+24].p[0]-SPEEDH;  /*move heli to left*/
      if (obj[c+24].p[0]<=0) obj[c+24].p[0]=638;
      }
    draw_heli();
    setvisualpage(page);
    delay(0);   delay(del);
    setactivepage(!page);
    erase_heli();
    }   /*end while no kbhit*/
  ch=getch();
  if(ch==0)  getch();
  setactivepage(!page);
  setfillstyle(SOLID_FILL, 15);
  bar(0,0,640,32);   /*white top */
  setfillstyle(SOLID_FILL, 0);
  bar(0,301,640,350);   /*black bottom */
  load_traits("DEF");
  lflag=1;
  load_file();	/*load character file*/
  chrcur=cur;
  lflag=0;
  draw_it();	/*draw default charact0er*/
  getman();
  alloc_lines();      /*allocate memory for lines*/
  init_var2();
  strcpy(command,"");
  strcpy(precom,"");
  init_mob();
  init_ob();
  del=320;
while(ex2 == 0)		/*every new location starts here*/
{
x2=x1;  y2=y1;
if (onepic>0) {newloc=curloc;  curloc=onepic;}
spec[4]=0;
for(count=0;count<2;count++)     /*draw picture on both pages*/
{
if (curloc==8||curloc==22||curloc==19)  getmob();
if (curloc==42||curloc==43)  {getbroad(); getbspike();}
if (curloc==56) obj[130].loc=56;
for (b=0;b<NUMCAR;b++)
  carx[b]=mobj[b].p[0];
for (b=0;b<NUMROAD;b++)
  roadx[b]=mobj[b+NUMCAR].p[0];
for (b=0;b<NUMSPIKE;b++)
  spikex[b]=mobj[b+NUMCAR+NUMROAD].p[0];
load_file();   /*load picture*/
if (spec[23]==3&&curloc==62) door[0].vis=0;
if (spec[23]==4&&curloc==62) door[1].vis=0;
if (spec[23]==5&&curloc==62) door[2].vis=0;
if (curloc==63)
  switch(spec[23]) {
    case 6:
      door[0].vis=0;  door[0].next=62;
      break;
    case 7:
      door[0].vis=0;  door[0].next=66;
      break;
    case 8:
      door[0].vis=0;  door[0].next=67;
      break;
    case 9:
      door[0].vis=0;  door[0].next=68;
      break;
    }
if (curloc==64)
  switch(spec[23]) {
    case 10:
      door[0].vis=0;  door[0].next=62;
      break;
    case 11:
      door[0].vis=0;  door[0].next=69;
      break;
    case 12:
      door[0].vis=0;  door[0].next=70;
      break;
    case 13:
      door[0].vis=0;  door[0].next=71;
      break;
    }
if (curloc==65)
  switch(spec[23]) {
    case 14:
      door[0].vis=0;  door[0].next=62;
      break;
    case 15:
      door[0].vis=0;  door[0].next=72;
      break;
    case 16:
      door[0].vis=0;  door[0].next=73;
      break;
    case 17:
      door[0].vis=0;  door[0].next=74;
      break;
    }
/*printf("DOORFLAG=%d\n",doorflag);*/
if (doorflag>0)
  {
  dorhit();
  onemo=1;
    x2=x1;  y2=y1;
    x4=x3;  y4=y3;
  }
if (!onepic&&count==1&&spec[1]!=2&&spec[1]!=3)
  {
    if (y1<=y3) get_char();
    if (spec[20]>=1&&curloc3==curloc)
      get_bot();
    if (y3<y1) get_char();
    if (curloc==42||curloc==43)
      {
      drroad();
      drspike();
      }
    if (y1<=y3)  draw_char();
    if (spec[20]>=1&&curloc3==curloc)
      draw_bot();
    if (y3<y1) draw_char();
    if (spec[4]==1)
      drmob();
  }
if (curloc==55) {mobj[14].loc=55; drmob();}
setvisualpage(page);
setactivepage(!page);
setfillstyle(SOLID_FILL, 15);
bar(0,0,640,300);   /*white top */
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
setusercharsize(1,1,1,1);
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
setcolor(15);
oldcolor=lcolor;
lcolor=15;
setlinestyle(0,ULIN1,1);
lcolor=oldcolor;        /*initial line color */
draw_it();
lobrush=brush;
draw_cbrush(lobrush,oldcolor);
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
drob();         	/*draw objects*/
put_com();              /*put out cursor and command*/
page=!page;	/*flip pages*/
}   /*end for loop*/
doorflag=0;
setactivepage(page);
if (!onepic&&spec[1]!=2&&spec[1]!=3)
    {
    if (y1<=y3) get_char();
    if (spec[20]>=1&&curloc3==curloc)
      get_bot();
    if (y3<y1)  get_char();
    if (curloc==42||curloc==43)
      {
      drroad();
      drspike();
      }
    if (y1<=y3) draw_char();
    if (spec[20]>=1&&curloc==curloc3)
      draw_bot();
    if (y3<y1) draw_char();
    if (spec[4]==1)
	drmob();
    }
if (curloc==55)  {mobj[14].loc=55; drmob();}
setvisualpage(page);
if (curloc==61) dead();
if ((curloc==63||curloc==64||curloc==65)&&obj[245].loc==-3) obj[245].loc=-2;
else ex=0;
if (onepic)
  {
  putout(des[telpic]);    /*look at moon*/
  ch=getch();    /*get key*/
  if (ch==0)  getch();
  ex=1;
  onepic=0;
  }
while (ex == 0)    /*while there is no exit*/
  {
    if (curloc==55)  /*border*/
      bordr();
    if (curloc==60&&moonindx<6) {gotomoon(); moonindx++;}
    if (curloc==62&&spec[23]<2)
     {putout("You ran out of money and were stranded at the wrong moon port!");
      qflg=1; putout("Play Again (Y/N)");}
    if (curloc==75&&shipindx<6) {gotoship(); shipindx++;}
    if (curloc==77)
	   {putout("You are face to face with General Collins.  Around the room you see screens of different people in their homes.  You of course get caught and executed.  You are no longer alive.");
	     qflg=1; putout("Play Again (Y/N)");}
    gettime(&dtime);       /*get user's time*/
    if (dtime.ti_hund>utime.ti_hund)
      mtime.ti_hund=dtime.ti_hund-utime.ti_hund;
    else
      mtime.ti_hund=99-(utime.ti_hund-dtime.ti_hund);

   if (spec[1]==1)  /*take a shower*/
       {  setactivepage(page);  erase_char();  mtime.ti_hund=90;
       for (b=1;b<=600;b++)    /*600 sec= 10 minutes*/
	  { mtime.ti_sec++; timr(); check_eve();}
	   putout("Ten minutes pass.");/* get_char(); draw_char();*/
	    obj[21].loc=-2; spec[1]=0; mtime.ti_hund=0;
	    refresh();
	  setactivepage(!page);
       }
    else
     { if (spec[1]==2)  /*go to sleep*/
	{  setactivepage(page); mtime.ti_hund=90;
	  for (b=1;b<=1200;b++)    /*1200 sec= 20 minutes*/
	     { mtime.ti_sec++; timr(); check_eve();}
	  putout("Twenty minutes pass.");
	  spec[1]=0; mtime.ti_hund=0; obj[7].loc=-2; refresh();
	  setactivepage(!page);
	 }
      else
       {
       timr();
       if (!(check_eve()))
	  {
	  spec[4]=0;
	  if (curloc>7 && curloc<24) spec[4]=1;
	  if (dx!=0||dy!=0||spec[4]==1)  spec[5]=1; /* have to flip pages*/
		else  spec[5]=0;
	  if (spec[20]>=1&&curloc3==curloc)  mvbot();
	  if (dx2!=0||dy2!=0) spec[5]=1;
	  if (spec[5]==1)		/*we need to flip pages*/
	    {                             /* (we have moving objects)*/
	    if (onemo==1&&spec[1]!=3)
	      {
	      one();
	      onemo=0;
	      }
	    dir_char();
	    if (spec[20]>=1&&curloc3==curloc)
	      dir_bot();
	    mvmob();
	    bhit();
	    if (hitflag>0&&hitflag<5)
	      dorcheck();
	    obhit();
	    if (hitflag==0)
	      {
	      if ((curloc!=42&&curloc!=43)||(curloc==42&&dx<0)||(curloc==43&&dx>0))
		x1 += dx;
	      y1 += dy;
	      }
	    hitflag=0;            /*fix boundaries*/
	    if (spec[20]>=1&&curloc3==curloc)
		{
		x3 += dx2;
		y3 += dy2;
		}
	    if (curloc==42||curloc==43)
		{mvroad(); mvspike();}
	    if (x1<0)  {x1 = 0; hitflag=1;}
	    if (y1<0)  {y1 = 0; hitflag=2;}
	    if (x1>639-WMAN) {x1 = 639-WMAN; hitflag=3;}
	    if (y1>300-HMAN-1) {y1 = 300-HMAN-1; hitflag=4;}
	    setactivepage(!page);		/*go to second screen*/
	    if (spec[1]!=3)
	      {
	      if (y1<=y3)
		get_char();
	      if (spec[20]>=1&&curloc3==curloc)
		get_bot();
	      if (y3<y1) get_char();
	      }
	    if (curloc==42||curloc==43)
	      {
	      drroad();
	      drspike();
	      }
	    if (spec[1]!=3)
	      {
	      if (y1<=y3)
		draw_char();
	      if (spec[20]>=1&&curloc3==curloc)
		draw_bot();
	      if (y3<y1)  draw_char();
	      }
	    if (spec[4]==1)
	      drmob();
	    setvisualpage(!page);                    /*show character*/

	    delay(0);
	    delay(del);
	    if (spec[4]==1)
	      mobhit();
	    setactivepage(page);                    /*go to old (1st) page*/
	    if (curloc==42||curloc==43)
		{
		erase_road();
		erase_spike();
		}
	    if (spec[4]==1)
	      erase_mob();   /*erase moving objects*/
	    if (spec[1]!=3)
	      {
	      if (y1<=y3)
		erase_char();
	      if (spec[20]>=1&&curloc3==curloc)
		erase_bot();
	      if (y3<y1)
		erase_char();
	      }
	    page=!page;
	    if (curloc!=newloc)
	      refresh();
	    } /*end spec[5] flag*/
	  }    /*end if no event happened*/
	}     /*end sleep*/
     }       /*end shower*/

  if (kbhit() != 0)
    {
    ch = getch();
    key[0]=ch;  key[1]=0;
    if (ch == 0)  ch2= getch();
    switch (ch)
      {
      case 0:
	switch(ch2)
	  {
	  case 15:
	    putinv();
	    break;
	  case 59:			/*F1*/
	    menu();
	    break;
	  case 60:
	    save_game();
	    break;
	  case 61:			/*F3*/
	    strcpy(command,precom);
	    cursx=precur;
	    setactivepage(!page);
	    setfillstyle(1,0);
	    bar(16,cursy,639,cursy+16);
	    put_com();
	    setactivepage(page);
            setfillstyle(1,0);
	    bar(16,cursy,639,cursy+16);
	    put_com();
	    break;
	  case 62:
	    restore_game();
	    break;
	  case 63:
	    hint();
	    break;
	  case 68:			/*F10*/
	    del=del+300;
	    if (del>900) del=20;
	    break;
	  case 71:			/*up-left */
	    if (spec[1]!=3)
	      {
	      dx = -speed;
	      dy = -speed;
	      mode=1;
	      }
	    break;
	  case 72:			/*up arrow*/
	    if (spec[1]!=3)
	      {
	      dx = 0;
	      dy = -speed;
	      mode=2;
	      }
	    break;
	  case 73:			/*up-right*/
	    if (spec[1]!=3)
	      {
	      dx = speed;
	      dy = -speed;
	      mode=4;
	      }
	    break;
	  case 75:			/*left arrow*/
	    if (spec[1]!=3)
	      {
	      dx = -speed;		/*change in x is -1 */
	      dy = 0;
	      mode=1;
	      }
	    break;
	  case 76:		/*5-stop*/
	    dx=0;
	    dy=0;
	    break;
	  case 77: 			/*right arrow*/
	    if (spec[1]!=3)
	     {
	     dx = speed;
	     dy = 0;
	     mode=4;
	     }
	   break;
	 case 79:			/*down-left*/
	    if (spec[1]!=3)
	     {
	     dx = -speed;
	     dy = speed;
	     mode=1;
	     }
	   break;
	 case 80:			/*down arrow*/
	    if (spec[1]!=3)
	     {
	     dx = 0;
	     dy = speed;
	     mode=0;
	     }
	   break;
	 case 81:			/*down-right*/
	    if (spec[1]!=3)
	     {
	     dx = speed;
	     dy = speed;
	     mode=4;
	     }
	   break;
	  }	/*end extended keys switch*/
	break;
      case 8:			/*  backspace*/
	if (cursx>16)
	  {
	  setfillstyle(SOLID_FILL,0);
	  setactivepage(page);
	  bar(cursx-16,cursy,cursx+16,cursy+16);
	  setactivepage(!page);
	  bar(cursx-16,cursy,cursx+16,cursy+16);
	  command[strlen(command)-1]=0;
          cursx=cursx-16;
	  draw_cursor();
	  }
	break;
      case 9:			/*'TAB'*/
      case 11:
	putinv();
	break;
      case 13:			/* '<cr>'  carriage return*/
	strcpy(precom,command);	/*save old command*/
	strcpy(it,command);
	spec[3]=1;   /*set flag to ignore commas, periods*/
	make_words();
	spec[3]=0;
	match_words();
	setfillstyle(SOLID_FILL,0);
	precur=cursx;		/*save cursor*/
        cursx=16;		/*reset cursor*/
	setactivepage(page);
	bar(16,310,639,349);		/*blackout old sentence*/
	draw_cursor();
	setactivepage(!page);
	bar(16,310,639,349);		/*blackout old sentence*/
	draw_cursor();
	strcpy(command,"");
	break;
      case 27:	/*esc*/
	quit();
	break;
      case 43:			/* '+' speed up*/
	if (speed<8) speed++;
	dx=(dx>0)*speed-(dx<0)*speed;
	dy=(dy>0)*speed-(dy<0)*speed;
	break;
      case 45:			/* '-' slow down*/
	if (speed>1) speed--;
	dx=(dx>0)*speed-(dx<0)*speed;
	dy=(dy>0)*speed-(dy<0)*speed;
	break;
      default:		/*alpha or other symbol*/
	if (cursx<592)     /*608*/
	  {
	  setcolor(15);
	  setfillstyle(SOLID_FILL,0);
	  settextstyle(0,0,2);
	  setactivepage(page);
	  bar(cursx,cursy,cursx+16,cursy+16);  /*blackout cursor*/
	  outtextxy(cursx,cursy,key);
	  setactivepage(!page);
	  bar(cursx,cursy,cursx+16,cursy+16);  /*blackout cursor*/
	  outtextxy(cursx,cursy,key);
	  cursx=cursx+16;
	  strcat(command,key);
	  draw_cursor();
	  }
	break;
      }                            /*end switch*/
   }                           /*end if kbhit*/
   if (hitflag==6)  {hitflag=0;
	putout("You were hit by a car.  Now you are dead.");  dead();}
  }                             /*end while*/
}		/*end 2nd while*/
closegraph();
}	       /*end main*/

