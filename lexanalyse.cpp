#include"lexanalyse.h"

int LexAnalyser::IfLetter(char ch)                       //判断字母
{
	if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
		return 1;
	else
		return 0;
}

int LexAnalyser::IfDigit(char ch)                       //判断数字
{
	if (ch >= '0' && ch <= '9')
		return 1;
	else
		return 0;
}
string LexAnalyser::Convert(double Num)	//float转string
{
	ostringstream oss;
	oss << Num;
	string str(oss.str());
	return str;
}
string LexAnalyser::Convert2(ll Num)	//ll转string
{
	ostringstream oss;
	oss << Num;
	string str(oss.str());
	return str;
}
//常数识别机 ll存入CT double存入RT
void LexAnalyser::constant(string s)
{
	double ans = 0;//结果s 
	bool t = 0;//常数类型 整数0 实型1 
	ll e = 1;//指数的符号 + 1  - -1
	ll f = 1;//常数的符号 
	ll p = 0, m = 0;//p是指数位  m是小数位数 
	int i;

	for (i = 0; i < s.size(); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
			ans = ans * 10 + (s[i] - '0');
		else if (s[i] == '.')
		{
			t = 1;
			break;
		}
		else if (s[i] == 'e')
		{
			break;
		}
		else if (s[i] == '-')
			f = -1;
	}
	for (i = i; i < s.size(); i++)
	{
		if (t == 0)
			break;
		if (s[i] >= '0' && s[i] <= '9')
		{
			ans = ans * 10 + (s[i] - '0');
			m++;
		}
		else if (s[i] == 'e')
		{
			break;
		}
	}
	for (i = i; i < s.size(); i++)
	{
		if (t == 0)
			t = 1;
		if (s[i] == '-')
			e = -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			p = p * 10 + (s[i] - '0');
		}
	}
	TokenNode token;
	if (t == 1)
	{
		ans = f * ans * pow(10, (e * p - m));//
		string temp = Convert(ans);
		vector<string>::iterator i;
		i = RT.begin();
		int num = 0, bo = 0;
		while (i != RT.end())
		{
			num++;
			if (*i == temp)
			{
				bo = 1;
				break;
			}
			i++;
		}
		if (bo == 1)
		{
			token.name = "RT";
			token.location = num;
			Token.push_back(token);
		}
		else
		{
			token.name = "RT";
			token.location = num + 1;
			RT.push_back(temp);
			Token.push_back(token);
		}
	}
	if (t == 0)
	{
		ans = ans * f;
		string temp = Convert2((ll)ans);
		vector<string>::iterator i;
		i = CT.begin();
		int num = 0, bo = 0;
		while (i != CT.end())
		{
			num++;
			if (*i == temp)
			{
				bo = 1;
				break;
			}
			i++;
		}
		if (bo == 1)
		{
			token.name = "CT";
			token.location = num;
			Token.push_back(token);
		}
		else
		{
			token.name = "CT";
			token.location = num + 1;
			CT.push_back(temp);
			Token.push_back(token);
		}
	}
}

int LexAnalyser::reserve(char* strt)      //查关键字
{
	string str = strt;
	vector<string>::iterator i;
	i = KT.begin();
	int num = 0;
	while (i != KT.end())
	{
		num++;
		if (*i == str)
			return num;
		i++;
	}
	return 0;
}

int LexAnalyser::reserve2(char* strt)      //查界符
{
	string str = strt;
	vector<string>::iterator i;
	i = PT.begin();
	int num = 0;
	while (i != PT.end())
	{
		num++;
		if (*i == str)
			return num;
		i++;
	}
	return 0;
}
int LexAnalyser::InsertIT(char* strt)   //标识符
{
	string str = strt;
	vector<string>::iterator i;
	i = IT.begin();
	int num = 0;
	string s = strt;
	while (i != IT.end())
	{
		num++;
		if (*i == s)
			return num;
		i++;
	}
	IT.push_back(s);
	return num + 1;
}
int LexAnalyser::InsertcT(char* strt)
{
	string str = strt;
	vector<string>::iterator i;
	i = cT.begin();
	int num = 0;
	string s = strt;
	while (i != cT.end())
	{
		num++;
		if (*i == s)
			return num;
		i++;
	}
	cT.push_back(s);
	return num + 1;
}
int LexAnalyser::InsertST(char* strt)
{
	string str = strt;
	vector<string>::iterator i;
	i = ST.begin();
	int num = 0;
	string s = strt;
	while (i != ST.end())
	{
		num++;
		if (*i == s)
			return num;
		i++;
	}
	ST.push_back(s);
	return num + 1;
}
void LexAnalyser::Print()
{
	vector<TokenNode>::iterator i;
	i = Token.begin();
	TokenNode t;
	while (i != Token.end())
	{
		t = *i;
		cout << t.name << " " << t.location << endl;
		i++;
	}
}

void LexAnalyser::lexical(string line)
{

	int i_line;            //line中第i个字符 
	char ch, strt[50];
	int value, i_str;            //当前单词中的第i个字符 
	TokenNode token;
	i_line = 0;
	ch = line[i_line++];
	while (ch)
	{
		i_str = 0;
		while (ch == ' ' || ch == '\n')
			ch = line[i_line++];

		if (IfLetter(ch))				//字母开头的 
		{
			while (IfLetter(ch) || IfDigit(ch))   //若是字母或数字 
			{
				strt[i_str++] = ch;       //拼接到strt中
				ch = line[i_line++];
			}
			strt[i_str] = '\0';
			value = reserve(strt);     //查关键字表；

			if (value)				//不是关键字就是标识符 
			{
				token.name = "KT";
				token.location = value;
				Token.push_back(token);
			}
			else
			{
				value = InsertIT(strt);
				token.name = "IT";
				token.location = value;
				Token.push_back(token);
			}
		}

		else if (IfDigit(ch))           //常数开头的
		{
			int e_n = 0, d_n = 0;
			while (IfDigit(ch) || ch == 'e' || ch == '.')//add error pending   -needing
			{
				if (ch == 'e')
				{
					if (e_n == 0)
						e_n = 1;
					else
					{
						cout << "词法错误error：CT/RT" << endl;
						exit(0);
					}
				}
				if (ch == '.')
				{
					if (d_n == 0)
						d_n = 1;
					else
					{
						cout << "词法错误error：CT/RT" << endl;
						exit(0);
					}
				}
				strt[i_str++] = ch;
				ch = line[i_line++];
			}
			constant((string)strt);
		}
		else if (ch == 34 || ch == 39)      //34="   39='
		{
			if (ch == 39)//单 
			{

				ch = line[i_line++];
				strt[0] = ch;
				ch = line[i_line++];
				ch = line[i_line++];
				strt[1] = '\0';
				value = InsertcT(strt);
				token.name = "cT";
				token.location = value;
				Token.push_back(token);
			}
			else
			{
				ch = line[i_line++];
				while (IfLetter(ch))
				{
					strt[i_str++] = ch;       //拼接到strt中
					ch = line[i_line++];
				}
				ch = line[i_line++];
				strt[i_str] = '\0';
				value = InsertST(strt);
				token.name = "ST";
				token.location = value;
				Token.push_back(token);
			}
		}
		else
		{
			strt[i_str++] = ch;
			if (ch == ':')
			{
				ch = line[i_line];
				if (ch == '=')
				{
					strt[i_str++] = ch;
					i_line++;
				}
			}
			if (ch == '>')
			{
				ch = line[i_line];
				if (ch == '=')
				{
					strt[i_str++] = ch;
					i_line++;
				}
			}
			if (ch == '<')
			{
				ch = line[i_line];
				if (ch == '=')
				{
					strt[i_str++] = ch;
					i_line++;
				}
			}
			strt[i_str] = '\0';
			value = reserve2(strt);
			if (value)
			{
				token.name = "PT";
				token.location = value;
				Token.push_back(token);
			}
			else
			{
				cout << "词法错误error：PT" << endl;
				exit(0);
			}
			ch = line[i_line++];
		}
	}
}


void LexAnalyser::lexAnalyse(string file_name) {
	ifstream input_file(file_name);
	string file_string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
	lexical(file_string);

}
