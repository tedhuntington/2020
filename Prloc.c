#include "conio.h"
#include "fcntl.h"
#include "dos.h"
#include "stdio.h"
#define NUMLOC 40
struct doors		/*door structs*/
  {
  int a[4];	/*x1,y1,x2,y2*/
  int vis;	/*0-yes, 1-no*/
  int next;	/*next room*/
  };
struct doors door[9];
int pntx[4],pnty[4];	/*boundary points for picture*/
FILE *fptr;

main()
  {
  int a,b;
  char nm[10];

  for (a=0;a<NUMLOC;a++)
    {
    itoa(a,nm,10);
    strcat(nm,".DOR");
    if ( (fptr=fopen(nm,"rb"))==NULL)
       {printf("Can't open file %s",nm); getch(); }
    else
       fread(&door,sizeof(door[0]),9,fptr);
    fclose(fptr);
    printf("Room  #%d\n",a);
    for (b=0;b<10;b++)
      printf("door %d:   x1 %d   y1 %d  x2 %d  y2 %d   vis %d  to loc: %d\n",
		b,door[b].a[0],door[b].a[1],door[b].a[2],door[b].a[3],
		door[b].vis,door[b].next);
  itoa(a,nm,10);
  strcat(nm,".EDG");
  if ( (fptr=fopen(nm,"rb"))==NULL)
     {printf("Can't open file %s",nm); getch(); }
  else
     {
     fread(&pntx[0],sizeof(pntx[0]),4,fptr);
     fread(&pnty[0],sizeof(pnty[0]),4,fptr);
     }
  fclose(fptr);
  printf("\n\nBoundary points\n");
  for(b=0;b<4;b++)
    printf("x%d %d  y%d %d\n",b,pntx[b],b,pnty[b]);
  }  /*end for a*/
}