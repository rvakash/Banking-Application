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

	int comp; char data[20]; int c; int x=0; int y=0; char usncopy[11]; char namecopy[20];
	int listenfd=0,connfd=0;
	struct sockaddr_in serv_addr; // server address
	char sendbuff1[20];//takes the messge and sends to the client
	int numrv;

	listenfd=socket(AF_INET,SOCK_STREAM,0);//MAKING THE SOCKET
	printf("\n socket retrieve success! \n");
	
	//some standard defnitions
	
	memset(&serv_addr,'0',sizeof(serv_addr));
	memset(sendbuff1,'0',sizeof(sendbuff1));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(5004);
	
	//binding
	bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	printf("\n binding done! \n");

	if (listen(listenfd,10)==-1)
	{
		printf("\n failed to lsiten! \n");
		return -1;
	}

	// binding done

	char name[20]; int n1=0,z; char recvbuff2[20]; char usn2[11], accnum[11], amountarr[3];
	int option,balance, amount;
	while(1)
	{
		connfd=accept(listenfd,(struct sockaddr*)NULL,NULL); // accept waiting request
		printf("\n request accepted\n");
		if((n1=read(connfd,recvbuff2,sizeof(recvbuff2)-1))>0)
		{
			//memset(recvbuff2,'0',sizeof(recvbuff2));
			recvbuff2[n1]=0;
			printf("\n the detail entered is : ");
			if(fputs(recvbuff2,stdout)==EOF)
			{
				printf("\n Error: fputs error \n");
			}
			printf("\n");
		}
		
		if(n1<0)
		{ printf(" \n Read error \n"); }
		printf("\n");

		printf(" Server searching, please wait \n");
		printf(" server searching for %s \n",recvbuff2);
		printf("here");
		for(z=0; z<10; z++)
			accnum[z]=recvbuff2[z];
		accnum[z] = '\0';
//		strcpy(usn2,recvbuff2);
		option = recvbuff2[11];
		printf("\n the account to be searched for is %s \n",accnum);
		
		amountarr[0]=recvbuff2[13];

		amountarr[1]=recvbuff2[14];

		amountarr[2]=recvbuff2[15];
		
		sscanf(amountarr, "%d", &amount);
		memset(usncopy,'0',sizeof(usncopy));
		memset(namecopy,'0',sizeof(namecopy));
		FILE *fp;
		fp=fopen("student.txt","r");

		//check the file and compare the usn and get the name and details
		
		c=fgetc(fp);
		while(!feof(fp))
		{
			// entering the while loop
			printf("in loop");
			memset(usncopy,'0',sizeof(usncopy));
			memset(namecopy,'0',sizeof(namecopy));
			while(c!='-')
			{
				usncopy[x]=c;
				x++;
				c=fgetc(fp);
				if(feof(fp))
					break;

			}
		
			usncopy[x]='\0';

			c=getc(fp);
/*			printf("here");
			option = c;
			printf("here1");
			c=getc(fp);
			c=getc(fp);
*/
			while(c!='\n')
			{ namecopy[y]=c;
				y++;
				c=fgetc(fp);
			}
			
			namecopy[y]='\0';

			c=fgetc(fp);
		
			if((strcmp(usncopy,accnum))==0)
			{
				comp=0;strcpy(name,namecopy);break;
			}
		
			else if((strcmp(usncopy,usn2))!=0)
			{
				comp=1;x=0;y=0;
			}
		}//close of while

		if(comp==1)
		{
			strcpy(name,"no such account");
		}
		else
		{
			sscanf(name, "%d", &balance);
			if(option == 48)
			{
				balance = balance + amount;
				printf("balance deposited");
				strcpy(name,"deposited");
			}
			else if(option == 49)
			{
				balance = balance - amount;
				printf("balance withdraw");
				strcpy(name,"withdrawed");
			}
			else if(option == 50)
			{
				balance = balance;
				printf("balance balance");	
				//strcpy(name,"balance");
			}
		}


		fp=fopen("student.txt","r+");

		//check the file and compare the usn and get the name and details
		c=fgetc(fp);
		while(c!='-')
		{
			c=fgetc(fp);
		}
		//c=getc(fp);
		fprintf(fp,"%d", balance);


		fclose(fp);
		strcpy(sendbuff1,name);
		write(connfd,sendbuff1,strlen(sendbuff1));

		close(connfd);

		sleep(1);
	}
	
	return 0;
	system("pause");
}
		




