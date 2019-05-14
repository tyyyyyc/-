#ifndef STRUCT_H
#define STRUCT_H

#include "tools.h"
/*typedef struct Student{
	char name[20];  //姓名
	char sex;  //性别
	int id;  //学号
	int Chinese_grade; //语文成绩
	int Math_grade; //数学成绩
	int English_grade; //英语成绩
	int login_times;
	char passwd[10]; //密码
	int flag_stu_ex; //离校学生标志位
	int flag_stu_firstlogin; //学生第一次登陆系统标志位	
	int flag_stu_wrong; //学生密码错误次数
	int flag_stu_grade; //录入学生成绩标志位
}Student;
*/
typedef struct Student
{
    int    		id;        // 学号
    char 		passwd[10];        // 密码
    char        name[20];  // 姓名
    char        sex;       // 性别
    float       score_c;   // 语文
    float       score_m;   // 数学
    float       score_e;   // 英语
    float       score_s;   // 总分
    float       score_a;   // 平均
	int 		flag_stu_ex; //离校学生标志位
	int 		flag_stu_firstlogin; //学生第一次登陆系统标志位	
	int 		flag_stu_wrong; //学生密码错误次数
	int 		flag_stu_grade; //录入学生成绩标志位
}Student;

typedef struct Teacher{
	char 		name[20]; //姓名
	char 		sex; //性别
	int 		id; //工号
	char 		passwd[10]; //密码
	int 		flag_tea_ex; //离校老师标志位
	int 		flag_tea_firstlogin; //老师第一次登陆系统标志位
	int 		flag_tea_wrong; //老师密码错误次数
}Teacher;
//extern Teacher TEA[50];
//学生数组指针
extern Student* STU;
//老师数组指针 
extern Teacher* TEA;
//老师人数
extern int count;
//学生人数
extern int count1;
//当前学生
extern int now_stu;
//校长第一次登陆系统标志位
extern int flag;
//校长强制修改的密码
extern char admin_passwd1[10];


#endif//STRUCT_H
