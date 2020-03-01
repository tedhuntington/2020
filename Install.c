/*install.c - installs 2020 on hard disk*/
#include "dir.h"

main()
{
int ret;

/*ret=system("mkdir c:\2020");
if (ret<0) err();
ret=system("mkdir c:\2020\objects");
if (ret<0) err();
ret=system("mkdir c:\2020\locs");
if (ret<0) err();
ret=system("mkdir c:\2020\cast");
if (ret<0) err();
system("copy a:*.* c:\2020\*.*");
system("a:");
system("cd locs");
system("copy a:*.* c:\2020\locs\*.*");*/
system("a:");
system("cd ..");
system("cd objects");
system("copy a:*.* c:\2020\objects\*.*");
system("cd ..");
system("cd cast");
system("copy a:*.* c:\2020\cast\*.*");
printf("Installation to C: drive complete.\n");
}

err()
{
printf("error!\n");
exit(0);
}