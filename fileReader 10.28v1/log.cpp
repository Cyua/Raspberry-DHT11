#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <iostream>

using namespace std;

// 获取当前时间
int getTime(char* out, int fmt)
{
	if(out == NULL)
		return -1;
	time_t t;
	struct tm *tp;
	t = time(NULL);

	tp = localtime(&t);
	if(fmt == 0)
	{
		sprintf(out, "%2.2d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", tp->tm_year+1900, tp->tm_mon+1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
	}
	else if(fmt == 1)
	{
		sprintf(out, "%2.2d-%2.2d-%2.2d", tp->tm_year+1900, tp->tm_mon+1, tp->tm_mday);
	}
	else if(fmt == 2)
	{
		sprintf(out, "%2.2d:%2.2d:%2.2d", tp->tm_hour, tp->tm_min, tp->tm_sec);
	}

	return 0;
}


//写入log文件
void WriteInLog(const char *fmt, ...)
{
	FILE*	pFile;			// 文件指针   
	long	log_size;		// 写入的长度
	char	buffer[500];	// 写入内容的缓存 
	size_t	result;			// 返回值是读取的内容数量
	char	tim[80];		// 当前时间的缓存
	string	log;
	getTime(tim, 0);

	// 将f格式字符串中格式符替换成后面的形参
	va_list argptr;
	va_start(argptr, fmt);			//获取fmt后面的参数
	vsprintf(buffer, fmt, argptr);	//将参数格式化到buffer中
	va_end(argptr);

	log = string(tim) + "      " + string(buffer) + "\r\n";

	//追加方式打开，如果没有该文件，则创建文件
	pFile = fopen("runstate.log", "ab+");
	if (pFile == NULL) {			// 如果文件错误，退出1   
		fputs("File error", stderr);
		exit(1);
	}

	log_size = log.length();		// 获得文件长度
	
	// 返回值是读取的内容数量 
	result = fwrite(log.c_str(), 1, log_size, pFile);
	if (result != log_size) {		// 返回值如果不是文件大小，读错误  
		fputs("fwrite error", stderr);
		exit(3);
	}
	
	// 关闭文件 
	fclose(pFile);
}


int main()
{
	// char tim[100];
	// getTime(tim, 0);
	// printf("%s\n", tim);
	// getTime(tim, 1);
	// printf("%s\n", tim);
	// getTime(tim, 2);
	// printf("%s\n", tim);
	// system("pause");

	WriteInLog("sdsfs%ddfsg", 5);
	WriteInLog("sdsfs%ddfsg", 15);
	WriteInLog("sdsfs%ddfsg", 25);
	WriteInLog("sdsfs%ddfsg", 35);
	WriteInLog("sdsfs%ddfsg", 45);
	WriteInLog("sdsfs%ddfsg", 55);

	for (int i = 0; i < 10; i++) {
		char t[] = "erttrye";
		t[0] = i + '0';
		WriteInLog("sdsfs%sdfsg", t);
	}

	WriteInLog("sdsfsdfsg");
	WriteInLog("sdsfsdfsg");
	WriteInLog("sdsfsdfsg");
	WriteInLog("sdsfsdfsg");
	WriteInLog("sdsfsdfsg");
	WriteInLog("sdsfsdfsg");
	// system("pause");
	return 0;
}