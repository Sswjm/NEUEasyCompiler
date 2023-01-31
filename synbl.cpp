#include"SYNBL.h"
using namespace std;

int synbl::sym_search(string str)//查找变量
{
	int num = 1;
	vector<symbol>::iterator it;
	it = sym.begin();
	while (it != sym.end())
	{
		if (it->name == str)
		{
			return num;
		}
		num++;
		it++;
	}
	return 0;
}

void synbl::init_symbol()//符号表初始化
{
	vector<TokenNode>::iterator it;
	vector<string>::iterator i;
	int num;
	it = Token.begin();
	while (it != Token.end())
	{
		if (it->name == "IT")
		{

			i = IT.begin();
			i += ((it->location) - 1);
			string str = *i;
			num = sym_search(str);
			if (num == 0)
			{
				symbol sy;
				sy.name = str;
				sy.type = '&';
				sy.cat = '&';
				sy.offset = -1;
				sym.push_back(sy);
			}
		}
		it++;
	}
}

void synbl::enter(string id, char type, char cat, int offset)//插入变量
{
	int location = sym_search(id);
	vector<symbol>::iterator it;
	it = sym.begin();
	if (location)
	{
		(it + location - 1)->type = type;
		(it + location - 1)->cat = cat;
		(it + location - 1)->offset = offset;
	}
}

void synbl::synbl_print()//符号表输出
{
	cout << "SYNBL" << endl;
	cout << "name\t" << "type\t" << "cat\t" << "offset" << endl;
	vector<symbol>::iterator it;
	it = sym.begin();
	while (it != sym.end())
	{
		cout << it->name << "\t";
		if (it->type == '&')
			cout << "--\t";
		else
			cout << it->type << "\t";
		if(it->cat=='&')
			cout << "--  \t";
		else
			cout << it->cat << "\t";
		if(it->offset==-1)
			cout << "--"<<endl;
		else
		cout<< it->offset << endl;
		it++;
	}
}