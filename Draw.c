/*  Draw.c   */
/*       by Ted Huntington   */

/*  This program allows the user to draw pictures that  */
/*  will be used in interactive graphic adventures  */

#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "process.h"
#include "math.h"
#include "string.h"
#include "graphics.h"
#include "alloc.h"

#define NUMMOVE 610    /*number of moves*/
#define CURX 460    /*coords of current brush*/
#define CURY 303
#define ULIN1 0xcccc
#define SLEN  40
#define SANG 0    /*start and end angles for ellipse*/
#define EANG 360

/*Globals*/
unsigned size;    	/*  size of bit image */
void *brushbuff;	/*  pointer to buffer*/
unsigned csize;    	/*  size of cursor bit image */
void *cbuff;	/*  pointer to cursor buffer*/
int lcolor,lc,oldcolor;	/*  line color */
int mcolor;             /*mix color*/
int pattern;		/*  fill pattern  */
int border;		/*  border color*/
int brush;
int p1;			/*  1st point for circle or line*/
int p2;			/*  2nd point for circle or line*/
char upat1[8] =  {0x18, 0x3c,0x7e,0xff,0xff,0x7e,0x3c,0x18};
char upat2[8] =  {0x00, 0xf7,0xf7,0xf7,0x00,0xfe,0xfe,0xfe};
char upat3[8] =  {0xee, 0xee,0xee,0xee,0xe0,0xee,0xee,0x0e};
int x1,y1,x2,y2;        /*point coordinates*/
int lstyle;		/*line style*/
int style,direction,tsize;    /*text descriptions*/
int ex,ex2;			/*exit flags*/
int savd;			/*picture saved?*/
int midx,midy;		/*midpoint for circle*/
int radx,rady;		/*radii for ellipse*/
int pntx[4],pnty[4];	/*boundary points*/
char disp;   /*display 0-on 1-off*/

struct action         /*actions*/
   {
   int name;  /*0-color,1-brush,2-lstyle,3-point,*/
	      /*4-line,5-circle,6-rect,7-fill,8-text*/
   int a[5];   /*x1-color-brush,y1-style,x2-rad-direct-tsize,y2-strlen*/
   char str[SLEN];  /*string*/
   };
int cur;   /*current act*/

struct action act[NUMMOVE];

struct doors		/*door structs*/
  {
  int a[4];	/*x1,y1,x2,y2*/
  int vis;	/*0-yes, 1-no*/
  int next;	/*next room*/
  };
struct doors door[9];

main()
{
int g_driver, g_mode, g_error;

int dx, dy;		/*change in x1 and x2*/

int count;		/*  pause counter */
int locolor;		/*  local color */
char temp[2];
int lb;			/*  brush number */
int mode;		/* flag means we are drawing*/
float hypot;  /*was double*/
int ihypot;
char ch,ch1,ch2;		/*key*/
int ich,ich1;		/*int-<char*/
char tstr[SLEN];
char tstr2[SLEN];
int fillflag;		/*ok  hueristic*/
int lobrush;		/*local brush*/


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
setvisualpage(0);
setactivepage(0);

x1=y1=x2=y2=dx=dy=0;
midx=midy=0;
radx=0; rady=0;
mode=0;
brush=0;
x1=y1=100;       /*set current coord*/
fillflag = 0;
ex2=0;
cur=0;
lcolor=0;   lstyle=0;    lb=0;
savd=0;
while(ex2 == 0)
{
free(0);		/*free up memory*/
ex=0;
printf("0-black, 1-white background");
ch=getch();
if (ch==48)  setfillstyle(SOLID_FILL, 0);
else
setfillstyle(SOLID_FILL, 15);
setusercharsize(1,1,1,1);
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
setcolor(15);
printf("Display 0-on 1-off");
ch=getch();
if (ch==48) disp=0;
else disp=1;
bar(0,0,640,300);     /* set white background  */
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
if (disp==0)
  {
  outtextxy(0,302,"0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15  current:");
  outtextxy(145,340,"brush:");
  outtextxy(220,340,"color:");
  outtextxy(300,340,"cursor:                 moves left");
  for (count=0;count<16;count++)
    {
    setfillstyle(SOLID_FILL, count);
    bar(0+count*23,311,23+count*23,319);
    }
  outtextxy(5,321,"0 1 2 3 4 5 6 7 8 9 10");
  setfillstyle(SOLID_FILL, 15);
  bar(CURX-9,CURY,CURX+9,CURY+18);
  oldcolor=lcolor;
  lcolor=15;
  setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
  draw_brushes();
  }
lcolor=oldcolor;        /*initial line color */
if (cur>0) draw_it();
if (disp==1)
  {
  setfillstyle(SOLID_FILL, 0);
  bar(0,301,640,350);   /*black bottom */
  }
else
  {
  lobrush=brush;
  draw_cbrush(lobrush,oldcolor);
  putimage(x1,y1,cbuff,XOR_PUT);
  }
while (ex == 0)    /*while there is no exit*/
  {
  if (disp==0)
  {
  /*update display*/

  if (fillflag!=1 && (mode==0 || mode==3 || mode==6 ||
		      mode==9 || mode==11 || mode==13 ))
     putimage(x1,y1,cbuff,XOR_PUT);
  else
     fillflag=0;
  x1 += dx;
  y1 += dy;
  dx=dy=0;   /*reset dx and dy*/
  if (x1<0)  x1 = 0;    /*fix boundaries*/
  if (y1<0)  y1 = 0;
  if (x1>639-brush) x1 = 639-brush;
  if (y1>300-brush) y1 = 300-brush;

  /*cleanup display*/

  setfillstyle(0,0);
  bar(360,340,490,350);
  bar(270,340,290,350);
  bar(195,340,210,350);
  setfillstyle(1,15);
  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
  /*update display*/
  setcolor(15);
  itoa(brush,temp,10);
  outtextxy(195,340,temp);
  itoa(lcolor,temp,10);
  outtextxy(275,340,temp);
  itoa(x1,temp,10);
  outtextxy(360,340,temp);
  itoa(y1,temp,10);
  outtextxy(390,340,temp);
  itoa(NUMMOVE-cur,temp,10);
  outtextxy(460,340,temp);
  setcolor(lcolor);
  switch (mode)
     {
     case 0:     /*no draw*/
        if (fillflag == 0)
	   putimage(x1,y1,cbuff,XOR_PUT);
	else
	   fillflag = 0;
	break;
     case 1:    /*draw*/
	putimage(x1,y1,brushbuff,COPY_PUT);
	act[cur].name=3;
	act[cur].a[0]=x1;
	act[cur].a[1]=y1;
	cur++;
	break;
     case 2:    /*line 1st point*/
	putimage(x1,y1,brushbuff,COPY_PUT);
	mode=3;  /*back to no draw*/
	x2=x1;  y2=y1;	/*save old coords*/
	fillflag=1;
	break;
     case 3:     /*no line draw*/
        if (fillflag == 0)
	   putimage(x1,y1,cbuff,XOR_PUT);
	else
	   fillflag = 1;
	break;
     case 4:	/* line draw */
	setcolor(lcolor);
	line(x1,y1,x2,y2);
	act[cur].name=4;
	act[cur].a[0]=x1;
	act[cur].a[1]=y1;
	act[cur].a[2]=x2;
	act[cur].a[3]=y2;
	cur++;
	x2=x1;  y2=y1;  /*get new coords*/
	mode=3;
	break;
     case 5:     /*circle1 1st point*/
	x2=x1;  y2=y1;
        putimage(x1,y1,brushbuff,COPY_PUT);
	mode=6;
     case 6:     /*no circle draw*/
        if (fillflag == 0)
	   putimage(x1,y1,cbuff,XOR_PUT);
	else
	   fillflag = 0;
	break;
     case 7:    /*circle draw*/
	setcolor(lcolor);
	/*find midpoints*/
	if (x1>x2) midx= (int)(x2+(x1-x2)/2);
	else midx = (int)(x1+(x2-x1)/2);
	if (y1>y2) midy= (int)(y2+(y1-y2)/2);
	else midy = (int)(y1+(y2-y1)/2);
	if (x1==x2)   hypot=(abs(y1-y2)/2)*1.3;
	if (y1==y2)  {if (x1>x2) hypot=(x1-x2)/2;
			else hypot=(x2-x1)/2;}
/*	if (x1!=x2 && y1!=y2)
	   {
	   hypot=abs((x1-midx)*(x1-midx)) + abs((y1-midy)*(y1-midy))*1.8;
	   hypot= sqrt(hypot);
	   }                            */
/*	hypot=1.0;*/
	ihypot=(int)hypot;
/*	printf("%d %d %d\n",midx,midy,ihypot);*/
	circle(midx,midy,ihypot);
	act[cur].name=5;
	act[cur].a[0]=midx;
	act[cur].a[1]=midy;
	act[cur].a[2]=(int)hypot;
	cur++;
	mode=0;
	break;
     case 8:     /*1st point*/
	setcolor(lcolor);
	x2=x1;  y2=y1;
        putimage(x1,y1,brushbuff,COPY_PUT);
	mode=9;
	fillflag=1;
	break;
     case 9:     /*no rectangle draw*/
	putimage(x1,y1,cbuff,XOR_PUT);
	break;
     case 10:	/* rectangle draw */
	setcolor(lcolor);
	rectangle(x1,y1,x2,y2);
	act[cur].name=6;
	act[cur].a[0]=x1;
	act[cur].a[1]=y1;
	act[cur].a[2]=x2;
	act[cur].a[3]=y2;
	cur++;
	x2=x1;  y2=y1;  /*get new coords*/
	mode=9;
	break;
     case 11:				/*text*/
       for (count=0;count<SLEN;count++)
	  {
	  tstr[count]=0x0;
	  tstr2[count]=0x0;
	  }
       strcpy(tstr,"");
       strcpy(tstr2,"");
       while (ex!=-1)
	 {
	 ch1=getch();
	 tstr[ex]=ch1;
	 ex++;
	 if (ch1==13)
	    {
            setcolor(0);
	    outtextxy(600,305,"text");
	    setcolor(lcolor);
	    if (ex==1) strcpy(tstr,"");
	    else
	      {
	      strncpy(tstr2,tstr,ex-1);
	      ex=-1;
	      }
	    }
	 }
       ex=0;
       setcolor(lcolor);
       settextstyle(style,direction,tsize);
       setusercharsize(tsize+1,1,tsize+1,1);
       outtextxy(x1,y1,tstr2);
       act[cur].name=8;
       act[cur].a[0]=x1;
       act[cur].a[1]=y1;
       act[cur].a[2]=style;
       act[cur].a[3]=direction;
       act[cur].a[4]=tsize;
       act[cur].a[5]=strlen(tstr2);
       strcpy(act[cur].str,tstr2);
       cur++;
       setusercharsize(1,1,1,1);
       settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
       mode=0;
       fillflag=1;
       break;
     case 12:     /*ellipse 1st point*/
	fillflag=1;
	x2=x1;  y2=y1;
	mode=13;
	break;
     case 13:     /*no ellipse draw*/
        if (fillflag == 0)
	   putimage(x1,y1,cbuff,XOR_PUT);
	else
	   fillflag = 0;
	break;
     case 14:    /*ellipse draw*/
	putimage(x2,y2,cbuff,XOR_PUT);     /*take away 1st point*/
	setcolor(lcolor);
	/*find midpoints*/
	if (x1>x2) midx= (int)(x2+(x1-x2)/2);
	else
	  midx = (int)(x1+(x2-x1)/2);
	if (y1>y2) midy= (int)(y2+(y1-y2)/2);
	else
	  midy = (int)(y1+(y2-y1)/2);
	radx=abs(x1-x2)/2;   rady=abs(y1-y2)/2;
	ellipse(midx,midy,SANG,EANG,radx,rady);
	act[cur].name=9;
	act[cur].a[0]=midx;
	act[cur].a[1]=midy;
	act[cur].a[2]=radx;
	act[cur].a[3]=rady;
	cur++;
	mode=0;
	break;
     }
   }  /*end if disp==0*/
  count = 0;
    ch = getch();

    if (ch == 0)  ch= getch();
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    switch (ch)
      {
      case 32:			/*space - toggle draw mode*/
	fillflag=1;		/*to make sure no little dot after line*/
	if (mode == 0)
	   {
	   setcolor(15);
	   outtextxy(600,305,"draw");
	   setcolor(lcolor);
	   mode=1;
	   }
	else
	   {
	   setcolor(0);
	   outtextxy(600,305,"draw");
           setcolor(lcolor);
	   mode=0;
	   }
	break;
      case 49:			/*down-left-10*/
	dx= -8;
	dy =8;
	break;
      case 50:			/*down-10*/
	dx= 0;
	dy =8;
	break;
      case 51:			/*down-right-10*/
	dx= 8;
	dy =8;
	break;
      case 52:			/*left-10*/
	dx =-8;
	dy = 0;
	break;
      case 54:			/*right-10*/
	dx= 8;
	dy = 0;
	break;
      case 55:			/*up-left-10*/
	dx= -8;
	dy =-8;
	break;
      case 56:			/*up-10*/
	dx= 0;
	dy =-8;
	break;
      case 57:			/*up-right-10*/
	dx= 8;
	dy =-8;
	break;
      case 67:			/*C - circle*/
	fillflag=1;		/*to make sure no little dot after line*/
	if (x1==x2 && y1==y2)
	   mode=6;
	switch (mode)
	   {
	   case 0:
	     setcolor(15);
	     outtextxy(530,305,"Circle");
	     setcolor(lcolor);
	     mode=5;
	     break;
	   case 6:
             setcolor(0);
	     mode=7;
             outtextxy(530,305,"Circle");
	     setcolor(lcolor);
	     break;
	   }
	break;
      case 71:			/*up-left */
	dx = -1;
	dy = -1;
	break;
      case 72:			/*up arrow*/
	dx = 0;
	dy = -1;
	break;
      case 73:			/*up-right*/
	dx = 1;
	dy = -1;
	break;
      case 75:			/*left arrow*/
	dx = -1;		/*change in x is -1 */
	dy = 0;
	break;
      case 76:			/*'L' - Save in file*/
	load_file();
	break;
      case 77: 			/*right arrow*/
	dx = 1;
	dy = 0;
	break;
      case 79:			/*down-left*/
	dx = -1;
	dy = 1;
	break;
      case 80:			/*down arrow*/
	dx = 0;
	dy = 1;
	break;
      case 81:			/*down-right*/
	dx = 1;
	dy = 1;
	break;
      case 83:			/*'S' - Save in file*/
	save_file();
	break;
      case 85:			/*'U' - Undo 10 commands*/
	if (cur>9) cur=cur-10;
	ex=-1;
	break;
      case 98:			/*'b' - brush style*/
	setcolor(15);
	outtextxy(210,320,"brush=");
	ch1=getch();
	ch2=getch();
	lb=atoi(&ch1);
	if (lb < 0  || lb > 10)
	   {
	   outtextxy(280,320,"invalid brush!");
	   getch();
	   setcolor(0);
	   outtextxy(280,320,"invalid brush!");
	   }
	else
	   {
	   brush=lb;
	   act[cur].name=1;
	   act[cur].a[0]=brush;
	   cur++;
	   putimage(x1,y1,cbuff,XOR_PUT);
	   locolor=lcolor;
	   draw_cbrush(brush,locolor);
	   if (brush==0)
	     setlinestyle(lstyle,ULIN1,1);
	   else
	     setlinestyle(lstyle,ULIN1,3);
	   fillflag=1;
	   }
        setcolor(0);
	outtextxy(210,320,"brush=");
	break;
      case 99:			/*'c' - line color*/
	setcolor(15);
	outtextxy(210,320,"color=");
	ch1=getch();
	ch2=getch();
	ich1=atoi(&ch1);
	lcolor=ich1;
	if (lcolor < 0  || lcolor > 15)
	   {
	   outtextxy(280,320,"invalid color!");
	   getch();
	   setcolor(0);
	   outtextxy(280,320,"invalid color!");
	   }
        setcolor(0);
	outtextxy(210,320,"color=");
	locolor=lcolor;
	act[cur].name=0;
	act[cur].a[0]=lcolor;
	cur++;
	draw_cbrush(brush,locolor);
	break;
      case 100:			/* 'd' - draw */
	draw_it();
	break;
     case 101:			/*'e' - ellipse*/
	if (x1==x2 && y1==y2)
	   mode=12;
	switch (mode)
	   {
	   case 0:
	     setcolor(15);
	     outtextxy(530,305,"Ellipse");
	     setcolor(lcolor);
	     mode=12;
	     break;
	   case 13:
             setcolor(0);
	     mode=14;
	     outtextxy(530,305,"Ellipse");
	     setcolor(lcolor);
	     break;
	   }
	break;
      case 102:			/* 'f' - fill  */
        setcolor(15);
	outtextxy(210,320,"fill style=");
	ch1=getch();
	ch2=getch();
	  pattern=atoi(&ch1);
	if (pattern < 0  || pattern > 15)
	   {
	   outtextxy(350,320,"invalid!");
	   getch();
	   setcolor(0);
	   outtextxy(350,320,"invalid!");
	   }
	else
	   {
	   setcolor(0);
	   outtextxy(210,320,"fill style=");
	   setcolor(15);
	   outtextxy(210,320,"border=");
	   ch1=getch();
	   ch2=getch();
	   border=atoi(&ch1);
	   if (border < 0  || border > 15)
	     {
	     outtextxy(350,320,"invalid!");
	     getch();
	     setcolor(0);
	     outtextxy(350,320,"invalid!");
	     }
	   setcolor(0);
	   outtextxy(210,320,"border=");
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
	     floodfill(x1,y1,border);
	   else
	     {
	     setcolor(15);
	     outtextxy(210,320,"mix color=");
	     ch1=getch();
	     ch2=getch();
	     mcolor=atoi(&ch1);
	     if (mcolor < 0  || border > 15)
	       {
	       outtextxy(350,320,"invalid!");
	       getch();
	       setcolor(0);
	       outtextxy(350,320,"invalid!");
	       mcolor=15;
	       }
	     setcolor(0);
	     outtextxy(210,320,"mix color=");
	     floodwfill(x1,y1,border,lcolor,mcolor);
	     }
	   act[cur].name=7;
	   act[cur].a[0]=x1;
	   act[cur].a[1]=y1;
	   act[cur].a[2]=border;
	   act[cur].a[3]=pattern;
	   act[cur].a[4]=mcolor;
	   cur++;
	   fillflag=1;
	   }
	break;
      case 108:			/*l - line*/
	 if (x1==x2 && y1==y2)
	   {
	   mode=0;
           setcolor(0);
	   outtextxy(600,305,"line");
	   setcolor(lcolor);
	   }
	 else
	 switch(mode)
	   {
	   case 0:
	     mode=2;    /*line mode*/
             setcolor(15);
	     outtextxy(600,305,"line");
	     setcolor(lcolor);
	     break;
	   case 3:
	     mode=4;
	     break;
	   }
	 break;
      case 110:			/*n - new*/
	ex=1;
	cur=0;
	break;
      case 113:      		/*q - quit*/
	if (savd<cur)
	   {
	   printf("Save? (Y/N)\n");
	   ch1=getch();
	   if (ch1!='n' && ch1!='N') save_file();
	   }
	ex2=1;
	ex=1;
	break;
      case 114:			/*r - rectangle*/
	 if (x1==x2 && y1==y2)
	   {
	   mode=0;
           setcolor(0);
	   outtextxy(600,305,"rect");
	   setcolor(lcolor);
	   }
	 else
	 switch(mode)
	   {
	   case 0:
	     mode=8;    /*rectangle mode*/
             setcolor(15);
	     outtextxy(600,305,"rect");
	     setcolor(lcolor);
	     break;
	   case 8:
	     mode=9;
	     break;
	   case 9:
	     mode=10;
	     break;
	   }
	 break;
      case 115:			/*s - set line style */
	 setcolor(15);
	 outtextxy(210,320,"line style=");
	 ch1=getch();
	 if (ch1==13) lstyle=0;
	 else
	   lstyle=ch1-48;
	 if (lstyle < 0  || lstyle > 4)
	   {
	   outtextxy(350,320,"0-4");
	   getch();
	   setcolor(0);
	   outtextxy(350,320,"0-4");
	   }
	else
	   {
	   act[cur].name=2;
	   act[cur].a[0]=lstyle;
	   cur++;
	   setcolor(0);
	   outtextxy(210,320,"line style=");
	   if (brush>0)
	     setlinestyle(lstyle,ULIN1,3);
	   else
	     setlinestyle(lstyle,ULIN1,1);
	   }
	break;
      case 116:			/*t - text*/
	    setcolor(15);
	    outtextxy(210,320,"style:");
	    while (ex==0)
	      {
	      ch1=getch();
	      ch2=getch();
	      ich1=atoi(&ch1);
	      if (ich1<0 || ich1>4)
		 {
		 outtextxy(270,320,"0-4 only!");
		 getch();
		 setcolor(0);
                 outtextxy(270,320,"0-4 only!");
		 setcolor(15);
		 }
	       else
		 {
		 style=ich1;
		 setcolor(0);
		 outtextxy(210,320,"style:");
		 ex=1;
		 }
	      }  /*end while*/
	      ex=0;
            setcolor(15);
	    outtextxy(210,320,"direction:");
	    while (ex==0)
	      {
	      ch1=getch();
	      ch2=getch();
	      ich1=atoi(&ch1);
	      if (ich1<0 || ich1>1)
		 {
		 outtextxy(320,320,"0-horiz 1-vert");
		 getch();
		 setcolor(0);
		 outtextxy(320,320,"0-horiz 1-vert");
		 setcolor(15);
		 }
	       else
		 {
		 direction=ich1;
		 setcolor(0);
		 outtextxy(210,320,"direction:");
		 ex=1;
		 }
	      }  /*end while*/
	      ex=0;
	      setcolor(15);
	      outtextxy(210,320,"size:");
	      while (ex==0)
		{
		ch1=getch();
		ch2=getch();
		ich1=atoi(&ch1);
		if (ich1<0 || ich1>9)
		  {
		  outtextxy(270,320,"0-9");
		  getch();
		  setcolor(0);
		  outtextxy(270,320,"0-9");
		  setcolor(15);
		  }
		else
		  {
		  if (ich1==9 && style==0) ich1=15;
		  tsize=ich1;
		  setcolor(0);
		  outtextxy(210,320,"size:");
		  ex=1;
		  }
	       }  /*end while*/
	    ex=0;
	    mode=11;    /*text mode*/
	    setcolor(15);
	    outtextxy(600,305,"text");
	    setcolor(lcolor);
	    break;
	  case 117:	/*'u' - undo */
	    if (cur>0) cur--;
	    ex=-1;
	    break;
       }                            /*end switch*/
 /*   } */                          /*end if kbhit*/

  }                             /*end while*/
}		/*end 2nd while*/
closegraph();
}                              /*end main*/

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

/*  subs.c - subroutines */
/*   Ted Huntington   */

/*  DRAW_BRUSHES()	*/
/*  DRAW_CBRUSH()	*/
/*  DRAW_IT()		*/
/*  SAVE_FILE()		*/
/*  LOAD_FILE()		*/

draw_brushes()
{
int x,y,f;

x=40;
y=330;
f=15;

setcolor(lcolor);
putpixel(8,y,lcolor);    /*single point brush*/

bar(23,y,24,y+1);	 /*2x2 brush*/

bar(40,y,42,y+2);     /*3x3 brush*/

bar(x+f,y,x+f+3,y+3);     /*4x4 brush*/

bar(x+2*f,y,x+2*f+4,y+4);     /*5x5 brush*/

bar(x+3*f,y,x+3*f+5,y+5);     /*6x6 brush*/

bar(x+4*f,y,x+4*f+6,y+6);     /*7x7 brush*/

bar(x+5*f,y,x+5*f+7,y+7);     /*8x8 brush*/

setfillstyle(2,lcolor);
bar(x+6*f,y,x+6*f+7,y+7);     /*8x8 brush-1*/

setfillstyle(10,lcolor);
bar(x+7*f,y,x+7*f+8,y+8);     /*9x9 brush-1*/

setfillstyle(11,lcolor);
bar(x+8*f,y,x+8*f+9,y+9);     /*10x10 brush-1*/
}

draw_cbrush(int lbrush,int col)
{
free(brushbuff);
free(cbuff);
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
  case 1:
     setfillstyle(SOLID_FILL, 7);
     bar(CURX,CURY,CURX+1,CURY+1);  /*brush 1*/
     csize = imagesize(CURX,CURY,CURX+1,CURY+1);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+1,CURY+1,cbuff);
     setfillstyle(SOLID_FILL, col);
     bar(CURX,CURY,CURX+1,CURY+1);
     size = imagesize(CURX,CURY,CURX+1,CURY+1);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+1,CURY+1,brushbuff);
     break;
  case 2:
     setfillstyle(SOLID_FILL, 7);
     bar(CURX,CURY,CURX+2,CURY+2);  /* brush 2*/
     csize = imagesize(CURX,CURY,CURX+2,CURY+2);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+2,CURY+2,cbuff);
     setfillstyle(SOLID_FILL, col);
     bar(CURX,CURY,CURX+2,CURY+2);
     size = imagesize(CURX,CURY,CURX+2,CURY+2);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+2,CURY+2,brushbuff);
     break;
  case 3:
     setfillstyle(SOLID_FILL, 7);
     bar(CURX,CURY,CURX+3,CURY+3);  /*brush 3*/
     csize = imagesize(CURX,CURY,CURX+3,CURY+3);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+3,CURY+3,cbuff);
     setfillstyle(SOLID_FILL, col);
     bar(CURX,CURY,CURX+3,CURY+3);
     size = imagesize(CURX,CURY,CURX+3,CURY+3);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+3,CURY+3,brushbuff);
     break;
  case 4:
     setfillstyle(SOLID_FILL, 7);
     bar(CURX,CURY,CURX+4,CURY+4);  /*brush 4*/
     csize = imagesize(CURX,CURY,CURX+4,CURY+4);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+4,CURY+4,cbuff);
     setfillstyle(SOLID_FILL, col);
     bar(CURX,CURY,CURX+4,CURY+4);
     size = imagesize(CURX,CURY,CURX+4,CURY+4);
     if (cur>0) realloc(brushbuff,size);
     else brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+4,CURY+4,brushbuff);
     break;
  case 5:
     setfillstyle(SOLID_FILL, 7);
     bar(CURX,CURY,CURX+5,CURY+5);  /*brush 5*/
     csize = imagesize(CURX,CURY,CURX+5,CURY+5);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+5,CURY+5,cbuff);
     setfillstyle(SOLID_FILL, col);
     bar(CURX,CURY,CURX+5,CURY+5);
     size = imagesize(CURX,CURY,CURX+5,CURY+5);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+5,CURY+5,brushbuff);
     break;
  case 6:
     setfillstyle(SOLID_FILL, 7);
     bar(CURX,CURY,CURX+6,CURY+6);  /*brush 6*/
     csize = imagesize(CURX,CURY,CURX+6,CURY+6);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+6,CURY+6,cbuff);
     setfillstyle(SOLID_FILL, col);
     bar(CURX,CURY,CURX+6,CURY+6);
     size = imagesize(CURX,CURY,CURX+6,CURY+6);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+6,CURY+6,brushbuff);
     break;
  case 7:
     setfillstyle(SOLID_FILL, 7);
     bar(CURX,CURY,CURX+7,CURY+7);  /*brush 7*/
     csize = imagesize(CURX,CURY,CURX+7,CURY+7);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+7,CURY+7,cbuff);
     setfillstyle(SOLID_FILL, col);
     bar(CURX,CURY,CURX+7,CURY+7);
     size = imagesize(CURX,CURY,CURX+7,CURY+7);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+7,CURY+7,brushbuff);
     break;
  case 8:
     setfillstyle(LINE_FILL, 7);
     bar(CURX,CURY,CURX+8,CURY+8);  /*brush 8*/
     csize = imagesize(CURX,CURY,CURX+8,CURY+8);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+8,CURY+8,cbuff);
     setfillstyle(LINE_FILL, col);
     bar(CURX,CURY,CURX+8,CURY+8);
     size = imagesize(CURX,CURY,CURX+8,CURY+8);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+8,CURY+8,brushbuff);
     break;
  case 9:
     setfillstyle(CLOSE_DOT_FILL, 7);
     bar(CURX,CURY,CURX+9,CURY+9);  /*brush 9*/
     csize = imagesize(CURX,CURY,CURX+9,CURY+9);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+9,CURY+9,cbuff);
     setfillstyle(CLOSE_DOT_FILL, col);
     bar(CURX,CURY,CURX+9,CURY+9);
     size = imagesize(CURX,CURY,CURX+9,CURY+9);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+9,CURY+9,brushbuff);
     break;
  case 10:
     setfillstyle(CLOSE_DOT_FILL, 7);
     bar(CURX,CURY,CURX+10,CURY+10);  /*brush 10*/
     csize = imagesize(CURX,CURY,CURX+10,CURY+10);
     cbuff=malloc(csize);
     getimage(CURX,CURY,CURX+10,CURY+10,cbuff);
     setfillstyle(CLOSE_DOT_FILL, col);
     bar(CURX,CURY,CURX+10,CURY+10);
     size = imagesize(CURX,CURY,CURX+10,CURY+10);
     brushbuff=malloc(size);
     getimage(CURX,CURY,CURX+10,CURY+10,brushbuff);
     break;
  }
}

draw_it()
{
int c,radius;

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
	x1=act[c].a[0];
	y1=act[c].a[1];
	putimage(x1,y1,brushbuff,COPY_PUT);
	break;
      case 4:
	setfillstyle(1,lcolor);
	setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	x1=act[c].a[0];
	y1=act[c].a[1];
	x2=act[c].a[2];
	y2=act[c].a[3];
	line(x1,y1,x2,y2);
	break;
      case 5:
        setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	x1=act[c].a[0];
	y1=act[c].a[1];
	radius=act[c].a[2];
	circle(x1,y1,radius);
	break;
      case 6:
        setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	x1=act[c].a[0];
	y1=act[c].a[1];
	x2=act[c].a[2];
	y2=act[c].a[3];
	rectangle(x1,y1,x2,y2);
	break;
      case 7:
	x1=act[c].a[0];
	y1=act[c].a[1];
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
	     floodfill(x1,y1,border);
	   else
	     floodwfill(x1,y1,border,lcolor,mcolor);
	break;
      case 8:
	x1=act[c].a[0];
	y1=act[c].a[1];
	style=act[c].a[2];
	direction=act[c].a[3];
	tsize=act[c].a[4];
	settextstyle(style,direction,tsize);
	setusercharsize(tsize+1,1,tsize+1,1);
	outtextxy(x1,y1,act[c].str);
	break;
      case 9:
        setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	x1=act[c].a[0];
	y1=act[c].a[1];
	radx=act[c].a[2];
	rady=act[c].a[3];
	ellipse(x1,y1,SANG,EANG,radx,rady);
	break;
      case 10:
        setfillstyle(1,lcolor);
	x1=act[c].a[0];
	y1=act[c].a[1];
	x2=act[c].a[2];
	y2=act[c].a[3];
	bar(x1,y1,x2,y2);
	break;
      }     	/*end switch*/
   }		/*end for*/
}   /*end draw_it*/

save_file()
{
FILE *fptr;
char nm2[30],nm3[30];
char nm[30],lt,filnam[30],lt2;
int p,numdoor,op;
char px[3],py[3];
char objpic,objnum[11],objloc,objnam[11];
struct objects
  {
  char name[11];
  int p[4];
  int loc;
  int mov;
  };
struct objects obj[1];

op=0;
printf("(O)bject or (P)icture? ");
objpic=getche();
if (objpic=='O' || objpic=='o')
  {
  op=1;
  printf("Name for this object? ");
  gets(&objnam[0]);
  strcpy(obj[0].name,objnam);
  printf("Object number: ");
  gets(&objnum[0]);
  printf("Location where object can be found: ");
  gets(&objloc);
  obj[0].loc=atoi(&objloc);
  printf("object starting start point:\nPx: ");
  gets(&px[0]);
  printf("Py: ");
  gets(&py[0]);
  obj[0].p[0]=atoi(&px[0]);
  obj[0].p[1]=atoi(&py[0]);
  printf("object width/height:\nWidth: ");
  gets(&px[0]);
  printf("Height: ");
  gets(&py[0]);
  obj[0].p[2]=atoi(&px[0]);
  obj[0].p[3]=atoi(&py[0]);
  printf("Movement: (0-none -1=lt -2=rt 1=up 2=dn) ");
  gets(&px[0]);
  obj[0].mov=atoi(&px[0]);
  strcpy(filnam,"OBJ");
  strcat(filnam,objnum);
  strcpy(nm,filnam);
  strcat(filnam,".FIL");    		/*make object file*/
  if ( (fptr=fopen(filnam,"wb"))==NULL)
     {printf("Can't open file %s",filnam);  getch();}
  else
     {
     fwrite(obj,sizeof(obj[0]),1,fptr);
     }
  fclose(fptr);
  }
  else
  {
  printf("Keep same boundary points? (y/n) ");
  lt=getche();
  if (lt=='n' || lt=='N')
  {
  printf("Enter location boundary points:\n");
  for (p=0;p<4;p++)
    {
    printf("P%dx: ",p);
    gets(&px[p]);
    printf("P%dy: ",p);
    gets(&py[p]);
    pntx[p]=atoi(&px[p]);
    pnty[p]=atoi(&py[p]);
    }
  }  /*end keep same boundary points-no*/
  printf("Keep same door points? (y/n) ");
  lt2=getche();
  if (lt2=='n' || lt2=='N')
  {
  printf("How many doors? ");
  gets(&px[0]);
  numdoor=atoi(&px[0]);
  printf("Enter door boundary points:\n");
  for (p=0;p<numdoor;p++)
    {
    printf("x1: ");
    gets(&px[p]);
    printf("y1: ");
    gets(&py[p]);
    door[p].a[0]=atoi(&px[p]);
    door[p].a[1]=atoi(&py[p]);
    printf("x2: ");
    gets(&px[p]);
    printf("y2: ");
    gets(&py[p]);
    door[p].a[2]=atoi(&px[p]);
    door[p].a[3]=atoi(&py[p]);
    printf("visable door? (0-yes 1-no) ");
    gets(&px[0]);
    door[p].vis=atoi(&px[0]);
    printf("Door leads to loc #: ");
    gets(&px[0]);
    door[p].next=atoi(&px[0]);
    }	/*end for*/
  } 	/*end keep same door*/


}    /*end if - object or picture*/
if (op!=1)
  {
  printf("Name of picture/object: ");
  gets(nm);
  }
strcpy(nm2,nm);
strcpy(nm3,nm2);
strcat(nm,".pic");
if ( (fptr=fopen(nm,"wb"))==NULL)
   {printf("Can't open file %s",nm);  getch();}
else
   {
   act[cur].name=0;
   act[cur].a[0]=0;
   cur++;
   act[cur].name=1;
   act[cur].a[0]=0;
   cur++;
   fwrite(act,sizeof(act[0]),cur,fptr);
   savd=cur;	/*don't ask for saving each time no work is done*/
   }
fclose(fptr);
if (lt=='n' || lt=='N')
  {
  strcat(nm2,".EDG");			/*make boundary file*/
  if ( (fptr=fopen(nm2,"wb"))==NULL)
     {printf("Can't open file %s",nm2);  getch();}
  else
     {
     fwrite(pntx,sizeof(pntx[0]),4,fptr);
     fwrite(pnty,sizeof(pnty[0]),4,fptr);
     }
  fclose(fptr);
  }   /*end if we made new boundary points*/
if (lt2=='n' || lt2=='N')
  {
  strcat(nm3,".DOR");			/*make door file*/
  if ( (fptr=fopen(nm3,"wb"))==NULL)
     {printf("Can't open file %s",nm3);  getch();}
  else
     fwrite(door,sizeof(door[0]),10,fptr);
  fclose(fptr);
  }   /*end if we made new door points*/
ex=-1;
printf("done saving");
}

load_file()
{
FILE *fptr;
char name[30];
int a;

a=0;
printf("Name:");
gets(name);
if ( (fptr=fopen(name,"rb"))==NULL)
   {printf("Can't open file %s",name); getch(); }
else
   {
   while( fread(&act[a],sizeof(act[a]),1,fptr)==1)
      a++;
   fclose(fptr);
   cur=a;
   }
savd=cur;	/*don't ask for saving each time no work is done*/
ex=-1;
}
