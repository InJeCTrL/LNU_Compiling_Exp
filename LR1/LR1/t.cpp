#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<stack>
using namespace std;
int main(void)
{
	string str;//���봮
	string tStr;//��ʱ�������
	string ProdStr[7] = {"","E��E+T","E��T","T��T*F","T��F","F��(E)","F��i"};//����ʽ����
	int pos = 0;//���봮�±�
	int tN;//����ͳ�Ʋ���ʽ�Ҳ����Ÿ���
	stack<string> S;//����ջ
	map<string,map<string,string>> Map;//Ԥ�������

	//����ջԤ��ѹ���ʼ״̬����ʼ�ڵ�
	S.push("0");

	//Ԥ�������
	Map["0"]["i"] = "s5";
	Map["0"]["("] = "s4";
	Map["0"]["E"] = "1";
	Map["0"]["T"] = "2";
	Map["0"]["F"] = "3";
	Map["1"]["+"] = "s6";
	Map["1"]["$"] = "acc";
	Map["2"]["+"] = "r2";
	Map["2"]["*"] = "s7";
	Map["2"][")"] = "r2";
	Map["2"]["$"] = "r2";
	Map["3"]["+"] = "r4";
	Map["3"]["*"] = "r4";
	Map["3"][")"] = "r4";
	Map["3"]["$"] = "r4";
	Map["4"]["i"] = "s5";
	Map["4"]["("] = "s4";
	Map["4"]["E"] = "8";
	Map["4"]["T"] = "2";
	Map["4"]["F"] = "3";
	Map["5"]["+"] = "r6";
	Map["5"]["*"] = "r6";
	Map["5"][")"] = "r6";
	Map["5"]["$"] = "r6";
	Map["6"]["i"] = "s5";
	Map["6"]["("] = "s4";
	Map["6"]["T"] = "9";
	Map["6"]["F"] = "3";
	Map["7"]["i"] = "s5";
	Map["7"]["("] = "s4";
	Map["7"]["F"] = "10";
	Map["8"]["+"] = "s6";
	Map["8"][")"] = "s11";
	Map["9"]["+"] = "r1";
	Map["9"]["*"] = "s7";
	Map["9"][")"] = "r1";
	Map["9"]["$"] = "r1";
	Map["10"]["+"] = "r3";
	Map["10"]["*"] = "r3";
	Map["10"][")"] = "r3";
	Map["10"]["$"] = "r3";
	Map["11"]["+"] = "r5";
	Map["11"]["+"] = "r5";
	Map["11"]["+"] = "r5";
	Map["11"]["+"] = "r5";

	//�������봮
	cin>>str;
	str.append("$");

	printf("%10s%20s%20s\n","����ջ","���봮","����");
	while (1)
	{//ѭ����������
		stack<string> tStack;//��ʱջ
		string tsinf = "";//��ʱջ�������
		string outStr = "";//��ʱ��������ַ���
		while (!S.empty())
		{//��ջ
			tStack.push(S.top());
			S.pop();
		}
		while (!tStack.empty())
		{//���ջ���ݵ��ַ���
			S.push(tStack.top());
			tStack.pop();
			tsinf.append(S.top());
		}
		printf("%-10s%20s",tsinf.c_str(),str.substr(pos).c_str());
		if ((tStr = Map[S.top()][str.substr(pos,1)]) != "")
		{//Ԥ��������ж�Ӧ��Ԫ���й���
			if (tStr.substr(0,1) == "s")
			{//�ƽ�
				outStr.append("�ƽ�");
				outStr.append(str.substr(pos,1));
				printf("%20s\n",outStr.c_str());
				S.push(str.substr(pos,1));//���봮ͷ��ջ
				pos++;
				S.push(tStr.substr(1));//״̬��ջ
			}
			else if (tStr.substr(0,1) == "r")
			{//��Լ
				tN = ProdStr[atoi(tStr.substr(1).c_str())].length() - 3;//��Լ�Ĳ���ʽ�Ҳ����Ÿ���
				tN *= 2;
				outStr.append("��");
				outStr.append(ProdStr[atoi(tStr.substr(1).c_str())]);
				outStr.append("��Լ");
				printf("%20s\n",outStr.c_str());
				while (tN--)
					S.pop();//Ԫ����״̬��ջ
				string tS = S.top();
				S.push(ProdStr[atoi(tStr.substr(1).c_str())].substr(0,1));//Vt��ջ
				S.push(Map[tS][S.top()]);//״̬��ջ
			}
			else
			{//���
				printf("%20s\n","acc");
				break;
			}
		}
		else
		{
			printf("%20s\n","Sytax Error!");
			break;
		}
	}
	system("pause");
	return 0;
}