/*proaudio card?*/

main()
{
char ch1;

clrscr();
printf("Do you have a Pro Audio Spectrum Card installed (Y/N)?");
ch1=getche();

if (ch1!='n'&&ch1!='N')
  system("0.bat");
system("game.exe");
}