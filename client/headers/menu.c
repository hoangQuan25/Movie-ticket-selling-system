#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "../../lib/socket/socket.h"
#include "../../lib/messages/message.h"

void viewWelcome(){
    printf("--------------Hệ thống đặt vé xem phim CinemaNet------------------\n\n");
    printf("1. Đăng nhập tài khoản\n");
    printf("2. Đăng ký tài khoản\n");
    printf("3. Thoát hệ thống\n\n");
    printf("------------------------------------------------------------------\n");
}

/**
 * @function viewLogin: view the login information
 * 
 * @param username : the username to login
 * @param password : the password to login
 */
void viewLogin(char username[], char password[]){
    printf("Đăng nhập\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Mật khẩu: ");
    scanf("%s", password);
}

void viewRegister(char *name, char *username, char *password) {
    printf("Đăng ký\n");
    printf("Họ và tên: ");
    memset(name, 0, 255);
    fgets(name, 255, stdin);
    
    // Remove the newline character from 'name' if present
    size_t length = strlen(name);
    if (length > 0 && name[length - 1] == '\n') {
        name[length - 1] = '\0';
    }
    
    printf("Username: ");
    scanf("%s", username);
    printf("Mật khẩu: ");
    scanf("%s", password);
}


void viewAdmin(){
    printf("--------------Hệ thống đặt vé xem phim CinemaNet------------------\n\n");
    printf("1. Thêm phim mới\n");
    printf("2. Công bố chiếu phim \n");
    printf("3. Thay đổi thông tin công chiếu\n");
    printf("4. Đăng xuất\n\n");
    printf("------------------------------------------------------------------\n");
}

void viewUser(){
    printf("--------------Hệ thống đặt vé xem phim CinemaNet------------------\n\n");
    printf("1. Xem danh sách thể loại\n");
    printf("2. Tìm phim \n");
    printf("3. Đặt vé\n");
    printf("4. Đăng xuất\n");
    printf("5. Đổi mật khẩu\n");
    printf("------------------------------------------------------------------\n");
}

void viewChangePassword(char *oldPassword, char *newPassword) {
    printf("Đổi mật khẩu\n");
    printf("Mật khẩu cũ: ");
    scanf("%s", oldPassword);
    printf("Mật khẩu mới: ");
    scanf("%s", newPassword);
}
