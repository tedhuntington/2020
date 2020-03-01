/*  lang.c   */
/*  language interpretting for 2020!   */
/*  by Ted Huntington  */

#include "2020.h"

struct symbols
   {
   char nm;
   };
struct words
  {
  char nm[15];
  };
struct objects
  {
  char name[11];
  int p[4];
  int loc;
  };
extern struct objects obj[NUMOBJ];
extern struct words cword[10];
extern struct words word[NUMWORD+1];
extern char des[DESC1][DESC2];	/*current location description*/
extern char strtim[17];	/*string for time*/
extern int wdflag;		/*how many words in an input sentence*/
extern int retsen;		/*return sentence flag*/
extern int slot,channel;	/*tv variables*/
extern int telpic;		/*telescope picture*/
extern int spec[NUMSPEC];  		/*special flags  (i.e. tv, shower)*/
extern int sent[10];   	/*sentence in numbers*/
extern int ex,ex2;
extern int x1,y1,x2,y2,x3,y3,x4,y4,curloc,curloc3,newloc;
extern int cash,cash0,inv,qflg;

get_retsen()             /*get return sentence flag*/
{
int tmpi;
int c,c0;

retsen=-1;
if (sent[1]==267)  moveup(1);  /* (look)  at*/

for(c=0;c<=wdflag;c++)
  {if (sent[c]==202||sent[c]==203||sent[c]==204||
       sent[c]==45||sent[c]==285)  {moveup(c); c--;}}  /*the-a-an-of-damn*/

reduce();  /*reduce words like 'stock certificates' into 'stock'*/
/*printf("\n %d  %d %d %d %d %d",wdflag,sent[0],sent[1],sent[2],sent[3],sent[4],sent[5]);
*/
if (sent[0]==70) {retsen=999; putout("There is no time to sit!");}

      if (sent[0]==219)    /*what*/
	{
	if ((sent[1]==6)&&(sent[2]==224)&&(sent[3]==246)) /*time is it*/
	   retsen=1;
	}
      if ((sent[0]==12||sent[0]==5)&&(sent[1]==404||sent[1]==405||sent[1]==406||sent[1]==407)&&
	  (sent[2]==266||sent[2]==274)&&(sent[3]==408||sent[3]==406||
	  sent[3]==463)) deliv();
      if ((sent[0]==12||sent[0]==5||sent[0]==132||sent[0]==133)&&
	 (sent[1]==386||sent[1]==387)&&(sent[2]==266||sent[2]==274||
	 sent[2]==257||sent[2]==270||sent[2]==256))
	   throwout();
      if ((sent[0]==12||sent[0]==5||sent[0]==132||sent[0]==133)&&
	 (sent[2]==386||sent[2]==387)&&(sent[1]==266||sent[1]==274||
	 sent[1]==257))
	   throwout();
      if (sent[0]==12&&(sent[1]==389||sent[1]==390)&&(sent[2]==266||sent[2]==274)&&
	  sent[3]==437)  stock();
      if (sent[0]==12&&(sent[1]==368||sent[1]==382)&&
	(sent[2]==266||sent[2]==274)&&sent[3]==437)  cashex();
      give();
      if ((sent[0]==12)&&sent[1]==461||sent[1]==462) poison();
      if (sent[0]==44||sent[0]==136) {dial(); wdflag=5;} 
      if (sent[0]==121||sent[0]==122) hint();
      if (sent[0]==66&&sent[1]==283) {sent[0]=4; moveup(1);}
      if (sent[1]==397&&(sent[2]==263||sent[2]==271))
	{sent[1]=sent[2]; sent[2]=397;}
if (retsen!=999)
{
switch(wdflag)  /*branch on number of words in sentence*/
  {
  case 0:   /* 1 word*/
    switch(sent[0])   /*branch on word*/
      {
      case 0:
      case 7:  retsen=999; quit();    /*quit-exit*/
	break;
      case 1:
      case 10:
      case 25:  retsen=3;	/*look-scope-watch*/
	break;
      case 4:
      case 5:
      case 8:
      case 19:
      case 21:
      case 22:
      case 23:
      case 24:
      case 26:
      case 27:
      case 34:
      case 36:
      case 37:  retsen=4;	/*-verb- what?*/
	break;
      case 2:  /*save*/
	retsen=999;
	putout("Ok.");
	save_game();
	break;
      case 3:  /*res*/
	retsen=999; putout("Ok.");
	restore_game();
	break;
      case 6:	retsen=1;	/*time*/
	break;
      case 9:   shower();     /*shower*/
	break;
      case 42:  /*sleep*/
	sleep();
	break;
      case 43:  retsen=48;    /*love*/  /*yes!*/
	break;
      case 17:
      case 18:
      case 20:   retsen=12; /*inv-inven-*/
	break;
      case 29:	retsen=53;     /*date*/
	break;
      case 30:   /*shit*/
	if (curloc==4) retsen=90;
	else retsen=36;
	break;
      case 31:  retsen=37;  /*fuck*/
	break;
      case 49:
      case 50:
	retsen=95;
	break;
      case 53:
      case 54:
	retsen=96;
	break;
      case 55:
      case 127:
	stay();
	break;
      case 57:
	follow();
	break;
      case 60:  /*piss-pee*/
      case 61:
	retsen=90;
	break;
      case 62:  /*fart*/
	retsen=123;
	break;
      case 63:
      case 64:
      case 80:
      case 81:
      case 82:
	retsen=123;
	break;
      case 89:
	if (curloc==4||curloc==6) retsen=14;
	else retsen=9;
	break;
      case 238:  retsen=47;  /*I*/
       break;
      case 288:  retsen=51;
	break;
      case 402:  moms();
	break;
      case 483:
	retsen=999; putout("bastard.");
	break;
      case 507:
	retsen=999; putout("dance!");
	break;
      default:  retsen=200;  /*recognize word, but not meaning*/
      }  /*end branch on  word*/
      if ((sent[0]>10) && (sent[0]<119) && retsen==200) retsen=4;   /*verb what?*/
      if (sent[0]>287&&retsen==200) retsen=52;   /*yes, object.*/
      break;
  case 1:   /* 2 words*/
    switch(sent[0])   /*branch on 1st word*/
      {
      case 0:
	if (sent[1]==4)  retsen=999; quit();  /*quit game*/
	break;
      case 1:  /*look*/
      case 10:
      case 25:
	switch(sent[1])  /*branch on 2nd word*/
	  {
	  case 6:  retsen=1;  /*time*/
	    break;
	  case 246:  /*It*/
	  case 445:  /*robot*/
	    if (curloc3==curloc&&(spec[20]==1||spec[20]==2))
	      retsen=132;
	    else
	      retsen=8;
	    break;
	  case 264:   /*around*/
	    retsen=3;
	    break;
	  case 288:  retsen=51;
	    break;
	  case 289:  retsen=999; putout("The rug is lumpy."); /*rug*/
	    break;
	  case 290:    /*statue*/
	    if (curloc==1)  retsen=39;
	    else  retsen=25;
	    break;
	  case 291:  /*fireplace*/
	    if (curloc==1)  retsen=41;
	    else  retsen=25;
	    break;
	  case 292:  /*grate*/
	    if (curloc==1) retsen=11;
	    else retsen=25;
	    break;
	  case 293:
	  case 357:    /*wall-walls*/
	    if (curloc<20)  retsen=20;
	    else  retsen=25;
	    break;
	  case 294:    /*floor*/
	    switch (curloc)
	      {
	      case 1:         /*bedroom*/
		if (obj[100].loc==1) retsen=38;
		else retsen=35;
		break;
	      default:
		retsen=35;
	      }
	    break;
	  case 295:
	  case 25:   /*telescope-scope*/
	    if (curloc==2) retsen=24;
	    else  retsen=25;
	    break;
	  case 297:  /*city*/
	    if (curloc==2)  retsen=28;
	    else  retsen=25;
	    break;
	  case 298:
	  case 299:  /*water-ocean*/
	    if (curloc==2) retsen=45;
	    else retsen=25;
	    break;
	  case 300:
	  case 301:
	  case 302:  /*traffic-road-highway*/
	    if (curloc==2)  retsen=46;
	    else  retsen=25;
	    break;
	  case 303:
	  case 304:  /*bed-waterbed*/
	    if (curloc==2)  retsen=50;
	    else  retsen=25;
	    break;
	  case 305:  /*desk*/
	    if (curloc==2) retsen=69;
	    else retsen=25;
	    break;
	  case 307:  /*link*/
	    if (obj[8].loc==-2 || obj[8].loc==curloc) retsen=91;
	    else retsen=25;
	    break;
	  case 309:
            if (curloc>7 && curloc<40) retsen=83;
	    else retsen=25;
	    break;
	  case 310:
	  case 311:
	    if (curloc>7 && curloc<40) retsen=83;
	    else retsen=32;
	    break;
	  case 313:
	    if (curloc==2) retsen=3;
	    else retsen=92;
	    break;
	  case 314:
	    if (curloc==6) retsen=3;
	    else retsen=92;
	    break;
	  case 315:
	    if (curloc==4) retsen=3;
	    else retsen=92;
	    break;
	  case 316:
	    if (curloc<8) retsen=3;
	    else retsen=92;
	    break;
	  case 326:
	  case 327:  /*tv-television*/
	    if (curloc==7)  retsen=34;
	    else  retsen=25;
	    break;
	  case 329:
	  case 348:  /*window(s)*/
	    switch(curloc)
	      {
	      case 2:
		retsen=30;
		break;
	      case 7:
		retsen=31;
		break;
	      default:
		retsen=32;        /*no windows*/
		break;
	      }	/*end switch*/
	    break;
	  case 336:  /*sofa*/
	  case 337:
	  case 455:
	    retsen=999; putout("The couch is kind of lumpy, and too comfy to sit on.");
	    break;
	  case 344:  /*button*/
	    if (curloc==2) retsen=29;
	    else retsen=25;
	    break;
	  case 354:   /*statues*/
	    if (curloc==1)  retsen=39;
	    else  retsen=32;
	    break;
	  case 355:  /*fire*/
	    retsen=42;
	    break;
	  case 364:   /*phone*/
	  case 367:
	  case 32:
	  case 44:
	  case 401:
	    phone();
	    break;
	  case 365: /*drawer*/
	     if (curloc==2)
	       {
	       if (obj[179].loc==2) retsen=72;
	       else retsen=70;
	       }
	     else
	     {
	     if (curloc==6)
	       {
	       if (obj[147].loc==6) retsen=72;
	       else retsen=70;
	       }
	     else retsen=25;
	     }
	     break;
	  case 368:  /*money*/
	  case 382:
	    if (obj[180].loc==-1 || obj[180].loc==curloc||obj[181].loc==-1||
	       obj[181].loc==curloc||obj[187].loc==curloc||obj[187].loc==-1||
	       obj[188].loc==curloc||obj[188].loc==-1||obj[189].loc==-1||
	       obj[189].loc==curloc) retsen=113;
	    else retsen=10;
	    for(c=190;c<233;c++)
	      if (obj[c].loc==-1||obj[c].loc==curloc) retsen=113;
	    break;
	  case 370:
	  case 389:   /*stock*/
	  case 391:
	    for(c=100;c<119;c++)
	      if (curloc==obj[c].loc||obj[c].loc==-1) {c=120;retsen=11;}
	    if (retsen!=11) retsen=25;
	    break;
	  case 371:  /*stocks*/
	  case 390:
	  case 392:
	    for(c=100;c<119;c++)
	      if (curloc==obj[c].loc||obj[c].loc==-1) {c=120;retsen=11;}
	    if (retsen!=11) retsen=32;
	    break;
	  case 397:  /*trnsltr*/
	    if (obj[28].loc==curloc||obj[28].loc==-1)
	      retsen=71;
	    else
	      retsen=10;
	    break;
	  case 394:
	  case 404:  /*box*/
	  case 406:
	    for(c=174;c<179;c++)
	      if (curloc==obj[c].loc||obj[c].loc==-1) {c=179;retsen=109;}
	    if (retsen!=109) retsen=25;
	    if (obj[15].loc==curloc) retsen=130;
	    if (curloc==53) retsen=131;
	    break;
	  case 405:  /*boxes*/
	  case 407:
	    for(c=174;c<179;c++)
	      if (curloc==obj[c].loc||obj[c].loc==-1) {c=179;retsen=109;}
	    if (retsen!=109) retsen=32;
	    break;
	 case 408:  /*mailbox*/
	 case 419:
	   if (curloc>=12 &&curloc<=15) retsen=108;
	   else
	     {
	     if (sent[1]==408) retsen=25;
	     else retsen=32;
	     }
	   break;
	 case 409:  /*apt*/
	 case 410:
	   if (curloc>=12 &&curloc<=15) retsen=106;
	   else
	     {
	     if (curloc==8) retsen=107;
	     else
	       {
	       if (sent[1]==409) retsen=25;
	       else retsen=32;
	       }
	     }
	   break;
	case 413:  /*person*/
	case 414:
	case 415:
	case 403:
	case 412:
	case 411:
	case 489:
	case 490:
	case 491:
	case 492:
	case 493:
	case 494:
	case 481:
	case 499:
	case 503:
	case 505:
	  lpeople();
	  break;
	case 417:
	case 420:
	  if (obj[172].loc==-1 || obj[172].loc==curloc)
	    retsen=111;
	  else  retsen=9;
	  break;
	case 418:
	case 421:
	  if (obj[173].loc==-1 || obj[173].loc==curloc)
	    retsen=112;
	  else retsen=9;
	  break;
	case 437:  /*machine*/
	  if (curloc==44)  retsen=119;
	  if (curloc==47)  retsen=120;
	  if (curloc==48)  retsen=121;
	  if (retsen==0) retsen=35;
	  break;
	case 461:
	  if (obj[251].loc==curloc||obj[251].loc==-1)
	    {retsen=999; putout("The cyanide is powdery.");}
	  else retsen=10;
	default:
	  retsen=11;
	  break;
	}  /*end branch on 2nd word*/
	break;
      case 2:  /*save*/
	if (sent[1]==228)
	  {
	  retsen=999;
	  save_game();
	  }
	break;
      case 3:  /*res*/
	if (sent[1]==228)
	  {
	  retsen=999;
	  restore_game();
	  }
	break;
      case 4:
      case 19:  /*get-take*/
	suminv();
/*	if (inv==9&&sent[1]!=389&&sent[1]!=390&&sent[1]!=441&&sent[1]!=442&&
	sent[1]!=368&&sent[1]!=382) retsen=129;
	else
	{*/
	tmpi=cmp_inv();
	switch (tmpi)  /*branch on inventory item*/
	  {
	  case 0:   /*job*/
	    if (curloc==40)
	      {
	      if (spec[9]==0)
	       {
	       for (c=174;c<179;c++)
		 obj[c].loc=-1;
	       spec[9]=1;
	       retsen=102;
	       }
	      else
		retsen=105;
	      }
	    else
	      {
	      if (curloc==46)
		{if (spec[18]==0) {spec[18]=1; govt();}
		 else retsen=25;
		 }
	      else
	       retsen=25;
	      }
	    break;
	  case 1:  /*package-box*/
	  case 2:
	    for(c=174;c<179;c++)
	      {
	      if (curloc==obj[c].loc)
		{
		if (close_enough(c)) /*here and close enough*/
		   {
		   obj[c].loc=-1;  c=179;  retsen=5;
		   }
		else
		   retsen=6;
		 }  /*end if we are in same room*/
	      } /*end for*/
	    if (retsen==0)
	      {if(tmpi==1) retsen=25;
	       else retsen=32;}
	    break;
	  case 3:  gdisc(0);  break;
	  case 4:  gdisc(1);  break;
	  case 5:  gdisc(2);  break;
	  case 6:   /*ticket*/
	    buyticket();
	    break;
	  case 100:   /*stock*/
	  case 101:
	    for(c=100;c<119;c++)
	      {
	      if (curloc==obj[c].loc)
		 {
		 if (curloc3==curloc)  {obj[c].loc=-1; retsen=49;}
		 else
		   {
		   if (close_enough(c)) /*paper here and close enough*/
		     {obj[c].loc=-1;  c=120;  retsen=5;}
		   else
		     retsen=6;
		   }
		 }  /*end if we are in same room*/
	      } /*end for*/
	    if (retsen==0)
	      {if (tmpi==100||tmpi==101) retsen=25;
	       else retsen=32;}
	    break;
	  case 131:   /*garbage-trash*/
	    for(c=131;c<140;c++)
	      {
	      if (curloc==obj[c].loc)
		 {
		 if (close_enough(c)) /*trash here and close enough*/
		   {obj[c].loc=-1;  c=140;  retsen=5;}
		 else
		   retsen=6;
		 }  /*end if we are in same room*/
	      } /*end for*/
            if (retsen==0)
	       retsen=25;
	    break;
	  case 9:   /*shower*/
	    shower();
	    break;
	  case 180:  /*money*/
	    c0=0;
	    if (obj[180].loc==curloc)
		{if (close_enough(180)) {obj[180].loc=-1; cash=cash+100;retsen=5;c0=1;}
		else retsen=6;}
	    if (obj[181].loc==curloc)
	       {if (close_enough(181)) {obj[181].loc=-1; cash=cash+75;retsen=5;c0=1;}
	       else retsen=6;}
	    if (obj[187].loc==curloc)
	       {if (close_enough(187)) {obj[187].loc=-1; cash=cash+20;retsen=5;c0=1;}
	       else retsen=6;}
	    if (obj[188].loc==curloc)
	       {if (close_enough(188)) {obj[188].loc=-1; cash=cash+10;retsen=5;c0=1;}
	       else retsen=6;}
	    if (obj[189].loc==curloc)
	       {if (close_enough(189)) {obj[189].loc=-1; cash=cash+75;retsen=5;c0=1;}
	       else retsen=6;}
	    for(c=190;c<209;c++)
	      {
	      if (obj[c].loc==curloc)
		{if (close_enough(c)) {obj[c].loc=-1; cash=cash+40;retsen=5;c0=1;}
		else retsen=6;}
	      }
	    if (obj[209].loc==curloc)
		{if (close_enough(209)) {obj[209].loc=-1; cash0=cash0+100;retsen=5;c0=1;}
		else retsen=6;}
	    if (obj[210].loc==curloc)
	       {if (close_enough(210)) {obj[210].loc=-1; cash0=cash0+75;retsen=5;c0=1;}
	       else retsen=6;}
	    if (obj[211].loc==curloc)
	       {if (close_enough(211)) {obj[211].loc=-1; cash0=cash0+20;retsen=5;c0=1;}
	       else retsen=6;}
	    if (obj[212].loc==curloc)
	       {if (close_enough(212)) {obj[212].loc=-1; cash0=cash0+10;retsen=5;c0=1;}
	       else retsen=6;}
	    if (obj[213].loc==curloc)
	       {if (close_enough(213)) {obj[213].loc=-1; cash0=cash0+75;retsen=5;c0=1;}
	       else retsen=6;}
	    for(c=214;c<233;c++)
	      {
	      if (obj[c].loc==curloc)
		{if (close_enough(c)) {obj[c].loc=-1; cash0=cash0+40;retsen=5;c0=1;}
		else retsen=6;}
	      }
	    if (retsen==0) retsen=25;
	    if (c0==1) retsen=5;
	    c0=0;
	  break;
	  case 254:
	    retsen=999; putout("You must be more specific.");
	    break;
	  default:
	    if (curloc==obj[tmpi].loc)
	      {     /*close enough?*/
	      if (close_enough(tmpi))
		{
		obj[tmpi].loc=-1;
		retsen=5;
		}
	     else	/*not close enough*/
	       retsen=6;
	     }
	   else {if (obj[tmpi].loc==-1) retsen=7;
		 else retsen=9;}
	}   /*end branch on inventory item*/
/*	}*/  /*end else*/
	suminv();
	break;
      case 5:   /*drop*/
	tmpi=cmp_inv();
	 switch (tmpi)  /*branch on inv item*/
	   {
	   case 1:   /*package*/
	   case 2:
	     for(c=174;c<179;c++)
	       {
	       if (obj[c].loc==-1)
		 { obj[c].loc=curloc;  obj[c].p[0]=x1-5; obj[c].p[1]=y1+HMAN;
		 c=179;  retsen=5;}
	       else
		 retsen=6;
	       }  /*end for*/
	     break;
	   case 3:
	     ddisc();
	     break;
	   case 100:   /*stock*/
	   case 101:
	     for(c=100;c<119;c++)
	       {
	       if (obj[c].loc==-1)
		 { obj[c].loc=curloc;  obj[c].p[0]=x1-5; obj[c].p[1]=y1+HMAN;
		  retsen=5;}
	       else
		 retsen=6;
	       }  /*end for*/
	     break;
	   case 131:   /*trash-garbage*/
	     for(c=131;c<140;c++)
	       {
	       if (obj[c].loc==-1)
		 { obj[c].loc=curloc;  obj[c].p[0]=x1-5; obj[c].p[1]=y1+HMAN;
		 c=140;  retsen=5;}
	       else
		 retsen=6;
	       }  /*end for*/
	     break;
	   case 180:  /*money*/
	    if (obj[180].loc==-1) {obj[180].loc=curloc; obj[180].p[0]=x1-5; obj[180].p[1]=y1+HMAN+2;
					cash=cash-100;retsen=5;}
	    if (obj[181].loc==-1) {obj[181].loc=curloc; obj[181].p[0]=x1-5; obj[181].p[1]=y1+HMAN+2;
					cash=cash-75;retsen=5;}
	    if (obj[187].loc==-1) {obj[187].loc=curloc; obj[187].p[0]=x1-5; obj[187].p[1]=y1+HMAN+2;
					cash=cash-20;retsen=5;}
	    if (obj[188].loc==-1) {obj[188].loc=curloc; obj[188].p[0]=x1-5; obj[188].p[1]=y1+HMAN+2;
					cash=cash-10;retsen=5;}
	    if (obj[189].loc==-1) {obj[189].loc=curloc; obj[189].p[0]=x1-5; obj[189].p[1]=y1+HMAN+2;
					cash=cash-75;retsen=5;}
            for(c=190;c<209;c++)
	      {
	      if (obj[c].loc==-1)
		{obj[c].loc=curloc; cash=cash-40;retsen=5;obj[c].p[0]=x1-5; obj[c].p[1]=y1+HMAN+2;}
	      }
	    if (obj[209].loc==-1) {obj[209].loc=curloc; obj[209].p[0]=x1-5; obj[209].p[1]=y1+HMAN+2;
					cash0=cash0-100;retsen=5;}
	    if (obj[210].loc==-1) {obj[210].loc=curloc; obj[210].p[0]=x1-5; obj[210].p[1]=y1+HMAN+2;
					cash0=cash0-75;retsen=5;}
	    if (obj[211].loc==-1) {obj[211].loc=curloc; obj[211].p[0]=x1-5; obj[211].p[1]=y1+HMAN+2;
					cash0=cash0-20;retsen=5;}
	    if (obj[212].loc==-1) {obj[212].loc=curloc; obj[212].p[0]=x1-5; obj[212].p[1]=y1+HMAN+2;
					cash0=cash0-10;retsen=5;}
	    if (obj[213].loc==-1) {obj[213].loc=curloc; obj[213].p[0]=x1-5; obj[213].p[1]=y1+HMAN+2;
					cash0=cash0-75;retsen=5;}
	    for(c=214;c<233;c++)
	      {
	      if (obj[c].loc==-1)
		{obj[c].loc=curloc; cash0=cash0-40;retsen=5;obj[c].p[0]=x1-5; obj[c].p[1]=y1+HMAN+2;}
	      }
	    if (retsen==0) retsen=10;
	    break;
	   default:   /*reg drop*/
	     if (curloc==70&&obj[172].loc==-1) {retsen=999;
	      putout("Tom takes the seeds from you and is very excited about saving a very special species of plant.");
	      obj[172].loc=-2;spec[24]++;}
	     else {
	     if (curloc==70&&obj[173].loc==-1) {retsen=999;
	      putout("Tom takes the spores from you and is very happy to save a very special species of mushroom.");
	      obj[173].loc=-2;spec[24]++;}
	     else
	       {
	     if (obj[tmpi].loc==-1) {obj[tmpi].loc=curloc;
			  obj[tmpi].p[0]=x1-5; obj[tmpi].p[1]=y1+HMAN+2;
			  retsen=5;}
	     else if (obj[tmpi].loc!=-1) retsen=10;}}
	     break;
	   }  /*end branch on inv item*/
	suminv();
	break;
      case 7:  /*exit*/
	if (sent[1]==309||sent[1]==395) exitcar();
	break;
      case 8:   /*start*/
	if (sent[1]==258) retsen=2;   /*over*/
	break;
      case 12:  /*put*/
	if (sent[1]==461||sent[1]==462) poison();
	break;
      case 11:
      case 13:
      case 46:  /*turn-switch-change*/
	tmpi=0;
	switch (sent[1])  /*branch on 2nd word*/
	  {
	  case 263:	/*on*/
	    retsen=19;
	    break;
	  case 349:
	  case 350:  /*channel-station*/
	    tmpi=1;
	    break;
	  case 351:
	  case 352:  /*channels-stations*/
	    tmpi=2;
	    break;
	  }  /*end branch on 2nd word*/
	if (curloc==7)   /*in tv room*/
	  {
	  if (spec[0]==1)   /*and tv is on*/
	    {
	    obj[slot*10+channel+30].loc=-2;  /*turn off old chan*/
	    channel++;
	    if (channel==10)  channel=0;
	    obj[slot*10+channel+30].loc=7;
	    retsen=5;
	    }
	  else
	    retsen=34;
	  }
	else
	  {
	  if (tmpi==1)  retsen=25;
	  else retsen=32;
	  }
	break;
      case 21:   /*open*/
	tmpi=0;
	switch(sent[1])  /*branch on 2nd word*/
	  {
	  case 309:
	  case 325:
	  case 395:
	     tmpi=10;	/*car*/
	    break;
	  case 329: tmpi=1;     /*window*/
	    break;
	  case 330:
	  case 331:
	  case 332:
	  case 341:  tmpi=2;       /*shade-curtain-blind-drape*/
	    break;
	  case 334:
	  case 333:
	  case 335:
	  case 342:  tmpi=3;      /*curtains-shades-blinds-drapes*/
	    break;
	  case 308:
	  case 312:
	  case 398:  tmpi=4;      /*refridgerator*/
	    break;
	  case 399:  tmpi=5;	  /*freezer*/
	    break;
	  case 400:
	  case 362:
	  case 363:  tmpi=6;   /*cupboard-cabinets*/
	    break;
	  case 360:  tmpi=7;   /*oven*/
	    break;
	  case 365:
	  case 305:  tmpi=8;  /*drawer*/
	    break;
	  case 394:
	  case 404:  /*package-box*/
	  case 406:
	    tmpi=9;
	    break;
	  }    /*end branch on 2nd word*/
	if (tmpi>1)
	  {
	  switch(tmpi)
	    {
	    case 2:
	    case 3:
	      if (curloc==7)   /*if we are in the tv room*/
		{
		if (obj[3].loc==7)
		  {
		  obj[3].loc=-2;  obj[4].loc=-2;  obj[5].loc=-2;
		  retsen=5;
		  }
		else
		  retsen=15;		/*they are already open*/
		}
	       else
		{               /*no curtains-shades here*/
		if (tmpi==2)  retsen=25;
		else  retsen=32;
		}
	    break;
	    case 4:
	      if (curloc==6)
		{
		if (close_enough(9))
		  {if (obj[145].loc==6) retsen=55;
		  else
		  {obj[145].loc=6;  retsen=5;}
		  }
		else
		  retsen=6;
		}
	      else
		retsen=25;
	    break;
	    case 5:
	      if (curloc==6)
		{
		if (close_enough(9))
		  {if (obj[146].loc==6) retsen=55;
		  else
		  {obj[146].loc=6;  retsen=5;}
		  }
		else
		  retsen=6;
		}
	      else
		retsen=25;
	    break;
	    case 6:
	      if (curloc==6)
		{                   /*left*/
		if (close_enough(141))
		  {
		  if (obj[143].loc==6) retsen=55;
		  else
		  {obj[143].loc=6;  retsen=5;  }
		  }
		else
		if (close_enough(142))
		  {
		  if (obj[144].loc==6) retsen=55;
		  else
		  {obj[144].loc=6;  retsen=5;}
		  }
		else
		  retsen=6;
		}
	      else
		retsen=25;
	    break;
	    case 7:
	      if (curloc==6)
		{                   /*left*/
		if (close_enough(23))
		{
		if (obj[148].loc==6) retsen=55;
		else
		  {obj[148].loc=6; obj[149].loc=6; retsen=5;}
		}
		else
		  retsen=6;       /*rt*/
		}
	      else
		retsen=25;
	    break;
	    case 8:
	      if (curloc==6)
		{
		if (close_enough(141))
		  {if (obj[147].loc==6) retsen=55;
		  else
		    {obj[147].loc=6; retsen=5;
		    }
		  }
		else
		  retsen=6;
		}
	      else
	      {
	      if (curloc==2)
		{
		if (close_enough(2)||(x1<195&&x1>110&&y1>165))
		  {if (obj[179].loc==2) retsen=72;
		  else
		  {obj[179].loc=2; retsen=5;
		    if(obj[180].loc==-2) obj[180].loc=2;
		    if(obj[182].loc==-2) obj[182].loc=2;
		    if(obj[183].loc==-2) obj[183].loc=2;
		    if(y1>165&&y1<191&&x1>110&&x1<195) y1=y2=y3=y4=165;
		    }
		  }
		else
		  retsen=6;
		}
	      else
		retsen=25;
	      }
	    break;
	    case 9:
	      if (curloc==5)
		{
		if (obj[15].loc==5)
		  {
		  if (close_enough(15))
		    {
		    if (spec[20]==0)
		      {
		      retsen=5;
		      spec[20]=1;
		      obj[233].loc=5;
			/*set robot location*/
			x3=x4=362; y3=y4=222;
		      }
		    else retsen=55;
		    }
		  else retsen=6;
		  }
		else retsen=9;
		}
	      else retsen=9;
	    break;
	    case 10:  /*open car*/
	      opcr();
	    break;
	    }  /*end switch*/
	  }    /*end if tmpi>1*/
	else  retsen=9;	/*can't open*/
	break;
     case 22:
     case 23:    /*close-shut*/
       tmpi=0;
       switch (sent[1])  /*branch on 2nd word*/
	 {
	 case 309:
	 case 325:
	 case 395:
	   tmpi=10;  /*car*/
	   break;
	 case 329: tmpi=1;     /*window*/
	   break;
	 case 330:
	 case 331:
	 case 332:  tmpi=2;
	   break;
	 case 333:
	 case 334:
	 case 335:  tmpi=3;
	   break;
	 case 308:
	 case 312:
	 case 398:  tmpi=4;
	    break;
	  case 399:  tmpi=5;
	    break;
	  case 400:
	  case 362:
	  case 363:  tmpi=6;
	    break;
	  case 360:  tmpi=7;
	    break;
	  case 365:  tmpi=8;
	    break;
	  case 394:
	  case 404:
	  case 406:   tmpi=9;
	    break;
	 }  /*end branch on 2nd word*/
       if(tmpi>1)    /*close shades-curtains-blinds-drapes*/
	 {
	 switch(tmpi)
	 {
	 case 2:
	 case 3:
	 if (curloc==7)   /*if we are in the tv room*/
	   {
	   if (obj[3].loc==-2)
	     {
	     obj[3].loc=7;  obj[4].loc=7;  obj[5].loc=7;
	     retsen=5;
	     }
	   else
	     retsen=17;		/*they are already closed*/
	   }
	 else
	   {               /*no curtains-shades here*/
	   if (tmpi==2)  retsen=25;
	   else  retsen=32;
	   }
	 break;
	 case 4:
	      if (curloc==6)
		{
		if (close_enough(9))
		  {if (obj[145].loc==-2) retsen=56;
		  else
		  {obj[145].loc=-2;  retsen=5;}
		  }
		else
		  retsen=6;
		}
	      else
		retsen=25;
	    break;
	    case 5:
	      if (curloc==6)
		{
		if (close_enough(9))
		  {if (obj[146].loc==-2) retsen=56;
		  else
		  {obj[146].loc=-2;  retsen=5;}
		  }
		else
		  retsen=6;
		}
	      else
		retsen=25;
	    break;
	    case 6:
	      if (curloc==6)
		{                   /*left*/
		if (close_enough(141))
		  {
		  if (obj[143].loc==-2) retsen=56;
		  else
		  {obj[143].loc=-2;  retsen=5;  }
		  }
		else
		if (close_enough(142))
		  {
		  if (obj[144].loc==-2) retsen=56;
		  else
		  {obj[144].loc=-2;  retsen=5;}
		  }
		else
		  retsen=6;
		}
	      else
		retsen=25;
	    break;
	    case 7:
	      if (curloc==6)
		{                   /*left*/
		if (close_enough(23))
		{
		if (obj[148].loc==-2) retsen=56;
		else
		  {obj[148].loc=-2; obj[149].loc=-2; retsen=5;}
		}
		else
		  retsen=6;       /*rt*/
		}
	      else
		retsen=25;
	    break;
	    case 8:
	      if (curloc==6)
		{
		if (close_enough(141))
		  {if (obj[147].loc==-2) retsen=56;
		  else
		  {obj[147].loc=-2; retsen=5;}
		  }
		else
		  retsen=6;
		}
	      else
	      {
	      if (curloc==2)
		{
		if (close_enough(2)||(x1<195&&x1>110&&y1>150))
		  {if (obj[179].loc==-2) retsen=70;
		  else
		  {obj[179].loc=-2; retsen=5;
		  if (obj[180].loc==2&&obj[180].p[0]==150) obj[180].loc=-2;
		  if (obj[182].loc==2&&obj[182].p[0]==135) obj[182].loc=-2;
		  if (obj[183].loc==2&&obj[183].p[0]==178) obj[183].loc=-2;
		  }
		  }
		else
		  retsen=6;
		}
	      else
		retsen=25;
	      }
	    break;
	  case 9:
	      if (curloc==5)
		{
		if (obj[15].loc==5)
		  {
		  if (close_enough(15))
		    {
		    if (spec[20]==1)
		      {
		      retsen=5;
		      spec[20]=0;
		      obj[233].loc=-2;
		      }
		    else retsen=56;
		    }
		  else retsen=6;
		  }
		else retsen=9;
		}
	      else retsen=9;
	  break;
	  case 10:
	    clcr();
	  break;
	  }  /*switch*/
	  }    /*end if tmpi>1*/
	else  retsen=9;	/*can't*/
       break;
    case 24:
    case 27:   /*push-press*/
      switch(sent[1])  /*branch on 2nd word*/
	{
	case 344:  /*button*/
	  if (curloc==2)   /*if we are in the bedroom*/
	    {
	    if (close_enough(1))
	      {telpic++; if (telpic>94) telpic=90; retsen=27;}
	    else
	      retsen=6;		/*not close enough*/
	    }    /*end if curloc==2*/
	  else
	    {
	    if (curloc==62)  {elev();}
	    else
	      {
	      if (curloc==63||curloc==64||curloc==65)
		   {retsen=999;putout("Which one?");}
	      else
		retsen=25;	/*not here.*/
	      }
	    }
	  break;
	}	/*end branch on 2nd word*/
      break;
    case 56:  /*go*/
      godrive();
      break;
    case 98:  /*drive*/
      retsen=998;
      godrive();
      break;
    case 57:  /*follow*/
      if (sent[1]==240) follow();
      break;
    case 59:  /*answer*/
      if (sent[1]==364||sent[1]==367||sent[1]==32||sent[1]==44||sent[1]==401)
	phone();
      break;
    case 71:  /*talk-speak to-with*/
    case 86:
      switch(sent[1])
	{
	case 239:   /*you*/
	  retsen=97;
	  break;
	case 240:  /*me*/
	  retsen=97;
	  break;
	case 246:  /*it*/
	  retsen=98;
	  break;
	case 247:  /*god*/
	  retsen=99;
	  break;
	case 403:
	  if (curloc==41) mom();
	  break;
	case 411:  /*human-person*/
	case 412:
	case 415:
	case 481:
	case 487:
	case 489:
	case 492:
	case 493:
	case 494:
	case 499:
	case 503:
	case 505:
	  if (curloc==40)  pack();
	  if (curloc==41)  mom();
	  if (curloc==46)  govt();
	  if (curloc==73) givemed();
	  if (curloc==66) {retsen=999; putout("Lee is generally quiet.");}
	  if (curloc==68) {retsen=999; putout("Timothy speaks about quarks, quasars, and the few moments after the beginning of time.");}
	  if (curloc==70) {retsen=999; putout("Tom talks about music and the environment, and Tracy talks about voice and food things.");}
	  if (retsen==0)  retsen=9;
	  break;
	case 413:
	  if (curloc==40)  pack();
	  if (curloc==46)  govt();
	  if (curloc==73) givemed();
	  if (curloc==66) {retsen=999; putout("Lee is generally quiet.");}
	  if (curloc==68) {retsen=999; putout("Timothy speaks about quarks, quasars, and the few moments after the beginning of time.");}
	  if (curloc==70) {retsen=999; putout("Tom talks about music and the environment, and Tracy talks about voice and food things.");}
	  if (retsen==0)  retsen=9;
	  break;
	case 414:
          if (curloc==41)  mom();
          if (retsen==0)  retsen=9;
	  break;
	case 490:
	case 491:
	  if (curloc==73) givemed();
	  break;
	}  /*end sw*/
    case 85:  /*say*/
      if (sent[1]==49 || sent[1]==50) retsen=95;
      if (sent[1]==53 || sent[1]==54) retsen=96;
      if (sent[1]==402)
	moms();
      if (sent[1]==57) follow();
      if (sent[1]==127||sent[1]==55) stay();
      break;
    case 88:  /*deliver*/
      deliv();
      break;
    case 123:  /*insert*/
    case 124:
    case 125:
       if (sent[1]==389||sent[1]==390)  stock();
       if (sent[1]==368||sent[1]==382)  cashex();
       break;
    case 126:
      if (sent[1]==444) {retsen=999; quit();}
      break;
    case 128:   /*unlock*/
      if (sent[1]==309||sent[1]==325) unlk();
      break;
    case 129:   /*lock*/
      if (sent[1]==309||sent[1]==325) lk();
      break;
    case 130:  /*buy*/
    case 131:  /*purch*/
       if (sent[438])  /*ticket*/
	    buyticket();
       break;
    case 134: /*give*/
      give();
      break;
    case 500:
    case 501:  /*Ted*/
      if (sent[1]==481) retsen=89;
      break;
    case 502:  /*Ellen*/
      if (sent[1]==482)  retsen=88;
      break;
    case 446:  /*president*/
      if (sent[1]==481) retsen=89;
      break;
    case 508:
     if (sent[1]==509) {retsen=999; putout("This cat makes Leo Buscalia look human.");}
     break;
    case 510:
     if (sent[1]==511) {retsen=999; putout("John Lennon was a great man who was killed. What if he were still alive today? What a nice planet this would be.");}
     break;
    case 513:
    if (sent[1]==514) {retsen=999; putout("Action!");}
     break;
    }  /*end 2 words*/
    break;
  case 2:  /*3 words*/
    if ((sent[0]==12)&&sent[1]==461||sent[1]==462) poison();
    give();
    switch(sent[0])  /*branch on 1st word*/
      {
      case 1:  /*look*/
	switch(sent[1])  /*branch on 2nd word*/
	  {
	  case 265:  /*under*/
	    if (sent[2]==289)
	      {
	      if (curloc==1)
		{
		if (close_enough(6))
		  {
		  if (obj[187].loc==-2)  {obj[187].loc=1;retsen=116;}
		  else retsen=117;
		  }
		else retsen=6;
		}
	      else
		retsen=25;
	      }
	  break;
	  case 257:
	  case 268:
	  case 269:
	  case 266:
	  case 274:    /*into-through-thru-in-inside*/
	    if ((sent[2]==295)||(sent[2]==25)) /*telescope-scope*/
	      {
	      if (curloc==2)
		{
		if (close_enough(1))	/*if close enough*/
		  retsen=23;
		else
		  retsen=6;
		}
	      else
		{
		moveup(1);
		retsen=25;	/*no telescope here*/
		}
	      }  /*end if*/
	    if (sent[2]==291) /*fireplace*/
	      {
	      if (curloc==1)  retsen=41;
	      else retsen=25;
	      }
	    if (sent[2]==336||sent[2]==455)  /*couch*/
	      {
	      if (close_enough(10))
		{if (obj[188].loc==-2) {retsen=118; obj[188].loc=7;}
		 else retsen=117;
		}
	      else
		retsen=6;
	      }
	    if (sent[2]==404||sent[2]==406||sent[2]==394)  /*box*/
		{
		if (curloc==5&&obj[15].loc==5)
		  { if (spec[20]==1) retsen=134;
		    else {if (spec[20]==0) {retsen=999; putout("The package is closed.");}
			  else retsen=135;}
		  }
		}
	    break;
	  case 422:  /*earth id*/
	    if (sent[2]==424)
	      {if (obj[182].loc==-1||obj[182].loc==curloc) retsen=114;
	      else retsen=9;}
	    break;
	  case 432:
	  case 433:  /*keys*/
	    {if (obj[183].loc==-1||obj[183].loc==curloc) retsen=124;
	    else retsen=9;}
	  break;
	}  /*end branch on 2nd word*/
	break;
      case 4:  /*get*/
      case 19:
	if ((sent[1]==266||sent[1]==257) && (sent[2]==309||sent[2]==395)) gocar();
	if (sent[0]==4&&sent[1]==270&&
	    (sent[2]==309||sent[2]==395)) exitcar();
	if (sent[1]==266 && (sent[2]==303||sent[2]==304)) sleep();
	suminv();
/*	if (inv==9) retsen=129;
	else
	{   */
	tmpi=cmp_inv();
	switch(tmpi)
	  {
	  case 3:  gdisc(0);  break;
	  case 4:  gdisc(1);  break;
	  case 5:  gdisc(2);  break;
	  }
	/*}*/
	suminv();
	break;
      case 5:   /*drop*/
	tmpi=cmp_inv();
	switch(tmpi)
	  {
	  case 3:  ddisc(0);  break;
	  case 4:  ddisc(1);  break;
	  case 5:  ddisc(2);  break;
	  }
        suminv();
	break;
      case 24:
      case 27:   /*push-press*/
      switch(sent[1])  /*branch on 2nd word*/
	{
	case 344:  /*button*/
	  if (curloc==2)   /*if we are in the bedroom*/
	    {
	    if (close_enough(1))
	      {telpic++; if (telpic>94) telpic=90; retsen=27;}
	    else
	      retsen=6;		/*not close enough*/
	    }    /*end if curloc==2*/
	  else
	    {
	    if (curloc==62)  {elev();}
	    else
	      {
	      if (curloc==63||curloc==64||curloc==65) {inelev();}
	      else
		retsen=25;	/*not here.*/
	      }
	    }
	  break;
	}	/*end branch on 2nd word*/
      break;
      case 11:
      case 13:
      case 46: /*turn-switch-change*/
	switch(sent[1])  /*branch on 2nd word*/
	  {
	  case 263:  /*on*/
	    moveup(1);
	    switch(sent[1])  /*branch on 3rd word*/
	      {
	      case 326:
	      case 327:
	      case 339:
	      case 328:
	      case 340:  /*tv-television-radio-stereo-music*/
		if (curloc==7)   /*if we are in the tv room*/
		  {
		  if (spec[0]==0)     /*okay tv is off*/
		    {
		    spec[0]=1;
		    obj[slot*10+channel+30].loc=7;
		    retsen=5;
		    }
		  else
		    retsen=21;		/*tv is already on*/
		  }
		else
		  retsen=25; 		/*can't do that here*/
	      break;
	      case 397: /*translator*/
		if (obj[28].loc==-1) {if (spec[25]==1) retsen=21;
				      else {spec[25]=1; retsen=14;}}
		else {retsen=10;}
	      break;
	      }  /*end branch on 3rd word*/
	    break;
	  case 271:   /*off*/
	    moveup(1);
	    switch(sent[1])   /*branch on 3rd word*/
	      {
	      case 326:
	      case 327:
	      case 339:
	      case 328:
	      case 340:  /*tv-television-radio-stereo-music*/
		if (curloc==7)   /*if we are in the tv room*/
		  {
		  if (spec[0]==1)     /*okay tv is on*/
		    {
		    spec[0]=0;
		    obj[slot*10+channel+30].loc=-2;
		    retsen=5;
		    }
		  else
		    retsen=33;		/*tv is already off*/
		  }
		else
		  retsen=25; 		/*no tv here*/
	      break;
	      case 397: /*translator*/
		if (obj[28].loc==-1) {if (spec[25]==0) retsen=33;
				      else {spec[25]=0; retsen=14;}}
		else {retsen=10;}
	      break;
	      }  /*end branch on 3rd word*/
	    break;
	  case 349:
	  case 350:
	  case 351:
	  case 352:    /*channel...*/
	    switch(sent[2])   /*branch on 3rd word*/
	      {
	      tmpi=0;
	      case 48:
	      case 272:  /*backward*/
		tmpi=2;
		break;
	      case 273:   /*forward*/
		tmpi=1;
		break;
	      }  /*end branch on 3rd word*/
	    if (curloc==7)	/*if we are in tv room*/
	      {
	      if (spec[0]==1)   /*and tv is on*/
		{
		obj[slot*10+channel+30].loc=-2;	/*turn off old channel*/
		if (tmpi==2)
		  {channel--;
		  if(channel==-1) channel=9;
		  }
		else
		  {
		  channel++;
		  if (channel==10) channel=0;
		  }
		obj[slot*10+channel+30].loc=7;
		retsen=5;
		}    /*end if tv is on*/
	      else
		retsen=34;   /*tv is off*/
	      }	/*end if we are in tv room*/
	    else
	      retsen=25;
	    break;

	  }  /*end branch on 2nd word*/
      case 56:  /*go*/
	if (sent[1]==276 && (sent[2]==42||sent[2]==303||sent[2]==304))
	  sleep();
	  break;
      case 132:   /*throw*/
      case 133:
	 if ((sent[1]==386||sent[1]==387)&&
	 (sent[2]==266||sent[2]==270||sent[2]==274||
	   sent[2]==257||sent[2]==256))
	   throwout();
	 if ((sent[1]==266||sent[1]==270||sent[1]==274||
	 sent[1]==257||sent[1]==256)&&(sent[2]==386||sent[2]==387))
	   throwout();
	break;
      case 218:  /*who*/
	if (sent[1]==225 && sent[2]==239)  /*are you*/
	  retsen=75;
	if (sent[1]==226 && sent[2]==238)  /*am I*/
	  retsen=76;
	if (sent[1]==224 && sent[2]==248)  /*is this*/
	  retsen=76;
	if (sent[1]==224 && sent[2]==249)  /*is that*/
	  retsen=78;
	break;
      case 219:  /*what*/
        if (sent[1]==225 && sent[2]==239)  /*are you*/
	  retsen=93;
        if (sent[1]==226 && sent[2]==238)  /*am I*/
	  retsen=94;
        if (sent[1]==224 && sent[2]==248)  /*is this*/
	  retsen=77;
        if (sent[1]==224 && sent[2]==249)  /*is that*/
	  retsen=78;
	break;
      case 220:  /*where*/
        if (sent[1]==225 && sent[2]==239)  /*are you*/
	  retsen=74;
        if (sent[1]==226 && sent[2]==238)  /*am I*/
	  retsen=73;
        if (sent[1]==224 && sent[2]==248)  /*is this*/
	  retsen=73;
        if (sent[1]==224 && sent[2]==249)  /*is that*/
	  retsen=78;
	break;
      case 262:
	if (sent[1]==276&&sent[2]==443) retsen=133;
	break;
      case 238:
	if (sent[1]==43&&sent[2]==239) {retsen=999; putout("I love you too!");}
      }  /*end branch on 1st word*/
      break;
    default:   /*4+ words*/
	break;
  }  /*end branch on number of words in sent*/
}   /*end get_retsen (get return sentence)*/
}

give()
{
      if (sent[0]==134)  /*give*/
	{
	if (sent[1]==340||sent[1]==459||sent[1]==460||sent[1]==426||
	sent[1]==427||sent[1]==434||sent[1]==435||sent[1]==505||
	sent[1]==413||sent[1]==412||sent[1]==489||sent[1]==459||sent[1]==460)
	  {
	  if (curloc==66&&obj[184].loc==-1) {retsen=999; wdflag=5;
	    putout("Lee takes the music of the USA disk and thanks you profusely.");
	    obj[184].loc=-2;spec[24]++;}
	  else retsen=9;
	  }
	if (sent[1]==430||sent[1]==459||sent[1]==460||sent[1]==426||
	sent[1]==427||sent[1]==434||sent[1]==435||sent[1]==492||
	sent[1]==493||sent[1]==413||sent[1]==412||sent[1]==459||sent[1]==460)
	  {
	  if (curloc==68&&obj[186].loc==-1) {retsen=999;
	    putout("Professor Godless takes the History of Earth disk and thanks you very much.");
	    obj[186].loc=-2;spec[24]++;}
	  else retsen=9;
	  }
	if (sent[1]==417||sent[1]==420||((sent[2]==420||sent[2]==417)&&
	(sent[1]==494||sent[1]==481||sent[1]==413||sent[1]==412||
	sent[1]==429)))
	  {
	  if (curloc==70&&obj[172].loc==-1) {retsen=999;
            putout("Tom takes the seeds from you and is very excited to keep a species of plant living.");
	    obj[172].loc=-2;spec[24]++;}
	  else retsen=9;
	  }
	if (sent[1]==418||sent[1]==421||((sent[2]==421||sent[2]==418)&&
	(sent[1]==494||sent[1]==481||sent[1]==413||sent[1]==412||
	sent[1]==429)))
	  {
	  if (curloc==70&&obj[173].loc==-1) {retsen=999;
            putout("Tom takes the spores from you and is very happy to keep a special species of mushroom alive.");
	    obj[173].loc=-2;spec[24]++;}
	  else retsen=9;
	  }
	if (sent[1]==428||sent[1]==459||sent[1]==460||sent[1]==426||
	sent[1]==427||sent[1]==434||sent[1]==435||sent[1]==491||
	sent[1]==490||sent[1]==413||sent[1]==412||sent[1]==429||
	sent[1]==459||sent[1]==460)
	  {
	  if (curloc==73&&obj[185].loc==-1)
	    {
	    if (spec[24]==4)
	       {spec[24]++; givemed();}
	    else
	      {retsen=999;
	    putout("Professor Sagan takes the Encylopedia Galactica disk and looks impatiently at you.");
	      obj[185].loc=-2;spec[24]++;}
	    }
	  else retsen=9;
	  }
	}
	if (sent[0]==12&&(sent[1]==461||sent[1]==462)&&sent[2]==298)
	  poison();
}

givemed()
{
retsen=999;
if (curloc==73&&spec[24]!=5) putout("Sagan talks about life on other planets around the billions of other suns in the universe.");
if (curloc3==73&&spec[24]==5)
  {
  putout("Professor Sagan says:  'You have done an excellent job.  You have secured the robot here on the moon.  In room C3 there is a shuttle which will take you to the General's private ship. Take this cyanide and put it in his water supply.");
  spec[24]=6; obj[251].loc=-1; obj[185].loc=-2;
  }
if (curloc3!=73&&spec[24]==5)
  putout("Professor Sagan says, 'You have done an excellent job bringing everything here from earth, but you don't have the robot!'");

}

poison()
{
if (curloc==80)
  {
  if (obj[251].loc==-1)
    {
    retsen=999;
    putout("You put the tranquilizer in the General's water supply. The General human is captured. The General human had killed other humans by hand and will be in a jail until dead. You then take the shuttle back to Moon Port 3. You are most popular and rewarded with a million earth dollars!");
    endcred();
    }
  }
else
  retsen=9;
}

endcred()
{
putout("That's the end of the game! I hope you enjoyed playing it.  I had fun making it.");
putout("When I began writing this program in early 1993 I had no idea it would take me this long.");
putout("It's now April 1996.  In that time I saw other games like DOOM and MYST come out which completely blow the graphics of this game away.");
putout("When I first saw DOOM, I really thought that this game sucked in comparison.");
putout("What 2020 does have are some pretty interesting, intelligent ideas and concepts.");
putout("I think it has a more realistic vision of our future than most stories.");
putout("Just as importantly, 2020 helps people understand that all words have meaning and should NEVER be censored.");
putout("Finally, I also think that the choice of character, defining different skin, hair, etc... traits helps everyone understand that people look different from each other and that it's ok to talk about!");
putout("I strongly urge you to support space exploration (to other suns), the development of the moon and mars. It is also very important to vote for people who will give us humans the right to our own body.");
putout("The right to your own body, means abolishing the current laws prohibiting possession and use of drugs, the sale of sex, any and all pictures or information about anything, and suicide.");
putout("These may not be things you read, or hear about too often, but it is clearly the correct path to a tolerant, peaceful, conscious civilization.  Let us eliminate violence.");
qflg=1; putout("Play Again (Y/N)?");
}

throwout()
{
int c;

	    if (curloc==53)
	       { for (c=131;c<140;c++)
		   {if (obj[c].loc==-1)
		     {
		     if (close_enough(140))
		       {
		       obj[c].loc=-3;
		       retsen=14;
		       }
		     else retsen=6;
		     }
		   }
	       if (retsen==0) retsen=8;
	       }
	     else retsen=9;

}

godrive()
{
if (spec[1]!=3) {retsen=999;  if (retsen==998) putout("You are not in a vehicle.");
		else putout("Just walk there.");}
else
  {
  if (curloc==56)  {retsen=999;putout("You're out of gas!");}
   else
    {
     if (obj[234].loc==32)
	{
	  retsen=999;  putout("It refuses to go because the car door is still open.");
	  }
	else
	{
	if (sent[1]==447||sent[1]==449||sent[1]==450)
	   {retsen=999;
	   putout("You were caught and arrested.  Nice going.");
	   dead();
	   }
	else
	  {
	  if (sent[1]==448||sent[1]==439)
	    if (obj[234].loc==32)
	       {
	       retsen=999;  putout("It refuses to go because the car door is still open.");
		}
	    else
	      {retsen=999; putout("You drive south."); newloc=55;refresh(); spec[22]=1;
	    }
	  }
	}
      }
    }
    if (retsen==998) retsen=999;
}
sleep()
{
if (curloc==2) {
  spec[1]=2; obj[7].loc=2;  erase_char();  retsen=5;}
else retsen=9;
}

buyticket()
{
retsen=999;
if (curloc!=57)
  putout("How?");
else
{
if (cash0==1000)
  {
  if (close_enough(239)) {  if (spec[25]==1&&obj[28].loc==-1) {
		putout("You: I want to buy a ticket to the moon.");
		putout("Translator: Yo quiero comprar un billete a la luna.");
		putout("Woman:  Bueno.  ­Muchas graci s!");
		putout("Translator: Good. Thank you very much!");
		putout("You buy a ticket to the moon.");
		zeromon();obj[237].loc=-2; refresh();}
		else
		  {retsen=999;putout("You don't speak Spanish and cannot communicate with the woman."); }
   }
  else
    {
    if (close_enough(238))
      {		if (spec[25]==1&&obj[28].loc==-1) {
		putout("You: I want to buy a ticket.");
		putout("Translator: Yo quiero comprar un billete.");
		putout("Man:  Bueno.  ­Muchas graci s!");
		putout("Translator: Good. Thank you very much!");
		putout("You buy a ticket to the USA.");
		zeromon();obj[236].loc=-2;refresh();}
		else
		  {retsen=999;putout("You don't speak Spanish and cannot communicate with the man."); }
      }
    else
      retsen=6;
    }
  }
else
  {if (cash>0) putout("You don't have enough earth dollars.");
   else
     {
     if (cash0==0) putout("You don't have any money!");
     else putout("You don't have enough money!");
     }
   }
}
}

zeromon()
{
int lcn;

cash0=0;
obj[180].loc=-2;
obj[181].loc=-2;
for (lcn=187;lcn<233;lcn++)
  obj[lcn].loc=-2;
}

dial()
{
if (curloc!=6) retsen=9;
else
  {
  retsen=999;
  switch(sent[1])
    {
    case 240:  putout("Good Blondie tune.");
    break;
    case 247:  putout("There is no god, one or more humans made the word god.");
               putout("The sound for the letter o goes back to before the time of the hieroglyphs in egypt.");
               putout("Most humans in Egypt thought that there were gods named Horus and Aman.");
               putout("There are no gods, devils, heavens, hells, spirits, ghosts, witches. There are photons, and I think that photons are matter.");
    break;
    case 498:
    case 527:
    case 528:
      putout("Do you want to get busted?!!??!  I thought no!");
      break;
    case 403:
      putout("You have never seen her number.");
      break;
    case 439:
    case 446:
      putout("You have never seen that number.");
      break;
    case 482:
    case 502:
      putout("Good luck.");
      break;
    case 481:
    case 487:
    case 500:
    case 501:
    case 505:
      putout("Some body touch Ted before I die.");
      break;
    case 495:
      putout("There is a busy signal.");
    break;
    case 496:
      putout("You buy some new age music.");  obj[180].loc=-2; if (cash>100) cash-=100;
    break;
    case 497:
      putout("The General thanks you for coming to your senses and wants you to report to him on the White House Lawn at 0800 hours.");
    break;
    case 506:  putout("Andy Adams says, 'hey human build a robot.'");
      break;
    case 513:
    case 514:
      putout("Jack Williams says, 'Make your own drink!'");
      break;
    default:
      putout("Dial, call, enough already.  Contain the humans that cause damage with intent, no consent and not in defense of a primate.  Let all other humans that have not caused damage to other bodies free.");
      putout("Show the brain image and sound machines. Science good. Religion bad. Go to other planets, moons, and stars. Touch might be good! If sex with consent and pleasure are good, why no ads for sex with consent?");
      putout("How can using drugs be more bad than causing damage?  Where is the machine that can hear thoughts?  When is touch and sex with consent going to be promoted?");
      break;
    }
  }
}

hint()
{
retsen=999;
switch(curloc)
  {
  case 1:  putout("Look under the rug."); break;
  case 2:  putout("You can sleep to pass time away.  The robot can help collect the stock.  Open the desk drawer."); break;
  case 4:  putout("You can shower to elapse 10 minutes of time."); break;
  case 5:  putout("Open the package and type 'follow' for the robot to follow you."); break;
  case 6:  putout("Answer your phone messages."); break;
  case 7:  putout("Look in the couch.  Watch the tv for information."); break;
  case 8:  putout("The middle key on the number pad will stop you. It's time you started using the number pad. Wait for the right time to cross."); break;
  case 12:
  case 13:
  case 14:
  case 15:
    putout("Deliver the packages to the correct apartments.");
     break;
  case 32:
    putout("Drive south to the border of Mexico.  Make sure you have $1000 earth dollars, your ID, and translator.");
    break;
  case 33:
  case 34:
    putout("One of these cars is yours.  Use the key to open the door of your car.");
    break;
  case 40:  putout("Ask the clerk for a job.");
     break;
  case 41:  putout("Say the password Tom gives you in his video message.");
     break;
  case 45:
  case 49:
  case 50:
  case 51:
  case 52:
  case 53:
    putout("Pick up the trash and put it in the trash can.");
    break;
  case 44:
    putout("Get each of the three disks you need to bring to the Moon.");
    break;
  case 46:
    putout("Get a job from the clerk, if you know what I mean.");
    break;
  case 47:
    putout("Sell or insert your stock into the machine.");
    break;
  case 48:
    putout("Insert your money into the currency machine.");
    break;
  case 57:
    putout("Buy a ticket from on eof the clerks. Make sure the translator is on.");
    break;
  case 58:
  case 59:
    putout("Pick a door.");
    break;
  case 62:
    putout("Push the button.");
    break;
  case 63:
  case 64:
  case 65:
    putout("Push button 0,1,2 or 3.");
    break;
  case 66:
    putout("Give the music of the usa disk to Lee.  duh.");
    break;
  case 68:
    putout("Give the History of the Earth disk to Professor Godless.");
    break;
  case 70:
    putout("Give the seeds and the spores to Tommy bub.");
    break;
  case 73:
    putout("Give the encyclopedia galactica to Carl, and talk to him after returning the other items.");
    break;
  case 76:
    putout("Pick the right door.  I'm not telling you which one. We've gone too far together to turn back now.");
    break;
  case 80:
    putout("You need to put some poison in the General's water, so when he drinks his coffee (every 10 minutes), he will die.");
    break;
  default:
      putout("No hint needed here se¤ora.");  break;
  }
}

lpeople()
{
retsen=999;
switch(curloc)
  {
  case 41:  putout("Mom looks like a force to be reckoned with."); break;
  case 46:
  case 40:  putout("The clerk looks nice enough."); break;
  case 66:  putout("Lee looks comfortable."); break;
  case 68:  putout("He's huge!  My art skills are... well ...getting better."); break;
  case 70:  putout("Tom and Tracy are just relaxing on the sofa."); break;
  case 73:  putout("Sagan looks suspiciously like my father.  But other than that, he looks like a wisened old owl, who would never condone killing another human, no matter how evil."); break;
  default: putout("They ain't no people here.");
  }
}
