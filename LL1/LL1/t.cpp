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

	cout<<"����ջջ��\t���봮\t����"<<endl;
	while (S.top() != "$")
	{//ѭ����������
		string tmp = S.top();
		cout<<"\t"<<S.top()<<"\t"<<str.substr(pos)<<"\t";
		if (tmp == str.substr(pos,1))
		{//���봮��Чͷ��ջ����ͬ�����ջ��ջ�����봮ָ�����ƫ��
			S.pop();
			pos++;
			cout<<"ʶ��"<<tmp<<endl;
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
			cout<<"��"<<Map[tmp][str.substr(pos,1)]<<"��Լ"<<endl;
		}
		else
		{
			cout<<"Sytax Error!"<<endl;
			break;
		}
	}
	system("pause");
	return 0;
}
