#pragma once

// top文件 存放一些全局定义信息

#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <stack>

// Lexical
#define KeyWord_NUM 6
#define Delimiter_NUM 5
#define Operator_NUM 38
#define WRONG -1
#define RIGHT 1

#define LC_Wrong_Path "./lexical/lexical-wrong.txt"
#define LC_Right_Path "./lexical/lexical-result.txt"
#define PS_Wrong_Path "./parser/parser-wrong.txt"
#define PS_Right_Path "./parser/parser-result.txt"

#define PS_Production_Path "./parser/parser-production.txt"
#define PS_ItemGroup_Path "./parser/parser-itemgroup.txt"
#define PS_LR1table_Path "./parser/parser-LR1_table.txt"
#define PS_TREE_Path "./parser/parser-grammar_tree.txt"

#define SM_QUADRUPLE_Path "./parser/parser-4_ruple.txt"

// 打开下面注释表示含过程调用，需要修改 common.h 的 Grammar_rule[] 以适应
//#define CALL 1

#ifdef CALL
    #define Input_Path "./test/test-code-call.txt"
#else
    #define Input_Path "./test/test-code-nocall-1.txt"
#endif // CALL


#define ERROR_Pre -10
#define ERROR_KEYWORDS -20
#define ERROR_IDENTIFIER -30
#define ERROR_OPERATOR -40
#define ERROR_DELIMITER -50
#define ERROR_DIGIT -60
#define ERROR_NODFA -70

#define LEXICAL_RIGHT 10

#define ENTRANCE_KEYWORDS 0
#define ENTRANCE_IDENTIFIER 1
#define ENTRANCE_OPERATOR 2
#define ENTRANCE_DELIMITER 3
#define ENTRANCE_DIGIT 4

// Parser
#define ERROR_SHIFT -1
#define ERROR_REDUCE -2
#define ERROR_GOTO -3

#define PARSER_RIGHT 1
#define PARSER_GOING 0

// Semantic
#define SEMANTIC_RIGHT 0
#define ERROR_NOT_FOUND -1
#define ERROR_REPEAT -2

//关键字
static std::string KeyWords[KeyWord_NUM] = {
    "int","void","if","else","while","return"
};
//标识符
static std::set<std::string> Identifier;
//数值
static std::set<std::string> Digit;
//界符
static std::string Delimiter[Delimiter_NUM] = {
    ";",
    "(",")",
    "{","}"
};
//算符
static std::string Operator[Operator_NUM] = {
    "+","++","+=",
    "-","--","-=","->",
    ">",">>",">=",">>=",
    "<","<<","<=","<<=",
    "&","&&","&=",
    "|","||","|=",
    "*","*=","/","/=","%","%=","=","==","!","!=","^","^=",
    ",","?",":",".","~"
};

//文法 - 非终结符定义
#define Grammar_symbol_NUM 26
#define Grammar_rule_NUM 50

#define TERMINAL 0
#define ARGUMENT 1

// 根据需要添加（在原有文法中消除空产生式）
static std::string  Grammar_symbol_name[Grammar_symbol_NUM] = {
    // Grammar_symbol 变元（ID、num做终结符处理 - identifier、digit）
    "Program","类型","ID","形参","语句块",
    "参数列表","参数","内部声明","语句串","内部变量声明",
    "语句","if语句","while语句","return语句","赋值语句",
    "表达式","加法表达式","relop","项","因子",
    "num","FTYPE","call","实参","实参列表",
    "epsilon" // 实际消除
};

// 文法 - 非终结符的符号映射（仅换名）
//      - 和上面的 Grammar_symbol_name 对应，可随意修改，数量一致即可
static std::string Grammar_symbol_def[Grammar_symbol_NUM] = {
    "program","type","identifier","formal_para","state_block",
    "para_list","para","inter_declaration","state_string","inter_argument_declaration",
    "state","if_state","while_state","return_state","assign_state",
    "expression","add_expression","relop","item","divisor",
    "number","ftype","call","actual_para","actual_para_list",
    "epsilon"
};

// 文法 - 语法规则（不含过程调用）
//      - 每一个 vector<string> 对象的第一个元素是变元，后续的都是产生式
//      - 消除 epsilon 产生式
static std::vector<std::string> Grammar_rule[Grammar_rule_NUM] = {
    {"Program","类型","ID","(","形参",")","语句块"},
    {"类型","int"},
    {"类型","void"},// todo : more KeyWords
    {"形参","参数列表"},
    {"形参","void"},
    {"参数列表","参数"},
    {"参数列表","参数",",","参数列表"},
    {"参数","int","ID"},
    {"语句块","{","内部声明","语句串","}"},
    {"语句块","{","语句串","}"},
    //{"内部声明","epsilon"},
    {"内部声明","内部变量声明",";"},
    {"内部声明","内部变量声明",";","内部声明"},
    {"内部变量声明","int","ID"},
    {"语句串","语句"},
    {"语句串","语句","语句串"},
    {"语句","if语句"},
    {"语句","while语句"},
    {"语句","return语句"},
    {"语句","赋值语句"},
    {"赋值语句","ID","=","表达式",";"},
    {"return语句","return",";"},
    {"return语句","return","表达式",";"},
    {"while语句","while","(","表达式",")","语句块"},
    {"if语句","if","(","表达式",")","语句块"},
    {"if语句","if","(","表达式",")","语句块","else","语句块"},
    {"表达式","加法表达式"},
    {"表达式","(","加法表达式",")"}, // 原本没有
    {"表达式","加法表达式","relop","表达式"},
    {"relop","<"},{"relop","<="},{"relop",">"},{"relop",">="},{"relop","=="},{"relop","!="}, //todo:more Operators
    {"加法表达式","项"},
    {"加法表达式","项","+","加法表达式"},
    {"加法表达式","项","-","加法表达式"},
    {"项","因子"},
    {"项","因子","*","项"},
    {"项","因子","/","项"},
    {"因子","num"},
    {"因子","(","表达式",")"},
    {"因子","ID","FTYPE"},
    {"因子","ID"},
    //{"FTYPE","epsilon"},
    {"FTYPE","call"},
    {"call","(","实参",")"},
    {"call","(",")"},
    //{"实参","epsilon"},
    {"实参","实参列表"},
    {"实参列表","表达式"},
    {"实参列表","表达式",",","实参列表"}
};
