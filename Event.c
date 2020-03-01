/*event.c - make events for 2020*/

#ifdef DOS
#include "conio.h"
#endif
#include "stdio.h"
#include "stdlib.h"
#include "2020.h"
#include "fcntl.h"
#include "time.h"
#ifdef DOS
#include "dos.h"
#endif

#ifdef Linux
typedef struct _event2020
   {
   struct tm *beg;     /*begin time for event*/
   struct tm *end;	/*end time for event*/
   int loc;		/*location # of event*/
   int obnum;		/*object number that appears-disappears*/
   }event2020;
event2020 *eve;
time_t temptime;
#endif

#ifdef DOS
struct event2020
   {
   struct time beg;     /*begin time for event*/
   struct time end;	/*end time for event*/
   int loc;		/*location # of event*/
   int obnum;		/*object number that appears-disappears*/
   };

struct event2020 eve[NUMEVE];
#endif

#ifdef Linux
char PATH[] = {'/','r','o','o','t','/','2','0','2','0','D','/','\0'};
#endif
#ifdef DOS
char PATH[] = {0x5c,'2','0','2','0',0x5c,'\0'};
#endif

main()
{
int a;
#ifdef Linux
char *nm;
#endif
#ifdef DOS
char nm[25];
#endif
FILE *fptr;
void *tptr;


#ifdef Linux

nm=(char *)malloc(100);

eve=(event2020 *)malloc(sizeof(event2020)*(100));

temptime=time(NULL);
for(a=0;a<NUMEVE;a++)
{
eve[a].beg=(struct tm *)malloc(sizeof(struct tm));
eve[a].end=(struct tm *)malloc(sizeof(struct tm));


//had not good effect!
//eve[a].beg=localtime(&temptime);
//eve[a].end=localtime(&temptime);
}



eve[0].beg->tm_hour=6;	eve[0].beg->tm_min=0;	eve[0].beg->tm_sec=0;
eve[0].end->tm_hour=6;	eve[0].end->tm_min=30;	eve[0].end->tm_sec=0;
fprintf(stderr,"Hour now: %d",eve[0].beg->tm_hour);

#endif
#ifdef DOS
eve[0].beg.ti_hour=6;	eve[0].beg.ti_min=0;	eve[0].beg.ti_sec=0;
eve[0].beg.ti_hund=0;
eve[0].end.ti_hour=6;	eve[0].end.ti_min=30;	eve[0].end.ti_sec=0;
eve[0].end.ti_hund=0;
#endif
eve[0].loc=7;	eve[0].obnum=0;

#ifdef Linux
eve[1].beg->tm_hour=6;	eve[1].beg->tm_min=30;	eve[1].beg->tm_sec=0;
eve[1].end->tm_hour=7;	eve[1].end->tm_min=0;	eve[1].end->tm_sec=0;
#endif
#ifdef DOS
eve[1].beg.ti_hour=6;	eve[1].beg.ti_min=30;	eve[1].beg.ti_sec=0;
eve[1].beg.ti_hund=0;
eve[1].end.ti_hour=7;	eve[1].end.ti_min=0;	eve[1].end.ti_sec=0;
eve[1].end.ti_hund=0;
#endif
eve[1].loc=7;	eve[1].obnum=1;



#ifdef Linux
eve[2].beg->tm_hour=7;	eve[2].beg->tm_min=0;	eve[2].beg->tm_sec=0;
eve[2].end->tm_hour=7;	eve[2].end->tm_min=30;	eve[2].end->tm_sec=0;
#endif
#ifdef DOS
eve[2].beg.ti_hour=7;	eve[2].beg.ti_min=0;	eve[2].beg.ti_sec=0;
eve[2].beg.ti_hund=0;
eve[2].end.ti_hour=7;	eve[2].end.ti_min=30;	eve[2].end.ti_sec=0;
eve[2].end.ti_hund=0;
#endif
eve[2].loc=7;	eve[2].obnum=2;


#ifdef Linux
eve[3].beg->tm_hour=7;	eve[3].beg->tm_min=30;	eve[3].beg->tm_sec=0;
eve[3].end->tm_hour=8;	eve[3].end->tm_min=0;	eve[3].end->tm_sec=0;
#endif
#ifdef DOS
eve[3].beg.ti_hour=7;	eve[3].beg.ti_min=30;	eve[3].beg.ti_sec=0;
eve[3].beg.ti_hund=0;
eve[3].end.ti_hour=8;	eve[3].end.ti_min=0;	eve[3].end.ti_sec=0;
eve[3].end.ti_hund=0;
#endif
eve[3].loc=7;	eve[3].obnum=3;


#ifdef Linux
eve[4].beg->tm_hour=8;	eve[4].beg->tm_min=0;	eve[4].beg->tm_sec=0;
eve[4].end->tm_hour=8;	eve[4].end->tm_min=30;	eve[4].end->tm_sec=0;
#endif
#ifdef DOS
eve[4].beg.ti_hour=8;	eve[4].beg.ti_min=0;	eve[4].beg.ti_sec=0;
eve[4].beg.ti_hund=0;
eve[4].end.ti_hour=8;	eve[4].end.ti_min=30;	eve[4].end.ti_sec=0;
eve[4].end.ti_hund=0;
#endif
eve[4].loc=7;	eve[4].obnum=4;


#ifdef Linux
eve[5].beg->tm_hour=8;	eve[5].beg->tm_min=30;	eve[5].beg->tm_sec=0;
eve[5].end->tm_hour=9;	eve[5].end->tm_min=0;	eve[5].end->tm_sec=0;
#endif
#ifdef DOS
eve[5].beg.ti_hour=8;	eve[5].beg.ti_min=30;	eve[5].beg.ti_sec=0;
eve[5].beg.ti_hund=0;
eve[5].end.ti_hour=9;	eve[5].end.ti_min=0;	eve[5].end.ti_sec=0;
eve[5].end.ti_hund=0;
#endif
eve[5].loc=7;	eve[5].obnum=5;





#ifdef Linux
eve[6].beg->tm_hour=9;	eve[6].beg->tm_min=0;	eve[6].beg->tm_sec=0;
eve[6].end->tm_hour=9;	eve[6].end->tm_min=30;	eve[6].end->tm_sec=0;
#endif
#ifdef DOS
eve[6].beg.ti_hour=9;	eve[6].beg.ti_min=0;	eve[6].beg.ti_sec=0;
eve[6].beg.ti_hund=0;
eve[6].end.ti_hour=9;	eve[6].end.ti_min=30;	eve[6].end.ti_sec=0;
eve[6].end.ti_hund=0;
#endif
eve[6].loc=7;	eve[6].obnum=6;



#ifdef Linux
eve[7].beg->tm_hour=6;	eve[7].beg->tm_min=10;	eve[7].beg->tm_sec=53;
eve[7].end->tm_hour=9;	eve[7].end->tm_min=30;	eve[7].end->tm_sec=0;
#endif
#ifdef DOS
eve[7].beg.ti_hour=6;	eve[7].beg.ti_min=10;	eve[7].beg.ti_sec=53;
eve[7].beg.ti_hund=0;
eve[7].end.ti_hour=9;	eve[7].end.ti_min=30;	eve[7].end.ti_sec=0;
eve[7].end.ti_hund=0;
#endif
eve[7].loc=5;    eve[7].obnum=15;  /*It's box*/

#ifdef Linux
eve[8].beg->tm_hour=6;	eve[8].beg->tm_min=1;	eve[8].beg->tm_sec=7;
eve[8].end->tm_hour=9;	eve[8].end->tm_min=30;	eve[8].end->tm_sec=0;
#endif
#ifdef DOS
eve[8].beg.ti_hour=6;	eve[8].beg.ti_min=1;	eve[8].beg.ti_sec=7;
eve[8].beg.ti_hund=0;
eve[8].end.ti_hour=9;	eve[8].end.ti_min=30;	eve[8].end.ti_sec=0;
eve[8].end.ti_hund=0;
#endif
eve[8].loc=6;	eve[8].obnum=13;     /*Lee*/

#ifdef Linux
eve[9].beg->tm_hour=6;	eve[9].beg->tm_min=15;	eve[9].beg->tm_sec=4;
eve[9].end->tm_hour=9;	eve[9].end->tm_min=30;	eve[9].end->tm_sec=0;
#endif
#ifdef DOS
eve[9].beg.ti_hour=6;	eve[9].beg.ti_min=15;	eve[9].beg.ti_sec=4;
eve[9].beg.ti_hund=0;
eve[9].end.ti_hour=9;	eve[9].end.ti_min=30;	eve[9].end.ti_sec=0;
eve[9].end.ti_hund=0;
#endif
eve[9].loc=6;	eve[9].obnum=14;     /*Robin*/



#ifdef Linux
eve[10].beg->tm_hour=6;	eve[10].beg->tm_min=38;	eve[10].beg->tm_sec=12;
eve[10].end->tm_hour=9;	eve[10].end->tm_min=30;	eve[10].end->tm_sec=0;
#endif
#ifdef DOS
eve[10].beg.ti_hour=6;	eve[10].beg.ti_min=38;	eve[10].beg.ti_sec=12;
eve[10].beg.ti_hund=0;
eve[10].end.ti_hour=9;	eve[10].end.ti_min=30;	eve[10].end.ti_sec=0;
eve[10].end.ti_hund=0;
#endif
eve[10].loc=6;	eve[10].obnum=29;     /*Tom*/

#ifdef Linux
eve[11].beg->tm_hour=6;	eve[11].beg->tm_min=45;	eve[11].beg->tm_sec=45;
eve[11].end->tm_hour=9;	eve[11].end->tm_min=30;	eve[11].end->tm_sec=0;
#endif
#ifdef DOS
eve[11].beg.ti_hour=6;	eve[11].beg.ti_min=45;	eve[11].beg.ti_sec=45;
eve[11].beg.ti_hund=0;
eve[11].end.ti_hour=9;	eve[11].end.ti_min=30;	eve[11].end.ti_sec=0;
eve[11].end.ti_hund=0;
#endif
eve[11].loc=6;	eve[11].obnum=163;     /*General Smith*/

#ifdef Linux
eve[12].beg->tm_hour=7;	eve[12].beg->tm_min=0;	eve[12].beg->tm_sec=0;
eve[12].end->tm_hour=9;	eve[12].end->tm_min=30;	eve[12].end->tm_sec=0;
#endif
#ifdef DOS
eve[12].beg.ti_hour=7;	eve[12].beg.ti_min=0;	eve[12].beg.ti_sec=0;
eve[12].beg.ti_hund=0;
eve[12].end.ti_hour=9;	eve[12].end.ti_min=30;	eve[12].end.ti_sec=0;
eve[12].end.ti_hund=0;
#endif
eve[12].loc=6;	eve[12].obnum=164;     /*Sagan*/

#ifdef Linux
eve[13].beg->tm_hour=6;	eve[13].beg->tm_min=17;	eve[13].beg->tm_sec=15;
eve[13].end->tm_hour=9;	eve[13].end->tm_min=30;	eve[13].end->tm_sec=0;
#endif
#ifdef DOS
eve[13].beg.ti_hour=7;	eve[13].beg.ti_min=17;	eve[13].beg.ti_sec=15;
eve[13].beg.ti_hund=0;
eve[13].end.ti_hour=9;	eve[13].end.ti_min=30;	eve[13].end.ti_sec=0;
eve[13].end.ti_hund=0;
#endif
eve[13].loc=6;	eve[13].obnum=165;     /* Pat */

#ifdef Linux
eve[14].beg->tm_hour=7;	eve[14].beg->tm_min=36;	eve[14].beg->tm_sec=5;
eve[14].end->tm_hour=9;	eve[14].end->tm_min=30;	eve[14].end->tm_sec=0;
#endif
#ifdef DOS
eve[14].beg.ti_hour=7;	eve[14].beg.ti_min=36;	eve[14].beg.ti_sec=5;
eve[14].beg.ti_hund=0;
eve[14].end.ti_hour=9;	eve[14].end.ti_min=30;	eve[14].end.ti_sec=0;
eve[14].end.ti_hund=0;
#endif
eve[14].loc=6;	eve[14].obnum=166;     /*female phone call*/

#ifdef Linux
eve[15].beg->tm_hour=7;	eve[15].beg->tm_min=52;	eve[15].beg->tm_sec=2;
eve[15].end->tm_hour=9;	eve[15].end->tm_min=30;	eve[15].end->tm_sec=0;
#endif
#ifdef DOS
eve[15].beg.ti_hour=7;	eve[15].beg.ti_min=52;	eve[15].beg.ti_sec=2;
eve[15].beg.ti_hund=0;
eve[15].end.ti_hour=9;	eve[15].end.ti_min=30;	eve[15].end.ti_sec=0;
eve[15].end.ti_hund=0;
#endif
eve[15].loc=6;	eve[15].obnum=167;     /* FBI */

#ifdef Linux
eve[16].beg->tm_hour=8;	eve[16].beg->tm_min=13;	eve[16].beg->tm_sec=16;
eve[16].end->tm_hour=9;	eve[16].end->tm_min=30;	eve[16].end->tm_sec=0;
#endif
#ifdef DOS
eve[16].beg.ti_hour=8;	eve[16].beg.ti_min=13;	eve[16].beg.ti_sec=16;
eve[16].beg.ti_hund=0;
eve[16].end.ti_hour=9;	eve[16].end.ti_min=30;	eve[16].end.ti_sec=0;
eve[16].end.ti_hund=0;
#endif
eve[16].loc=6;	eve[16].obnum=168;     /* Godless */

#ifdef Linux
eve[17].beg->tm_hour=8;	eve[17].beg->tm_min=30;	eve[17].beg->tm_sec=12;
eve[17].end->tm_hour=9;	eve[17].end->tm_min=30;	eve[17].end->tm_sec=0;
#endif
#ifdef DOS
eve[17].beg.ti_hour=8;	eve[17].beg.ti_min=30;	eve[17].beg.ti_sec=12;
eve[17].beg.ti_hund=0;
eve[17].end.ti_hour=9;	eve[17].end.ti_min=30;	eve[17].end.ti_sec=0;
eve[17].end.ti_hund=0;
#endif
eve[17].loc=6;	eve[17].obnum=169;     /* salesperson */

#ifdef Linux
eve[18].beg->tm_hour=8;	eve[18].beg->tm_min=45;	eve[18].beg->tm_sec=45;
eve[18].end->tm_hour=9;	eve[18].end->tm_min=30;	eve[18].end->tm_sec=0;
#endif
#ifdef DOS
eve[18].beg.ti_hour=8;	eve[18].beg.ti_min=45;	eve[18].beg.ti_sec=45;
eve[18].beg.ti_hund=0;
eve[18].end.ti_hour=9;	eve[18].end.ti_min=30;	eve[18].end.ti_sec=0;
eve[18].end.ti_hund=0;
#endif
eve[18].loc=6;	eve[18].obnum=170;     /* General Worth */





a=0;
strcpy(nm,PATH);
#ifdef Linux

strcat(nm,"EventL.bin");

//fprintf(stderr,"%s",nm);

#endif
#ifdef DOS
strcat(nm,"EVENT.BIN");
#endif
if ( (fptr=fopen(nm,"wb"))==NULL)
   {printf("Can't open file %s",nm);  
#ifdef DOS
   getch();
#endif
   }
else
   {
//fprintf(stderr,"got here");
   for (a=0;a<NUMEVE;a++)
#ifdef Linux
     {
       fprintf(stderr,"event %d:%d to %d:%d",eve[a].beg->tm_hour,eve[a].beg->tm_min,eve[a].end->tm_hour,eve[a].end->tm_min);
     fwrite(&eve[a],sizeof(event2020),1,fptr);
     fwrite(&eve[a].beg->tm_hour,4,1,fptr);
     fwrite(&eve[a].beg->tm_min,4,1,fptr);
     fwrite(&eve[a].beg->tm_sec,4,1,fptr);
     fwrite(&eve[a].end->tm_hour,4,1,fptr);
     fwrite(&eve[a].end->tm_min,4,1,fptr);
     fwrite(&eve[a].end->tm_sec,4,1,fptr);
     }
#endif
#ifdef DOS
     fwrite(&eve[a],sizeof(eve[0]),1,fptr);
#endif
   }
fclose(fptr);
}




