#include <netinet/in.h>	//for sockaddr_in
#include <sys/socket.h>	//for socket function
#include <netdb.h>		//for gethostbyname

#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int c, char **v)
{
	const char query[] =
		"GET / HTTP/1.0\r\n"
		"Host: localhost\r\n"
		"\r\n";
	const char hostname[] = "localhost";
	struct sockaddr_in sin;
	struct hostent *h;
	const char *cp;
	int fd;
	ssize_t n_written, remaining;
	char buf[1024];
	
	//look up the IP address for the hostname. watch out;this isn't threadsafe on most platforms.
	h = gethostbyname(hostname);
	if (!h) {
		fprintf(stderr, "Couldn't lookup %s: %s", hostname, hstrerror(h_errno));
		return 1;
	}
	
	if (h->h_addrtype != AF_INET) {
		fprintf(stderr, "No ipv6 support, sorry.");
		return 1;
	}
	
	//allocate a new socket
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");
		return 1;
	}
	
	//connect to the remote host
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8000);
	sin.sin_addr = *(struct in_addr *)h->h_addr;
	if (connect(fd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("connect");
		close(fd);
		return 1;
	}
	
	//write the query. xxx can send succeed partially?
	cp = query;
	remaining = strlen(query);
	while (remaining) {
		n_written = send(fd, cp, remaining, 0);
		if (n_written <= 0) {
			perror("send");
			return 1;
		}
		remaining -= n_written;
		cp += n_written;
	}
	
	while (1) {
		ssize_t result = recv(fd, buf, sizeof(buf), 0);
		if (result == 0) {
			break;
		} else if (result < 0) {
			perror("recv");
			close(fd);
			return 1;	
		}
		
		fwrite(buf, 1, result, stdout);	
	}
	
	printf("\n");
	
	close(fd);
	return 0;
}