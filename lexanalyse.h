#pragma once
#ifndef _LEXANALYSE_H_
#define _LEXANALYSE_H_

#include"datastructure.h"
class LexAnalyser {
protected:
	void lexAnalyse(string file_name);
	void Print();
	vector<TokenNode> Token;  //存储Token序列，以便进行后续操作
	vector<string> KT = { "program","var","integer","real","char","begin","end","if","then","else","while","do" };//关键词表
	vector<string> PT = { ",",":",";",":=","*","/","+","-",".","(",")" ,"<",">","<=",">=","=="};//界符表
	vector<string> IT;//标识符表
	vector<string> CT;//常整数表
	vector<string> RT;//实数表（小数）
	vector<string> cT;//字符表
	vector<string> ST;//字符串表
private:
	int IfLetter(char ch);
	int IfDigit(char ch);
	string Convert(double Num);
	string Convert2(ll Num);
	void constant(string s);
	int reserve(char* strt);
	int reserve2(char* strt);
	int InsertIT(char* strt);
	int InsertcT(char* strt);
	int InsertST(char* strt);
	void lexical(string line);
};



#endif
