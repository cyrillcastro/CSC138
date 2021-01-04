/* Cyrill Castro
 * CSC 138
 * Prof J Dai
 *
 * Socket Project 4
 * SERVER SIDE 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 256

int main() {
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int s, new_s, len;

	/* build address data structure */
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	/* setup passive open */
	s = socket (PF_INET, SOCK_STREAM, 0);

	if (s < 0) {
		perror("ERROR: Failed to create socket.");
		exit(EXIT_FAILURE);
	} else {
		/* Bind the socket to data structure */
		new_s = bind(s,(struct sockaddr *)&sin, sizeof(sin));
		
		if (new_s < 0) {
			perror("ERROR: Failed to bind socket.");
			exit(EXIT_FAILURE);
		} else {
			/* Make the socket to listen */
			listen(s, MAX_PENDING);
			//printf("Server is listening to port: %d," SERVER_PORT);

			int new = accept(s, (struct sockaddr *)&sin, &len);
			/* wait for connection, then recieve and print text */
			if (new < 0) {
				perror("ERROR: Failed to accept connection.");
				exit(EXIT_FAILURE);
			} else {
				while (1) {
					len = sizeof(sin);
					/* Accept connections */
					bzero(buf, MAX_LINE);
					/* Receive and print text */
					recv(new, buf, len, 0);
					printf("%s", buf);;
				}	
			
				close(new);
				return EXIT_SUCCESS;
			} // end of accept check			
		} // end of bind check
	} // end of socket check 
}
