#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "evaluator.h"

#define NUM_FILES 5

void checkEvalTreeBasic(ExprTreeNode *root, std::vector<std::string> &evalOutput, int &lineCount, bool &error){
    // cout<<"eval1"<<endl;
    if(root == nullptr){
        error = true;
        std::cerr << "Eval tree isn't built correctly" << std::endl;
        return;
    }
    if(root->type == "VAR" || root->type == "VAL"){
        // cout<<"eval2"<<endl;
        return;
    }
    checkEvalTreeBasic(root->left, evalOutput, lineCount, error);
    checkEvalTreeBasic(root->right, evalOutput, lineCount, error);
    // cout<<root->evaluated_value->get_p_str()<<endl;
    // cout<<root->evaluated_value->get_frac_str()<<endl;
    // cout<<evalOutput[lineCount]<<endl;
    if(root->evaluated_value->get_frac_str() != evalOutput[lineCount]){
        error = true;
        // cout<<"eval3"<<endl;
        std::cerr << "Eval tree isn't built correctly" << std::endl;
        return;
    }
    lineCount++;
}

void checkParseTreeBasic(ExprTreeNode *root, std::vector<std::string> &tokenVector, bool &error, bool isMainRoot = false){
    // cout<<"0"<<endl;
    if(root == nullptr){
        error = true;
        std::cerr << "Parse tree isn't built correctly" << std::endl;
        return;
    }
    cout<<"1"<<endl;
    if(isMainRoot){
        if(root->left == nullptr || root->right == nullptr){
            error = true;
            // cout<<"2"<<endl;
            std::cerr << "Parse tree isn't built correctly at node :=" << std::endl;
            return;
        }
        // cout<<"3"<<endl;
        checkParseTreeBasic(root->left, tokenVector, error);
        // cout<<"4"<<endl;
        tokenVector.push_back(":=");

        const bool needsParentheses = (root->right->type != "VAR" && root->right->type != "VAL");
        // cout<<"5"<<endl;
        if (needsParentheses) {
            // cout<<"6"<<endl;
            tokenVector.push_back("(");
        }
        // cout<<"7"<<endl;
        checkParseTreeBasic(root->right, tokenVector, error);
        // cout<<"8"<<endl;
        if (needsParentheses) {
            // cout<<"9"<<endl;
            tokenVector.push_back(")");
        }

        return;
    }

    if(root->type == "VAR"){
        // cout<<"10"<<endl;
        tokenVector.push_back(root->id);
        return;
    }
    if(root->type == "VAL"){
        // cout<<"11"<<endl;
        cout<<root->val<<endl;
        tokenVector.push_back(root->val->get_p_str());
        // cout<<"12"<<endl;
        return;
    }
    if(root->left == nullptr || root->right == nullptr){
        error = 1;
        std::cerr << "Parse tree isn't built correctly" << std::endl;
        return;
    }

    const bool needParanthesesLeft = (root->left->type != "VAR" && root->left->type != "VAL");

    if(needParanthesesLeft) {
        tokenVector.push_back("(");
    }

    checkParseTreeBasic(root->left, tokenVector, error);

    if(needParanthesesLeft) {
        tokenVector.push_back(")");
    }

    if (root->type == "ADD") {
        tokenVector.push_back("+");
    } else if (root->type == "SUB") {
        tokenVector.push_back("-");
    } else if (root->type == "MUL") {
        cout<<"L"<<endl;
        tokenVector.push_back("*");
    } else if (root->type == "DIV") {
        tokenVector.push_back("/");
    } else {
        error = 1;
        std::cerr << "Invalid type detected in the parse Tree, neither of VAR, VAL, ADD, SUB, MUL, DIV FOUND "<<root->type << std::endl;
        return; 
    }
    const bool needParanthesesRight = (root->right->type != "VAR" && root->right->type != "VAL");

    if(needParanthesesRight) {
        tokenVector.push_back("(");
    }

    checkParseTreeBasic(root->right, tokenVector, error);

    if(needParanthesesRight) {
        tokenVector.push_back(")");
    }

}


int main() {
    for(int  fileNum = 1; fileNum <= NUM_FILES; fileNum++) {
        Evaluator evaluator;
        std::string filePath = "./test_cases/test_" + std::to_string(fileNum) + ".txt";

        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the file: " << filePath << std::endl;
            return 1;
        }

        
        std::string evalFilePath = "./test_cases/eval_output_" + std::to_string(fileNum) + ".txt";

        std::ifstream evalFile(evalFilePath);

        if (!evalFile.is_open()) {
            std::cerr << "Failed to open the file: " << evalFilePath << std::endl;
            return 1;
        }
        std::vector<std::string> evalOutput;
        std::string evalLine;
        while (std::getline(evalFile, evalLine)) {
            evalOutput.push_back(evalLine);
        }
        int evalCurr = 0;

        std::string line;
        std::regex tokenRegex("([a-zA-Z_][a-zA-Z0-9_]*|:=|\\(|\\)|\\+|\\-|\\*|\\/|\\d+)");
        int lineNum = 1;
        while (std::getline(inputFile, line)) {
            std::vector<std::string> tokens;
            auto words_begin = std::sregex_iterator(line.begin(), line.end(), tokenRegex);
            auto words_end = std::sregex_iterator();

            for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                tokens.push_back(i->str());
            }
            evaluator.parse(tokens);
            std::vector<std::string> tokenVector;
            bool parseError = false;
            checkParseTreeBasic(evaluator.expr_trees[evaluator.expr_trees.size() - 1], tokenVector, parseError, true);
            // cout<<"anna"<<endl;
            if(tokenVector != tokens || parseError){
                std::cerr << "Parse tree isn't built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
                return 1;
            }
            else{
                std::cout << "Parse tree built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
            }
            evaluator.eval();
            bool evalError = false;
            checkEvalTreeBasic(evaluator.expr_trees[evaluator.expr_trees.size() - 1]->right, evalOutput, evalCurr, evalError);
            if(evalError){
                std::cerr << "Eval tree isn't built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
                return 1;
            }
            else{
                std::cout << "Eval tree built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
            }
            lineNum++;
        }
        inputFile.close();

    }

    return 0;
}