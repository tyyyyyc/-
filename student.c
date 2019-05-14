#include "student.h"
#include "struct.h"
#include "tools.h"
#include "sams.h"

Student* STU;
int now_stu;
int temp;
float score_sc,score_sm,score_se;
char stu_passwd[10] = {};
char stu_passwd2[10] = {};
int arr_c[100] = {};
int arr_m[100] = {};
int arr_e[100] = {};
int arr_s[100] = {};

//进入学生系统
void student_menu(){
	pf("欢迎进入学生系统...\n");
	pf("1、查询成绩\n");
	pf("2、修改密码\n");
	pf("3、查看个人信息\n");
	pf("4、退出学生系统\n");
	pf("------------------\n");
}

//判断学生是否存在
bool is_stu_id_exist(int id)
{
	int i;
	for(i=0; i<count1; i++)
	{
		if(id == STU[i].id && 0 == STU[i].flag_stu_ex)
		{
			now_stu = i;
			break;
		}
	}
	return i==count1?false:true;
}

//修改密码
void change_passwd(void)
{
	char str[10] = {};
	char str1[10] = {};
	pf("请输入密码:\n");
	get_passwd(str,true,10);
	if(strcmp(str,STU[now_stu].passwd) == 0)
	{
		pf("请输入你要修改的密码:\n");
		get_passwd(str1,true,10);
		strcpy(STU[now_stu].passwd,str1);
		pf("修改成功\n");
		return;
	}
	else
	{
		pf("密码不正确\n");
	}
}

// 显示学生信息
void stu_information(void)
{
	    pf("学号:%d 姓名:%s 性别:%s \n",STU[now_stu].id,STU[now_stu].name,
        'm' == STU[now_stu].sex ? "男" : "女");
}

//学生进入系统
void student_start(void)
{
	int id1;
	pf("请输入学号：\n");
	sf("%d",&id1);
	getchar();
	if(is_stu_id_exist(id1) && 1 == STU[now_stu].flag_stu_ex)
	{
		pf("该学生不存在...\n");
		return;
	}
	else if(is_stu_id_exist(id1) && STU[now_stu].flag_stu_wrong<3 && 0 == STU[now_stu].flag_stu_ex)
	{	
		if(0 == STU[now_stu].flag_stu_firstlogin)
		{
			printf("密码：\n");
			get_passwd(stu_passwd,true,10);
			pf("请修改你的密码:\n");
			get_passwd(STU[now_stu].passwd,true,10);
			STU[now_stu].flag_stu_firstlogin = 1;
		}
		pf("输入密码:\n");
		get_passwd(stu_passwd2,true,10);
		if(0 == strcmp(stu_passwd2,STU[now_stu].passwd))
		{
			printf("密码正确!\n");
			while(true)
			{
				student_menu();
				switch(get_cmd('1','4'))
				{
					case '1': find_stu_score(); break;
					case '2': change_passwd(); break;
					case '3': stu_information(); break;
					case '4': return;
				}
			}
		}
		else
		{	
			pf("密码错误！\n");
			STU[now_stu].flag_stu_wrong ++ ;
			return;
		}
	}
	if(STU[now_stu].flag_stu_wrong >= 3)
	{
		pf("该帐号已被锁定! -请联系老师解锁-\n");
		pf("请输入任意键继续...\n");
		getch();
		return;
	}
}

// 语文成绩排名
void stu_rank_c(void)
{
	for(int i=0;i<count1;i++)
	{
		if(0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade)
		{
			arr_c[i] = STU[i].score_c;
		}
		pf("%d ",arr_c[i]);
	}
	for(int i=0;i<count1;i++)
	{
		if(0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade)
		{
			for(int j=i+1;j<count1;j++)
			{
				if(arr_c[i] < arr_c[j])
				{
    				temp = arr_c[i];
					arr_c[i] = arr_c[j];
					arr_c[j] = temp;
				}
			}
		}
	}
	for(int x=0;x<count1;x++)
	{
		if(STU[now_stu].score_c == arr_c[x])
		{
			printf("语文排名:%d",x+1);
		}	
	}
}

// 数学成绩排名
void stu_rank_m(void)
{
	for(int i=0;i<count1;i++)
	{
		if(0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade)
		{
			arr_m[i] = STU[i].score_m;
		}
	}
    for(int i=0;i<count1;i++)
	{
		if(0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade)
		{
			for(int j=i+1;j<count1;j++)
			{
				if(arr_m[i] < arr_m[j])
				{
    				temp = arr_m[i];
					arr_m[i] = arr_m[j];
					arr_m[j] = temp;
				}
			}
		}
	}
	for(int x=0;x<count1;x++)
	{
		if(STU[now_stu].score_m == arr_m[x])
		{
			printf("数学排名:%d",x+1);
		}	
	}
}

// 英语成绩排名
void stu_rank_e(void)
{
	for(int i=0;i<count1;i++)
	{
		if(0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade)
		{
			arr_e[i] = STU[i].score_e;
		}
	}
    for(int i=0;i<count1;i++)
	{
		if(0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade)
		{
			for(int j=i+1;j<count1;j++)
			{
				if(arr_e[i] < arr_e[j])
				{
    				temp = arr_e[i];
					arr_e[i] = arr_e[j];
					arr_e[j] = temp;
				}
			}
		}
	}
	for(int x=0;x<count1;x++)
	{
		if(STU[now_stu].score_e == arr_e[x])
		{
			printf("英语排名:%d",x+1);
		}	
	}
}

// 总分成绩排名
void stu_rank_s(void)
{
   	for(int i=0;i<count1;i++)
	{
		if(0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade)
		{
			arr_s[i] = STU[i].score_c + STU[i].score_m + STU[i].score_e;
		}
		pf("%d ",arr_s[i]);
	}
	for(int i=0;i<count1;i++)
	{
		if(0 == STU[i].flag_stu_ex && 1 == STU[i].flag_stu_grade)
		{
			for(int j=i+1;j<count1;j++)
			{
				if(arr_s[i] < arr_s[j])
				{
    				temp = arr_s[i];
					arr_s[i] = arr_s[j];
					arr_s[j] = temp;
				}
			}
		}
	}
	for(int x=0;x<count1;x++)
	{
		if(STU[now_stu].score_s == arr_s[x])
		{
			printf("总成绩排名:%d",x+1);
		}	
	}
}
//平均成绩
void average(void)
{
	for(int i=0;i<count1;i++)
	{
		score_sc += STU[i].score_c; 
		score_sm += STU[i].score_m;
		score_se += STU[i].score_e;
	}
	printf("语文：%f\t 数学：%f\t 英语: %f\t",score_sc/count1,score_sm/count1,score_se/count1);
}

//学生成绩
void stu_score(void)
{
    pf("学号:%d 姓名:%s 语文:%f 数学%f 英语:%f 总分%f\n",
        STU[now_stu].id,STU[now_stu].name,STU[now_stu].score_c,STU[now_stu].score_m,
        STU[now_stu].score_e,STU[now_stu].score_s);
}
//学生排名
void find_stu_paiming()
{
	while(true)
	{
		clear_src();
		pf("---查询成绩排名---\n");
		printf("1、语文\n");
		printf("2、数学\n");
		printf("3、英语\n");
		printf("4、总分\n");
		pf("5、年段语文、数学、英语平均成绩\n");
		printf("6、返回\n");
		switch(get_cmd('1', '6'))
		{
			case '1': stu_rank_c(); break;
			case '2': stu_rank_m(); break;
			case '3': stu_rank_e(); break;
			case '4': stu_rank_s(); break;
			case '5': average(); break;
			case '6': return;
		}
	}
}

// 显示学生成绩
void find_stu_score(void)
{
	while(true)
	{
		pf("---查询成绩---\n");
		printf("1、各科成绩\n");
		printf("2、查询排名\n");
		printf("3、返回\n");
		switch(get_cmd('1', '3'))
		{
			case '1': stu_score(); break;
			case '2': find_stu_paiming(); break;
			case '3': return;
		}
	}
}
