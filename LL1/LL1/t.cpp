#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<stack>
using namespace std;
int main(void)
{
	string str;//���봮
	int pos = 0;//���봮�±�
	int i;//���ڲ���ʽ�Ҳ�����ѹջ
	stack<string> S;//����ջ
	map<string,map<string,string>> Map;//Ԥ�������

	//����ջԤ��ѹ�����������ʼ�ڵ�
	S.push("$");
	S.push("E");

	//Ԥ�������
	Map["E"]["i"] = "E#TR";
	Map["E"]["("] = "E#TR";
	Map["R"]["+"] = "R#+TR";
	Map["R"][")"] = "R#";
	Map["R"]["$"] = "R#";
	Map["T"]["i"] = "T#FS";
	Map["T"]["("] = "T#FS";
	Map["S"]["+"] = "S#";
	Map["S"]["*"] = "S#*FS";
	Map["S"][")"] = "S#";
	Map["S"]["$"] = "S#";
	Map["F"]["i"] = "F#i";
	Map["F"]["("] = "F#(E)";

	//�������봮
	cin>>str;
	str.append("$");

	printf("%10s%20s%20s\n","����ջ","���봮","����");
	while (S.top() != "$")
	{//ѭ����������
		stack<string> tStack;//��ʱջ
		string tmp = S.top();
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
		if (tmp == str.substr(pos,1))
		{//���봮��Чͷ��ջ����ͬ�����ջ��ջ�����봮ָ�����ƫ��
			S.pop();
			pos++;
			outStr.append("ʶ��");
			outStr.append(tmp);
			printf("%20s\n",outStr.c_str());
		}
		else if (Map[tmp][str.substr(pos,1)] != "")
		{//Ԥ��������ж�Ӧ��Ԫ���в���ʽ
			S.pop();//����ջ�ȳ�ջ
			i = 0;
			while (Map[tmp][str.substr(pos,1)].substr(Map[tmp][str.substr(pos,1)].length() - 1 - i,1) != "#")
			{//������ջ
				S.push(Map[tmp][str.substr(pos,1)].substr(Map[tmp][str.substr(pos,1)].length() - 1 - i,1));
				i++;
			}
			outStr.append("��");
			outStr.append(Map[tmp][str.substr(pos,1)]);
			outStr.append("��Լ");
			printf("%20s\n",outStr.c_str());
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
