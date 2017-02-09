#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 
Stolen with changes from: 
https://github.com/troydhanson/network/blob/master/unixdomain/cli.c
*/

char *socket_path = "/var/tmp/fcgiwrap.sock";

int main(int argc, char *argv[]) {
    struct sockaddr_un addr;
    char buf[100];
    int c,fd,rc,verbose;

    while ((c = getopt (argc, argv, "vhf:")) != -1)
        switch (c)
        {
            case 'v':
                verbose = 1;
                break;
            case 'f':
                socket_path = optarg;
                break;
            case 'h':
                printf("Usage: fcgi_slap [-v] [-f /path/to/socket]\n");
                exit(0);
        }
    if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        fprintf(stderr, "Could not open socket: %s\n", socket_path);
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    if (*socket_path == '\0') {
        *addr.sun_path = '\0';
        strncpy(addr.sun_path+1, socket_path+1, sizeof(addr.sun_path)-2);
    }
    else {
        strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
    }

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("connect error");
        fprintf(stderr, "Could not create socket connection to: %s\n", socket_path);
        exit(-1);
    }
    else {
        if (verbose) printf("Connected to %s successfully\n", socket_path);
    }

    return 0;
}
