#ifndef SOCKET_H
#define SOCKET_H

void sendMessage(int fd, char *message);
void recvMessage(int fd, char *message);
void sendResult(int fd, int result);
void sendResultWithToken(int fd, int result, char *token);
int recvResult(int fd);

#endif