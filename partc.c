#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    //general validility check
    if (argc != 2) {
        printf("USAGE: partc FILEIN\n");
        return 1;
    }

    //pipe error check
    int pipeFD[2];
    if (pipe(pipeFD) == -1) {
        perror("pipe");
        return 2;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 3;
    }

    if (pid > 0) { //PARENT
        //close read part of pipe
        close(pipeFD[0]);

        //redirect stdout to the write pipe
        //pun intended
        if (dup2(pipeFD[1], STDOUT_FILENO) == -1) {
            perror("dup2 (parent)");
            return 4;
        }
        //no need for this FD, close it
        close(pipeFD[1]);

        //execute parta
        char *parta_args[] = {"./parta", argv[1], NULL};
        execv("./parta", parta_args);

        // if failed:
        perror("execv (parta)");
        exit(5);
    } else { //CHILD
        //close write part of pipe
        close(pipeFD[1]);

        //redirect to read part
        if (dup2(pipeFD[0], STDIN_FILENO) == -1) {
            perror("dup2 (child)");
            return 6;
        }
        //no need for FD anymore
        close(pipeFD[0]);

        //execute the sort
        execlp("sort", "sort", "-t", "-k2", "-n", NULL);

        //if execlp fails
        perror("execlp (sort)");
        exit(7);
    }

    //parent must wait for child
    wait(NULL);

    return 0;
}
