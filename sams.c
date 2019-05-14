#include "sams.h"
#include "tools.h"
#include "admin.h"
#include "student.h"
#include "teacher.h"
#include "struct.h"

void sams_menu(void){
	//clear_src();
	pf("---学生成绩管理系统---\n");
	pf("-------------------\n");
	pf("请以以下身份进入系统：\n");
	pf("1、student\n");
	pf("2、teacher\n");
	pf("3、admin\n");
	pf("4、exit\n");
	pf("-------------------\n");
}
//系统初始化
void sams_init(void){
	//申请堆内存、加载数据
	STU = calloc(MAX_STU,sizeof(Student));
	TEA = calloc(MAX_TEA,sizeof(Teacher));
	//加载校长第一次登陆标志位、老师人数、学生人数
	FILE *frp_flag = fopen("flag.txt","r");
	if(NULL == frp_flag) return;
	fscanf(frp_flag,"%d %d %d",&flag,&count,&count1);
	
	//加载老师离校标志位
	FILE *frp_flag_tea_ex = fopen("flag_tea_ex.txt","r");
	if(NULL == frp_flag_tea_ex) return;
	for(int i=0;i<count;i++){
		fscanf(frp_flag_tea_ex,"%d",&TEA[i].flag_tea_ex);
	}

	//加载学生离校标志位
	FILE *frp_flag_stu_ex = fopen("flag_stu_ex.txt","r");
	if(NULL == frp_flag_stu_ex) return;
	for(int i=0;i<count1;i++){
		fscanf(frp_flag_stu_ex,"%d",&STU[i].flag_stu_ex);
	}

	//加载学生密码、学生第一次登陆标志位的标志位
	FILE *frp_stu_passwd_flag = fopen("stu_passwd_flag.txt","r");
	if(NULL == frp_stu_passwd_flag) return;
	for(int i=0;i<count1;i++){
		fscanf(frp_stu_passwd_flag,"%s %d",STU[i].passwd,&STU[i].flag_stu_firstlogin);
	}
	//加载学生录入成绩、学生密码错误次数的标志位
	FILE *frp_stu_flag = fopen("stu_flag.txt","r");
	if(NULL == frp_stu_flag) return;
	for(int i=0;i<count1;i++){
		fscanf(frp_stu_flag,"%d %d",&STU[i].flag_stu_grade,&STU[i].flag_stu_wrong);
	}
	
	//加载老师密码、老师第一次登陆标志位、老师密码错误次数
	FILE *frp_tea_passwd_flag = fopen("tea_passwd_flag.txt","r");
	if(NULL == frp_tea_passwd_flag) return;
	for(int i=0;i<count;i++){
		fscanf(frp_tea_passwd_flag,"%s %d %d",TEA[i].passwd,&TEA[i].flag_tea_firstlogin,&TEA[i].flag_tea_wrong);
	}

	//加载校长密码
	FILE *frp_admin_passwd = fopen("admin_passwd.txt","r");
	if(NULL == frp_admin_passwd) return;
	fscanf(frp_admin_passwd,"%s",admin_passwd1);

	//加载老师的信息
	FILE *frp_TEA_information = fopen("TEA.txt","r");
	if(NULL == frp_TEA_information) return;
	for(int i=0;i<count;i++){
		if(0 == TEA[i].flag_tea_ex){
			fscanf(frp_TEA_information,"%s %s %d",TEA[i].name,&TEA[i].sex,&TEA[i].id);
		}
	}
	
	//加载离职老师的信息
	FILE *frp_TEA_EX = fopen("TEA_ex.txt","r");
	if(NULL == frp_TEA_EX) return;
	for(int i=0;i<count;i++){
		if(TEA[i].flag_tea_ex){
			fscanf(frp_TEA_EX,"%s %s %d",TEA[i].name,&TEA[i].sex,&TEA[i].id);
		}
	}	

	//加载学生的信息
	FILE *frp_STU_information = fopen("STU_all.txt","r");
	if(NULL == frp_STU_information) return;
	for(int i=0;i<count1;i++){
		if(0 == STU[i].flag_stu_ex){
			fscanf(frp_STU_information,"%s %s %d %f %f %f %f",STU[i].name,&STU[i].sex,&STU[i].id,&STU[i].score_c,&STU[i].score_m,&STU[i].score_e,&STU[i].score_s);
		}
	}
	
	//加载离职学生的信息
	FILE *frp_STU_EX = fopen("STU_ex.txt","r");
	if(NULL == frp_STU_EX) return;
	for(int i=0;i<count1;i++){
		if(STU[i].flag_stu_ex){
			fscanf(frp_STU_EX,"%s %s %d",STU[i].name,&STU[i].sex,&STU[i].id);
		}	
	}
	pf("系统初始化...\n");
}

//系统开始运行
void sams_start(void){
	//进入系统的流程控制
	pf("系统开始运行...\n");
	while(true){
		sams_menu();
		switch(get_cmd('1','4')){
			case '1':student_start(); break;
			case '2':teacher_start(); break;
			case '3':admin_start(); break;
			case '4':return;
		}
	}
}

//系统结束
void sams_exit(void){
	//释放堆内存、保存数据
	
	//保存校长第一次登陆标志位、老师人数、学生人数
	FILE *fwp_flag = fopen("flag.txt","w");
	fprintf(fwp_flag,"%d %d %d\n",flag,count,count1);
	fclose(fwp_flag);
	
	//保存老师离校标志位
	FILE *fwp_flag_tea_ex = fopen("flag_tea_ex.txt","w");
	for(int i=0;i<count;i++){
		fprintf(fwp_flag_tea_ex,"%d\n",TEA[i].flag_tea_ex);
	}
	fclose(fwp_flag_tea_ex);

	//保存学生离校标志位
	FILE *fwp_flag_stu_ex = fopen("flag_stu_ex.txt","w");
	for(int i=0;i<count1;i++){
		fprintf(fwp_flag_stu_ex,"%d\n",STU[i].flag_stu_ex);
	}
	fclose(fwp_flag_stu_ex);
	
	//保存校长密码
	FILE *fwp_admin_passwd = fopen("admin_passwd.txt","w");
	fprintf(fwp_admin_passwd,"%s\n",admin_passwd1);
	fclose(fwp_admin_passwd);

	//保存学生密码、学生第一次登陆标志位、学生录入成绩的标志位
	FILE *fwp_stu_passwd_flag = fopen("stu_passwd_flag.txt","w");
	for(int i=0;i<count1;i++){
		fprintf(fwp_stu_passwd_flag,"%s %d\n",STU[i].passwd,STU[i].flag_stu_firstlogin);
	}	
	fclose(fwp_stu_passwd_flag);
	//保存学生入录成绩、密码错误次数的标志位
	FILE *fwp_stu_flag = fopen("stu_flag.txt","w");
	for(int i=0;i<count1;i++){
		fprintf(fwp_stu_flag,"%d %d\n",STU[i].flag_stu_grade,STU[i].flag_stu_wrong);
	}	
	fclose(fwp_stu_flag);

	//保存老师密码、老师第一次登陆标志位、老师密码错误次数
	FILE *fwp_tea_passwd_flag = fopen("tea_passwd_flag.txt","w");
	for(int i=0;i<count;i++){
		//pf("-----执行了吗-----\n");
		fprintf(fwp_tea_passwd_flag,"%s %d %d\n",TEA[i].passwd,TEA[i].flag_tea_firstlogin,TEA[i].flag_tea_wrong);
	}	
	fclose(fwp_tea_passwd_flag);
	
	//保存老师信息
	FILE *fwp_TEA_information = fopen("TEA.txt","w");
	for(int i=0;i<count;i++){
		if(0 == TEA[i].flag_tea_ex){
			fprintf(fwp_TEA_information,"%s %c %d\n",TEA[i].name,TEA[i].sex,TEA[i].id);
		}
	}
	fclose(fwp_TEA_information);

	//保存离职老师信息
	FILE *fwp_TEA_EX = fopen("TEA_ex.txt","w");
	for(int i=0;i<count;i++){
		if(TEA[i].flag_tea_ex){
			fprintf(fwp_TEA_EX,"%s %c %d\n",TEA[i].name,TEA[i].sex,TEA[i].id);
		}
	}
	fclose(fwp_TEA_EX);
	
	//保存学生信息
	FILE *fwp_STU_information = fopen("STU_all.txt","w");
	for(int i=0;i<count1;i++){
		if(0 == STU[i].flag_stu_ex){
			fprintf(fwp_STU_information,"%s %c %d %f %f %f %f\n",STU[i].name,STU[i].sex,STU[i].id,STU[i].score_c,STU[i].score_m,STU[i].score_e,STU[i].score_s);
		}
	}
	fclose(fwp_STU_information);

	//保存离校学生信息
	FILE *fwp_STU_EX = fopen("STU_ex.txt","w");
	for(int i=0;i<count1;i++){
		if(STU[i].flag_stu_ex){
			fprintf(fwp_STU_EX,"%s %c %d\n",STU[i].name,STU[i].sex,STU[i].id);
		}
	}
	fclose(fwp_STU_EX);
	free(STU);
	free(TEA);

	pf("系统退出...\n");
}
