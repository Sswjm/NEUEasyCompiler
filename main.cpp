#include"parser.h"
#include"objectivecode.h"


int main()
{
	vector<QuaternionNode> qua;
	string file_name = "test1.txt";
	Parser parser(file_name);
	parser.init_symbol();
	bool is_right = parser.mainControl();
	//读出四元式
	if (is_right) {
		qua = parser.getQuaternion();
		cout << "Grammer is right" << endl;
		cout << endl;
	}
	else {
		cout << "Grammer is wrong, please check your source file: " << is_right << endl;
		exit(0);
	}
	//parser.check();
	vector<QuaternionNode>::iterator pList = qua.begin();
	for (pList;pList != qua.end();pList++) {
		cout << "(" << pList->op << ", " << pList->objective1.name << ", " << pList->objective2.name << ", " << pList->result.name << ")" << endl;
	}
	cout << endl;
	parser.synbl_print();
	cout << endl;
	//
	objective ob;
	ob.init(qua);
	ob.optimizequa(ob.divide());
	ob.Active_Information(ob.qua);
	ob.Objective_Code(ob.qua,ob.Act_inf);

}