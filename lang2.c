/*lang2.c  - language file continued*/

#include "2020.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#ifdef DOS
#include "dos.h"
#include "graphics.h"
#endif
#ifdef Linux
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#endif

#if Linux
struct words
  {
  char nm[20];   /*15*/
  };
#endif
#if DOS
struct words
  {
  char nm[15];
  };
#endif
struct objects
  {
  char name[11];
  int p[4];
  int loc;
  };
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
struct doors		/*door structs*/
  {
  int a[4];	/*x1,y1,x2,y2*/
  int vis;	/*0-yes, 1-no*/
  int next;	/*next room*/
  };
extern struct objects mobj[NUMMOBJ];
extern struct doors door[NUMDOR];
extern struct daction *act1,*act2;   /*pic draw actions-begin link, temp link*/
extern struct daction *act3;   /*temp2 link*/
#ifdef Linux
extern char *PATH;
extern char LPATH[];
//extern char PATH[];
#endif
#ifdef DOS
extern char PATH[256];
#endif
extern struct objects obj[NUMOBJ];
#ifdef Linux
//extern struct words *cword;
extern struct words cword[100];
#endif
#ifdef DOS
extern struct words cword[80];
#endif
extern struct words word[NUMWORD+1];
#ifdef Linux
extern struct tm *mtime;
#endif
#ifdef DOS
extern struct time mtime;
#endif
extern char des[DESC1][DESC2];	/*current location description*/
#ifdef Linux
extern char *strtim;	/*string for time*/
#endif
#ifdef DOS
extern char strtim[17];	/*string for time*/
#endif
extern int numwd;              /*number of words in database*/
extern int wdflag;		/*how many words in an input sentence*/
extern int retsen;		/*return sentence flag*/
extern int slot,channel;	/*tv variables*/
extern int onepic;		/*flag for one picture*/
extern int telpic;		/*telescope picture*/
extern int spec[NUMSPEC];  		/*special flags  (i.e. tv, shower)*/
extern int sent[10];   	/*sentence in numbers*/
extern int ex,ex2;
extern int hx1,hy1,hx2,hy2,rx3,ry3,rx4,ry4,curloc,curloc3;
extern int cash,cash0,inv;
extern int numimg,numimg3,dx,dy,dx2,dy2,mode,mode3,del,page,newloc,lflag;
extern int skin[8];             /*characters attributes*/
extern int cur,chrcur,cash,cash0,moonindx,shipindx,carx[NUMCAR],qflg;
extern unsigned size;    	/*  size of bit image */
#ifdef Linux
extern char *command;	/*string for user input*/
//extern char *it;		/*string for computer*/
extern char it[400];		/*string for computer*/
#endif
#ifdef DOS
extern char command[COMLEN];	/*string for user input*/
extern char it[300];		/*string for computer*/
#endif
extern int cursx,cursy;
extern char cursor[2];
#ifdef Linux
extern char Key;
extern FILE *input,*output;
extern int status;
#endif
#ifdef Linux
extern        Display *xdisplay;
extern        Window xwindow;
extern        int xscreen;
extern        unsigned long xforeground, xbackground;
extern        XEvent xevent;
extern        GC xgc;
extern        Colormap cmap;
extern        XColor color, colorrgb;
extern	Pixmap pixmap[3];
extern XFontStruct *font_info;
extern char *font_name;
extern char **font_path;
extern int font_path_num;
extern unsigned int *klmap;
extern XImage *TitleImage;
extern int ampm;
XImage *scr3;
#endif

int crx,cry,siz,curnum,linv;
char sgnm[10][26],gmnum[2];

gdisc(int c)
{
if (obj[184+c].loc==-2 && curloc==44)
  {
  if (obj[182].loc==-1)
    {
    if (close_enough(161))
      {
      retsen=14;
      obj[184+c].loc=-1;
      }
    else retsen=6;
    }
  else
    retsen= 115;
  }
else
  {
  if (obj[184+c].loc==curloc)
    {
    if (close_enough(184+c))
      {retsen=5;  obj[184+c].loc=-1;}
    else
      retsen=6;
    }
  else retsen=8;
  }
}

ddisc(int c)
{
if (c==0&&curloc==66&&obj[184].loc==-1) {retsen=999; wdflag=-1;
    putout("Lee takes the music of the USA disk and thanks you profusely.");
    obj[184].loc=-2; spec[24]++; retsen=999;}
if (c==2&&curloc==68&&obj[186].loc==-1) {retsen=999; wdflag=-1;
    putout("Professor Godless takes the History of Earth disk and thanks you very much.");
    obj[186].loc=-2;spec[24]++;}
if (c==1&&curloc==73&&obj[185].loc==-1)
	    {
	    if (spec[24]==4)
	       givemed();
	    else
	      {retsen=999; wdflag=-1;
	    putout("Professor Sagan takes the Encylopedia Galactica disk and looks impatiently at you.");
	      obj[185].loc=-2;spec[24]++;}
	    }
if (obj[184+c].loc==-1)  {retsen=5;
	  obj[184+c].p[0]=hx1-5; obj[184+c].p[1]=hy1+HMAN+3;  obj[184+c].loc=curloc;}
else retsen=10;
if (((obj[184].loc==-1&&obj[185].loc==-1)||(obj[185].loc==-1&&obj[186].loc==-1)||
   (obj[184].loc==-1&&obj[186].loc==-1))&&wdflag==1) {retsen=999; putout("Which one?");}
}

reduce()
{
if (wdflag==2 && (sent[1]==389||sent[1]==390) && (sent[2]==391 || sent[2]==392)) wdflag=1;
if (wdflag==2 && sent[1]==15 && sent[2]==388) wdflag=1;  /*salt shaker*/
if (wdflag==2 && sent[1]==16 && sent[2]==388) wdflag=1;  /*peppa shaka*/
if ((sent[0]==71||sent[0]==86) && (sent[1]==276||sent[1]==279)) moveup(1);
					/*talk to -> talk*/
if (sent[1]==305 && sent[2]==365) {wdflag--; sent[1]=365;}
if (sent[1]==422 && sent[2]==424) {wdflag--; sent[1]=424;}
if (sent[1]==340&&sent[2]==425)
   {wdflag=2; sent[2]=426; } /*music usa disc->music disc*/
if (sent[1]==428&&sent[2]==429)
   {wdflag=2; sent[2]=426;}  /*->encyclopedia disc*/
if (sent[1]==430&&(sent[2]==431||sent[2]==422)&&(sent[3]==422||sent[3]==426||
   sent[3]==427||sent[3]==434||sent[3]==435||sent[3]==459||sent[3]==460))
   {wdflag=2; sent[2]=426;}  /*->history disc*/
if (sent[1]==425&&(sent[2]==441||sent[2]==442||sent[2]==368||sent[2]==382))
   {wdflag=1; sent[1]=368;}  /*usa dollar->money*/
if (sent[1]==309 && sent[2]==325)  {wdflag=1;}  /*car door -> car*/
/*if ((sent[0]==132||sent[0]==133)&&(sent[1]==256||sent[1]==270)) moveup(1);*/
if ((sent[0]==66)&&(sent[1]==283)) {sent[0]=4; moveup(1);}
if ((sent[0]==4||sent[0]==130||sent[0]==131)&&(sent[1]==438)&&(sent[2]==276)&&
   (sent[3]==422||sent[3]==423||sent[3]==425||sent[3]==241))
     {sent[0]=130; wdflag=1;}  /*buy ticket*/
if ((sent[1]==456||sent[1]==458)&&sent[2]==344) {sent[1]=344; wdflag--;} /*elev but*/
if (sent[0]==238&&sent[1]==135&&sent[2]==276) {moveup(0);moveup(0);moveup(0);}
if (sent[1]==459||sent[1]==460) sent[1]=434;
if (sent[2]==459||sent[2]==460) sent[2]=434;
}

govt()
{
int c,c0;

c0=0;
for (c=131;c<140;c++)
  {
  if (obj[c].loc==-3) c0++;
  }
if (c0==9&&spec[18]==2) spec[18]=3;
if (spec[18]==0)
  retsen=101;
if (spec[18]==1)
  retsen=125;
if (spec[18]==2)
  retsen=126;
if (spec[18]==3)
  retsen=127;
if (spec[18]==4)
  retsen=128;
}

pack()
{
if (spec[9]==0)
  retsen=101;
if (spec[9]==1)
  retsen=103;
if (spec[9]==2)
  retsen=104;
if (spec[9]==3)
  retsen=105;
}

deliv()
{
int c,d;

d=0;
if (spec[9]==0) retsen=10;
if (spec[9]==1)
  {
  for(c=174;c<179;c++)
    {
    if (obj[c].loc==-1) {d=c; c=179;}
    else retsen=10;
    }
  if (d!=0)
    {
    if (curloc>=12&&curloc<=15)
      {
      for (c=151;c<159;c++)
	{
	if (close_enough(c)) {obj[d].loc=-2;  retsen=110;
			  spec[c-141]++; c=159;}
	else retsen=6;
	}
      }
    else
      retsen=9;
    }
  if (spec[9]==2||spec[9]==3) retsen=10;
  if (spec[10]==1&&spec[11]==1&&spec[12]==1&&spec[14]==1&&spec[16]==1)
     spec[9]=2;
  }
}

mom()
{
retsen=100;
}

moms()
{
if (curloc==41&&obj[171].p[0]==446)
   {obj[171].p[0]=400;  obj[171].p[1]=144;  spec[8]=1; retsen=87;}
else retsen=14;
}

match_words()		/*make sure words are recognized*/
{
int a,b;
int recog;		/*recognize a word*/

#ifdef Linux
char *tword;
char *c;
#endif
#ifdef DOS
char tword[81];
char c[300];
#endif

#ifdef Linux
tword=malloc(81);
c=malloc(301);
#endif

numwd=NUMWORD;
recog=0;
for (a=0;a<=wdflag;a++)
  {
  for (b=0;b<=numwd;b++)
    {
#ifdef Linux

    if (!strcasecmp(cword[a].nm,word[b].nm))
#endif
#ifdef DOS
    if (!stricmp(cword[a].nm,word[b].nm))   /*word match?*/
#endif
      {
      sent[recog]=b;
      recog++;                              /*future symbol*/
      b=numwd+1;
      }
    }   /*end for b*/
  if ((recog!=a+1) && retsen!=999)          /*don't recognize a word*/
    {
    strcpy(tword,"I do not recognize the word '");
    strcat(tword,cword[a].nm);
    strcat(tword,"'.");
    putout(tword);
    a=wdflag+1;   /*get out */
    }
  }  /*end for a*/
if ((recog==wdflag+1)&&(cword[0].nm[0]!=0)) /*we know every word & words>0*/
  {                             /*so now interpret*/
  get_retsen();
  switch(retsen)
    {
    case 0:                     /*end   (quit, exit)*/
      ex2=1;  ex=1;
      putout("Goodbye!");
      break;
    case 1:                     /*time*/
      if (obj[20].loc==-1)
	{
        strcpy(tword,"It is now ");
	strcat(tword,strtim);
	putout(tword);
	}
      else
        putout("I do not know the time.");
      break;
    case 2:
      putout("Ok.");
      start_over();
      break;
    case 3:
      strcpy(c,des[curloc-1]);
      putout(c);
      putob();
      break;
    case 4:			/*action object*/
      strcpy(tword,cword[0].nm);
      strcat(tword," what?");
      putout(tword);
      break;
    case 5:                   /*succesful action*/
      putout("Ok.");
      refresh();
      break;
    case 6:			/*not close enough*/
      putout("You are not close enough.");
      break;
    case 7:                    /*already have object*/
      putout("You already have it.");
      break;
    case 8:			/*don't recognize get-take object*/
      putout("No.");
      break;
    case 9:			/*get something i recognize but isn't here*/
      putout("Not here.");
      break;
    case 10:			/*drop object you don't have*/
      putout("You do not have it.");
      break;
    case 11:			/*the 'X' is 'X'y.*/
      strcpy(tword,"The ");
      strcat(tword,cword[1].nm);
      strcat(tword," is ");
      strcat(tword,cword[1].nm);
      strcat(tword,"y.");
      putout(tword);
      break;
    case 12:			/*inven or inventory*/
      putinv();
      break;
    case 13:			/*open*/
      putout("Open what?");
      break;
    case 14:
      putout("Ok.");
      break;
    case 15:
      putout("They are already open.");
      break;
    case 16:
#ifdef Linux
    if (!strcasecmp(cword[0].nm,"close"))
#endif
#ifdef DOS
      if (!stricmp(cword[0].nm,"close"))
#endif
         putout("Close what?");
      else   putout("Shut what?");
      break;
    case 17:
      putout("They are already closed.");
      break;
    case 18:
#ifdef Linux
    if (!strcasecmp(cword[0].nm,"switch"))
#endif
#ifdef DOS
      if (!stricmp(cword[0].nm,"switch"))
#endif
	putout("Switch what?");
      else
#ifdef Linux
    if (!strcasecmp(cword[0].nm,"turn"))
#endif
#ifdef DOS
	if (!stricmp(cword[0].nm,"turn"))
#endif
          putout("Turn what?");
	else
	  putout("Change what?");
      break;
    case 19:
#ifdef Linux
    if (!strcasecmp(cword[0].nm,"switch"))
#endif
#ifdef DOS
      if (!stricmp(cword[0].nm,"switch"))
#endif
	putout("Switch on what?");
      else
	  putout("Turn on what?");
      break;
    case 20:
      putout("There is nothing unusual about the walls.");
      break;
    case 21:	/*tv already on*/
      putout("It's already on.");
      break;
    case 22:	/*look under rug*/
      putout("There is nothing under the rug.");
      break;
    case 23:   /*look thru telescope*/
      onepic=telpic;
      putout("Ok.");
      refresh();
      break;
    case 24:
      putout("The telescope is very high power.  A button sets the various positions.");
      break;
    case 25:
      strcpy(tword,"There is no ");
      strcat(tword,cword[1].nm);
      strcat(tword," here.");
      putout(tword);
      break;
    case 26:
      if (sent[0]==98)    /*push*/
	putout("Push what?");
      else
	putout("Press what?");
      break;
    case 27:
      putout("You push the button and the telescope moves.");
      break;
    case 28:
      putout("The city is densely populated. Air and ground traffic are visable.");
      break;
    case 29:
      putout("The button controls the telescope setting.");
      break;
    case 30:
      putout("In the distance you see the city. You can make out individual land and air vehicles making there way to and from the city.  The ocean lies between you and the city.");
      break;
    case 31:
      if (obj[3].loc != -2)
	putout("The shades block your view of the window.");
      else
	putout("You have a stunning view of the neighbor's brick wall.");
      break;
    case 32:
      strcpy(tword,"There are no ");
      strcat(tword,cword[1].nm);
      strcat(tword," here.");
      putout(tword);
      break;
    case 33:
      putout("It is already off.");
      break;
    case 34:
      if (spec[0]==1)  /*tv is on*/
	putout(des[TVC+slot*10+channel]);    /*tv description*/
      else
	putout("The television is off.");
      break;
    case 35:
      strcpy(tword,"The ");
      strcat(tword,cword[1].nm);
      strcat(tword," looks normal.");
      putout(tword);
      break;
    case 36:
      putout("Shit is a word that was censored in the 20th century, but not the 21st.  It is usually used to mean feces.");
      break;
    case 37:
      putout("Fuck is a word that was censored in the 20th century, but not the 21st.  It is usually used to mean sexual intercourse.");
      break;
    case 38:      /*look floor*/
      putout("The floor is covered with paper!");
      break;
    case 39:     /*look statue*/
      putout("The statues are from Japan.  They are ceramic soldier humans.");
      break;
    case 40:
      putout("The ocean looks dark and vast.");
      break;
    case 41:     /*look fire*/
      putout("The fireplace is just for show.  There is no chimney for a fire.");
      break;
    case 42:
      putout("Where's the fire?");
      break;
    case 43:     /*look fireplace*/
      putout("The fireplace is just for show.");
      break;
    case 44:			/*the 'X's are 'X'y.*/
      strcpy(tword,"The ");
      strcat(tword,cword[1].nm);
      strcat(tword," are ");
      strncat(tword,cword[1].nm,strlen(cword[1].nm)-1);
      strcat(tword,"y.");
      putout(tword);
      break;
    case 45:
      putout("The ocean is a massive body of water and salt, teaming with life.");
      break;
    case 46:
      putout("Land and air vehicles travel along the air-land highway which goes north and south.");
      break;
    case 47:
      putout("Yes, you.");
      break;
    case 48:
      putout("Yes!");
      break;
    case 49:
      putout("It collects all of the stock certificates for you!");
      refresh();
      break;
    case 50:
      putout("The waterbed looks inviting!");
      break;
    case 51:
      putout("I enjoyed making and playing this game!");
      break;
    case 52:
      strcpy(tword,"Yes, ");
      strcat(tword,cword[0].nm);
      strcat(tword,".");
      putout(tword);
      break;
    case 53:
      putout("Today is February 29, 2020.");
      break;
    case 54:
      putout("You have to urinate.");
      break;
    case 55:
      putout("It is already open.");
      break;
    case 56:
      putout("It is already closed.");
      break;
    case 57:
      putout("The videophone has a screen and a camara.  The other person is shown on your screen, while you are shown on their screen.  There are no messages now.");
      break;
    case 58:
      putout("Lee Adams called and left this message:");
      putout("You must go to the library, get the 'Music of the USA' discs, come to the Moon, and meet me at Moon Port 3 in room A1.");
      break;
    case 59:
      putout("Robin Carlin Dettor called and left this message:");
      putout("You must come to the Moon now!  You will need to sell your stock to get enough money for the ticket.  The band is depending on you dude.");
      break;
    case 60:
     putout("Tom Haught and Helen Flynt called and left this message:");
     putout("You must bring the last seeds of a nearly extinct plant, and the last spores from a nearly extinct mushroom to me. You will need to go to Mom's and give this password: 'underground'. Bring the seeds and spores to me in room B2.");
     break;
    case 61:
     putout("General Smith called and left this message:");
     putout("We are watching your every move, seeing, and hearing your thoughts, so if you try to leave the USA we will see and stop you.");
     break;
    case 62:
     putout("Carl Sagan called and left this message:");
     putout("You must bring the 'Encyclopedia Galactica' discs from the library and meet me at Moon Station 3, in room C2.");
     break;
    case 63:
     putout("Matilda Pupin called and left this message:");
     putout("I am just calling because I saw your video on the videodating web and wondered if you were interested in going to a museum or zoo.  Call me at 1-949-4569-5690.");
     break;
    case 64:
     putout("Andromeda Williams called and left this message:");
     putout("The Government is tracking you, don't worry though the UN is aware of your situation and will protect you, but not the robot.");
     break;
    case 65:
     putout("FBI agent Bill Johnson called and left this message:");
     putout("You must stop playing this game and turn yourself in to the police right now.  If you go outside with the robot you will be arrested.");
     break;
    case 66:
     putout("Professor Godless called and left this message:");
     putout("You must get the 'History of Earth' book discs from the library and bring them to the moon.  I am in Moon Port 3, room A3.  These valuable discs contain the complete history of planet earth, including all of recorded human history.");
     break;
    case 67:
     putout("Foster Heartgate from Heart and Soul Entertainment called and left this message:");
     putout("For a limited time only we are selling new age music that will soothe your heart and soul.  To order a copy of this wonderful music on CD call 1-800-5555-1212 now!.");
     break;
    case 68:
     putout("General Worth called and left this message:");
     putout("If you quit playing this game now I will make you my secretary general for life, at a standard salary of $1,000,000 a year....that's 1 million dollars a year.  If you are interested call me at 1-202-0000-0001.");
     break;
    case 69:
      putout("The desk is made of wood, and has just one drawer.");
      break;
    case 70:
      putout("The drawer is closed.");
      break;
    case 71:
      putout("The translator can only translate english into spanish and spanish into english.  It must be turned on and off.");
      break;
    case 72:
      putout("The drawer is open.");
      break;
    case 73:
      putout("You are on planet Earth, somewhere in Southern California, in the United States of America.");
      break;
    case 74:
      putout("I am here.");
      break;
    case 75:
      putout("I am the narrator of this non-lame game.");
      break;
    case 76:
      putout("You a human made from the sperm of President Huntington.   That is the only data I have.");
      break;
    case 77:
      putout("This is a word used to describe something nearby.");
      break;
    case 78:
      putout("That is a word used to describe something in the distance.");
      break;
    case 79:
      putout("What is a question word.");
      break;
    case 80:
      putout("Not Much.");
      break;
    case 81:
      putout("The Stock Certificates are for various companies around the planet.  They are like money only larger.");
      break;
    case 82:
      putout("You sleep for about 20 minutes.");
      break;
    case 83:
      putout("The cars are all very colorful and pretty, but move very quickly use caution when crossing the street. They all have USA license plates, another change made by the former President.");
      break;
    case 84:
      putout("You look under the rug and find a note.");
      break;
    case 85:
      putout("You look under a statue and find a note.");
      break;
    case 86:
      putout("You look behind a statue and find a note.");
      break;
    case 87:
      putout("Mom moves over to let you into the back room!");
      refresh();
      break;
    case 88:
      putout("Ellen Degeneres:  (1958-    )  Human, hinted that a machine that can see and hear thoughts exists.");
      break;
    case 89:
      putout("Theodore Huntington:  (1969-2020)  Human, cares for truth, science, pleasure.");
      break;
    case 90:
      putout("You do not have to go now.");
      break;
    case 91:
      putout("The link allows you see when you get messages from other humans.");
      break;
    case 92:
      strcpy(tword,"You are not in the ");
      strcat(tword,cword[1].nm);
      strcat(tword,".");
      putout(tword);
      break;
    case 93:
      putout("I am a machine.  I am data entered by Ted Huntington earlier.");
      break;
    case 94:
      putout("You are a human.");
      break;
    case 95:
      putout("Hi.");
      break;
    case 96:
      putout("Bye.");
      break;
    case 97:
      putout("What kind of sounds should you and I make to talk?");
      break;
    case 98:
      putout("It asks: 'what do you want me to do?'.");
      break;
    case 99:
      putout("There is no god, here or anywhere in the universe.  Humans made the word god, and the sound and letter o.");
      break;
    case 100:
      putout("Mom says that since President Huntington made one earth income tax, and eliminated federal, state, sales, social security, and all the other taxes, business has been very good and easy to run.");
      break;
    case 101:
      putout("The clerk says: 'I have a job to give.'");
      break;
    case 102:
      putout("The clerk says: 'Great!  Here are 5 packages. Deliver 1 package to apartments 1,2,3,5 and 7.  Come back here when you are done and I will pay you $75 US dollars.'");
      refresh();
      break;
    case 103:
      putout("The clerk says:  'You no complete the job I gave you yet!'");
      break;
    case 104:
      putout("The clerk says:  'Good work.  Here is $75.00 for a job well done.'");
      obj[181].loc=curloc;
      spec[9]=3;
      refresh();
      break;
    case 105:
      putout("The clerk says:  'You like to be located at package delivery places, do you not?'");
      break;
    case 106:
      putout("The apartments each have a numbered mailbox in front of them.");
      break;
    case 107:
      putout("Your apartment is one of the more roomy apartments in this small neighborhood.");
      break;
    case 108:
      putout("The mailboxes hold packages.");
      break;
    case 109:
      putout("The packages contain items for the people they are addressed to.");
      break;
    case 110:
      putout("You put the package in the mailbox.");
      break;
    case 111:
      putout("The seeds are from a plant that is nearly extinct due to government and public ignorence of its beneficial uses.");
      break;
    case 112:
      putout("The spores are from a mushroom that is nearly extinct due to government and public ignorence of its beneficial uses.");
      break;
    case 113:
      putout("The money is in USA dollars which are equal in value to earth dollars, 1 USA dollar = 1 earth dollar.");
      break;
    case 114:
      putout("Your Earth I.D. card is used to prove you can drive, a passport, birth certificate, social security card, and positive DNA sequence identification card.");
      break;
    case 115:
      putout("You do not have your earth id with you.");
      break;
    case 116:
      putout("You find a $20 USA dollar bill under the rug!");
      refresh();
      break;
    case 117:
      putout("Nothing is there.");
      break;
    case 118:
      putout("You find a $10 USA dollar bill in the couch!");
      refresh();
      break;
    case 119:
      putout("You must have your global id card in order to get disks out of the library.  You can get disks by simply typing 'get <title>'.");
      break;
    case 120:
      putout("To use the machine you insert stock and receive USA dollars in return.");
      break;
    case 121:
      putout("To use the machine you insert your USA dollars and receive Earth dollars in return.");
      break;
    case 122:
      putout("A fart usually just happens, although you can try to stop the gas.");
      break;
    case 123:
      putout("You do not feel like doing that right now.");
      break;
    case 124:
      putout("The key unlocks and starts your car.");
      break;
    case 125:
      putout("The clerk says: 'Great!  All you have to do is pick up the pieces of garbage in the park and put them in the trash can.  I'll pay you $75 US dollars for that.'");
      spec[18]=2;
      break;
    case 126:
      putout("The clerk says: 'You have not finished the job I gave you yet!'");
      break;
    case 127:
      putout("The clerk says: 'Good work!  Here is the $75 US dollars I promised you.'");
      obj[189].loc=curloc;
      spec[18]=4;
      refresh();
      break;
    case 128:
      putout("The clerk says: 'It's really boring around here, but you are welcome to stay if you like.'");
      break;
    case 129:
      putout("You can not carry any more!");
      break;
    case 130:
      putout("The package is huge!");
      break;
    case 131:
      putout("The garbage can holds garbage.");
      break;
    case 132:
      putout("The robot says: 'say follow or stay and I will obey.'");
      break;
    case 133:
      putout("The right to body established by President Huntington means that every body controls what can go into and be taken out of their own body, formally partially controlled by humans in governments.");
      break;
    case 134:
      putout("There is a robot in the large package.");
      break;
    case 135:
      putout("The box is empty.");
      break;
    case 136:
      putout("You do not have a key to unlock the car door.");
      break;
    case 137:
      putout("The key does not unlock the door of this car.");
      break;
    case 138:
      putout("The car door is locked.");
      break;
    case 139:
      putout("The car door is already unlocked.");
      break;
    case 140:
      putout("The car door is already open.");
      break;
    case 141:
      putout("The car door is already closed.");
      break;
    case 142:
      putout("The car door is already locked.");
      break;
    case 143:
      putout("The car door is open.");
      break;
    case 200:
      strcpy(tword,"I recognize the word '");
      tword[strlen(tword)+1]=0;
      strcat(tword,cword[0].nm);
      tword[strlen(tword)+1]=0;
      strcat(tword,"', but do not recognize the sentence.");
      tword[strlen(tword)+1]=0;
      putout(tword);
      break;
    case 999:
       retsen=0;
       break;
    default:
      putout("I recognize all of the words, but not the sentence.");
      break;
    }		/*end switch on retsen*/
  }             /*end if we know every word in sentence*/
}		/*end match words*/

phone()
{
if (curloc==6)
  {
  switch(spec[7])
    {
    case 0:
      retsen=57;
      break;
    case 1:
      retsen=58;
      obj[13].loc=-2;
      refresh();
      break;
    case 2:
      retsen=59;
      obj[14].loc=-2;
      refresh();
      break;
    case 3:
      retsen=60;
      obj[29].loc=-2;
      refresh();
      break;
    case 4:
      retsen=61;
      obj[163].loc=-2;
      refresh();
      break;
    case 5:
      retsen=62;
      obj[164].loc=-2;
      refresh();
      break;
    case 6:
      retsen=63;
      obj[165].loc=-2;
      refresh();
      break;
    case 7:
      retsen=64;
      obj[166].loc=-2;
      refresh();
      break;
    case 8:
      retsen=65;
      obj[167].loc=-2;
      refresh();
      break;
    case 9:
      retsen=66;
      obj[168].loc=-2;
      refresh();
      break;
    case 10:
      retsen=67;
      obj[169].loc=-2;
      refresh();
      break;
    case 11:
      retsen=68;
      obj[170].loc=-2;
      refresh();
      break;
    }
  spec[7]=0;
  if (obj[13].loc==6) spec[7]=1;
  if (obj[14].loc==6) spec[7]=2;
  if (obj[29].loc==6) spec[7]=3;
  if (obj[163].loc==6) spec[7]=4;
  if (obj[164].loc==6) spec[7]=5;
  if (obj[165].loc==6) spec[7]=6;
  if (obj[166].loc==6) spec[7]=7;
  if (obj[167].loc==6) spec[7]=8;
  if (obj[168].loc==6) spec[7]=9;
  if (obj[169].loc==6) spec[7]=10;
  }
else
  retsen=25;
}

cmp_inv()   /*compare inventory items*/
{
if (sent[1]==306) return(7);  /*card*/
if (sent[1]==307) return(8);  /*link*/
if (sent[1]==9) return(9);  /*shower*/
if (sent[1]==10) return(20);  /*watch*/
if (sent[1]==15) return(16);   /*salt*/
if (sent[1]==16) return(17);  /*pepper*/
if (sent[1]==370||sent[1]==389||sent[1]==391) return(100);  /*stock*/
if (sent[1]==371||sent[1]==390||sent[1]==392) return(101);  /*stocks*/
if (sent[1]==386||sent[1]==387) return(131);  /*trash-garbage*/
if (sent[1]==416||sent[1]==87||sent[1]==457) return(0);  /*job*/ /*package-box*/
if (sent[1]==404||sent[1]==405||sent[1]==406||sent[1]==407) return(1);
if (sent[1]==417||sent[1]==420) return(172); /*seed*/
if (sent[1]==418||sent[1]==421) return(173); /*spore*/
if (sent[1]==368||sent[1]==382) return(180);  /*money*/
if (sent[1]==424) return(182);  /*earth id card*/
if (sent[1]==397) return(28);  /*translator*/
if (sent[1]==432||sent[1]==433) return(183);  /*car keys*/
if (sent[1]==426||sent[1]==427||sent[1]==434||sent[1]==435||sent[1]==459||
    sent[1]==460) return(3);
if (sent[1]==426||sent[1]==434||sent[1]==459||sent[1]==460)
   {if (obj[184].loc==-1||obj[184].loc==curloc) return(3);
    else
      {if (obj[185].loc==-1||obj[185].loc==curloc) return(4);
       else
	 {
	 if (obj[186].loc==-1||obj[186].loc==curloc) return(5);
	 }
      }
   }
if (sent[1]==340&&sent[2]==426) return(3);  /*music disk*/
if (sent[1]==428&&sent[2]==426) return(4);  /*encyclopedia disk*/
if (sent[1]==430&&sent[2]==426) return(5);  /*history disk*/
if (sent[1]==438) return(6);  /*ticket to moon*/
if (sent[1]==461||sent[1]==462) return(251);
}

suminv()
{
int f0,a;

inv=0;
if (obj[184].loc==-1) inv++;
if (obj[185].loc==-1) inv++;
if (obj[186].loc==-1) inv++;
f0=0;
if (obj[179].loc==-1||obj[180].loc==-1) f0=1;
for(a=187;a<209;a++)
      {
      if (obj[a].loc==-1) f0=1;
      }
if (f0==1)
  inv++;

f0=0;
for(a=209;a<233;a++)
      {
      if (obj[a].loc==-1) f0=1;
      }
if (f0==1)
  inv++;

f0=0;
if (obj[8].loc==-1) inv++;
if (obj[28].loc==-1) inv++;
if (obj[183].loc==-1) inv++;
if (obj[16].loc==-1) inv++;
if (obj[17].loc==-1) inv++;
if (obj[20].loc==-1) inv++;
if (obj[172].loc==-1) inv++;
if (obj[173].loc==-1) inv++;

f0=0;
for(a=100;a<119;a++)
  if (obj[a].loc==-1) f0++;
if (f0>0)  inv++;

f0=0;
for(a=131;a<140;a++)
  if (obj[a].loc==-1) f0++;
if (f0>0)  inv++;

f0=0;
for(a=174;a<179;a++)
  if (obj[a].loc==-1) f0++;
if (f0>0)  inv++;
if (obj[182].loc==-1) inv++;
}

putinv()
{
int a,f0;
char tinv[300],tmp[5];

linv=0;
strcpy(tinv,"You are carrying:         ");


if (obj[184].loc==-1) {strcat(tinv,"the music of the usa disk "); linv++;}
if (obj[185].loc==-1) {strcat(tinv,"the encyclopedia galactica"); linv++;}
if (obj[186].loc==-1) {strcat(tinv,"the history of earth disk "); linv++;}

f0=0;
if (obj[179].loc==-1||obj[180].loc==-1) f0=1;
for(a=187;a<209;a++)
      {
      if (obj[a].loc==-1) f0=1;
      }
if (f0==1)
  {
#ifdef Linux
    sprintf(tmp,"%d",cash);
#endif
#ifdef DOS
  itoa(cash,tmp,10);
#endif
  strcat(tinv,tmp);
  if (cash<100)
    {
    linv++;
    strcat(tinv," USA Dollars            ");
    }
  else
  {
  if (cash<1000)
    {
    linv++;
    strcat(tinv," USA Dollars           ");
    }
  else
    {
    linv++;
    strcat(tinv," USA Dollars          ");
    }
  }
}

f0=0;
for(a=209;a<233;a++)
      {
      if (obj[a].loc==-1) f0=1;
      }
if (f0==1)
  {
#ifdef Linux
  sprintf(tmp,"%d",cash0);
#endif
#ifdef DOS
  itoa(cash0,tmp,10);
#endif
  strcat(tinv,tmp);
  if (cash0<100)
    {
    linv++;
    strcat(tinv," Earth Dollars          ");
    }
  else
  {
  if (cash0<1000)
    {
    linv++;
    strcat(tinv," Earth Dollars         ");
    }
  else
    {
    linv++;
    strcat(tinv," Earth Dollars        ");
    }
  }
}

f0=0;
if (obj[8].loc==-1) {strcat(tinv,"a portable link           "); linv++;}
if (obj[28].loc==-1) {strcat(tinv,"a translator              "); linv++;}
if (obj[183].loc==-1) {strcat(tinv,"car key                   ");linv++;}
invchk(tinv);
if (obj[16].loc==-1) {strcat(tinv,"a salt shaker             "); linv++;}
invchk(tinv);
if (obj[17].loc==-1) {strcat(tinv,"a pepper shaker           ");linv++;}
invchk(tinv);
if (obj[20].loc==-1) {strcat(tinv,"a watch                   ");linv++;}
invchk(tinv);
if (obj[172].loc==-1) {strcat(tinv,"some plant seeds          ");linv++;}
invchk(tinv);
if (obj[173].loc==-1) {strcat(tinv,"some mushroom spores      ");linv++;}
invchk(tinv);
f0=0;
for(a=100;a<119;a++)
  if (obj[a].loc==-1) f0++;
if (f0==1)  {strcat(tinv,"1 stock certificate       "); linv++;}
if (f0>1)
  {
#ifdef Linux
    sprintf(tmp,"%d",f0);
#endif
#ifdef DOS
  itoa(f0,tmp,10);  
#endif
strcat(tinv,tmp); linv++;
    if (f0<10)  strcat(tinv," stock certificates      ");
    else        strcat(tinv," stock certificates     ");
  }
invchk(tinv);
f0=0;
for(a=131;a<140;a++)
  if (obj[a].loc==-1) f0++;
if (f0==1)  {strcat(tinv,"1 piece of garbage        "); linv++;}
if (f0>1)
  {
#ifdef Linux
    sprintf(tmp,"%d",f0);
#endif
#ifdef DOS
  itoa(f0,tmp,10);  
#endif
strcat(tinv,tmp); linv++;
     strcat(tinv," pieces of garbage       ");
  }
invchk(tinv);
f0=0;
for(a=174;a<179;a++)
  if (obj[a].loc==-1) f0++;
if (f0==1)  {strcat(tinv,"1 package                 "); linv++;}
if (f0>1)
  {
#ifdef Linux
    sprintf(tmp,"%d",f0);
#endif
#ifdef DOS
  itoa(f0,tmp,10);  
#endif
strcat(tinv,tmp); linv++;
     strcat(tinv," packages                ");
  }
invchk(tinv);
if (obj[182].loc==-1) {strcat(tinv,"your earth i.d. card      "); linv++;}
invchk(tinv);
if (obj[251].loc==-1) {strcat(tinv,"tranquilizer drug         "); linv++;}
if (inv==0)  strcat(tinv,"nothing.");
spec[6]=1;
if (linv!=-90) putout(tinv);
spec[6]=0;
}

invchk(char tinv[300])
{
if (linv==9)
  {
  spec[6]=1;
  putout(tinv);
  spec[6]=0;
  strcpy(tinv,"");
  linv=-90;
  }
}

putob()
{
int a,f0;
char c[30];

f0=0;
if (obj[180].loc==curloc||obj[181].loc==curloc)  f0=1;
for(a=187;a<209;a++)
      {
      if (obj[a].loc==curloc) f0=1;
      }
if (f0==1)
  putout("Some money is here.");
f0=0;
if (obj[184].loc==curloc)
  putout("the music of the usa disk is here. ");
if (obj[185].loc==curloc)
  putout("the encyclopedia galactica disk is here. ");
if (obj[186].loc==curloc)
  putout("the history of the planet earth disk is here. ");
if (obj[8].loc==curloc)
 putout("A link is here.");
if (obj[16].loc==curloc)
 putout("a salt shaker is here.");
if (obj[17].loc==curloc)
 putout("a pepper shaker is here.");
if (obj[172].loc==curloc)
 putout("Some seeds are here.");
if (obj[173].loc==curloc)
 putout("Some spores are here.");
if (obj[182].loc==curloc)
 putout("Your earth i.d. card is here.");
if (obj[183].loc==curloc)
 putout("A car key is here.");
if (obj[28].loc==curloc)
 putout("A translator is here.");

f0=0;
for (a=100;a<119;a++)
  if (obj[a].loc==curloc) f0++;
if (f0==1)
 putout("A stock certificate is here.");
if (f0>1)
  putout("Some stock certificates are here.");

f0=0;
for (a=131;a<140;a++)
  if (obj[a].loc==curloc) f0++;
if (f0==1)
 putout("A piece of garbage is here.");
if (f0>1)
  putout("Some pieces of garbage are here.");

f0=0;
for (a=174;a<179;a++)
  if (obj[a].loc==curloc) f0++;
if (f0==1)
 putout("A package is here.");
if (f0>1)
  putout("Some packages are here.");
if(obj[251].loc==curloc) putout("A tranquilizer drug is here.");
}

close_enough(int ob)		/*are you close enough to the object?*/
{
if ( (abs(hx1-obj[ob].p[0])<70||abs(hx1-(obj[ob].p[0]+obj[ob].p[2]))<70) &&
     (abs(hy1+HMAN-obj[ob].p[1])<100||abs(hy1+HMAN-(obj[ob].p[1]+obj[ob].p[3]))<100) &&
      obj[ob].loc==curloc)  /*70*/
  return(1);
else
  return(0);
}   /*end close_enough*/

moveup(int st)		/*move up words in sentence*/
{			/*made for "at", "the", etc*/
int a;

for(a=st;a<wdflag;a++)
   {
   sent[a]=sent[a+1];
   strcpy(cword[a].nm,cword[a+1].nm);
   }
wdflag--;
}	/*end moveup*/

stock()
{
int a;

if (curloc==47)
  {
  if (close_enough(160))
    {
    for(a=100;a<119;a++)
      if (obj[a].loc==-1)
	{obj[a].loc=-3;
	spec[19]++;
	obj[a+90].loc=-1;
	cash=cash+40;
	retsen=14;
	}
    if (retsen==0) retsen=10;
    }
  else retsen=6;
  }
else
  retsen=9;
}

cashex()
{
int a;

if (curloc==48)
  {
  if (close_enough(162))
    {
    if (obj[180].loc==-1) {obj[209].loc=-1; obj[180].loc=-2; cash=cash-100;
				cash0=cash0+100; retsen=14;}
    if (obj[181].loc==-1) {obj[210].loc=-1; obj[181].loc=-2; cash=cash-75;
				cash0=cash0+75; retsen=14;}
    if (obj[187].loc==-1) {obj[211].loc=-1; obj[187].loc=-2; cash=cash-20;
				cash0=cash0+20; retsen=14;}
    if (obj[188].loc==-1) {obj[212].loc=-1; obj[188].loc=-2; cash=cash-10;
				cash0=cash0+10; retsen=14;}
    if (obj[189].loc==-1) {obj[213].loc=-1; obj[189].loc=-2; cash=cash-75;
				cash0=cash0+75; retsen=14;}
    for(a=190;a<209;a++)
      if (obj[a].loc==-1)
	{obj[a].loc=-2;
	obj[a+24].loc=-1;
	cash=cash-40;  cash0=cash0+40;
	retsen=14;
	}
    if (retsen==0) retsen=10;
    }
  else retsen=6;
  }
else
  retsen=9;
}

follow()
{
if (curloc3==curloc && obj[15].loc==5)
  {
  if (spec[20]>=1)
    {
    spec[20]=2;
    retsen=14;
    }
  }
else
  retsen=9;
}

stay()
{
if (curloc3==curloc && obj[15].loc==5)
  {
  if (spec[20]>=1)
    {
    spec[20]=1;
    retsen=14;
    }
  }
else
  retsen=9;
}

unlk()
{
int a;
int f0;

f0=0;
for (a=119;a<=129;a++)
  {if (close_enough(a)) f0=1;}
if (close_enough(130)) f0=2;
if (obj[183].loc !=-1) f0=3;
if ((curloc<32 || curloc>34)&&curloc!=56) f0=4;
switch(f0)
  {
  case 0:
    retsen=6;
    break;
  case 1:
    retsen=137;
    break;
  case 2:
    if (spec[21]==1) retsen=139;
    if (spec[21]==2) retsen=143;
    if (spec[21]==0)
      {
      retsen=14;
      spec[21]=1;
      }
    break;
  case 3:
    retsen=136;
    break;
  case 4:
    retsen=9;
    break;
  }
}

lk()
{
int a;
int f0;

f0=0;
for (a=119;a<=129;a++)
  {if (close_enough(a)) f0=1;}
if (close_enough(130)||spec[1]==3) f0=2;
if (obj[183].loc !=-1) f0=3;
if ((curloc<32 || curloc>34)&&curloc!=56) f0=4;
switch(f0)
  {
  case 0:
    retsen=6;
    break;
  case 1:
    retsen=137;
    break;
  case 2:
    if (spec[21]==0) retsen=142;
    if (spec[21]==1)
      {
      retsen=14;
      spec[21]=0;
      }
    if (spec[22]==2)  retsen=143;
    break;
  case 3:
    retsen=136;
    break;
  case 4:
    retsen=9;
    break;
  }
}

opcr()
{
int a;
int f0;

f0=0;
for (a=119;a<=129;a++)
  {if (close_enough(a)) f0=1;}
if (close_enough(130)) f0=2;
if ((curloc<32 || curloc>34) && curloc!=56) f0=3;
switch(f0)
  {
  case 0:
    retsen=6;
    break;
  case 1:
    retsen=137;
    break;
  case 2:
    if (spec[21]==2) retsen=140;
    if (spec[21]==0) retsen=138;
    if (spec[21]==1) {retsen=5; spec[21]=2; obj[234].loc=curloc;
		    if (curloc==56) {obj[234].p[0]=384; obj[234].p[1]=216;}}
    break;
  case 3:
    retsen=9;
    break;
  }
}

clcr()
{
int a;
int f0;

f0=0;
for (a=119;a<=129;a++)
  {if (close_enough(a)) f0=1;}
if (close_enough(130)) f0=2;
if ((curloc<32 || curloc>34)&&curloc!=56) f0=3;
switch(f0)
  {
  case 0:
    retsen=6;
    break;
  case 1:
    retsen=137;
    break;
  case 2:
    if (spec[21]==0) retsen=138;
    if (spec[21]==1) retsen=141;
    if (spec[21]==2) {retsen=5; spec[21]=1; obj[234].loc=-2;}
    break;
  case 3:
    retsen=9;
    break;
  }
}

gocar()
{
if (curloc==32||curloc==56)
  {
  if (close_enough(130))
  {
  retsen=999;
  if (obj[234].loc==32||obj[234].loc==56)
    {
    if (curloc3==32||curloc3==56)
      {
      putout("You and It get into the car.");
      if (curloc==32)
	putout("It says we must drive south.");
      dx=dy=dx2=dy2=0;
      }
    else
      {
      putout("You get in the car.");
      }
    spec[1]=3;
    refresh();
    }
  else
    putout("The car door is not open.");
  }
  else
    retsen=6;
  }
else
 retsen=9;
}

exitcar()
{
if (curloc==32||curloc==56)
  {
  retsen=999;
  if (obj[234].loc==32||obj[234].loc==56)
    {
    if (curloc3==32||curloc3==56)
      putout("You and It get out of the car.");
    else
      putout("You get out of the car.");
    spec[1]=0;
/*    setactivepage(!page);            */
    if (curloc==56) spec[22]=1; /*set coords*/
    refresh();
    }
  else
    putout("The car door is not open.");
  }
else
 {
 retsen=9;
 }
}

savmenu()
{
FILE *fptr;
char sgstr[300],tmpstr[255];
int b;

/*get current save game names*/
b=0;
strcpy(sgstr,"");

strcpy(tmpstr,PATH);
strcat(tmpstr,LPATH);
#ifdef Linux
strcat(tmpstr,"Sav.gam");
if ((fptr=fopen(tmpstr,"rb"))==0)
  {
  fprintf(stderr,"Error trying to open file Sav.gam");
  }
#endif
#ifdef DOS
strcat(tmpstr,"sav.gam");
if ((fptr=fopen(tmpstr,"rb"))==0)
{
 printf("Can't open file sav.gam");
}
#endif  
else
  {
#ifdef Linux
  while (fread(&sgnm[b],sizeof(sgnm[0]),1,fptr) ==1)
    {sgnm[b][26]=0; strcat(sgstr,sgnm[b]); b++;}
#endif
#ifdef DOS
  while (fread(&sgnm[b],sizeof(sgnm[0]),1,fptr) ==1)
    {sgnm[b][26]=0; strcat(sgstr,sgnm[b]); b++;}
#endif
  }
fclose(fptr);
spec[6]=3;
putout(sgstr);
spec[6]=0;

}

resmenu()
{
FILE *fptr;
char sgstr[300],tmpstr[255];
int b;

/*get current save game names*/
b=0;
strcpy(sgstr,"");
strcpy(tmpstr,PATH);
strcat(tmpstr,LPATH);
#ifdef Linux
strcat(tmpstr,"Sav.gam");
if ((fptr=fopen(tmpstr,"rb"))==0)
  fprintf(stderr,"Error trying to open file %s",tmpstr);
#endif
#ifdef DOS
strcat(tmpstr,"sav.gam");
if ((fptr=fopen(tmpstr,"rb"))==0)
  printf("Can't open file sav.gam");
#endif
else
  {
//#ifdef DOS
  while (fread(&sgnm[b],sizeof(sgnm[0]),1,fptr) ==1)
    {sgnm[b][26]=0; strcat(sgstr,sgnm[b]); b++;}
//#endif
  }
fclose(fptr);
spec[6]=4;
putout(sgstr);
spec[6]=0;
}
savscrn()
{
char ch1,ch2;
int qt,mcur,fact,bcry;

#ifdef Linux
curnum=0;  mcur=8;  fact=20; crx=104; cry=62; siz=430; bcry=62;
#endif
#ifdef DOS
curnum=0;  mcur=8;  fact=19; crx=104; cry=62; siz=425; bcry=62;
#endif
qt=0;
wbox();
while(qt!=1)
 {
#ifdef Linux
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
     //status=1;
     break;
   case KeyPress:
     status=1;
     ch1=XLookupKeysym(&xevent.xkey,0);
     break;
    }  //end switch
   }  //end while

#endif
#ifdef DOS
 ch1=getch();
 if (ch1==0)
  {
  ch2=getch();                                      /*up*/
#endif
#ifdef Linux
	if (ch1==82)  
#endif
#ifdef DOS
  if (ch2==72)  
#endif
{  if (curnum==0)  {bbox(); curnum=mcur;
					cry=cry+mcur*fact;wbox();}
		   else {bbox(); curnum--; cry=cry-fact; wbox();}}
  else
    {                                             /*down*/
#ifdef Linux
	if (ch1==84)  
#endif
#ifdef DOS
    if (ch2==80) 
#endif
      {if (curnum==mcur) {bbox(); curnum=0;
						cry=bcry; wbox();}
		   else {bbox(); curnum++; cry=cry+fact; wbox();}}
    }
#ifdef DOS
  }
 else
  {
#endif
  if (ch1==13)  
   {  
       doname();
		   qt=1; }
  if (ch1==27) 
       {
        qt=1;
        }
#ifdef DOS
  }
#endif
 } /*end while*/
}

doname()
{
int qt,oldcx,oldcy;
char ch,key[2],comd[26];

  qt=0;  oldcx=cursx;  oldcy=cursy;
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0], xgc, crx+54,cry-5,siz-115,16);
ShowScreenF();
#endif
#ifdef DOS
  setcolor(15);
  setfillstyle(SOLID_FILL,15);
  bar(crx,cry,crx+siz,cry+19);
/*  settextstyle(0,0,2);*/
  setcolor(0);
  setfillstyle(SOLID_FILL,0);
#endif
  cursx=crx+5;  cursy=cry+2;
  draw_cursor2();
  strcpy(comd,"");
  while (qt!=1)
  {
#ifdef Linux
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
     //status=1;
     break;
   case KeyPress:
     status=1;
     ch=XLookupKeysym(&xevent.xkey,0);
     key[0]=ch;
     key[1]=0;
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
	if (cursx>111)
	  {
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0], xgc, cursx+50-16,cursy-5,32,16);
//ShowScreenF();
#endif
#ifdef DOS
	  setfillstyle(SOLID_FILL,15);
	  bar(cursx-16,cursy,cursx+16,cursy+16);
#endif
	  comd[strlen(comd)-1]=0;
          cursx=cursx-16;
	  draw_cursor2();
	  }
	break;
      case 13:			/* '<cr>'  carriage return*/
	strcpy(sgnm[curnum],comd);
/*	sgnm[curnum][26]=0;*/
	padit();
	gmnum[0]=49+curnum; gmnum[1]=0; savg(gmnum); qt=1;
	wrsgnm();
	break;
      case 27:
	  savmenu(); qt=1;
	break;
      default:		/*alpha or other symbol*/
	if (cursx<495)     /*480-500*/
	  {
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0], xgc, cursx+50,cursy-5,16,16);
XSetForeground (xdisplay, xgc, 0x0);
XDrawString(xdisplay,pixmap[0],xgc,cursx+50,cursy-1+(font_info->ascent+font_info->descent)/2,key,1);

//ShowScreenF();
#endif
#ifdef DOS
	  setcolor(15);
	  setfillstyle(SOLID_FILL,15);
	  settextstyle(0,0,2);
	  bar(cursx,cursy,cursx+16,cursy+16);  /*whiteout cursor*/
	  setcolor(0);
	  outtextxy(cursx,cursy,key);
#endif
	  cursx=cursx+16;
	  strcat(comd,key);
	  draw_cursor2();
	  }
	break;
      }                            /*end switch*/
   }                           /*end while*/
   cursx=oldcx;  cursy=oldcy;
}

padit()
{ int b;

if (strlen(sgnm[curnum])<26)
  {
  for (b=strlen(sgnm[curnum]);b<26;b++)
    sgnm[curnum][b]=32;
/*  sgnm[curnum][26]=0;*/
  }
}

draw_cursor2()
{
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0], xgc, cursx+50,cursy-5,16,16);
ShowScreenF();
#endif
#ifdef DOS
setcolor(0);
outtextxy(cursx,cursy,cursor);
#endif
}

wrsgnm()
{
FILE *fptr;
int b;
char tmpstr[255];

strcpy(tmpstr,PATH);
#ifdef Linux
strcat(tmpstr,LPATH);
strcat(tmpstr,"Sav.gam");
fptr=fopen(tmpstr,"wb");
#endif
#ifdef DOS
strcat(tmpstr,"sav.gam");
fptr=fopen(tmpstr,"wb");
#endif
for (b=0;b<9;b++)
  fwrite(&sgnm[b],sizeof(sgnm[0]),1,fptr);
fclose(fptr);
}

resscrn()
{
char ch1,ch2;
int qt,curnum,mcur,fact,bcry;

#ifdef Linux
curnum=0;  mcur=8;  fact=20; crx=104; cry=62; siz=425; bcry=62;
#endif
#ifdef DOS
curnum=0;  mcur=8;  fact=19; crx=104; cry=62; siz=425; bcry=62;
#endif
qt=0;
wbox();
while(qt!=1)
 {
#ifdef Linux
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
     //status=1;
     break;
   case KeyPress:
     status=1;
     ch1=XLookupKeysym(&xevent.xkey,0);
     ch2=0;
     break;
    }  //end switch
   }  //end while
 //  if (1) 
 //    {
#endif
#ifdef DOS
 ch1=getch();
 if (ch1==0)
  {
  ch2=getch();                                      /*up*/
#endif
#ifdef Linux
	if (ch1==82)  
#endif
#ifdef DOS
  if (ch2==72)  
#endif
{  if (curnum==0)  {bbox(); curnum=mcur;
					cry=cry+mcur*fact;wbox();}
		   else {bbox(); curnum--; cry=cry-fact; wbox();}}
  else
    {                                             /*down*/
#ifdef Linux
	if (ch1==84)  
#endif
#ifdef DOS
    if (ch2==80) 
#endif
{if (curnum==mcur) {bbox(); curnum=0;
						cry=bcry; wbox();}
		   else {bbox(); curnum++; cry=cry+fact; wbox();}}
    }
#ifdef DOS
  }
 else
  {
#endif
  if (ch1==13)  { gmnum[0]=49+curnum;gmnum[1]=0;
		  if (strncmp(sgnm[curnum],"Save game name",14))
		     {resg(gmnum);  qt=1; }
		}
  if (ch1==27) qt=1;
#ifdef DOS
  }
#endif
 } /*end while*/
}


bbox()
{
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x00ffffff);
XDrawRectangle(xdisplay, pixmap[0],xgc,crx+53,cry-7,siz-115,20);
ShowScreenF();
#endif
#ifdef DOS
setcolor(15);
rectangle(crx,cry,crx+siz,cry+19);
#endif
}

wbox()
{
#ifdef Linux
XSetForeground (xdisplay, xgc, 0x006f307f);
XDrawRectangle(xdisplay, pixmap[0],xgc,crx+53,cry-7,siz-115,20);
ShowScreenF();
#endif
#ifdef DOS
setcolor(5);
rectangle(crx,cry,crx+siz,cry+19);
#endif
}

savg(char sgnum[2])
{
FILE *fptr;
char savgam[255],syslin[255],ch;


#ifdef Linux
sgnum[1]=0;
#endif
strcpy(savgam,PATH);
strcat(savgam,sgnum);
#ifdef Linux
strcat(savgam,".sav");
#endif
#ifdef DOS
strcat(savgam,".SAV");    		/*make save file*/
#endif
if ( (fptr=fopen(savgam,"wb"))==NULL)
     {printf("Can't open file %s",savgam);  
#ifdef Linux
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
     //status=1;
     break;
   case KeyPress:
     status=1;
     ch=XLookupKeysym(&xevent.xkey,0);
     break;
    }  //end switch
   }  //end while


#endif
#ifdef DOS
  ch=getch();
  if(ch==0)  getch();
#endif

     }
  else
     {
     fwrite(&hx1,sizeof(hx1),1,fptr);        fwrite(&hx2,sizeof(hx2),1,fptr);
     fwrite(&rx3,sizeof(rx3),1,fptr);        fwrite(&rx4,sizeof(rx4),1,fptr);
     fwrite(&hy1,sizeof(hy1),1,fptr);        fwrite(&hy2,sizeof(hy2),1,fptr);
     fwrite(&ry3,sizeof(ry3),1,fptr);        fwrite(&ry4,sizeof(ry4),1,fptr);
     fwrite(&curloc,sizeof(curloc),1,fptr);
     fwrite(&curloc3,sizeof(curloc3),1,fptr);
     fwrite(&inv,sizeof(inv),1,fptr);
     fwrite(&del,sizeof(del),1,fptr);
     fwrite(&numimg,sizeof(numimg),1,fptr);
     fwrite(&numimg3,sizeof(numimg3),1,fptr);
     fwrite(&dx,sizeof(dx),1,fptr);
     fwrite(&dy,sizeof(dy),1,fptr);
     fwrite(&dx2,sizeof(dx2),1,fptr);
     fwrite(&dy2,sizeof(dy2),1,fptr);
     fwrite(&mode,sizeof(mode),1,fptr);
     fwrite(&mode3,sizeof(mode3),1,fptr);
     fwrite(&cash,sizeof(cash),1,fptr);
     fwrite(&cash0,sizeof(cash0),1,fptr);
     fwrite(&chrcur,sizeof(chrcur),1,fptr);
     fwrite(&mtime,sizeof(mtime),1,fptr);
     fwrite(&spec,sizeof(spec[0]),NUMSPEC,fptr);
     fwrite(&skin,sizeof(skin[0]),8,fptr);
     fwrite(&obj,sizeof(obj[0]),NUMOBJ,fptr);
     }
  fclose(fptr);
#ifdef Linux
  strcpy(syslin,"cp ");
  strcat(syslin,PATH);
  strcat(syslin,LPATH);
  strcat(syslin,"Def.pic ");
  strcat(syslin,PATH);
  strcat(syslin,LPATH);
  strcat(syslin,"8");
#endif
#ifdef DOS
  strcpy(syslin,"copy");
  strcat(syslin,PATH);
  strcat(syslin,LPATH);
  strcat(syslin,"def.pic ");
  strcat(syslin,PATH);
  strcat(syslin,LPATH);
  strcat(syslin,"8");
#endif
  strcat(syslin,sgnum);
  strcat(syslin,".pic > ");
#ifdef Linux
  strcat(syslin,PATH);
  strcat(syslin,LPATH);
  strcat(syslin,"out.out");
#endif
#ifdef DOS
  strcat(syslin,PATH);
  strcat(syslin,LPATH);
  strcat(syslin,"out.out");
#endif
  system(syslin);
}


resg(char rgnum[2])
{
FILE *fptr;
char resgam[255],syslin[255],ch;

#ifdef Linux
  strcpy(syslin,"cp ");
  strcat(syslin,PATH);
  strcat(syslin,LPATH);
  strcat(syslin,"8");
#endif
#ifdef DOS
  strcpy(syslin,"copy ");
  strcat(syslin,PATH);
  strcat(syslin,"8");
#endif
strcat(syslin,rgnum);
#ifdef Linux
strcat(syslin,".pic ");
strcat(syslin,PATH);
strcat(syslin,LPATH);
strcat(syslin,"Def.pic > ");
strcat(syslin,PATH);
strcat(syslin,LPATH);
strcat(syslin,"out.out");
#endif
#ifdef DOS
strcat(syslin,".pic ");
strcat(syslin,PATH);
strcat(syslin,"def.pic > ");
strcat(syslin,PATH);
strcat(syslin,"out.out");
#endif
system(syslin);
strcpy(resgam,PATH);
#ifdef Linux
strcat(resgam,LPATH);
#endif
strcat(resgam,rgnum);
#ifdef Linux
strcat(resgam,".sav");
#endif
#ifdef DOS
strcat(resgam,".SAV");    		/*make save file*/
#endif
if ( (fptr=fopen(resgam,"rb"))==NULL)
   {
#ifdef DOS
printf("Error opening file %s",resgam); 
#endif
#ifdef Linux
fprintf(stderr,"No file %s\n",resgam); 
//status=0;
//  while (status!=1)
//  {
   /* wait for next event */
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
  //   status=1;
     ch=XLookupKeysym(&xevent.xkey,0);
     break;
    }  //end switch
//   }  //end while


#endif
#ifdef DOS
  ch=getch();
  if(ch==0)  getch();
#endif
    }
else
   {
   fread(&hx1,sizeof(hx1),1,fptr);     fread(&hx2,sizeof(hx2),1,fptr);
   fread(&rx3,sizeof(rx3),1,fptr);     fread(&rx4,sizeof(rx4),1,fptr);
   fread(&hy1,sizeof(hy1),1,fptr);     fread(&hy2,sizeof(hy2),1,fptr);
   fread(&ry3,sizeof(ry3),1,fptr);     fread(&ry4,sizeof(ry4),1,fptr);
   fread(&curloc,sizeof(curloc),1,fptr);
   fread(&curloc3,sizeof(curloc3),1,fptr);
   fread(&inv,sizeof(inv),1,fptr);
   fread(&del,sizeof(del),1,fptr);
   fread(&numimg,sizeof(numimg),1,fptr);
   fread(&numimg3,sizeof(numimg3),1,fptr);
   fread(&dx,sizeof(dx),1,fptr);
   fread(&dy,sizeof(dy),1,fptr);
   fread(&dx2,sizeof(dx2),1,fptr);
   fread(&dy2,sizeof(dy2),1,fptr);
   fread(&mode,sizeof(mode),1,fptr);
   fread(&mode3,sizeof(mode3),1,fptr);
   fread(&cash,sizeof(cash),1,fptr);
   fread(&cash0,sizeof(cash0),1,fptr);
   fread(&chrcur,sizeof(chrcur),1,fptr);
   fread(&mtime,sizeof(mtime),1,fptr);
   fread(&spec,sizeof(spec[0]),NUMSPEC,fptr);
   fread(&skin,sizeof(skin[0]),8,fptr);
   fread(&obj,sizeof(obj[0]),NUMOBJ,fptr);
   }
fclose(fptr);
/*cur=chrcur;*/

newloc=curloc;
curloc=80+rgnum[0]-48;  /*80 is save game character*/
  lflag=5;
  load_file();
  lflag=0;
#ifdef Linux

  XDestroyImage(TitleImage);
  TitleImage= XGetImage(xdisplay,pixmap[0],0,0,640,300,AllPlanes,ZPixmap);

XSetForeground (xdisplay, xgc, 0x00ffffff);
XFillRectangle (xdisplay, pixmap[0],xgc,0,0,640,32);
XSetForeground (xdisplay, xgc, 0x0);
XFillRectangle (xdisplay, pixmap[0],xgc,0,32,640,318);

#endif
#ifdef DOS
  setactivepage(!page);
  setfillstyle(1, 15);
  bar(0,0,640,32);   /*white top */
#endif
  draw_it();
  getman();
#ifdef Linux
  XPutImage(xdisplay,pixmap[0],xgc,TitleImage,0,0,0,0,640,300);  
#endif
#ifdef DOS
  setactivepage(page);
#endif
 /* alloc_lines();*/
curloc=newloc;
dx=dy=dx2=dy2=0;
refresh();
}

bordr()
{
int b;

if (obj[182].loc==-1)
  { 
  putout("You show the United Nations guard your earth id and are allowed to pass.");
    for (b=1;b<=3600;b++)    /*3600 sec= 1 hour*/
	  { 
#ifdef Linux
	  mtime->tm_sec++;
#endif
#ifdef DOS
	  mtime.ti_sec++; 
#endif
	   timr(); check_eve();}
	   putout("One hour passes."); 
#ifdef DOS
           mtime.ti_hund=0;
#endif
   newloc=56; curloc=56;  curloc3=56;  obj[130].loc=56;
   refresh();
  }
else
  {
  putout("You are not carrying any form of identification, and the delay causes you to be captured.  Nice going.");
  dead();
  }
}

gotomoon()
{
int b;

if (moonindx==5)
  {       for (b=1;b<=7200;b++)    /*7200 sec= 2 hours*/
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
#ifdef DOS
	  mtime.ti_sec++; 
#endif
timr(); check_eve();}
	   putout("Two hours pass."); 
#ifdef DOS
           mtime.ti_hund=0;
#endif
  putout("You are on the moon."); newloc=62;  hx1=325; rx3=345; hy1=ry3=225;refresh();}
else
  {
  if (moonindx==0)  {obj[240].loc=60; refresh();}
  else
    {
    obj[239+moonindx].loc=-2;
    obj[240+moonindx].loc=60;
    refresh();
    }
  }
}

gotoship()
{
if (shipindx==5)
  {putout("You have docked with the General's ship."); newloc=76;  hx1=rx3=325; hy1=ry3=225;refresh();}
else
  {
  if (shipindx==0)  {obj[246].loc=60; refresh();}
  else
    {
    obj[245+shipindx].loc=-2;
    obj[246+shipindx].loc=75;
    refresh();
    }
  }
}

elev()
{
if (hy1>160) retsen=6;
else
  {
  door[0].vis=1; door[1].vis=1; door[2].vis=1;
  if (hx1<260) {retsen=999;
	       if (obj[245].loc==62&&obj[245].p[0]<260)
		 {
		 putout("The left elevator door closes.");
		 door[0].vis=1;   obj[245].loc=-2;
		 spec[23]=2;
		 refresh();
		 }
	       else
		 {
		 putout("The left elevator door opens.");
		 door[0].vis=0; obj[245].loc=62; obj[245].p[0]=182;
		 spec[23]=3;
		 refresh();}
		 }
  if (hx1>=260&&hx1<=365)
		{retsen=999;
	       if (obj[235].loc==62&&obj[245].p[0]>=260&&obj[245].p[0]<=365)
		 {
		 putout("The middle elevator door closes.");
		 door[1].vis=1;   obj[245].loc=-2;
		 spec[23]=2;
		 refresh();
		 }
	       else
		 {putout("The middle elevator door opens.");
	       door[1].vis=0; obj[245].p[0]=285; obj[245].loc=62;
               spec[23]=4;
	       refresh();}
	       }
  if (hx1>365)
	       {retsen=999;
	       if (obj[245].loc==62&&obj[245].p[0]>365)
		 {
		 putout("The right elevator door closes.");
		 door[2].vis=1;   obj[245].loc=-2;
		 spec[23]=2;
		 refresh();
		 }
	       else
		 {
	       putout("The right elevator door opens.");
	       door[2].vis=0; obj[245].p[0]=390; obj[245].loc=62;
               spec[23]=5;
	       refresh();}
	       }
  }
}

inelev()
{
if (hy1>160) retsen=6;
else
  {
  if (sent[2]<470||sent[2]>473)  putout("There is no such button here!");
  else
  {   putout("Ok.");  retsen=999;
  obj[245].p[0]=288; obj[245].p[1]=36;
  if (obj[245].loc==63)  obj[245].loc=0;
  else {if (curloc==63) obj[245].loc=63;}
  if (obj[245].loc==64)  obj[245].loc=0;
  else  {if (curloc==64) obj[245].loc=64;}
  if (obj[245].loc==65)  obj[245].loc=0;
  else  {if (curloc==65) obj[245].loc=65;}
  if (spec[23]==7||spec[23]==8||spec[23]==9) spec[23]=3;
  if (spec[23]==11||spec[23]==12||spec[23]==13) spec[23]=4;
    if (spec[23]==15||spec[23]==16||spec[23]==17) spec[23]=5;
  switch(sent[2])
    {
    case 470: /*0*/
       if (spec[23]==3)  spec[23]=6;
       if (spec[23]==4)  spec[23]=10;
       if (spec[23]==5)  spec[23]=14;
       break;
    case 471:
       if (spec[23]==3)  spec[23]=7;
       if (spec[23]==4)  spec[23]=11;
       if (spec[23]==5)  spec[23]=15;
      break;
    case 472:
       if (spec[23]==3)  spec[23]=8;
       if (spec[23]==4)  spec[23]=12;
       if (spec[23]==5)  spec[23]=16;
      break;
    case 473:
       if (spec[23]==3)  spec[23]=9;
       if (spec[23]==4)  spec[23]=13;
       if (spec[23]==5)  spec[23]=17;
      break;
      }
    } /*end else*/
  refresh();
  }
}

putout(char abc[300])		/*write out nicely to screen*/
{
#ifdef Linux
#define W 12
#define H 20
#endif
#ifdef DOS
#define W 16
#define H 19
#endif

int ll;
int len,tx,ty,a,numlin,Lns,c,d,e,f,opt,lwl;
#ifdef DOS
unsigned *scr3;
#endif
char ch,ch2;
#ifdef Linux
//char *lin,*lin3,*lin4,*lin5;
//char *para,*par2,*scom;
char lin[100],lin3[100],lin4[100],lin5[100];       /*270*/
char para[300],par2[300],scom[COMLEN];
#endif
#ifdef DOS
char lin[100],lin3[100],lin4[100],lin5[100];       /*270*/
//char lin[26+1],lin3[26+1],lin4[26+1],lin5[26+1];       /*270*/
char para[300],par2[300],scom[COMLEN];
#endif

#ifdef Linux
/*lin=malloc(27);
lin3=malloc(27);
lin4=malloc(27);
lin5=malloc(27);
para=malloc(301);
par2=malloc(301);
scom=malloc(COMLEN);*/
#endif

ll=26;
if (spec[6]==2) ll=12;
para[0]=0;  /*paragraph*/
lin[0]=0;  /*single line*/
lin5[0]=0;  /*single line*/
lin4[0]=0;  /*single line*/
lin3[0]=0;
d=0; c=-1;  opt=0;


strcpy(par2,it);  /*save it*/
strcpy(scom,command);  /*save command*/
strcpy(it,abc);
if (spec[6]>0) strcpy(para,abc);

if (spec[6]==0)
{


make_words();

for (a=0;a<=wdflag;a++)
  {
  if ((d+strlen(cword[a].nm))>ll)
    {             /*would be too long */
    if (a>0) lwl=strlen(cword[a-1].nm);
    lin3[d]=0; d--;
    c=ll-d;   /*number of extra spaces needed in the line*/
    d=0;  /*start on 1st char*/
    while(c>0)
      {
      if (lin3[d]==32 && lin3[d+1]!=32)
	  {
	    strncpy(lin4,lin3,d);
	    lin4[d]=0;
	    strcpy(lin5,"");
	    f=0;
	    for(e=d;e<ll;e++)
	      {
	      lin5[f]=lin3[e];
	      f++;
	      }
	    lin5[f]=0;
	    strcat(lin4," ");
	    d=d+2;
	    strcat(lin4,lin5);
	    strcpy(lin3,lin4);
	    c--;
	  }
      else
	d++;
      if (d> (strlen(lin3)-lwl)) d=0;
      } /*end while*/
    strncat(para,lin3,ll);   /*add justified line to paragraph*/
    strcpy(lin3,cword[a].nm);  /*copy first word of next line*/
    d=strlen(cword[a].nm);
    strcat(lin3," ");  /*add a space to word*/
    d++;
    }      /*end if would be too long*/
  else
    {
    if (d+strlen(cword[a].nm)<ll)  /*would be too short*/
      {
      strcat(lin3,cword[a].nm);  /*add word*/
      d=d+strlen(cword[a].nm);
	d++;
      strcat(lin3," ");
      }
    else
      if (d+strlen(cword[a].nm)==ll) 			/*just right*/
	 {
	 strcat(lin3,cword[a].nm);
	 strncat(para,lin3,ll);  /*copy line to paragraph*/
	 d=0; c=-1;
	 strcpy(lin3,"");
	 }
     }
    }  /*end for each word in paragraph*/

/*check for left over words*/
if (d>0)
  strcat(para,lin3);   /*put on last line*/
d=0;
para[300]=0;
}  /*end spec[6]*/
/*put out text to screen*/
  numlin=1;   /*1*/
  len=strlen(para);
  while (len>ll)
    {
    len=len-ll;
    numlin++;		/*number of lines*/
    }
  if (numlin==1)
     {
     tx=(639 -len*W)/2;
#ifdef DOS
     size=imagesize(tx-10,0,tx+(len)*W+10,numlin*H+20);
#endif
     }
  else
    {
    tx=(639 -ll*W)/2;
#ifdef DOS
    size=imagesize(tx-10,0,tx+ll*W+10,numlin*H+20);
#endif
    }
  ty=(299-numlin*H)/2;

#ifdef DOS
  scr3=malloc(size);
  setactivepage(page);
#endif
#ifdef Linux
//update the pixmap with the screen
//copy the space under the white rectangle

//add the character - somehow character is not there
XSetForeground (xdisplay, xgc, 0x00ffffff);
  if (numlin==1)
{
scr3=XGetImage(xdisplay,pixmap[0],tx-10,ty-10,len*W,numlin*H+5,AllPlanes,ZPixmap);

XFillRectangle(xdisplay, pixmap[0],xgc,tx-10,ty-10,len*W,numlin*H+5);
}
else
{
scr3=XGetImage(xdisplay,pixmap[0],tx-10,ty-10,ll*W+10,numlin*H+10,AllPlanes,ZPixmap);
XFillRectangle(xdisplay, pixmap[0], xgc,tx-10,ty-10,ll*W+10,numlin*H+10);
}

XSetForeground (xdisplay, xgc, 0x002020ff);
  if (numlin==1)
{
XDrawRectangle(xdisplay, pixmap[0],xgc,tx-10,ty-10,len*W-1,numlin*H+4);
}
else
{
XDrawRectangle(xdisplay, pixmap[0], xgc,tx-10,ty-10,ll*W+9,numlin*H+9);
}


XSetForeground (xdisplay, xgc, 0x0);
#endif

#ifdef DOS
  if (numlin==1)
    getimage(tx-10,ty-10,tx+len*W,ty+numlin*H+5,scr3);/*get background*/
  else
    getimage(tx-10,ty-10,tx+ll*W+10,ty+numlin*H+10,scr3);/*get background*/
  setlinestyle(0,0,1);
  setfillstyle(1,15);
  if (numlin==1)
    bar(tx-10,ty-10,tx+len*W-5,ty+numlin*H+5);
  else
    bar(tx-10,ty-10,tx+ll*W+10,ty+numlin*H+10);
  setcolor(0);
  if (numlin==1)
    rectangle(tx-10,ty-10,tx+len*W-5,ty+numlin*H+5);
  else
    rectangle(tx-10,ty-10,tx+ll*W+10,ty+numlin*H+10);
#endif

  for(a=0;a<numlin;a++)
    {
    for(c=0;c<ll;c++)
      lin[c]=para[c+(a*ll)];
    lin[ll]=0;  /*add end to string - eos*/
#ifdef Linux
    XDrawString(xdisplay,pixmap[0],xgc,tx,ty+H*a+(font_info->ascent+font_info->descent)/2,lin,strlen(lin));
#endif
#ifdef DOS
    outtextxy(tx,ty+H*a,lin);  /*16*/
#endif
    }
  switch(spec[6])
    {
    case 2: opt0(opt); break;
    case 3: savscrn(); break;
    case 4: resscrn(); break;
    default: 
#ifdef Linux
ShowScreenF();  //to show the text
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
     ch=13;
     break;
   case KeyPress:
     status=1;
     ch=XLookupKeysym(&xevent.xkey,0);
     break;
    }  //end switch
   }  //end while


#endif
#ifdef DOS
  ch=getch();
  if(ch==0)  getch();
#endif
      break;
    }
  if (qflg>0)
    {
    if (qflg==2)
      { if (ch=='Y' || ch=='y')	qflg=3;
	else qflg=1;}
    else
      {
      if (qflg==1)
	{  if (ch=='Y' || ch=='y') qflg=2;
	   else qflg=3; }
      }
  switch (qflg)
    {
    case 1:
      qflg=0;
      break;
    case 2:
      qflg=0;
      start_over();
      break;
    case 3:
      ex2=1; ex=1; exit(0);
      break;
    }    /*end switch*/
  } /*end qflg*/
  if (spec[6]==2)
    {
    ch=0;
    while (ch!=13&&ch!=27)
      {
      opt0(opt);
#ifdef Linux
status=0;
  while (status!=1)
  {
//   if (XPending(xdisplay))
//    {

  /* wait for next event */
   XNextEvent (xdisplay, &xevent);
   switch (xevent.type) 
    {
   /* ignore this event */
   case Expose:
     break;
   case ButtonPress:
     status=1;
     ch=13;
     break;
   case KeyPress:
     status=1;
     ch=XLookupKeysym(&xevent.xkey,0);
     ch2=0;
     break;
    }  //end switch
   }  //end while

  
  if (1) 
     {
#endif
#ifdef DOS
  ch=getch();
  if (ch==0)
    {
    ch2=getch();   
#endif
#ifdef Linux
	if (ch==82)  
#endif
#ifdef DOS
	if (ch2==72)  
#endif
               {opt1(opt);  if (opt==0)  opt=6;
			else opt--; }
#ifdef Linux
	if (ch==84)  
#endif
#ifdef DOS
	if (ch2==80)  
#endif
                 {opt1(opt);  if (opt==6)  opt=0;
			else opt++;}
	}
      }
    }
  if (spec[6]<2)
    {
if (ch==0) {
#ifdef Linux


   /* wait for next event */
   XNextEvent (xdisplay, &xevent);
   switch (xevent.type) 
    {
   /* ignore this event */
   case Expose:
     break;
   case ButtonPress:
     status=1;
     break;
   case KeyPress:
     status=1;
     break;
    }  //end switch


#endif
#ifdef DOS
  ch=getch();
  if(ch==0)  getch();
#endif
       }  //end if ch==0
    }
#ifdef Linux
if (numlin==1)
{
XPutImage(xdisplay,pixmap[0],xgc,scr3,0,0,tx-10,ty-10,len*W,numlin*H+5);
}
else
{
XPutImage(xdisplay,pixmap[0],xgc,scr3,0,0,tx-10,ty-10,ll*W+10,numlin*H+10);
}

XDestroyImage(scr3);
ShowScreenF();
#endif
#ifdef DOS
  putimage(tx-10,ty-10,scr3,COPY_PUT);	/*put back background*/
#endif

#ifdef DOS
  free(scr3);		/*free that shit*/
#endif
  strcpy(it,par2);  /*restore old it*/
  strcpy(command,scom);  /*restore old command*/
  make_words();    /*and user input by words*/
  for(a=0;a<=ll;a++)   /*clear first line*/
    lin3[a]=0;
  if (spec[6]==2&&ch!=27)
    {
    switch(opt)
      {
      case 0:  story();  break;
      case 1:  help();  break;
      case 2:  start_over();  break;
      case 3:  save_game(); break;
      case 4:  restore_game(); break;
      case 5:  spec[6]=0; quit();  break;
      case 6: break;
      }
    spec[6]=0;
    }
}		/*end putout*/

opt0(int opt)
  {

#ifdef Linux
//fprintf(stderr,"opt %d ",opt*19);
XSetForeground (xdisplay, xgc, klmap[5]);
XDrawRectangle (xdisplay, pixmap[0],xgc,243,74+(opt*20),143,19);
ShowScreenF();
#endif
#ifdef DOS
  setcolor(5);
  rectangle(218,81+(opt*19),420,100+(opt*19));
#endif
  }

opt1(int opt)
  {

#ifdef Linux
XSetForeground (xdisplay, xgc, klmap[15]);
XDrawRectangle (xdisplay, pixmap[0],xgc,243,74+(opt*20),143,19);
ShowScreenF();
#endif
#ifdef DOS
  setcolor(15);
  rectangle(218,81+(opt*19),420,100+(opt*19));
#endif
  }


