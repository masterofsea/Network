#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFF_SIZE 256

int main(){
	char buffer[BUFF_SIZE];
	fd_set readfds;
	int nfds;	
	int ret;			
	int fd1;
	
	fd1 = STDIN_FILENO;
	nfds = STDIN_FILENO + 1;

	fcntl(fd1, F_SETFL, fcntl(fd1, F_GETFL) | O_NONBLOCK);	
		
	
	do{		
		FD_ZERO(&readfds);
		FD_SET(fd1, &readfds);
		ret = select(nfds, &readfds, NULL, NULL, NULL);
		if (ret == -1) {
			return -1;						
		}		
		
		if (FD_ISSET(fd1, &readfds)) {				
			ret = read(fd1, buffer, BUFF_SIZE);
			buffer[ret] = '\0';				
			printf("%s", buffer);
		}
		
		
	}while(1);
}



