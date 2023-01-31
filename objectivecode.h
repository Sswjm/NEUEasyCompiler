#pragma once
#include "datastructure.h"

struct ACT_INF //��Ԫʽ�Ļ�Ծ��Ϣ
{
	string num1;
	string num2;
	string ans;
	ACT_INF(string a = "", string b = "", string c = "")
	{
		num1 = a; num2 = b; ans = c;
	}
};

struct ACT_SYNBL
{
	string name;
	string act_inf;
	ACT_SYNBL(string a = "", string b = "")
	{
		name = a; act_inf = b;
	}
};

class objective
{
public:
	vector<QuaternionNode> qua;
	vector<QuaternionNode> Block[15];

	set<string>Tmp_var; //��ʱ����
	set<string>var; //����ʱ����
	vector<ACT_INF>Act_inf;
	vector<string>objcode;
	stack<string>SEM; //����������ַ
	vector<vector<ACT_SYNBL>>Act_synbl;

    void example();
    void example2();
    int to_int(string str);
    bool is_inActsynbl(Objective token, vector<ACT_SYNBL>act_synbl);
    void Active_Information(vector<QuaternionNode>qua);
    void Objective_Code(vector<QuaternionNode>qua, vector<ACT_INF>Act_inf);
    void run();

    void init(vector<QuaternionNode> quat);     //��ʼ����Ԫʽ�ṹ������
    void addition(int n, string A, string typ);   //�ѱ��A��ӵ��ڵ�n�ϣ�˳��ɾ�����ñ��
    int getnode(string B);   //��ȡ���ΪB�Ľڵ��id
    void makeleaf(string B, string typ);   //����Ҷ�ӽڵ�
    void delnode(int n);     //ɾ��idΪn�Ľڵ�
    int findnode(string opl, string B, string C);   //��DAG�в������޷���A=B op C�Ľڵ�
    int makenode(string opl, string B, string C);  //�����м�ڵ�
    string coutvalue(string opl, string B, string C);   //���������������ֵ
    void makequa(int block);   //����block�����Ż������Ԫʽ
    void deletedag();  //��dag����
    void optimizequa(int block_num);    //�Ż���Ԫʽ
    int divide();             //���ֻ�����

};



