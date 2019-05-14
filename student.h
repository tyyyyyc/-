#ifndef STUDENT_H
#define STUDENT_H

#include "struct.h"
#include "tools.h"

//#define S_DATA_PATH     "data/s_data.bin"
//#define SD_DATA_PATH    "data/sd_data.bin"
//#define STU_MAX         50

void student_start(void);

// 学生登陆
int stu_login(const char* id_p,const char* pd_p);
// 进入学生子系统
void stu_menu(Student* stu_p);
// 显示学生信息
void stu_show(Student* stu_p);
// 显示学生成绩
void stu_show_score(Student* stu_p);
// 语文成绩排名
void stu_rank_c(void);
// 数学成绩排名
void stu_rank_m(void);
// 英语成绩排名
void stu_rank_e(void);
// 总分成绩排名
void stu_rank_s(void);
//查询排名
void find_stu_paiming(void);
//显示成绩
void find_stu_score(void);
//平均成绩

#endif//STUDENT_H
