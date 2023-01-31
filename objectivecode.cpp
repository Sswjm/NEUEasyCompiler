#include "objectivecode.h"

struct Node {                //DAG节点
	int left;
	int right;
	int id;
	string op;
	Objective m_sign;                    //主标记
	Objective sign[105];                  //附加标记
};

struct DAG {                  //DAG
	int num = 0;
	Node node[105];
}dag;

void objective::init(vector<QuaternionNode> quat)     //初始化四元式结构体数组
{
	qua = quat;
    /*Objective a1("x", "1");
    Objective b1("y", "1");
    Objective an1("t0", "2");
    QuaternionNode q1(0, 2, ">", a1, b1, an1);
    qua.push_back(q1);
    Objective a2("t0", "2");
    Objective b2("", "");
    Objective an2("", "");
    QuaternionNode q2(0, 3, "if", a2, b2, an2);
    qua.push_back(q2);
    Objective a3("x", "1");
    Objective b3("y", "1");
    Objective an3("t1", "2");
    QuaternionNode q3(0, 2, "+", a3, b3, an3);
    qua.push_back(q3);
    Objective a4("y", "1");
    Objective b4("x", "1");
    Objective an4("t2", "2");
    QuaternionNode q4(0, 2, "+", a4, b4, an4);
    qua.push_back(q4);
    Objective a5("t1", "2");
    Objective b5("t2", "2");
    Objective an5("t3", "2");
    QuaternionNode q5(0, 2, "*", a5, b5, an5);
    qua.push_back(q5);
    Objective a6("t3", "2");
    Objective b6("", "");
    Objective an6("x", "1");
    QuaternionNode q6(0, 0, "=", a6, b6, an6);
    qua.push_back(q6);
    Objective a7("", "");
    Objective b7("", "");
    Objective an7("", "");
    QuaternionNode q7(0, 3, "el", a7, b7, an7);
    qua.push_back(q7);
    Objective a8("x", "1");
    Objective b8("y", "1");
    Objective an8("t4", "2");
    QuaternionNode q8(0, 2, "+", a8, b8, an8);
    qua.push_back(q8);
    Objective a9("t4", "2");
    Objective b9("x", "1");
    Objective an9("t5", "2");
    QuaternionNode q9(0, 2, "*", a9, b9, an9);
    qua.push_back(q9);
    Objective a10("t5", "2");
    Objective b10("", "");
    Objective an10("y", "1");
    QuaternionNode q10(0, 0, "=", a10, b10, an10);
    qua.push_back(q10);
    Objective a11("", "");
    Objective b11("", "");
    Objective an11("", "");
    QuaternionNode q11(0, 3, "ie", a11, b11, an11);
    qua.push_back(q11);*/
}

void objective::addition(int n, string A, string typ)   //把标记A添加到节点n上，顺便删除无用标记
{
    int j, k;
    k = getnode(A);
    if (k != 0)      //如果getnode(A)不为空
    {
        for (j = 0; j < 105; j++)       //在节点getnode(A)上删除附标记
        {
            if (dag.node[k - 1].sign[j].name == A)
            {
                dag.node[k - 1].sign[j].name = "";
                dag.node[k - 1].sign[j].type = "";
            }
        }
    }
    if (dag.node[n - 1].m_sign.name != "")
    {
        for (j = 0; j < 105; j++)     //在节点n上添加附标记
        {
            if (dag.node[n - 1].sign[j].name == "")
            {
                dag.node[n - 1].sign[j].name = A;
                dag.node[n - 1].sign[j].type = typ;
                break;
            }
        }
    }
    else { dag.node[n - 1].m_sign.name = A; dag.node[n - 1].m_sign.type = typ; }

    if (dag.node[n - 1].m_sign.type == "2")    //若主标记为临时变量，附标记为非临时，则互换
    {
        for (j = 0; j < 105; j++)
        {
            if (dag.node[n - 1].sign[j].type == "1")
            {
                string a;
                a = dag.node[n - 1].sign[j].name;
                dag.node[n - 1].sign[j].name = dag.node[n - 1].m_sign.name;
                dag.node[n - 1].m_sign.name = a;
                dag.node[n - 1].sign[j].type = "2";
                dag.node[n - 1].m_sign.type = "1";
            }
        }
    }
}

int objective::getnode(string B)   //获取标记为B的节点的id
{
    int n = 0;      //节点id
    for (int i = 0; i < dag.num; i++)
    {
        if (dag.node[i].m_sign.name == B) n = i + 1;
        for (int j = 0; j < 105; j++)
        {
            if (dag.node[i].sign[j].name == B) n = i + 1;
        }
    }
    return n;
}

void objective::makeleaf(string B, string typ)   //构造叶子节点
{
    dag.num++;
    dag.node[dag.num - 1].m_sign.name = B;
    dag.node[dag.num - 1].m_sign.type = typ;
    dag.node[dag.num - 1].id = dag.num;
}

void objective::delnode(int n)     //删除id为n的节点
{
    dag.node[n - 1].m_sign.name = "";
    dag.node[n - 1].id = 0;
    for (int i = n - 1; i < dag.num - 1; i++)
    {
        dag.node[i].id = dag.node[i + 1].id;
        dag.node[i].left = dag.node[i + 1].left;
        dag.node[i].m_sign.name = dag.node[i + 1].m_sign.name;
        dag.node[i].m_sign.type = dag.node[i + 1].m_sign.type;
        dag.node[i].op = dag.node[i + 1].op;
        dag.node[i].right = dag.node[i + 1].right;
        for (int j = 0; j < 105; j++)
        {
            dag.node[i].sign[j].name = dag.node[i + 1].sign[j].name;
            dag.node[i].sign[j].type = dag.node[i + 1].sign[j].type;
        }
    }
    dag.node[dag.num - 1].id = 0;
    dag.node[dag.num - 1].left = 0;
    dag.node[dag.num - 1].m_sign.name = "";
    dag.node[dag.num - 1].m_sign.type = "";
    dag.node[dag.num - 1].op = "";
    dag.node[dag.num - 1].right = 0;
    for (int j = 0; j < 105; j++)
    {
        dag.node[dag.num - 1].sign[j].name = "";
        dag.node[dag.num - 1].sign[j].type = "";
    }
    dag.num--;
}

int objective::findnode(string opl, string B, string C)   //在DAG中查找有无符合A=B op C的节点
{
    int n = 0;
    int l, r, k = 0;
    l = getnode(B);
    r = getnode(C);
    for (int i = 0; i < dag.num; i++)
    {
        k = 0;
        if (dag.node[i].op == opl)  //op满足
        {
            l = dag.node[i].left;
            for (int j = 0; j < 105; j++)
            {
                if (dag.node[l - 1].sign[j].name == B) k = 1;
            }
            if ((dag.node[l - 1].m_sign.name == B) || k == 1)  //B满足
            {
                k = 0;
                r = dag.node[i].right;
                for (int j = 0; j < 105; j++)
                {
                    if (dag.node[r - 1].sign[j].name == C) k = 1;
                }
                if ((dag.node[r - 1].m_sign.name == C) || k == 1)  //C满足
                {
                    n = i + 1; break;
                }
            }
        }
    }
    return n;
}

int objective::makenode(string opl, string B, string C)  //构造中间节点
{
    dag.num++;
    dag.node[dag.num - 1].id = dag.num;
    dag.node[dag.num - 1].left = getnode(B);
    dag.node[dag.num - 1].right = getnode(C);
    dag.node[dag.num - 1].op = opl;
    return dag.num;
}

string objective::coutvalue(string opl, string B, string C)   //计算两个数运算的值
{
    char a;
    char s[105];
    float v;
    a = opl[0];
    switch (a)
    {
    case '+':
        v = atof(B.c_str()) + atof(C.c_str());
        break;
    case '-':
        v = atof(B.c_str()) - atof(C.c_str());
        break;
    case '*':
        v = atof(B.c_str()) * atof(C.c_str());
        break;
    case '/':
        v = atof(B.c_str()) / atof(C.c_str());
        break;
    }
    sprintf_s(s, "%f", v);
    string p(s);
    return p;
}

void objective::makequa(int block)   //生成block块中优化后的四元式
{
    int i, j, k = 0;
    int numB = 0, l, r;
    for (i = 0; i < dag.num; i++)
    {
        k = 0;
        if (dag.node[i].op == "")  //是叶子节点
        {
            for (j = 0; j < 105; j++)
            {
                if (dag.node[i].sign[j].type == "1") { k = 1; numB = j; }
            }
            if (dag.node[i].m_sign.type == "3" ||
                dag.node[i].m_sign.type == "1" && k == 1)  //主标记为数字，附标记有非临时变量
            {
                cout << block << " ( = " << dag.node[i].sign[numB].name << " _ " << dag.node[i].m_sign.name << " )" << endl; //( = B _ A)
                qua[0].result.name = dag.node[i].m_sign.name; qua[0].result.type = dag.node[i].m_sign.type;
                qua[0].block = block;
                qua[0].objective1.name = dag.node[i].sign[numB].name; qua[0].objective1.type = dag.node[i].sign[numB].type;
                qua[0].objective2.name = ""; qua[0].objective2.type = "";
                qua[0].op = "=";
                qua[0].type = 0;
                Block[block].push_back(qua[0]);
            }

        }
        else
        {
            l = dag.node[i].left;
            r = dag.node[i].right;
            cout << block << " ( " << dag.node[i].op << " " << dag.node[l - 1].m_sign.name << " " << dag.node[r - 1].m_sign.name << " " << dag.node[i].m_sign.name << " )" << endl;
            qua[0].result.name = dag.node[i].m_sign.name; qua[0].result.type = dag.node[i].m_sign.type;
            qua[0].block = block;
            qua[0].objective1.name = dag.node[l - 1].m_sign.name; qua[0].objective1.type = dag.node[l - 1].m_sign.type;
            qua[0].objective2.name = dag.node[r - 1].m_sign.name; qua[0].objective2.type = dag.node[r - 1].m_sign.type;
            qua[0].op = dag.node[i].op;
            qua[0].type = 2;

            Block[block].push_back(qua[0]);
        }
    }
}

void objective::deletedag()   //对dag清零
{
    int i, j;
    for (i = 0; i < dag.num; i++)
    {
        dag.node[i].id = 0;
        dag.node[i].left = 0;
        dag.node[i].m_sign.name = "";
        dag.node[i].m_sign.type = "";
        dag.node[i].op = "";
        dag.node[i].right = 0;
        for (j = 0; j < 105; j++)
        {
            dag.node[i].sign[j].name = "";
            dag.node[i].sign[j].type = "";
        }
    }
    dag.num = 0;
}

int objective::divide()      //划分基本块
{
    int i = 0;
    int num = 1;
    while (qua[i].op != "")        //当还有未处理的四元式，循环
    {
        if (qua[i].type != 3 || qua[i].op == "lb" || qua[i].op == "wh")
            qua[i].block = num;
        if (qua[i].op == "if" || qua[i].op == "el" || qua[i].op == "ie" || qua[i].op == "do" || qua[i].op == "we" || qua[i].op == "gt")
        {
            qua[i].block = num; num++;
        }
        i++;
        if (i >= qua.size())
            break;
    }
    if (qua[i - 1].op == "if" || qua[i - 1].op == "el" || qua[i - 1].op == "ie" || qua[i - 1].op == "do" || qua[i - 1].op == "we" || qua[i - 1].op == "gt")
        num--;
    return num;
}

void objective::optimizequa(int block_num)    //优化四元式
{
    int newleft, newright;        //新建节点id
    int i = 0, j, k;
    int n;
    string p;                   //若B,C为数字，p=B op C
    string A, B, C;               //（，B，C，A）
    //init();                      //初始化四元式结构体数组
    for (k = 1; k <= block_num; k++)   //块循环
    {
        if (qua[i].type == 3)
        {
            cout << qua[i].block << " ( " << qua[i].op << " " << qua[i].objective1.name << " " << qua[i].objective2.name << " " << qua[i].result.name << " )" << endl;
            Block[qua[i].block].push_back(qua[i]);
            i++;
            k = qua[i].block;
        }
        while (qua[i].op != "" && qua[i].block == k)        //当基本块还有未处理的四元式且是同一块时，循环
        {
            A = qua[i].result.name;
            B = qua[i].objective1.name;
            C = qua[i].objective2.name;
            newleft = 0;
            newright = 0;
            if (getnode(B) == 0 && qua[i].type != 3) { makeleaf(B, qua[i].objective1.type); newleft = getnode(B); }
            switch (qua[i].type)
            {
            case 0:   //单目
                n = getnode(B);
                addition(n, A, qua[i].result.type);
                break;
            case 2:   //双目
                if (getnode(C) == 0) { makeleaf(C, qua[i].objective2.type); newright = getnode(C); }
                j = 0;
                if ((qua[i].op == "*") || (qua[i].op == "/") || (qua[i].op == "+") || (qua[i].op == "-"))j = 1;
                if ((qua[i].objective1.type == "3") && (qua[i].objective2.type == "3") && j == 1)   //两个操作数都为数字
                {
                    p = coutvalue(qua[i].op, B, C);
                    if (newleft != 0) delnode(newleft);  //是新节点，则删除
                    if (newright != 0) delnode(newright);
                    if ((n = getnode(p)) == 0) { makeleaf(p, "3"); n = getnode(p); }
                }
                else
                {
                    if ((n = findnode(qua[i].op, B, C)) == 0)  //在DAG中查找有无符合A=B op C的节点
                        n = makenode(qua[i].op, B, C);
                }
                addition(n, A, qua[i].result.type);                  //添加附加标记
                break;
            case 3:
                break;
            }
            i++;
            if (i >= qua.size())
                break;
        }
        makequa(k);      //生成优化的四元式
        if (qua[i - 1].type == 3)
        {
            cout << qua[i - 1].block << " ( " << qua[i - 1].op << " " << qua[i - 1].objective1.name << " " << qua[i - 1].objective2.name << " " << qua[i - 1].result.name << " )" << endl;
            Block[qua[i - 1].block].push_back(qua[i - 1]);
        }
        deletedag();    //对dag清零
    }
}


int objective::to_int(string str)
{
    int res = 0;
    for (int j = 0; j < (int)str.size(); j++)
    {
        res = res * 10 + (str[j] - 48);
    }
    return res;
}

bool objective::is_inActsynbl(Objective token, vector<ACT_SYNBL>act_synbl)
{
    bool flag = 0;
    for (int i = 0; i < (int)act_synbl.size(); i++)
    {
        if (token.name == act_synbl[i].name) { flag = 1; break; }
    }
    return flag;
}

void objective::Active_Information(vector<QuaternionNode>qua)//填活跃信息
{
    //初始化Act_synbl表，临时变量N，非临时变量Y
    for (int i = 0; i < (int)qua.size(); i++)
    {
        vector<ACT_SYNBL>act_synbl;
        //objective1不为空且不是数字时
        if (qua[i].objective1.name != "" && qua[i].objective1.type != "3")
        {
            if (!is_inActsynbl(qua[i].objective1, act_synbl)) //不在表中
            {
                //非临时变量
                if (qua[i].objective1.type == "1")
                {
                    ACT_SYNBL tmp(qua[i].objective1.name, "Y");
                    act_synbl.push_back(tmp);
                }
                else if (qua[i].objective1.type == "2")//临时变量
                {
                    ACT_SYNBL tmp(qua[i].objective1.name, "N");
                    act_synbl.push_back(tmp);
                }
            }
        }

        //objective2不为空且不是数字时
        if (qua[i].objective2.name != "" && qua[i].objective2.type != "3")
        {
            if (!is_inActsynbl(qua[i].objective2, act_synbl)) //不在表中
            {
                //非临时变量
                if (qua[i].objective2.type == "1")
                {
                    ACT_SYNBL tmp(qua[i].objective2.name, "Y");
                    act_synbl.push_back(tmp);
                }
                else if (qua[i].objective2.type == "2")//临时变量
                {
                    ACT_SYNBL tmp(qua[i].objective2.name, "N");
                    act_synbl.push_back(tmp);
                }
            }
        }

        //result不为空且不是数字时
        if (qua[i].result.name != "" && qua[i].result.type != "3")
        {
            if (!is_inActsynbl(qua[i].result, act_synbl)) //不在表中
            {
                //非临时变量
                if (qua[i].result.type == "1")
                {
                    ACT_SYNBL tmp(qua[i].result.name, "Y");
                    act_synbl.push_back(tmp);
                }
                else if (qua[i].result.type == "2")//临时变量
                {
                    ACT_SYNBL tmp(qua[i].result.name, "N");
                    act_synbl.push_back(tmp);
                }
            }
        }
        Act_synbl.push_back(act_synbl);
    }

    //填四元式的活跃信息
    for (int i = 0; i < (int)qua.size(); i++)
    {
        vector<ACT_INF>act_inf;

        ACT_INF tmp;
        for (int k = 0; k < (int)Act_synbl[i].size(); k++)
        {
            if (qua[i].objective1.name == Act_synbl[i][k].name)
            {
                tmp.num1 = Act_synbl[i][k].act_inf;
                Act_synbl[i][k].act_inf = "Y";
            }

            if (qua[i].objective2.name == Act_synbl[i][k].name)
            {
                tmp.num2 = Act_synbl[i][k].act_inf;
                Act_synbl[i][k].act_inf = "Y";
            }

            if (qua[i].result.name == Act_synbl[i][k].name)
            {
                tmp.ans = Act_synbl[i][k].act_inf;
                Act_synbl[i][k].act_inf = "N";
            }
        }
        act_inf.push_back(tmp);
        reverse(act_inf.begin(), act_inf.end());
        Act_inf.insert(Act_inf.end(), act_inf.begin(), act_inf.end());
        //Act_inf.push_back(act_inf);
    }
}
//目标代码生成
void objective::Objective_Code(vector<QuaternionNode>qua, vector<ACT_INF>Act_inf)
{

    for (int i = 0; i < (int)qua.size(); i++)
    {
        int wh_id = 0;
        ACT_SYNBL Rdl("", ""); //初始化R寄存器描述表
            // 双操作数，两个操作数不可互换位置
        if (qua[i].op == "-" || qua[i].op == "/" || qua[i].op == "!=" ||
            qua[i].op == ">=" || qua[i].op == "<=" || qua[i].op == ">" ||
            qua[i].op == "<")
        {
            if (Rdl.name == "") //当前寄存器空闲
            {
                string tmp1 = "LD R," + qua[i].objective1.name;
                objcode.push_back(tmp1);
            }
            else //当前寄存器不空闲
            {
                if (Rdl.name != qua[i].objective1.name) //第一个操作数不在寄存器中
                {
                    string tmp1, tmp2;
                    if (Rdl.act_inf == "Y")
                    {
                        tmp1 = "ST R," + Rdl.name; objcode.push_back(tmp1);
                        tmp2 = "LD R," + qua[i].objective1.name;
                        objcode.push_back(tmp2);
                    }
                    else
                    {
                        string tmp1 = "LD R," + qua[i].objective1.name;
                        objcode.push_back(tmp1);
                    }
                }
            }

            string tmp2;
            //更新寄存器状态的活跃信息
            Rdl.act_inf = Act_inf[i].num1;

            if (qua[i].op == "-")tmp2 = "SUB R," + qua[i].objective2.name;
            else if (qua[i].op == "/")tmp2 = "DIV R," + qua[i].objective2.name;
            else if (qua[i].op == "!=")tmp2 = "NE R," + qua[i].objective2.name;
            else if (qua[i].op == ">=")tmp2 = "GE R," + qua[i].objective2.name;
            else if (qua[i].op == "<=")tmp2 = "LE R," + qua[i].objective2.name;
            else if (qua[i].op == ">")tmp2 = "GT R," + qua[i].objective2.name;
            else if (qua[i].op == "<")tmp2 = "LT R," + qua[i].objective2.name;

            objcode.push_back(tmp2);
            Rdl.name = qua[i].result.name; Rdl.act_inf = Act_inf[i].ans;//修改寄存器描述表
        }
        else if (qua[i].op == "+" || qua[i].op == "*") // +或*操作，两个操作数可以互换位置
        {
            //当前寄存器与该操作数无关
            if (Rdl.name != "" && Rdl.name != qua[i].objective1.name && Rdl.name != qua[i].objective2.name)
            {
                if (Rdl.act_inf == "Y")
                {
                    string tmp1 = "ST R," + Rdl.name; objcode.push_back(tmp1);
                }
            }
            else
            {
                string tmp1, tmp2;
                if (Rdl.name == qua[i].objective1.name)
                {
                    //更新寄存器状态的活跃信息
                    Rdl.act_inf = Act_inf[i].num1;

                    if (qua[i].op == "*") { tmp1 = "MUL R,"; }
                    else if (qua[i].op == "+") { tmp1 = "ADD R,"; }

                    objcode.push_back(tmp1 + qua[i].objective2.name);
                }
                else if (Rdl.name == qua[i].objective2.name)
                {
                    //更新寄存器状态的活跃信息
                    Rdl.act_inf = Act_inf[i].num1;

                    if (qua[i].op == "*") { tmp1 = "MUL R,"; }
                    else if (qua[i].op == "+") { tmp1 = "ADD R,"; }

                    objcode.push_back(tmp1 + qua[i].objective1.name);
                }
                else
                {
                    tmp1 = "LD R," + qua[i].objective1.name;
                    objcode.push_back(tmp1);
                    if (qua[i].op == "*") { tmp2 = "MUL R,"; }
                    else if (qua[i].op == "+") { tmp2 = "ADD R,"; }

                    objcode.push_back(tmp2 + qua[i].objective2.name);
                }
            }

            Rdl.name = qua[i].result.name; Rdl.act_inf = Act_inf[i].ans;//修改寄存器描述表
        }
        else if (qua[i].op == "if" || qua[i].op == "el" || qua[i].op == "ie")
        {
            //更新寄存器状态的活跃信息
            if (qua[i].op == "if")Rdl.act_inf = Act_inf[i].num1;
            if (Rdl.act_inf == "Y") { objcode.push_back("ST R," + Rdl.name); Rdl.act_inf = "N"; }

            string tmp;
            if (qua[i].op == "if") { tmp = "FJ R,"; objcode.push_back(tmp); }
            else if (qua[i].op == "el") { tmp = "JMP "; objcode.push_back(tmp); }
            //当前SEM栈不为空时，先退栈返填
            if (!SEM.empty())
            {
                string tmp = SEM.top();
                SEM.pop();

                objcode[to_int(tmp)] = objcode[to_int(tmp)] + to_string(objcode.size());
            }
            if (qua[i].op != "ie")SEM.push(to_string(objcode.size() - 1));

        }
        else if (qua[i].op == "wh" || qua[i].op == "do" || qua[i].op == "we")
        {
            //更新寄存器状态的活跃信息
            if (qua[i].op == "do")Rdl.act_inf = Act_inf[i].num1;
            if (Rdl.act_inf == "Y") { objcode.push_back("ST R," + Rdl.name); Rdl.act_inf = "N"; }

            string tmp;
            if (qua[i].op == "wh") { wh_id = (int)objcode.size(); }
            else if (qua[i].op == "do") { tmp = "FJ R,"; objcode.push_back(tmp); }
            else if (qua[i].op == "we") { tmp = "JMP " + to_string(wh_id); objcode.push_back(tmp); }
            //当前SEM栈不为空时，先退栈返填
            if (!SEM.empty())
            {
                string tmp = SEM.top();
                SEM.pop();

                objcode[to_int(tmp)] = objcode[to_int(tmp)] + to_string(objcode.size());
            }
            if (qua[i].op == "do")SEM.push(to_string(objcode.size() - 1));

        }
        else if (qua[i].op == "lb" || qua[i].op == "gt")
        {
            string tmp;
            if (qua[i].op == "lb") { tmp = qua[i].result.name + ":"; }
            else if (qua[i].op == "gt") { tmp = "JMP " + qua[i].result.name; }

            objcode.push_back(tmp);
        }
        else if (qua[i].op == "=")
        {
            string tmp1, tmp2;
            if (Rdl.name != qua[i].objective1.name)//寄存器中不是当前操作数
            {
                if (Rdl.act_inf == "Y") { tmp1 = "ST R," + Rdl.name; objcode.push_back(tmp1); }
                tmp2 = "LD R," + qua[i].objective1.name;
                objcode.push_back(tmp2);
            }

            Rdl.act_inf = Act_inf[i].num1; //更新寄存器活跃信息

            Rdl.name = qua[i].result.name; Rdl.act_inf = Act_inf[i].ans;
        }
        else //其他情况
        {

        }
        if (Rdl.act_inf == "Y") { objcode.push_back("ST R," + Rdl.name); }
    }

    //输出目标代码
    for (int i = 0; i < (int)objcode.size(); i++)
    {
        cout << left << setw(10) << i << left << setw(10) << objcode[i] << endl;
    }
}

