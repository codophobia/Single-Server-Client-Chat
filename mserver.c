#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
void *handler(void *sock)
{
	int client_sock = *((int *)sock);
	char msg[500];
	int len;
	while((len = recv(client_sock,msg,500,0)) > 0) {
		len = send(client_sock,msg,strlen(msg),0);
		if(len < 0) {
			perror("message not sent");
			exit(1);
		}
		memset(msg,'\0',sizeof(msg));
	}
}
int main(int argc,char *argv[])
{
	struct sockaddr_in server_addr,client_addr;
	int server_sock;
	int client_sock;
	int client_addr_size;
	int portno;
	char msg[500];
	int len;
	pthread_t thread;
	
	if(argc > 2) {
		printf("too many arguments");
		exit(1);
	}
	portno = atoi(argv[1]);
	server_sock = socket(AF_INET,SOCK_STREAM,0);
	memset(server_addr.sin_zero,'\0',sizeof(server_addr.sin_zero));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_addr_size = sizeof(client_addr);

	if(bind(server_sock,(struct sockaddr *)&server_addr,sizeof(server_addr)) != 0) {
		perror("server socket binding failed");
		exit(1);
	}

	if(listen(server_sock,5) != 0) {
		perror("server socket failed to listen");
		exit(1);
	}

	while(1) {
		if((client_sock = accept(server_sock,(struct sockaddr *)&client_addr,&client_addr_size)) < 0) {
			perror("server failed to accept client connection");
			exit(1);
		}
		
		pthread_create(&thread,NULL,handler,&client_sock);
		
	}
	close(server_sock);
	return 0;
}