#include "struct.h"
#include "teacher.h"
#include "tools.h"
#include "sams.h"

Teacher *TEA;
int count1; //记录学生的人数
char tea_passwd[10] = {}; //教师第一次登陆随便输入的密码
char tea_passwd2[10] = {}; //再次确定密码
void teacher_menu()
{
	clear_src();
	pf("欢迎进入教师管理系统...\n");
	pf("1、添加学生\n");
	pf("2、删除学生\n");
	pf("3、查找学生\n");
	pf("4、修改学生信息\n");
	pf("5、录入学生成绩\n");
	pf("6、重置学生密码\n");
	pf("7、显示所有在校学生信息\n");
	pf("8、显示所有退学学生信息\n");
	pf("9、退出管理员系统\n");
	pf("------------------\n");
}

void add_stu_single()
{ //单个添加
	if(count1 >= MAX_STU)
    {
        pf("*** 学生已满,无法添加! ***");
        return;
    }
	printf("姓名: 性别(m.男 w.女):\n");
	scanf("%s %c", STU[count1].name, &STU[count1].sex);
	getchar();
	STU[count1].id = 201600 + count1; //学号自动生成
	count1 ++;
}

void add_stu_volume(){	//批量添加
	if(count1 >= MAX_STU)
    {
        pf("*** 学生已满,无法添加! ***");
        return;
    }
	printf("输入录入的学生数:");
	int num;
	sf("%d", &num);
	getchar();
    printf("姓名: 性别(m.男 w.女):\n");	
	for(int i=0; i<num; i++)
	{
		sf("%s %c", STU[count1].name, &STU[count1].sex);
		getchar();
		STU[count1].id = 201600 + count1; //学号自动生成
		count1 ++;
	}
}

void tea_add_stu(void)
{
	while(true)
	{
		clear_src();
		pf("---添加学生---\n");
		printf("1、单个添加\n");
		printf("2、批量添加\n");
		printf("3、返回\n");
		switch(get_cmd('1', '3'))
		{
			case '1': add_stu_single(); break;
			case '2': add_stu_volume(); break;
			case '3': return;
		}
	}
}


void tea_del_stu(void)
{  //删除学生
	if(0 >= count1)
    {
        pf("*** 系统内无学生! ***");
        return;
    }
	int id1,id2;
	printf("请输入删除人学号：\n");	
	scanf("%d",&id1);
	getchar();
	pf("请确认学号：\n");
	scanf("%d",&id2);
	getchar();
	if(id1 == id2)
	{ 
		for(int i=0;i<count1;i++)
		{
			if(id1 == STU[i].id && 0 == STU[i].flag_stu_ex)
			{
				STU[i].flag_stu_ex = 1;
				pf("删除学生成功");
				return;
			}	
		}
		pf("学生不存在\n");
	}
	else
		pf("两次输入的学号不一致！");
		return;
}

void search_stu_by_name()
{  //按姓名查找学生
	char str[20] = {};
	printf("输入姓名:");
	scanf("%s",str);
	getchar();
	for(int i=0;i<count1;i++){	
		if(0 == strcmp(STU[i].name,str) && 0 == STU[i].flag_stu_ex){
			printf("姓名：%s\t性别：%s\t学号：%d\t\n",STU[i].name,'w'==STU[i].sex?"女":"男",STU[i].id);
		}	
	}
	printf("请输入任意键继续...\n");
	getch();
}

void search_stu_by_id()
{	//按学号查找学生
	int id;
	printf("输入学号:");
	scanf("%d",&id);
	getchar();
	for(int i=0;i<count1;i++)
	{	
		if(STU[i].id == id && 0 == STU[i].flag_stu_ex)
		{
			printf("姓名：%s\t性别：%s\t学号：%d\t\n",STU[i].name,'w'==STU[i].sex?"女":"男",STU[i].id);
		}
	}
	printf("请输入任意键继续...\n");
	getch();
}

void find_stu(void){
	while(true)
	{
		clear_src();
		printf("1.按姓名查找\n");
		printf("2.按学号查找\n");
		printf("3.返回\n");
		switch(get_cmd('1', '3'))
		{
			case '1': search_stu_by_name(); break;
			case '2': search_stu_by_id(); break;
			case '3': return;
		}
	}
}
void change_stu_basic_information()
{ //修改学生基础信息
	int id;
	printf("输入修改学生的学号:");
   	scanf("%d",&id);
	getchar();
   	for(int i=0;i<count1;i++){
		if(id == STU[i].id && 0 == STU[i].flag_stu_ex){
			while(true){
        		clear_src();
        		puts("***请选择要修改的学生信息***");
        		puts("   1.修改学生姓名");
        		puts("   2.修改学生性别");
        		puts("   3.返回上一级");
        		puts("-------------------------");
        		switch(get_cmd('1','3')){
            		case '1': 
                		pf("学生姓名:%s\n",STU[i].name);
						pf("请输入修改的名字：");
                		sf("%s",STU[i].name);
						getchar();		 break;
            		case '2':
                		pf("学生性别:%c",STU[i].sex);
						pf("请输入要修改的性别:");
                		sf("%c",&STU[i].sex);
						getchar();		 break;
            		case '3': 				return;
        		}
        		pf("*** 修改成功! ***");
    		}
		}
//		else
//			pf("此学生不存在");
//			return;
    }	
}
void change_stu_grade()
{  //修改学生成绩
	int id;
	printf("输入修改学生的学号:");
   	scanf("%d",&id);
	getchar();
   	for(int i=0;i<count1;i++){
		if(id == STU[i].id && 0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade){
			printf("语文:%f\t数学:%f\t英语:%f\t\n", STU[i].score_c, STU[i].score_m, STU[i].score_e);
			printf("修改语文:  数学:  英语:\n");
			scanf("%f %f %f", &STU[i].score_c, &STU[i].score_m, &STU[i].score_e);
			getchar();
			pf("修改成功");
	    	break;
		}
		if(id == STU[i].id && 0 == STU[i].flag_stu_ex && 0 == STU[i].flag_stu_grade){
			pf("该学生还没有录入成绩");
			return;
		}
    }
}	

void change_stu_information(void){
	while(true)
	{
		clear_src();
		printf("1.修改学生基础信息\n");
		printf("2.修改学生成绩\n");
		printf("3.返回\n");
		switch(get_cmd('1', '3'))
		{
			case '1': change_stu_basic_information(); break;
			case '2': change_stu_grade(); break;
			case '3': return;
		}
	}
}

void add_stu_grade_single()
{  //单个录入学生成绩
	int id;	
	printf("输入学生的学号:");
   	scanf("%d",&id);
	getchar();
   	for(int i=0; i<count1; i++)
	{
		if(id == STU[i].id && 0 == STU[i].flag_stu_ex)
		{
			printf("语文: 数学: 英语:\n");
			sf("%f %f %f",&STU[i].score_c,&STU[i].score_m,&STU[i].score_e);
			getchar();
			STU[i].flag_stu_grade = 1;
			pf("录入成功！\n");
	    	break;
		}
    }
}

void add_stu_grade_volume()  //批量录入学生成绩
{
 	int n;
	int id;
	printf("输入录入学生的人数:");
	scanf("%d",&n);
	getchar();
   	for(int i=0; i<n; i++)
	{
		printf("学号:\n");
		scanf("%d",&id);
		getchar();	
		for(int j=0;j<count1;j++)
		{
			if(id == STU[j].id && 0 == STU[j].flag_stu_ex)
			{
				pf("语文： 数学： 英语：\n");
				sf("%f %f %f",&STU[j].score_c,&STU[j].score_m,&STU[j].score_e);
				getchar();
				STU[j].flag_stu_grade = 1;
				pf("录入成功！\n");
				break;
			}
		}
	}
}

void login_stu_grade(void)
{
	while(true)
	{
		clear_src();
		printf("1.单个录入\n");
		printf("2.批量录入\n");
		printf("3.返回\n");
		switch(get_cmd('1', '3'))
		{
			case '1': add_stu_grade_single(); break;
			case '2': add_stu_grade_volume(); break;
			case '3': return;
		}
	}
}

void tea_unlock_stu(void)
{  //解锁学生帐号
	if(0 >= count1)
    {
        pf("*** 系统内无学生! ***");
        return;
    }
	int id;
	printf("输入学生的学号:");
   	scanf("%d",&id);
	getchar();
	for(int i=0;i<count1;i++)
	{
		if(id == STU[i].id)
		{
			strcpy(STU[i].passwd, "123456");
			STU[i].flag_stu_firstlogin = 0;
			printf("解锁成功\n");
			return;
    	}
	}
}

void list_now_stu(void)
{  //显示在校学生信息
	for(int i=0;i<count1;i++)
	{
		STU[i].score_s = STU[i].score_c + STU[i].score_m + STU[i].score_e;
	}
	for(int i=0;i<count1;i++)
	{
		if(0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade)
		{
			printf("姓名：%s\t性别：%s\t学号：%d\t语文：%f\t数学：%f\t英语：%f\t 总分:%f\t\n",STU[i].name,'w'==STU[i].sex?"女":"男",STU[i].id,STU[i].score_c,STU[i].score_m,STU[i].score_e,STU[i].score_s);
		}
		else if(0 == STU[i].flag_stu_ex && 0 == STU[i].flag_stu_grade)
		{
			printf("姓名：%s\t性别：%s\t学号：%d\t\n",STU[i].name,'w'==STU[i].sex?"女":"男",STU[i].id);
		}	
	}
	printf("请输入任意键继续...\n");
	getch();
}

void list_ex_stu(void
){  //显示开除学籍学生信息
	for(int i=0;i<count1;i++){
		if(1 == STU[i].flag_stu_ex)
		{
			printf("姓名：%s\t性别：%s\t学号：%d\t\n",STU[i].name,'w'==STU[i].sex?"女":"男",STU[i].id);
		}	
	}
	printf("请输入任意键继续...\n");
	getch();
}



void teacher_start(void)
{
	int id;
	pf("请输入工号：\n");
	sf("%d",&id);
	getchar();
	for(int i=0;i<count;i++)
	{
		if(id == TEA[i].id && 1 == TEA[i].flag_tea_ex)
		{
			pf("该教师不存在...\n");
			return;
		}
		//pf("先前%d\n",TEA[i].flag_tea_firstlogin);
		else if(id == TEA[i].id && TEA[i].flag_tea_wrong<3 && 0 == TEA[i].flag_tea_ex)
		{
			if(0 == TEA[i].flag_tea_firstlogin)
			{
				printf("密码：\n");
				get_passwd(tea_passwd,true,10);
				pf("请修改你的密码:\n");
				get_passwd(TEA[i].passwd,true,10);
				TEA[i].flag_tea_firstlogin = 1;
				//pf("之后%d\n",TEA[i].flag_tea_firstlogin);
			}
			pf("输入密码:\n");
			get_passwd(tea_passwd2,true,10);
			if(0 == strcmp(tea_passwd2,TEA[i].passwd))
			{
				printf("密码正确!\n");
				while(true)
				{
					teacher_menu();
					switch(get_cmd('1','9'))
					{
						case '1': tea_add_stu(); break;
						case '2': tea_del_stu(); break;
						case '3': find_stu(); break;
						case '4': change_stu_information(); break;
						case '5': login_stu_grade(); break;
						case '6': tea_unlock_stu(); break;
						case '7': list_now_stu(); break;
						case '8': list_ex_stu(); break;
						case '9': return;
					}
				}
			}
			else
			pf("密码错误！\n");
			TEA[i].flag_tea_wrong++;
			return;
		}
		if(TEA[i].flag_tea_wrong >= 3)
		{
			pf("该帐号已被锁定! -请联系校长解锁-\n");
			pf("请输入任意键继续...\n");
			getch();
			return;
		}
	}	
}

