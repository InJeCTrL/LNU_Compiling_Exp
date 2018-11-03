#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
int GetValueofInt(char *strptr,long *retval,int Redix)
{//��ȡ��������ֵ�������������򷵻�0�������򷵻�1
	char *ptr = NULL;
	long tret = 0;//���صļ����޷�������ֵ
	int ret;//����״̬

	ptr = strptr;//ָ��������ͷ
	while (*ptr)
	{
		if (!isdigit(*ptr) && *ptr != 'A' && *ptr != 'B' && *ptr != 'C' && *ptr != 'D' && *ptr != 'E' && *ptr != 'F')
			break;//���ϲ������֣��˳�ѭ��
		tret *= Redix;//���Խ�����
		if ((*ptr) >= 'A')
			tret += ((*ptr) - 0x30 - 7);//������ĸ���֣���������ص���ֵ
		else
			tret += ((*ptr) - 0x30);//���������֣���������ص���ֵ
		ptr++;
	}
	if (*ptr)
		return 0;//��������(���������ַ�)
	*retval = tret;//������ֵ
	return 1;//������
}
int IsNum(char *strItem,long *retval,double *retval_double)
{//�ж��ַ���ָ���Ƿ���һ���޷�������1����������0����������2����С��
	char *ptr = NULL;
	char *pE = NULL;//ָ��E/e��ָ��
	char *Start = strItem,*End = NULL;//�ַ���ͷָ�롢βָ�� 
	long tRet = 0;//�����ص��޷�������ֵ
	double tRet_f = 0;//�����ص��޷���С����ֵ
	long intp = 0;//��������
	double deci = 0;//С������
	int NegHead = 0;//��ѧ������ָ�������Ƿ�Ϊ��

	ptr = strItem;
	//�ж�Hex��Oct������0
	if (*ptr == '0' && *(ptr + 1) != '.')//��ͷ��0������С����
	{
		if (!*(ptr + 1))
		{//������0
			*retval = 0;
			return 1;
		}
		else if (*(ptr + 1) == 'x')
		{//������Hex
			ptr += 2;//����"0x"
			if (GetValueofInt(ptr,&tRet,16))
			{
				*retval = tRet;//�����޷���Hex��ֵ
				return 1;
			}
		}
		else if (isdigit(*(ptr + 1)))
		{//������Oct
			ptr++;//����"0"
			if (GetValueofInt(ptr,&tRet,8))
			{
				*retval = tRet;//�����޷���Oct��ֵ
				return 1;
			}
		}
		else
			return 0;//����HexҲ����OctҲ����0
	}
	//�ж�Dec(����)
	if (GetValueofInt(ptr,&tRet,10))
	{
		*retval = tRet;//�����޷���Dec������ֵ
		return 1;
	}
	//�ж�Dec(С����ѧ����)
	if ((pE = strchr(strItem,'E')) || (pE = strchr(strItem,'e')))
	{//�ҵ���ѧ������E/e
		*pE = 0;
		if (IsNum(strItem,&intp,&deci))
		{//E֮ǰ�����Ѽ���
			tRet_f = intp + deci;
			deci = intp = 0;
			*pE = 'E';//�ָ�E
			if (*(pE + 1) == '-')
			{//��ѧ����ָ��Ϊ����
				NegHead = 1;
				pE += 2;//Խ������
			}
			else
				pE++;
			if (IsNum(pE,&intp,&deci))
			{//E֮�������Ѽ���
				if (NegHead)
					tRet_f *= pow(10,-(intp+deci));//��ѧ����ָ��Ϊ����
				else
					tRet_f *= pow(10,intp+deci);//��ѧ����ָ��Ϊ����
				*retval_double = tRet_f;//���ؿ�ѧ����ֵ
				return 2;
			}
			else
				return 0;
		}
		else
			return 0;
	}

	//�ж�Dec(С����������)
	while (*ptr)
	{
		if (!isdigit(*ptr) && *ptr != '.')
			return 0;//��������Ҳ����С����
		else if (isdigit(*ptr))
			ptr++;//�����������ָ��
		else if (*ptr == '.')
		{//�ҵ���һ��С����
			End = ptr + 1;
			while (*End)
			{
				if (!isdigit(*End))
					return 0;//��������
				else
					End++;//�����������ָ��
			}
			End--;
			while (*End != '.')
			{//��ʼ����С�����ֵ���ֵ��������deci
				deci += (*End - 0x30);
				deci *= 0.1;
				End--;
			}
			while (*strItem != '.')
			{//��ʼ�����������ֵ���ֵ��������intp
				intp *= 10;
				intp += (*strItem - 0x30);
				strItem++;
			}
			*retval_double = intp + deci;//������ֵ
			return 2;
		}
	}

}

int main(void)
{
	int n,i,ret;
	long val_i;//�������֣����ص�����
	double val_f;//�������֣����صĸ�����ֵ
	char **strList = NULL;
	printf("Ҫ����n���ַ�����n = ");
	scanf("%d",&n);
	getchar();
	strList = (char**)malloc(n*sizeof(char*));
	for (i=0;i<n;i++)
	{
		strList[i] = (char*)malloc(n*sizeof(char*));
		printf("�� %d ��:\n",i+1);
		gets(strList[i]);
	}
	printf("\n\n");
	for (i=0;i<n;i++)
	{
		ret = IsNum(strList[i],&val_i,&val_f);
		if (ret == 1)
			printf("No.%d is an Integer, value is %ld .\n",i+1,val_i);//�ж�����
		else if (ret == 2)
			printf("No.%d is a Float, value is %lf .\n",i+1,val_f);//�жϸ�����
		else
			printf("No.%d is not a number.\n",i+1);//�жϲ�����
	}

	system("pause");
	return 0;
}
