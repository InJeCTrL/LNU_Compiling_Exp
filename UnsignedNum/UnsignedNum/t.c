#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
int GetValueofInt(char *strptr,long *retval,int Redix)
{//获取整数的数值，若不是整数则返回0，若是则返回1
	char *ptr = NULL;
	long tret = 0;//返回的计算无符号数数值
	int ret;//返回状态

	ptr = strptr;//指向整数开头
	while (*ptr)
	{
		if (!isdigit(*ptr) && *ptr != 'A' && *ptr != 'B' && *ptr != 'C' && *ptr != 'D' && *ptr != 'E' && *ptr != 'F')
			break;//遇上不是数字，退出循环
		tret *= Redix;//乘以进制数
		if ((*ptr) >= 'A')
			tret += ((*ptr) - 0x30 - 7);//加入字母数字，计算待返回的数值
		else
			tret += ((*ptr) - 0x30);//加入新数字，计算待返回的数值
		ptr++;
	}
	if (*ptr)
		return 0;//不是整数(遇到其它字符)
	*retval = tret;//传回数值
	return 1;//是整数
}
int IsNum(char *strItem,long *retval,double *retval_double)
{//判断字符串指向是否是一个无符号数，1：是整数，0：不是数，2：是小数
	char *ptr = NULL;
	char *pE = NULL;//指向E/e的指针
	char *Start = strItem,*End = NULL;//字符串头指针、尾指针 
	long tRet = 0;//待传回的无符号数数值
	double tRet_f = 0;//待传回的无符号小数数值
	long intp = 0;//整数部分
	double deci = 0;//小数部分
	int NegHead = 0;//科学计数的指数部分是否为负

	ptr = strItem;
	//判断Hex、Oct整数、0
	if (*ptr == '0' && *(ptr + 1) != '.')//开头是0并且无小数点
	{
		if (!*(ptr + 1))
		{//可能是0
			*retval = 0;
			return 1;
		}
		else if (*(ptr + 1) == 'x')
		{//可能是Hex
			ptr += 2;//跳过"0x"
			if (GetValueofInt(ptr,&tRet,16))
			{
				*retval = tRet;//传回无符号Hex数值
				return 1;
			}
		}
		else if (isdigit(*(ptr + 1)))
		{//可能是Oct
			ptr++;//跳过"0"
			if (GetValueofInt(ptr,&tRet,8))
			{
				*retval = tRet;//传回无符号Oct数值
				return 1;
			}
		}
		else
			return 0;//不是Hex也不是Oct也不是0
	}
	//判断Dec(整数)
	if (GetValueofInt(ptr,&tRet,10))
	{
		*retval = tRet;//传回无符号Dec整数数值
		return 1;
	}
	//判断Dec(小数科学计数)
	if ((pE = strchr(strItem,'E')) || (pE = strchr(strItem,'e')))
	{//找到科学计数的E/e
		*pE = 0;
		if (IsNum(strItem,&intp,&deci))
		{//E之前内容已计数
			tRet_f = intp + deci;
			deci = intp = 0;
			*pE = 'E';//恢复E
			if (*(pE + 1) == '-')
			{//科学计数指数为负数
				NegHead = 1;
				pE += 2;//越过负号
			}
			else
				pE++;
			if (IsNum(pE,&intp,&deci))
			{//E之后内容已计数
				if (NegHead)
					tRet_f *= pow(10,-(intp+deci));//科学计数指数为负数
				else
					tRet_f *= pow(10,intp+deci);//科学计数指数为正数
				*retval_double = tRet_f;//传回科学计数值
				return 2;
			}
			else
				return 0;
		}
		else
			return 0;
	}

	//判断Dec(小数正常计数)
	while (*ptr)
	{
		if (!isdigit(*ptr) && *ptr != '.')
			return 0;//不是数字也不是小数点
		else if (isdigit(*ptr))
			ptr++;//是数字则后移指针
		else if (*ptr == '.')
		{//找到第一个小数点
			End = ptr + 1;
			while (*End)
			{
				if (!isdigit(*End))
					return 0;//不是数字
				else
					End++;//是数字则后移指针
			}
			End--;
			while (*End != '.')
			{//开始处理小数部分的数值，并存入deci
				deci += (*End - 0x30);
				deci *= 0.1;
				End--;
			}
			while (*strItem != '.')
			{//开始处理整数部分的数值，并存入intp
				intp *= 10;
				intp += (*strItem - 0x30);
				strItem++;
			}
			*retval_double = intp + deci;//传回数值
			return 2;
		}
	}

}

int main(void)
{
	int n,i,ret;
	long val_i;//若是数字，返回的整数
	double val_f;//若是数字，返回的浮点数值
	char **strList = NULL;
	printf("要输入n组字符串，n = ");
	scanf("%d",&n);
	getchar();
	strList = (char**)malloc(n*sizeof(char*));
	for (i=0;i<n;i++)
	{
		strList[i] = (char*)malloc(n*sizeof(char*));
		printf("第 %d 组:\n",i+1);
		gets(strList[i]);
	}
	printf("\n\n");
	for (i=0;i<n;i++)
	{
		ret = IsNum(strList[i],&val_i,&val_f);
		if (ret == 1)
			printf("No.%d is an Integer, value is %ld .\n",i+1,val_i);//判断整数
		else if (ret == 2)
			printf("No.%d is a Float, value is %lf .\n",i+1,val_f);//判断浮点数
		else
			printf("No.%d is not a number.\n",i+1);//判断不是数
	}

	system("pause");
	return 0;
}
