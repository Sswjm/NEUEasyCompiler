# NEUEasyCompiler
A easy Pascal compiler with cpp

## 简介
本项目实现了一个简单的pascal语言编译前端模拟程序。本程序整体使用面向对象的方法完成，易于理解。其中语法分析部分使用易于理解的递归下降子程序法完成。

## 功能说明
输入简单的psacal源程序，运行main.cpp，可以在控制台输出该程序对应的变量信息、四元组、目标代码。 

## 文件说明
*datastructure.h* 定义数据结构  
*lexanalyse.h*    定义词法分析类  
*objectcode.h* 定义目标代码生成类  
*parser.h*  定义语法分析类  
*SYNBL.h* 定义符号表类
*lexanalyse.cpp* 词法分析器实现  
*main.cpp* 主程序  
*objectivecode.cpp* 目标代码生成实现 
*parser.cpp* 语法分析实现  
*symbl.cpp* 符号表实现  
*synbl.cpp*  符号表实现  
*grammer.txt* 文法说明  
*test1.txt*, *test2.txt* 测试文本  
