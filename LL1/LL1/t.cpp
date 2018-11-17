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

	printf("%10s%20s%20s\n","分析栈","输入串","动作");
	while (S.top() != "$")
	{//循环分析过程
		stack<string> tStack;//临时栈
		string tmp = S.top();
		string tsinf = "";//临时栈输出内容
		string outStr = "";//临时输出动作字符串
		while (!S.empty())
		{//倒栈
			tStack.push(S.top());
			S.pop();
		}
		while (!tStack.empty())
		{//输出栈内容到字符串
			S.push(tStack.top());
			tStack.pop();
			tsinf.append(S.top());
		}
		printf("%-10s%20s",tsinf.c_str(),str.substr(pos).c_str());
		if (tmp == str.substr(pos,1))
		{//输入串有效头与栈顶相同则分析栈出栈，输入串指针向后偏移
			S.pop();
			pos++;
			outStr.append("识别到");
			outStr.append(tmp);
			printf("%20s\n",outStr.c_str());
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
			outStr.append("按");
			outStr.append(Map[tmp][str.substr(pos,1)]);
			outStr.append("归约");
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
