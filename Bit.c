/*  bit.c   */
/*  bit image lines for 2020!   */
/*  by Ted Huntington  */

#include "2020.h"
#include "alloc.h"
#include "graphics.h"

struct objects
  {
  char name[11];
  int p[4];
  int loc;
  };
extern struct objects obj[NUMOBJ];
extern int numimg,numimg3,mode,mode3;
extern int x1,y1,x2,y2;        /*point coordinates*/
extern int x3,y3,x4,y4;
extern int skin[8];             /*characters attributes*/
extern int skin3[8];             /*characters attributes*/
extern unsigned sizeman;	/*size of character image*/
extern unsigned sizeheli;	/*size of heli image*/
extern unsigned sizeline;	/*size of line fills*/
extern unsigned sizecar;
extern unsigned sizeroad;
extern unsigned sizespike;
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

alloc_lines()
{
 free(screen[0]);
 free(lines[0]); free(lines[1]); free(lines[2]); free(lines[3]);
 free(lines[4]); free(lines[5]); free(lines[6]); free(lines[7]);
 free(lines[8]); free(lines[9]); free(lines[10]); free(lines[11]);
 free(lines[12]); free(lines[13]); free(lines[14]); free(lines[15]);
 free(lines[16]);
 sizeman=imagesize(0,0,WMAN+3,HMAN);
  screen[0]=malloc(sizeman);     /*allocate for screen image*/
  screen[1]=malloc(sizeman);     /*allocate for screen image*/
/*  sizeline=imagesize(0,0,1+skin[7]*2,HMAN);*/
  sizeline=imagesize(0,0,3,HMAN);
  lines[0]=malloc(sizeline);     /*pants&dress- head to toe left side*/
  lines[7]=malloc(sizeline);     /*pants&dress- head to toe right*/
/*  if (skin[7]==0)    dress
    {*/
    sizeline=imagesize(0,0,0,HMAN);  /*HMAN-DF*/
    lines[10]=malloc(sizeline);     /*dress- head to toe left side*/
    lines[11]=malloc(sizeline);                  /*right*/
    sizeline=imagesize(0,0,0,HMAN); /*HMAN-DF2*/
    lines[12]=malloc(sizeline);     /*dress- head to toe left inside*/
    lines[13]=malloc(sizeline);                  /*right*/
/*    }*/    /*this was an error found by Kevin Borgnis! */
  sizeline=imagesize(0,0,2,1);
  lines[1]=malloc(sizeline);    /*top of head*/
  lines[2]=malloc(sizeline);
  sizeline=imagesize(0,0,4,1);  /*between head and shoulders*/
  lines[3]=malloc(sizeline);
  lines[4]=malloc(sizeline);
  sizeline=imagesize(0,0,2,NOSEY);  /*between top of head and nose*/
  lines[5]=malloc(sizeline);
  lines[6]=malloc(sizeline);
  sizeline=imagesize(0,NOSEY,0,BSHIRTY-1);  /*between nose and shoulders*/
  lines[8]=malloc(sizeline);
  sizeline=imagesize(0,NOSEY,1,BSHIRTY-1);  /*between nose and shoulders*/
  lines[9]=malloc(sizeline);
  sizeline=imagesize(0,EPANTSY-17,5,ENDBODY);  /*bottom of pants to shoes*/
  lines[14]=malloc(sizeline);
  lines[15]=malloc(sizeline);
  sizeline=imagesize(0,ENDBODY-3,4,ENDBODY);  /*bottom of pants to shoes*/
  lines[16]=malloc(sizeline);
}

getlines()
{
getimage(x1,y1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 x1+1+skin[7]*2,y1+HMAN-4*(mode==1),lines[0]);
getimage(x1+ECHX-5-skin[7]*2,y1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     x1+ECHX-3,y1+HMAN-4*(mode==4),lines[7]);
if (skin[7]==0)    /*dress*/
  {
  getimage(x1+2,y1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 x1+2,y1+HMAN-DF,lines[10]);
  getimage(x1+ECHX-6,y1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     x1+ECHX-6,y1+HMAN-DF,lines[11]);
  getimage(x1+3,y1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 x1+3,y1+HMAN-DF2,lines[12]);
  getimage(x1+ECHX-7,y1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     x1+ECHX-7,y1+HMAN-DF2,lines[13]);
  }
getimage(x1,y1,x1+2,y1+1,lines[1]);
getimage(x1+ECHX-7,y1,x1+ECHX-4,y1+1,lines[2]);
if (skin[2]!=2 || (skin[2]==2 && mode!=2))
  {
  if (mode!=2 || skin[2]<2)
    {
    getimage(x1+3,y1+BSHIRTY-4,x1+5,y1+BSHIRTY-3,lines[3]);
    getimage(x1+ESHIRTX-7,y1+BSHIRTY-4,x1+ESHIRTX-5,y1+BSHIRTY-3,lines[4]);
    }
  }
if (mode==1||(skin[2]==0&&mode!=4))
  {
  getimage(x1,y1,x1,y1+NOSEY-3,lines[5]);
  getimage(x1,y1+NOSEY,x1,y1+BSHIRTY-1,lines[8]);
  }
if (mode==4||(skin[2]==0&&mode!=1))
  {
  getimage(x1+ESHIRTX-3,y1,x1+ESHIRTX-1,y1+NOSEY-3,lines[6]);
  getimage(x1+ESHIRTX-3,y1+NOSEY,x1+ESHIRTX-2,y1+BSHIRTY-1,lines[9]);
  }
/*shoes*/
getimage(x1,y1+EPANTSY-1,x1+3,y1+ENDBODY-7*(numimg==0)-5*(numimg==1),lines[14]);
getimage(x1+ESHIRTX-5,y1+EPANTSY-1,x1+ESHIRTX-4+2*(numimg==4),
	 y1+ENDBODY-7*(numimg==5)-5*(numimg==4),lines[15]);
/*square under shoe*/
getimage(x1+(ESHIRTX-8)*(numimg==1||numimg==3||numimg==7)+
	4*(numimg==6||numimg==4)+(ESHIRTX-4)*(numimg==5),y1+ENDBODY-4,
	 x1+(ESHIRTX-7)*(numimg==1||numimg==3||numimg==7)+2+
	 4*(numimg==6||numimg==4)+4*(numimg==2)+(ESHIRTX-4)*(numimg==5),
	 y1+ENDBODY-2,lines[16]);
}

alloc_lines3()
{
 free(screen3[0]);
 free(lines3[0]); free(lines3[1]); free(lines3[2]); free(lines3[3]);
 free(lines3[4]); free(lines3[5]); free(lines3[6]); free(lines3[7]);
 free(lines3[8]); free(lines3[9]); free(lines3[10]); free(lines3[11]);
 free(lines3[12]); free(lines3[13]); free(lines3[14]); free(lines3[15]);
 free(lines3[16]);
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
}

getlines3()
{
getimage(x3,y3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 x3+1+skin3[7]*2,y3+HMAN-4*(mode3==1),lines3[0]);
getimage(x3+ECHX-5-skin3[7]*2,y3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     x3+ECHX-3,y3+HMAN-4*(mode3==4),lines3[7]);
if (skin3[7]==0)    /*dress*/
  {
  getimage(x3+2,y3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 x3+2,y3+HMAN-DF,lines3[10]);
  getimage(x3+ECHX-6,y3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     x3+ECHX-6,y3+HMAN-DF,lines3[11]);
  getimage(x3+3,y3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 x3+3,y3+HMAN-DF2,lines3[12]);
  getimage(x3+ECHX-7,y3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     x3+ECHX-7,y3+HMAN-DF2,lines3[13]);
  }
getimage(x3,y3,x3+2,y3+1,lines3[1]);
getimage(x3+ECHX-7,y3,x3+ECHX-4,y3+1,lines3[2]);
if (skin3[2]!=2 || (skin3[2]==2 && mode3!=2))
  {
  if (mode3!=2 || skin3[2]<2)
    {
    getimage(x3+3,y3+BSHIRTY-4,x3+5,y3+BSHIRTY-3,lines3[3]);
    getimage(x3+ESHIRTX-7,y3+BSHIRTY-4,x3+ESHIRTX-5,y3+BSHIRTY-3,lines3[4]);
    }
  }
if (mode3==1||(skin3[2]==0&&mode3!=4))
  {
  getimage(x3,y3,x3,y3+NOSEY-3,lines3[5]);
  getimage(x3,y3+NOSEY,x3,y3+BSHIRTY-1,lines3[8]);
  }
if (mode3==4||(skin3[2]==0&&mode!=1))
  {
  getimage(x3+ESHIRTX-3,y3,x3+ESHIRTX-1,y3+NOSEY-3,lines3[6]);
  getimage(x3+ESHIRTX-3,y3+NOSEY,x3+ESHIRTX-2,y3+BSHIRTY-1,lines3[9]);
  }
/*shoes*/
getimage(x3,y3+EPANTSY-1,x3+3,y3+ENDBODY-7*(numimg3==0)-5*(numimg3==1),lines3[14]);
getimage(x3+ESHIRTX-5,y3+EPANTSY-1,x3+ESHIRTX-4+2*(numimg3==4),
	 y3+ENDBODY-7*(numimg3==5)-5*(numimg3==4),lines3[15]);
/*square under shoe*/
getimage(x3+(ESHIRTX-8)*(numimg3==1||numimg3==3||numimg3==7)+
	4*(numimg3==6||numimg3==4)+(ESHIRTX-4)*(numimg3==5),y3+ENDBODY-4,
	 x3+(ESHIRTX-7)*(numimg3==1||numimg3==3||numimg3==7)+2+
	 4*(numimg3==6||numimg3==4)+4*(numimg3==2)+(ESHIRTX-4)*(numimg3==5),
	 y3+ENDBODY-2,lines3[16]);
}

putlines()
{
putimage(x1,y1+skin[2]*HF*(mode!=1)+
	  (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	  lines[0],COPY_PUT);
putimage(x1+ECHX-5-skin[7]*2,y1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     lines[7],COPY_PUT);
if (skin[7]==0)    /*dress*/
  {
  putimage(x1+2,y1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 lines[10],COPY_PUT);
  putimage(x1+ECHX-6,y1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     lines[11],COPY_PUT);
  putimage(x1+3,y1+skin[2]*HF*(mode!=1)+
	 (!(skin[2]==0&&mode==4)&&(skin[2]==0||mode==1))*(NOSEY+7),
	 lines[12],COPY_PUT);
  putimage(x1+ECHX-7,y1+skin[2]*HF*(mode!=4)+
	     (!(skin[2]==0&&mode==1)&&(skin[2]==0||mode==4))*(NOSEY+7),
	     lines[13],COPY_PUT);
  }
putimage(x1,y1,lines[1],COPY_PUT);
putimage(x1+ECHX-7,y1,lines[2],COPY_PUT);
if (skin[2]!=2 || (skin[2]==2 && mode!=2))
  {
  if (mode !=2 || skin[2]<2)              /*neck lines*/
    {
    putimage(x1+3,y1+BSHIRTY-4,lines[3],COPY_PUT);
    putimage(x1+ESHIRTX-7,y1+BSHIRTY-4,lines[4],COPY_PUT);
    }
  }
if (mode==1||(skin[2]==0&&mode!=4))
  {
  putimage(x1,y1,lines[5],COPY_PUT);
  putimage(x1,y1+NOSEY,lines[8],COPY_PUT);
  }
if (mode==4||(skin[2]==0&&mode!=1))
  {
  putimage(x1+ESHIRTX-3,y1,lines[6],COPY_PUT);
  putimage(x1+ESHIRTX-3,y1+NOSEY,lines[9],COPY_PUT);
  }
/*shoes*/
putimage(x1,y1+EPANTSY-1,lines[14],COPY_PUT);
putimage(x1+ESHIRTX-5,y1+EPANTSY-1,lines[15],COPY_PUT);
putimage(x1+(ESHIRTX-8)*(numimg==1||numimg==3||numimg==7)+
	 4*(numimg==6||numimg==4)+(ESHIRTX-4)*(numimg==5),
	 y1+ENDBODY-4,lines[16],COPY_PUT);
}

putlines3()
{
putimage(x3,y3+skin3[2]*HF*(mode3!=1)+
	  (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	  lines3[0],COPY_PUT);
putimage(x3+ECHX-5-skin3[7]*2,y3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     lines3[7],COPY_PUT);
if (skin3[7]==0)    /*dress*/
  {
  putimage(x3+2,y3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 lines3[10],COPY_PUT);
  putimage(x3+ECHX-6,y3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     lines3[11],COPY_PUT);
  putimage(x3+3,y3+skin3[2]*HF*(mode3!=1)+
	 (!(skin3[2]==0&&mode3==4)&&(skin3[2]==0||mode3==1))*(NOSEY+7),
	 lines3[12],COPY_PUT);
  putimage(x3+ECHX-7,y3+skin3[2]*HF*(mode3!=4)+
	     (!(skin3[2]==0&&mode3==1)&&(skin3[2]==0||mode3==4))*(NOSEY+7),
	     lines3[13],COPY_PUT);
  }
putimage(x3,y3,lines3[1],COPY_PUT);
putimage(x3+ECHX-7,y3,lines3[2],COPY_PUT);
if (skin3[2]!=2 || (skin3[2]==2 && mode3!=2))
  {
  if (mode3 !=2 || skin3[2]<2)              /*neck lines*/
    {
    putimage(x3+3,y3+BSHIRTY-4,lines3[3],COPY_PUT);
    putimage(x3+ESHIRTX-7,y3+BSHIRTY-4,lines3[4],COPY_PUT);
    }
  }
if (mode3==1||(skin3[2]==0&&mode3!=4))
  {
  putimage(x3,y3,lines3[5],COPY_PUT);
  putimage(x3,y3+NOSEY,lines3[8],COPY_PUT);
  }
if (mode3==4||(skin3[2]==0&&mode3!=1))
  {
  putimage(x3+ESHIRTX-3,y3,lines3[6],COPY_PUT);
  putimage(x3+ESHIRTX-3,y3+NOSEY,lines3[9],COPY_PUT);
  }
/*shoes*/
putimage(x3,y3+EPANTSY-1,lines3[14],COPY_PUT);
putimage(x3+ESHIRTX-5,y3+EPANTSY-1,lines3[15],COPY_PUT);
putimage(x3+(ESHIRTX-8)*(numimg3==1||numimg3==3||numimg3==7)+
	 4*(numimg3==6||numimg3==4)+(ESHIRTX-4)*(numimg3==5),
	 y3+ENDBODY-4,lines3[16],COPY_PUT);
}

getman()
{
int c;

for(c=0;c<8;c++)    /*get character images*/
   {
   man[c]=malloc(sizeman);
   getimage(SCHX+c*F,SCHY,SCHX+WMAN+c*F,SCHY+HMAN,man[c]);
   }
}

getrobot()
{
int c;

for(c=0;c<8;c++)    /*get character images*/
   {
   robot[c]=malloc(sizeman);
   getimage(SCHX+c*F,SCHY,SCHX+WMAN+c*F,SCHY+HMAN,robot[c]);
   }
}


getcar(int c)
{
sizecar=imagesize(0,0,136,48);
if (c==0)
  screen[6]=malloc(sizecar);
car[c]=malloc(sizecar);
getimage(0,0,136,48,car[c]);
}

getroad(int c)
{
sizeroad=imagesize(0,0,72,1);
if (c==0)
  screen[7]=malloc(sizeroad);
road[c]=malloc(sizeroad);
getimage(0,0,72,1,road[c]);
}

getspike(int c)
{
sizespike=imagesize(0,0,8,24);
if (c==0)
  screen[8]=malloc(sizespike);
spike[c]=malloc(sizespike);
getimage(0,0,8,24,spike[c]);
}

alloc_lines2()
{
int c;
int off;

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
}

getlines2()
{
int c;
int off;

for (c=0;c<4;c++)
  {
  off=38*c;
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
  }
}

putlines2()
{
int c;
int off;

for (c=0;c<4;c++)
  {
  off=38*c;   /*offset between helicopters-38*/
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
  }
}

getheli()
{
int c;

for(c=0;c<4;c++)
  {
  heli[c]=malloc(sizeheli);
  getimage(obj[c+24].p[0],obj[c+24].p[1],obj[c+24].p[0]+58,obj[c+24].p[1]+24,heli[c]);
  }
}