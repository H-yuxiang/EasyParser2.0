#include "tool.h"
#include "Lexical.h"
#include "Parser.h"

int main() {
    std::string file_path;
    std::cout << "请输入文件路径：\n";
    std::cin >> file_path;
    //std::string input = file_to_str(Input_Path);
    std::string input = file_to_str(file_path);
    
    // 1. Lexical analyse
    Lexical LC;
    std::pair<int, std::vector<token>> is_LC_right = LC.Analyze(input);
    if(is_LC_right.first > 0){
        std::cout << "词法分析成功\n";
    }
    else {
        std::cout << "词法分析失败\n";
        system("pause");
        return 0;
    }

    // 2. Parser analyse
    Parser PS;
    PS.load_argument_def();
    PS.load_production();
    //PS.show_production();
    PS.get_first();
    //PS.show_first();
    //PS.show_closure();
    PS.get_item_group();
    //PS.show_item_group();
    //PS.show_item_group_shift_mp();
    PS.get_LR1_table();
    //PS.show_LR1_table();
    int is_PS_right = PS.Analyse(is_LC_right.second);
    if (is_PS_right < 0) {
        system("pause");
        return 0;
    }

    // 3. Semantic analyse
    //PS.show_tree(PS.get_tree());
    int is_SM_right = PS.semanticAnalyse();
    if (is_SM_right < 0) {
        system("pause");
        return 0;
    }
    std::vector<std::pair<int, Quadruple>> semantic_result = PS.get_Q_ruple(); 
    
    // further operation..
    system("pause");
    return 0;
}
