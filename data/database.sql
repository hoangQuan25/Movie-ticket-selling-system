CREATE DATABASE ticketbooking;

CREATE TABLE users (
    id bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name varchar(255) NOT NULL,
    username varchar(255) NOT NULL,
    password varchar(255) NOT NULL,
    role_id bigint(20) NOT NULL
);