#include <bits/stdc++.h>
#include "1605047_SymbolInfo.h"
using namespace std;


class ScopeTable {
    FILE *logOut;
    int id, size_of_symbolAra;
    SymbolInfo** symbolInfoAraPt;
    ScopeTable* parentScope;


    int getHashedIndx( string str) {
        long long base = 299, val = 0, p = str.length() - 1;
        for(int i = 0 ; i < str.length(); i++) {
            val += (str[i])*((long long)pow(base, p--)) % size_of_symbolAra;
        }
        return (int)(val%size_of_symbolAra);
    }

public:
    ScopeTable( int _id,  int n, FILE *fp) {
        logOut = fp;
        id = _id, size_of_symbolAra = n;
        symbolInfoAraPt = new SymbolInfo* [size_of_symbolAra];
        for(int i = 0; i < size_of_symbolAra; i++) symbolInfoAraPt[i] = nullptr;
        parentScope = nullptr;
    }

    int getId()  { return this->id; }

    int getSizeOfSymbolAra()  { return size_of_symbolAra; }

    ScopeTable *getParentScope()  { return parentScope; }

    void setParentScope(ScopeTable *parentScope) { ScopeTable::parentScope = parentScope; }

    bool insertSymbol( string name,  string type, string opt) {
        SymbolInfo* temp = nullptr;
        if(lookUpSymbol(name) == nullptr) {
            int indx = getHashedIndx(name), pos = 0;
            SymbolInfo* currentSymbol = symbolInfoAraPt[indx];
            temp = currentSymbol;
            if(currentSymbol == nullptr){
                symbolInfoAraPt[indx] = new SymbolInfo(name, type, opt, indx, pos);
                temp = symbolInfoAraPt[indx];
            } else if(currentSymbol->getNextSymbolInfo() == nullptr) {
                SymbolInfo* newSymbol = new SymbolInfo(name, type, opt, indx, ++pos);
                newSymbol->setPrevSymbolInfo(currentSymbol);
                currentSymbol->setNextSymbolInfo(newSymbol);
                temp = newSymbol;
            } else {
                while(currentSymbol->getNextSymbolInfo() != nullptr) {
                    currentSymbol = currentSymbol->getNextSymbolInfo();
                    pos++;
                }
                SymbolInfo* newSymbol = new SymbolInfo(name, type, opt, indx, pos);
                newSymbol->setPrevSymbolInfo(currentSymbol);
                currentSymbol->setNextSymbolInfo(newSymbol);
                temp = newSymbol;
            }

            //cout<<"Inserted in ScopeTable# "<<this->getId()<<" at position "<<temp->getIndxOfBucket()<<", "<<temp->getPosAtBucket()<<endl;
            //fprintf(logOut, "Inserted in ScopeTable# %d at position %d, %d\n", this->getId(), temp->getIndxOfBucket(), temp->getPosAtBucket());
            return true;
        }
        //cout<<printer(SymbolInfo(name, type, -1, -1))<<" already exists in current ScopeTable"<<endl;
        //fprintf(logOut, " < %s : %s > already exists in current ScopeTable\n", name.c_str(), type.c_str());
        return false;
    }

    SymbolInfo* lookUpSymbol( string symbolName) {
        for(int i = 0; i < size_of_symbolAra; i++) {
            SymbolInfo* currentSymbol = symbolInfoAraPt[i];
            while(currentSymbol != nullptr) {
                if(currentSymbol->getName() == symbolName) {
                    return currentSymbol;
                }
                currentSymbol = currentSymbol->getNextSymbolInfo();
            }
        }
        return nullptr;
    }

    bool deleteSymbol( string name) {
        int indx = getHashedIndx(name);
        SymbolInfo* currentSymbol = symbolInfoAraPt[indx], *prevSymbol = nullptr, *nextSymbol = nullptr;
        while(currentSymbol != nullptr) {
            if(currentSymbol->getName() == name){
                //cout<<"Found in ScopeTable# "<<this->getId()<<" at position "<<currentSymbol->getIndxOfBucket()<<", "<<currentSymbol->getPosAtBucket()<<endl;
                //fprintf(logOut, "Found in ScopeTable# %d at position %d, %d\n", this->getId(), currentSymbol->getIndxOfBucket(), currentSymbol->getPosAtBucket());
                //cout<<"Deleted entry at "<<currentSymbol->getIndxOfBucket()<<", "<<currentSymbol->getPosAtBucket()<<" from current ScopeTable"<<endl;
                //fprintf(logOut, "Deleted entry at %d, %d from current ScopeTable\n", currentSymbol->getIndxOfBucket(), currentSymbol->getPosAtBucket());
                prevSymbol = currentSymbol->getPrevSymbolInfo();
                nextSymbol = currentSymbol->getNextSymbolInfo();
                if(prevSymbol == nullptr) {
                    symbolInfoAraPt[indx] = currentSymbol->getNextSymbolInfo();
                    if(symbolInfoAraPt[indx]) symbolInfoAraPt[indx]->setPrevSymbolInfo(nullptr);
                }
                else if(nextSymbol == nullptr) {
                    prevSymbol->setNextSymbolInfo(nullptr);
                }
                else {
                    prevSymbol->setNextSymbolInfo(nextSymbol);
                    nextSymbol->setPrevSymbolInfo(prevSymbol);
                }
                delete currentSymbol;
                return true;
            }
            currentSymbol = currentSymbol->getNextSymbolInfo();
        }
        //cout<<"Not found"<<endl;
        //cout<<name<<" not found"<<endl;
        //fprintf(logOut, "Not found\n%s not found\n", name.c_str());
        return false;
    }


    void printScope() {
        //cout<<"\nScopeTable# "<<id<<endl;
        fprintf(logOut, "\nScopeTable # %d\n", id);
        for(int i = 0 ; i < size_of_symbolAra; i++){
            if(!symbolInfoAraPt[i])continue;
            //cout<<i<<" --> ";
            fprintf(logOut,"%d --> ",i);
            SymbolInfo* currentSymbol = symbolInfoAraPt[i];
            while(currentSymbol ) {
                string nm = currentSymbol->getName(), typ = currentSymbol->getType();
                //cout<<*currentSymbol;
                fprintf(logOut, " < %s , %s > ", nm.c_str(), typ.c_str());
                currentSymbol = currentSymbol->getNextSymbolInfo();
            }
            //cout<<endl;
            fprintf(logOut, "\n");
        }
        //cout<<endl;
        //fprintf(logOut, "\n");
    }

    virtual ~ScopeTable() {
        for(int i = 0 ; i < size_of_symbolAra; i++){
            SymbolInfo* currentSymbol = symbolInfoAraPt[i];
            SymbolInfo* temp = currentSymbol;
            while(temp){
                temp = temp->getNextSymbolInfo();
                delete currentSymbol;
                currentSymbol = temp;
            }
        }
        delete [] symbolInfoAraPt;
    }

};
