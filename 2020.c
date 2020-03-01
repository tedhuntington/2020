/*  2020.c   */
/*       by Ted Huntington   */
/*  This program runs the interactive graphic adventure.... */
/*  			2 0 2 0   !!!			    */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#ifdef Linux
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
//#include <unistd.h>
#include "bitmap.h"
#endif
#ifdef DOS
#include "conio.h"
#include "process.h"
#endif
#include "math.h"
#include "time.h"
#include "string.h"
#ifdef DOS
#include "alloc.h"
#include "graphics.h"
#include "dos.h"
#endif
#include "fcntl.h"
#include "ctype.h"
#include "2020.h"

/*structures*/
#ifdef Linux
struct action         /*actions*/
   {
   short int name;  /*0-color,1-brush,2-lstyle,3-point,*/
	      /*4-line,5-circle,6-rect,7-fill,8-text*/
   short int *a;   /*x1-color-brush,y1-style,x2-rad-direct-tsize,y2-strlen*/
   char *str;  /*string*/
   };
struct daction         /*dynamic actions*/
   {
   short int name;
   short int *a;
   char *str;
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
struct daction         /*dynamic actions*/
   {
   int name;
   int a[5];
   char str[SLEN];
   struct daction *next;
   };
#endif
struct daction *act1,*act2;   /*pic draw actions-begin link, temp link*/
struct daction *act3;   /*temp2 link*/
int cur,chrcur;   /*current act*/

#ifdef Linux
struct doors		/*door structs*/
  {
  short int a[4];	/*x1,y1,x2,y2*/
  short int vis;	/*0-yes, 1-no*/
  short int next;	/*next room*/
  };
#endif
#ifdef DOS
struct doors		/*door structs*/
  {
  int a[4];	/*x1,y1,x2,y2*/
  int vis;	/*0-yes, 1-no*/
  int next;	/*next room*/
  };
#endif
struct doors door[NUMDOR];
struct objects
  {
  char name[LENOBJ];
  int p[4];
  int loc;
  };
struct objects obj[NUMOBJ];
struct objects mobj[NUMMOBJ];
#ifdef Linux
time_t temptime;
//had to make my own time
struct mytime
{
int tm_hour;
int tm_min;
int tm_sec;
};
struct tm *today;
struct tm *utime,*dtime;
struct mytime *mtime;
#endif
#ifdef DOS
struct date today;
struct time utime,mtime,dtime;
#endif
#if Linux
struct words
  {
  char nm[20];   /*15*/
  };
struct words cword[100];  //80
#endif
#if DOS
struct words
  {
  char nm[15];   /*15*/
  };
struct words cword[80];
#endif
struct words word[] = {"quit","look","save","restore","get","drop",
	"time","exit","start","shower","watch","turn","put","switch",
	"read","salt","pepper","inven","inventory","take","inv","open",
	"close","shut","push","scope","pull","press","enter","date",
	"shit","fuck","phone","smell","touch","listen","feel","taste",
	"eat","drink","smoke","hate","sleep","love","call","damn","change",
	"mean","think","hello","hi","good","bad","bye","goodbye","stop","go",
	"follow","lead","answer","piss","pee","fart","cum","come","search",
	"pick","scratch","toke","play","sit","talk","type","write",
	"dance","stand","walk","run","speed","slow","masterbate","jerk",
	"ejaculate","breathe","inject","say","speak","work","deliver","wash",
	"dry","live","die","kill","hurt","punch","kick","shoot","drive",
	"steer","direct","produce","develop","stab","cut","bang","do",
	"separate","connect","disconnect","hang","recognize","know","move",
	"kiss","slap","curse","screw","use","ask","make","help","hint",
	"insert","exchange","sell","commit","stay","unlock","lock","buy",
	"purchase","throw","toss","give","want","dial","compro","see","hear","","","","","","","",
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
	"card","link","refridge","car","cars","automobiles","fridge",
	"bedroom","kitchen","bathroom","room","bath","bathtub","tub",
	"toilet","mirror","towel","rack","sink","door","tv","television",
	"stereo","window","shade","curtain","blind","shades","curtains",
	"blinds","couch","couches","carpet","radio","music","drape",
	"drapes","doors","button","scope","inside","windows","date",
	"channel","station","channels","stations","change","statues",
	"fire","grill","walls","table","stove","oven","microwave",
	"cabinet","cabinets","telephone","drawer","microscope",
	"videophone","money","drawers","paper","papers","wing","wings",
	"plane","planes","airplanes","helicopter","helicopters","heli",
	"helis","life","cash","nature","science","sun","trash","garbage",
	"shaker","stock","stocks","certificate","certificates","can",
	"container","automobile","sidewalk","translator","refridgerator",
	"freezer","cupboard","message","underground","mom","package",
	"packages","box","boxes","mailbox","apartment","apartments",
	"human","person","man","woman","clerk","job","seed","spore",
	"mailboxes","seeds","spores","earth","moon","id","usa","disc",
	"discs","encyclopedia","galactica","history","planet","key","keys",
	"disk","disks","world","machine","ticket","mexico","canada","dollar",
	"dollars","body","suicide","robot","president","north","south",
	"east","west","blue","green","orange","red","sofa","elevator",
	"employment","elevators","cd","rom","drug","tranquilizer","mail",
	"together","apart","","","but","however","0","1","2","3","4","5",
	"6","7","8","9","Phillips","Huntington","Maurois","Pupin",
	"Jones","Smith","Collins","Dettor","Adams","Piraino","Sagan","carl",
	"professor","godless","tom","161945695690","180055551212","120200000001",
	"911","Tracy","Ted","Theodore","Galvani","Sylvia","Peter","Lee","Andy",
	"Volta","Abney","Hershel","John","Lennon","JFK","Oliver","Williams",
	"letter","word","sound","photon","pleasure",
	"politician","lawyer","doctor","thief","surgeon","fisher","fire",
	"cop","police","architect","writer","poet","musician",
	"engineer","teacher","student","self","ceo","female"};

struct event2020
   {
#ifdef Linux
   struct tm *beg;     /*begin time for event*/
   struct tm *end;	/*end time for event*/
#endif
#ifdef DOS
   struct time beg;     /*begin time for event*/
   struct time end;	/*end time for event*/
#endif
   int loc;		/*location # of event*/
   int obnum;		/*object number that appears-disappears*/
   };
#ifdef Linux
//struct event2020 *eve;
struct event2020 eve[NUMEVE];
#endif
#ifdef DOS
struct event2020 eve[NUMEVE];
#endif

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
#ifdef DOS
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
#endif
char upat1[8] =  {0x18, 0x3c,0x7e,0xff,0xff,0x7e,0x3c,0x18};
char upat2[8] =  {0x00, 0xf7,0xf7,0xf7,0x00,0xfe,0xfe,0xfe};
char upat3[8] =  {0xee, 0xee,0xee,0xee,0xe0,0xee,0xee,0x0e};
char cursor[2] = {0xdb, 0x00};

#ifdef Linux
//unsigned char **hpat;
unsigned char hpat[16][9];

//char *PATH;
extern char *PATH;
char LPATH[] = {0x2f,'\0'};
unsigned int *klmap;
#endif
#ifdef DOS
char PATH[256];
char LPATH[] = {0x5c,'\0'};
#endif
#ifdef Linux
char *strtim;	/*string for time*/
char *command;	/*string for user input*/
//char *it;		/*string for computer*/
char it[400];		/*string for computer*/
//char *precom;	/*previous command*/
char des[DESC1][DESC2];	/*current location description*/
char *name;
#endif
#ifdef DOS
char strtim[17];	/*string for time*/
char command[COMLEN];	/*string for user input*/
char it[300];		/*string for computer*/
char des[DESC1][DESC2];	/*current location description*/
char name[30];
#endif
char precom[COMLEN];	/*previous command*/
int lcolor,lc,oldcolor;	/*  line color */
int pattern,border,brush,redraw;/*  fill pattern  */
int onemo;		/* just erase extra*/
int p1,p2,midx,midy;			/*  1st point for circle or line*/
int lstyle,style,direction,tsize;    /*text descriptions*/
int ex,ex2;			/*exit flags*/
int radx,rady;		/*radii for ellipse*/
int hx1,hy1,hx2,hy2;        /*character coordinates*/
int rx3,ry3,rx4,ry4;       /*robot coords*/
int carx[NUMCAR];   /*car coord*/
int roadx[NUMROAD],spikex[NUMSPIKE];
#ifdef Linux
short int skin[8],skin3[8];
#endif
#ifdef DOS
int skin[8],skin3[8];
#endif
int numimg,numimg2,numimg3,numimg4;
int page;		/*current graphics page*/
int lflag;		/*load character flag*/
#ifdef linux
short int *pntx,*pnty;	/*boundary points for picture*/
#endif
#ifdef DOS
int pntx[4],pnty[4];	/*boundary points for picture*/
#endif
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
int ampm;		/*am-0 pm-1*/
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
int initmesg;
#ifdef Linux
FILE *input;
FILE *output;
int status;
char Key;
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
//prototypes
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
#ifdef DOS
int g_driver, g_mode, g_error;
#endif
int b,c,count;		/*  pause counter */
int locolor;		/*  local color */
unsigned lcnt;  /*long counter*/
int lb;			/*  brush number */
float hypot;
char ch,ch1,ch2;
char key[2];		/*key*/
int ich,ich1,ich2;		/*int-<char*/
#ifdef Linux
char *tstr,*tstr2;
#endif
#ifdef DOS
char tstr[SLEN],tstr2[SLEN];
#endif
int lobrush;		/*local brush*/
#ifdef Linux
int tdla;
struct timeval tmv,tmv2;
char title[]="2020 Adventure";
char icon_title[]="2020";
char tmpstr[255];
FILE *fptr;
int a;
#endif



/*run character maker*/
#ifdef Linux
set2020path();
strcpy(tmpstr,PATH);
strcat(tmpstr,"/char");
system(tmpstr);
//system("./char");
#endif
#ifdef DOS
system("CHAR.EXE");
#endif
/*detect graphics */



#ifdef Linux
//cursta=0;

//malloc
mtime=(struct mytime *)malloc(sizeof(struct mytime));
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
//spec=malloc(NUMSPEC*4);
//sent=malloc(10*4);
tstr=malloc(SLEN);
tstr2=malloc(SLEN);
/*cword=malloc(80*4);  //want a 32 bit address to a 32 bit address to a char
for(b=0;b<80;b++)
{
cword[b].nm=malloc(15);
}*/
strtim=malloc(17);	/*string for time*/
//precom=malloc(COMLEN);	/*previous command*/
command=malloc(COMLEN);	/*string for user input*/
//it=malloc(301);		/*string for computer*/
des[0][0]=(unsigned int)malloc(DESC1*DESC2);
//for(b=0;b<DESC1;b++)
//{
//des[b]=malloc(DESC2);
//}
name=malloc(30);
key[0]=(unsigned int)malloc(2);
pntx=malloc(2*5);
pnty=malloc(2*5);
//PATH=malloc(256);
klmap=(unsigned int *)malloc(16*8);
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


#endif
#ifdef DOS
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

#ifdef Linux

temptime=time(NULL);
today=localtime(&temptime);
today->tm_year=120;//2020;
//utime=temptime;       /*get user's time*/  /*set my time*/

//temptime=time(NULL);
//mtime=localtime(&temptime2);
mtime->tm_hour=6;  mtime->tm_min=0;  mtime->tm_sec=0;
//fprintf(stderr,"time= %d:%d:%d",mtime->tm_hour,mtime->tm_min,mtime->tm_sec);
//no hund! mtime.ti_hund=0;



#endif
#ifdef DOS
getdate(&today);  	/*get today's date*/
today.da_year=2020;	/*set tomarrow's date*/
gettime(&utime);       /*get user's time*/  /*set my time*/
mtime.ti_hour=6;  mtime.ti_min=0;  mtime.ti_sec=0; mtime.ti_hund=0;
#endif


page=0;

desc();    /*load descriptions*/



#ifdef DOS
setvisualpage(!page);
setactivepage(page);
#endif

dx=dy=dx2=dy2=0;     doorflag=0;   midx=midy=0;   redraw=1; onemo=1;
radx=0; rady=0;     speed=5;  brush=0;   ex2=0;   cur=0;
lcolor=0;   ex=0;  curloc=0;   curobj=-1;
onepic=0;  telpic=90;  c2=(10-speed);   c3=(10-speed);
slot=0;  channel=0;   qflg=0;  b=0; moonindx=0; shipindx=0;



  init_var();
//curloc=5;
//curloc=11;
  load_file();        /*load title picture*/

#ifdef Linux


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

//        XSelectInput(xdisplay, xwindow, KeyPressMask|ButtonPressMask);

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



depth = DefaultDepth(xdisplay, DefaultScreen(xdisplay));
visual=DefaultVisual(xdisplay,DefaultScreen(xdisplay));

//fximage=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,640,300,8,0);
   //640x3 %8?
//fximage->data=(char *)malloc(fximage->bytes_per_lie*300+16);

pixmap[0] = XCreatePixmap(xdisplay, xwindow, 640,350, depth);
//pixmap[1] = XCreatePixmap(xdisplay, xwindow, 640,350, depth);

XFlush (xdisplay);

#endif


#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,300);
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0],xgc,0,300,640,50);
#endif

#ifdef DOS
  setfillstyle(SOLID_FILL, 15);
  bar(0,0,640,300);   /*white top */
  setfillstyle(SOLID_FILL, 0);
  bar(0,301,640,350);   /*black bottom */
#endif



  draw_it();		/*draw title picture*/


#ifdef Linux

  TitleImage= XGetImage(xdisplay,pixmap[0],0,0,640,300,AllPlanes,ZPixmap);
//  TitleImage= XGetImage(xdisplay,pixmap[0],0,obj[24].p[1],640,30,AllPlanes,ZPixmap);


ShowScreenF();

#endif

#ifdef DOS
  setvisualpage(page);     /*show title*/
#endif
  load_obj();		/*load objects*/
  load_mobj();          /*load moving objects*/
#ifdef Linux
  load_events();	/*load events*/
#endif
#ifdef DOS
  load_events(eve);	/*load events*/
#endif


#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,32);
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0],xgc,0,32,640,318);
#endif

#ifdef DOS
  setactivepage(!page);    /*flip to page 1*/
  setfillstyle(SOLID_FILL, 15);
  bar(0,0,640,32);   /*white top */
  alloc_lines();
  alloc_lines3();      /*allocate memory for char lines*/
#endif
  lflag=2;     /*flag=ted*/
#ifdef Linux
  load_traits("Ted");
#endif
#ifdef DOS
  load_traits("TED");
#endif
  for(c=0;c<=8;c++)
    skin3[c]=skin[c];




  load_file(); 		/*load ted character*/
  lflag=0;
  

  draw_it();	/*draw ted on page 1*/
  getrobot();	/*get image of ted*/


#ifdef Linux
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,300);
#endif
#ifdef DOS
  setfillstyle(SOLID_FILL, 0);
  bar(0,0,640,300);   /*black top */
#endif

  for (c=0;c<4;c++)
    {
    lflag=3;     /*flag=object(heli)*/
    curobj=c+24;
    load_file();   /*load heli*/
    draw_it();	/*draw heli on page 1*/
    lflag=0;
    }
#ifdef DOS
  alloc_lines2();      /*allocate memory for heli lines*/
#endif

  getheli();	/*get image of heli*/

/*  setvisualpage(!page);*/
  for(c=0;c<NUMMOBJ;c++)			/*draw objects*/
  {
  draw_mo(c);
  if (c<NUMCAR)
    getcar(c);
  if (c>=NUMCAR && c<NUMCAR+NUMROAD)
    getroad(c-NUMCAR);
  if (c>=NUMCAR+NUMROAD)
    getspike(c-NUMCAR-NUMROAD);
/*  getch();*/
  }



#ifdef DOS
  setactivepage(page);     /*flip back to page 0*/
#endif
  hx1=hx2=rx3=rx4=TITX;       /*set current coord*/
  hy1=hy2=ry3=ry4=TITY;

#ifdef Linux
  //XPutImage(xdisplay,pixmap[0],xgc,robot[6],0,0,rx3,ry3,WMAN,HMAN);
#endif
#ifdef DOS
  getlines3();
  putimage(rx3,ry3,robot[6],COPY_PUT);	/*draw ted on page 0*/
  putlines3();
#endif
  draw_heli();
#ifdef DOS
  setactivepage(!page);  /*page 1 active*/
#endif

#ifdef DOS
  load_file();        /*load title picture*/
#endif

#ifdef DOS
  setfillstyle(SOLID_FILL, 15);
  bar(0,0,640,300);   /*white top */
  setfillstyle(SOLID_FILL, 0);
  bar(0,301,640,350);   /*black bottom */
#endif


#ifdef Linux
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,0,0,0,0,640,300);
#endif
#ifdef DOS
  draw_it();		/*draw title picture*/
#endif

#ifdef Linux
  XPutImage(xdisplay,pixmap[0],xgc,robot[6],0,0,rx3,ry3,WMAN,HMAN);
  putlines();	/*putimage lines*/
  XDestroyImage(TitleImage);
  TitleImage= XGetImage(xdisplay,pixmap[0],0,0,640,300,AllPlanes,ZPixmap);

fprintf(stderr,"Welcome to 2020\n");  
ShowScreenF();

#endif
#ifdef DOS
  putimage(rx3,ry3,robot[6],COPY_PUT);	/*draw ted on page 0*/
  putlines3();
#endif


#if Linux


  status=0;
  while (status!=1)
  {

                /* wait for next event */
                XNextEvent (xdisplay, &xevent);
                //fprintf(stderr,"%d ",xevent.type);
                switch (xevent.type) {
                /* ignore this event */
                case Expose:
			  if (xevent.xexpose.count==0)
		         ShowScreenF();  //too slow
                        break;
                case ButtonPress:
                     status=1;
			//fprintf(stdout,"A mouse button was pressed.\n");
                     break;
		case KeyPress:
                      status=1;
                    break;
                }  //end switch

#endif
#if DOS
  while (kbhit()==0)    /*while no key press*/
    {
#endif
    for(c=0;c<4;c++)
      {
      obj[c+24].p[0]=obj[c+24].p[0]-SPEEDH;  /*move heli to left*/
#ifdef Linux
      if (obj[c+24].p[0]<=0) obj[c+24].p[0]=570;
#endif
#ifdef DOS
      if (obj[c+24].p[0]<=0) obj[c+24].p[0]=638;
#endif
      }
    draw_heli();
#ifdef Linux
  ShowScreenT();  //erase heli rect
#endif
#ifdef DOS
    setvisualpage(!page);
#endif
#ifdef DOS
    delay(0);   delay(del);
#endif
#ifdef Linux
//shuold make this a delay(us) function
del=30000;
gettimeofday(&tmv,NULL);
tdla=0;
gettimeofday(&tmv2,NULL);
while(tdla<del)  //30000)  //30 us
{
if (tmv.tv_usec>tmv2.tv_usec)
{
tdla=(999999-tmv.tv_usec)+tmv2.tv_usec;
}
else
{
tdla=tmv2.tv_usec-tmv.tv_usec;
}
gettimeofday(&tmv2,NULL);
}  //end while
#endif


#ifdef DOS
    setactivepage(page);
#endif

#ifdef DOS
    erase_heli();
#endif

#ifdef DOS
    for(c=0;c<4;c++)
      {
      obj[c+24].p[0]=obj[c+24].p[0]-SPEEDH;  /*move heli to left*/
      if (obj[c+24].p[0]<=0) obj[c+24].p[0]=638;
      }
    draw_heli();
#endif


#ifdef DOS
    setvisualpage(page);
#endif
#ifdef DOS
    delay(0);   delay(del);
#endif
#ifdef DOS
    setactivepage(!page);
#endif
#ifdef Linux
//erase last image and put title image again
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,0,0,0,0,640,300);
#endif
#ifdef DOS
    erase_heli();
#endif
    }   /*end while no kbhit*/


#ifdef DOS
  ch=getch();
  if(ch==0)  getch();
#endif

#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,32);
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0],xgc,0,32,640,318);
#endif


#ifdef DOS
  setactivepage(!page);
  setfillstyle(SOLID_FILL, 15);
  bar(0,0,640,32);   /*white top */
  setfillstyle(SOLID_FILL, 0);
  bar(0,301,640,350);   /*black bottom */
#endif

#ifdef Linux
  load_traits("Def");
#endif
#ifdef DOS
  load_traits("DEF");  /*tph may have deleted DEF*/
#endif

  lflag=1;
  load_file();	/*load character file*/
  chrcur=cur;
  lflag=0;

  draw_it();	/*draw default character*/
  getman();
#ifdef DOS
  alloc_lines();      /*allocate memory for lines*/
#endif

  init_var2();


  strcpy(command,"");
  strcpy(precom,"");
  init_mob();

  init_ob();

  /*del=320;*/
#ifdef Linux
   del=30000;  //30000 ns= normal delay .033us=30 fps
#endif
#ifdef DOS
  del=3000;
#endif

//newloc=12;



while(ex2 == 0)		/*every new location starts here*/
{
hx2=hx1;  hy2=hy1;
if (spec[20]==2) {rx4=rx3;  ry4=ry3;}
if (curloc!=newloc)
  {curloc=newloc; 
if (spec[20]==2) curloc3=curloc;
if (curloc==58||curloc==59) {hx1=hx2=300; rx3=rx4=320;}}

if (curloc==60 || curloc==61 || curloc==75) spec[1]=3;  /*erase characters*/
if (curloc==62||curloc==76) spec[1]=0;  /*on moon*/
if (curloc==63&&obj[245].loc==-2) {obj[245].loc=63;}
if (curloc==63&&obj[245].loc==0) {obj[245].loc=-3; }
if (curloc==64&&obj[245].loc==-2) {obj[245].loc=64;}
if (curloc==64&&obj[245].loc==0) {obj[245].loc=-3; }
if (curloc==65&&obj[245].loc==-2) {obj[245].loc=65;}
if (curloc==65&&obj[245].loc==0) {obj[245].loc=-3; }
if (curloc==75) {spec[20]=0;}
if (onepic>0) {newloc=curloc;  curloc=onepic;}
spec[4]=0;
if (curloc>7 && curloc<24) spec[4]=1;
if ((curloc<8||curloc>56)&&doorflag)
  {dx=0;  dy=0;  dx2=0;  dy2=0;}
#ifdef Linux
for(count=0;count<1;count++)     /*draw picture on one page*/
#endif
#ifdef DOS
for(count=0;count<2;count++)     /*draw picture on both pages*/
#endif
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
    hx2=hx1;  hy2=hy1;
    rx4=rx3;  ry4=ry3;
  }

if (0) //!onepic&&count==1&&spec[1]!=2&&spec[1]!=3)
  {
    if (hy1<=ry3) get_char();
    if (spec[20]>=1&&curloc3==curloc)
      get_bot();
    if (ry3<hy1) get_char();
    if (curloc==42||curloc==43)
      {
      drroad();
      drspike();
      }
    if (hy1<=ry3)  draw_char();
    if (spec[20]>=1&&curloc3==curloc)
      draw_bot();
    if (ry3<hy1) draw_char();
    if (spec[4]==1)
      drmob();
  }

if (curloc==55) {mobj[14].loc=55; drmob();}
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,300);
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0],xgc,0,300,640,50);
//textstyle and size
XSetForeground (xdisplay, xgc, 0x00ffffff);
#endif

#ifdef DOS
setvisualpage(page);
setactivepage(!page);
setfillstyle(SOLID_FILL, 15);
bar(0,0,640,300);   /*white top */
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
setusercharsize(1,1,1,1);
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
setcolor(15);
#endif
oldcolor=lcolor;
lcolor=15;
#ifdef DOS
setlinestyle(0,ULIN1,1);
#endif
lcolor=oldcolor;        /*initial line color */
//fprintf(stderr,"draw_it\n");  
/*draw room picture*/
draw_it();
//fprintf(stderr,"after draw_it\n");  

#ifdef DOS
lobrush=brush;
draw_cbrush(lobrush,oldcolor);
#endif

#ifdef Linux
//  XDestroyImage(TitleImage);
//  TitleImage= XGetImage(xdisplay,pixmap[0],0,0,640,350,AllPlanes,ZPixmap);
#endif

#ifdef DOS
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
#endif
//fprintf(stderr,"here1\n");  
drob();         	/*draw objects*/

put_com();              /*put out cursor and command*/

#ifdef Linux
//get an image of the room with objects but no characters
  XDestroyImage(TitleImage);
  TitleImage= XGetImage(xdisplay,pixmap[0],0,0,640,300,AllPlanes,ZPixmap);
#endif
#ifdef Linux
//draw full screen (without characters)
//resize
ShowScreenF();


#endif



page=!page;	/*flip pages*/
}   /*end for loop*/
doorflag=0;
#ifdef DOS
setactivepage(page);
#endif



/*draw initial character*/
if (!onepic&&spec[1]!=2&&spec[1]!=3)
    {
    if (hy1<=ry3) get_char();
    if (spec[20]>=1&&curloc3==curloc)
      get_bot();
    if (ry3<hy1)  get_char();
    if (curloc==42||curloc==43)
      {
      drroad();
      drspike();
      }
    if (hy1<=ry3) draw_char();
    if (spec[20]>=1&&curloc==curloc3)
      draw_bot();
    if (ry3<hy1) draw_char();
    if (spec[4]==1)
	drmob();
    }

if (curloc==55)  {mobj[14].loc=55; drmob();}





#ifdef DOS
setvisualpage(page);
#endif
if (curloc==61) dead();
if ((curloc==63||curloc==64||curloc==65)&&obj[245].loc==-3) obj[245].loc=-2;
else ex=0;
if (onepic)
  {
  putout(des[telpic]);    /*look at moon*/
#ifdef Linux
//again this should be a function getkey()
status=0;
  while (status!=1)
  {
   /* wait for next event */
   XNextEvent (xdisplay, &xevent);
   switch (xevent.type)
    {
   /* ignore this event */
   case Expose:
     break;
   case ButtonPress:
     status=1;
     //ch=13;
     break;
   case KeyPress:
     status=1;
     //ch=XLookupKeysym(&xevent.xkey,0);
     break;
    }  //end switch
   }  //end while

#endif
#ifdef DOS
  ch=getch();    /*get key*/
  if (ch==0)  getch();
#endif
  ex=1;
  onepic=0;
  }

if (initmesg==0 && curloc==1)
{
putout("Welcome to 2020!              Press the F1 key for story and instructions.");
initmesg=1;
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

#ifdef DOS
    gettime(&dtime);       /*get user's time*/
    if (dtime.ti_hund>utime.ti_hund)
      mtime.ti_hund=dtime.ti_hund-utime.ti_hund;
    else
      mtime.ti_hund=99-(utime.ti_hund-dtime.ti_hund);
#endif

   if (spec[1]==1)  /*take a shower*/
       {
#ifdef DOS  
       setactivepage(page);  
#endif
//#ifdef Linux
//for Linux - simply redraw screen, because of the complex window resize/redraw
//function, to erase part of the screen for one special event (like a shower)
//is more code than to simply redraw the full screen for one time
//       ShowScreenF();

//#endif
//#ifdef DOS
       erase_char();  
//#endif
#ifdef DOS
       mtime.ti_hund=90;
#endif
       for (b=1;b<=600;b++)    /*600 sec= 10 minutes*/
	  { 
#ifdef Linux
	   mtime->tm_sec++;
           if (mtime->tm_sec>=60)
             {
             mtime->tm_sec=0;
             mtime->tm_min++;
             }
           if (mtime->tm_min==60)
             {mtime->tm_min=0;
             mtime->tm_hour++;}

            if (mtime->tm_hour==13)
              {
              mtime->tm_hour=1;
              ampm=1;
              }


#endif
#if DOS
	   mtime.ti_sec++; 
           timr();
#endif
           check_eve();}
	   putout("Ten minutes pass.");/* get_char(); draw_char();*/
	    obj[21].loc=-2; spec[1]=0; 
#ifdef DOS
	    mtime.ti_hund=0;
#endif
	    refresh();
#ifdef DOS
	  setactivepage(!page);
#endif
       }
    else
     { if (spec[1]==2)  /*go to sleep*/
	{ 
#ifdef DOS	
 	setactivepage(page); mtime.ti_hund=90;
#endif
	  for (b=1;b<=1200;b++)    /*1200 sec= 20 minutes*/
	     {
#ifdef Linux
	  mtime->tm_sec++;  //timr will add time
    if (mtime->tm_sec>=60)
      {
      mtime->tm_sec=0;
      mtime->tm_min++;
      }
    if (mtime->tm_min==60)
      {mtime->tm_min=0;
      mtime->tm_hour++;}

    if (mtime->tm_hour==13)
      {
      mtime->tm_hour=1;
      ampm=1;
      }

	
#endif
#ifdef DOS 
	  mtime.ti_sec++; 
          timr();
#endif
	  check_eve();
         if (qflg>0)
            {
             b=1200;
            }
 		}  /* end for b*/
          if (qflg==0)
            {
	    putout("Twenty minutes pass.");
	    }
	  spec[1]=0; 
#ifdef DOS
	  mtime.ti_hund=0;
#endif
	  obj[7].loc=-2; refresh();
#ifdef DOS
	  setactivepage(!page);
#endif
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
	  if (spec[5]==1)		/*need to flip pages*/
	    {                             /* (there are moving objects)*/




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
		hx1 += dx;
	      hy1 += dy;
	      }
	    hitflag=0;            /*fix boundaries*/
	    if (spec[20]>=1&&curloc3==curloc)
		{
		rx3 += dx2;
		ry3 += dy2;
		}
	    if (curloc==42||curloc==43)
		{mvroad(); mvspike();}
	    if (hx1<0)  {hx1 = 0; hitflag=1;}
	    if (hy1<0)  {hy1 = 0; hitflag=2;}
	    if (hx1>639-WMAN) {hx1 = 639-WMAN; hitflag=3;}
	    if (hy1>300-HMAN-1) {hy1 = 300-HMAN-1; hitflag=4;}
#ifdef DOS
	    setactivepage(!page);		/*go to second screen*/
#endif
	    if (spec[1]!=3)
	      {





	      if (hy1<=ry3)
		get_char();
	      if (spec[20]>=1&&curloc3==curloc)
		get_bot();
	      if (ry3<hy1) get_char();
	      }
	    if (curloc==42||curloc==43)
	      {
	      drroad();
	      drspike();
	      }
	    if (spec[1]!=3)
	      {
	      if (hy1<=ry3)
		draw_char();
	      if (spec[20]>=1&&curloc3==curloc)
		draw_bot();
	      if (ry3<hy1)  draw_char();
	      }
	    if (spec[4]==1)
	      drmob();


#ifdef DOS
	    setvisualpage(!page);                    /*show character*/
#endif

#ifdef Linux
   //can use sleep(seconds) or nanosleep(a,b)
   //sleep(1);
#endif
#ifdef DOS
	    delay(0);
	    delay(del);
#endif
	    if (spec[4]==1)
	      mobhit();
#ifdef DOS
	    setactivepage(page);                    /*go to old (1st) page*/
#endif


#ifdef DOS
	    if (curloc==42||curloc==43)
		{
		erase_road();
		erase_spike();
		}
	    if (spec[4]==1)
	      erase_mob();   /*erase moving objects*/
	    if (spec[1]!=3)
	      {
	      if (hy1<=ry3)
		erase_char();
	      if (spec[20]>=1&&curloc3==curloc)
		erase_bot();
	      if (ry3<hy1)
		erase_char();
	      }
#endif
	    page=!page;
	    if (curloc!=newloc)
	      refresh();


	    } /*end spec[5] flag*/
	  }    /*end if no event happened*/
	}     /*end sleep*/
     }       /*end shower*/


#if Linux
//add at least 200 ms delay, machine more slow will not be delayed
//may want to make this a thread with signal(SIGALRM,timerhandler) and thread_signal(head->s)
//I think the best way to do this is to keep track of time -
//enough to say that each frame will be 33ms (30 fps)
gettimeofday(&tmv,NULL);

tdla=0;
gettimeofday(&tmv2,NULL);
while(tdla<del)  //30000)  //30 us
{
if (tmv.tv_usec>tmv2.tv_usec)
{
tdla=(999999-tmv.tv_usec)+tmv2.tv_usec;
}
else
{
tdla=tmv2.tv_usec-tmv.tv_usec;
}

gettimeofday(&tmv2,NULL);

//do timer loop around key checks



status=0;
//  while (status!=1)
//  {
   /* wait for next event */
   if (XPending(xdisplay))
    {
   XNextEvent (xdisplay, &xevent);

   switch (xevent.type)
    {
   /* ignore this event */

//resize, gotfocus
   case Expose:
     if (xevent.xexpose.count==0)
       {
       ShowScreenF();
       ShowScreen2();
       }
     break;
   case ButtonPress:
     //status=1;
     break;
   case KeyPress:
     status=1;
     ch=XLookupKeysym(&xevent.xkey,0);
     ch2=0;
     key[0]=ch;
     key[1]=0;
     if (ch==-30 || ch==-31) status=0;  //ignore shift keys
     //fprintf(stderr,"%x ",ch);
     break;
    }  //end switch
    }//if pending
  if (status==1)
     {
//fprintf(stderr,"key=%c %c",ch,key[0]);
#endif
#if DOS
  if (kbhit() != 0)
    {
    ch = getch();
    key[0]=ch;  key[1]=0;
    if (ch == 0)  ch2= getch();
#endif
    switch (ch)
      {
#ifdef DOS
      case 0:
	switch(ch2)
	  {
#endif
	  case 15:
	    putinv();
	    break;
#ifdef Linux
	  case -66:
#endif
#ifdef DOS
	  case 59:			/*F1*/
#endif
	    menu();
	    break;
#ifdef Linux
	  case -65:
#endif
#ifdef DOS
	  case 60:
#endif
	    save_game();
	    break;
#ifdef Linux
	  case -64:
#endif
#ifdef DOS
	  case 61:			/*F3*/
#endif
	    strcpy(command,precom);
#ifdef DOS
	    cursx=precur;
#endif
#ifdef Linux
//erase cursor
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0], xgc, cursx,cursy+5,16,30);

//XSetForeground (xdisplay, xgc, 0x0);
//XFillRectangle (xdisplay, pixmap[0], xgc, cursx,cursy,16,30);
#endif
#ifdef DOS
	    setactivepage(!page);
	    setfillstyle(1,0);
	    bar(16,cursy,639,cursy+16);
#endif
	    put_com();
#ifdef DOS
	    setactivepage(page);
            setfillstyle(1,0);
	    bar(16,cursy,639,cursy+16);
	    put_com();
#endif
	    break;
#ifdef Linux
	  case -63:
#endif
#ifdef DOS
	  case 62:
#endif
	    restore_game();
	    break;
#ifdef Linux
	  case -62:
#endif
#ifdef DOS
	  case 63:
#endif
	    hint();
	    break;
#ifdef Linux
	  case -57:
#endif
#ifdef DOS
	  case 68:			/*F10*/
#endif
#ifdef Linux
//30000 is normal
	 if (del>300000)
           {del=300;}
         else
           {
           del*=2;
           }
#endif
#ifdef DOS
	    /*del=del+300;
	    if (del>900) del=20;*/
	    del=del+1000;
          if (del>10000) del=20;
#endif
	    break;
	  case 71:			/*up-left */
	    if (spec[1]!=3)
	      {
	      dx = -speed;
	      dy = -speed;
	      mode=1;
	      }
	    break;
#ifdef Linux
	case 82:
#endif
#ifdef DOS
	  case 72:			/*up arrow*/
#endif
	    if (spec[1]!=3)
	      {
            if (dx !=0 || dy !=0) /*already moving=stop*/
		  {
		  dx=dy=0;
              }
            else
              {
	        dx = 0;
	        dy = -speed;
	        mode=2;
              }
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
#ifdef Linux
	case 81:
#endif
#ifdef DOS
	  case 75:			/*left arrow*/
#endif
	    if (spec[1]!=3)
	      {
            if (dx !=0 || dy !=0) /*already moving=stop*/
		  {
		  dx=dy=0; 	
              }
            else
              {
	        dx = -speed;		/*change in x is -1 */
	        dy = 0;
	        mode=1;
              }
	      }
	    break;
	  case 76:		/*5-stop*/
	    dx=0;
	    dy=0;
/*	    mode=3; */
	    break;
#ifdef Linux
	case 83:

#endif
#ifdef DOS
	  case 77: 			/*right arrow*/
#endif
	    if (spec[1]!=3)
	     {
            if (dx !=0 || dy !=0) /*already moving=stop*/
		  {
		  dx=dy=0; 	
              }
            else
              {
   	        dx = speed;
	        dy = 0;
	        mode=4;
              }
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
#ifdef Linux
	case 84:

#endif
#ifdef DOS
	 case 80:			/*down arrow*/
#endif
	    if (spec[1]!=3)
	     {
            if (dx !=0 || dy !=0) /*already moving=stop*/
		  {
		  dx=dy=0;
              }
            else
              {
 	        dx = 0;
	        dy = speed;
	        mode=0;
              }
	     }
	   break;
#ifdef DOS
	 case 81:			/*down-right*/
	    if (spec[1]!=3)
	     {
	     dx = speed;
	     dy = speed;
	     mode=4;
	     }
	   break;
#endif

#ifdef DOS
	  }	/*end extended keys switch*/
	break;
#endif

      case 8:			/*  backspace*/
	if (cursx>16)
	  {
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0], xgc, cursx,cursy,16,30);
ShowScreen2();
#endif

#ifdef DOS
	  setfillstyle(SOLID_FILL,0);
	  setactivepage(page);
	  bar(cursx-16,cursy,cursx+16,cursy+16);
	  setactivepage(!page);
	  bar(cursx-16,cursy,cursx+16,cursy+16);
#endif
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
#ifdef DOS
	setfillstyle(SOLID_FILL,0);
#endif
	precur=cursx;		/*save cursor*/
        cursx=16;		/*reset cursor*/
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay,pixmap[0], xgc,16,300,639,50);
ShowScreen2();
#endif
#ifdef DOS
	setactivepage(page);
	bar(16,310,639,349);		/*blackout old sentence*/
	draw_cursor();
	setactivepage(!page);
	bar(16,310,639,349);		/*blackout old sentence*/
#endif
	draw_cursor();
	strcpy(command,"");
	break;
      case 27:	/*esc*/
	quit();
	break;
#ifdef Linux
      case 0x5d:   //']'
#endif
#ifdef DOS
      case 43:			/* '+' speed up*/
#endif
	if (speed<8) speed++;
	dx=(dx>0)*speed-(dx<0)*speed;
	dy=(dy>0)*speed-(dy<0)*speed;
	break;
#ifdef Linux
      case 0x5b:   //'['
#endif
#ifdef DOS
      case 45:			/* '-' slow down*/
#endif
	if (speed>1) speed--;
	dx=(dx>0)*speed-(dx<0)*speed;
	dy=(dy>0)*speed-(dy<0)*speed;
	break;
      default:		/*alpha or other symbol*/
	if (cursx<592)     /*608*/
	  {
#ifdef Linux
//erase cursor
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0], xgc, cursx,cursy+5,16,30);
//draw letter
XSetForeground (xdisplay, xgc, 0x00ffffff);
XDrawString(xdisplay,pixmap[0],xgc,cursx,cursy+10+(font_info->ascent+font_info->descent)/2,key,1);

ShowScreen2();
//may have to draw charater

#endif
#ifdef DOS
	  setcolor(15);
	  setfillstyle(SOLID_FILL,0);
	  settextstyle(0,0,2);
	  setactivepage(page);
	  bar(cursx,cursy,cursx+16,cursy+16);  /*blackout cursor*/
	  outtextxy(cursx,cursy,key);
	  setactivepage(!page);
	  bar(cursx,cursy,cursx+16,cursy+16);  /*blackout cursor*/
	  outtextxy(cursx,cursy,key);
#endif
	  cursx=cursx+16;
	  strcat(command,key);
	  draw_cursor();
	  }
	break;
      }                            /*end switch*/
   }                           /*end if kbhit*/
}  //end timer while
   if (hitflag==6)  {hitflag=0;
	putout("You were hit by a car.  Now you are dead.");  dead();}
  }                             /*end while*/
}		/*end 2nd while*/

#ifdef Linux
       XDestroyWindow(xdisplay, xwindow);
        XCloseDisplay (xdisplay);
#endif
#ifdef DOS
closegraph();
#endif
}	       /*end main*/


#ifdef Linux
ShowScreenT()
{
unsigned int nukl;
XImage *fximage2;
int a,b;
int th,tw;
Pixmap lpixmap;


XGetGeometry(xdisplay, xwindow, root_win, x_return, y_return, width_return,height_return, border_width_return, depth_return);
th=*height_return; 
tw=*width_return;  
//fprintf(stderr,"w=%d h=%d\n",tw,th);
if (tw==640 && th==350)
{

XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,obj[24].p[1],640,30,0,obj[24].p[1]);
}
else
{
//scale pixmap[0] to lpixmap
th=th*.857;
if (fximage>0) {XDestroyImage(fximage);}
fximage=XGetImage(xdisplay,pixmap[0],0,obj[24].p[1],640,30,AllPlanes,ZPixmap);
fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,tw,th/10,8,0);
//fximage2->data=(char *)malloc(fximage2->bytes_per_line*th+16);
fximage2->data=(char *)malloc(th*tw*3);
for(a=0;a<tw;a++)
  for(b=0;b<th/10.0;b++)
    {
    nukl=XGetPixel(fximage,a*640/tw,b*300.0/th);
    XPutPixel(fximage2,a,b,nukl);
 //copy using ->data[?]
    }

//fprintf(stderr,"height=%d\n",th/10.0);
lpixmap = XCreatePixmap(xdisplay, xwindow, tw,(th/10.0), depth);
XPutImage(xdisplay,lpixmap,xgc,fximage2,0,0,0,0,tw,th/10.0);

free(fximage2->data);
//XDestroyImage(fximage2);  //problem?
//XDestroyImage(fximage);

XCopyArea(xdisplay,lpixmap,xwindow,xgc,0,0,tw,th/10.0,0,obj[24].p[1]*(th/300.0)); 
XFreePixmap(xdisplay,lpixmap);

}  //end if then else
//#endif

XFlush (xdisplay);

}


#endif



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
//#endif

XFlush (xdisplay);

}
#endif



#ifdef Linux
ShowScreen2()
{
unsigned int nukl;
XImage *fximage2;
int a,b;
int th,tw;
Pixmap lpixmap;


XGetGeometry(xdisplay, xwindow, root_win, x_return, y_return, width_return,height_return, border_width_return, depth_return);
th=*height_return; 
tw=*width_return;  
//fprintf(stderr,"w=%d h=%d\n",tw,th);
if (tw==640 && th==350)
{
XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,300,640,50,0,300);
}
else
{
//th*=.857;
//scale pixmap[0] to lpixmap
if (fximage>0) {XDestroyImage(fximage);}
fximage=XGetImage(xdisplay,pixmap[0],0,300,640,50,AllPlanes,ZPixmap);
fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,tw,th/7,8,0);
fximage2->data=(char *)malloc(fximage2->bytes_per_line*th+16);
for(a=0;a<tw;a++)
  for(b=0;b<th/7;b++)
    {
    // fprintf(stderr,"%d ",300+(b*50/(th/7)));

    nukl=XGetPixel(fximage,a*640/tw,(b*50/(th/7)));
    XPutPixel(fximage2,a,b,nukl);
 //copy using ->data[?]
    }


lpixmap = XCreatePixmap(xdisplay, xwindow, tw,th/7, depth);
XPutImage(xdisplay,lpixmap,xgc,fximage2,0,0,0,0,tw,th/7);

free(fximage2->data);
//XDestroyImage(fximage2);  //problem?
//XDestroyImage(fximage);

XCopyArea(xdisplay, lpixmap, xwindow, xgc,0, 0,tw,th/7,0, th*6/7); 
XFreePixmap(xdisplay,lpixmap);

}  //end if then else
//#endif


XFlush (xdisplay);

}
#endif



#ifdef Linux
ShowScreenH()
{
unsigned int nukl;
XImage *fximage2;
int a,b;
int th,tw;
Pixmap lpixmap;
float rx,ry;


XGetGeometry(xdisplay, xwindow, root_win, x_return, y_return, width_return,height_return, border_width_return, depth_return);
th=*height_return; 
tw=*width_return;  
//fprintf(stderr,"w=%d h=%d\n",tw,th);
if (tw==640 && th==350)
{
XCopyArea(xdisplay,pixmap[0],xwindow,xgc,hx1-10,hy1-10,WMAN+20,HMAN+20,hx1-10,hy1-10);
}
else
{
//th*=.857;
//scale pixmap[0] to lpixmap
rx=tw/640.0;
ry=th/350.0;						//14+30=44*3=132+4  65+30=95*3=285+3
if (fximage>0) {XDestroyImage(fximage);}    //14*3=42+6  //65*3=195+5
XFlush (xdisplay);
fximage=XGetImage(xdisplay,pixmap[0],hx1-10,hy1-10,WMAN+30,HMAN+30,AllPlanes,ZPixmap);
fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,rx*(WMAN+30),ry*(HMAN+30),8,0);

//must make sure malloc is enough or seg fault
//fximage2->data=(char *)malloc((int)((rx*(WMAN+30))*(ry*(HMAN+30))*3));

fximage2->data=(char *)malloc((int)((rx*(WMAN+50))*(ry*(HMAN+50))*3));
//fximage2->data=(char *)malloc(fximage2->bytes_per_line*th); //(HMAN+30));


for(a=0;a<(int)(rx*(WMAN+30.0));a++)
  {
  for(b=0;b<(int)(ry*(HMAN+30.0));b++)
    {


    //fprintf(stderr,"%d %d=%d %d-%d %d  ",a,b,hx1,hy1,(int)(hx1-10+(a/rx)),(int)(hy1-10+(b*350.0/th)));

//   fprintf(stderr,"%d,%d  ",(int)(a/rx),(int)(b/ry));

    nukl=XGetPixel(fximage,(int)(a/rx),(int)(b/ry));

    XPutPixel(fximage2,a,b,nukl);
    }
   }

lpixmap = XCreatePixmap(xdisplay, xwindow,rx*(WMAN+30),ry*(HMAN+30),depth);

XPutImage(xdisplay,lpixmap,xgc,fximage2,0,0,0,0,rx*(WMAN+30),ry*(HMAN+30));

free(fximage2->data);


//XDestroyImage(fximage2);  //problem?
//XDestroyImage(fximage);


XCopyArea(xdisplay, lpixmap, xwindow, xgc,0, 0,rx*(WMAN+30),ry*(HMAN+30),rx*(hx1-10),ry*(hy1-10));


XFreePixmap(xdisplay,lpixmap);

}  //end if then else
//#endif


XFlush (xdisplay);


}


#endif



#ifdef Linux
ShowScreenR()
{
unsigned int nukl;
XImage *fximage2;
int a,b;
int th,tw;
Pixmap lpixmap;
float rx,ry;


XGetGeometry(xdisplay, xwindow, root_win, x_return, y_return, width_return,height_return, border_width_return, depth_return);
th=*height_return;
tw=*width_return;  
//fprintf(stderr,"w=%d h=%d\n",tw,th);
if (tw==640 && th==350)
{
XCopyArea(xdisplay,pixmap[0],xwindow,xgc,rx3-10,ry3-10,WMAN+20,HMAN+20,rx3-10,ry3-10);
}
else
{
//th*=.857;
//scale pixmap[0] to lpixmap
rx=tw/640.0;
ry=th/350.0;						//14+30=44*3=132+4  65+30=95*3=285+3
if (fximage>0) {XDestroyImage(fximage);}    //14*3=42+6  //65*3=195+5
fximage=XGetImage(xdisplay,pixmap[0],rx3-10,ry3-10,WMAN+30,HMAN+30,AllPlanes,ZPixmap);
fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,rx*(WMAN+30),ry*(HMAN+30),8,0);

//must make sure malloc is enough or seg fault
//fximage2->data=(char *)malloc((int)((rx*(WMAN+30))*(ry*(HMAN+30))*3));

//fximage2->data=(char *)malloc(fximage2->bytes_per_line*ry*(HMAN+30)); //(HMAN+30));
fximage2->data=(char *)malloc((int)((rx*(WMAN+50))*(ry*(HMAN+50))*3));


for(a=0;a<(int)(rx*(WMAN+30));a++)
  {
  for(b=0;b<(int)(ry*(HMAN+30));b++)
    {


    //fprintf(stderr,"%d %d=%d %d-%d %d  ",a,b,hx1,hy1,(int)(hx1-10+(a/rx)),(int)(hy1-10+(b*350.0/th)));

    nukl=XGetPixel(fximage,a/rx,b/ry);

    XPutPixel(fximage2,a,b,nukl);
    }
   }

lpixmap = XCreatePixmap(xdisplay, xwindow,rx*(WMAN+30),ry*(HMAN+30),depth);

XPutImage(xdisplay,lpixmap,xgc,fximage2,0,0,0,0,rx*(WMAN+30),ry*(HMAN+30));

free(fximage2->data);


//XDestroyImage(fximage2);  //problem?
//XDestroyImage(fximage);


XCopyArea(xdisplay, lpixmap, xwindow, xgc,0, 0,rx*(WMAN+30),ry*(HMAN+30),rx*(rx3-10),ry*(ry3-10)); 


XFreePixmap(xdisplay,lpixmap);

}  //end if then else
//#endif


XFlush (xdisplay);


}
#endif

#ifdef Linux
ShowScreenK()
{
unsigned int nukl;
XImage *fximage2;
int a,b;
int th,tw;
Pixmap lpixmap;
float rx,ry;


XGetGeometry(xdisplay, xwindow, root_win, x_return, y_return, width_return,height_return, border_width_return, depth_return);
th=*height_return; 
tw=*width_return;  
//fprintf(stderr,"w=%d h=%d\n",tw,th);
if (tw==640 && th==350)
{
XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,155,640,125, 0,155);
}
else
{
//scale pixmap[0] to lpixmap
//th=th*.857;
rx=tw/640.0;
ry=th/350.0;
if (fximage>0) {XDestroyImage(fximage);}
fximage=XGetImage(xdisplay,pixmap[0],0,155,640,125,AllPlanes,ZPixmap);
fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,tw,(int)(ry*125.0),8,0);
fximage2->data=(char *)malloc(tw*ry*125*4);
for(a=0;a<tw;a++)
  for(b=0;b<(int)(ry*125);b++)
    {
    nukl=XGetPixel(fximage,(int)(a/rx),(int)(b/ry));
    XPutPixel(fximage2,a,b,nukl);
 //copy using ->data[?]
    }

//fprintf(stderr,"height=%d\n",ry*125.0);
lpixmap = XCreatePixmap(xdisplay, xwindow, tw,(int)(ry*125.0), depth);
XPutImage(xdisplay,lpixmap,xgc,fximage2,0,0,0,0,tw,(int)(ry*125.0));

free(fximage2->data);
//XDestroyImage(fximage2);  //problem?
//XDestroyImage(fximage);

XCopyArea(xdisplay,lpixmap,xwindow,xgc,0,0,tw,(int)(ry*125.0),0,(int)(155.0*ry)); 
XFreePixmap(xdisplay,lpixmap);

}  //end if then else
//#endif

XFlush (xdisplay);

}
#endif

#ifdef Linux
ShowScreenRD()
{
unsigned int nukl;
XImage *fximage2;
int a,b;
int th,tw;
Pixmap lpixmap;
float rx,ry;


XGetGeometry(xdisplay, xwindow, root_win, x_return, y_return, width_return,height_return, border_width_return, depth_return);
th=*height_return; 
tw=*width_return;  
//fprintf(stderr,"w=%d h=%d\n",tw,th);
if (tw==640 && th==350)
{
//XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,155,640,125, 0,155);
XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,mobj[NUMCAR].p[1],640,2,0,mobj[NUMCAR].p[1]);

}
else
{
//scale pixmap[0] to lpixmap
//th=th*.857;
rx=tw/640.0;
ry=th/350.0;
if (fximage>0) {XDestroyImage(fximage);}
//fximage=XGetImage(xdisplay,pixmap[0],0,155,640,125,AllPlanes,ZPixmap);
fximage=XGetImage(xdisplay,pixmap[0],0,mobj[NUMCAR].p[1],640,2,AllPlanes,ZPixmap);
//fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,tw,(int)(ry*125.0),8,0);
fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,tw,(int)(ry*2.0),8,0);
//fximage2->data=(char *)malloc(th*tw*10);
fximage2->data=(char *)malloc(ry*2*tw*4);
for(a=0;a<tw;a++)
  for(b=0;b<(int)(ry*2);b++)
    {
    nukl=XGetPixel(fximage,(int)(a/rx),(int)(b/ry));
    XPutPixel(fximage2,a,b,nukl);
 //copy using ->data[?]
    }

lpixmap = XCreatePixmap(xdisplay, xwindow, tw,(int)(ry*2.0), depth);
XPutImage(xdisplay,lpixmap,xgc,fximage2,0,0,0,0,tw,(int)(ry*2.0));

free(fximage2->data);
//XDestroyImage(fximage2);  //problem?
//XDestroyImage(fximage);

XCopyArea(xdisplay,lpixmap,xwindow,xgc,0,0,tw,(int)(ry*2.0),0,(int)(mobj[NUMCAR].p[1]*ry)); 
XFreePixmap(xdisplay,lpixmap);

}  //end if then else
//#endif

XFlush (xdisplay);

}
#endif



#ifdef Linux
ShowScreenSP()
{
unsigned int nukl;
XImage *fximage2;
int a,b;
int th,tw;
Pixmap lpixmap;
float rx,ry;


XGetGeometry(xdisplay, xwindow, root_win, x_return, y_return, width_return,height_return, border_width_return, depth_return);
th=*height_return; 
tw=*width_return;  
//fprintf(stderr,"w=%d h=%d\n",tw,th);
if (tw==640 && th==350)
{
XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,mobj[NUMCAR+NUMROAD].p[1],640,25, 0,mobj[NUMCAR+NUMROAD].p[1]);
//XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,mobj[NUMCAR].p[1],640,2,0,mobj[NUMCAR].p[1]);

}
else
{
//scale pixmap[0] to lpixmap
//th=th*.857;
rx=tw/640.0;
ry=th/350.0;
if (fximage>0) {XDestroyImage(fximage);}
fximage=XGetImage(xdisplay,pixmap[0],0,mobj[NUMCAR+NUMROAD].p[1],640,25,AllPlanes,ZPixmap);
fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,tw,(int)(ry*25.0),8,0);
fximage2->data=(char *)malloc(ry*25*tw*4);
for(a=0;a<tw;a++)
  for(b=0;b<(int)(ry*25);b++)
    {
    nukl=XGetPixel(fximage,(int)(a/rx),(int)(b/ry));
    XPutPixel(fximage2,a,b,nukl);
 //copy using ->data[?]
    }

lpixmap = XCreatePixmap(xdisplay, xwindow, tw,(int)(ry*25.0), depth);
XPutImage(xdisplay,lpixmap,xgc,fximage2,0,0,0,0,tw,(int)(ry*25.0));

free(fximage2->data);
//XDestroyImage(fximage2);  //problem?
//XDestroyImage(fximage);

XCopyArea(xdisplay,lpixmap,xwindow,xgc,0,0,tw,(int)(ry*25.0),0,(int)(mobj[NUMCAR+NUMROAD].p[1]*ry)); 
XFreePixmap(xdisplay,lpixmap);

}  //end if then else
//#endif

XFlush (xdisplay);

}
#endif



quit()
{
qflg=2;
putout("Quit? (Y/N)");
}

erase_char()
{  
#ifdef linux
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,hx2,hy2, hx2,hy2,WMAN+5,HMAN+5);

ShowScreenH();

#endif
#ifdef DOS
putimage(hx2,hy2,screen[page],COPY_PUT);
#endif
}

erase_bot()
{
#ifdef Linux
//XPutImage(xdisplay,pixmap[0],xgc,screen3[0],0,0,rx4,ry4,WMAN,HMAN);
//XDestroyImage(screen3[0]);
#endif
#ifdef DOS  
putimage(rx4,ry4,screen3[page],COPY_PUT);
#endif
}

get_char()
{   /*get background*/
#ifdef Linux
//screen[0]=  XGetImage(xdisplay,pixmap[0],hx1,hy1,WMAN,HMAN,AllPlanes,ZPixmap);
#endif
#ifdef DOS
    getimage(hx1,hy1,hx1+WMAN,hy1+HMAN,screen[!page]);
#endif
//    getlines(); 	/*getimage lines*/
}

get_bot()
{   /*get background*/
#ifdef Linux
//screen3[0]=  XGetImage(xdisplay,pixmap[0],rx3,ry3,WMAN,HMAN,AllPlanes,ZPixmap);
#endif
#ifdef DOS
    getimage(rx3,ry3,rx3+WMAN,ry3+HMAN,screen3[!page]);
#endif
    //getlines3(); 	/*getimage lines*/
}

draw_char()
{
    /*put character on screen*/
#ifdef Linux
//erase char first for linux because no page flipping

XPutImage(xdisplay,pixmap[0],xgc,TitleImage,hx2,hy2, hx2,hy2,WMAN+5,HMAN+5);
//XPutImage(xdisplay,pixmap[0],xgc,TitleImage,hx1,hy1, hx1,hy1,WMAN+5,HMAN+5);

  XPutImage(xdisplay,pixmap[0],xgc,man[numimg],0,0, hx1,hy1,WMAN,HMAN);

   putlines();	/*putimage lines*/

//copy updated part of pixmap to screen
//have to show enough of the pixmap that erased the last char

ShowScreenH();

#endif
#ifdef DOS
    putimage(hx1,hy1,man[numimg],COPY_PUT);
    putlines();	/*putimage lines*/
#endif
 
}

draw_bot()
{
    /*put robot on screen*/
#ifdef Linux
//  XPutImage(xdisplay,pixmap[0],xgc,robot[numimg3],0,0,rx3,ry3,WMAN,HMAN);

//erase char first for linux because no page flipping

XPutImage(xdisplay,pixmap[0],xgc,TitleImage,rx4,ry4, rx4,ry4,WMAN+5,HMAN+5);

XPutImage(xdisplay,pixmap[0],xgc,robot[numimg3],0,0, rx3,ry3,WMAN,HMAN);
   putlines3();	
//copy updated part of pixmap to screen
//have to show enough of the pixmap that erased the last char
ShowScreenR();

#endif
#ifdef DOS
    putimage(rx3,ry3,robot[numimg3],COPY_PUT);
#endif
    //putlines3();	/*putimage lines*/
}

erase_heli()
{
int c;

for(c=0;c<4;c++)
  {
#ifdef Linux

#if 0 
  if (obj[c+24].p[0]==570)
  XPutImage(xdisplay,pixmap[0],xgc,screen[c+1],0,0,SPEEDH,obj[c+24].p[1],58,24);   //58 24  61 26
  else
  XPutImage(xdisplay,pixmap[0],xgc,screen[c+1],0,0,obj[c+24].p[0]+SPEEDH,obj[c+24].p[1],58,24);  //61,26);

XDestroyImage(screen[c+1]);
#endif


#endif
#ifdef DOS
  if (obj[c+24].p[0]==638)
    putimage(SPEEDH,obj[c+24].p[1],screen[c+1],COPY_PUT);
  else
    putimage(obj[c+24].p[0]+SPEEDH,obj[c+24].p[1],screen[c+1],COPY_PUT);
#endif
  }
}

draw_heli()
{
int c;

//getlines2(); 	/*getimage lines*/
for(c=0;c<4;c++)
  {
#ifdef Linux

//fprintf(stderr,"%d %d\n",obj[c+24].p[0]+SPEEDH+40,obj[c+24].p[1]+24);
#if 0 
  if (obj[c+24].p[0]==570)  //638)
    screen[c+1]=  XGetImage(xdisplay,pixmap[0],SPEEDH,obj[c+24].p[1],60,24,AllPlanes,ZPixmap);  //60 24
  else
    screen[c+1]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+SPEEDH,obj[c+24].p[1],60,24,AllPlanes,ZPixmap);
#endif

  XPutImage(xdisplay,pixmap[0],xgc,heli[c],0,0,obj[c+24].p[0],obj[c+24].p[1],60,25);  //61,26);
#endif
#ifdef DOS
  if (obj[c+24].p[0]==638)
    getimage(SPEEDH,obj[c+24].p[1],60+SPEEDH,obj[c+24].p[1]+24,screen[c+1]);
  else
    getimage(obj[c+24].p[0]+SPEEDH,obj[c+24].p[1],obj[c+24].p[0]+SPEEDH+60,obj[c+24].p[1]+24,screen[c+1]);
   /*put heli on screen*/
  putimage(obj[c+24].p[0],obj[c+24].p[1],heli[c],COPY_PUT);
#endif
  }
putlines2();	/*putimage lines*/
}

timr()
{
char temp[4];

#ifdef Linux
//for Linux (and could be for DOS)
//this code will be run fast enough to detect a change in the second counter
    temptime=time(NULL);
    utime=localtime(&temptime);


    if (utime->tm_sec != mtime->tm_sec)
       {
       spec[2]=1;
       mtime->tm_sec++;
       }
    else
       {
       spec[2]=0;
       }

    if (mtime->tm_sec>=60)
      {
      mtime->tm_sec=0;
      mtime->tm_min++;
      }
    if (mtime->tm_min==60)
      {mtime->tm_min=0;
      mtime->tm_hour++;}

    if (mtime->tm_hour==13)
      {
      mtime->tm_hour=1;
      ampm=1;
      }

    sprintf(temp,"%d",mtime->tm_hour);

    if (mtime->tm_hour<10) strcat(strtim,"0");
    strcpy(strtim,temp);
    strcat(strtim,":");

    sprintf(temp,"%d",mtime->tm_min);
    if (mtime->tm_min<10) strcat(strtim,"0");
    strcat(strtim,temp);
    strcat(strtim,":");
    sprintf(temp,"%d",mtime->tm_sec);
    if (mtime->tm_sec<10) strcat(strtim,"0");
    strcat(strtim,temp);
    if (ampm)  strcat(strtim," pm.");
    else strcat(strtim," am.");

//} //end while

#endif  //Linux
#ifdef DOS    
    if (mtime.ti_hund>89&&spec[2]==0)
      {spec[2]=1;
       mtime.ti_sec++;}
    if ((mtime.ti_hund>30&&mtime.ti_hund<80)/*||(spec[1]==0)*/)
	spec[2]=0;

    if (mtime.ti_sec==60)
      {
      mtime.ti_sec=0;
      mtime.ti_min++;
      }
    if (mtime.ti_min==60)
      {mtime.ti_min=0;
      mtime.ti_hour++;}

    if (mtime.ti_hour==13)
      {
      mtime.ti_hour=1;
      ampm=1;
      }
    itoa(mtime.ti_hour,temp,10);
    if (mtime.ti_hour<10) strcat(strtim,"0");
    strcpy(strtim,temp);
    strcat(strtim,":");
    itoa(mtime.ti_min,temp,10);
    if (mtime.ti_min<10) strcat(strtim,"0");
    strcat(strtim,temp);
    strcat(strtim,":");
    itoa(mtime.ti_sec,temp,10);
    if (mtime.ti_sec<10) strcat(strtim,"0");
    strcat(strtim,temp);
    if (ampm)  strcat(strtim," pm.");
    else strcat(strtim," am.");


#endif

}

check_eve()      /*check time events*/
{
int c;
int evfl;
evfl=0;
    for(c=0;c<NUMEVE;c++)
	{				 /*make object visable*/
#ifdef Linux
	if (mtime->tm_hour==eve[c].beg->tm_hour &&
	  mtime->tm_min==eve[c].beg->tm_min &&
	  mtime->tm_sec==eve[c].beg->tm_sec)
#endif
#ifdef DOS
	if (mtime.ti_hour==eve[c].beg.ti_hour&&
	  mtime.ti_min==eve[c].beg.ti_min&&
	  mtime.ti_sec==eve[c].beg.ti_sec)
#endif
	  {
	  evfl=1;
	  if (c<NUMTV)   /*we are turning to a new slot*/
	    {
	    if (slot!=eve[c].obnum)
	      {
	      obj[slot*10+channel+30].loc=-2;   /*turn off old tv picture*/
	      slot=eve[c].obnum;
	      if (spec[0]==1)
		obj[slot*10+channel+30].loc=eve[c].loc;
	      if (curloc==eve[c].loc&&spec[0]==1)
		refresh();    /*end if we are in tv room and tv is on*/
	      }  /*end if we have not already turned slot*/
	    }  /*end if we are turning a slot*/
	  else
	      {
	      if (obj[eve[c].obnum].loc!=eve[c].loc)
		{
		obj[eve[c].obnum].loc=eve[c].loc;
		if (curloc==eve[c].loc)
		  refresh();
		if (c!=7)
		  {
		  if (obj[8].loc==-1)  {putout("You got a phone call.");
					spec[7]=c-7;}
		  }
		else
		  {
		  if (obj[8].loc==-1)  putout("You got a large package.");
		  }
		}    /*end if object is not already set*/
	      }  /*end if we are not turning a slot*/
	  } /*end if event time matches time now*/
						/*make object disappear*/
#ifdef Linux
      if (mtime->tm_hour==eve[c].end->tm_hour&&
	  mtime->tm_min==eve[c].end->tm_min&&
	  mtime->tm_sec==eve[c].end->tm_sec&&
#endif
#ifdef DOS
      if (mtime.ti_hour==eve[c].end.ti_hour&&
	  mtime.ti_min==eve[c].end.ti_min&&
	  mtime.ti_sec==eve[c].end.ti_sec&&
#endif
	  obj[eve[c].obnum].loc!=-2&&c>11)
	    {
	    evfl=1;
	    obj[eve[c].obnum].loc=-2;
	    refresh();
	    }
    }     /*end for all events*/
		    /*end of game event*/

#if Linux
      if (mtime->tm_hour==9 && mtime->tm_min==30 && mtime->tm_sec==0 &&
#endif

#if DOS
      if (mtime.ti_hour==9 && mtime.ti_min==30 && mtime.ti_sec==0 &&
#endif
		curloc<55)
	  {
	  evfl=1;
	  spec[1]=0;  /*turn off shower*/
	  putout("Time is up.  You were caught and arrested for 'suspicious actions', a new crime.");
#ifdef Linux
	  mtime->tm_hour=0;  mtime->tm_min=0;
#endif
#ifdef DOS
	  mtime.ti_hour=0;  mtime.ti_min=0;
#endif
	  qflg=1;
	  putout("Play Again? (Y/N)");
	  }        /*end game event*/
return(evfl);
}

put_com()		/*put out command*/
{
#ifdef Linux
int i;
char tsr[3];

XSetForeground (xdisplay, xgc, 0x00ffffff);
XDrawString(xdisplay,pixmap[0],xgc,0,320+(font_info->ascent+font_info->descent)/2,">",1);

cursx=16;
for (i=0;i<strlen(command);i++)
{
tsr[0]=command[i];
tsr[1]=0;
//tsr[1]=30;
//tsr[2]=0;
XDrawString(xdisplay,pixmap[0],xgc,cursx,320+(font_info->ascent+font_info->descent)/2,tsr,2);
cursx+=16;
//if (i==strlen(command)) cursx-=16;
//XDrawString(xdisplay,pixmap[0],xgc,16,320+(font_info->ascent+font_info->descent)/2,command,strlen(command));
}
//cursx+=16;

draw_cursor();
//draw cursor after text

ShowScreen2();

//show only this part of screen
//ShowScreen();
#endif
#ifdef DOS
setcolor(15);
settextstyle(0,0,2);
outtextxy(0,310,">");			/*display cursor*/
outtextxy(16,310,command);		/*display current command*/
outtextxy(cursx,cursy,cursor);
#endif
}	/*end put_com*/

drob()
{
int d;

for(d=0;d<NUMOBJ;d++)			/*draw objects*/
  {
  if (obj[d].loc==curloc)
   {
    draw_obj(d);
    }
  }   /*end objects for loop*/
}	/*end drob*/

getmob()
{
#ifdef DOS
getimage(0,155,136,203,screen[6]);
#endif
}

getbroad()
{
#ifdef DOS
getimage(100,179,172,180,screen[7]);
#endif
}

getbspike()
{
#ifdef DOS
getimage(0,56,8,80,screen[8]);
#endif
}

drmob()
{
int a;
int th,tw;


#ifdef Linux
//first erase cars - brute force method
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,0,150, 0,150,640,130);
#endif
for (a=0;a<NUMCAR;a++)
  {
  if (mobj[a].loc==curloc)
    {
#ifdef Linux
    if (curloc==55&&a==14)   //car in some special location?
      {
      XPutImage(xdisplay,pixmap[0],xgc,car[14],0,0,423,112,136,48);

      }
    else 
      {
//erase char first for linux because no page flipping ?
      //XPutImage(xdisplay,pixmap[0],xgc,TitleImage,mobj[a].p[0]+CARSPD,mobj[a].p[1],mobj[a].p[0]+CARSPD,mobj[a].p[1],136,48);

//draw car
      XPutImage(xdisplay,pixmap[0],xgc,car[a],0,0,mobj[a].p[0],mobj[a].p[1],136,48);
      }

#endif
#ifdef DOS
    if (curloc==55&&a==14) putimage(423,112,car[14],COPY_PUT);
    else putimage(mobj[a].p[0],mobj[a].p[1],car[a],COPY_PUT);
#endif
    }
  }

#ifdef Linux
//now show all cars brute force method
//    XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,155,640,125, 0,155);



//XGetGeometry(xdisplay, xwindow, root_win, x_return, y_return, width_return,height_return, border_width_return, depth_return);
//th=*height_return; 
//tw=*width_return;  

//if (tw==640 && th==350)
  ShowScreenK();
//else
//  ShowScreenF();

#endif

}

drroad()
{
int a;

#ifdef Linux
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,0,mobj[NUMCAR].p[1], 0,mobj[NUMCAR].p[1],640,2);
#endif

for (a=0;a<NUMROAD;a++)
#ifdef Linux
XPutImage(xdisplay,pixmap[0],xgc,road[a],0,0,mobj[a+NUMCAR].p[0],mobj[a+NUMCAR].p[1],72,1);
#endif
#ifdef DOS
  putimage(mobj[a+NUMCAR].p[0],mobj[a+NUMCAR].p[1],road[a],COPY_PUT);
#endif

#ifdef Linux
ShowScreenRD();

//    XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,mobj[NUMCAR].p[1],640,2, 0,mobj[NUMCAR].p[1]);
#endif
}

drspike()
{
int a;

#ifdef Linux
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,0,mobj[NUMCAR+NUMROAD].p[1], 0,mobj[NUMCAR+NUMROAD].p[1],640,25);
#endif


for (a=0;a<NUMSPIKE;a++)
#ifdef Linux
XPutImage(xdisplay,pixmap[0],xgc,spike[a],0,0,mobj[a+NUMCAR+NUMROAD].p[0],mobj[a+NUMCAR+NUMROAD].p[1],8,24);
#endif
#ifdef DOS
  putimage(mobj[a+NUMCAR+NUMROAD].p[0],mobj[a+NUMCAR+NUMROAD].p[1],spike[a],COPY_PUT);
#endif

#ifdef Linux
ShowScreenSP();

//    XCopyArea(xdisplay,pixmap[0],xwindow,xgc,0,mobj[NUMCAR+NUMROAD].p[1],640,25, 0,mobj[NUMCAR+NUMROAD].p[1]);
#endif


}

mvmob()
{
int a;

for (a=0;a<NUMCAR;a++)
  {
  carx[a]=mobj[a].p[0];
  if (a<15)
    {
    mobj[a].p[0]=mobj[a].p[0]-CARSPD;
    if (mobj[a].p[0]<0)
      {
      mobj[a].p[0]=500;
      mobj[a].loc++;
      if (mobj[a].loc>23)  mobj[a].loc=8;
      }
    }
  else
    {
    mobj[a].p[0]=mobj[a].p[0]+CARSPD;
    if (mobj[a].p[0]>500)
      {
      mobj[a].p[0]=4;
      mobj[a].loc--;
      if (mobj[a].loc<8)  mobj[a].loc=23;
      }
    }
  }
}

mvroad()
{
int a;

for (a=0;a<NUMROAD;a++)
  {
  roadx[a]=mobj[a+NUMCAR].p[0];
  mobj[a+NUMCAR].p[0]=mobj[a+NUMCAR].p[0]-dx;
  if (mobj[a+NUMCAR].p[0]<0)
    mobj[a+NUMCAR].p[0]=649-dx;
    if (mobj[a+NUMCAR].p[0]>649)
      mobj[a+NUMCAR].p[0]=-dx;
  }
}

mvspike()
{
int a;

for (a=0;a<NUMSPIKE;a++)
  {
  spikex[a]=mobj[a+NUMCAR+NUMROAD].p[0];
  mobj[a+NUMCAR+NUMROAD].p[0]=mobj[a+NUMCAR+NUMROAD].p[0]-dx;
  if (mobj[a+NUMCAR+NUMROAD].p[0]<0)
    mobj[a+NUMCAR+NUMROAD].p[0]=649-dx;
  if (mobj[a+NUMCAR+NUMROAD].p[0]>649)
    mobj[a+NUMCAR+NUMROAD].p[0]=-dx;
  }
}

erase_mob()
{
int a;

#ifdef DOS
for (a=0;a<NUMCAR;a++)
  {
  if (a<15)
    {
    if (mobj[a].loc==curloc || (mobj[a].loc==curloc+1 && mobj[a].p[0]==500)||
       (curloc==23 && mobj[a].loc==8 && mobj[a].p[0]==500))
	  putimage(carx[a],mobj[a].p[1],screen[6],COPY_PUT);
    }
  else
    {
    if (mobj[a].loc==curloc || (mobj[a].loc==curloc-1 && mobj[a].p[0]==4)||
       (curloc==8 && mobj[a].loc==23 && mobj[a].p[0]==4))
	  putimage(carx[a],mobj[a].p[1],screen[6],COPY_PUT);
    }
  }
  //end for a
#endif
}

erase_road()
{
int a;

#ifdef DOS
for (a=0;a<NUMROAD;a++)
  {
  putimage(roadx[a],mobj[a+NUMCAR].p[1],screen[7],COPY_PUT);
  }
#endif
}

erase_spike()
{
int a;

#ifdef DOS
for (a=0;a<NUMSPIKE;a++)
  {
  putimage(spikex[a],mobj[a+NUMCAR+NUMROAD].p[1],screen[8],COPY_PUT);
  }
#endif
}

draw_mo(int d)
{
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,mobj[d].p[0],mobj[d].p[1],
	mobj[d].p[0]+mobj[d].p[2],mobj[d].p[1]+mobj[d].p[3]);
#endif
#ifdef DOS
    setfillstyle(SOLID_FILL, 15);      /*white box*/
    bar(mobj[d].p[0],mobj[d].p[1],
	mobj[d].p[0]+mobj[d].p[2],mobj[d].p[1]+mobj[d].p[3]);
#endif
    curobj=d;
    draw_mobj();
}

draw_cbrush(int lbrush,int col)
{
#ifdef DOS
free(brushbuff);
free(cbuff);

setfillstyle(SOLID_FILL, 15);      /*clear current brush area*/
bar(CURX-9,CURY,CURX+9,CURY+18);
csize = imagesize(CURX,CURY,CURX+lbrush,CURY+lbrush);
cbuff=malloc(csize);
size = imagesize(CURX,CURY,CURX+lbrush,CURY+lbrush);
brushbuff=malloc(size);
setfillstyle(SOLID_FILL, 7);


switch (lbrush)
  {
  case 0:
#ifdef DOS
     putpixel(CURX,CURY,7);    /*brush 0*/
     getimage(CURX,CURY,CURX,CURY,cbuff);
     setfillstyle(SOLID_FILL, col);
#endif
     break;
  case 1:
#ifdef DOS
     bar(CURX,CURY,CURX+1,CURY+1);  /*brush 1*/
     getimage(CURX,CURY,CURX+1,CURY+1,cbuff);
     setfillstyle(SOLID_FILL, col);
#endif
     break;
  case 2:
#ifdef DOS
     bar(CURX,CURY,CURX+2,CURY+2);  /* brush 2*/
     getimage(CURX,CURY,CURX+2,CURY+2,cbuff);
     setfillstyle(SOLID_FILL, col);
#endif
     break;
  case 3:
#ifdef DOS
     bar(CURX,CURY,CURX+3,CURY+3);  /*brush 3*/
     getimage(CURX,CURY,CURX+3,CURY+3,cbuff);
     setfillstyle(SOLID_FILL, col);
#endif
     break;
  case 4:
#ifdef DOS
     bar(CURX,CURY,CURX+4,CURY+4);  /*brush 4*/
     getimage(CURX,CURY,CURX+4,CURY+4,cbuff);
     setfillstyle(SOLID_FILL, col);
#endif
     break;
  case 5:
#ifdef DOS
     bar(CURX,CURY,CURX+5,CURY+5);  /*brush 5*/
     getimage(CURX,CURY,CURX+5,CURY+5,cbuff);
     setfillstyle(SOLID_FILL, col);
#endif
     break;
  case 6:
#ifdef DOS
     bar(CURX,CURY,CURX+6,CURY+6);  /*brush 6*/
     getimage(CURX,CURY,CURX+6,CURY+6,cbuff);
     setfillstyle(SOLID_FILL, col);
#endif
     break;
  case 7:
#ifdef DOS
     bar(CURX,CURY,CURX+7,CURY+7);  /*brush 7*/
     getimage(CURX,CURY,CURX+7,CURY+7,cbuff);
     setfillstyle(SOLID_FILL, col);
#endif
     break;
  case 8:
#ifdef DOS
     setfillstyle(LINE_FILL,7);
     bar(CURX,CURY,CURX+8,CURY+8);  /*brush 8*/
     getimage(CURX,CURY,CURX+8,CURY+8,cbuff);
     setfillstyle(LINE_FILL, col);
#endif
     break;
  case 9:
#ifdef DOS
     setfillstyle(CLOSE_DOT_FILL, 7);
     bar(CURX,CURY,CURX+9,CURY+9);  /*brush 9*/
     getimage(CURX,CURY,CURX+9,CURY+9,cbuff);
     setfillstyle(CLOSE_DOT_FILL, col);
#endif
     break;
  case 10:
#ifdef DOS
     setfillstyle(CLOSE_DOT_FILL, 7);
     bar(CURX,CURY,CURX+10,CURY+10);  /*brush 10*/
     getimage(CURX,CURY,CURX+10,CURY+10,cbuff);
     setfillstyle(CLOSE_DOT_FILL, col);
#endif
     break;
  }
#ifdef DOS
bar(CURX,CURY,CURX+lbrush,CURY+lbrush);
getimage(CURX,CURY,CURX+lbrush,CURY+lbrush,brushbuff);
#endif

#endif
}


draw_it()
{
int xx1,yy1,xx2,yy2;	/*draw_it point coords*/
int c,radius,d;
#ifdef DOS
int mcolor;
struct action tact[1];
#endif
#ifdef Linux
int a,b,i;
int brm,sp10;
unsigned int mcolor;
struct action *tact;
char *tpstr;
#endif


#ifdef Linux
tact=(struct action *)malloc(sizeof(struct action));
tact[0].str=(char *)malloc(SLEN);
tact[0].a = (short int *)malloc(10*2);
tpstr=malloc(20);
#endif
lcolor=0;  brush=0;


#ifdef Linux
XSetForeground (xdisplay, xgc, 0x0);
XSetLineAttributes(xdisplay, xgc,1, LineSolid, CapButt|CapProjecting, JoinMiter);


#endif
#ifdef DOS
setcolor(lcolor);
setlinestyle(0,ULIN1,1);
draw_cbrush(brush,lcolor);        /*get current color and size brush*/
#endif
act2=act1;    /*save start of list*/

//fprintf(stderr,"CUR= %d\n",cur);
for (c=0;c<cur;c++)
   {
   tact[0].name=act2->name;
   tact[0].a[0]=act2->a[0];
   tact[0].a[1]=act2->a[1];
   tact[0].a[2]=act2->a[2];
   tact[0].a[3]=act2->a[3];
   tact[0].a[4]=act2->a[4];
   strcpy(tact[0].str,act2->str);
   if (curobj>-1) 	/*we are drawing an object*/
     {
     d=tact[0].name;
     if (d>2)                    /*2 point translation*/
       {
       if (lflag==3)
	 {
	 tact[0].a[0]+=obj[curobj].p[0];       /*add offsets*/
	 tact[0].a[1]+=obj[curobj].p[1];
	 }
       else
	 {
	 tact[0].a[0]+=mobj[curobj].p[0];       /*add offsets*/
	 tact[0].a[1]+=mobj[curobj].p[1];
	 }
       }
     if (d==4 || d==6 || d==10)	/*4 point translation*/
       {
       if (lflag==3)
	 {
	 tact[0].a[2]+=obj[curobj].p[0];       /*add offsets*/
	 tact[0].a[3]+=obj[curobj].p[1];
	 }
       else
	 {
	 tact[0].a[2]+=mobj[curobj].p[0];       /*add offsets*/
	 tact[0].a[3]+=mobj[curobj].p[1];
	 }
       }
     }    /*end if we are drawing object*/


//fprintf(stderr,"tact= %d\n",tact[0].name);

   switch (tact[0].name)
      {
      case 0:
	lcolor=tact[0].a[0];
#ifdef Linux
//map colors

lincolor=klmap[lcolor];




XSetForeground (xdisplay, xgc, lincolor);
//XSetForeground (xdisplay, xgc, 0x0000ff00);
#endif
#ifdef DOS
	setcolor(lcolor);
	setfillstyle(1,lcolor);
	draw_cbrush(brush,lcolor);    /*get current color and size brush*/
#endif
	break;
      case 1:
	brush=tact[0].a[0];
#ifdef Linux
  XSetLineAttributes(xdisplay, xgc,2*(brush>0)+1, LineSolid, CapButt|CapProjecting, JoinMiter);
//width=1, line_style, cap_style, join_style

       //change brush size/pattern
	linbrush=brush;
#endif        
#ifdef DOS
	draw_cbrush(brush,lcolor);    /*get current color and size brush*/
#endif
	break;
      case 2:
	lstyle=tact[0].a[0];
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
	xx1=tact[0].a[0];
	yy1=tact[0].a[1];
#ifdef Linux
//square brush
if (linbrush>0)
{
if (linbrush==7 || linbrush==10) {sp10=0;}  //10 is the title page statue
for(a=xx1;a<xx1+linbrush+1;a++)
 {
  for(b=yy1;b<yy1+linbrush+1;b++)

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
 XDrawPoint(xdisplay, pixmap[0], xgc, xx1, yy1);
#endif


#ifdef DOS
	putimage(xx1,yy1,brushbuff,COPY_PUT);
#endif
	break;
      case 4:
#ifdef DOS
	setfillstyle(1,lcolor);
	setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
#endif
	xx1=tact[0].a[0];
	yy1=tact[0].a[1];
	xx2=tact[0].a[2];
	yy2=tact[0].a[3];
#ifdef Linux
XDrawLine(xdisplay, pixmap[0], xgc, xx1,yy1,xx2,yy2);
//XDrawLine(xdisplay,xwindow, xgc, xx1,yy1,xx2,yy2);
#endif
#ifdef DOS
	line(xx1,yy1,xx2,yy2);
#endif
	break;
      case 5:
#ifdef DOS
	setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
#endif
	xx1=tact[0].a[0];
	yy1=tact[0].a[1];
	radius=tact[0].a[2];
#ifdef Linux
//        XDrawArc(xdisplay,pixmap[0], xgc, xx1-(radius/2), yy1-(radius/2), radius, radius, 0, 360*64);
        XDrawArc(xdisplay,pixmap[0], xgc, xx1-radius, yy1-radius, radius*2, radius*2, 0, 360*64);
#endif
#ifdef DOS
	circle(xx1,yy1,radius);
#endif
	break;
      case 6:
#ifdef DOS
	setlinestyle(lstyle,ULIN1,2*(brush>0)+1);
#endif
	xx1=tact[0].a[0];
	yy1=tact[0].a[1];
	xx2=tact[0].a[2];
	yy2=tact[0].a[3];
#ifdef Linux
if (xx1>xx2)  { xx2=xx1;  xx1=tact[0].a[2]; }
if (yy1>yy2)  { yy2=yy1;  yy1=tact[0].a[3]; }
XDrawRectangle(xdisplay,pixmap[0], xgc, xx1, yy1, xx2-xx1, yy2-yy1);


#endif
#ifdef DOS
	rectangle(xx1,yy1,xx2,yy2);
#endif
	break;
      case 7:
	xx1=tact[0].a[0];
	yy1=tact[0].a[1];
	border=tact[0].a[2];
	pattern=tact[0].a[3];

	if (pattern==15)  mcolor=tact[0].a[4];
#ifdef Linux
//i have to copy the pixmap to an image
//fill in the part on the image
//then copy the image back to the pixmap


//was xgetimage here
if (fximage>0) 
  {

  XDestroyImage(fximage);}
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


//mcolor=mix color for 15

//#if 0 
memset(pmp,0,81*301);

mixcolor=mcolor;
bordercolor=klmap[border];
//floodlinpatfill4((unsigned int)((xx1<<0x10)|yy1),(unsigned short int)0);
//fprintf(stderr,"fill3= %d,%d\n",xx1,yy1);
//floodlinpatfill3(xx1,yy1,0,0);

floodlinpatfill3(xx1,yy1,0,0,0);

//floodlinpatfill2(xx1,yy1,klmap[border],lincolor,mcolor,0,0);
//floodlinpatfill2b(xx1,yy1,klmap[border],lincolor,mcolor,0,0);
//floodwfill(xx1,yy1,klmap[border],lincolor,mcolor);
//floodlinpatfill(xx1,yy1,klmap[border],lincolor,mcolor,0,0);

//was xputimage here
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
             floodfill(xx1,yy1,border);
	   else
	     floodwfill(xx1,yy1,border,lcolor,mcolor);
#endif
	break;
      case 8:
	xx1=tact[0].a[0];
	yy1=tact[0].a[1];
	style=tact[0].a[2];
	direction=tact[0].a[3];
	tsize=tact[0].a[4];
#ifdef Linux
strcpy(font_name,"*chart*");
//strcpy(font_name,"*helv*");
//strcpy(font_name,"*courier (bit*");
if (tsize==1) {tsize=0;}
if (tsize==2) {tsize=3;}  //make 16= 18
if (tsize==15)
{//strcpy(font_name,"*");
  tsize=30;
  strcpy(font_name,PATH);
  strcat(font_name,LPATH);
  strcat(font_name,"2020.bmp");
  load_bitmap(font_name);
}  //72 is most size font
else
{
//sprintf(tpstr,"%d*",tsize*2+12);
sprintf(tpstr,"");
strcat(font_name,tpstr);
//fprintf(stderr,"%s",font_name);
font_info=XLoadQueryFont(xdisplay,font_name);
if (!font_info)
   {
   fprintf(stderr, "Could not load font %s\n",font_name);
   strcpy(font_name,"*chart*24*");
   font_info=XLoadQueryFont(xdisplay,font_name);
  // exit(1);
   }
XSetFont(xdisplay,xgc,font_info->fid);

//font_path=(char **)XGetFontPath(xdisplay,&font_path_num);
//   fprintf(stderr, "Font path=\n%s %d\n",font_path[0],font_path_num);

if (direction) { //vert
for(i=0;i<strlen(tact[0].str);i++) {
XDrawString(xdisplay,pixmap[0],xgc,xx1,yy1+(font_info->ascent+font_info->descent)/2+(font_info->ascent+font_info->descent)*i,&tact[0].str[i],1);
}  //end for
}
else {  //horiz
XDrawString(xdisplay,pixmap[0],xgc,xx1,yy1+(font_info->ascent+font_info->descent)/2,tact[0].str,strlen(tact[0].str));

}  //end if direciton
}//end else special large 2020 font
#endif
#ifdef DOS
	settextstyle(style,direction,tsize);
	setusercharsize(tsize+1,1,tsize+1,1);
	outtextxy(xx1,yy1,tact[0].str);
#endif
	break;
      case 9:
	xx1=tact[0].a[0];
	yy1=tact[0].a[1];
	radx=tact[0].a[2];
	rady=tact[0].a[3];
#ifdef Linux
//   XDrawArc(xdisplay,pixmap[0],xgc,xx1-(radx/2),yy1-(rady/2),radx,rady,0,360*64);
   XDrawArc(xdisplay,pixmap[0],xgc,xx1-radx,yy1-rady,radx*2,rady*2,0,360*64);
#endif
#ifdef DOS
	ellipse(xx1,yy1,SANG,EANG,radx,rady);
#endif
	break;
      case 10:
#ifdef DOS
        setfillstyle(1,lcolor);
#endif
	xx1=tact[0].a[0];
	yy1=tact[0].a[1];
	xx2=tact[0].a[2];
	yy2=tact[0].a[3];
#ifdef Linux

if (xx1>xx2)  { xx2=xx1;  xx1=tact[0].a[2]; }
if (yy1>yy2)  { yy2=yy1;  yy1=tact[0].a[3]; }

        XSetFillStyle(xdisplay, xgc, FillSolid);
//        XFillRectangle(xdisplay, pixmap[0], xgc, xx1, yy1, xx2, yy2);
        XFillRectangle(xdisplay, pixmap[0], xgc, xx1, yy1, xx2-xx1, yy2-yy1+1);


#endif
#ifdef DOS
	bar(xx1,yy1,xx2,yy2);
#endif
	break;
      }     	/*end switch*/
   act2=act2->next;    /*move up the list*/


   }		/*end for*/
act2=act1;   /*go back to beginning*/
act3=act1;
for (c=0;c<cur;c++)
  {
  act1=act2->next;
  free(act2);
  act2=act1;
  }
free(act1);

curobj=-1;
/*setcolor(0);*/
#ifdef DOS
setfillstyle(SOLID_FILL, 0);
bar(0,301,640,350);   /*black bottom */
#endif

#ifdef Linux
//free(tact[0].a);
//free(tact[0].str);
//free(tact);
//free(tpstr);



//set font back for putout
strcpy(font_name,"*chart*");

//sprintf(tpstr,"%d*",18);
sprintf(tpstr,"");
strcat(font_name,tpstr);

font_info=XLoadQueryFont(xdisplay,font_name);
if (!font_info)
   {
   fprintf(stderr, "Could not load font %s\n",font_name);
   strcpy(font_name,"*chart*24*");
   font_info=XLoadQueryFont(xdisplay,font_name);
  // exit(1);
   }
XSetFont(xdisplay,xgc,font_info->fid);



#endif

}   /*end draw_it*/

#ifdef Linux
floodlinpatfill4(unsigned int sb,unsigned short int lcb)
{  
unsigned int nukl;
unsigned int tf;
unsigned int bitf,tst;
short int sx,sy;
unsigned char lcx,lcy;

sx=(sb>>0x10);
sy=(sb&0xffff);
lcx=(lcb>>0x8);
lcy=(lcb&0xff);

nukl=XGetPixel(fximage,sx,sy);


tst=(sx/32)+(sy*20);


if (nukl!=bordercolor && (*(pmp+tst)&(1<<(sx%32)))==0)//border or have been here
  {  //this is not a border or already colored pixel


  bitf=(hpat[linpat][lcy]&(1<<lcx));//>>(7-lcx);


  tf=lincolor*(bitf>0)+mixcolor*(bitf>0);


    *(pmp+tst)|=(1<<(sx%32));  //set this pixel to 1 in the pixel map

    XPutPixel(fximage,sx,sy,tf);


sb=(sx<<0x10)|sy;
//lcb=(lcx<<0x8|lcy);



//#if 0 
//#if 0

  if (sx>0)
    {
sb=((sx-1)<<0x10)|sy;
    if (lcx==0)
      {
lcb=(7<<0x8|lcy);
      floodlinpatfill4(sb,lcb);
      }
    else
      {
lcb=((lcx-1)<<0x8|lcy);
      floodlinpatfill4(sb,lcb);
      }
    }




  if (sx<639)  //550) //639) 
    {
sb=((sx+1)<<0x10)|sy;
    if (lcx==7)
      {
lcb=lcy;
      floodlinpatfill4(sb,lcb);
      }
    else
      {
lcb=((lcx+1)<<0x8|lcy);
      floodlinpatfill4(sb,lcb);
      }
    }
//#endif



  if (sy<299) //286 //3)  //9)//2) //9)
    {
sb=(sx<<0x10)|(sy+1);
    if (lcy==7)
      {
lcb=(lcx<<0x8);
      //MyS[cursta].funk=&floodlinpatfill4;//(sb,lcb);
      //MyS[cursta].para=sb;
      //MyS[cursta].para2=lcb;
      //&MyS[cursta]
      //cursta++;
      floodlinpatfill4(sb,lcb);
	
      }
    else
      {
lcb=(lcx<<0x8|(lcy+1));
      floodlinpatfill4(sb,lcb);
      }
    }
//#endif 


  if (sy>0)
    {
sb=(sx<<0x10)|(sy-1);
    if (lcy==0)
      {
lcb=(lcx<<0x8|7);
      floodlinpatfill4(sb,lcb);
      }
    else
      {
lcb=(lcx<<0x8|(lcy-1));
      floodlinpatfill4(sb,lcb);
      }
    }





//#endif

  }

}
#endif



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




#ifdef Linux
floodlinpatfill(int sx,int sy, unsigned int lb, unsigned int lc1,unsigned int lc2,int lcx,int lcy)
{  
unsigned int nukl;
unsigned int tf;
unsigned int bitf;

nukl=XGetPixel(fximage,sx,sy);
//if (nukl!=lb && sx>-1 && sx<640 && sy>-1 && sy<300) / && nukl!=lc2)

if (nukl!=lb && nukl!=lc1)// && nukl!=lc2)
  {  //this is not a border or already colored pixel
  bitf=(hpat[linpat][lcy]&(1<<lcx));//>>(7-lcx);

  tf=lc1*(bitf>0)+lc2*(bitf>0);

//  if (nukl!=tf)
    XPutPixel(fximage,sx,sy,tf);
  if (sx>0)
    {
    if (lcx==0)
      {
      floodlinpatfill(sx-1,sy,lb,lc1,lc2,7,lcy);
      }
    else
      {
      floodlinpatfill(sx-1,sy,lb,lc1,lc2,lcx-1,lcy);
      }
    }
  if (sy>0)
    {
    if (lcy==0)
      {
      floodlinpatfill(sx,sy-1,lb,lc1,lc2,lcx,7);
      }
    else
      {
      floodlinpatfill(sx,sy-1,lb,lc1,lc2,lcx,lcy-1);
      }
    }
  if (sx<639)
    {
    if (lcx==7)
      {
      floodlinpatfill(sx+1,sy,lb,lc1,lc2,0,lcy);
      }
    else
      {
      floodlinpatfill(sx+1,sy,lb,lc1,lc2,lcx+1,lcy);
      }
    }
  if (sy<299)
    {
    if (lcy==7)
      {
      floodlinpatfill(sx,sy+1,lb,lc1,lc2,lcx,0);
      }
    else
      {
      floodlinpatfill(sx,sy+1,lb,lc1,lc2,lcx,lcy+1);
      }
    }
 

  }
}
#endif




#ifdef Linux
floodlinfill(int sx,int sy, unsigned int lb, unsigned int lc1,unsigned int lc2,unsigned int lcf)
{
unsigned int nukl;

nukl=XGetPixel(fximage,sx,sy);
if (nukl!=lb && nukl!=lc1 && nukl!=lc2)
  {  //this is not a border or already colored pixel
  XPutPixel(fximage,sx,sy,lc1*lcf + lc2*!lcf);
  if (sx>0)
    floodlinfill(sx-1,sy,lb,lc1,lc2,!lcf);
  if (sy>0)
    floodlinfill(sx,sy-1,lb,lc1,lc2,!lcf);
  if (sx<639)
    floodlinfill(sx+1,sy,lb,lc1,lc2,!lcf);
  if (sy<299)
    floodlinfill(sx,sy+1,lb,lc1,lc2,!lcf);
 

  }
}
#endif

#ifdef Linux
floodfill(int sx, int sy, unsigned int bord)
{
unsigned int nukl;

nukl=XGetPixel(fximage,sx,sy);
if (nukl!=bord && nukl!=lincolor)
  {  //this is not a border pixel
  XPutPixel(fximage,sx,sy,lincolor);


  if (sx>0)
    floodfill(sx-1,sy,bord);
  if (sy>0)
    floodfill(sx,sy-1,bord);
  if (sx<639)
    floodfill(sx+1,sy,bord);
  if (sy<299)
    floodfill(sx,sy+1,bord);

  }
}
#endif

#ifdef Linux
floodwfill(int sx, int sy, unsigned int lb, unsigned int lc1,unsigned int lc2)
#endif
#ifdef DOS
floodwfill(int sx, int sy, int lb, int lc1,int lc2)    /*flood fill shape with white*/
#endif
{
#ifdef Linux
mofillxy(sx,sy,lb,lc1,lc2,0,-1,-1);
mofillxy(sx-1, sy+1, lb, lc1, lc2, 0, -1, 1);
//mofillxy(sx, sy-1, lb, lc1, lc2, 0, -1, 1);
mofillxy(sx+1, sy, lb, lc1, lc2, 1, 1, -1);
mofillxy(sx, sy+1, lb, lc1, lc2, 1, 1, 1);

//mofillxy(sx, sy-1, lb, lc1, lc2, 0, 1, 1);
//mofillxy(sx, sy+1, lb, lc1, lc2, 0, -1, 1);
#endif

#ifdef DOS
mofillxy(sx,sy,lb,lc1,lc2,0,-1,-1);
mofillxy(sx, sy-1, lb, lc1, lc2, 0, -1, 1);
mofillxy(sx, sy, lb, lc1, lc2, 0, 1, -1);
mofillxy(sx, sy+1, lb, lc1, lc2, 0, 1, 1);
#endif


}

#ifdef Linux
mofillxy(int sx,int sy, unsigned int lb, unsigned int lc1, unsigned int lc2, int lcf, int xd, int yd)
#endif
#ifdef DOS
mofillxy(int sx,int sy,int lb,int lc1,int lc2,int lcf,int xd,int yd)
#endif
{
#ifdef Linux
if (XGetPixel(fximage,sx,sy)!=lb && (sx>-1) &&  (sy>-1) && (sx<640) && (sy<299))
  {
//  mofillx(sx, sy, lb, lc1, lc2,lcf,xd,yd);
//  mofillxy(sx,sy+yd,lb,lc1,lc2,lcf,xd,yd);
mofillx(sx, sy, lb, lc1, lc2,(lcf==0),xd,yd);
  mofillxy(sx,sy+yd,lb,lc1,lc2,(lcf==0),xd,yd);
  }

#endif
#ifdef DOS
if (getpixel(sx,sy)!=lb && (sx>-1) &&  (sy>-1) && (sx<640) && (sy<301))
  {
  mofillx(sx, sy, lb, lc1, lc2,lcf,xd,yd);
  mofillxy(sx,sy+yd,lb,lc1,lc2,lcf,xd,yd);
  }
#endif
}

#ifdef Linux
mofillx(int sx,int sy, unsigned int lb, unsigned int lc1, unsigned int lc2, int lcf, int xd, int yd)
#endif
#ifdef DOS
mofillx(int sx,int sy, int lb, int lc1, int lc2, int lcf, int xd, int yd)
#endif
{
int lc3;
#ifdef Linux
if (XGetPixel(fximage,sx,sy)!=lb && (sx>-1) &&  (sy>-1) && (sx<639) && (sy<300))
  {
  if (lcf==1) lc3=lc1;
  else lc3=lc2;

  XPutPixel(fximage,sx,sy,lc3);
  mofillx(sx+xd,sy,lb,lc1,lc2,(lcf==0),xd,yd);
  }
#endif

#ifdef DOS
if (getpixel(sx,sy)!=lb && (sx>-1) &&  (sy>-1) && (sx<640) && (sy<301))
  {
  if (lcf==1) lc3=lc1;
  else lc3=lc2;
  putpixel(sx,sy,lc3);
  mofillx(sx+xd,sy,lb,lc1,lc2,(lcf==0),xd,yd);
  }
#endif
}

mofilly(int sx,int sy, int lb, int lc1, int lc2, int lcf, int xd, int yd)
{
int lc3;


#ifdef Linux
if (XGetPixel(fximage,sx,sy)!=lb && (sx>-1) &&  (sy>-1) && (sx<640) && (sy<299))
  {
  if (lcf==1) lc3=lc1;
  else lc3=lc2;
  XPutPixel(fximage,sx,sy,lc3);
  mofillx(sx,sy+yd,lb,lc1,lc2,(lcf==0),xd,yd);
  }
#endif

#ifdef DOS
if (getpixel(sx,sy)!=lb && (sx>-1) &&  (sy>-1) && (sx<640) && (sy<301))
  {
  if (lcf==1) lc3=lc1;
  else lc3=lc2;
  putpixel(sx,sy,lc3);
  mofillx(sx,sy+yd,lb,lc1,lc2,(lcf==0),xd,yd);
  }
#endif
}

load_file()
{
FILE *fptr;
#ifdef Linux
//char *nm2,*nm3,*nm;
char nm2[256],nm3[256],nm[256];
#endif
#ifdef DOS
char nm2[256],nm3[256],nm[256];
#endif
int a;
#ifdef Linux
int rex,b;
//char tmpstr[SLEN+1];
char *tmpstr;
struct action *tact;
char tmpst2[255];
#endif
#ifdef DOS
struct action tact[1];
#endif


#ifdef Linux
tmpstr=(char *) malloc(SLEN+2);
//nm2=malloc(256);
//nm3=malloc(256);
//nm=malloc(256);
tact=(struct action *) malloc(sizeof(struct action));
tact[0].str=malloc(SLEN);
tact[0].a=(short int *)malloc(10*4);
#endif
a=0;

#ifdef DOS
getcwd(PATH,512);
strcat(PATH,LPATH);
#endif


switch (lflag)
  {
  case 0:
  case 5:
#ifdef Linux
    sprintf(nm,"%d",curloc);
#endif
#ifdef DOS
    itoa(curloc,nm,10);
#endif
#ifdef Linux
	strcpy(nm2,PATH);
    strcat(nm2,LPATH);
#endif
#ifdef DOS
    strcpy(nm2,PATH);
#endif
    strcat(nm2,nm);
    strcpy(nm3,nm2);
    strcpy(nm,nm2);
    if (curloc==0)
#ifdef Linux
      strcat(nm,".ply");
#endif
#ifdef DOS
      strcat(nm,".PLY");
#endif
    else
#ifdef Linux
      strcat(nm,".pic");
#endif

#ifdef DOS
      strcat(nm,".PIC");
#endif
    break;
  case 1:
    strcpy(nm,PATH);
#ifdef Linux
      strcat(nm,LPATH);
      strcat(nm,"Def.pic");
#endif
#ifdef DOS
    strcat(nm,"DEF.PIC");
#endif
    break;
  case 2:
    strcpy(nm,PATH);
#ifdef Linux
      strcat(nm,LPATH);
      strcat(nm,"Ted.pic");
#endif
#ifdef DOS
    strcat(nm,"TED.PIC");
#endif
    break;
  case 3:
    strcpy(nm,PATH);
#ifdef Linux
    strcat(nm,LPATH);
    strcat(nm,"Obj");
#endif
#ifdef DOS
    strcat(nm,"OBJ");
#endif

#ifdef Linux
    sprintf(nm2,"%d",curobj);
#endif
#ifdef DOS
    itoa(curobj,nm2,10);
#endif
    strcat(nm,nm2);
#ifdef Linux
    strcat(nm,".pic");
#endif
#ifdef DOS
    strcat(nm,".PIC");
#endif
    break;
  case 4:
    strcpy(nm,PATH);
#ifdef Linux
      strcat(nm,LPATH);
      strcat(nm,"Mobj");
#endif
#ifdef DOS
    strcat(nm,"MOBJ");
#endif
#ifdef Linux
    sprintf(nm2,"%d",curobj);
#endif
#ifdef DOS
    itoa(curobj,nm2,10);
#endif
    strcat(nm,nm2);
#ifdef Linux
    strcat(nm,".pic");
#endif
#ifdef DOS
    strcat(nm,".PIC");
#endif
    break;
  }
if ( (fptr=fopen(nm,"rb"))==NULL)
   {printf("Can't open file %s",nm); 
#ifdef Linux
  while (fread(&Key,1,1,input)!=1) {}
#endif
#ifdef DOS
    getch(); 
#endif
    }
else
   {




   act1=malloc(sizeof(struct daction));   /*make first link*/



#ifdef Linux

act1->str=malloc(SLEN);
act1->a=malloc(10*2);

#endif


   act2=act1;   /*save beginning of list*/
#ifdef Linux
     rex=1;
     while(rex==1)
     {
//   int name;  /*0-color,1-brush,2-lstyle,3-point,*/
	      /*4-line,5-circle,6-rect,7-fill,8-text*/
 //  int a[5];   /*x1-color-brush,y1-style,x2-rad-direct-tsize,y2-strlen*/
//   char str[SLEN];  /*string*/

     rex=fread(&tact[0].name,sizeof(short int),1,fptr);


    for(b=0;b<5;b++)
      {
      fread(&tact[0].a[b],sizeof(short int),1,fptr);
      }

//fread(&tmpstr,2,1,fptr);  //2 extra?

    for (b=0;b<40;b++)
{//for now read in 40 bytes because reading in 0s cause problrem
fread(&tmpstr[b],1,1,fptr);
}
//    fread(&tmpstr,sizeof(SLEN),1,fptr);

   //if (tmpstr[0] != 0)
    //  {
      strcpy(tact[0].str,tmpstr);
    //  }





//    fread(&tact[0].str,sizeof(SLEN),1,fptr);
    



 #endif
#ifdef DOS
     while( fread(&tact[0],sizeof(tact[0]),1,fptr)==1)
        {
#endif
	act2->name=tact[0].name;
	act2->a[0]=tact[0].a[0];
	act2->a[1]=tact[0].a[1];
	act2->a[2]=tact[0].a[2];
	act2->a[3]=tact[0].a[3];
	act2->a[4]=tact[0].a[4];

#ifdef Linux
        if (tact[0].str != 0)
          {
//fprintf(stderr,"string= %s\n",tact[0].str);
#endif
	strcpy(act2->str,tact[0].str);
#ifdef Linux
           }
#endif
//fprintf(stderr,"got here2 act2 %p %d",act2->next,sizeof(struct daction));
#ifdef Linux
	act2->next=malloc(30);//30);  //malloc(sizeof(struct daction));=16

#endif
#ifdef DOS
	act2->next=malloc(sizeof(struct daction));   /*allocate next link*/
#endif

	act2=act2->next;    /*move up the list*/
#ifdef Linux

act2->str=malloc(SLEN);

act2->a=malloc(10*4);
#endif

	a++;
	}
     cur=a;
   }
fclose(fptr);



if (lflag==0)
  {
  if (curloc!=0)
    {
#ifdef Linux
    strcat(nm3,".dor");
#endif
#ifdef DOS
    strcat(nm3,".DOR");
#endif
    if ( (fptr=fopen(nm3,"rb"))==NULL)
       {printf("Can no open file %s",nm3); 
#ifdef Linux
  while (fread(&Key,1,1,input)!=1) {}
#endif
#ifdef DOS
    getch(); 
#endif
       }
    else
       fread(&door,sizeof(door[0]),NUMDOR,fptr);


    fclose(fptr);
    }

#ifdef Linux
  strcat(nm2,".edg");
#endif
#ifdef DOS
  strcat(nm2,".EDG");
#endif
  if ( (fptr=fopen(nm2,"rb"))==NULL)
     {printf("Can no open file %s",nm2);
#ifdef Linux
  while (fread(&Key,1,1,input)!=1) {}
#endif
#ifdef DOS
    getch();
#endif
     }
  else
     {

     fread(&pntx[0],sizeof(pntx[0]),4,fptr);
     fread(&pnty[0],sizeof(pnty[0]),4,fptr);
     }
  fclose(fptr);
  }



#ifdef Linux
free(tmpstr);
//free(nm2);
//free(nm3);
//free(nm);
free(tact[0].str);
free(tact[0].a);
free(tact);


#endif

}

load_obj()
{
FILE *fptr;
#ifdef Linux
struct tmpobj
  {
  char name[11];
  short int p[4];
  short int loc;
  };
#endif
#ifdef DOS
struct tmpobj
  {
  char name[11];
  int p[4];
  int loc;
  };
#endif
struct tmpobj tmpo[1];
char nm[256],nm2[256];
int a;

a=0;
#ifdef DOS
getcwd(PATH,512);
#endif
strcat(PATH,LPATH);

#ifdef Linux
fprintf(stderr,"Copying objects to memory...\n");
#endif
for(a=0;a<NUMOBJ;a++)
  {
  strcpy(nm,PATH);
#ifdef Linux
   strcat(nm,"Obj");
#endif
#ifdef DOS
  strcat(nm,"OBJ");
#endif
#ifdef Linux
    sprintf(nm2,"%d",a);
#endif
#ifdef DOS
  itoa(a,nm2,10);
#endif
  strcat(nm,nm2);
#ifdef Linux
  strcat(nm,".fil");
#endif
#ifdef DOS
  strcat(nm,".FIL");
#endif
  if ( (fptr=fopen(nm,"rb"))==NULL)
     {printf("Can no open file %s",nm); 
#ifdef Linux
  while (fread(&Key,1,1,input)!=1) {}
#endif
#ifdef DOS
    getch(); 
#endif
}
  else 
     {
#ifdef Linux
     //fread(&tmpo[0].name,sizeof(struct tmpobj),1,fptr);
     fread(&tmpo[0].name,11,1,fptr);//sizeof(struct tmpobj),1,fptr);
     tmpo[0].name[10]=0;
     fread(&tmpo[0].p,8,1,fptr);
     fread(&tmpo[0].loc,2,1,fptr);
#endif
#ifdef DOS
     fread(&tmpo,sizeof(tmpo[0]),1,fptr);
#endif
     }
  fclose(fptr);

  strcpy(obj[a].name,tmpo[0].name);
  obj[a].p[0]=tmpo[0].p[0];  obj[a].p[1]=tmpo[0].p[1];
  obj[a].p[2]=tmpo[0].p[2];  obj[a].p[3]=tmpo[0].p[3];
  obj[a].loc=tmpo[0].loc;


  } 			/*end for*/

}

load_mobj()
{
FILE *fptr;
char nm[256],nm2[256];
int a;
#ifdef Linux
struct tmpobj
  {
  char name[11];
  short int p[4];
  short int loc;
  };
#endif
#ifdef DOS
struct tmpobj
  {
  char name[11];
  int p[4];
  int loc;
  };
#endif
struct tmpobj tmpo[1];

a=0;
#ifdef DOS
getcwd(PATH,512);
#endif
strcat(PATH,LPATH);

#ifdef Linux
fprintf(stderr,"Copying moving objects to memory...\n");
#endif

for(a=0;a<NUMMOBJ;a++)
  {

  strcpy(nm,PATH);
#ifdef Linux
  strcat(nm,"Mobj");
#endif
#ifdef DOS
  strcat(nm,"MOBJ");
#endif
#ifdef Linux
    sprintf(nm2,"%d",a);
#endif
#ifdef DOS
  itoa(a,nm2,10);
#endif
  strcat(nm,nm2);
#ifdef Linux
  strcat(nm,".fil");
#endif
#ifdef DOS
  strcat(nm,".FIL");
#endif
  if ( (fptr=fopen(nm,"rb"))==NULL)
     {printf("Can't open file %s",nm); 
#ifdef Linux
  while (fread(&Key,1,1,input)!=1) {}
#endif
#ifdef DOS
    getch(); 
#endif
}
  else
     {
#ifdef Linux
     fread(&tmpo[0].name,11,1,fptr);//sizeof(struct tmpobj),1,fptr);
     tmpo[0].name[10]=0;
     fread(&tmpo[0].p,8,1,fptr);
     fread(&tmpo[0].loc,2,1,fptr);
#endif
#ifdef DOS
     fread(&tmpo,sizeof(tmpo[0]),1,fptr);
#endif
     }
  fclose(fptr);

 

  strcpy(mobj[a].name,tmpo[0].name);
  mobj[a].p[0]=tmpo[0].p[0];  mobj[a].p[1]=tmpo[0].p[1];
  mobj[a].p[2]=tmpo[0].p[2];  mobj[a].p[3]=tmpo[0].p[3];
  mobj[a].loc=tmpo[0].loc;
  } 			/*end for*/
}

draw_obj(int d)
{
int tfl;



if (curloc==56) {  obj[130].p[0]=424;  obj[130].p[1]=176;obj[130].loc=56;}
if (spec[22]==1) {hx1=hx2=400; hy1=hy2=200; rx3=rx4=380; ry3=ry4=180; }
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,obj[d].p[0],obj[d].p[1],obj[d].p[2],obj[d].p[3]);
#endif
#ifdef DOS
    setfillstyle(SOLID_FILL, 15);      /*white box*/
    bar(obj[d].p[0],obj[d].p[1],
	obj[d].p[0]+obj[d].p[2],obj[d].p[1]+obj[d].p[3]);
#endif
    curobj=d;
tfl=lflag;
lflag=3;


load_file();

if (curloc==56) {  obj[130].p[0]=424;  obj[130].p[1]=176; obj[130].loc=56;}
if (spec[22]==1) {hx1=hx2=400; hy1=hy2=200; rx3=rx4=380; ry3=ry4=180;  spec[22]=0;}



draw_it();	/*draw object*/
lflag=tfl;

#ifdef DOS
    setfillstyle(SOLID_FILL, 0);
    bar(0,301,640,350);   /*black bottom */
#endif
}

draw_mobj()
{
int tfl,a;

tfl=lflag;
lflag=4;
load_file();
draw_it();	/*draw object*/
lflag=tfl;
}

load_traits(char lname[11])
{
#define BUFF1 11
#define BUFF2 8
char buff[BUFF1],buffs[BUFF2];
int inhandle,a;
char lnm2[256];
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
#if 0//def Linux
//for now change all but first letter to lower case
tempst=(char *)malloc(11);
newname=(char *)malloc(11);
memset (newname, 0, 11);
memset (tempst, 0, 11);
strcpy(newname,lname);
newname[1]=0;
for(a=1;a<strlen(lname);a++)
{
d=(char)*(lname+a)+32;  //lower case
tempst[a-1]=d;
}
strcat(newname,tempst);
newname[strlen(tempst)+1]=0;

strcat(lnm2,newname);
strcat(lnm2,".txt");
free(tempst);
#endif
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

bhit()
{
float m1,m2;		/*slopes of boundary checks*/
float diff0,diff1,diff2,diff3;
int a;

  diff1=pntx[1]-pntx[0];
  diff0=pnty[1]-pnty[0];
  diff2=hx1+dx-pntx[0];
					/*line 0*/ /*left*/
  if ((diff1==0)&&(hx1+dx<=pntx[0]))  hitflag=1;    /*vert line*/
  else
    {
#ifdef Linux
    m1=fabs((float)diff0/(diff1+!(diff1)));
    m2=fabs((float)(hy1+dy+HMAN-pnty[0])/(diff2+!(diff2)));
#endif
#ifdef DOS
    m1=abs((float)diff0/(diff1+!(diff1)));
    m2=abs((float)(hy1+dy+HMAN-pnty[0])/(diff2+!(diff2)));
#endif
    if (m2>1.0) m2=1.0;
    if ((int)((m2-0.01)*100)<=(int)(m1*100)  &&
      (int)(m1*100)<=(int)((m2+0.01)*100)) hitflag=1;
    }
  /*line 2*/          /*right*/
  diff1=pntx[2]-pntx[3];
  diff0=pnty[2]-pnty[3];
  diff2=hx1+dx+WMAN-pntx[3];
  diff3=hy1+dy+HMAN-pnty[3];
  if ((diff1==0)&&(hx1+dx+WMAN>=pntx[2]))  hitflag=3;     /*vert*/
    else
      {
#ifdef Linux
      m1=fabs((float)diff0/(diff1+!(diff1)));
      m2=fabs((float)diff3/(diff2+!(diff2)));
#endif
#ifdef DOS
      m1=abs((float)diff0/(diff1+!(diff1)));
      m2=abs((float)diff3/(diff2+!(diff2)));
#endif
          if (m2>1.0) m2=1.0;
      //if (diff2==0 && diff3==0) hitflag=3;
      if ((int)(m1*100) == (int)(m2*100)) hitflag=3;
      if ((int)((m2-0.01)*100) <= (int)(m1*100) &&
	 (int)(m1*100)<= (int)((m2+0.01)*100)) hitflag=3;
      }
  /*line 1*/       /*top*/
  diff0=pnty[2]-pnty[1];
  diff1=pntx[2]-pntx[1];
  diff2=hx1+dx-pntx[1];
  if (diff0==0)
    {if ((hy1+dy+HMAN<=pnty[2])||(pnty[2]==0&&hy1+dy<0)) hitflag=2;}
  else
    {
    m1=(float)diff0/(diff1+!(diff1));
    m2=(float)(hy1+dy+HMAN-pnty[1])/(diff2+!(diff2));
    if ((int)((m1-0.1*speed)*10)<=(int)(m2*10)  &&
      (int)(m2*10)<=(int)((m1+0.1*speed)*10)) hitflag=2;
    }
  /*line 3*/           /*bottom*/
  diff0=pnty[0]-pnty[3];
  diff1=pntx[0]-pntx[3];
  diff2=hx1+dx+WMAN-pntx[3];
  m1=(float)diff0/(diff1+!(diff1));
  m2=(float)(hy1+dy+HMAN-pnty[3])/(diff2+!(diff2));
  if (diff0==0)
    {
      if (hy1+dy+HMAN>=pnty[0])
	 hitflag=4;
    }
  else
    if ((int)((m2-0.05*speed)*100)<=(m1*100) &&
	     (m1*100)<=(int)((m2+0.05*speed)*100)) hitflag=4;

}

dorcheck()
{
int c,yy1,xx1;

  yy1=hy1+HMAN;   /*+4*/
  /*find new door*/

/*  printf("%d",hitflag);   */
/*    printf("%d",doorflag);*/
  doorflag=0;

  for (c=0;c<NUMDOR;c++)
    {
    switch (hitflag)
      {
      case 1:     /*left door*/
	  if (((door[c].a[1]>door[c].a[3])&&(door[c].a[1]>=yy1&&yy1>=door[c].a[3]) ||
	   (door[c].a[1]<door[c].a[3])&&(door[c].a[1]<=yy1&&yy1<=door[c].a[3]))&&
	   ((door[c].a[0]>door[c].a[2])&&(door[c].a[0]+10>hx1+dx&&hx1+dx>door[c].a[2]-10)||
	   (door[c].a[0]<door[c].a[2])&&(door[c].a[0]-10<hx1+dx&&hx1+dx<door[c].a[2]+10)||
	   (door[c].a[0]==door[c].a[2])&&(hx1+dx<=door[c].a[0])&&(door[c].a[0]<300)))
	     {
	     if (door[c].vis==0)
	       {
	       doorflag=1;
	       newloc=door[c].next;
	       c=NUMDOR;
	       }
	     }
	break;
      case 2:     /*top door*/
	 if (door[c].a[1]==0&&door[c].a[3]==0&&!doorflag) yy1=hy1;
	 else yy1=yy1-8;
	 if (((door[c].a[0]>door[c].a[2])&&(door[c].a[0]>hx1&&hx1>door[c].a[2]) ||
	   (door[c].a[0]<door[c].a[2])&&(door[c].a[0]<hx1&&hx1<door[c].a[2]))&&
	   ((door[c].a[1]>door[c].a[3])&&(door[c].a[1]>=yy1&&yy1>=door[c].a[3])||
	   (door[c].a[1]<door[c].a[3])&&(yy1<=door[c].a[3]&&yy1>=door[c].a[1])||
	   (door[c].a[1]==door[c].a[3])&&(yy1-speed<=door[c].a[1])))  /*18*/
	   {
	   if (door[c].vis==0)
	     {
	     if (door[c].a[1]<150 && door[c].a[3]<150)
	       {
	       doorflag=4;
	       newloc=door[c].next;
	       if (curloc==57&&c==2) spec[23]=1;
	       if (curloc==58&&c==3) spec[23]=2;
	       if (curloc==62)
		 switch(c)
		   {
		   case 0:  spec[23]=3; break;
		   case 1:  spec[23]=4; break;
		   case 2:  spec[23]=5; break;
		   }
	       c=NUMDOR;
	       }
	     }
	   }
       break;
      case 3:     /*right door*/
	 if (((door[c].a[1]>door[c].a[3])&&(door[c].a[1]>=yy1&&yy1>=door[c].a[3]) ||
	   (door[c].a[1]<door[c].a[3])&&(door[c].a[1]<=yy1&&yy1<=door[c].a[3]))&&
	   ((door[c].a[0]>door[c].a[2])&&(door[c].a[0]+10>=hx1+dx+WMAN&&hx1+WMAN+dx>=door[c].a[2]-10)||
	   (door[c].a[0]<door[c].a[2])&&(door[c].a[0]-10<=hx1+dx+WMAN&&hx1+WMAN+dx<=door[c].a[2]+10)||
	   ((door[c].a[0]==door[c].a[2])&&(hx1+dx+WMAN>door[c].a[0]-speed)&&(door[c].a[0]>300))))
	   {                                                      /*10*/
	   if (door[c].vis==0)
	     {
	     doorflag=3;
	     newloc=door[c].next;
	     c=NUMDOR;
	     }
	   }
       break;
      case 4:     /*bottom door*/
	 if (((door[c].a[0]>door[c].a[2])&&(door[c].a[0]>hx1&&hx1>door[c].a[2]) ||
	   (door[c].a[0]<door[c].a[2])&&(door[c].a[0]<hx1&&hx1<door[c].a[2]))&&
	   ((door[c].a[1]>door[c].a[3])&&(door[c].a[1]>=yy1&&yy1>=door[c].a[3])||
	   (door[c].a[1]<door[c].a[3])&&(door[c].a[1]<=yy1&&yy1<=door[c].a[3])||
	   (door[c].a[1]==door[c].a[3])&&(door[c].a[1]<=yy1+10)))
	   {
	   if (door[c].vis==0)
	     {
	     if (door[c].a[1]>150&&door[c].a[3]>150)
	       {
	       doorflag=2;
	       newloc=door[c].next;
	       c=NUMDOR;
	       }
	     }
	   }
       break;
       }	/*end switch*/
    }          /*end for*/
}

dorhit()
{
int c,xx1,flag;

  /*find new door*/
/* printf("\n%d",doorflag);*/
  for (c=0;c<NUMDOR;c++)
    {
    if (newloc==42) {hx1=40; rx3=20; /*c=NUMDOR;*/}
    if (newloc==43) {hx1=619; rx3=639;/*  c=NUMDOR;*/}
    switch (doorflag)
      {
      case 1:     /*left door-right door*/
	   if (door[c].vis==0)
	     {
	       if (door[c].a[0]>300&&door[c].a[2]>300)
		 {
		 if (abs(door[c].a[1]-door[c].a[3])<80)
		   hy1=(int)(door[c].a[1]+(door[c].a[3]-door[c].a[1])/2)-HMAN;
		 if (door[c].a[0]>door[c].a[2])
		   hx1=door[c].a[2];
		 else
		   hx1=door[c].a[0];
		 hx1=hx1-15-speed;
		 if (spec[20]==2) {rx3=hx1; hx1-=20; mode3=1;}
		 c=NUMDOR;
		 }
	       }
	break;
      case 2:     /*bottom door-top door*/
	   if (door[c].vis==0)
	     {
	       if (door[c].a[1]==door[c].a[3] && door[c].a[1]<150)
		 {
		 if (curloc<8)
		   hx1=(int)(door[c].a[0]+(door[c].a[2]-door[c].a[0])/2);
		 if (door[c].a[1]<=door[c].a[3])
		   hy1=door[c].a[3]-HMAN;
		 else
		   hy1=door[c].a[1]-HMAN;
		 hy1=hy1+speed;
/*                 if (curloc>23&&curloc<54&&curloc!=41) hy1=hy1+HMAN+5;*/
                 if (curloc>23&&curloc<54&&curloc==41) hy1=hy1-HMAN/2-20;
                 if (curloc>23&&curloc<54) hy1=hy1+HMAN+5;
      		 c=NUMDOR;
		 if (curloc==58&&newloc==57) hx1=495;
		 if (curloc==59&&newloc==57) hx1=165;
		 if (spec[20]==2) 
			{if (newloc==41) {ry3=hy1; hy1+=5; mode3=0;}  /*special mom location*/
			 else  {ry3=hy1; hy1+=20; mode3=0;}}
		 if (newloc==41) hy1=hy1-15-speed;
		 }
	     }
       break;
      case 3:     /*right door-left door*/
	     if (door[c].vis==0)
	       {
		 if (door[c].a[0]<300&&door[c].a[2]<300)
		   {
		   if (abs(door[c].a[1]-door[c].a[3])<80)
		     hy1=(int)(door[c].a[3]+(door[c].a[1]-door[c].a[3])/2)-HMAN;
		   if (door[c].a[0]>door[c].a[2])
		     hx1=door[c].a[0];
		   else
		     hx1=door[c].a[2];
		   hx1=hx1+7+speed;
		   if (spec[20]==2) {hx1+=20; rx3=hx1-20; mode3=4;}
		   c=NUMDOR;
		   }
		 }
       break;
      case 4:     /*top door-bottom door*/
	   if (door[c].vis==0)
	     {
	       if ((door[c].a[3]==door[c].a[1])&&(door[c].a[1]>150))
		 {
		 if (door[c].a[1]>=door[c].a[3])
		   hy1=door[c].a[3]-HMAN;
		 else
		   hy1=door[c].a[1]-HMAN;
		 hy1=hy1-speed-5;  /*-5*/
		 if (spec[20]==2)  {ry3=hy1;hy1-=20;  mode3=2;}

		 c=NUMDOR;
		 }
	       }
       break;
       }	/*end switch*/
    }          /*end for*/
}

mobhit()       /*check for hit with objects*/
{
int nx,ny,ny2,a;

nx=hx1+WMAN;
ny=hy1+HMAN;
ny2=hy1+20;

for (a=0;a<NUMCAR;a++)
  {
  if  (((((mobj[a].p[0]<=nx) && (nx<= (mobj[a].p[0]+mobj[a].p[2]))) ||
       ((mobj[a].p[0]<=hx1) && (hx1<=(mobj[a].p[0]+mobj[a].p[2]))))  &&
      (((mobj[a].p[1]<=ny) && (ny<= (mobj[a].p[1]+mobj[a].p[3]))) ||
      ((mobj[a].p[1]<=hy1) && (hy1<= (mobj[a].p[1]+mobj[a].p[3])))||
      ((mobj[a].p[1]<=ny2) && (ny2<= (mobj[a].p[1]+mobj[a].p[3])))))
       && (mobj[a].loc==curloc))
    {
    hitflag=6;
    a=NUMCAR;
    }
  }
}

obhit()       /*check for hit with objects*/
{
int nx,ny,a;

nx=hx1+dx+WMAN;
ny=hy1+dy+HMAN;
for (a=0;a<NUMOBJ;a++)
  {
  if ((obj[a].p[0]<=nx) && (nx<= (obj[a].p[0]+obj[a].p[2]+WMAN)) &&
      (obj[a].p[1]<=ny) && (ny<= (obj[a].p[1]+obj[a].p[3])) &&
      (obj[a].loc==curloc) && (a<28 || a>118))
    {
    hitflag=5;
    a=NUMOBJ;
    }
  }
}

#ifdef Linux
load_events()  //if the variable is passed the malloc is released when done?
#endif
#ifdef DOS
load_events(struct event2020 eve[NUMEVE])
#endif
{
int a;
FILE *fptr;
char nm[256];

#ifdef Linux
int tempint;
#endif


#ifdef Linux
//for Linux/Unix variable must be malloced (given addresses and memory to use)
//eve=(struct event2020 *)malloc(sizeof(struct event2020)*(NUMEVE*2));
for(a=0;a<NUMEVE;a++)
{

//temptime=time(NULL);
//eve[a].beg=(struct tm *)malloc(sizeof(struct tm));
//eve[a].end=(struct tm *)malloc(sizeof(struct tm));

//eve[a].beg=localtime(&temptime);
//eve[a].end=localtime(&temptime);

}


//try to remember to free memory used for events when program ends
//or let operating system take back memory I guess
#endif

a=0;
#ifdef DOS
getcwd(PATH,512);
#endif
strcat(PATH,LPATH);

strcpy(nm,PATH);
#ifdef Linux
  strcat(nm,"EventL.bin");
#endif
#ifdef DOS
  strcat(nm,"EVENT.BIN");
#endif
if ( (fptr=fopen(nm,"rb"))==NULL)
   {printf("Can't open file %s",nm); 
#ifdef Linux
//this will seg fault because Xwindow is open- while (fread(&Key,1,1,input)!=1) {}
#endif
#ifdef DOS
    getch(); 
#endif
}
else
   {

   for (a=0;a<NUMEVE;a++)
#ifdef Linux
     {
     //fread(&eve[a],sizeof(struct event2020),1,fptr);
	fread(&eve[a],8,1,fptr);  //just read in 2 4-byte meaningless addresses
	fread(&eve[a].loc,4,1,fptr);  //read in location
	fread(&eve[a].obnum,4,1,fptr);  //read in object number

//change pointer that is from file (that pointer was lost)
//to an address that can be written to
eve[a].beg=(struct tm *)malloc(sizeof(struct tm));
eve[a].end=(struct tm *)malloc(sizeof(struct tm));

     fread(&eve[a].beg->tm_hour,4,1,fptr);
     fread(&eve[a].beg->tm_min,4,1,fptr);
     fread(&eve[a].beg->tm_sec,4,1,fptr);
     fread(&eve[a].end->tm_hour,4,1,fptr);
     fread(&eve[a].end->tm_min,4,1,fptr);
     fread(&eve[a].end->tm_sec,4,1,fptr);
     }
#endif
#ifdef DOS
     fread(&eve[a],sizeof(eve[0]),1,fptr);
#endif
   }
fclose(fptr);
}    			/*end load events*/

make_words()		/*function to separate sentence into words*/
{
int len,a;
int flag1;           /*0-nothing 1-letters */




wdflag=0;
flag1=0;
len=strlen(it);
strcpy(cword[0].nm,"");

a=0;
while(a<len)
  {              /*if we have a letter-symbol  ! ? . , */

  if (it[a]!=32&&flag1<2&&
      ((it[a]!=33&&it[a]!=34&&it[a]!=39&&it[a]!=63&&
      it[a]!=46&&it[a]!=44)||spec[3]==0))
    {
    flag1=1;
    if (strlen(cword[wdflag].nm)<15)
      strncat(cword[wdflag].nm,&it[a],1);     /*&it[a]*/
    else a=len;
    }
  else
    if (it[a]!=32&&flag1==2&&
	((it[a]!=33&&it[a]!=34&&it[a]!=39&&it[a]!=63&&
	it[a]!=46&&it[a]!=44)||spec[3]==0))
      { 			/*we have a new word*/
      wdflag++;
      strcpy(cword[wdflag].nm,"");
      strncat(cword[wdflag].nm,&it[a],1);  /*&it*/
      flag1=0;
      if (a>0)
      {
      if (it[a-1]==32 && it[a+1]==32)
	{
	flag1=3;
	if (a>0) a--;
	}
      }
    else             /*a==0*/
      {
      if (it[a+1]==32 && a==0)
	{
	flag1=3;
	if (a>0) a--;
	}
      }
      }
    else
      if (it[a]==32)    /*space bar*/
	{
	if (flag1!=0)   /*space(s) before 1st word*/
	  flag1=2;    /*new word- the end of the old word*/
	}
   a++;
   }   /*end while*/
it[0]=0;


}	/*end make words*/

refresh()
{
redraw=1;
onemo=1;
ex=1;
}

shower()
{
     /*take a shower*/
if (curloc==4)  /*in bathroom*/
  if (close_enough(22))
     { obj[21].loc=4; retsen=5; spec[1]=1;}
  else
      retsen=6;   /*not close enough*/
else
  retsen=25;   /*no tv here*/
}

draw_cursor()
{
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0], xgc, cursx,cursy+5,16,20);
ShowScreen2();

#endif
#ifdef DOS
setcolor(15);
setactivepage(page);
outtextxy(cursx,cursy,cursor);
setactivepage(!page);
outtextxy(cursx,cursy,cursor);
#endif
}

start_over()		/*start game over*/
{
int a;

dx=dy=0;     doorflag=0;   refresh();
brush=0;  cur=0;
lcolor=0;  newloc=1;   curobj=-1;  onepic=0;  telpic=90;
#ifdef Linux
mtime->tm_hour=6/*9*/;  mtime->tm_min=0;  mtime->tm_sec=0;// mtime.ti_hund=0;
#endif
#ifdef DOS
mtime.ti_hour=6/*9*/;  mtime.ti_min=0;  mtime.ti_sec=0; mtime.ti_hund=0;
#endif
moonindx=0;

init_var();
init_var2();
/*restore objects status*/
load_obj();
load_mobj();          /*load moving objects*/
init_mob();
init_ob();

}

init_var()		/*initialize variables*/
{
int a;

hx1=280;       /*set current coord*/
hy1=200;
hx2=hx1;  hy2=hy1;
rx3=361;  ry3=222;
rx4=rx3;  ry4=ry3;
moonindx=0; shipindx=0;
ampm=0; page=0;
mode=3;    mode3=3;
numimg=6;  numimg3=6;
slot=0/*6*/;  channel=0;

for(a=0;a<10;a++)
   sent[a]=-1;
for(a=0;a<=NUMSPEC;a++)
   spec[a]=0;
cash=0; cash0=0;
#ifdef Linux
del=30000;
#endif
#ifdef DOS
del=3000;   /*del=320;*/  /*  del=20 for 386*/
#endif
inv=2;
cursx=16;  cursy=310;   precur=16;
initmesg=0;
}

init_var2()
{
hx1=280;       /*set current coord*/
hy1=200; hx2=hx1;  hy2=hy1; rx3=361;  ry3=222; rx4=rx3;  ry4=ry3; ampm=0; page=0;
mode=3;   mode3=3; numimg=6;  numimg3=6; curloc=1;  curloc3=5; newloc=1;
}

init_mob()
{
int a;

for (a=0;a<NUMCAR;a++)
  {
  /*set initial car positions*/
  if (a<15)
    {
    mobj[a].p[0]=500;
    mobj[a].p[1]=155;
    }
  else
    {
    mobj[a].p[0]=4;
    mobj[a].p[1]=225;
    }
  carx[a]=mobj[a].p[0];
  }
for (a=NUMCAR;a<NUMCAR+NUMROAD;a++)
  {
  mobj[a].p[0]=80+160*(a-NUMCAR);
  mobj[a].p[1]=185;
  roadx[a-NUMCAR]=mobj[a].p[0];
  }
for (a=NUMCAR+NUMROAD;a<NUMCAR+NUMROAD+NUMSPIKE;a++)
  {
  mobj[a].p[0]=80+160*(a-NUMCAR-NUMROAD);
  mobj[a].p[1]=56;
  spikex[a-NUMCAR-NUMROAD]=mobj[a].p[0];
  }
}

init_ob()
{
int a,aa;

for (a=119;a<131;a++)
  {
  /*set initial car positions*/
  if (a==119 || a==123 || a==127) aa=0;
  if (a==120 || a==124 || a==128) aa=1;
  if (a==121 || a==125 || a==129) aa=2;
  if (a==122 || a==126 || a==130) aa=3;
  obj[a].p[0]= aa*150 + 25;
  obj[a].p[1]=190;
  }
obj[131].p[0]= 500;  obj[131].p[1]=250;
obj[132].p[0]= 220;  obj[132].p[1]=10;
obj[133].p[0]= 10;  obj[133].p[1]=210;
obj[134].p[0]= 110;  obj[134].p[1]=160;
obj[135].p[0]= 52;  obj[135].p[1]=65;
obj[136].p[0]= 475;  obj[136].p[1]=265;
obj[137].p[0]= 600;  obj[137].p[1]=126;
obj[138].p[0]= 432;  obj[138].p[1]=126;
obj[139].p[0]= 532;  obj[139].p[1]=82;
obj[140].p[0]= 10;  obj[140].p[1]=220;
}

dead()
{
qflg=1;
putout("Play Again? (Y/N)");
}

save_game()
{
savmenu();
}

restore_game()
{
moonindx=0;
resmenu();
}

dir_char()
{
      if (dx!=0||dy!=0)
	{
	if (c2>=(10-speed)) c2=-(10-speed);
	else
	  c2++;
	}
      switch(mode)
       {
       case 0: 			/*down*/
	 numimg2=(c2<0)*6 + (c2>=0)*7;
	 break;
       case 1:                   /*left*/
	 numimg2=(c2>=0);
	 break;
       case 2:                   /*up*/
	 numimg2=(c2<0)*2 + (c2>=0)*3;
	 break;
       case 3:                  /*stopped*/
	 numimg2=numimg;
	 break;
	case 4:
	  numimg2=(c2<0)*4 + (c2>=0)*5;   /*right*/
	  break;
       } 	/*end switch*/
    numimg=numimg2;		/*set new image number*/
    hx2=hx1;  hy2=hy1;   /*save old coord*/
}

dir_bot()
{
      if (dx2!=0||dy2!=0)
	{
	if (c3>=(10-speed)) c3=-(10-speed);
	else
	  c3++;
	}
      switch(mode3)
       {
       case 0: 			/*down*/
	 numimg4=(c3<0)*6 + (c3>=0)*7;
	 break;
       case 1:                   /*left*/
	 numimg4=(c3>=0);
	 break;
       case 2:                   /*up*/
	 numimg4=(c3<0)*2 + (c3>=0)*3;
	 break;
       case 3:                  /*stopped*/
	 numimg4=numimg3;
	 break;
	case 4:
	  numimg4=(c3<0)*4 + (c3>=0)*5;   /*right*/
	  break;
       } 	/*end switch*/
    numimg3=numimg4;		/*set new image number*/
    rx4=rx3;  ry4=ry3;   /*save old coord*/
}

mvbot()
{
dx2=0;  dy2=0;

if (spec[20]==2)
{
if (abs(abs(hx1)-abs(rx3))>20)
  {
  if (hx1<rx3) {dx2=-speed; mode3=1;}
  else {dx2=speed; mode3=4;}
  }
if (abs(abs(hy1)-abs(ry3))>20)
  {
  if (hy1<ry3) {dy2=-speed; mode3=2;}
  else {dy2=speed; mode3=0;}
  }
}
}

one()
{
#ifdef DOS
      setactivepage(!page);
#endif
#ifdef Linux
//put original image back
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,0,0,0,0,640,300);

#endif
#ifdef DOS

      if (curloc==42||curloc==43)
	{
	erase_road();
	erase_spike();
	}
      erase_char();
      if (spec[20]>=1&&curloc3==curloc)
	erase_bot();
      if (spec[4]==1)
	{
	erase_mob();   /*erase moving objects*/
	/*getmob();*/  /*get background screens for moving objects*/
	}
#endif
#ifdef DOS
      setactivepage(page);
#endif
}

load_bitmap(char * bmfile)
{
BITMAPFILEHEADER bmf;
BITMAPINFOHEADER bmi;
FILE *fptr;
int numr;
int a,b;
unsigned char *bdata;
XImage * fximage2;
int nw,ofs;
unsigned int nukl;

fptr=fopen(bmfile,"rb");
if (fptr==0)  fprintf(stderr,"Error opening %s\n",bmfile);
else
{
//fread(&bmf,sizeof(BITMAPFILEHEADER),1,fptr);
fread(&bmf.bfType,2,1,fptr);
fread(&bmf.bfSize,4,1,fptr);
fread(&bmf.bfReserved1,2,1,fptr);
fread(&bmf.bfReserved2,2,1,fptr);
fread(&bmf.bfOffBits,4,1,fptr);
//fprintf(stderr,"bs=%d hd=%x size=%x Off=%x\n",sizeof(BITMAPFILEHEADER),bmf.bfType,bmf.bfSize,bmf.bfOffBits);
fread(&bmi.biSize,4,1,fptr);
fread(&bmi.biWidth,4,1,fptr);
fread(&bmi.biHeight,4,1,fptr);
fread(&bmi.biPlanes,2,1,fptr);
fread(&bmi.biBitCount,2,1,fptr);
fread(&bmi.biCompression,4,1,fptr);
fread(&bmi.biSizeImage,4,1,fptr);
fread(&bmi.biXPelsPerMeter,4,1,fptr);
fread(&bmi.biYPelsPerMeter,4,1,fptr);
fread(&bmi.biClrUsed,4,1,fptr);
fread(&bmi.biClrImportant,4,1,fptr);


//fprintf(stderr,"w=%d h=%d\n",bmi.biWidth,bmi.biHeight);
//fprintf(stderr,"remainder=%f \n",fmodf(7.0,4.0));
//fprintf(stderr,"remainder=%f \n",fmodf((float)bmi.biWidth,8.0));
//nw=bmi.biWidth;
//if (nw&1>0) nw=nw+1;
//if (nw&2>0) nw=nw+2;
//if (nw&4>0) nw=nw+4;


//number of bytes - not just width has to be %8=0
nw=(int)fmodf((float)bmi.biWidth*3,4.0);
if (nw>0)  {nw=bmi.biWidth*3+4-nw;}
else
  nw=bmi.biWidth*3;



//fprintf(stderr,"w=%d h=%d\n",nw,bmi.biHeight);
//read data
bdata=(unsigned char *)malloc(nw*bmi.biHeight);
fread(bdata,nw*bmi.biHeight,1,fptr);
fclose(fptr);


//now draw
//#if 0 
//fximage2=XCreateImage(xdisplay,visual,depth,ZPixmap,0,0,bmi.biWidth,bmi.biHeight,8,0);   //not good?
//fximage2->data=bdata;
//fximage2->data=(char *)malloc(nw*bmi.biHeight*3+300);  //not good?
  fximage2= XGetImage(xdisplay,pixmap[0],0,0,640,300,AllPlanes,ZPixmap);

for(a=0;a<bmi.biHeight;a++)  
{
for(b=0;b<bmi.biWidth;b++)  //nw
{
//
ofs=(bmi.biHeight-a-1)*nw+b*3;

//nukl=0;
//nukl=0<<0x18|(*(bdata+ofs)<<0x10)|(*(bdata+ofs+1)<<0x8)|(*(bdata+ofs+2));
nukl=0<<0x18|(*(bdata+ofs+2)<<0x10)|(*(bdata+ofs+1)<<0x8)|(*(bdata+ofs));
//fprintf(stderr,"%x ",nukl);
if (nukl!=0)
  XPutPixel(fximage2,200+b,50+a,nukl);
}
}

//XPutImage(xdisplay,pixmap[0],xgc,fximage2,0,0,0,0,bmi.biWidth-1,bmi.biHeight-1);
XPutImage(xdisplay,pixmap[0],xgc,fximage2,200,50,200,50,bmi.biWidth,bmi.biHeight);

//free(fximage2->data);
//#endif

}//end if bitmap file found

}


