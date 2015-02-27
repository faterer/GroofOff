#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream>

#define MAXLINE 512
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 9876
#define INFTIM 1000

#define setnonblocking(s) fcntl(s, F_SETFL, fcntl(s, F_GETFL) | O_NONBLOCK)

ssize_t socket_send(int sockfd, const char* buffer, size_t buflen)
{
    ssize_t tmp;
    size_t total = buflen;
    const char *p = buffer;
    
    for(;;)
    {
        tmp = send(sockfd, p, total, 0);
        if (tmp < 0)
        {
            if (errno == EINTR)
                continue;
                
            if (errno == EAGAIN)
            {
                usleep(1000);
                continue;    
            }

            return -1;
        } 
        
        if ((size_t)tmp == total)
            return buflen;
            
        total -= tmp;
        p += tmp;   
    }

    return tmp;
}


void epoll_ctl_err_show()
{
    std::cout << "error at epoll_ctl" << std::endl;
    if (EBADF == errno)
    {
        std::cout << "error at epoll_ctl, error is EBADF" << std::endl;    
    }
    else if (EEXIST == errno)
    {
        std::cout << "error at epoll_ctl, error is EEXIST" << std::endl;    
    }
    else if (EINVAL == errno)
    {
        std::cout << "error at epoll_ctl, error is EINVAL" << std::endl;    
    }
    else if (ENOENT == errno)
    {
        std::cout << "error at epoll_ctl, error is ENOENT" << std::endl;    
    }
    else if (ENOMEM == errno)
    {
        std::cout << "error at epoll_ctl, error is ENOMEM" << std::endl;    
    }
    else if (ENOSPC == errno)
    {
        std::cout << "error at epoll_ctl, error is ENOSPC" << std::endl;    
    }
}

int main()
{
    std::cout << "start epoll echo server..." << std::endl;
    int epfd = epoll_create(2);
    
    struct sockaddr_in clientaddr;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd)
    {
        std::cout << "error at socket" << std::endl;
        exit(1);    
    }

    setnonblocking(listenfd);
    
    struct epoll_event ev;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN | EPOLLET;
    if (-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev))
    {
        epoll_ctl_err_show();    
    }
    
    struct sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(sockaddr_in));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (sockaddr*)&serveraddr, sizeof(sockaddr_in));

    listen(listenfd, LISTENQ);

    int nfds = 0;
    int sockfd;
    const int time_out = 500;
    const int max_events = 20;
    int connfd = 0;
    socklen_t client_addr_len;
    struct epoll_event events[max_events];
    ssize_t n;
    char line[MAXLINE];

    for (;;)
    {
        nfds = epoll_wait(epfd, events, max_events, time_out);
        for (int i = 0; i < nfds; ++i)
        {
            if (events[i].data.fd == listenfd)
            {
                client_addr_len = sizeof(clientaddr);
                connfd = accept(listenfd, reinterpret_cast<struct sockaddr *>(&clientaddr), &client_addr_len);
                if (-1 == connfd)
                {
                    std::cout << "error at accept" << std::endl;
                    exit(1);        
                }
                std::cout << "accept a connection from " << inet_ntoa(clientaddr.sin_addr) << std::endl;
                 
                setnonblocking(connfd);
                ev.data.fd = connfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
            }
            else if (events[i].events & EPOLLIN)
            {
               std::cout << "event epollin" << std::endl;
               if ((sockfd = events[i].data.fd) < 0)
               {
                   continue;    
               }
               memset(line, 0, MAXLINE);
               n = 0;
               int nread = 0;
               
               while((nread = read(sockfd, line + n, MAXLINE)) > 0)
               {
                   n += nread;
               }

               std::cout << "message: " << line << std::endl;
               if (nread == -1 && errno != EAGAIN)
               {
                   epoll_ctl_err_show();
                   std::cout << "readline error" << std::endl;
                   close(sockfd);
                   events[i].data.fd = -1;    
               }

               if (nread == 0)
               {
                   close(sockfd);
                   continue;   
               }

               ev.data.fd = sockfd;
               ev.events = EPOLLOUT | EPOLLET;
               epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
            }
            else if(events[i].events & EPOLLOUT)
            {
               std::cout << "event epollout" << std::endl;
               sockfd = events[i].data.fd;
               socket_send(sockfd, line, strlen(line) + 1);

               ev.data.fd = sockfd;
               ev.events = EPOLLIN | EPOLLET;
               epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
            }
        }
    }
}
