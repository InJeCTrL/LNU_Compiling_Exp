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
	char *ptr = NULL;//游标
	char *fast = NULL;//超前指针
	char t;//临时保存截断符
	int KeyNum[32] = {0};//关键字出现次数
	int i;

	gets(str);//输入字符串
	ptr = str;
	while (*ptr)
	{
		while (*ptr && *ptr == ' ')
			ptr++;//跳过空格
		fast = ptr;//超前指针赋值
		while (*fast)
		{//超前指针后转
			if (!*fast || *fast == ' ')
				break;
			fast++;
		}
		t = *fast;//保存截断符
		*fast = 0;
		for (i=0;i<32;i++)
		{//检查所有关键字是否出现
			if (strcmp(ptr,Keywords[i]) == 0)
			{
				KeyNum[i]++;//若找到关键字则关键字数量增加
			}
		}
		*fast = t;//恢复截断符
		ptr = fast;
	}

	for (i=0;i<32;i++)
	{
		if (KeyNum[i])
			printf("Number of keyword \" %s \" is %d\n",Keywords[i],KeyNum[i]);
	}

	system("pause");
	return 0;
}
