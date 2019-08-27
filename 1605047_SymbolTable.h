#include <bits/stdc++.h>
#include "1605047_ScopeTable.h"
using namespace std;




class SymbolTable {
    FILE *logOut;
    ScopeTable* currentScope;
    int tableCnt, bucketCnt;
public:
    SymbolTable(int bucketCnt, FILE *fp) {
        logOut = fp;
        currentScope = nullptr, tableCnt = 0, SymbolTable::bucketCnt = bucketCnt;
        ScopeTable* newScope = new ScopeTable(++tableCnt, bucketCnt, logOut);
        newScope->setParentScope(currentScope);
        currentScope = newScope;
    }
    void enterScope() {
        ScopeTable* newScope = new ScopeTable(++tableCnt, bucketCnt, logOut);
        newScope->setParentScope(currentScope);
        currentScope = newScope;
        //cout<<"New ScopeTable with id "<<tableCnt<<" created"<<endl;
        fprintf(logOut, "\nNew ScopeTable with id %d created\n", tableCnt);
    }
    void exitScope() {
        ///tableCnt--; // it depends on the id of newScopes
        //cout<<"ScopeTable with id "<<currentScope->getId()<<" removed"<<endl;
        fprintf(logOut, "\nScopeTable with id %d removed\n", currentScope->getId());
        ScopeTable* prevScope = currentScope->getParentScope();
        delete currentScope;
        currentScope = prevScope;
    }
    bool insert(string name, string type, string opt = "") { return currentScope->insertSymbol(name, type, opt); }
    bool remove( string& name) { return currentScope->deleteSymbol(name); }
    SymbolInfo* lookUpCurrentScope(string name) {
        SymbolInfo* itr = currentScope->lookUpSymbol(name);
        if(itr) {
            //cout<<"Found in ScopeTable# "<<temp->getId()<<" at position "<<itr->getIndxOfBucket()<<", "<<itr->getPosAtBucket()<<endl;
            //fprintf(logOut, "Found in ScopeTable# %d at position %d, %d\n", currentScope->getId(), itr->getIndxOfBucket(), itr->getPosAtBucket());
            return itr;
        }
        //cout<<"Not Found"<<endl;
        //fprintf(logOut, "Not Found\n");
        return nullptr;
    }
    SymbolInfo* lookUp(string name) {
        ScopeTable* temp = currentScope;
        while(temp) {
            SymbolInfo* itr = temp->lookUpSymbol(name);
            if(itr) {
                //cout<<"Found in ScopeTable# "<<temp->getId()<<" at position "<<itr->getIndxOfBucket()<<", "<<itr->getPosAtBucket()<<endl;
                //fprintf(logOut, "Found in ScopeTable# %d at position %d, %d\n", temp->getId(), itr->getIndxOfBucket(), itr->getPosAtBucket());
                return itr;
            }
            temp = temp->getParentScope();
        }
        //cout<<"Not Found"<<endl;
        //fprintf(logOut, "Not Found\n");
        return nullptr;
    }
    void printCurrentScope() { currentScope->printScope(); }

    void printAllScopeTable() {
        ScopeTable* temp = currentScope;
        while(temp) {
            temp->printScope();
            temp = temp->getParentScope();
        }
    }

    virtual ~SymbolTable() {
        while(currentScope){
            ScopeTable* temp = currentScope;
            currentScope = currentScope->getParentScope();
            delete temp;
        }
    }

};


/*
int main() {
    return 0;
}*/

