#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>

#define D_ADDRESS "/tmp/sock_dgram_server"
#define READ_SIZE 256
#define LISTEN_BACKLOG 1


int main(char* argc, int argv){
    const char *socket_path = D_ADDRESS;
    struct sockaddr_un addr;    
    int sfd, cfd;
    int ret;
    
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", socket_path);

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1) {
            return -1;
    }    
    ret = bind(sfd, (const struct sockaddr *) &addr, sizeof(sa_family_t));
    if (ret == -1) {
            return -2;
    }
    ret = listen(sfd, LISTEN_BACKLOG);
    unsigned char buffer[READ_SIZE];
    ssize_t recv_size;
    do{
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1) {
            return -3;
        }
        do{            
            recv_size = recv(cfd, buffer, READ_SIZE, 0);
            if (recv_size == -1) {
                return -4;
            }
            printf("%s", buffer);
        }while(recv_size);
    }while(1);    
}
