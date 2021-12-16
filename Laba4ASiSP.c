#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int N = 0;
int currentChildID = 0;

void ParentGetsSignal(int sig)
{
    printf("#%d %d Parent gets SIGUSR2 from Child%d\n", ++N, getpid(), currentChildID);
}
void Child1GetsSignal(int sig)
{
    printf("#%d %d Child1 gets SIGUSR1\n", ++N, getpid());
}
void Child2GetsSignal(int sig)
{
    printf("#%d %d Child2 gets SIGUSR1\n", ++N, getpid());
}
void ParentPutsSignal(int childNumber)
{
    printf("#%d %d Parent puts SIGUSR1 for Child%d\n", ++N, getpid(), childNumber);
}
void Child1PutsSignal()
{
    printf("#%d %d Child1 puts SIGUSR2\n", ++N, getpid());
}
void Child2PutsSignal()
{
    printf("#%d %d Child2 puts SIGUSR2\n", ++N, getpid());
}
void Exit(int s)
{
    exit(0);
}

void main()
{
    pid_t parent, child1, child2;
    static struct sigaction parentAction, child1Action, child2Action;

    child1 = fork();
    if (child1 == 0)
    {
        child1Action.sa_handler = Child1GetsSignal;
        sigaction(SIGUSR1, &child1Action, NULL);

        child1Action.sa_handler = Exit;
        sigaction(SIGINT, &child1Action, NULL);

        parent = getppid();
        for (;;)
        {
            sleep(1);
            Child1PutsSignal();
            kill(parent, SIGUSR2);
            pause();
        }
    }
    else
    {
        child2 = fork();
        if (child2 == 0)
        {
            child2Action.sa_handler = Child2GetsSignal;
            sigaction(SIGUSR1, &child2Action, NULL);

            child2Action.sa_handler = Exit;
            sigaction(SIGINT, &child2Action, NULL);

            parent = getppid();
            for (;;)
            {
                sleep(1);
                Child2PutsSignal;
                kill(parent, SIGUSR2);
                pause();
            }
        }
        else if (parent = fork())
        {
            parentAction.sa_handler = ParentGetsSignal;
            sigaction(SIGUSR2, &parentAction, NULL);

            parentAction.sa_handler = Exit;
            sigaction(SIGINT, &parentAction, NULL);

            for (;;)
            {
                currentChildID = 1;
                ParentPutsSignal(1);
                kill(child1, SIGUSR1);
                pause();

                currentChildID = 2;
                ParentPutsSignal(2);
                kill(child2, SIGUSR1);
                pause();
            }
        }
    }
}
