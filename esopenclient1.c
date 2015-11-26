#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{

	int sockfd=0; int n=0;
	char recvbuff[20];
	struct sockaddr_in serv_addr;
while(1)
{
	memset(recvbuff,'0',sizeof(recvbuff));

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("\nerror: could not create the socket\n");
		return 1;
	}
	printf("\n socket created successfully\n");
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(5004);
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("\n Error: connect failed \n");
		return 1;
	}

	printf("\n Connect done successfully\n");
	printf("\n 0 Deposit");
	printf("\n 1 Withdraw");
	printf("\n 2 Balance");
	printf("\nEnter your account number,option and amount separated by -  : ");
	char usn[15]; char sendbuff2[20];
	scanf("%s",&usn);
	printf("\n");
	strcpy(sendbuff2,usn);
	write(sockfd,sendbuff2,strlen(sendbuff2));

	while((n=read(sockfd,recvbuff,sizeof(recvbuff)-1))>0)
	{
		recvbuff[n]=0;
		printf("\n the amount is: ");
		if(fputs(recvbuff,stdout)==EOF)
		{
			printf("\nfputs error\n");
		}
	}
	if(n<0)
	{
		printf("\nread error\n");
	}
printf("\n");
}
return 0;
}//end of main

