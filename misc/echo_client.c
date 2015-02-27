#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define BUFSIZE 512
#define SERV_PORT 9876

#define setnonblocking(s) fcntl(s, F_SETFL, fcntl(s, F_GETFL) | O_NONBLOCK)

int main()
{
    int sockfd;
    int send_bytes, recv_bytes;
    static int sent_data = 1;
    int recv_data = 0;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.
    servaddr.sin_port = htons(SERV_PORT);
   
    connect(sockfd, (struct socdaddr*)&servaddr, sizeof(servaddr));
    
    for(;;)
    {
        send_bytes = send(sockfd, (void*)&sent_data, sizeof(int), 0);
        recv_bytes = recv(sockfd, (void*)&recv_data, sizeof(int), 0);
        printf(" data recv %d\n", recv_data);
        sleep(1);
    }
     
}
