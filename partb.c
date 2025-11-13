#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    //check for suplied arguments
    if (argc != 3) {
        printf("USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    //for naming purposes
    char *input_filename = argv[1];
    char *output_filename = argv[2];

    //supplied code, edited second half to perform
    int fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd < 0) {
        printf("ERROR: could not open %s\n", output_filename);
        return 2;
    }

    //now redirect to the output file
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(fd);
        return 3;
    }

    //no need for opened file anymore
    close(fd);

    //print header to STDOUT, writing to file
    printf("Category,Count\n");
    fflush(stdout)

    //prep args for execv
    char *parta_args[] = {"./parta", input_filename, NULL};

    //execute parta
    int ee = execv("./parta", parta_args);

    //if return, error occurred
    if (ee == -1) {
        perror("execv");
        return 4;
    }

    return 0;
}
