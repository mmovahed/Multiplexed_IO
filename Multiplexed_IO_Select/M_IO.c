#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main (void)
{
    struct timeval tv;  
    fd_set readfds;
    int ret;
    int fd1,fd2;
    fd1 = open("First.txt",O_RDONLY);
    fd2 = open("Sec.txt",O_RDONLY);

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(fd1,&readfds);
    FD_SET(fd2,&readfds);

    tv.tv_sec = 50;
    tv.tv_usec = 0;

    ret = select (STDIN_FILENO + 1,&readfds,NULL,NULL,&tv);
    if (ret == -1) {
        perror ("selected fd set");
        return 1;
    } else if (!ret) {
        printf ("%d seconds elapsed.\n", 50);
        return 0;
    }

    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        char buf[1024+1];
        int len;

        len = read (STDIN_FILENO, buf, 1024);
        if (len == -1) {
            perror ("read");
            return 1;
        }
        if (len) {
            buf[len] = '\0';
            printf ("read from stdin: %s\n", buf);
        }
        return 0;
    }
    
    else if (FD_ISSET(fd1, &readfds)) {
        char buf[1024+1];
        int len;

        len = read (fd1, buf, 1024);
        if (len == -1) {
            perror ("read error");
            return 1;
        }
        if (len) {
            buf[len] = '\0';
            printf ("read from first file: %s\n", buf);
        }
        return 0;
    }
    
    else if (FD_ISSET(fd2, &readfds)) {
        char buf[1024+1];
        int len;

        len = read (fd2, buf, 1024);
        if (len == -1) {
            perror ("read error");
            return 1;
        }
        if (len) {
            buf[len] = '\0';
            printf ("read from seconde file : %s\n", buf);
        }
        return 0;
    }
    
    fprintf (stderr, "This should not happen!\n");
    return 1;
}