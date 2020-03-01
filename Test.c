#include "stdlib.h"
main()
{
float cash;
char str[100],str2[100];
int cha;

cash=100.95;
itoa((int)cash,str,10);
cha=(int) cash*100;
cha=cha-(int)cash;
/*strcpy(str,fcvt(cash,0,2,0));*/
strcat(str,".");
strcpy(str,fcvt(cash*100,0,2,0));
printf("%s",str);

}