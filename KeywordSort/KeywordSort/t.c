#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
	char str[2048] = {0};//输入的字符串(其中可能包含关键字)
	char Keywords[32][10] = {"while","if","else","return","switch","for","do","break","auto",
							 "short","int","long","float","double","char","struct","union",
							 "enum","typedef","const","unsigned","signed","extern","register",
							 "static","volatile","void","goto","continue","default","sizeof","case"};
	char *ptr = NULL;
	int KeyNum[32] = {0};//关键字出现次数
	int i;
	gets(str);//输入字符串
	
	for (i=0;i<32;i++)
	{//检查所有关键字是否出现
		ptr = str;//每次检查从开头开始
		while (ptr = strstr(ptr,Keywords[i]))
		{
			KeyNum[i]++;//若找到关键字则关键字数量增加
			ptr++;//跳过识别点
		}
	}
	for (i=0;i<32;i++)
	{
		printf("Number of keyword \" %s \" is %d\n",Keywords[i],KeyNum[i]);
	}

	system("pause");
	return 0;
}
