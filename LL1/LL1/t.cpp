#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<stack>
using namespace std;
int main(void)
{
	string str;//输入串
	int pos = 0;//输入串下标
	int i;//用于产生式右部逆序压栈
	stack<string> S;//分析栈
	map<string,map<string,string>> Map;//预测分析表

	//分析栈预先压入结束符和起始节点
	S.push("$");
	S.push("E");

	//预测分析表
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

	//输入输入串
	cin>>str;
	str.append("$");

	cout<<"分析栈栈顶\t输入串\t动作"<<endl;
	while (S.top() != "$")
	{//循环分析过程
		string tmp = S.top();
		cout<<"\t"<<S.top()<<"\t"<<str.substr(pos)<<"\t";
		if (tmp == str.substr(pos,1))
		{//输入串有效头与栈顶相同则分析栈出栈，输入串指针向后偏移
			S.pop();
			pos++;
			cout<<"识别到"<<tmp<<endl;
		}
		else if (Map[tmp][str.substr(pos,1)] != "")
		{//预测分析表中对应单元格有产生式
			S.pop();//分析栈先出栈
			i = 0;
			while (Map[tmp][str.substr(pos,1)].substr(Map[tmp][str.substr(pos,1)].length() - 1 - i,1) != "#")
			{//逆序入栈
				S.push(Map[tmp][str.substr(pos,1)].substr(Map[tmp][str.substr(pos,1)].length() - 1 - i,1));
				i++;
			}
			cout<<"按"<<Map[tmp][str.substr(pos,1)]<<"归约"<<endl;
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
