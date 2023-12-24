#pragma once

// top�ļ� ���һЩȫ�ֶ�����Ϣ

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
#define LC_Rignt_Path "./lexical/lexical-result.txt"
#define PS_Wrong_Path "./parser/parser-wrong.txt"
#define PS_Rignt_Path "./parser/parser-result.txt"

#define PS_Production_Path "./parser/parser-production.txt"
#define PS_ItemGroup_Path "./parser/parser-itemgroup.txt"
#define PS_LR1table_Path "./parser/parser-LR1_table.txt"
#define PS_TREE_Path "./parser/parser-grammar_tree.txt"

#define SM_QUADRUPLE_Path "./parser/parser-4_ruple.txt"

// ������ע�ͱ�ʾ�����̵��ã���Ҫ�޸� common.h �� Grammar_rule[] ����Ӧ
#define CALL 1

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
#define ERROR_ARGU_NOT_FOUND -1
#define ERROR_ARGU_REPEAT -2
#define ERROR_FUNC_NOT_FOUND -3
#define ERROR_FUNC_REPEAT -4
#define ERROR_MAIN_NOT_FOUND -5
#define ERROR_FUNC_PARA_SIZE -6

//�ؼ���
static std::string KeyWords[KeyWord_NUM] = {
    "int","void","if","else","while","return"
};
//��ʶ��
static std::set<std::string> Identifier;
//��ֵ
static std::set<std::string> Digit;
//���
static std::string Delimiter[Delimiter_NUM] = {
    ";",
    "(",")",
    "{","}"
};
//���
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

//�ķ� - ���ս������
#define Grammar_symbol_NUM 31
#ifdef CALL
#define Grammar_rule_NUM 53
#else
#define Grammar_rule_NUM 48
#endif // CALL


#define TERMINAL 0
#define ARGUMENT 1

// ������Ҫ���ӣ���ԭ���ķ��������ղ���ʽ��
static std::string  Grammar_symbol_name[Grammar_symbol_NUM] = {
    // Grammar_symbol ��Ԫ��ID��num���ս������ - identifier��digit��
    "Program","����","ID","�β�","����",
    "�����б�","����","�ڲ�����","��䴮","�ڲ���������",
    "���","if���","while���","return���","��ֵ���",
    "����ʽ","�ӷ�����ʽ","relop","��","����",
    "num","FTYPE","call","ʵ��","ʵ���б�",
    "������","����","��������","��������","��������",
    "epsilon" // ʵ������
};

// �ķ� - ���ս���ķ���ӳ�䣨��������
//      - ������� Grammar_symbol_name ��Ӧ���������޸ģ�����һ�¼���
static std::string Grammar_symbol_def[Grammar_symbol_NUM] = {
    "program","type","identifier","formal_para","state_block",
    "para_list","para","inter_declaration","state_string","inter_argument_declaration",
    "state","if_state","while_state","return_state","assign_state",
    "expression","add_expression","relop","item","divisor",
    "number","ftype","call","actual_para","actual_para_list",
    "declaration_string","declaration","declaration type","func_declaration","argu_declaration",
    "epsilon"
};

// �ķ� - �﷨���򣨲������̵��ã�
//      - ÿһ�� vector<string> ����ĵ�һ��Ԫ���Ǳ�Ԫ�������Ķ��ǲ���ʽ
//      - ���� epsilon ����ʽ
static std::vector<std::string> Grammar_rule[Grammar_rule_NUM] = {
    #ifdef CALL
    {"Program","������"},
    {"������","����"},
    {"������","����","������"},
    {"����","int","ID","��������"},
    {"����","int","ID","��������"},
    {"����","void","ID","��������"},
    {"��������",";"},
    {"��������","(","�β�",")","����"},
    #else
    {"Program","����","ID","(","�β�",")","����"},
    {"����","int"},
    {"����","void"},// todo : more KeyWords
    #endif // CALL
    {"�β�","�����б�"},
    {"�β�","void"},
    {"�����б�","����"},
    {"�����б�","����",",","�����б�"},
    {"����","int","ID"},
    {"����","{","�ڲ�����","��䴮","}"},
    {"����","{","��䴮","}"},
    //{"�ڲ�����","epsilon"},
    {"�ڲ�����","�ڲ���������",";"},
    {"�ڲ�����","�ڲ���������",";","�ڲ�����"},
    {"�ڲ���������","int","ID"},
    {"��䴮","���"},
    {"��䴮","���","��䴮"},
    {"���","if���"},
    {"���","while���"},
    {"���","return���"},
    {"���","��ֵ���"},
    {"��ֵ���","ID","=","����ʽ",";"},
    {"return���","return",";"},
    {"return���","return","����ʽ",";"},
    {"while���","while","(","����ʽ",")","����"},
    {"if���","if","(","����ʽ",")","����"},
    {"if���","if","(","����ʽ",")","����","else","����"},
    {"����ʽ","�ӷ�����ʽ"},
    {"����ʽ","(","�ӷ�����ʽ",")"}, // ԭ��û��
    {"����ʽ","�ӷ�����ʽ","relop","����ʽ"},
    {"relop","<"},{"relop","<="},{"relop",">"},{"relop",">="},{"relop","=="},{"relop","!="}, //todo:more Operators
    {"�ӷ�����ʽ","��"},
    {"�ӷ�����ʽ","��","+","�ӷ�����ʽ"},
    {"�ӷ�����ʽ","��","-","�ӷ�����ʽ"},
    {"��","����"},
    {"��","����","*","��"},
    {"��","����","/","��"},
    {"����","num"},
    {"����","(","����ʽ",")"},
    {"����","ID","call"},
    {"����","ID"},
    //{"FTYPE","epsilon"},
    //{"FTYPE","call"},
    {"call","(","ʵ���б�",")"},
    {"call","(",")"},
    //{"ʵ��","epsilon"},
    //{"ʵ��","ʵ���б�"},
    {"ʵ���б�","����ʽ"},
    {"ʵ���б�","����ʽ",",","ʵ���б�"}
};