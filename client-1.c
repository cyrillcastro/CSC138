/* Cyrill Castro
 * CSC 138
 * Prof J Dai
 *
 * Socket Assignment 4
 * CLIENT SIDE 
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define SERVER_PORT 5432
#define MAX_LINE 256

int main(int argc, char *argv[]) 
{
	struct hostent *hp;

	struct sockaddr_in sin; 
	char *host;
	char buf[MAX_LINE];
	int s;			/* socket */
	int len;		/* addr_len */
	host = argv[1];
	
	if ((host == NULL) || (host == '\0')) {
		perror("ERROR: Host argument is null.");
		exit(EXIT_FAILURE);
	} else { 
		/* translate host name into peer's IP address */
		hp = gethostbyname(host);
		
		if (hp == NULL) {
			perror("ERROR: Null pointer.");
			exit(EXIT_FAILURE);
		} else {
			/* build address data structure */
			bzero((char*)&sin, sizeof(sin));
			sin.sin_family = AF_INET; /*Internet Address*/
			bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
			sin.sin_port = htons(SERVER_PORT);

			/* Create the socket */
			s = socket(PF_INET, SOCK_STREAM, 0);
			if (s < 0) {
				perror("ERROR: Failed to create socket.");
				exit(EXIT_FAILURE);
			} else {
				/* Connect the socket with server*/
				int c = connect(s, (const struct sockaddr *)&sin, sizeof(sin));

				if (c < 0) {
					perror("ERROR: Failed to connect socket.");
					exit(EXIT_FAILURE);
				} else {
					/* main loop: get and send lines of text */
					while (1) {
						bzero(&buf, MAX_LINE);
						fgets(buf, sizeof(buf), stdin);
						buf[MAX_LINE - 1] = '\0';
						len = strlen(buf) + 1;
						send(s, buf, len, 0);
					}	
					close(s);
					return EXIT_SUCCESS;
				} // end of connect check  
			} // end of socket check
		} // end of gethostbynamecheck 
	} // end of host check 
}
