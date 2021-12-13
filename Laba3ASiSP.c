

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <time.h>

void DO(){
		sleep(1);
		int N,Pid,Tm,Ts;
		time_t T = time(NULL);
		struct tm tm = *localtime(&T);	
		FILE* f;		
				f=fopen("text.txt","r");			

		for(int i =1;i<=4;i++){
		
				fscanf(f,"%d %d %d %d",&N,&Pid,&Tm,&Ts);
			printf("%d %d %d %d %d %d\n",N,getpid(),Tm,Ts,tm.tm_min,tm.tm_sec );
			
		}
				fclose(f);

}
int main(int argc, char **argv)
{
	pid_t pid;
	if((pid=fork())==0){//daczczynny1
		DO();
		printf("daczynny1 %d\n",getpid());
	}else if(pid!=-1){//bacjkouski
			if((pid=fork())==0){//daczczynny2
				DO();
				printf("daczynny2 %d\n",getpid());
			}else if(pid!=-1){//bacjkouski
				if((pid=fork())==0){//daczczynny3
					DO();
					printf("daczynny3 %d\n",getpid());
				}else if(pid!=-1){//bacjkouski
						if((pid=fork())==0){//daczczynny4
							DO();
							printf("daczynny4 %d\n",getpid());
						}else if(pid!=-1){//bacjkouski
							char ch[100]="";
							FILE* f=fopen("text.txt","w");
							for(int i=1;i<=4;i++){
								
								
								time_t T = time(NULL);
								struct tm tm = *localtime(&T);
								sprintf(ch,"%d %d %d %d\n",i,pid,tm.tm_min,tm.tm_sec);
								fprintf(f,"%s",ch);
								printf("%s",ch);
							}
							printf("bacjkouski %d\n",pid);
							fclose(f);
							
							
						}
				}
			}
	}
	wait((int*)0);
	return 0;
}

