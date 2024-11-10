#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 255

void sendMessage(int fd, char *message) {
    int length = htonl(strlen(message));
    printf("Sending message length: %d\n", ntohl(length));  // Print original message length
    send(fd, &length, sizeof(length), 0);
    printf("Sending message content: %s\n", message);       // Print actual message content
    send(fd, message, strlen(message), 0);
}


void recvMessage(int fd, char *message) {
    int length = 0;
    char buffer[BUFSIZE];
    memset(&buffer, 0, BUFSIZE);

    recv(fd, &length, sizeof(length), 0);                // Receive length
    int msg_len = ntohl(length);                         // Convert to host byte order
    printf("Received message length: %d\n", msg_len);    // Print received message length

    if (msg_len > 0 && msg_len < BUFSIZE) {
        recv(fd, buffer, msg_len, 0);                    // Receive the message
        buffer[msg_len] = '\0';                          // Null-terminate the string
        printf("Received message content: %s\n", buffer); // Print received message content
        strcpy(message, buffer);                         // Copy to message buffer
    } else {
        fprintf(stderr, "Error: received message length out of range\n");
    }
}


void sendResult(int fd, int result) {
    int message = htonl(result);
    printf("Sending result: %d\n", result);  // Print the result before sending
    send(fd, &message, sizeof(message), 0);
}


int recvResult(int fd) {
    int result;
    recv(fd, &result, sizeof(result), 0);

    int host_result = ntohl(result);                         // Convert to host byte order
    printf("Received result from server: %d\n", host_result);  // Print received result

    return host_result;
}
