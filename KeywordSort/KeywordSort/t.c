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
	char *ptr = NULL;//�α�
	char *fast = NULL;//��ǰָ��
	char t;//��ʱ����ضϷ�
	int KeyNum[32] = {0};//�ؼ��ֳ��ִ���
	int i;

	gets(str);//�����ַ���
	ptr = str;
	while (*ptr)
	{
		while (*ptr && *ptr == ' ')
			ptr++;//�����ո�
		fast = ptr;//��ǰָ�븳ֵ
		while (*fast)
		{//��ǰָ���ת
			if (!*fast || *fast == ' ')
				break;
			fast++;
		}
		t = *fast;//����ضϷ�
		*fast = 0;
		for (i=0;i<32;i++)
		{//������йؼ����Ƿ����
			if (strcmp(ptr,Keywords[i]) == 0)
			{
				KeyNum[i]++;//���ҵ��ؼ�����ؼ�����������
			}
		}
		*fast = t;//�ָ��ضϷ�
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
