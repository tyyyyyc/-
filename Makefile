CC=gcc
STD=-std=gnu99
# pipe 通过管道生成目标文件 O2 优化级别 Wall生成更多警告 Werror把警告当错误
FLAG=-pipe  -Wall -Werror
OBJ=tools.o student.o teacher.o admin.o sams.o main.o
BIN=sams

all:$(OBJ)
	$(CC) $(STD) $(FLAG) $(OBJ) -o $(BIN)
	./$(BIN)

%.o:%.c
	$(CC) $(STD) $(FLAG) -c $< -o$@
clean:
	rm $(OBJ) $(BIN) 
