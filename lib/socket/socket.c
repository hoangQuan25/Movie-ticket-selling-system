#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 255

void printBorder() {
    printf("\n==============================\n");
}

void sendMessage(int fd, char *message) {
    int length = htonl(strlen(message));
    
    printBorder();
    printf("SENDING MESSAGE\n");
    printf("------------------------------\n");
    printf("Message Length (Original): %d\n", ntohl(length));
    printf("Message Content:\n\"%s\"\n", message);
    printBorder();
    
    send(fd, &length, sizeof(length), 0);  // Send the length
    send(fd, message, strlen(message), 0); // Send the actual message
}

void recvMessage(int fd, char *message) {
    int length = 0;
    char buffer[BUFSIZE];
    memset(&buffer, 0, BUFSIZE);

    recv(fd, &length, sizeof(length), 0);         // Receive length
    int msg_len = ntohl(length);                  // Convert to host byte order
    
    printBorder();
    printf("RECEIVING MESSAGE\n");
    printf("------------------------------\n");
    printf("Message Length (Received): %d\n", msg_len);

    if (msg_len > 0 && msg_len < BUFSIZE) {
        recv(fd, buffer, msg_len, 0);             // Receive the message
        buffer[msg_len] = '\0';                   // Null-terminate the string
        printf("Message Content: \"%s\"\n", buffer);
        strcpy(message, buffer);                  // Copy to message buffer
    } else {
        fprintf(stderr, "Error: Received message length out of range\n");
    }
    printBorder();
}

void sendResult(int fd, int result) {
    int message = htonl(result);

    // Send the result code first
    printBorder();
    printf("SENDING RESULT\n");
    printf("------------------------------\n");
    printf("Result: %d\n", result);
    printBorder();

    // Send the result code (integer)
    send(fd, &message, sizeof(message), 0);
}

void sendResultWithToken(int fd, int result, char *token) {
    int message = htonl(result);

    // Send the result code first
    printBorder();
    printf("SENDING RESULT WITH TOKEN\n");
    printf("------------------------------\n");
    printf("Result: %d\n", result);
    printf("Token: %s\n", token);
    printBorder();

    send(fd, &message, sizeof(message), 0);

    if (token != NULL) {
        // If there's a token, send it after the result code
        int tokenLength = strlen(token) + 1;  // Including null terminator
        int networkTokenLength = htonl(tokenLength); // Convert token length to network byte order

        // Send the length of the token first
        send(fd, &networkTokenLength, sizeof(networkTokenLength), 0);

        // Send the token string
        send(fd, token, tokenLength, 0);
    }
}

int recvResult(int fd) {
    int result;
    recv(fd, &result, sizeof(result), 0);         // Receive the result
    
    int host_result = ntohl(result);              // Convert to host byte order
    printBorder();
    printf("RECEIVED RESULT\n");
    printf("------------------------------\n");
    printf("Result from Server: %d\n", host_result);
    printBorder();
    
    return host_result;
}

int recvResultWithToken(int fd, char *token) {
    int result;
    int tokenLength = 0;

    // Receive the result code
    if (recv(fd, &result, sizeof(result), 0) <= 0) {
        fprintf(stderr, "Error: Failed to receive result code\n");
        return -1; // Return error code
    }
    result = ntohl(result);

    // Receive the token length
    if (recv(fd, &tokenLength, sizeof(tokenLength), 0) <= 0) {
        fprintf(stderr, "Error: Failed to receive token length\n");
        return -1; // Return error code
    }
    tokenLength = ntohl(tokenLength);

    // Check if token length is within bounds
    if (tokenLength <= 0 || tokenLength > 255) {
        fprintf(stderr, "Error: Invalid token length received: %d\n", tokenLength);
        return -1; // Return error code
    }

    // Receive the token itself
    if (recv(fd, token, tokenLength, 0) <= 0) {
        fprintf(stderr, "Error: Failed to receive token data\n");
        return -1; // Return error code
    }
    token[tokenLength] = '\0'; // Null-terminate token

    // Print token for debugging
    printBorder();
    printf("RECEIVED RESULT WITH TOKEN\n");
    printf("------------------------------\n");
    printf("Result from Server: %d\n", result);
    printf("Token: %s\n", token);
    printBorder();

    return result;
}

