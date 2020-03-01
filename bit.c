/*  bit.c   */
/*  bit image lines for 2020!   */
/*  by Ted Huntington  */

#include "2020.h"
#ifdef Linux
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#endif
#ifdef DOS
#include "alloc.h"
#include "graphics.h"
#endif

struct objects
  {
  char name[11];
  int p[4];
  int loc;
  };
extern struct objects obj[NUMOBJ];
extern int numimg,numimg3,mode,mode3;
extern int hx1,hy1,hx2,hy2;        /*point coordinates*/
extern int rx3,ry3,rx4,ry4;
#ifdef DOS
extern int skin[8];             /*characters attributes*/
extern int skin3[8];             /*characters attributes*/
extern void *man[8];		/*pointer to character image*/
extern void *screen[7+NUMMOBJ];       /*pointer to background for images*/
extern void *screen3[2];       /*pointer to background for images*/
extern void *heli[5];		/*pointer to heli images*/
extern void *lines3[17];
extern void *car[NUMCAR];
extern void *road[NUMROAD];
extern void *spike[NUMSPIKE];
extern void *robot[8];    	/*background lines  17-char 37-heli*/
extern void *lines[170];	    /*37*4= 148+17=165*/
#endif
extern unsigned sizeman;	/*size of character image*/
extern unsigned sizeheli;	/*size of heli image*/
extern unsigned sizeline;	/*size of line fills*/
extern unsigned sizecar;
extern unsigned sizeroad;
extern unsigned sizespike;
#ifdef Linux
extern Display *xdisplay;
extern Window xwindow;
extern int xscreen;
//unsigned long xforeground, xbackground;
//XEvent xevent;
extern GC xgc;
// Colormap cmap;
// XColor color, colorrgb;

extern Pixmap pixmap[3];
extern int depth;
// XImage *fximage;
// Visual *visual;

extern XImage *man[8];		/*pointer to character image*/
extern XImage *screen[7+NUMMOBJ];       /*pointer to background for images*/
extern XImage *screen3[2];       /*pointer to background for images*/
extern XImage *heli[5];		/*pointer to heli images*/
extern XImage *lines3[17];
extern XImage *car[NUMCAR];
extern XImage *road[NUMROAD];
extern XImage *spike[NUMSPIKE];
extern XImage *robot[8];    	/*background lines  17-char 37-heli*/
extern XImage *lines[170];	    /*37*4= 148+17=165*/

extern short int skin[8];             /*characters attributes*/
extern short int skin3[8];             /*characters attributes*/
extern XImage *TitleImage;
#endif


alloc_lines()
{
#ifdef DOS
 free(screen[0]);
 free(lines[0]); free(lines[1]); free(lines[2]); free(lines[3]);
 free(lines[4]); free(lines[5]); free(lines[6]); free(lines[7]);
 free(lines[8]); free(lines[9]); free(lines[10]); free(lines[11]);
 free(lines[12]); free(lines[13]); free(lines[14]); free(lines[15]);
 free(lines[16]);
#ifdef Linux
sizeman=(WMAN+4)*(HMAN+1);
#endif
#ifdef DOS
 sizeman=imagesize(0,0,WMAN+3,HMAN);
#endif
  screen[0]=malloc(sizeman);     /*allocate for screen image*/
  screen[1]=malloc(sizeman);     /*allocate for screen image*/
/*  sizeline=imagesize(0,0,1+skin[7]*2,HMAN);*/
#ifdef Linux
sizeline=4*(HMAN+1);
#endif
#ifdef DOS
  sizeline=imagesize(0,0,3,HMAN);
#endif
  lines[0]=malloc(sizeline);     /*pants&dress- head to toe left side*/
  lines[7]=malloc(sizeline);     /*pants&dress- head to toe right*/
/*  if (skin[7]==0)    dress
    {*/
#ifdef Linux
sizeline=HMAN+1;
#endif
#ifdef DOS
    sizeline=imagesize(0,0,0,HMAN);  /*HMAN-DF*/
#endif
    lines[10]=malloc(sizeline);     /*dress- head to toe left side*/
    lines[11]=malloc(sizeline);                  /*right*/
#ifdef Linux
    sizeline=HMAN+1;
#endif
#ifdef DOS
    sizeline=imagesize(0,0,0,HMAN); /*HMAN-DF2*/
#endif
    lines[12]=malloc(sizeline);     /*dress- head to toe left inside*/
    lines[13]=malloc(sizeline);                  /*right*/
/*    }*/    /*this was an error found by Kevin Borgnis! */
#ifdef Linux
sizeline=6;
#endif
#ifdef DOS
  sizeline=imagesize(0,0,2,1);
#endif
  lines[1]=malloc(sizeline);    /*top of head*/
  lines[2]=malloc(sizeline);
#ifdef Linux
sizeline=10;
#endif
#ifdef DOS
  sizeline=imagesize(0,0,4,1);  /*between head and shoulders*/
#endif
  lines[3]=malloc(sizeline);
  lines[4]=malloc(sizeline);
#ifdef DOS
  sizeline=imagesize(0,0,2,NOSEY);  /*between top of head and nose*/
#endif
  lines[5]=malloc(sizeline);
  lines[6]=malloc(sizeline);
#ifdef DOS
  sizeline=imagesize(0,NOSEY,0,BSHIRTY-1);  /*between nose and shoulders*/
#endif
  lines[8]=malloc(sizeline);
#ifdef DOS
  sizeline=imagesize(0,NOSEY,1,BSHIRTY-1);  /*between nose and shoulders*/
#endif
  lines[9]=malloc(sizeline);
#ifdef DOS
  sizeline=imagesize(0,EPANTSY-17,5,ENDBODY);  /*bottom of pants to shoes*/
#endif
  lines[14]=malloc(sizeline);
  lines[15]=malloc(sizeline);
#ifdef DOS
  sizeline=imagesize(0,ENDBODY-3,4,ENDBODY);  /*bottom of pants to shoes*/
#endif
  lines[16]=malloc(sizeline);
#endif
}

getlines()
{
#ifdef Linux
lines[0]=XGetImage(xdisplay,pixmap[0],hx1,hy1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 hx1+1+skin[7]*2,hy1+HMAN-4*(mode==1),AllPlanes,ZPixmap);
lines[7]=XGetImage(xdisplay,pixmap[0],hx1+ECHX-5-skin[7]*2,hy1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     hx1+ECHX-3,hy1+HMAN-4*(mode==4),AllPlanes,ZPixmap);
#endif
#ifdef DOS
getimage(hx1,hy1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 hx1+1+skin[7]*2,hy1+HMAN-4*(mode==1),lines[0]);
getimage(hx1+ECHX-5-skin[7]*2,hy1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     hx1+ECHX-3,hy1+HMAN-4*(mode==4),lines[7]);
#endif
if (skin[7]==0)    /*dress*/
  {
#ifdef Linux
   lines[10]=XGetImage(xdisplay,pixmap[0],hx1+2,hy1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 hx1+2,hy1+HMAN-DF,AllPlanes,ZPixmap);
   lines[11]=XGetImage(xdisplay,pixmap[0],hx1+ECHX-6,hy1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     hx1+ECHX-6,hy1+HMAN-DF,AllPlanes,ZPixmap);
   lines[12]=XGetImage(xdisplay,pixmap[0],hx1+3,hy1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 hx1+3,hy1+HMAN-DF2,AllPlanes,ZPixmap);
   lines[13]=XGetImage(xdisplay,pixmap[0],hx1+ECHX-7,hy1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     hx1+ECHX-7,hy1+HMAN-DF2,AllPlanes,ZPixmap);
   
#endif
#ifdef DOS
  getimage(hx1+2,hy1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 hx1+2,hy1+HMAN-DF,lines[10]);
  getimage(hx1+ECHX-6,hy1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     hx1+ECHX-6,hy1+HMAN-DF,lines[11]);
  getimage(hx1+3,hy1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 hx1+3,hy1+HMAN-DF2,lines[12]);
  getimage(hx1+ECHX-7,hy1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     hx1+ECHX-7,hy1+HMAN-DF2,lines[13]);
#endif
  }

#ifdef Linux
lines[1]=XGetImage(xdisplay,pixmap[0],hx1,hy1,hx1+2,hy1+1,AllPlanes,ZPixmap);
lines[2]=XGetImage(xdisplay,pixmap[0],hx1+ECHX-7,hy1,hx1+ECHX-4,hy1+1,AllPlanes,ZPixmap);

#endif
#ifdef DOS
getimage(hx1,hy1,hx1+2,hy1+1,lines[1]);
getimage(hx1+ECHX-7,hy1,hx1+ECHX-4,hy1+1,lines[2]);
#endif
if (skin[2]!=2 || (skin[2]==2 && mode!=2))
  {
  if (mode!=2 || skin[2]<2)
    {
#ifdef Linux
lines[3]=XGetImage(xdisplay,pixmap[0],hx1+3,hy1+BSHIRTY-4,hx1+5,hy1+BSHIRTY-3,AllPlanes,ZPixmap);
lines[4]=XGetImage(xdisplay,pixmap[0],hx1+ESHIRTX-7,hy1+BSHIRTY-4,hx1+ESHIRTX-5,hy1+BSHIRTY-3,AllPlanes,ZPixmap);

#endif
#ifdef DOS
    getimage(hx1+3,hy1+BSHIRTY-4,hx1+5,hy1+BSHIRTY-3,lines[3]);
    getimage(hx1+ESHIRTX-7,hy1+BSHIRTY-4,hx1+ESHIRTX-5,hy1+BSHIRTY-3,lines[4]);
#endif
    }
  }
if (mode==1||(skin[2]==0&&mode!=4))
  {
#ifdef Linux
lines[5]=XGetImage(xdisplay,pixmap[0],hx1,hy1,hx1,hy1+NOSEY-3,AllPlanes,ZPixmap);
lines[8]=XGetImage(xdisplay,pixmap[0],hx1,hy1+NOSEY,hx1,hy1+BSHIRTY-1,AllPlanes,ZPixmap);

#endif
#ifdef DOS
  getimage(hx1,hy1,hx1,hy1+NOSEY-3,lines[5]);
  getimage(hx1,hy1+NOSEY,hx1,hy1+BSHIRTY-1,lines[8]);
#endif
  }
if (mode==4||(skin[2]==0&&mode!=1))
  {
#ifdef Linux
lines[6]=XGetImage(xdisplay,pixmap[0],hx1+ESHIRTX-3,hy1,hx1+ESHIRTX-1,hy1+NOSEY-3,AllPlanes,ZPixmap);
lines[9]=XGetImage(xdisplay,pixmap[0],hx1+ESHIRTX-3,hy1+NOSEY,hx1+ESHIRTX-2,hy1+BSHIRTY-1,AllPlanes,ZPixmap);

#endif
#ifdef DOS
  getimage(hx1+ESHIRTX-3,hy1,hx1+ESHIRTX-1,hy1+NOSEY-3,lines[6]);
  getimage(hx1+ESHIRTX-3,hy1+NOSEY,hx1+ESHIRTX-2,hy1+BSHIRTY-1,lines[9]);
#endif
  }
/*shoes*/
#ifdef Linux
lines[14]=XGetImage(xdisplay,pixmap[0],hx1,hy1+EPANTSY-1,hx1+3,hy1+ENDBODY-7*(numimg==0)-5*(numimg==1),AllPlanes,ZPixmap);
lines[15]=XGetImage(xdisplay,pixmap[0],hx1+ESHIRTX-5,hy1+EPANTSY-1,hx1+ESHIRTX-4+2*(numimg==4),
	 hy1+ENDBODY-7*(numimg==5)-5*(numimg==4),AllPlanes,ZPixmap);
lines[16]=XGetImage(xdisplay,pixmap[0],hx1+(ESHIRTX-8)*(numimg==1||numimg==3||numimg==7)+
	4*(numimg==6||numimg==4)+(ESHIRTX-4)*(numimg==5),hy1+ENDBODY-4,
	 hx1+(ESHIRTX-7)*(numimg==1||numimg==3||numimg==7)+2+
	 4*(numimg==6||numimg==4)+4*(numimg==2)+(ESHIRTX-4)*(numimg==5),
	 hy1+ENDBODY-2,AllPlanes,ZPixmap);

#endif
#ifdef DOS
getimage(hx1,hy1+EPANTSY-1,hx1+3,hy1+ENDBODY-7*(numimg==0)-5*(numimg==1),lines[14]);
getimage(hx1+ESHIRTX-5,hy1+EPANTSY-1,hx1+ESHIRTX-4+2*(numimg==4),
	 hy1+ENDBODY-7*(numimg==5)-5*(numimg==4),lines[15]);
/*square under shoe*/
getimage(hx1+(ESHIRTX-8)*(numimg==1||numimg==3||numimg==7)+
	4*(numimg==6||numimg==4)+(ESHIRTX-4)*(numimg==5),hy1+ENDBODY-4,
	 hx1+(ESHIRTX-7)*(numimg==1||numimg==3||numimg==7)+2+
	 4*(numimg==6||numimg==4)+4*(numimg==2)+(ESHIRTX-4)*(numimg==5),
	 hy1+ENDBODY-2,lines[16]);
#endif
}

alloc_lines3()
{
 free(screen3[0]);
 free(lines3[0]); free(lines3[1]); free(lines3[2]); free(lines3[3]);
 free(lines3[4]); free(lines3[5]); free(lines3[6]); free(lines3[7]);
 free(lines3[8]); free(lines3[9]); free(lines3[10]); free(lines3[11]);
 free(lines3[12]); free(lines3[13]); free(lines3[14]); free(lines3[15]);
 free(lines3[16]);
#ifdef DOS
 sizeman=imagesize(0,0,WMAN+3,HMAN);
  screen3[0]=malloc(sizeman);     /*allocate for screen image*/
  screen3[1]=malloc(sizeman);     /*allocate for screen image*/
  sizeline=imagesize(0,0,1+skin3[7]*2,HMAN);
  lines3[0]=malloc(sizeline);     /*pants&dress- head to toe left side*/
  lines3[7]=malloc(sizeline);     /*pants&dress- head to toe right*/
  if (skin3[7]==0)    /*dress*/
    {
    sizeline=imagesize(0,0,0,HMAN-DF);
    lines3[10]=malloc(sizeline);     /*dress- head to toe left side*/
    lines3[11]=malloc(sizeline);                  /*right*/
    sizeline=imagesize(0,0,0,HMAN-DF2);
    lines3[12]=malloc(sizeline);     /*dress- head to toe left inside*/
    lines3[13]=malloc(sizeline);                  /*right*/
    }
  sizeline=imagesize(0,0,2,1);
  lines3[1]=malloc(sizeline);    /*top of head*/
  lines3[2]=malloc(sizeline);
  sizeline=imagesize(0,0,4,1);  /*between head and shoulders*/
  lines3[3]=malloc(sizeline);
  lines3[4]=malloc(sizeline);
  sizeline=imagesize(0,0,2,NOSEY);  /*between top of head and nose*/
  lines3[5]=malloc(sizeline);
  lines3[6]=malloc(sizeline);
  sizeline=imagesize(0,NOSEY,0,BSHIRTY-1);  /*between nose and shoulders*/
  lines3[8]=malloc(sizeline);
  sizeline=imagesize(0,NOSEY,1,BSHIRTY-1);  /*between nose and shoulders*/
  lines3[9]=malloc(sizeline);
  sizeline=imagesize(0,EPANTSY-17,5,ENDBODY);  /*bottom of pants to shoes*/
  lines3[14]=malloc(sizeline);
  lines3[15]=malloc(sizeline);
  sizeline=imagesize(0,ENDBODY-3,4,ENDBODY);  /*bottom of pants to shoes*/
  lines3[16]=malloc(sizeline);
#endif
}

getlines3()
{
#ifdef Linux
lines3[0]=XGetImage(xdisplay,pixmap[0],rx3,ry3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 rx3+1+skin3[7]*2,ry3+HMAN-4*(mode3==1),AllPlanes,ZPixmap);
lines3[7]=XGetImage(xdisplay,pixmap[0],rx3+ECHX-5-skin3[7]*2,ry3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     rx3+ECHX-3,ry3+HMAN-4*(mode3==4),AllPlanes,ZPixmap);

#endif
#ifdef DOS
getimage(rx3,ry3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 rx3+1+skin3[7]*2,ry3+HMAN-4*(mode3==1),lines3[0]);
getimage(rx3+ECHX-5-skin3[7]*2,ry3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     rx3+ECHX-3,ry3+HMAN-4*(mode3==4),lines3[7]);
#endif
if (skin3[7]==0)    /*dress*/
  {
#ifdef Linux
lines3[10]=XGetImage(xdisplay,pixmap[0],rx3+2,ry3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 rx3+2,ry3+HMAN-DF,AllPlanes,ZPixmap);
lines3[11]=XGetImage(xdisplay,pixmap[0],rx3+ECHX-6,ry3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     rx3+ECHX-6,ry3+HMAN-DF,AllPlanes,ZPixmap);
lines3[12]=XGetImage(xdisplay,pixmap[0],rx3+3,ry3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 rx3+3,ry3+HMAN-DF2,AllPlanes,ZPixmap);
lines3[13]=XGetImage(xdisplay,pixmap[0],rx3+ECHX-7,ry3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     rx3+ECHX-7,ry3+HMAN-DF2,AllPlanes,ZPixmap);

#endif
#ifdef DOS
  getimage(rx3+2,ry3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 rx3+2,ry3+HMAN-DF,lines3[10]);
  getimage(rx3+ECHX-6,ry3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     rx3+ECHX-6,ry3+HMAN-DF,lines3[11]);
  getimage(rx3+3,ry3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 rx3+3,ry3+HMAN-DF2,lines3[12]);
  getimage(rx3+ECHX-7,ry3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     rx3+ECHX-7,ry3+HMAN-DF2,lines3[13]);
#endif
  }
#ifdef Linux
lines3[1]=XGetImage(xdisplay,pixmap[0],rx3,ry3,rx3+2,ry3+1,AllPlanes,ZPixmap);
lines3[2]=XGetImage(xdisplay,pixmap[0],rx3+ECHX-7,ry3,rx3+ECHX-4,ry3+1,AllPlanes,ZPixmap);

#endif
#ifdef DOS
getimage(rx3,ry3,rx3+2,ry3+1,lines3[1]);
getimage(rx3+ECHX-7,ry3,rx3+ECHX-4,ry3+1,lines3[2]);
#endif
if (skin3[2]!=2 || (skin3[2]==2 && mode3!=2))
  {
  if (mode3!=2 || skin3[2]<2)
    {
#ifdef Linux
lines3[3]=XGetImage(xdisplay,pixmap[0],rx3+3,ry3+BSHIRTY-4,rx3+5,ry3+BSHIRTY-3,AllPlanes,ZPixmap);
lines3[4]=XGetImage(xdisplay,pixmap[0],rx3+ESHIRTX-7,ry3+BSHIRTY-4,rx3+ESHIRTX-5,ry3+BSHIRTY-3,AllPlanes,ZPixmap);

#endif
#ifdef DOS
    getimage(rx3+3,ry3+BSHIRTY-4,rx3+5,ry3+BSHIRTY-3,lines3[3]);
    getimage(rx3+ESHIRTX-7,ry3+BSHIRTY-4,rx3+ESHIRTX-5,ry3+BSHIRTY-3,lines3[4]);
#endif
    }
  }
if (mode3==1||(skin3[2]==0&&mode3!=4))
  {
#ifdef Linux
lines3[5]=XGetImage(xdisplay,pixmap[0],rx3,ry3,rx3,ry3+NOSEY-3,AllPlanes,ZPixmap);
lines3[8]=XGetImage(xdisplay,pixmap[0],rx3,ry3+NOSEY,rx3,ry3+BSHIRTY-1,AllPlanes,ZPixmap);

#endif
#ifdef DOS
  getimage(rx3,ry3,rx3,ry3+NOSEY-3,lines3[5]);
  getimage(rx3,ry3+NOSEY,rx3,ry3+BSHIRTY-1,lines3[8]);
#endif
  }
if (mode3==4||(skin3[2]==0&&mode!=1))
  {
#ifdef Linux
lines3[6]=XGetImage(xdisplay,pixmap[0],rx3+ESHIRTX-3,ry3,rx3+ESHIRTX-1,ry3+NOSEY-3,AllPlanes,ZPixmap);
lines3[9]=XGetImage(xdisplay,pixmap[0],rx3+ESHIRTX-3,ry3+NOSEY,rx3+ESHIRTX-2,ry3+BSHIRTY-1,AllPlanes,ZPixmap);

#endif
#ifdef DOS
  getimage(rx3+ESHIRTX-3,ry3,rx3+ESHIRTX-1,ry3+NOSEY-3,lines3[6]);
  getimage(rx3+ESHIRTX-3,ry3+NOSEY,rx3+ESHIRTX-2,ry3+BSHIRTY-1,lines3[9]);
#endif
  }
/*shoes*/
#ifdef Linux
lines3[14]=XGetImage(xdisplay,pixmap[0],rx3,ry3+EPANTSY-1,rx3+3,ry3+ENDBODY-7*(numimg3==0)-5*(numimg3==1),AllPlanes,ZPixmap);
lines3[15]=XGetImage(xdisplay,pixmap[0],rx3+ESHIRTX-5,ry3+EPANTSY-1,rx3+ESHIRTX-4+2*(numimg3==4),
	 ry3+ENDBODY-7*(numimg3==5)-5*(numimg3==4),AllPlanes,ZPixmap);

#endif
#ifdef DOS
getimage(rx3,ry3+EPANTSY-1,rx3+3,ry3+ENDBODY-7*(numimg3==0)-5*(numimg3==1),lines3[14]);
getimage(rx3+ESHIRTX-5,ry3+EPANTSY-1,rx3+ESHIRTX-4+2*(numimg3==4),
	 ry3+ENDBODY-7*(numimg3==5)-5*(numimg3==4),lines3[15]);
#endif
/*square under shoe*/
#ifdef Linux
lines3[16]=XGetImage(xdisplay,pixmap[0],rx3+(ESHIRTX-8)*(numimg3==1||numimg3==3||numimg3==7)+
	4*(numimg3==6||numimg3==4)+(ESHIRTX-4)*(numimg3==5),ry3+ENDBODY-4,
	 rx3+(ESHIRTX-7)*(numimg3==1||numimg3==3||numimg3==7)+2+
	 4*(numimg3==6||numimg3==4)+4*(numimg3==2)+(ESHIRTX-4)*(numimg3==5),
	 ry3+ENDBODY-2,AllPlanes,ZPixmap);

#endif
#ifdef DOS
getimage(rx3+(ESHIRTX-8)*(numimg3==1||numimg3==3||numimg3==7)+
	4*(numimg3==6||numimg3==4)+(ESHIRTX-4)*(numimg3==5),ry3+ENDBODY-4,
	 rx3+(ESHIRTX-7)*(numimg3==1||numimg3==3||numimg3==7)+2+
	 4*(numimg3==6||numimg3==4)+4*(numimg3==2)+(ESHIRTX-4)*(numimg3==5),
	 ry3+ENDBODY-2,lines3[16]);
#endif
}

putlines()
{
#ifdef Linux  //lines[0] [1]
int oft,oft2;

//mode 1=dn 2=lf 3=rt   4=up
//4     
oft=hy1+skin[2]*HF*(mode!=1)+(!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7);  //right side
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,hx1,oft,hx1,oft,3,HMAN+1);
oft=hy1+skin[2]*HF*(mode!=4)+(!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7);  //7
oft2=hx1+ECHX-5-skin[7]*2;  //-5 *2
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft2,oft,oft2,oft,4,HMAN+1);


 
#endif
#ifdef DOS
putimage(hx1,hy1+skin[2]*HF*(mode!=1)+
	  (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	  lines[0],COPY_PUT);
putimage(hx1+ECHX-5-skin[7]*2,hy1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     lines[7],COPY_PUT);
#endif

#ifdef Linux
//special for pant
if (skin[7]>0)    
  {
oft=hx1+3;  //42
oft2=hy1+42-((skin[2]<2)&&(mode==1 || mode==4))*25;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-45+((skin[2]<2)&&(mode==1 || mode==4))*25);


oft=hx1+10;  //42
oft2=hy1+42-((skin[2]<2)&&(mode==1 || mode==4))*25;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-45+((skin[2]<2)&&(mode==1 || mode==4))*25);
  }
#endif


if (skin[7]==0)    /*dress*/
  {

#ifdef Linux  //10,11,12,13

#ifdef Linux // 0 //problem
if (mode==1|| mode==4)
{
oft=hx1+3;  //42
oft2=hy1+15;//-(skin[2]<2)*25;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-32);//+(skin[2]<2)*20);


oft=hx1+10;  //42
oft2=hy1+15;//-(skin[2]<2)*25;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-32);
}
#endif



oft=hx1+2;
oft2=hy1+skin[2]*HF*(mode!=1)+(!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7);
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN+1);
oft=hx1+ECHX-6;
oft2=hy1+skin[2]*HF*(mode!=4)+(!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7);
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN+1);
oft=hx1+3;
oft2=hy1+skin[2]*HF*(mode!=1)+(!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7);
//XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN);
oft=hx1+ECHX-7;
oft2=hy1+skin[2]*HF*(mode!=4)+(!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7);
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-oft2+hy1-10);


#endif
#ifdef DOS
  putimage(hx1+2,hy1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 lines[10],COPY_PUT);
  putimage(hx1+ECHX-6,hy1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     lines[11],COPY_PUT);
  putimage(hx1+3,hy1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 lines[12],COPY_PUT);
  putimage(hx1+ECHX-7,hy1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     lines[13],COPY_PUT);
#endif
  }
#ifdef Linux  //1,2  =3  top of head left and right
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,hx1,hy1,hx1,hy1,3,2);
oft=hx1+ECHX-7;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,hy1,oft,hy1,3,2);

#endif
#ifdef DOS
putimage(hx1,hy1,lines[1],COPY_PUT);
putimage(hx1+ECHX-7,hy1,lines[2],COPY_PUT);
#endif
if (skin[2]!=2 || (skin[2]==2 && mode!=2))
  {
  if (mode !=2 || skin[2]<2)              /*neck lines*/
    {
#ifdef Linux  //3,4  =5  neck
oft=hx1+3;
oft2=hy1+BSHIRTY-4;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,3,2);
oft=hx1+ESHIRTX-8;
oft2=hy1+BSHIRTY-4;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,3,2);


#endif
#ifdef DOS
    putimage(hx1+3,hy1+BSHIRTY-4,lines[3],COPY_PUT);
    putimage(hx1+ESHIRTX-7,hy1+BSHIRTY-4,lines[4],COPY_PUT);
#endif
    }
  }
if (mode==1||(skin[2]==0&&mode!=4))
  {
#ifdef Linux  //5,8   =3,2  takes out nose
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,hx1,hy1,hx1,hy1,1,NOSEY-2);//above nose/ear
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,hx1,hy1+NOSEY,hx1,hy1+NOSEY,1,BSHIRTY-NOSEY-2);  //left side under nose/ear
//could make hy1+NOSEY+1 to add more of a nose/ear on left
#endif   
#ifdef DOS
  putimage(hx1,hy1,lines[5],COPY_PUT);
  putimage(hx1,hy1+NOSEY,lines[8],COPY_PUT);
#endif
  }
if (mode==4||(skin[2]==0&&mode!=1))
  {
#ifdef Linux  //6,9 right head  =3,2
oft=hx1+ESHIRTX-3-1*(skin[2]==0&&mode!=1);//3   top to top of nose/ear rt side
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,hy1,oft,hy1,3,NOSEY-2);
//oft=hx1+ESHIRTX-1; //3
oft2=hy1+NOSEY;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,3,BSHIRTY-NOSEY);
//added line below
if (skin[2]==0&&mode!=1)
 XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft+1,hy1,oft+1,hy1,1,BSHIRTY-NOSEY);

#endif
#ifdef DOS
  putimage(hx1+ESHIRTX-3,hy1,lines[6],COPY_PUT);
  putimage(hx1+ESHIRTX-3,hy1+NOSEY,lines[9],COPY_PUT);
#endif
  }
/*shoes*/
#if 0 //def Linux  //14,15,16   5,5,4
oft2=hy1+EPANTSY-1;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,hx1,oft2,hx1,oft2,4,ENDBODY-EPANTSY-17);
oft=hx1+ESHIRTX-5;
oft2=hy1+EPANTSY-1;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,4,ENDBODY-EPANTSY-15);
oft=hx1+(ESHIRTX-9)*(numimg==1||numimg==3||numimg==7)+3*(numimg==6||numimg==4)+(ESHIRTX-4)*(numimg==5);
oft2=hy1+ENDBODY-4;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,3,ENDBODY-1);


#endif
#ifdef DOS
putimage(hx1,hy1+EPANTSY-1,lines[14],COPY_PUT);
putimage(hx1+ESHIRTX-5,hy1+EPANTSY-1,lines[15],COPY_PUT);
putimage(hx1+(ESHIRTX-8)*(numimg==1||numimg==3||numimg==7)+
	 4*(numimg==6||numimg==4)+(ESHIRTX-4)*(numimg==5),
	 hy1+ENDBODY-4,lines[16],COPY_PUT);
#endif
}



#ifdef Linux
putlines3()
{
int oft,oft2;

//mode 1=dn 2=lf 3=rt   4=up
//4     
oft=ry3+skin3[2]*HF*(mode3!=1)+(!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7);  //right side
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,rx3,oft,rx3,oft,3,HMAN+1);
oft=ry3+skin3[2]*HF*(mode3!=4)+(!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7);  //7
oft2=rx3+ECHX-5-skin3[7]*2;  //-5 *2
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft2,oft,oft2,oft,4,HMAN+1);


 
//special for pant
if (skin3[7]>0)    
  {
oft=rx3+3;  //42
oft2=ry3+42-((skin3[2]<2)&&(mode3==1 || mode3==4))*25;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-45+((skin3[2]<2)&&(mode3==1 || mode3==4))*25);


oft=rx3+10;  //42
oft2=ry3+42-((skin3[2]<2)&&(mode3==1 || mode3==4))*25;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-45+((skin3[2]<2)&&(mode3==1 || mode3==4))*25);
  }


if (skin3[7]==0)    /*dress*/
  {

#if 0 //problem
if (mode3==1|| mode3==4)
{
oft=rx3+3;  //42
oft2=ry3+42;//-(skin3[2]<2)*25;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-55);//+(skin3[2]<2)*20);


oft=rx3+10;  //42
oft2=ry3+42;//-(skin3[2]<2)*25;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-55);
}
#endif



oft=rx3+2;
oft2=ry3+skin3[2]*HF*(mode3!=1)+(!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7);
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN+1);
oft=rx3+ECHX-6;
oft2=ry3+skin3[2]*HF*(mode3!=4)+(!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7);
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN+1);
oft=rx3+3;
oft2=ry3+skin3[2]*HF*(mode3!=1)+(!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7);
//XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN);
oft=rx3+ECHX-7;
oft2=ry3+skin3[2]*HF*(mode3!=4)+(!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7);
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,1,HMAN-oft2+ry3-10);


  }

XPutImage(xdisplay,pixmap[0],xgc,TitleImage,rx3,ry3,rx3,ry3,3,2);
oft=rx3+ECHX-7;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,ry3,oft,ry3,3,2);

if (skin3[2]!=2 || (skin3[2]==2 && mode3!=2))
  {
  if (mode3 !=2 || skin3[2]<2)              /*neck lines*/
    {

oft=rx3+3;
oft2=ry3+BSHIRTY-4;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,3,2);
oft=rx3+ESHIRTX-8;
oft2=ry3+BSHIRTY-4;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,4,2);


    }
  }
if (mode3==1||(skin3[2]==0&&mode3!=4))
  {

XPutImage(xdisplay,pixmap[0],xgc,TitleImage,rx3,ry3,rx3,ry3,1,NOSEY-2);//above nose/ear
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,rx3,ry3+NOSEY,rx3,ry3+NOSEY,1,BSHIRTY-NOSEY-2);  //left side under nose/ear
//could make ry3+NOSEY+1 to add more of a nose/ear on left
  }
if (mode3==4||(skin3[2]==0&&mode3!=1))
  {

oft=rx3+ESHIRTX-3-1*(skin3[2]==0&&mode3!=1);//3   top to top of nose/ear rt side
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,ry3,oft,ry3,3,NOSEY-2);
//oft=rx3+ESHIRTX-1; //3
oft2=ry3+NOSEY;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,3,BSHIRTY-NOSEY);
//added line below
if (skin3[2]==0&&mode3!=1)
 XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft+1,ry3,oft+1,ry3,1,BSHIRTY-NOSEY);

  }
/*shoes*/
#if 0 //def Linux  //14,15,16   5,5,4
oft2=ry3+EPANTSY-1;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,rx3,oft2,rx3,oft2,4,ENDBODY-EPANTSY-17);
oft=rx3+ESHIRTX-5;
oft2=ry3+EPANTSY-1;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,4,ENDBODY-EPANTSY-15);
oft=rx3+(ESHIRTX-9)*(numimg3==1||numimg3==3||numimg3==7)+3*(numimg3==6||numimg3==4)+(ESHIRTX-4)*(numimg3==5);
oft2=ry3+ENDBODY-4;
XPutImage(xdisplay,pixmap[0],xgc,TitleImage,oft,oft2,oft,oft2,3,ENDBODY-1);


#endif
}
#endif

#ifdef DOS
putlines3()
{
putimage(rx3,ry3+skin3[2]*HF*(mode3!=1)+
	  (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	  lines3[0],COPY_PUT);
putimage(rx3+ECHX-5-skin3[7]*2,ry3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     lines3[7],COPY_PUT);

if (skin3[7]==0)    /*dress*/
  {
  putimage(rx3+2,ry3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 lines3[10],COPY_PUT);
  putimage(rx3+ECHX-6,ry3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     lines3[11],COPY_PUT);
  putimage(rx3+3,ry3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 lines3[12],COPY_PUT);
  putimage(rx3+ECHX-7,ry3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     lines3[13],COPY_PUT);
  }

putimage(rx3,ry3,lines3[1],COPY_PUT);
putimage(rx3+ECHX-7,ry3,lines3[2],COPY_PUT);

if (skin3[2]!=2 || (skin3[2]==2 && mode3!=2))
  {
  if (mode3 !=2 || skin3[2]<2)              /*neck lines*/
    {
    putimage(rx3+3,ry3+BSHIRTY-4,lines3[3],COPY_PUT);
    putimage(rx3+ESHIRTX-7,ry3+BSHIRTY-4,lines3[4],COPY_PUT);
    }
  }
if (mode3==1||(skin3[2]==0&&mode3!=4))
  {
  putimage(rx3,ry3,lines3[5],COPY_PUT);
  putimage(rx3,ry3+NOSEY,lines3[8],COPY_PUT);
  }
if (mode3==4||(skin3[2]==0&&mode3!=1))
  {
  putimage(rx3+ESHIRTX-3,ry3,lines3[6],COPY_PUT);
  putimage(rx3+ESHIRTX-3,ry3+NOSEY,lines3[9],COPY_PUT);
  }
/*shoes*/
putimage(rx3,ry3+EPANTSY-1,lines3[14],COPY_PUT);
putimage(rx3+ESHIRTX-5,ry3+EPANTSY-1,lines3[15],COPY_PUT);
putimage(rx3+(ESHIRTX-8)*(numimg3==1||numimg3==3||numimg3==7)+
	 4*(numimg3==6||numimg3==4)+(ESHIRTX-4)*(numimg3==5),
	 ry3+ENDBODY-4,lines3[16],COPY_PUT);
}

#endif


getman()
{
int c;

for(c=0;c<8;c++)    /*get character images*/
   {
#ifdef Linux
  man[c]=XGetImage(xdisplay,pixmap[0],SCHX+c*F,SCHY,WMAN,HMAN,AllPlanes,ZPixmap);
#endif
#ifdef DOS
   man[c]=malloc(sizeman);
   getimage(SCHX+c*F,SCHY,SCHX+WMAN+c*F,SCHY+HMAN,man[c]);
#endif
   }
}

getrobot()
{
int c;

for(c=0;c<8;c++)    /*get character images*/
   {
#ifdef Linux
   robot[c]=XGetImage(xdisplay,pixmap[0],SCHX+c*F,SCHY,WMAN,HMAN,AllPlanes,ZPixmap);
#endif
#ifdef DOS
   robot[c]=malloc(sizeman);
   getimage(SCHX+c*F,SCHY,SCHX+WMAN+c*F,SCHY+HMAN,robot[c]);
#endif
   }
}


getcar(int c)
{
#ifdef Linux
   car[c]=XGetImage(xdisplay,pixmap[0],0,0,136,48,AllPlanes,ZPixmap);
#endif
#ifdef DOS
sizecar=imagesize(0,0,136,48);
if (c==0)
  screen[6]=malloc(sizecar);
car[c]=malloc(sizecar);
getimage(0,0,136,48,car[c]);
#endif
}

getroad(int c)
{
#ifdef Linux
   road[c]=XGetImage(xdisplay,pixmap[0],0,0,72,1,AllPlanes,ZPixmap);
#endif
#ifdef DOS
sizeroad=imagesize(0,0,72,1);
if (c==0)
  screen[7]=malloc(sizeroad);
road[c]=malloc(sizeroad);
getimage(0,0,72,1,road[c]);
#endif
}

getspike(int c)
{
#ifdef Linux
   spike[c]=XGetImage(xdisplay,pixmap[0],0,0,8,24,AllPlanes,ZPixmap);
#endif
#ifdef DOS
sizespike=imagesize(0,0,8,24);
if (c==0)
  screen[8]=malloc(sizespike);
spike[c]=malloc(sizespike);
getimage(0,0,8,24,spike[c]);
#endif
}

alloc_lines2()
{
int c;
int off;

#ifdef DOS
sizeheli=imagesize(0,0,60,25);
for(c=0;c<4;c++)
  {
  off=38*c;
  screen[c+1]=malloc(sizeheli);     /*allocate for screen image*/
  sizeline=imagesize(0,0,7,0); lines[off+17]=malloc(sizeline);
  lines[off+19]=malloc(sizeline);  sizeline=imagesize(0,0,1,0);
  lines[off+18]=malloc(sizeline); lines[off+20]=malloc(sizeline);
  sizeline=imagesize(0,0,15,2); lines[off+21]=malloc(sizeline);
  sizeline=imagesize(0,0,12,0); lines[off+22]=malloc(sizeline); lines[off+32]=malloc(sizeline);
  sizeline=imagesize(0,0,9,0); lines[off+23]=malloc(sizeline); lines[off+31]=malloc(sizeline);
  sizeline=imagesize(0,0,8,0); lines[off+24]=malloc(sizeline); lines[off+30]=malloc(sizeline);
  sizeline=imagesize(0,0,8,0); lines[off+25]=malloc(sizeline); lines[off+29]=malloc(sizeline);
  sizeline=imagesize(0,0,8,0); lines[off+26]=malloc(sizeline); lines[off+28]=malloc(sizeline);
  sizeline=imagesize(0,0,6,5); lines[off+27]=malloc(sizeline);
  sizeline=imagesize(0,0,56,0); lines[off+33]=malloc(sizeline);
  sizeline=imagesize(0,0,64,0); lines[off+34]=malloc(sizeline);
  sizeline=imagesize(0,0,30,0); lines[off+35]=malloc(sizeline);
  sizeline=imagesize(0,0,24,0); lines[off+36]=malloc(sizeline);
  sizeline=imagesize(0,0,23,0); lines[off+37]=malloc(sizeline);
  sizeline=imagesize(0,0,21,0); lines[off+38]=malloc(sizeline);
  sizeline=imagesize(0,0,15,0); lines[off+39]=malloc(sizeline);
  sizeline=imagesize(0,0,40,0); lines[off+40]=malloc(sizeline);
  sizeline=imagesize(0,0,38,0); lines[off+41]=malloc(sizeline);
  sizeline=imagesize(0,0,36,0); lines[off+42]=malloc(sizeline);
  sizeline=imagesize(0,0,29,0); lines[off+43]=malloc(sizeline);
  sizeline=imagesize(0,0,24,0); lines[off+44]=malloc(sizeline);
  sizeline=imagesize(0,0,11,0); lines[off+45]=malloc(sizeline);
  sizeline=imagesize(0,0,8,0); lines[off+46]=malloc(sizeline);
  sizeline=imagesize(0,0,5,0); lines[off+47]=malloc(sizeline);
  sizeline=imagesize(0,0,2,0); lines[off+48]=malloc(sizeline);
  sizeline=imagesize(0,0,4,0); lines[off+49]=malloc(sizeline);
  sizeline=imagesize(0,0,7,0); lines[off+50]=malloc(sizeline);
  sizeline=imagesize(0,0,11,0); lines[off+51]=malloc(sizeline);
  sizeline=imagesize(0,0,14,0); lines[off+52]=malloc(sizeline);
  sizeline=imagesize(0,0,19,0); lines[off+53]=malloc(sizeline);
  sizeline=imagesize(0,0,26,0); lines[off+54]=malloc(sizeline);
  }  /*end for all helis*/
#endif
}

getlines2()
{
int c;
int off;

for (c=0;c<4;c++)
  {
  off=38*c;
#ifdef Linux
lines[off+17]=XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1],obj[c+24].p[0]+6,obj[c+24].p[1],AllPlanes,ZPixmap);
lines[off+18]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+1,obj[c+24].p[0]+1,obj[c+24].p[1]+1,AllPlanes,ZPixmap);
lines[off+19]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+3,obj[c+24].p[0]+1,obj[c+24].p[1]+3,AllPlanes,ZPixmap);
lines[off+20]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+4,obj[c+24].p[0]+6,obj[c+24].p[1]+4,AllPlanes,ZPixmap);
lines[off+21]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+5,obj[c+24].p[0]+15,obj[c+24].p[1]+7,AllPlanes,ZPixmap);
lines[off+22]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+8,obj[c+24].p[0]+12,obj[c+24].p[1]+8,AllPlanes,ZPixmap);
lines[off+23]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+9,obj[c+24].p[0]+9,obj[c+24].p[1]+9,AllPlanes,ZPixmap);
lines[off+24]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+10,obj[c+24].p[0]+8,obj[c+24].p[1]+10,AllPlanes,ZPixmap);
lines[off+25]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+11,obj[c+24].p[0]+7,obj[c+24].p[1]+11,AllPlanes,ZPixmap);
lines[off+26]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+12,obj[c+24].p[0]+6,obj[c+24].p[1]+12,AllPlanes,ZPixmap);
lines[off+27]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+13,obj[c+24].p[0]+5,obj[c+24].p[1]+17,AllPlanes,ZPixmap);
lines[off+28]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+18,obj[c+24].p[0]+6,obj[c+24].p[1]+18,AllPlanes,ZPixmap);
lines[off+29]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+19,obj[c+24].p[0]+7,obj[c+24].p[1]+19,AllPlanes,ZPixmap);
lines[off+30]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+20,obj[c+24].p[0]+8,obj[c+24].p[1]+20,AllPlanes,ZPixmap);
lines[off+31]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+21,obj[c+24].p[0]+9,obj[c+24].p[1]+21,AllPlanes,ZPixmap);
lines[off+32]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+22,obj[c+24].p[0]+12,obj[c+24].p[1]+22,AllPlanes,ZPixmap);
lines[off+33]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+23,obj[c+24].p[0]+52,obj[c+24].p[1]+23,AllPlanes,ZPixmap);
lines[off+34]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1]+24,obj[c+24].p[0]+56,obj[c+24].p[1]+24,AllPlanes,ZPixmap);
lines[off+35]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+26,obj[c+24].p[1],obj[c+24].p[0]+56,obj[c+24].p[1],AllPlanes,ZPixmap);
lines[off+36]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+31,obj[c+24].p[1]+1,obj[c+24].p[0]+55,obj[c+24].p[1]+1,AllPlanes,ZPixmap);
lines[off+37]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+32,obj[c+24].p[1]+2,obj[c+24].p[0]+53,obj[c+24].p[1]+2,AllPlanes,ZPixmap);
lines[off+38]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+31,obj[c+24].p[1]+3,obj[c+24].p[0]+51,obj[c+24].p[1]+3,AllPlanes,ZPixmap);
lines[off+39]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+26,obj[c+24].p[1]+4,obj[c+24].p[0]+49,obj[c+24].p[1]+4,AllPlanes,ZPixmap);
lines[off+40]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+17,obj[c+24].p[1]+5,obj[c+24].p[0]+47,obj[c+24].p[1]+5,AllPlanes,ZPixmap);
lines[off+41]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+17,obj[c+24].p[1]+6,obj[c+24].p[0]+45,obj[c+24].p[1]+6,AllPlanes,ZPixmap);
lines[off+42]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+17,obj[c+24].p[1]+7,obj[c+24].p[0]+43,obj[c+24].p[1]+7,AllPlanes,ZPixmap);
lines[off+43]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+20,obj[c+24].p[1]+8,obj[c+24].p[0]+39,obj[c+24].p[1]+8,AllPlanes,ZPixmap);
lines[off+44]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+23,obj[c+24].p[1]+9,obj[c+24].p[0]+37,obj[c+24].p[1]+9,AllPlanes,ZPixmap);
lines[off+45]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+24,obj[c+24].p[1]+10,obj[c+24].p[0]+35,obj[c+24].p[1]+10,AllPlanes,ZPixmap);
lines[off+46]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+25,obj[c+24].p[1]+11,obj[c+24].p[0]+33,obj[c+24].p[1]+11,AllPlanes,ZPixmap);
lines[off+47]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+26,obj[c+24].p[1]+12,obj[c+24].p[0]+31,obj[c+24].p[1]+12,AllPlanes,ZPixmap);
lines[off+48]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+27,obj[c+24].p[1]+13,obj[c+24].p[0]+29,obj[c+24].p[1]+13,AllPlanes,ZPixmap);
lines[off+49]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+27,obj[c+24].p[1]+17,obj[c+24].p[0]+31,obj[c+24].p[1]+17,AllPlanes,ZPixmap);
lines[off+50]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+26,obj[c+24].p[1]+18,obj[c+24].p[0]+34,obj[c+24].p[1]+18,AllPlanes,ZPixmap);
lines[off+51]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+25,obj[c+24].p[1]+19,obj[c+24].p[0]+38,obj[c+24].p[1]+19,AllPlanes,ZPixmap);
lines[off+52]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+24,obj[c+24].p[1]+20,obj[c+24].p[0]+41,obj[c+24].p[1]+20,AllPlanes,ZPixmap);
lines[off+53]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+23,obj[c+24].p[1]+21,obj[c+24].p[0]+45,obj[c+24].p[1]+21,AllPlanes,ZPixmap);
lines[off+54]=  XGetImage(xdisplay,pixmap[0],obj[c+24].p[0]+20,obj[c+24].p[1]+22,obj[c+24].p[0]+49,obj[c+24].p[1]+22,AllPlanes,ZPixmap);
#endif

#ifdef DOS
  getimage(obj[c+24].p[0],obj[c+24].p[1],obj[c+24].p[0]+6,obj[c+24].p[1],lines[off+17]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+1,obj[c+24].p[0]+1,obj[c+24].p[1]+1,lines[off+18]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+3,obj[c+24].p[0]+1,obj[c+24].p[1]+3,lines[off+19]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+4,obj[c+24].p[0]+6,obj[c+24].p[1]+4,lines[off+20]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+5,obj[c+24].p[0]+15,obj[c+24].p[1]+7,lines[off+21]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+8,obj[c+24].p[0]+12,obj[c+24].p[1]+8,lines[off+22]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+9,obj[c+24].p[0]+9,obj[c+24].p[1]+9,lines[off+23]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+10,obj[c+24].p[0]+8,obj[c+24].p[1]+10,lines[off+24]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+11,obj[c+24].p[0]+7,obj[c+24].p[1]+11,lines[off+25]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+12,obj[c+24].p[0]+6,obj[c+24].p[1]+12,lines[off+26]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+13,obj[c+24].p[0]+5,obj[c+24].p[1]+17,lines[off+27]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+18,obj[c+24].p[0]+6,obj[c+24].p[1]+18,lines[off+28]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+19,obj[c+24].p[0]+7,obj[c+24].p[1]+19,lines[off+29]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+20,obj[c+24].p[0]+8,obj[c+24].p[1]+20,lines[off+30]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+21,obj[c+24].p[0]+9,obj[c+24].p[1]+21,lines[off+31]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+22,obj[c+24].p[0]+12,obj[c+24].p[1]+22,lines[off+32]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+23,obj[c+24].p[0]+52,obj[c+24].p[1]+23,lines[off+33]);
  getimage(obj[c+24].p[0],obj[c+24].p[1]+24,obj[c+24].p[0]+56,obj[c+24].p[1]+24,lines[off+34]);
  getimage(obj[c+24].p[0]+26,obj[c+24].p[1],obj[c+24].p[0]+56,obj[c+24].p[1],lines[off+35]);
  getimage(obj[c+24].p[0]+31,obj[c+24].p[1]+1,obj[c+24].p[0]+55,obj[c+24].p[1]+1,lines[off+36]);
  getimage(obj[c+24].p[0]+32,obj[c+24].p[1]+2,obj[c+24].p[0]+53,obj[c+24].p[1]+2,lines[off+37]);
  getimage(obj[c+24].p[0]+31,obj[c+24].p[1]+3,obj[c+24].p[0]+51,obj[c+24].p[1]+3,lines[off+38]);
  getimage(obj[c+24].p[0]+26,obj[c+24].p[1]+4,obj[c+24].p[0]+49,obj[c+24].p[1]+4,lines[off+39]);
  getimage(obj[c+24].p[0]+17,obj[c+24].p[1]+5,obj[c+24].p[0]+47,obj[c+24].p[1]+5,lines[off+40]);
  getimage(obj[c+24].p[0]+17,obj[c+24].p[1]+6,obj[c+24].p[0]+45,obj[c+24].p[1]+6,lines[off+41]);
  getimage(obj[c+24].p[0]+17,obj[c+24].p[1]+7,obj[c+24].p[0]+43,obj[c+24].p[1]+7,lines[off+42]);
  getimage(obj[c+24].p[0]+20,obj[c+24].p[1]+8,obj[c+24].p[0]+39,obj[c+24].p[1]+8,lines[off+43]);
  getimage(obj[c+24].p[0]+23,obj[c+24].p[1]+9,obj[c+24].p[0]+37,obj[c+24].p[1]+9,lines[off+44]);
  getimage(obj[c+24].p[0]+24,obj[c+24].p[1]+10,obj[c+24].p[0]+35,obj[c+24].p[1]+10,lines[off+45]);
  getimage(obj[c+24].p[0]+25,obj[c+24].p[1]+11,obj[c+24].p[0]+33,obj[c+24].p[1]+11,lines[off+46]);
  getimage(obj[c+24].p[0]+26,obj[c+24].p[1]+12,obj[c+24].p[0]+31,obj[c+24].p[1]+12,lines[off+47]);
  getimage(obj[c+24].p[0]+27,obj[c+24].p[1]+13,obj[c+24].p[0]+29,obj[c+24].p[1]+13,lines[off+48]);
  getimage(obj[c+24].p[0]+27,obj[c+24].p[1]+17,obj[c+24].p[0]+31,obj[c+24].p[1]+17,lines[off+49]);
  getimage(obj[c+24].p[0]+26,obj[c+24].p[1]+18,obj[c+24].p[0]+34,obj[c+24].p[1]+18,lines[off+50]);
  getimage(obj[c+24].p[0]+25,obj[c+24].p[1]+19,obj[c+24].p[0]+38,obj[c+24].p[1]+19,lines[off+51]);
  getimage(obj[c+24].p[0]+24,obj[c+24].p[1]+20,obj[c+24].p[0]+41,obj[c+24].p[1]+20,lines[off+52]);
  getimage(obj[c+24].p[0]+23,obj[c+24].p[1]+21,obj[c+24].p[0]+45,obj[c+24].p[1]+21,lines[off+53]);
  getimage(obj[c+24].p[0]+20,obj[c+24].p[1]+22,obj[c+24].p[0]+49,obj[c+24].p[1]+22,lines[off+54]);
#endif
  }
}

putlines2()
{
int c;
int off;

for (c=0;c<4;c++)
  {
  off=38*c;   /*offset between helicopters-38*/
#ifdef Linux
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1],obj[c+24].p[0],obj[c+24].p[1],7,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+1,obj[c+24].p[0],obj[c+24].p[1]+1,2,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+3,obj[c+24].p[0],obj[c+24].p[1]+3,2,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+4,obj[c+24].p[0],obj[c+24].p[1]+4,7,3);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+5,obj[c+24].p[0],obj[c+24].p[1]+5,16,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+6,obj[c+24].p[0],obj[c+24].p[1]+6,12,1);  //added
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+7,obj[c+24].p[0],obj[c+24].p[1]+7,12,1);//added
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+8,obj[c+24].p[0],obj[c+24].p[1]+8,13,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+9,obj[c+24].p[0],obj[c+24].p[1]+9,10,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+10,obj[c+24].p[0],obj[c+24].p[1]+10,9,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+11,obj[c+24].p[0],obj[c+24].p[1]+11,8,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+12,obj[c+24].p[0],obj[c+24].p[1]+12,7,5);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+13,obj[c+24].p[0],obj[c+24].p[1]+13,6,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+17,obj[c+24].p[0],obj[c+24].p[1]+17,7,1);  //added
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+18,obj[c+24].p[0],obj[c+24].p[1]+18,7,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+19,obj[c+24].p[0],obj[c+24].p[1]+19,8,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+20,obj[c+24].p[0],obj[c+24].p[1]+20,9,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+21,obj[c+24].p[0],obj[c+24].p[1]+21,10,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+22,obj[c+24].p[0],obj[c+24].p[1]+22,13,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+23,obj[c+24].p[0],obj[c+24].p[1]+23,53,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0],obj[c+24].p[1]+24,obj[c+24].p[0],obj[c+24].p[1]+24,57,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+26,obj[c+24].p[1],obj[c+24].p[0]+26,obj[c+24].p[1],31,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+31,obj[c+24].p[1]+1,obj[c+24].p[0]+31,obj[c+24].p[1]+1,25,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+32,obj[c+24].p[1]+2,obj[c+24].p[0]+32,obj[c+24].p[1]+2,22,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+31,obj[c+24].p[1]+3,obj[c+24].p[0]+31,obj[c+24].p[1]+3,21,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+26,obj[c+24].p[1]+4,obj[c+24].p[0]+26,obj[c+24].p[1]+4,24,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+17,obj[c+24].p[1]+5,obj[c+24].p[0]+17,obj[c+24].p[1]+5,31,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+17,obj[c+24].p[1]+6,obj[c+24].p[0]+17,obj[c+24].p[1]+6,29,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+17,obj[c+24].p[1]+7,obj[c+24].p[0]+17,obj[c+24].p[1]+7,27,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+20,obj[c+24].p[1]+8,obj[c+24].p[0]+20,obj[c+24].p[1]+8,20,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+23,obj[c+24].p[1]+9,obj[c+24].p[0]+23,obj[c+24].p[1]+9,15,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+24,obj[c+24].p[1]+10,obj[c+24].p[0]+24,obj[c+24].p[1]+10,12,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+25,obj[c+24].p[1]+11,obj[c+24].p[0]+25,obj[c+24].p[1]+11,9,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+26,obj[c+24].p[1]+12,obj[c+24].p[0]+26,obj[c+24].p[1]+12,6,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+27,obj[c+24].p[1]+13,obj[c+24].p[0]+27,obj[c+24].p[1]+13,3,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+27,obj[c+24].p[1]+17,obj[c+24].p[0]+27,obj[c+24].p[1]+17,5,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+26,obj[c+24].p[1]+18,obj[c+24].p[0]+26,obj[c+24].p[1]+18,9,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+25,obj[c+24].p[1]+19,obj[c+24].p[0]+25,obj[c+24].p[1]+19,14,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+24,obj[c+24].p[1]+20,obj[c+24].p[0]+24,obj[c+24].p[1]+20,18,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+23,obj[c+24].p[1]+21,obj[c+24].p[0]+23,obj[c+24].p[1]+21,23,1);
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,obj[c+24].p[0]+20,obj[c+24].p[1]+22,obj[c+24].p[0]+20,obj[c+24].p[1]+22,30,1);
#endif

#ifdef DOS
  putimage(obj[c+24].p[0],obj[c+24].p[1],lines[off+17],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+1,lines[off+18],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+3,lines[off+19],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+4,lines[off+20],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+5,lines[off+21],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+8,lines[off+22],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+9,lines[off+23],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+10,lines[off+24],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+11,lines[off+25],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+12,lines[off+26],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+13,lines[off+27],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+18,lines[off+28],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+19,lines[off+29],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+20,lines[off+30],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+21,lines[off+31],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+22,lines[off+32],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+23,lines[off+33],COPY_PUT);
  putimage(obj[c+24].p[0],obj[c+24].p[1]+24,lines[off+34],COPY_PUT);
  putimage(obj[c+24].p[0]+26,obj[c+24].p[1],lines[off+35],COPY_PUT);
  putimage(obj[c+24].p[0]+31,obj[c+24].p[1]+1,lines[off+36],COPY_PUT);
  putimage(obj[c+24].p[0]+32,obj[c+24].p[1]+2,lines[off+37],COPY_PUT);
  putimage(obj[c+24].p[0]+31,obj[c+24].p[1]+3,lines[off+38],COPY_PUT);
  putimage(obj[c+24].p[0]+26,obj[c+24].p[1]+4,lines[off+39],COPY_PUT);
  putimage(obj[c+24].p[0]+17,obj[c+24].p[1]+5,lines[off+40],COPY_PUT);
  putimage(obj[c+24].p[0]+17,obj[c+24].p[1]+6,lines[off+41],COPY_PUT);
  putimage(obj[c+24].p[0]+17,obj[c+24].p[1]+7,lines[off+42],COPY_PUT);
  putimage(obj[c+24].p[0]+20,obj[c+24].p[1]+8,lines[off+43],COPY_PUT);
  putimage(obj[c+24].p[0]+23,obj[c+24].p[1]+9,lines[off+44],COPY_PUT);
  putimage(obj[c+24].p[0]+24,obj[c+24].p[1]+10,lines[off+45],COPY_PUT);
  putimage(obj[c+24].p[0]+25,obj[c+24].p[1]+11,lines[off+46],COPY_PUT);
  putimage(obj[c+24].p[0]+26,obj[c+24].p[1]+12,lines[off+47],COPY_PUT);
  putimage(obj[c+24].p[0]+27,obj[c+24].p[1]+13,lines[off+48],COPY_PUT);
  putimage(obj[c+24].p[0]+27,obj[c+24].p[1]+17,lines[off+49],COPY_PUT);
  putimage(obj[c+24].p[0]+26,obj[c+24].p[1]+18,lines[off+50],COPY_PUT);
  putimage(obj[c+24].p[0]+25,obj[c+24].p[1]+19,lines[off+51],COPY_PUT);
  putimage(obj[c+24].p[0]+24,obj[c+24].p[1]+20,lines[off+52],COPY_PUT);
  putimage(obj[c+24].p[0]+23,obj[c+24].p[1]+21,lines[off+53],COPY_PUT);
  putimage(obj[c+24].p[0]+20,obj[c+24].p[1]+22,lines[off+54],COPY_PUT);
#endif
  }
}

getheli()
{
int c;

for(c=0;c<4;c++)
  {
//fprintf(stderr,"%d %d %d\n",obj[c+24].p[0],obj[c+24].p[1],0);
#ifdef Linux
   heli[c]=XGetImage(xdisplay,pixmap[0],obj[c+24].p[0],obj[c+24].p[1],58,24,AllPlanes,ZPixmap);  //58 24
#endif
#ifdef DOS
  heli[c]=malloc(sizeheli);
  getimage(obj[c+24].p[0],obj[c+24].p[1],obj[c+24].p[0]+58,obj[c+24].p[1]+24,heli[c]);
#endif
  }
}

