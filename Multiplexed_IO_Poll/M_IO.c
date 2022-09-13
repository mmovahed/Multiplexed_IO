#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{
    struct pollfd fds[4];
    int ret;
    int fd1,fd2;
    fd1 = open("First.txt",O_RDONLY);
    fd2 = open("Sec.txt",O_RDONLY);
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;
    fds[2].fd = fd1;
    fds[2].events = POLLRDNORM;
    fds[3].fd = fd2;
    fds[3].events = POLLRDNORM;
    
    ret = poll (fds, 2, 5 * 1000);
    if (ret == -1) {
        perror ("poll");
        return 1;
    }
    if (!ret) {
        printf ("%d seconds elapsed.\n", 5);
        return 0;
    }
    if (fds[0].revents & POLLIN)
    printf ("stdin is readable\n");
    if (fds[1].revents & POLLOUT)
        printf ("stdout is writable\n");
    if (fds[2].revents & POLLRDNORM)
    printf ("First.txt is normal readable\n");
    if (fds[3].revents & POLLRDNORM)
        printf ("Second.txt is normal readable\n");
    
    return 0;

}