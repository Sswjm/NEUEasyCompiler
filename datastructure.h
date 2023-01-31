#pragma once
#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<fstream>
#include<stack>
#include<algorithm>
#include<sstream>
#include<queue>
#include <cstring>
#include <stdio.h>
#include<stdlib.h>
#include<set>
#include<cstdio>
#include<utility>
#include<map>

using namespace std;
typedef long long ll;

typedef struct TokenNode {
	string name;
	int location{};
}TokenNode;
typedef struct Objective {
	string name;
	string type;  //1 非临时变量  2 临时变量  3 常数  
	inline Objective(string Name = "", string Type = "")
	{
		name = Name;
		type = Type;
	}
}Objective;
typedef struct QuaternionNode {  //四元式数据类型
	int block;  //所属基本块  init 0
	int type;  //类型  init 0

	string op;//算符
	Objective objective1;//对象1
	Objective objective2;//对象2
	Objective result;//结果
	inline QuaternionNode(int Block, int Type, string Op, Objective Obj1, Objective Obj2, Objective Result)
	{
		block = Block;
		type = Type;
		op = Op;
		objective1 = Obj1;
		objective2 = Obj2;
		result = Result;
	}
}QuaternionNode;



#endif