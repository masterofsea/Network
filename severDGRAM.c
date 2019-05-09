#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define D_ADDRESS "/tmp/sock_dgram_server"
#define READ_SIZE 256


int main(int argc, char *argv[]) {

    int sfd = socket(AF_UNIX, SOCK_DGRAM, 0); // создание сокета    	

    const char *socket_path = D_ADDRESS;
    int ret;	
    ret = remove(socket_path);

    //initsock
    struct sockaddr_un addr;    
    memset(&addr, 0, sizeof(struct sockaddr_un));    
    addr.sun_family = AF_UNIX;
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", D_ADDRESS);

    //binding
    bind(sfd, (const struct sockaddr *) &addr, sizeof(addr));

    //receave
    struct sockaddr_un client_address;
    socklen_t client_address_length;
    unsigned char buffer[READ_SIZE];
    ssize_t recvfrom_size;
    client_address_length = sizeof(struct sockaddr_un);
    while(1)
    { 
        recvfrom_size = recvfrom(
                             sfd,
                             buffer,
                             READ_SIZE,
                             0,
                             (struct sockaddr *) &client_address,
                             &client_address_length);
        printf("%s\n", buffer);
    }
    
	
    return 0;
}	

