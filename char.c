/*  	 char.c   */
/*       by Ted Huntington   */

/*  This program creates characters that */
/*  will be used in interactive graphic adventures  */

#ifdef DOS
#include "graphics.h"
#endif
#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#ifdef Linux
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#endif
#ifdef DOS
#include "conio.h"
#include "process.h"

#endif
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
#ifdef Linux
extern char *PATH;
char LPATH[] = {0x2f,'\0'};
#endif
#ifdef DOS
char PATH[256];
char LPATH[] = {0x5c,'\0'};
#endif
char cursor[2] = {0xdb, 0x00};
int hx1,hy1,hx2,hy2;        /*point coordinates*/
int lstyle;		/*line style*/
int style,direction,tsize;    /*text descriptions*/
int ex,ex2;			/*exit flags*/
int savd;			/*picture saved?*/
int midx,midy;		/*midpoint for circle*/
int radx,rady;		/*radii for ellipse*/
#ifdef Linux
short int skin[8];
#endif
#ifdef DOS
int skin[8];             /*characters attributes*/
#endif
char name[30],name2[30],name3[30];
char names[5][11] = {"Tara","Tan","Maria","Juan","Chana"};
int rep;    /*repeat load file- error*/
int qflg;
int univ,cursx,cursy;

#ifdef Linux
struct action         /*actions*/
   {
   short int name;  /*0-color,1-brush,2-lstyle,3-point,*/
	      /*4-line,5-circle,6-rect,7-fill,8-text*/
   short int a[5];   /*x1-color-brush,y1-style,x2-rad-direct-tsize,y2-strlen*/
   char str[SLEN];  /*string*/
   };
struct daction         /*dynamic actions*/
   {
   short int name;
   short int a[5];
   char str[SLEN];
   struct daction *next;
   };
#endif
#ifdef DOS

struct action         /*actions*/
   {
   int name;  /*0-color,1-brush,2-lstyle,3-point,*/
	      /*4-line,5-circle,6-rect,7-fill,8-text*/
   int a[5];   /*x1-color-brush,y1-style,x2-rad-direct-tsize,y2-strlen*/
   char str[SLEN];  /*string*/
   };
#endif

int cur;   /*current act*/

struct action act[NUMMOVE];
int bcrx[12];  /*beg cursor*/
int mcur[12];  /*max cur index*/
int crx,cry;
int curnum[12],cnt,lnum,fact[12],siz[12];
int bald;		/*bald flag*/


#ifdef Linux
Display *xdisplay;
Window xwindow;
int xscreen;
unsigned long xforeground, xbackground;
XEvent xevent;
GC xgc;
Colormap cmap;
XColor color, colorrgb;

Pixmap pixmap[3];
int depth;
XImage *fximage;
XImage *TitleImage;
Visual *visual;
int lincolor;
int linbrush;
int linpat;
unsigned int *pmp;
XFontStruct *font_info;
char *font_name;
char **font_path;
int font_path_num;

int *x_return, *y_return;
unsigned int *width_return, *height_return;
unsigned int *border_width_return;
unsigned int *depth_return;
Window *root_win;
unsigned int mixcolor,bordercolor;

XImage *man[8];		/*pointer to character image*/
XImage *screen[7+NUMMOBJ];       /*pointer to background for images*/
XImage *screen3[2];       /*pointer to background for images*/
XImage *heli[5];		/*pointer to heli images*/
XImage *lines3[17];
XImage *car[NUMCAR];
XImage *road[NUMROAD];
XImage *spike[NUMSPIKE];
XImage *robot[8];    	/*background lines  17-char 37-heli*/
XImage *lines[170];	    /*37*4= 148+17=165*/

char dash_list[] = {1,3};//{2,3}; 
unsigned int *klmap;
FILE *input;
FILE *output;
int status;
char Key;
//unsigned char **hpat;
unsigned char hpat[16][9];
int sp10;
char *tpstr;
//prototypes
//void floodlinpatfill3(short int sx,short int sy, unsigned char lcx,unsigned char lcy);
void floodlinpatfill3(short int sx,short int sy, unsigned char lcx,unsigned char lcy,int recur);
#endif




#ifdef DOS
main()
{
#endif
#ifdef Linux
main(int argc, char *argv[])
{
#endif
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
#ifdef Linux
int a,b;
char title[]="2020 Human Maker";
char icon_title[]="2020";
FILE *fptr;
#endif



#ifdef Linux
root_win=(Window *)malloc(sizeof(Window));
x_return=(int *)malloc(20);
y_return=(int *)malloc(20);
width_return=(unsigned int *)malloc(20);
height_return=(unsigned int *)malloc(20);
border_width_return=(unsigned int *)malloc(20);
depth_return=(unsigned int *)malloc(20);

font_path=(char **)malloc(1000);
font_name=malloc(255);
//hpat=(unsigned char **)malloc(4*16);
//for(b=0;b<16;b++)
//{
//hpat[b]=(unsigned char *)malloc(8);
//}
//sprintf(hpat[0],"%c%c%c%c%c%c%c%c",0x0f,0x0f,0x0f,0x0f,0xf0,0xf0,0xf0,0xf0); 
//above is checker
sprintf(hpat[0],"%c%c%c%c%c%c%c%c",0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55);
//pattern 0 is on some cars
//9d,3a,74,e8,d1,23,47,8e
sprintf(hpat[1],"%c%c%c%c%c%c%c%c",0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff);
sprintf(hpat[2],"%c%c%c%c%c%c%c%c",0x33,0x66,0xcc,0x99,0x33,0x66,0xcc,0x99);
sprintf(hpat[3],"%c%c%c%c%c%c%c%c",0x22,0x44,0x88,0x11,0x22,0x44,0x88,0x11);
sprintf(hpat[4],"%c%c%c%c%c%c%c%c",0x22,0x44,0x88,0x11,0x22,0x44,0x88,0x11);
sprintf(hpat[5],"%c%c%c%c%c%c%c%c",0x22,0x44,0x88,0x11,0x22,0x44,0x88,0x11);
sprintf(hpat[6],"%c%c%c%c%c%c%c%c",0x93,0x27,0x4e,0x9c,0x39,0x72,0xe4,0xc9);
sprintf(hpat[7],"%c%c%c%c%c%c%c%c",0x11,0x11,0x11,0xff,0x11,0x11,0x11,0xff);
sprintf(hpat[8],"%c%c%c%c%c%c%c%c",0x18,0x24,0x42,0x81,0x81,0x42,0x24,0x18);
sprintf(hpat[9],"%c%c%c%c%c%c%c%c",0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55);
sprintf(hpat[10],"%c%c%c%c%c%c%c%c",0x22,0x44,0x88,0x11,0x22,0x44,0x88,0x11);
sprintf(hpat[11],"%c%c%c%c%c%c%c%c",0x22,0x44,0x88,0x11,0x22,0x44,0x88,0x11);

sprintf(hpat[12],"%c%c%c%c%c%c%c%c",0x18,0x3c,0x7e,0xff,0xff,0x7e,0x3c,0x18);
sprintf(hpat[13],"%c%c%c%c%c%c%c%c",0x00,0xf7,0xf7,0xf7,0x00,0x7f,0x7f,0x7f);
sprintf(hpat[14],"%c%c%c%c%c%c%c%c",0xee,0xee,0xee,0xee,0xe0,0xee,0xee,0x0e);
sprintf(hpat[15],"%c%c%c%c%c%c%c%c",0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55);

sprintf(hpat[10],"%c%c%c%c%c%c%c%c",0xe0,0xfb,0x0b,0x6b,0x0f,0xef,0xef,0xff);
//tp


pmp=(unsigned int *)malloc(81*301); //81*301);
//PATH=malloc(256);
set2020path();
klmap=(unsigned int *)malloc(16*4);
klmap[0]=0x0;
klmap[1]=0x000000a8;
klmap[2]=0x0000a800;
klmap[3]=0x0000a8a8;
klmap[4]=0x00a80000;
klmap[5]=0x00a800a8;
klmap[6]=0x00a85400;
klmap[7]=0x00a8a8a8;
klmap[8]=0x00545454;
klmap[9]=0x005454fc;
klmap[10]=0x0054fc54;
klmap[11]=0x0054fcfc;
klmap[12]=0x00fc5454;
klmap[13]=0x00fc54fc;
klmap[14]=0x00fcfc54;
klmap[15]=0x00ffffff;


input = fopen("/dev/tty", "r");      //open the terminal keyboard
output = fopen("/dev/tty", "w");     //open the terminal screen

if (!input || !output)
  {
  fprintf(stderr, "Unable to open /dev/tty\n");
  exit(1);
  }

tpstr=malloc(20);



        /* connect to the X server */
        xdisplay = XOpenDisplay ("");

        if (xdisplay == NULL) {
                fprintf (stderr, "cannot connect to server\n");
                exit (EXIT_FAILURE);
        }

        /* get default screen */
        xscreen = DefaultScreen (xdisplay);

        /* get black and white representation on current screen */
        xbackground = BlackPixel (xdisplay, xscreen);
        xforeground = WhitePixel (xdisplay, xscreen);

        /* Create window at (0,0), width 650, height 350, border width
           2, in default root  */
        xwindow = XCreateSimpleWindow (xdisplay,
                DefaultRootWindow(xdisplay), 0, 0, 640, 350, 2,
                xforeground, xbackground);

        if (xwindow == 0) {
                fprintf (stderr, "cannot open window\n");
                exit (EXIT_FAILURE);
        }

        XSetStandardProperties(xdisplay,xwindow,title,icon_title,None,argv,argc,NULL);


        /* ask for exposure event */
        XSelectInput(xdisplay, xwindow, ExposureMask|KeyPressMask|ButtonPressMask);

        /* pop this window up on the screen */
        XMapRaised (xdisplay, xwindow);


        /* wait for the window showing up before continuing */
        XNextEvent (xdisplay, &xevent);



        /* set graphics context of rectangle to red */
        xgc= XCreateGC (xdisplay, xwindow, 0, 0);

        if (DisplayPlanes (xdisplay, xscreen) != 1) {
                cmap = DefaultColormap (xdisplay, xscreen);
                if (XAllocNamedColor (xdisplay, cmap, "white", &color, &colorrgb))
                        XSetForeground (xdisplay, xgc, color.pixel);
        }



//font_name="*-helvetica-*-12-*";
strcpy(font_name,"*charter*");
font_info=XLoadQueryFont(xdisplay,font_name);
if (!font_info)
   {
   fprintf(stderr, "Could not load font\n");
   exit(1);
   }
XSetFont(xdisplay,xgc,font_info->fid);


      //  XFillRectangle (xdisplay, xwindow, xgc, 0, 0,640, 300);

depth = DefaultDepth(xdisplay, DefaultScreen(xdisplay));
visual=DefaultVisual(xdisplay,DefaultScreen(xdisplay));

pixmap[0] = XCreatePixmap(xdisplay, xwindow, 640,350, depth);
        XFlush (xdisplay);


XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,300);
XSetForeground (xdisplay, xgc, 0x0);
//XFillRectangle (xdisplay, pixmap[0],xgc,0,300,640,50);
XFillRectangle (xdisplay, pixmap[0],xgc,0,200,640,150);


#endif



#ifdef DOS
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
#endif


ex2=0;
cur=0;
brush=0;
hx1=hy1=100;       /*set current coord*/
lcolor=0;
savd=0;
ex=0;
lnum=0;
for(cnt=0;cnt<12;cnt++) curnum[cnt]=0;
curnum[0]=1;
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,300);
XSetForeground (xdisplay, xgc, 0x0);
//XFillRectangle (xdisplay, pixmap[0],xgc,0,300,640,50);
XFillRectangle (xdisplay, pixmap[0],xgc,0,200,640,150);

#endif
#ifdef DOS
setactivepage(0);
setvisualpage(1);
setusercharsize(1,1,1,1);
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
setcolor(15);
setfillstyle(SOLID_FILL, 15);
bar(0,0,640,300);   /*white top */
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
#endif
load_file("char0.pic");  /*char0.pic*/

lcolor=0;
draw_it();

/*setcolor(15);
setfillstyle(SOLID_FILL, 15);
draw_rex();*/
#ifdef DOS
randomize();		/*activate random number generator*/
#endif



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
#ifdef DOS
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
setvisualpage(0);
#endif

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
#ifdef DOS
    setactivepage(1);
#endif
#ifdef Linux
    load_file("Char1.pic");
#endif
#ifdef DOS
    load_file("char1.pic");
#endif
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,300);
XSetForeground (xdisplay, xgc, 0x0);
//XFillRectangle (xdisplay, pixmap[0],xgc,0,300,640,50);
//XFillRectangle (xdisplay, pixmap[0],xgc,0,200,640,150);
XFillRectangle (xdisplay, pixmap[0],xgc,0,290,640,160);
#endif
#ifdef DOS
    setfillstyle(SOLID_FILL, 15);
    bar(0,0,640,300);   /*white top */
    setfillstyle(SOLID_FILL, 0);
    bar(0,301,640,350);   /*black bottom */
#endif
    draw_it();
#ifdef DOS
    setfillstyle(SOLID_FILL, 0);
    bar(0,301,640,350);   /*black bottom */
    setvisualpage(1);
#endif
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
#ifdef DOS
getcwd(PATH,512);
#endif
strcat(PATH,LPATH);

if (univ==2)   /*default character*/
  {
  strcpy(tfil,PATH);
  strcpy(lfname,name);
  lfname[8]=0;
  strcat(tfil,lfname);
  strcpy(nm,tfil);
  strcpy(tfil,PATH);
#ifdef Linux
  strcat(tfil,"Def");
#endif
#ifdef DOS
  strcat(tfil,"DEF");
#endif
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
     
#ifdef Linux

      strcat(name3,".pic");
#endif
#ifdef DOS
      strcat(name3,".PIC");
#endif
      load_file(name3);
#ifdef Linux
      load_traits(name);  //this could be an error in DOS
#endif
#ifdef DOS
      load_traits(name2);	/*load traits to save for 2020 to load*/
#endif


      strcpy(tfil,PATH);
#ifdef Linux
      strcat(tfil,"Def");
#endif
#ifdef DOS
      strcat(tfil,"DEF");
#endif
      save_traits(tfil);	/*save traits for 2020 to load*/
      strcpy(nm,PATH);
#ifdef Linux
      strcat(nm,"Def.pic");
#endif
#ifdef DOS
      strcat(nm,"DEF.PIC");
#endif
      save_file(nm);
#ifdef DOS
      closegraph();
#endif
      exit(0);
      }
   else
      if (univ==0)   /*new character*/
	 {
/*	 strcpy(name,"test");*/
	 strcpy(tfil,PATH);
	 strcat(tfil,name);
	 strcpy(name2,tfil);
#ifdef Linux
	 strcat(name2,".pic");
#endif
#ifdef DOS
	 strcat(name2,".PIC");
#endif


#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,300);
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0],xgc,0,300,640,50);
//XFillRectangle (xdisplay, pixmap[0],xgc,0,200,640,150);
#endif

#ifdef DOS
	 setactivepage(0);
	 setfillstyle(SOLID_FILL, 15);
	 bar(0,0,640,32);   /*white top */
#endif
	 draw_char();
	 strcpy(nm,name2);
	 save_file(nm);
	 strcpy(nm,PATH);
#ifdef Linux
	 strcat(nm,"Def.pic");
#endif
#ifdef DOS
	 strcat(nm,"DEF.PIC");
#endif
	 save_file(nm);
	 strcpy(nm,PATH);
#ifdef Linux
	 strcat(nm,"Def");
#endif
#ifdef DOS
	 strcat(nm,"DEF");
#endif
	 save_traits(nm);	/*save traits for 2020 to load*/
	 strcpy(nm,PATH);
	 strcat(nm,name);
	 save_traits(nm);	/*save traits for later loading*/
#ifdef DOS
	 closegraph();
#endif
	 exit(0);
	 }
      else
	{
	if (univ==3)   /*same character*/
	  {
#ifdef DOS
	  closegraph();
#endif
	  exit(0);
	  }
      else ex=0;   /*not valid-stay in loop*/
   }
cur=0;
brush=0;
hx1=hy1=100;       /*set current coord*/
ex2=0;
lcolor=0;
savd=0;
ex=0;
#ifdef DOS
if (univ==0) setactivepage(0);
else setactivepage(1);
setusercharsize(1,1,1,1);
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
setcolor(15);
setfillstyle(SOLID_FILL, 15);
#endif

oldcolor=lcolor;
lcolor=15;
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,300);
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0],xgc,0,300,640,50);
//XFillRectangle (xdisplay, pixmap[0],xgc,0,200,640,150);
#endif

#ifdef DOS
setlinestyle(0,ULIN1,1);
setfillstyle(SOLID_FILL, 15);
bar(0,0,640,32);   /*white top */
#endif
lcolor=oldcolor;

draw_char();
if (cur>0) draw_it();
strcpy(tfil,PATH);
#ifdef Linux
strcat(tfil,"Def.pic");
#endif
#ifdef DOS
strcat(tfil,"DEF.PIC");
#endif
save_file(tfil);

#ifdef DOS
closegraph();
#endif
exit(0);
}                              /*end main*/

doname()
{
int ex;
char ch,key[2],command[37];

  ex=0;
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XDrawString(xdisplay,pixmap[0],xgc,56,112+(font_info->ascent+font_info->descent)/2,"Name:",5);

#endif
#ifdef DOS
  setcolor(15);
  setfillstyle(SOLID_FILL,0);
  settextstyle(0,0,2);
  outtextxy(56,112,"Name:");
#endif
  cursx=160;  cursy=112;
  draw_cursor();
  strcpy(command,"");
  while (ex!=1)
  {
#ifdef Linux
status=0;
  while(status==0)
   {
   XNextEvent (xdisplay, &xevent);

   switch (xevent.type) 
    {
   /* ignore this event */
   case Expose:
     break;
   case ButtonPress:
     //status=1;
     break;
   case KeyPress:
     status=1;
     ch=XLookupKeysym(&xevent.xkey,0);
     //ch2=ch;
     key[0]=ch;
     key[1]=0;
     //fprintf(stderr,"got key %x ",ch);
     break;
    }  //end switch
   }  //end while


#endif
#ifdef DOS
    ch = getch();
    key[0]=ch;  key[1]=0;
    if (ch == 0)  getch();
#endif
    switch (ch)
      {
      case 8:			/*  backspace*/
	if (cursx>175)
	  {
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0], xgc, cursx+50-16,cursy-5,32,16);
#endif
#ifdef DOS
	  setfillstyle(SOLID_FILL,0);
	  bar(cursx-16,cursy,cursx+16,cursy+16);
#endif
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
#ifdef Linux
	XSetForeground (xdisplay, xgc, 0x00ffffff);
	XFillRectangle (xdisplay, pixmap[0], xgc, cursx+50,cursy-5,16,16);
	XSetForeground (xdisplay, xgc, 0x0);
	XDrawString(xdisplay,pixmap[0],xgc,cursx+50,cursy-1+(font_info->ascent+font_info->descent)/2,key,1);
#endif
#ifdef DOS
	  setcolor(15);
	  setfillstyle(SOLID_FILL,0);
	  settextstyle(0,0,2);
	  bar(cursx,cursy,cursx+16,cursy+16);  /*blackout cursor*/
	  outtextxy(cursx,cursy,key);
#endif
	  cursx=cursx+16;
	  strcat(command,key);
	  draw_cursor();
	  }
	break;
      }                            /*end switch*/
   }                           /*end while*/
}


#ifdef Linux
ShowScreenF()
{
unsigned int nukl;
XImage *fximage2;
int a,b;
int th,tw;
Pixmap lpixmap;

//only have to erase the character, possibly robot, and cars

XGetGeometry(xdisplay, xwindow, root_win, x_return, y_return, width_return,height_return, border_width_return, depth_return);

th=*height_return; 
tw=*width_return;  
//fprintf(stderr,"w=%d h=%d\n",tw,th);
if (tw==640 && th==350)
{
XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,0,640,300,0, 0);
}
#if 0 
else
{
th=th*.857;
//scale pixmap[0] to lpixmap
if (fximage>0) {XDestroyImage(fximage);}
fximage=XGetImage(xdisplay,pixmap[0],0,0,640,300,AllPlanes,ZPixmap);
fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,tw,th,8,0);
fximage2->data=(char *)malloc(fximage2->bytes_per_line*th+16);
for(a=0;a<tw;a++)
  for(b=0;b<th;b++)
    {
    nukl=XGetPixel(fximage,a*640/tw,b*300/th);
    XPutPixel(fximage2,a,b,nukl);
 //copy using ->data[?]
    }


lpixmap = XCreatePixmap(xdisplay, xwindow, tw,th, depth);
XPutImage(xdisplay,lpixmap,xgc,fximage2,0,0,0,0,tw,th);

free(fximage2->data);
//XDestroyImage(fximage2);  //problem?
//XDestroyImage(fximage);

XCopyArea(xdisplay, lpixmap, xwindow, xgc,0, 0,tw,th,0, 0); 
XFreePixmap(xdisplay,lpixmap);

}  //end if then else
#endif

XFlush (xdisplay);

}
#endif




draw_cursor()
{
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0], xgc, cursx+50,cursy-5,16,16);
//XFillRectangle (xdisplay, pixmap[0], xgc, cursx,cursy+5,16,20);
//ShowScreen2();
ShowScreenF();

#endif
#ifdef DOS
setcolor(15);
setactivepage(page);
outtextxy(cursx,cursy,cursor);
setactivepage(!page);
outtextxy(cursx,cursy,cursor);
#endif
}


#if 0 
draw_cursor()
{
setcolor(15);
outtextxy(cursx,cursy,cursor);
}
#endif

doline0()
{
char ch1,ch2;

ex=0;
while(ex!=1)
 {
#ifdef Linux
status=0;
  while(status==0)
   {
   XNextEvent (xdisplay, &xevent);

   switch (xevent.type) 
    {
   /* ignore this event */
   case Expose:
     break;
   case ButtonPress:
     //status=1;
     break;
   case KeyPress:
     status=1;
     ch1=XLookupKeysym(&xevent.xkey,0);
     ch2=ch1;
     //key[0]=ch1;
     //key[1]=0;
     //fprintf(stderr,"%x ",ch1);
     break;
    }  //end switch
   }  //end while
  //if (1) {
#endif
#ifdef DOS
 ch1=getch();
 if (ch1==0)
  {
  ch2=getch();                                      /*left*/
#endif
#ifdef Linux
   if (ch2==81)
#endif
#ifdef DOS
  if (ch2==75)  
#endif
    {  if (curnum[lnum]==0)  {bbox(); curnum[lnum]=mcur[lnum];
					crx=crx+mcur[lnum]*fact[lnum];wbox();}
		   else {bbox(); curnum[lnum]--; crx=crx-fact[lnum]; wbox();}}
  else
    {
#ifdef Linux
   if (ch2==83)
#endif
#ifdef DOS                                             /*right*/
    if (ch2==77)  
#endif
    {if (curnum[lnum]==mcur[lnum]) {bbox(); curnum[lnum]=0;
						crx=bcrx[lnum]; wbox();}
		   else {bbox(); curnum[lnum]++; crx=crx+fact[lnum]; wbox();}}
    }
#ifdef DOS
  }
 else
  {
#endif
  if (ch1==13)  { if (curnum[lnum]==0) {system("tapimv2>out.out");
		  system("vmp>out.out");system("audiomat>out.out");}
		   ex=1;lnum++; }
#ifdef DOS
  }
#endif
 }
}

doline1()
{
char ch1,ch2;

ex=0;
while(ex!=1)
 {
#ifdef Linux
//fprintf(stderr,"here");
status=0;
  while(status==0)
   {
   XNextEvent (xdisplay, &xevent);

   switch (xevent.type) 
    {
   /* ignore this event */
   case Expose:
     break;
   case ButtonPress:
     //status=1;
     break;
   case KeyPress:
     status=1;
     ch1=XLookupKeysym(&xevent.xkey,0);
     ch2=ch1;
     //key[0]=ch;
     //key[1]=0;
     //fprintf(stderr,"%x ",ch1);
     break;
    }  //end switch
}//end while status
#endif
#ifdef DOS
ch1=getch();
if (ch1==0)
  {
  ch2=getch();                                      /*left*/
#endif
#ifdef Linux
   if (ch2==81)
#endif
#ifdef DOS
  if (ch2==75)  
#endif
    {  if (curnum[lnum]==0)  {bbox(); curnum[lnum]=mcur[lnum];
					crx=crx+mcur[lnum]*fact[lnum];wbox();}
		   else {bbox(); curnum[lnum]--; crx=crx-fact[lnum]; wbox();}}
  else
    {                                             /*right*/
#ifdef Linux
   if (ch2==83)
#endif
#ifdef DOS
    if (ch2==77)  
#endif
        {if (curnum[lnum]==mcur[lnum]) {bbox(); curnum[lnum]=0;
						crx=bcrx[lnum]; wbox();}
		   else {bbox(); curnum[lnum]++; crx=crx+fact[lnum]; wbox();}}
    }
#ifdef DOS
  }
else
  {
#endif
  if (ch1==13)  { ex=1;
		  switch(curnum[lnum])
		  {  case 0: donew(); break;
		     case 1: doold(); break;
		     case 2: doran(); break;
		     case 3: dosam(); break;
		  }
		  lnum++;
		}
#ifdef DOS
  }
#endif
 }
}

doline()
{
char ch1,ch2;

ex=0;
while(ex!=1)
 {
#ifdef Linux
status=0;
  while(status==0)
   {
   XNextEvent (xdisplay, &xevent);

   switch (xevent.type) 
    {
   /* ignore this event */
   case Expose:
     break;
   case ButtonPress:
     //status=1;
     break;
   case KeyPress:
     status=1;
     ch1=XLookupKeysym(&xevent.xkey,0);
     ch2=ch1;
     //key[0]=ch;
     //key[1]=0;
     //fprintf(stderr,"%x ",ch1);
     break;
    }  //end switch
  }  //end while
#endif
#ifdef DOS
ch1=getch();
if (ch1==0)
  {
  ch2=getch();                                      /*left*/
#endif
#ifdef Linux
   if (ch2==81)
#endif
#ifdef DOS
  if (ch2==75)  
#endif
      {  if (curnum[lnum]==0)  {bbox(); curnum[lnum]=mcur[lnum];
					crx=crx+mcur[lnum]*fact[lnum];wbox();}
		   else {bbox(); curnum[lnum]--; crx=crx-fact[lnum]; wbox();}}
  else
    {                                             /*right*/
#ifdef Linux
   if (ch2==83)
#endif
#ifdef DOS
    if (ch2==77)  
#endif
        {if (curnum[lnum]==mcur[lnum]) {bbox(); curnum[lnum]=0;
						crx=bcrx[lnum]; wbox();}
		   else {bbox(); curnum[lnum]++; crx=crx+fact[lnum]; wbox();}}
    }
#ifdef DOS
  }
else
  {
#endif
  if (ch1==13)  { skin[lnum-3]=curnum[lnum]; if (lnum==7||lnum==8||lnum==10)
		  skin[lnum-3]=!curnum[lnum]; lnum++; ex=1;}
#ifdef DOS
  }
#endif
 }
}


bbox()
{
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x0);
XDrawRectangle(xdisplay, pixmap[0],xgc,crx,cry,siz[lnum],20);
ShowScreenF();
#endif
#ifdef DOS
setcolor(0);
rectangle(crx,cry,crx+siz[lnum],cry+20);
#endif
}

wbox()
{
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffff00);
XDrawRectangle(xdisplay, pixmap[0],xgc,crx,cry,siz[lnum],20);
ShowScreenF();
#endif
#ifdef DOS
setcolor(5);
rectangle(crx,cry,crx+siz[lnum],cry+20);
#endif
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
#ifdef Linux
srand(time(0));
strcpy(name,names[(int)(5.0*((float)rand()/(float)RAND_MAX))]);
#endif
#ifdef DOS
strcpy(name,names[random(5)]);
#endif
}

dosam()
{
univ=3;
}

draw_cbrush(int lbrush,int col)
{
#ifdef DOS
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
#endif
}

randall()
{
#ifdef Linux
//fprintf(stderr,"Randomize");
  srand(time(0));

  skin[0]=(int)(5.0*((float)rand()/(float)RAND_MAX));
 // fprintf(stderr,"rand=%d %f\n",skin[0],(float)rand()/(float)RAND_MAX);

  //srand(1000);
  srand(time(0)*2);
  skin[1]=(int)(5.0*((float)rand()/(float)RAND_MAX));

  //srand(1001);
  srand(time(0)*3);
  skin[2]=(int)(4.0*((float)rand()/(float)RAND_MAX));

  if (skin[2]==3)
    {
    bald=1;
    skin[2]=0;
    }
  else bald=0;
  //srand(1002);
  srand(time(0)*3);
  skin[3]=(int)(3.0*((float)rand()/(float)RAND_MAX));
  srand(time(0)*4);
  //srand(1003);
  skin[4]=(int)(2.0*((float)rand()/(float)RAND_MAX));
  //srand(1003);
  srand(time(0)*5);
  skin[5]=(int)(2.0*((float)rand()/(float)RAND_MAX));
  //srand(time(0));
  srand(time(0)*6);
  skin[6]=(int)(6.0*((float)rand()/(float)RAND_MAX));
  //srand(time(0));
  srand(time(0)*7);
  skin[7]=(int)(2.0*((float)rand()/(float)RAND_MAX));
  //srand(time(0));
  srand(time(0)*8);
  skin[8]=(int)(6.0*((float)rand()/(float)RAND_MAX));
#endif
#ifdef DOS
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
#endif
}

#ifdef DOS
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
#endif

save_file(char lname[30])
{
FILE *fptr;

if ( (fptr=fopen(lname,"wb"))==NULL)
#ifdef Linux
{fprintf(stderr,"No file %s",lname);}
#endif
#ifdef DOS
   {printf("Error opening file %s",lname);  getch();}
#endif
else
   {
   fwrite(act,sizeof(act[0]),cur,fptr);
   ex=1;
   }
fclose(fptr);
}

save_traits(char lname[512])
{
int outhandle, bytes;
char lnm2[512];
FILE *fptr;



strcpy(lnm2,lname);
#ifdef Linux
strcat(lnm2,".txt");
#endif
#ifdef DOS
strcat(lnm2,".TXT");
if ( (outhandle = open(lnm2,O_CREAT)) < 0)
#endif

#ifdef Linux

  fptr=fopen(lnm2,"wb");
  if (!fptr) {
	printf("Error opening file %s",lnm2);
  }
//fprintf(stderr,"name= %s\n",lname);
#endif
#ifdef DOS
   {printf("Error opening file %s",lnm2);  getch();}
else
   {
#endif
   bytes=11;
#ifdef Linux
//  strncat(name,"           ",11-strlen(name));
  //name[strlen(name)]=0;
  fwrite(&name,1,bytes,fptr);
#endif
#ifdef DOS
   write(outhandle,name,bytes);    /*character name*/
   }
#endif

#ifdef Linux
fclose(fptr);
#endif
#ifdef DOS
close(outhandle);
#endif
strcpy(lnm2,lname);
#ifdef Linux
strcat(lnm2,".trt");
#endif
#ifdef DOS
strcat(lnm2,".TRT");
#endif
if ( (fptr=fopen(lnm2,"wb"))==NULL)
#ifdef Linux
{fprintf(stderr,"No file %s\n",lnm2);}
#endif
#ifdef DOS
   {printf("Error opening file %s",lnm2);  getch();}
#endif
else
   fwrite(skin,sizeof(skin[0]),8,fptr);
fclose(fptr);
ex=1;
}

load_file(char lname[11])
{
FILE *fptr;
int a;
char tmpstr[255];

strcpy(tmpstr,PATH);
strcat(tmpstr,LPATH);
strcat(tmpstr,lname);
a=0;
if ( (fptr=fopen(tmpstr,"rb"))==NULL)
#ifdef Linux
    {fprintf(stderr,"No file %s",tmpstr);}
#endif
#ifdef DOS
   {printf("Error opening file %s",tmpstr); getch(); }
#endif
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

load_traits(char lname[11])
{
#define BUFF1 11
#define BUFF2 8
char buff[BUFF1],buffs[BUFF2];
int inhandle,a;
char lnm2[512];
FILE *fptr;
#ifdef Linux
char d;
char *tempst;
char *newname;
#endif

a=0;
#ifdef DOS
getcwd(PATH,512);
#endif
strcat(PATH,LPATH);
strcpy(lnm2,PATH);

//#ifdef DOS
strcat(lnm2,lname);
#ifdef Linux
strcat(lnm2,".txt");
#endif
#ifdef DOS
strcat(lnm2,".TXT");
#endif
//#endif


if ( (inhandle=open(lnm2,O_RDONLY))<0)
   {
#ifdef DOS
printf("Error opening file %s",lnm2); 
#endif
#ifdef Linux
fprintf(stderr,"Error opening file %s",lnm2); 
#endif
#ifdef DOS
    getch(); 
#endif
}
else
   {
   read(inhandle,name,BUFF1);
   }
close(inhandle);
strcpy(lnm2,PATH);
strcat(lnm2,lname);
#ifdef Linux

//strcat(lnm2,newname);
strcat(lnm2,".trt");
#endif
#ifdef DOS
strcat(lnm2,".TRT");
#endif
if ( (fptr=fopen(lnm2,"rb"))==NULL)
   {printf("Error opening file %s",lnm2); 
#ifdef Linux
//free(newname);
//  while (fread(&Key,1,1,input)!=1) {}
#endif
#ifdef DOS
    getch(); 
#endif
}
else
   {
   while( fread(&skin[a],sizeof(skin[a]),1,fptr)==1 && a<8)
      a++;
   }
fclose(fptr);
#ifdef Linux
//free(newname);
#endif

}


#if 0
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
#ifdef Linux
strcat(lnm2,".txt");
#endif
#ifdef DOS
strcat(lnm2,".TXT");
#endif
if ( (inhandle=open(lnm2,O_RDONLY))<0)
   {printf("Can't open file %s",lnm2); getch(); }
else
   read(inhandle,name,BUFF1);
close(inhandle);
strcpy(lnm2,lname);
#ifdef Linux
strcat(lnm2,".trt");
#endif
#ifdef DOS
strcat(lnm2,".TRT");
#endif
if ( (fptr=fopen(lnm2,"rb"))==NULL)
   {printf("Can't open file %s",lnm2); getch(); }
else
   {
   while( fread(&skin[a],sizeof(skin[a]),1,fptr)==1 && a<8)
      a++;
   }
fclose(fptr);
}
#endif


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
#ifdef Linux
int xx1,xx2,yy1,yy2;
int a,b;
#endif

brush=0;
lcolor=0;
#ifdef DOS
setcolor(lcolor);
setlinestyle(0,ULIN1,1);
draw_cbrush(brush,lcolor);        /*get current color and size brush*/
#endif

#ifdef Linux
XSetForeground (xdisplay, xgc, 0x0);
XSetLineAttributes(xdisplay, xgc,1, LineSolid, CapButt|CapProjecting, JoinMiter);
#endif


for (c=0;c<cur;c++)
   {
//fprintf(stderr,"%d=%d  ",c,act[c].name);
   switch (act[c].name)
      {
      case 0:
	lcolor=act[c].a[0];
#ifdef Linux
	lincolor=klmap[lcolor];
	XSetForeground (xdisplay, xgc, lincolor);
#endif
#ifdef DOS
	setcolor(lcolor);
	setfillstyle(1,lcolor);
	draw_cbrush(brush,lcolor);    /*get current color and size brush*/
#endif

	break;
      case 1:
	brush=act[c].a[0];
#ifdef Linux
  	XSetLineAttributes(xdisplay, xgc,2*(brush>0)+1, LineSolid, CapButt|CapProjecting, JoinMiter);
	linbrush=brush;
#endif        
#ifdef DOS
	draw_cbrush(brush,lcolor);    /*get current color and size brush*/
#endif
	break;
      case 2:
	lstyle=act[c].a[0];
#ifdef Linux
	XSetDashes(xdisplay,xgc,0,dash_list,2);
	if (lstyle==0)
	  {
	  XSetLineAttributes(xdisplay, xgc,2*(brush>0)+1, LineSolid, CapButt|CapProjecting, JoinMiter);
	  }
	else
	  {
	  XSetLineAttributes(xdisplay, xgc,1, LineOnOffDash, CapButt|CapProjecting, JoinMiter);
	  }
#endif
#ifdef DOS
	setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
#endif
	break;
      case 3:
	a1=act[c].a[0];
	b1=act[c].a[1];
#ifdef Linux
//square brush
if (linbrush>0)
{
if (linbrush==7 || linbrush==10) {sp10=0;}  //10 is the title page statue
for(a=a1;a<a1+linbrush+1;a++)
 {
  for(b=b1;b<b1+linbrush+1;b++)

    {
    if (linbrush==10)
      {
      if ((sp10+b)&3>0 && (b&1>0))
        {
        XDrawPoint(xdisplay, pixmap[0], xgc, a, b);
        }
      else
        {
	XSetForeground (xdisplay, xgc, 0);
        XDrawPoint(xdisplay, pixmap[0], xgc, a, b);
	XSetForeground (xdisplay, xgc, lincolor);
        }
        if (b&1>0)
          {
	  if (sp10==7)
            sp10=0;
          else
            sp10++;
          }
       }
    else
       {
       XDrawPoint(xdisplay, pixmap[0], xgc, a, b);
        }
    }
 }
}

if (linbrush==0)  //1 point
 XDrawPoint(xdisplay, pixmap[0], xgc, a,b);
#endif
#ifdef DOS
	putimage(a1,b1,brushbuff,COPY_PUT);
#endif
	break;
      case 4:
	a1=act[c].a[0];
	b1=act[c].a[1];
	a2=act[c].a[2];
	b2=act[c].a[3];
#ifdef Linux
	XDrawLine(xdisplay, pixmap[0], xgc, a1,b1,a2,b2);
#endif
#ifdef DOS
	setfillstyle(1,lcolor);
	setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	line(a1,b1,a2,b2);
#endif
	break;
      case 5:
	a1=act[c].a[0];
	b1=act[c].a[1];
	radius=act[c].a[2];
#ifdef Linux
        XDrawArc(xdisplay,pixmap[0], xgc, a1-radius, b1-radius, radius*2, radius*2, 0, 360*64);
#endif
#ifdef DOS
        setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	circle(a1,b1,radius);
#endif
	break;
      case 6:
	a1=act[c].a[0];
	b1=act[c].a[1];
	a2=act[c].a[2];
	b2=act[c].a[3];
#ifdef Linux
        xx1=a1;  xx2=a2;  yy1=b1;  yy2=b2;
        if (xx1>xx2)  { xx2=xx1;  xx1=act[c].a[2]; }
        if (yy1>yy2)  { yy2=yy1;  yy1=act[c].a[3]; }
        XDrawRectangle(xdisplay,pixmap[0], xgc, xx1, yy1, xx2-xx1, yy2-yy1);
#endif
#ifdef DOS
        setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	rectangle(a1,b1,a2,b2);
#endif
	break;
      case 7:

	a1=act[c].a[0];
	b1=act[c].a[1];
	border=act[c].a[2];
	pattern=act[c].a[3];
	mcolor=act[c].a[4];
#ifdef Linux
//was xgetimage here

if (fximage>0) 
  {
  XDestroyImage(fximage);
  }
fximage=XGetImage(xdisplay,pixmap[0],0,0,640,300,AllPlanes,ZPixmap);
linpat=pattern;

if (pattern==15)
{
mcolor=klmap[mcolor];  //mix color
}
else
{
mcolor=klmap[0];  // mix every thing else with black
}

memset(pmp,0,81*301);

mixcolor=mcolor;
bordercolor=klmap[border];
//floodlinpatfill3((unsigned short int)a1,(unsigned short int)b1,0,0);
floodlinpatfill3((unsigned short int)a1,(unsigned short int)b1,0,0,0);
XPutImage(xdisplay,pixmap[0],xgc,fximage,0,0,0,0,640,300);

#endif
#ifdef DOS
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
#endif
	break;
      case 8:
	a1=act[c].a[0];
	b1=act[c].a[1];
	style=act[c].a[2];
	direction=act[c].a[3];
	tsize=act[c].a[4];
#ifdef Linux
strcpy(font_name,"*chart*");
if (tsize==1) {tsize=0;}
if (tsize==2) {tsize=3;}  //make 16= 18
if (tsize==15)
{  
  tsize=30;
}  //72 is most size font
//sprintf(tpstr,"%d*",tsize*2+12);
sprintf(tpstr,"");
strcat(font_name,tpstr);
font_info=XLoadQueryFont(xdisplay,font_name);
if (!font_info)
   {
   fprintf(stderr, "Could not load font %s\n",font_name);
   strcpy(font_name,"*chart*24*");
   font_info=XLoadQueryFont(xdisplay,font_name);
   }
   XSetFont(xdisplay,xgc,font_info->fid);
    XDrawString(xdisplay,pixmap[0],xgc,a1,b1+(font_info->ascent+font_info->descent)/2,act[c].str,strlen(act[c].str));
#endif
#ifdef DOS
	settextstyle(style,direction,tsize);
	setusercharsize(tsize+1,1,tsize+1,1);
	outtextxy(a1,b1,act[c].str);
#endif
	break;
      case 9:
	a1=act[c].a[0];
	b1=act[c].a[1];
	radx=act[c].a[2];
	rady=act[c].a[3];
#ifdef Linux
   	XDrawArc(xdisplay,pixmap[0],xgc,a1-radx,b1-rady,radx*2,rady*2,0,360*64);
#endif
#ifdef DOS
        setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
	ellipse(a1,b1,SANG,EANG,radx,rady);
#endif
	break;
      case 10:
	a1=act[c].a[0];
	b1=act[c].a[1];
	a2=act[c].a[2];
	b2=act[c].a[3];
#ifdef Linux
        xx1=a1;  xx2=a2;  yy1=b1;  yy2=b2;
	if (xx1>xx2)  { xx2=xx1;  xx1=act[c].a[2]; }
	if (yy1>yy2)  { yy2=yy1;  yy1=act[c].a[3]; }

        XSetFillStyle(xdisplay, xgc, FillSolid);
        XFillRectangle(xdisplay, pixmap[0], xgc, xx1, yy1, xx2-xx1, yy2-yy1+1);

#endif
#ifdef DOS
        setfillstyle(1,lcolor);
	bar(a1,b1,a2,b2);
#endif
	break;
      }     	/*end switch*/
   }		/*end for*/
}   /*end draw_it*/




#ifdef Linux
//void floodlinpatfill3(short int sx,short int sy, unsigned char lcx,unsigned char lcy)
void floodlinpatfill3(short int sx,short int sy, unsigned char lcx,unsigned char lcy,int recur)
{
unsigned int nukl;
unsigned int tf;
unsigned int bitf,tst;

if (recur>80000) return;
//fprintf(stderr,"f ");

nukl=XGetPixel(fximage,sx,sy);

tst=(sx/32)+(sy*20);

if (nukl!=bordercolor && (*(pmp+tst)&(1<<(sx%32)))==0)//border or have been here
  {  //this is not a border or already colored pixel



  bitf=(hpat[linpat][lcy]&(1<<lcx));//>>(7-lcx);

  tf=lincolor*(bitf>0)+mixcolor*(bitf>0);

    *(pmp+tst)|=(1<<(sx%32));  //set this pixel to 1 in the pixel map
    XPutPixel(fximage,sx,sy,tf);



//#if 0 
  if (sx>0)
    {
    if (lcx==0)
      {
      floodlinpatfill3(sx-1,sy,7,lcy,recur+1);
      }
    else
      {
      floodlinpatfill3(sx-1,sy,lcx-1,lcy,recur+1);
      }
    }

  if (sx<639) 
    {
    if (lcx==7)
      {
      floodlinpatfill3(sx+1,sy,0,lcy,recur+1);
      }
    else
      {
      floodlinpatfill3(sx+1,sy,lcx+1,lcy,recur+1);
      }
    }
//#endif
//#if 0 
  if (sy>0)
    {

    if (lcy==0)
      {
      floodlinpatfill3(sx,sy-1,lcx,7,recur+1);
      }
    else
      {
      floodlinpatfill3(sx,sy-1,lcx,lcy-1,recur+1);
      }
    }
   

  if (sy<299) //3)  //9)//2) //9)
    {
    if (lcy==7)
      {
      floodlinpatfill3(sx,sy+1,lcx,0,recur+1);
      }
    else
      {
      floodlinpatfill3(sx,sy+1,lcx,lcy+1,recur+1);
      }
    }
//#endif 
//#endif

  }

}
#endif

