
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable(){
    size = 0;
    root = nullptr;
}

void del(SymEntry* root){
    if(root){
        del(root->left);
        del(root->right);
        delete root;
    }
}

SymbolTable::~SymbolTable(){
    del(root);
}

void SymbolTable::insert(string k , UnlimitedRational* v){
    
    if(!root){
        root = new SymEntry(k,v);
        return;
    }
    
    SymEntry* c = root;
    SymEntry* p = nullptr;
    
    while(c!=nullptr){
        p = c;
        
        if(k < root->key){
            c = c->left;
        }
        else if (k > root->key){
            c = c->right;
        }
        else{
            c->val = v;
            return;
        }
    }
    if(k < p->key){ 
        p->left = new SymEntry(k,v);
        size++;
        return;
    }
    else{
        p->right = new SymEntry(k,v);
        size++;
        return;
    }
    
}

SymEntry* findmin(SymEntry* root){
    while(root->left !=nullptr){
        root = root->left;
    }
    return root;
}

void SymbolTable::remove(string k){
    if(root!=nullptr){
        return;
    }
    SymEntry* c = root;
    SymEntry* p = nullptr;
    while(c!=nullptr || c->key != k){
        p = c;
        if(k < root->key){
            c = c->left;
        }
        else {
            c = c->right;
        }
    }
    if(c==nullptr){
        return;
    }

    if(c->left==nullptr && c->right==nullptr){
        if(p==nullptr){
            root = nullptr;
        }
        else if(p->left == c){
            p->left = nullptr;
        }
        else{
            p->right = nullptr;
        }
        delete c;
    }
    else if(c->left!=nullptr && c->right!=nullptr){
        if(p==nullptr){
            root = c->left;
        }
        else if(p->left == c){
            p->left = c->left;
        }
        else{
            p->right = c->left;
        }
        delete c;
    }
    else if(c->left==nullptr && c->right!=nullptr){
        if(!p){
            root = c->right;
        }
        else if(p->left == c){
            p->left = c->right;
        }
        else{
            p->right = c->right;
        }
        delete c;
    }
    else{
        SymEntry* temp = findmin(c->right);
        SymEntry* temp2 = nullptr;;
        temp2->key = c->key;
        temp2->val = c->val;
        c->key = temp->key;
        c->val = temp->val;
        temp->key = temp2->key;
        temp->val = temp2->val;
        delete temp2;
        remove(temp->key);
    }
    size--;
}

UnlimitedRational* SymbolTable::search(string k){
    
    SymEntry* temp = root;
    while(temp!=nullptr){
        if(temp->key== k){
            return temp->val;
        }
        else if(temp->key < k && temp->right){
            temp = temp->right;
        }
        else{
            temp = temp->left;
        }
    }
    return root->val;
}

int SymbolTable::get_size(){
    return size;
}

SymEntry* SymbolTable::get_root(){
    return root;
}
