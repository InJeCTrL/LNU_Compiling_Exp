#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<stack>
using namespace std;
int main(void)
{
	string str;//输入串
	string tStr;//临时保存规则
	string ProdStr[7] = {"","E→E+T","E→T","T→T*F","T→F","F→(E)","F→i"};//产生式集合
	int pos = 0;//输入串下标
	int tN;//用于统计产生式右部符号个数
	stack<string> S;//分析栈
	map<string,map<string,string>> Map;//预测分析表

	//分析栈预先压入初始状态和起始节点
	S.push("0");

	//预测分析表
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

	//输入输入串
	cin>>str;
	str.append("$");

	printf("%10s%20s%20s\n","分析栈","输入串","动作");
	while (1)
	{//循环分析过程
		stack<string> tStack;//临时栈
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
		if ((tStr = Map[S.top()][str.substr(pos,1)]) != "")
		{//预测分析表中对应单元格有规则
			if (tStr.substr(0,1) == "s")
			{//移进
				outStr.append("移进");
				outStr.append(str.substr(pos,1));
				printf("%20s\n",outStr.c_str());
				S.push(str.substr(pos,1));//输入串头入栈
				pos++;
				S.push(tStr.substr(1));//状态入栈
			}
			else if (tStr.substr(0,1) == "r")
			{//归约
				tN = ProdStr[atoi(tStr.substr(1).c_str())].length() - 3;//归约的产生式右部符号个数
				tN *= 2;
				outStr.append("按");
				outStr.append(ProdStr[atoi(tStr.substr(1).c_str())]);
				outStr.append("归约");
				printf("%20s\n",outStr.c_str());
				while (tN--)
					S.pop();//元素与状态出栈
				string tS = S.top();
				S.push(ProdStr[atoi(tStr.substr(1).c_str())].substr(0,1));//Vt入栈
				S.push(Map[tS][S.top()]);//状态入栈
			}
			else
			{//完成
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