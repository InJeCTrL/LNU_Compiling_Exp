#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*文法：
type -> simple
		| ^ id
	    | array [ simple ] of type
simple -> integer
	     | char
		 | num dotdot num
*/
char str[1024] = {0};//输入的字符串
char *str_ptr = str;//指向输入串的指针
int MyStrcmp(char *ptr_word,char *ptr_str)
{//比较当前ptr_word的单词与ptr_str，以空格截断
	if (strstr(ptr_str,ptr_word) == str_ptr && (*(ptr_str + strlen(ptr_word)) == ' ' || *(ptr_str + strlen(ptr_word)) == 0))
		return 0;//得到相同单词
	return 1;//单词不同
}
int match(char *ptr)
{//匹配某单词，异常返回1
    if (MyStrcmp(ptr,str_ptr) == 0)
	{
		str_ptr += strlen(ptr) + 1;//str_ptr定位到下一个单词
		printf("匹配到单词： %s\n",ptr);
		return 0;//匹配到ptr相同的单词
	}
	else
	{
		printf("匹配失败 - 匹配单词错误！\n");
		return 1;
	}
}
int simple(void)
{//匹配simple(Vt)
	if (MyStrcmp("integer",str_ptr) == 0)
	{
		match("integer");
		return 0;
	}
	else if (MyStrcmp("char",str_ptr) == 0)
	{
		match("char");
		return 0;
	}
	else if (MyStrcmp("num",str_ptr) == 0)
	{
		match("num");
		if (match("dotdot") == 0 && match("num") == 0)
			return 0;
		return 1;
	}
	else
		return 1;
}
int type(void)
{//匹配type(Vt)
	if (MyStrcmp("integer",str_ptr) == 0 ||
		MyStrcmp("char",str_ptr) == 0 ||
		MyStrcmp("number",str_ptr) == 0)
	{
		return simple();
	}
	else if (MyStrcmp("^",str_ptr) == 0)
	{
		match("^");
		if (match("id") == 0)
			return 0;
		return 1;
	}
	else if (MyStrcmp("array",str_ptr) == 0)
	{
		match("array");
		if (match("[") == 0 && simple() == 0 && match("]") == 0 && match("of") == 0 && type() == 0)
			return 0;
		return 1;
	}
	else
		return 1;
}

int main(void)
{
	gets(str);//输入串
	printf("\n");
	if (simple() == 0 || type() == 0)
	{
		printf("输入串匹配成功\n");
	}
	else
	{
		printf("输入串匹配失败\n");
	}
	printf("\n");
	system("pause");
	return 0;
}