#include "admin.h"
#include "struct.h"
#include "sams.h"
#include "tools.h"

Teacher* TEA;
int count; //添加的教师的人数
int flag = 0; //判断是否为第一次登陆的标志位
char admin_passwd[10] = {}; //第一次登陆的密码
char admin_passwd1[10] = {}; //第一次登陆修改的密码
char admin_passwd2[10] = {}; //之后登陆的密码


void admin_menu(){
	//clear_src();
	pf("欢迎进入管理员系统...\n");
	pf("1、添加教师\n");
	pf("2、删除教师\n");
	pf("3、显示在职教师\n");
	pf("4、显示离职教师\n");
	pf("5、重置教师密码\n");
	pf("6、解锁教师密码\n");
	pf("7、重置自己密码\n");
	pf("8、退出管理员系统\n");
	pf("------------------\n");
}

//单个添加老师
void add_tea_single(void){ 
	if(count >= MAX_TEA)
    {
        pf("*** 老师已满,无法添加! ***");
        return;
    }
	printf("姓名: 性别(m.男 w.女):\n");
	scanf("%s %c", TEA[count].name, &TEA[count].sex);
	getchar();
	TEA[count].id = 20001 + count; //工号自动生成
	count ++;
}

//批量添加老师
void add_tea_volume(void){
	if(count >= MAX_TEA)
    {
        pf("*** 老师已满,无法添加! ***");
        return;
    }
	printf("输入录入的老师数:\n");
	int num;
	sf("%d", &num);
	getchar();
    printf("姓名: 性别(m.男 w.女):\n");	
	for(int i=0; i<num; i++)
	{
		sf("%s %c", TEA[count].name, &TEA[count].sex);
		getchar();
		TEA[count].id = 20001 + count;
		count ++;
	}
}

void admin_add_tea(void){
	while(true)
	{
		clear_src();
		pf("---添加老师---\n");
		printf("1、单个添加\n");
		printf("2、批量添加\n");
		printf("3、返回\n");
		switch(get_cmd('1', '3'))
		{
			case '1': add_tea_single(); break;
			case '2': add_tea_volume(); break;
			case '3': return;
		}
	}
}

//删除教师
void admin_del_tea(void){  
	if(0 >= count)
    {
        pf("*** 系统内无老师! ***");
        return;
    }
	uint32_t id;
	printf("请输入删除人工号：\n");	
	scanf("%d",&id);
	getchar();
	for(int i=0;i<MAX_TEA;i++){
		if(id == TEA[i].id){
			TEA[i].flag_tea_ex = 1;
			printf("删除教师成功\n");
			return;
		}	
	}
	printf("教师不存在\n");
}

//显示在职教师
void admin_list_tea(void){
	pf("显示在职教师\n");
	for(int i=0;i<count;i++){
		if(TEA[i].flag_tea_ex == 0){
			printf("姓名：%s\t性别：%s\t工号：%d\n",TEA[i].name,'w'==TEA[i].sex?"女":"男",TEA[i].id);
		}	
	}
	printf("请输入任意键继续...\n");
	getch();
}

//显示离职教师
void admin_list_ex_tea(void){
	pf("显示离职教师\n");
	for(int i=0;i<count;i++){
		if(TEA[i].flag_tea_ex == 1){
			printf("姓名：%s\t性别：%s\t工号：%d\n",TEA[i].name,'w'==TEA[i].sex?"女":"男",TEA[i].id);
		}	
	}
	printf("请输入任意键继续...\n");
	getch();
}

//重置教师密码
void admin_reset_tea(void){
	pf("重置教师密码\n");
	uint32_t id;
	printf("请输入要重置教师的工号：\n");	
	scanf("%d",&id);
	for(int i=0;i<count;i++){
		if(id == TEA[i].id){
			strcpy(TEA[i].passwd,"123456");
			TEA[i].flag_tea_firstlogin = 0;
			count1 = 0;
			pf("重置成功\n");
			return;
		}
	}
	pf("教师不存在\n");
}

//解锁教师密码
void admin_unlock_tea(void){
	pf("解锁教师密码\n");
	uint32_t id;
	printf("请输入要解锁教师的工号：\n");	
	scanf("%d",&id);
	for(int i=0;i<count;i++){
		if(id == TEA[i].id){
			TEA[i].flag_tea_wrong = 0;
			pf("解锁成功\n");
			return;
		}
	}
	pf("教师不存在\n");
}

//重置自己密码
void admin_reset_me(void){
	if(1 == flag){
		strcpy(admin_passwd,"123456");
		flag = 0;
		pf("重置成功\n");
		return;
	}
}

 //校长第一次登陆强行修改密码
bool admin_login(void){ 
	if(0 == flag){
		printf("密码：\n");
		get_passwd(admin_passwd,true,10);
		pf("请修改你的密码：\n");
		get_passwd(admin_passwd1,true,10);
		flag = 1;
	}
	pf("输入密码:\n");
	get_passwd(admin_passwd2,true,10);
	if(0 == strcmp(admin_passwd2,admin_passwd1)){
		printf("密码正确!\n");
		return true;
	}
		else 
		return false;	
}

void admin_start(void){
	if(!admin_login()){
		pf("密码错误！\n");
		return;
	}
	while(true){
		admin_menu();
		switch(get_cmd('1','8')){
			case '1': admin_add_tea(); break;
			case '2': admin_del_tea(); break;
			case '3': admin_list_tea(); break;
			case '4': admin_list_ex_tea(); break;
			case '5': admin_reset_tea(); break;
			case '6': admin_unlock_tea(); break;
			case '7': admin_reset_me(); break;
			case '8': return;
		}
	}
}
