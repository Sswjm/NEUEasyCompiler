#pragma once
#ifndef _SYNBL_H_
#define _SYNBL_H_

#include"lexanalyse.h"
class synbl :public LexAnalyser//���ű�
{
public:

	struct symbol {
		string name;		//name
		char type;		//����
		char cat;	//����
		int offset;
	};
	vector<symbol>sym;
	int sym_search(string str);
	void init_symbol();
	void enter(string id, char type, char cat, int offset);
	void synbl_print();
};


#endif
