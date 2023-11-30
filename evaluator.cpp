/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator(){
    symtable = new SymbolTable();
}

Evaluator::~Evaluator(){
    delete symtable;
}

void Evaluator::parse(vector<string> code) {

    UnlimitedInt* temp = new UnlimitedInt("0");
    ExprTreeNode* Root = new ExprTreeNode(":=", temp);

    expr_trees.push_back(Root); 

    Root->left = new ExprTreeNode("VAR", temp);
    Root->right = new ExprTreeNode();
    Root->left->id = code[0];

    ExprTreeNode* pres = Root->right;
    
    vector<ExprTreeNode*> stk;
    
    long unsigned int i = 2;
    
    while(i < code.size()) {
        
        if(code[i] == "(") {
            stk.push_back(pres);
            pres->left = new ExprTreeNode();
            pres = pres->left;
        }

        else if (code[i] == "+") {
            
            pres->type = "ADD";
            stk.push_back(pres);
            pres->right = new ExprTreeNode();
            pres = pres->right;
        }

        else if (code[i] == "-") {
            pres->type = "SUB";
            stk.push_back(pres);
            pres->right = new ExprTreeNode();
            pres = pres->right;
        }

        else if (code[i] == "*") {
            pres->type = "MUL";
            stk.push_back(pres);
            pres->right = new ExprTreeNode();
            pres = pres->right;
        }

        else if (code[i] == "/") {
            pres->type = "DIV";
            stk.push_back(pres);
            pres->right = new ExprTreeNode();
            pres = pres->right;
        }

        else if (code[i] == ")") {
            if(!stk.empty()){
            pres = stk.back();
            stk.pop_back();
            }
        }

        else{
            if(isdigit(code[i][0]) || (code[i][0] == '-' && isdigit(code[i][1]))) {
                pres->type = "VAL";
                UnlimitedInt* x = new UnlimitedInt(code[i]);
                UnlimitedInt* y = new UnlimitedInt("1");
                pres->val = new UnlimitedRational(x, y);
                pres->evaluated_value = new UnlimitedRational(x, y);
                delete x;
                delete y;
            }
            
            else{
                pres->type = "VAR";
                pres->id = code[i];
                pres->evaluated_value = new UnlimitedRational();
                pres->val = symtable->search(code[i]);
                pres->evaluated_value = symtable->search(code[i]);
            }
            
            if(!stk.empty()){
                pres = stk.back();
                stk.pop_back();   
            }
        }  
    i++;
    }  
}

UnlimitedRational* evaluate(ExprTreeNode* Node) {
    if(Node == nullptr){
        return new UnlimitedRational();
    }
    if(Node->type == "VAL" || Node->type == "VAR") {
        return Node->evaluated_value;
    }
    
    if(Node->type == "ADD") {
        Node->evaluated_value = UnlimitedRational::add(evaluate(Node->left), evaluate(Node->right));
        return Node->evaluated_value;
    }
    else if (Node->type == "SUB") {
        Node->evaluated_value =  UnlimitedRational::sub(evaluate(Node->left), evaluate(Node->right));
        return Node->evaluated_value;
    }
    else if (Node->type == "MUL") {
        Node->evaluated_value =  UnlimitedRational::mul(evaluate(Node->left), evaluate(Node->right));
        return Node->evaluated_value;
    }
    else {
        Node->evaluated_value = UnlimitedRational::div(evaluate(Node->left), evaluate(Node->right));
        return Node->evaluated_value;
    }
    
}

void Evaluator::eval() {
    ExprTreeNode* root = expr_trees.back();
    root->evaluated_value = new UnlimitedRational(evaluate(root->right)->get_p(),evaluate(root->right)->get_q());
    root->left->evaluated_value = root->evaluated_value;
    
    if(root->type == ":="){
        symtable->insert(root->left->id, root->left->evaluated_value);
    }   
}
