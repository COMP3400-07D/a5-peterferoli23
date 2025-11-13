#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];

    //open the file for reading:
    int fileRD = open(argv[1], O_RDONLY);
    //check for error
    if (fileRD < 0) {
        //print an error with perror & return
        perror("open");
        return 1;
    }

    //create ints for each category to track:
    int upper = 0, lower = 0, digit = 0, space = 0, other = 0;

    //for tracking purposes, use ssize_t
    ssize_t bytesRead;
    
    //while loop to iterate through the file
    while ((bytesRead = read(fileRD, buffer, BUFSIZE)) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            //unsigned char due to differing datatypes
            unsigned char c = buffer[i];
            if (isupper(c))
                upper++;
            else if (islower(c))
                lower++;
            else if (isdigit(c))
                digit++;
            else if (isspace(c))
                space++;
            else
                other++;
        }
    }

    if (bytes < 0) {
        perror("read");
        close(fileRD);
        return 1;
    }

    //close file once done:
    close(fileRD);

    //print out answer:
    printf("Upper,%d\n", upper);
    printf("Lower,%d\n", lower);
    printf("Number,%d\n", number);
    printf("Space,%d\n", space);
    printf("Other,%d\n", other);

    return 0;
}
