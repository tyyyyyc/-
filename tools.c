#include <get_keyboard.h>
#include "tools.h"
#include "struct.h"
#include "sams.h"

void clear_stdin(void){
	stdin->_IO_read_ptr = stdin->_IO_read_end;
}

void clear_src(void){
	system("clear");
}

// 任意键继续
void anykey_continue(void)
{
    pf("按任意键继续...");
    get_keyboard();
    pf("\n");
}

/*char get_str(char *str,size_t n){
	if(NULL == str || 0 == n) return NULL;

	size_t index = 0;
    while(index < n-1)
    {
        int8_t key_val = getch();
        if(KEY_ESC == key_val) return NULL;
        if(KEY_ENTER == key_val) break;
        if(KEY_BACKSPACE == key_val)
        {
            if(index > 0)
            {
                pf("\b \b");
                index--;
            }
            continue;
        }
        pf("%c",key_val);
        str[index++] = key_val;
    }
    
    str[index] = '\0';
    
    pf("\n");

    clear_stdin();

    return str;
}*/

char get_cmd(char start,char end){
	clear_stdin();
	pf("请输入指令：");
	while(true){
		char val = get_keyboard();	
		if(val >= start && val <= end){
			pf("%c\n",val);
			return val;
		}
	}
}


/*bool is_first_login(int* flag_first_login,size_t n){
	return 0 == flag_first_login[n]?true:false;	 
}*/
char* get_passwd(char* passwd,bool is_show,size_t size){
	if(NULL == passwd) return NULL;

	int count = 0;
	do{
		char val = get_keyboard();
		if(127 == val){
			if(count>0){
				printf("\b \b");
				count--;
			}
			continue;
		}else if(10 == val){
			printf("\n");
			break;	
		}
		passwd[count++] = val;
		if(is_show) printf("*");
	}while(count < size-1);

	passwd[count] = '\0';
	return passwd;
}

char* get_name(char* passwd,size_t size){
	if(NULL == passwd) return NULL;

	int count = 0;
	do{
		char val = get_keyboard();
		if(127 == val){
			if(count>0){
				printf("\b \b");
				count--;
			}
			continue;
		}else if(10 == val){
			printf("\n");
			break;	
		}
		passwd[count++] = val;
		printf("%c",val);
	}while(count < size-1);

	passwd[count] = '\0';
	return passwd;
}

/*void show_teachers(void){
	for(int i=0;i<count;i++){
		printf("姓名：%s\t性别：%s\t工号：%d\n",TEA[i].name,'w'==TEA[i].sex?"女":"男",TEA[i].id);	
	}
}*/

/*void scan_teachers(Teacher* TEA){
	printf("请输入姓名，性别（w：女m：男），工号：\n");
	scanf("%s%s%d",TEA->name,&TEA->sex,&TEA->id);
}*/

/*void show_students(void){
	for(int i=0;i<count1;i++){
		printf("姓名：%s\t性别：%s\t学号：%dt\n",STU[i].name,'w'==STU[i].sex?"女":"男",STU[i].id);
	}	
}*/
/*void show_students_grade(void){
	for(int i=0;i<count1;i++){
		printf("姓名：%s\t性别：%s\t学号：%d\t语文：%d\t数学：%d\t英语：%d\t\n",STU[i].name,'w'==STU[i].sex?"女":"男",STU[i].id,STU[i].Chinese_grade,STU[i].Math_grade,STU[i].English_grade);
	}	
}*/
