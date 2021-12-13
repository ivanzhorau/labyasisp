
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
int main(int argc, char **argv)
{
	char *a = argv[1];
	if (argc == 1)
		a = "/";
    printf("%d %s\n",argc, a);
		
	DIR *dir = opendir(a);
	struct dirent *entry;
	if(dir!=NULL){
		while( (entry=readdir(dir)) )
		{
        
        printf(" %s\n",entry->d_name);
		}
	}
	closedir(dir);
	return 0;
}

