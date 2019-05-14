#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getch.h>
#include <string.h>
#include <stdbool.h>
//#include "get_keyboard.h"

#define pf printf
#define sf scanf

void clear_src(void);
char get_cmd(char start,char end);
char* get_name(char* passwd,size_t size);
char* get_passwd(char* passwd,bool is_show,size_t size);

#endif//TOOLS_H
