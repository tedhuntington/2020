#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"

main()
{
wr();
rd();
}

rd()
{
FILE *fptr;
char name[28];

fptr=fopen("sav.gam","rb");
fread(&name,sizeof(name),1,fptr);
printf("%s\n",name);
fread(&name,sizeof(name),1,fptr);
printf("%s\n",name);
fclose(fptr);
}

wr()
{
FILE *fptr;
char name[26];

fptr=fopen("sav.gam","wb");
strcpy(name,"Save game name 1           ");
fwrite(&name,sizeof(name),1,fptr);
strcpy(name,"Save game name 2           ");
fwrite(&name,sizeof(name),1,fptr);
strcpy(name,"Save game name 3           ");
fwrite(&name,sizeof(name),1,fptr);
strcpy(name,"Save game name 4           ");
fwrite(&name,sizeof(name),1,fptr);
strcpy(name,"Save game name 5           ");
fwrite(&name,sizeof(name),1,fptr);
strcpy(name,"Save game name 6           ");
fwrite(&name,sizeof(name),1,fptr);
strcpy(name,"Save game name 7           ");
fwrite(&name,sizeof(name),1,fptr);
strcpy(name,"Save game name 8           ");
fwrite(&name,sizeof(name),1,fptr);
strcpy(name,"Save game name 9           ");
fwrite(&name,sizeof(name),1,fptr);
fclose(fptr);
}