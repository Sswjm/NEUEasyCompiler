#pragma once
#ifndef _PARSER_H_
#define _PARSER_H_

#include"SYNBL.h"

class Parser:public synbl {  //语法及语法制导翻译分析类，主要使用递归下降子程序法
public:
	~Parser() {}
	Parser(string file_name);
	void check();
	bool mainControl();   //递归下降语法分析主控程序
	vector<QuaternionNode> getQuaternion();  //返回结果的四元式序列
private:
	int i;
	bool tag;

	int offset;
	int len;
	char cat;
	char type;

	vector<QuaternionNode> Quaternion;  //四元式区，存储输出的四元式序列
	queue<string> id;  //用于存储标识符，填写符号表
	stack<Objective> sem;  //语义栈，暂存运算对象的属性值
	vector<string> tempvar;  //temporary variable 临时变量区

	void PROGRAM();
	void SUB_PROGRAM();
	void VARIABLE();
	void COM_SENTENCE();
	void ID_SEQUENCE();
	void TYPE();
	void SEN_SEQUENCE();
	void EVA_SENTENCE();
	void COND_SENTENCE();
	void LOOP_SENTENCE();
	void EXPRESSION();
	void TERM();
	void FACTOR();
	void LEXP();
	void ELSE();
	void LOP();

	void action_1();  //program() 生成program四元式
	void action_2();  //end()  生成end四元式
	void action_3();  //a1  变量声明
	void action_4();  //a2  变量声明
	void action_5();  //a3  变量声明
	void action_6();  //a4  变量声明
	void action_7();  //a5  变量声明
	void action_8();  //a6  变量声明
	void action_9();  //Push(id)  将当前标识符压入语义栈
	void action_10();  //ASSI(=)  赋值语句四元式生成函数
	void action_11(string w);  //GEQ(w)  表达式（算数与关系）四元式生成函数
	void action_12();  //IF(if)  条件语句开始四元式生成函数
	void action_13();  //EL(el)  else语句四元式生成函数
	void action_14();  //IE(ie)  条件语句结束四元式生成函数
	void action_15();  //WH()  循环语句开始四元式生成函数
	void action_16();  //Do(do)  do语句四元式生成函数
	void action_17();  //WE(we)  循环语句结束四元式生成函数
};


#endif