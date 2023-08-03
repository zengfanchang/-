#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

#define HOST "localhost"
#define user "zeng"
#define passwd "123123.."
#define db "yourdb"
#define table "user"

int main() {
    MYSQL *mysql = mysql_init(NULL);
    if (mysql == NULL) {
        printf("mysql init failed\n");
        return -1;
    }

    // 连接数据库
    mysql = mysql_real_connect(mysql, HOST, user, passwd, db, 3306, NULL, 0);    
    if (mysql == NULL) {
        printf("mysql connect failed\n");
        return -1;
    }
    printf("mysql connect success\n");
    
    // 查
    char rSql[1024] = {0};
    strcpy(rSql, "select * from user");
    if (mysql_query(mysql, rSql) != 0) {
        printf("mysql query failed\n");
        return -1;
    }

    int i = 0;
    MYSQL_RES *res = mysql_store_result(mysql);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != NULL) { // yi'h
        printf("row %d: %s\n", i++, row[0]);
    }

    // 增
    strcpy(rSql, "insert into user values('z', '123456')");
    if (mysql_query(mysql, rSql) != 0) { // 没有权限
        printf("mysql insert failed\n");
        return -1;
    }
    printf("mysql insert success\n");

    // 改
    strcpy(rSql, "update user set passwd='1231123' where username='z'");
    if (mysql_query(mysql, rSql) != 0) {
        printf("mysql update failed\n");
        return -1;
    }

    printf("mysql update success\n");

    // 删
    strcpy(rSql, "delete from user where username='z'");
    if (mysql_query(mysql, rSql) != 0) {
        printf("mysql delete failed\n");
        return -1;
    }
    printf("mysql delete success\n");
    mysql_close(mysql);
}