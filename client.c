#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
int htconnect(char *domain,int port){
int white_sock;
struct hostent *site;
struct sockaddr_in me;
site=gethostbyname(domain);
if(site==NULL)
{
return -2;
}
white_sock=socket(AF_INET,SOCK_STREAM,0);
if(white_sock<0){
return -1;
}
memset(&me,0,sizeof(struct sockaddr_in));
memcpy(&me.sin_addr,site->h_addr_list[0],site->h_length);
me.sin_family=AF_INET;
me.sin_port=htons(port);
return (connect(white_sock,(struct sockaddr*)&me,sizeof(struct sockaddr))<0)?1:white_sock;
}
int htsend(int sock,char *fmt, ...){
char BUF[1024];
va_list argptr;
va_start(argptr,fmt);
vsprintf(BUF,fmt,argptr);
va_end(argptr);
return send(sock,BUF,strlen(BUF),0);
}
void main(int argc,char **argv)
{
int black_sock;
char bugs_bunny[3];
if(argc<2){
printf("Usage:\n\twww_client host\n");
return ;
}
black_sock=htconnect(argv[1],80);
if(black_sock<0){
printf("Socket Connect Error!\n");
return 0;
}
htsend(black_sock,"GET /HTTP/1.0%c",10);
htsend(black_sock,"Host:%s%c",argv[1],10);
htsend(black_sock,"%c",10);
while(read(black_sock,bugs_bunny,1)>0){
printf("%c",bugs_bunny[0]);
}
close(black_sock);
}
