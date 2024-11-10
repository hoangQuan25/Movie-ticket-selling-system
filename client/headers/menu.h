#ifndef MENU_H
#define MENU_H

#include "../../lib/socket/socket.h"
#include "../../lib/messages/message.h"

#define LOGIN_SUCCESS_USER 1010
#define LOGIN_SUCCESS_ADMIN 1011
#define LOGIN_FAIL 2011
#define LOGIN_ALREADY 2012
#define LOGOUT_SUCCESS 1030
#define REGISTER_SUCCESS 1020
#define REGISTER_FAIL 2021
#define CHANGE_PASSWORD_SUCCESS 1110
#define CHANGE_PASSWORD_FAIL 2110

#define LOGIN_SUCCESS_MESSAGE "Đăng nhập thành công!\n"
#define LOGIN_FAIL_MESSAGE "Đăng nhập thất bại. Hãy kiểm tra lại thông tin.\n"
#define LOGIN_ALREADY_MESSAGE "Tài khoản của bạn đang được dùng ở một địa chỉ khác.\n"
#define REGISTER_SUCCESS_MESSAGE "Đăng ký thành công!\n"
#define REGISTER_FAIL_MESSAGE "Username đã tồn tại.\n"
#define LOGOUT_SUCCESS_MESSAGE "Đăng xuất thành công!\n"
#define INVALID_MESSAGE_MESSAGE "Yêu cầu không hợp lệ.\n"
#define CHANGE_PASSWORD_SUCCESS_MESSAGE "Đổi mật khẩu thành công!\n"
#define CHANGE_PASSWORD_FAIL_MESSAGE "Đổi mật khẩu thất bại. Vui lòng kiểm tra lại.\n" 

void viewWelcome();
void viewLogin(char username[], char password[]);
void viewRegister(char *name, char *username, char *password);
void viewAdmin();
void viewUser();
void viewChangePassword(char *oldPassword, char *newPassword);

#endif