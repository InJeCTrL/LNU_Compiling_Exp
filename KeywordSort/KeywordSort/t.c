#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
	char str[2048] = {0};//������ַ���(���п��ܰ����ؼ���)
	char Keywords[32][10] = {"while","if","else","return","switch","for","do","break","auto",
							 "short","int","long","float","double","char","struct","union",
							 "enum","typedef","const","unsigned","signed","extern","register",
							 "static","volatile","void","goto","continue","default","sizeof","case"};
	char *ptr = NULL;
	int KeyNum[32] = {0};//�ؼ��ֳ��ִ���
	int i;
	gets(str);//�����ַ���
	
	for (i=0;i<32;i++)
	{//������йؼ����Ƿ����
		ptr = str;//ÿ�μ��ӿ�ͷ��ʼ
		while (ptr = strstr(ptr,Keywords[i]))
		{
			KeyNum[i]++;//���ҵ��ؼ�����ؼ�����������
			ptr++;//����ʶ���
		}
	}
	for (i=0;i<32;i++)
	{
		printf("Number of keyword \" %s \" is %d\n",Keywords[i],KeyNum[i]);
	}

	system("pause");
	return 0;
}
