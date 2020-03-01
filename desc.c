/*  desc.c   */
/*  descriptions for 2020!   */
/*  by Ted Huntington  */

#define TVC 100
#include <string.h>
#include "2020.h"
extern char des[DESC1][DESC2];  /*228*/
extern spec[NUMSPEC];

desc()
{
strcpy(des[0],"You are in your apartment. There is a fireplace here. Above the fireplace, some japanese statues rest on a shelf. A rug sits in front of the fireplace.");
strcpy(des[1],"You are in your bedroom. A telescope points out a large oval window. In the distance you see the city. A waterbed is in the corner of the room and a desk sits next to the bed.");
strcpy(des[2],"You see the moon. A transport is making its approach. You can clearly see 'the bubbles', which are the human settlements. Solar panels and land-ing sites are also visible.");
strcpy(des[3],"You are in your bathroom. A shower, equipped with a seat, sits next to the dual toilet. On the left wall is the sink, mirror and towel rack.");
strcpy(des[4],"You are in the hallway of your apartment. Exits are on every wall. Your front door is on the back wall.");
strcpy(des[5],"You are in the kitchen. A table and chairs sit in the middle of the room. A sink and cupboards are on the front wall. A videophone also hangs on the front wall. A stove, oven, refridgerator, and freezer are on the left wall.");
strcpy(des[6],"You are in the  entertainment room. Two couches are here. On the front wall hangs your interactive tv/stereo. A large window is on the right wall.");
strcpy(des[7],"You are out in the street. The door leads into your apartment.");
strcpy(des[8],"You are out in the street.");
strcpy(des[9],"You are out in the street.");
strcpy(des[10],"You are out in the street.");
strcpy(des[11],"You are out in the street.  Apartments number 1 and 2 are here.");
strcpy(des[12],"You are out in the street.  Apartments number 3 and 4 are here.");
strcpy(des[13],"You are out in the street.  Apartments number 5 and 6 are here.");
strcpy(des[14],"You are out in the street.  Apartments number 7 and 8 are here.");
strcpy(des[15],"You are out in the street.");
strcpy(des[16],"You are out in the street.");
strcpy(des[17],"You are out in the street.");
strcpy(des[18],"You are out in the street.  Mom's Cafe is here.");
strcpy(des[19],"You are out in the street.");
strcpy(des[20],"You are out in the street.");
strcpy(des[21],"You are out in the street.  The Free Press is here.");
strcpy(des[22],"You are out in the street.");
strcpy(des[23],"You are out in the street.  The government job office is here.");
strcpy(des[24],"You are out in the street.");
strcpy(des[25],"You are out in the street.  The park entrance is here.");
strcpy(des[26],"You are out in the street.  The park is here.");
strcpy(des[27],"You are out in the street.  The park is here.");
strcpy(des[28],"You are out in the street.");
strcpy(des[29],"You are out in the street.  The library entrance is here.");
strcpy(des[30],"You are out in the street.");
strcpy(des[31],"You are out in the street.  There are parked cars here.");
strcpy(des[32],"You are out in the street.  There are parked cars here.");
strcpy(des[33],"You are out in the street.  There are parked cars here.");
strcpy(des[34],"You are out in the street.");
strcpy(des[35],"You are out in the street.  The currency exchange is here.");
strcpy(des[36],"You are out in the street.");
strcpy(des[37],"You are out in the street.  The stock exchange is here.");
strcpy(des[38],"You are out in the street.");
strcpy(des[39],"You are in the package delivery building.  A clerk is here behind the counter.");
strcpy(des[40],"You are in Mom's Cafe.  Mom is here.");
strcpy(des[41],"You are lost on the boulevard of broken dreams.");
strcpy(des[42],"You are lost on the boulevard of broken dreams.");
strcpy(des[43],"You are in the library.  A machine here dispenses books and disks.");
strcpy(des[44],"You are in the park.");
strcpy(des[45],"You are in the government job office.");
strcpy(des[46],"You are in the stock exchange building.");
strcpy(des[47],"You are in the currency exchange building.");
strcpy(des[48],"You are in the park.");
strcpy(des[49],"You are in the park.");
strcpy(des[50],"You are in the park.");
strcpy(des[51],"You are in the park.");
strcpy(des[52],"You are in the park.  A garbage can is here.");
strcpy(des[53],"You are in the back room at Mom's Cafe.");
strcpy(des[54],"You are at the border between the countries of the USA and Mexico.");
strcpy(des[55],"You are at the Mexican air and space port.");
strcpy(des[56],"You are in the Mexican air and space port.");
strcpy(des[57],"You are in the moon part of the air and space port.");
strcpy(des[58],"You are in the earth part of the air and space port.");
strcpy(des[59],"You are on your way to the moon.");
strcpy(des[60],"You are captured.");
strcpy(des[61],"You are at Moon Port 3, Level 0. There are three elevators here.");
strcpy(des[62],"You are in elevator A.");
strcpy(des[63],"You are in elevator B.");
strcpy(des[64],"You are in elevator C.");
strcpy(des[65],"You are in room A1.");
strcpy(des[66],"You are in room A2.");
strcpy(des[67],"You are in room A3. A man is here.");
strcpy(des[68],"You are in room B1.");
strcpy(des[69],"You are in room B2.");
strcpy(des[70],"You are in room B3.");
strcpy(des[71],"You are in room C1.");
strcpy(des[72],"You are in room C2.");
strcpy(des[73],"You are in room C3.");
strcpy(des[74],"You are docking with the General's ship.");
strcpy(des[75],"You are inside the General's ship.  There are four doors here.");
strcpy(des[76],"You have been caught by the general.");
strcpy(des[77],"You are in an empty room.");
strcpy(des[78],"You are in an empty room.");
strcpy(des[79],"You are in the main supply room.  There are ports for for food, water, and air input.");
strcpy(des[90],"You see the moon. A transport is making its approach. You can clearly see 'the bubbles', which are the human settlements. Solar panels and landing sites are also visible.");
strcpy(des[91],"You see Mercury.");
strcpy(des[92],"You see Venus.");
strcpy(des[93],"You see Mars.");
strcpy(des[94],"You see Jupiter.");
strcpy(des[TVC],"Public news channel:          All day coverage of the coup.");
strcpy(des[TVC+1],
"Space channel:                The first nuclear explosion in space took place near Jupiter in 1998.");
strcpy(des[TVC+2],"Science channel:              The military has developed robots that can walk and shoot.");
strcpy(des[TVC+3],"Music channel:                Tribute to John Lennon.");
strcpy(des[TVC+4],"Comedy channel:               Tribute to Second City Television.");
strcpy(des[TVC+5],"Military channel:             Nude channel out of service.");
strcpy(des[TVC+6],"Business channel:             Vej vegetarian fast food stock splits.");
strcpy(des[TVC+7],"Public news channel:          The coup plotters appear to be three Generals. Generals Smith and Worth are under the direction of General Collins.");
strcpy(des[TVC+8],"Moon channel:                 President Sagan reports on coup from the moon.");
strcpy(des[TVC+9],"Public Access channel:        Native American for native rule.");
strcpy(des[TVC+10],"Public news channel:          Commentary on the fate of the USA.");
strcpy(des[TVC+11],
"Space channel:                Launched in 1998, Orion is the first vessel to leave earth destined to reach nearby Barnard solar system in the year 2050. The ship uses atomic explosions to propel itself.");
strcpy(des[TVC+12],"Science channel:              The military has developed automatic guns that can be programmed to move and shoot." );
strcpy(des[TVC+13],"Music channel:                Tribute to Jimi Hendrix.");
strcpy(des[TVC+14],"Comedy channel:               Tribute to Woody Allen.");
strcpy(des[TVC+15],"Military channel:             Nude channel out of service.");
strcpy(des[TVC+16],"Business channel:             US Bond plunges after short period of unexpected highs.");
strcpy(des[TVC+17],"Public news channel:          Weather update.");
strcpy(des[TVC+18],"Moon channel:                 Moon Station 3. The largest of the 3 Moon Stations.");
strcpy(des[TVC+19],"Public Access channel:        Oriental American for oriental rule.");
strcpy(des[TVC+20],"Public news channel:          The United Nations has seized control of all major USA borders.");
strcpy(des[TVC+21],"Space channel:                Robots on Mars are  constructing the first Mars Station.");
strcpy(des[TVC+22],"Science channel:              The military maintains an Ocean Station off the South California coast. It's exact location is unknown.");
strcpy(des[TVC+23],"Music channel:                Tribute to Jim Morrison.");
strcpy(des[TVC+24],"Comedy channel:               Tribute to Sigmond Freud.");
strcpy(des[TVC+25],"Military channel:             Nude channel out of service.");
strcpy(des[TVC+26],"Business channel:             Market still steadily rising mainly due to the former President's income tax reductions, and right to body reform.");
strcpy(des[TVC+27],"Public news channel:          Reporting from the Capital.");
strcpy(des[TVC+28],"Moon channel:                 Moon Station 3. Lunar transports from Canada and Mexico are still running on schedule although heavily crowded with people leaving earth.");
strcpy(des[TVC+29],"Public Access channel:        Pink American for pink rule.");
strcpy(des[TVC+30],"Public news channel:          The United Nations has seized control of all major USA borders.");
strcpy(des[TVC+31],"Space channel:                The Barnard solar system was first seen clearly from starship Orion. As predicted Barnard has two large Jovian-like planets, each with their own satellites.");
strcpy(des[TVC+32],"Science channel:              Chaos theory has  given every-one a chance to visualize non-linear equations. First seen by Benoit Mendelbrot.");
strcpy(des[TVC+33],"Music channel:                Tribute to Frederic Chopin.");
strcpy(des[TVC+34],"Comedy channel:               Tribute to Saturday Night Live, and David Letterman.");
strcpy(des[TVC+35],"Military channel:             Nude channel out of service.");
strcpy(des[TVC+36],"Business channel:             Market still steadily rising mainly due to the former President's income tax reductions.");
strcpy(des[TVC+37],"Public news channel:          These are the top four violent criminals still at large on earth.");
strcpy(des[TVC+38],"Moon channel:                 Inside Moon Station 3.");
strcpy(des[TVC+39],"Public Access:                Brown American for brown rule.");
strcpy(des[TVC+40],"Public news channel:          Plea from Canada.");
strcpy(des[TVC+41],"Space channel:                A black hole remains after the death of a sun 3 times more massive than our own.");
strcpy(des[TVC+42],"Science channel:              Fractals offer a way to look at natural structures in the universe.");
strcpy(des[TVC+43],"Music channel:                Tribute to Lenny Kravitz and the Beastie Boys.");
strcpy(des[TVC+44],"Comedy channel:               Tribute to Richard Pryor.");
strcpy(des[TVC+45],"Military channel:             Nude channel out of service.");
strcpy(des[TVC+46],"Business channel:             Helicopter Inc. still boasting large profits.");
strcpy(des[TVC+47],"Public news channel:          Plea from Canada.");
/*strcpy(des[TVC+47],"Public news channel:          The military has closed all drug outlets and public libraries.");*/
/*strcpy(des[TVC+47],"Public news channel:          Police are arresting political prisoners.");*/
strcpy(des[TVC+48],"Moon channel:                 Inside Moon Station 3");
strcpy(des[TVC+49],"Public Access channel:        Get Real Program.");
strcpy(des[TVC+50],"Public news channel:          Plea from England.");
strcpy(des[TVC+51],"Space channel:                A supernova, the brilliant death of a sun 1 and 1/2 times more massive than our own.");
strcpy(des[TVC+52],"Science channel:              Simulation of a ship powered by Hydrogen to Helium fusion.");
strcpy(des[TVC+53],"Music channel:                Tribute to Ted Huntington.");
strcpy(des[TVC+54],"Comedy channel:               Tribute to Dennis Miller.");
strcpy(des[TVC+55],"Military channel:             Touch with consent channel out of service.");
strcpy(des[TVC+56],"Business channel:             Sex Inc. shutdown by USA military government.");
strcpy(des[TVC+57],"Public news channel:          Plea from England.");
strcpy(des[TVC+58],"Moon channel:                 Military Space Station occupied by General Collins.");
strcpy(des[TVC+59],"Public Access channel:        Police Video Show (rerun).");
strcpy(des[TVC+60],"Public news channel:          Plea from Mexico.");
strcpy(des[TVC+61],"Space channel:                Tau Ceti, a yellow sun 11.9 light years away was found to have at least 7 planets, two of which may sustain life.");
strcpy(des[TVC+62],"Science channel:              Tribute to Albert Einstein.");
strcpy(des[TVC+63],"Music channel:                Tribute to the music of the 1960's.");
strcpy(des[TVC+64],"Comedy channel:               Tribute to the Kids in the Hall.");
strcpy(des[TVC+65],"Military channel:             Nude channel out of service.");
strcpy(des[TVC+66],"Business channel:             Global Trade shutdown by USA military government.");
strcpy(des[TVC+67],"Public news channel:          Plea from Japan.");
strcpy(des[TVC+68],"Moon channel:                 Contain bodies that cause damage");
strcpy(des[TVC+69],"Public Access channel:        Free bodies that have not caused damage Show.");
/*strcpy(des[TVC+67],"Public news channel:          Most popular humans in the United Nations support containing humans damaging in the USA.");*/
}

story()
{
char t0[300];

strcpy(t0,"In the year 2020, a good man was elected President of the United States of America.");
strcat(t0," He was killed in 2020 by three violent generals and their elite army. Before being");
strcat(t0," killed he made some radical changes for the country, including the release of all nonviolent");
spec[6]=0;
putout(t0);
strcpy(t0,"humans from prisons and hospitals, stopped all arrests for nudity, drugs, and other nonviolent movements. Other");
strcat(t0," changes included earth laws with constant democratic vote,");
strcat(t0," sending  a ship to a different star, and growing life on planet mars and the moon of earth.");
putout(t0);
strcpy(t0,"At the time of his death President Huntington owned");
strcat(t0," an extremely intelligent, highly dexterous walking robot.  You are a human born from President Huntington");
strcat(t0," and are in serious danger. You must avoid the general's army, find the most popular ");
putout(t0);
strcpy(t0,"intellectual humans on earth, secure the robot, and restore truth, science, pleasure and democracy to the USA and planet earth.");
putout(t0);
}

menu()
{
char t0[300];

strcpy(t0,"The Story   ");
strcat(t0,"Instructions");
strcat(t0,"New Game    ");
strcat(t0,"Save Game   ");
strcat(t0,"Restore Game");
strcat(t0,"Quit        ");
strcat(t0,"Back to game");
spec[6]=2;
putout(t0);
spec[6]=0;
}

help()
{
char t0[300];

strcpy(t0,"ESC Quit                  ");
strcat(t0,"TAB Inventory             ");
strcat(t0,"F1 Main Menu              ");
strcat(t0,"F2 Save Game              ");
strcat(t0,"F3 Repeat last command    ");
strcat(t0,"F4 Restore Game           ");
strcat(t0,"F5 Hint                   ");

strcat(t0,"F10 Change game speed     ");

spec[6]=1;
putout(t0);
#ifdef Linux
strcpy(t0,"                          ");
#endif
#ifdef DOS
strcpy(t0,"For windows, play in full ");
strcat(t0,"window.  Press alt-enter. ");
#endif
strcat(t0,"                          ");
strcat(t0,"Movement:                 ");
strcat(t0,"arrow keys Move human     ");
strcat(t0,"press arrow key again to  ");
strcat(t0,"stop human                ");
#ifdef Linux
strcat(t0,"] human moves more fast   ");
strcat(t0,"[ human moves less fast   ");
#endif
#ifdef DOS
strcat(t0,"+ human moves more fast   ");
strcat(t0,"- human moves less fast   ");
#endif
putout(t0);
strcpy(t0,"Type in words followed by ");
strcat(t0,"the <Enter> key.  For     ");
strcat(t0,"example, 'look',          ");
strcat(t0,"'open desk', 'get the key'");
strcat(t0,"'look in telescope',      ");
strcat(t0,"'time', any words you want");
putout(t0);

spec[6]=0;
}
