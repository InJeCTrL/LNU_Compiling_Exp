#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*�ķ���
type -> simple
		| ^ id
	    | array [ simple ] of type
simple -> integer
	     | char
		 | num dotdot num
*/
char str[1024] = {0};//������ַ���
char *str_ptr = str;//ָ�����봮��ָ��
int MyStrcmp(char *ptr_word,char *ptr_str)
{//�Ƚϵ�ǰptr_word�ĵ�����ptr_str���Կո�ض�
	if (strstr(ptr_str,ptr_word) == str_ptr && (*(ptr_str + strlen(ptr_word)) == ' ' || *(ptr_str + strlen(ptr_word)) == 0))
		return 0;//�õ���ͬ����
	return 1;//���ʲ�ͬ
}
int match(char *ptr)
{//ƥ��ĳ���ʣ��쳣����1
    if (MyStrcmp(ptr,str_ptr) == 0)
	{
		str_ptr += strlen(ptr) + 1;//str_ptr��λ����һ������
		printf("ƥ�䵽���ʣ� %s\n",ptr);
		return 0;//ƥ�䵽ptr��ͬ�ĵ���
	}
	else
	{
		printf("ƥ��ʧ�� - ƥ�䵥�ʴ���\n");
		return 1;
	}
}
int simple(void)
{//ƥ��simple(Vt)
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
{//ƥ��type(Vt)
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
	gets(str);//���봮
	printf("\n");
	if (simple() == 0 || type() == 0)
	{
		printf("���봮ƥ��ɹ�\n");
	}
	else
	{
		printf("���봮ƥ��ʧ��\n");
	}
	printf("\n");
	system("pause");
	return 0;
}