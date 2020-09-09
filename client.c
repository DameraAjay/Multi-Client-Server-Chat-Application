/********************************************************
	Author: Damera Ajay
	Date  :JAN-14-2020
	Flags : port no should send throught commandline
*********************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <signal.h>

int main(int argc,char *argv[]){
	int client_socket,port;
	struct sockaddr_in serv_addr;
	char buff[1024];
	////checking required no of argument provided or not
	if(argc < 2){
		perror("[-]ERROR: port no is required..!\n");
		exit(0);
	}
	//creating socket
	client_socket = socket(AF_INET,SOCK_STREAM,0);
	if(client_socket < 0){
		perror("[-]ERROR: While creating client socket..!\n");
		exit(0);
	}
	
	printf("[+]Client socket created succussfully...\n");
	bzero(&serv_addr,sizeof(serv_addr));
	port = atoi(argv[1]);
	//assigning port and  ip
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	//connecting to server
	int con_val = connect(client_socket,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(con_val != 0){
		perror("[-]ERROR: While conneting to socket..!\n");
		exit(0);
	}
	bzero(buff,sizeof(buff));
	if(recv(client_socket,buff,1024,0) < 0){
		printf("[-]Error in receiving data...!\n");
		exit(0);
	}
	else{
		printf("%s",buff);
		if(strcmp(buff,"[-]Connection Limit Exceeded !!\n") == 0){
			exit(0);
		}
	}
	
	//printf("[+]Succussfully connected to server...\n");
	//infinite loop untill client exit
	int pid = fork();
	if(pid == 0){
		while(1){
			//printf("Client:\t");
			bzero(buff,sizeof(buff));
			//reading input
			fgets(buff,1024,stdin);
			//sending data to server
			//printf("%s\n",buff);
			send(client_socket,buff,strlen(buff),0);
			//checking for exit condition
			if(strncmp(buff,"/quit",5) == 0){
				//closing the socket discripter
				close(client_socket);
				printf("[-]Disconnected from server...!\n");
				break;
			}
		
		}
	}
	else{
		while(1){
			char buf[1024];
			bzero(buf,sizeof(buf));
			if(recv(client_socket,buf,1024,0) < 0){
				printf("[-]Error in receiving data...!\n");
			}
			else{
				printf("%s\n",buf);
			}
		}
	}
	kill(pid,SIGKILL);
	//closing socket discripter
	close(client_socket);
}
