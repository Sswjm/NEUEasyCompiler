/*语法分析预处理工作，包括：根据LL(1)求产生式的first集与follow集，根据first集与follow集填写LL(1)分析表*/
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<stack>
#include<set>
#include<algorithm>

using namespace std;

struct Production {
	string left;
	string right;
};
class PreTreat {
protected:
	vector<Production> productions;   //产生式集合
	vector<string> terminal;          //终结符集合
	vector<string> nonterminal;       //非终结符集合
	set<string> first;
	set<string> follow;

	void grammarRead();
public:
	~PreTreat(){}
	PreTreat();
};