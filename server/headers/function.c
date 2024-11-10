#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "../../lib/socket/socket.h"
#include "../../lib/messages/message.h"
#include "queryUser.h"
#include "function.h"

#define LOGIN_SUCCESS_USER 1010
#define LOGIN_SUCCESS_ADMIN 1011
#define LOGIN_FAIL 2011
#define LOGIN_ALREADY 2012
#define LOGOUT_SUCCESS 1030
#define REGISTER_SUCCESS 1020
#define REGISTER_FAIL 2021
#define CHANGE_PASSWORD_SUCCESS 1110
#define CHANGE_PASSWORD_FAIL 2110

void handleRequest(MYSQL *conn, char *type, int connfd, char **username, char *password, listLoginedAccount *arr, node h){
    if(strcmp(type, "LOGIN") == 0){
        handleLogin(connfd, arr, h, username, password);
        printf("username: %s\n", *username);
    }else if(strcmp(type, "LOGOUT") == 0){
        printf("username: %s\n", *username);
        handleLogout(connfd, arr, username);
    }else if (strcmp(type, "REGISTER") == 0)
    {
        handleRegister(conn, connfd, &h);
    }
    else if (strcmp(type, "CHANGE_PASSWORD") == 0)
    {
        handleChangePassword(connfd, conn, &h);
    }
}

void handleLogin(int connfd, listLoginedAccount *arr, node h, char **username, char *password){
    getLoginMessage(username, &password);
    int check = checkLogin(h, username, password, arr);
    printf("%d\n", check);
    if(check == 0){
        sendResult(connfd, LOGIN_FAIL);   
    }else if(check == 1){
        addToListLoginedAccount(arr, username);
        sendResult(connfd, LOGIN_SUCCESS_ADMIN);
    }else if(check == 2){
        addToListLoginedAccount(arr, username);
        sendResult(connfd, LOGIN_SUCCESS_USER);
    }else{
        sendResult(connfd, LOGIN_ALREADY);
    }
}

void handleLogout(int connfd, listLoginedAccount *arr, char **username){
    printf("%s\n", *username);
    deleteFromListLoginedAccount(arr, username);
    sendResult(connfd, LOGOUT_SUCCESS);
}

void handleRegister(MYSQL *conn, int connfd, node *h){
    char *name, *username, *password;
    name = (char *)malloc(255 * sizeof(char));
    username = (char *)malloc(255 * sizeof(char));
    password = (char *)malloc(255 * sizeof(char));
    getRegisterMessage(&name, &username, &password);

    // Thiết lập newUser
    user newUser;
    strcpy(newUser.name, name);
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    newUser.role_id = 2; // Mặc định là user

    addNode(h, newUser); // Thêm vào danh sách liên kết

    // Gọi hàm đăng ký và xử lý kết quả
    int result = registerUser(conn, newUser);
    if (result == 1)
    {
        sendResult(connfd, REGISTER_SUCCESS);
    }
    else
    {
        sendResult(connfd, REGISTER_FAIL);
    }
}

void handleChangePassword(int connfd, MYSQL *conn, node *h){
    char *username, *oldPassword, *newPassword;
    username = (char *)malloc(255 * sizeof(char));
    oldPassword = (char *)malloc(255 * sizeof(char));
    newPassword = (char *)malloc(255 * sizeof(char));
    getChangePasswordMessage(&username, &oldPassword, &newPassword); // Hàm này cần được viết để phân tích tin nhắn

    int result = changePassword(conn, username, oldPassword, newPassword);
    printf("%d\n", result);
    if (result == 1)
    {
        changeNodePassword(h, username, newPassword);
        sendResult(connfd, CHANGE_PASSWORD_SUCCESS);
    }
    else
    {
        sendResult(connfd, CHANGE_PASSWORD_FAIL);
    }
}