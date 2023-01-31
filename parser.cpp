/*���õݹ��½��ӳ���ʵ���﷨����*/
#include"parser.h"

Parser::Parser(string file_name)
{
	i = 0;
	tag = true;
	offset = 0;
	len = 0;
	cat = 'v';
	type = 'i';
	lexAnalyse(file_name);  //��ʼ��token����
}
void Parser::check() 
{
	cout << "Token Sequence: " << endl;
	Print();
	cout << "Quaternion Sequence: " << endl;
	vector<QuaternionNode>::iterator pList = Quaternion.begin();
	for (pList;pList != Quaternion.end();pList++) {
		cout << "(" << pList->op << ", " << pList->objective1.name << ", " << pList->objective2.name << ", " << pList->result.name << ")" << endl;
	}
}
vector<QuaternionNode> Parser::getQuaternion()
{
	return Quaternion;
}

//�﷨����ʵ��

bool Parser::mainControl()
{

	TokenNode t = { "#", 1 };
	Token.push_back(t);
	i = 0; //next(w)
	PROGRAM();
	if (Token[i].name != "#") {
		tag = false;
	}

	return tag;
}
void Parser::PROGRAM()
{
	if (Token[i].name == "KT" && Token[i].location == 1) {  //"program"
		action_1();
		i++;  //next(w)
		if (Token[i].name == "IT") {  //id
			i++;  //next(w)
			SUB_PROGRAM();
			if (Token[i].name == "PT" && Token[i].location == 9) { //"."
				action_2();
				i++;  //next(w)
			}
			else {
				tag = false; //error
			}
		}
		else {
			tag = false; //error
		}
	}
	else {
		tag = false;  //error
	}
}
void Parser::SUB_PROGRAM()
{
	VARIABLE();
	COM_SENTENCE();
}
void Parser::VARIABLE()
{
	if (Token[i].name == "KT" && Token[i].location == 2) {  //"var"
		action_3();

		i++;  //next(w)
		ID_SEQUENCE();
		if (Token[i].name == "PT" && Token[i].location == 2) {  //":"
			i++;  //next(w)
			TYPE();

			action_8();
			if (Token[i].name == "PT" && Token[i].location == 3) {  //";"
				i++;  //next(w)
			}
			else {
				tag = false;  //error
			}
		}
		else {
			tag = false;  //error
		}
	}
	else {
		tag = false;  //error
	}
}
void Parser::ID_SEQUENCE()
{
	if (Token[i].name == "IT") {  //"id"
		action_4();
		i++;  //next(w)
		while (Token[i].name == "PT" && Token[i].location == 1) {  //","
			i++;  //next(w)
			if (Token[i].name == "IT") {
				action_4();
				i++;
			}
			else {
				tag = false;  //error
				break;
			}
		}
	}
	else {
		tag = false;  //error
	}
}
void Parser::TYPE()
{
	if (Token[i].name == "KT" && Token[i].location == 3) {  //"integer"
		action_5();
		i++;  //next(w)
	}
	else if (Token[i].name == "KT" && Token[i].location == 4) {  //"real"
		action_6();
		i++;  //next(w)
	}
	else if (Token[i].name == "KT" && Token[i].location == 5) {  //"char"
		action_7();
		i++;  //next(w)
	}
	else {
		tag = false;
	}
}

//without if and while
/*void Parser::COM_SENTENCE()
{
	if (Token[i].name == "KT" && Token[i].location == 6) {  //"begin"
		i++;  //next(w)
		SEN_SEQUENCE();
		if (Token[i].name == "KT" && Token[i].location == 7) {  //"end"
			i++;  //next(w)
		}
		else {
			tag = false;
		}
	}
	else {
		tag = false;
	}
}
void Parser::SEN_SEQUENCE()
{
	EVA_SENTENCE();
	while (Token[i].name == "PT" && Token[i].location == 3) {  //";"
		i++;  //next(w)
		EVA_SENTENCE();
	}
}*/

void Parser::EVA_SENTENCE()
{
	if (Token[i].name == "IT") {  //id
		action_9();
		i++;  //next(w)
		if (Token[i].name == "PT" && Token[i].location == 4) {  //":="
			i++;  //next(w)
			EXPRESSION();
			action_10();
		}
		else {
			tag = false;
		}
	}
	else {
		//tag = false;
		return;
	}
}

//with if and while
void Parser::COM_SENTENCE()
{
	if (Token[i].name == "KT" && Token[i].location == 6) {  //"begin"
		i++;  //next(w)
		SEN_SEQUENCE();
		while (Token[i].name == "PT" && Token[i].location == 3) {  //";"
			i++;  //next(w)
			SEN_SEQUENCE();
		}
		if (Token[i].name == "KT" && Token[i].location == 7) {  //"end"
			i++;
		}
		else {
			tag = false;
		}
	}
	else {
		//tag = false;
		return;
	}
}
void Parser::SEN_SEQUENCE()
{
	if (Token[i].name == "IT") {  //id
		EVA_SENTENCE();
	}
	else if (Token[i].name == "KT" && Token[i].location == 8) {  //if
		COND_SENTENCE();
	}
	else if (Token[i].name == "KT" && Token[i].location == 11) {  //while
		LOOP_SENTENCE();
	}
	else if (Token[i].name == "KT" && Token[i].location == 6) {  //begin
		COM_SENTENCE();
	}
	else {
		tag = false;
	}
}
void Parser::COND_SENTENCE()
{
	if (Token[i].name == "KT" && Token[i].location == 8) {  //if
		i++;  //next(w)
		LEXP();
		action_12();
		if (Token[i].name == "KT" && Token[i].location == 9) {  //then
			i++;  //next(w)
			SEN_SEQUENCE();
			ELSE();
			action_14();
		}
		else {
			tag = false;
		}
	}
	else {
		return;
	}
}
void Parser::LOOP_SENTENCE() 
{
	if (Token[i].name == "KT" && Token[i].location == 11) {  // while
		action_15();
		i++;  //next(w)
		LEXP();
		if (Token[i].name == "KT" && Token[i].location == 12) {  //do
			action_16();
			i++;  //next(w)
			SEN_SEQUENCE();
			action_17();
		}
		else {
			tag = false;
		}
	}
	else {
		return;
	}
}
/*void Parser::SEN_SEQUENCE()
{
	if (Token[i].name == "IT") {  //"id"
		i++;  //next(w)
		if (Token[i].name == "KT" && Token[i].location == 4) {  //":="
			i++;  //next(w)
			EXPRESSION();
		}
		else {
			tag = false; 
		}
	}
	else if (Token[i].name == "KT" && Token[i].location == 8) {  //"if"
		i++;  //next(w)
		LEXP();
		if (Token[i].name == "KT" && Token[i].location == 9) {  //"then"
			i++;  //next(w)
			SEN_SEQUENCE();
			ELSE();
		}
		else {
			tag = false;
		}
	}
	else if (Token[i].name == "KT" && Token[i].location == 11) {  //"while"
		i++;  //next(w)
		LEXP();
		if (Token[i].name == "KT" && Token[i].location == 12) {  //"do"
			i++;  //next(w)
			SEN_SEQUENCE();
		}
		else {
			tag = false;
		}
	}
	else if(Token[i].name == "KT" && Token[i].location == 6){  //"begin"	
		i++;  //next(w)
		SEN_SEQUENCE();
		while (Token[i].name == "PT" && Token[i].location == 3) {  //";"
			i++;  //next(w)
			SEN_SEQUENCE();
		}
		if (Token[i].name == "KT" && Token[i].location == 7) {  //"end"
			i++;
		}
		else {
			tag = false;
		}	
	}
	else {
		tag = false;
	}
}*/
void Parser::EXPRESSION()    //�������ʽ�﷨�������ƻ�ʹ��LL1�����������Ҳ���Լ���ʹ�õݹ��½���������Ҫ�޸��ķ���
{
	TERM();
	while (true) {
		if (Token[i].name == "PT" && Token[i].location == 7) {  // +
			i++;
			TERM();
			action_11("+");
		}
		else if (Token[i].name == "PT" && Token[i].location == 8) {  // -
			i++;
			TERM();
			action_11("-");
		}
		else {
			break;
		}
	}
}
void Parser::TERM()
{
	FACTOR();
	while (true) {
		if (Token[i].name == "PT" && Token[i].location == 5) {  // *
			i++;
			TERM();
			action_11("*");
		}
		else if (Token[i].name == "PT" && Token[i].location == 6) {  // /
			i++;
			TERM();
			action_11("/");
		}
		else {
			break;
		}
	}
}
void Parser::FACTOR()
{
	if (Token[i].name == "IT" || Token[i].name == "CT") {  //id or cons
		action_9();
		i++;  //next(w)
	}
	else if (Token[i].name == "PT" && Token[i].location == 10) {  //(
		i++;  //next(w)
		EXPRESSION();
		if (Token[i].name == "PT" && Token[i].location == 11) {  //)
			i++;
		}
		else {
			tag = false;
		}
	}
	else {
		tag = false;
	}
}
void Parser::ELSE()
{
	if (Token[i].name == "KT" && Token[i].location == 10) {
		action_13();
		i++;  //next(w)
		SEN_SEQUENCE();
	}
}
void Parser::LEXP()
{
	EXPRESSION();
	if (Token[i].name == "PT" && Token[i].location == 12) {  // <
		i++;  //next(w)
		EXPRESSION();
		action_11("<");
	}
	else if (Token[i].name == "PT" && Token[i].location == 13) {  // >
		i++;  //next(w)
		EXPRESSION();
		action_11(">");
	}
	else if (Token[i].name == "PT" && Token[i].location == 14) {  // <=
		i++;  //next(w)
		EXPRESSION();
		action_11("<=");
	}
	else if (Token[i].name == "PT" && Token[i].location == 15) {  // >=
		i++;  //next(w)
		EXPRESSION();
		action_11(">=");
	}
	else if (Token[i].name == "PT" && Token[i].location == 16) {  // ==
		i++;  //next(w)
		EXPRESSION();
		action_11("==");
	}
	else {
		tag = false;
	}
}
void Parser::LOP()
{
	if (Token[i].name == "PT" && Token[i].location == 12) {  // <
		i++;  //next(w)
	}
	else if (Token[i].name == "PT" && Token[i].location == 13) {  // >
		i++;  //next(w)
	}
	else if (Token[i].name == "PT" && Token[i].location == 14) {  // <=
		i++;  //next(w)
	}
	else if (Token[i].name == "PT" && Token[i].location == 15) {  // >=
		i++;  //next(w)
	}
	else if (Token[i].name == "PT" && Token[i].location == 16) {  // ==
		i++;  //next(w)
	}
	else {
		tag = false;
	}
}

//�﷨�Ƶ�������������ʵ��

void Parser::action_1() //Program()
{
	Objective obj_1("I1", "1");
	Objective obj_2("", "");
	Objective res("", "");
	QuaternionNode quat(0, 3, "program", obj_1, obj_2, res);   //����һ���µĳ���ʼ��Ԫʽ
	Quaternion.push_back(quat);  //������Ԫʽ����
}
void Parser::action_2() //end()
{
	Objective obj_1("I1", "1");
	Objective obj_2("", "");
	Objective res("", "");
	QuaternionNode quat(0, 3, "end", obj_1, obj_2, res);   //����һ���µĳ��������Ԫʽ
	Quaternion.push_back(quat);  //������Ԫʽ����
}
void Parser::action_3() //a1
{
	/*���÷��ű��б������� (cat) Ϊ v �� offset�����ࣩΪ0*/
	cat = 'v';
	offset = 0;
}
void Parser::action_4() //a2
{
	/*id.entry = token.val, push(id_entry)*/
	int l = Token[i].location; 
	string id_entry = IT[l - 1];
	id.push(id_entry);
}
void Parser::action_5() //a3  integer
{
	/*type = i, len = 4*/
	type = 'i';
	len = 4;
}
void Parser::action_6() //a4  real
{
	/*type = r, len = 8*/
	type = 'r';
	len = 8;
}
void Parser::action_7() //a5 char
{
	/*type = c, len = 1*/
	type = 'c';
	len = 1;
}
void Parser::action_8() //a6
{
	/*fill in the symbol table*/
	while (!id.empty()) {
		string id_entry = id.front();
		id.pop();
		enter(id_entry, type, cat, offset);
		offset = offset + len;
	}
}


void Parser::action_9()  //push
{
	string token_name;
	int add;
	if (Token[i].name == "IT") {
		add = Token[i].location - 1;
		token_name = IT[add];
		Objective obj(token_name, "1");  //������������ʱ����
		sem.push(obj);  //������token�������ű�����ƺ�λ����Ϊ������Ϣ��������ջ
	}
	if (Token[i].name == "CT") {
		add = Token[i].location - 1;
		token_name = CT[add];
		Objective obj(token_name, "3");  //����ֵ������
		sem.push(obj);
	}
}
void Parser::action_10() //ASSI(=)
{
	string w = ":=";
	Objective obj_1 = sem.top();  //sem[m]
	sem.pop();
	Objective res = sem.top();  //sem[m-1]
	sem.pop();
	Objective obj_2("", "");

	QuaternionNode quat(0, 0, w, obj_1, obj_2, res); //����һ���µĸ�ֵ��Ԫʽ
	Quaternion.push_back(quat);  //������Ԫʽ����
}
void Parser::action_11(string w)  //GEQ(w)
{
	int location_tempvar = tempvar.size();
	string t_name = "t" + to_string(location_tempvar + 1);   //�����µ���ʱ����t
	tempvar.push_back(t_name);  //������ʱ��������

	Objective obj_2 = sem.top();
	sem.pop();
	Objective obj_1 = sem.top();
	sem.pop();
	Objective t(t_name, "2");
	
	QuaternionNode quat(0, 2, w, obj_1, obj_2, t);  //����һ���µ���Ԫʽ
	Quaternion.push_back(quat);  //������Ԫʽ����
	sem.push(t);  //����ʱ����t��������ջ
}
void Parser::action_12()  // IF(if) ������俪ʼ��Ԫʽ
{
	string w = "if";
	Objective obj_1 = sem.top();
	sem.pop();
	Objective obj_2("", "");
	Objective result("", "");

	QuaternionNode quat(0, 3, w, obj_1, obj_2, result);
	Quaternion.push_back(quat);
}
void Parser::action_13()    //EL(el)  else��Ԫʽ���ɺ���
{
	string w = "el";
	Objective obj_1("", "");
	Objective obj_2("", "");
	Objective result("", "");

	QuaternionNode quat(0, 3, w, obj_1, obj_2, result);
	Quaternion.push_back(quat);
}
void Parser::action_14()   //IE(ie)  ������������Ԫʽ
{
	string w = "ie";
	Objective obj_1("", "");
	Objective obj_2("", "");
	Objective result("", "");

	QuaternionNode quat(0, 3, w, obj_1, obj_2, result);
	Quaternion.push_back(quat);
}
void Parser::action_15()   //WH()  ѭ����俪ʼ��Ԫʽ
{
	string w = "wh";
	Objective obj_1("", "");
	Objective obj_2("", "");
	Objective result("", "");

	QuaternionNode quat(0, 3, w, obj_1, obj_2, result);
	Quaternion.push_back(quat);
}
void Parser::action_16()    //DO()  do�����Ԫʽ����
{
	string w = "el";
	Objective obj_1 = sem.top();
	sem.pop();
	Objective obj_2("", "");
	Objective result("", "");

	QuaternionNode quat(0, 3, w, obj_1, obj_2, result);
	Quaternion.push_back(quat);
}
void Parser::action_17()   //WE(we)  ѭ����������Ԫʽ����
{
	string w = "we";
	Objective obj_1("", "");
	Objective obj_2("", "");
	Objective result("", "");

	QuaternionNode quat(0, 3, w, obj_1, obj_2, result);
	Quaternion.push_back(quat);
}