#include<bits/stdc++.h>
#include "1605047_Function.h"
using namespace std;





class SymbolInfo {
    FunctionDetails* functionDetails;
    string Name, Type, DeclareType;
    int indxOfBucket, posAtBucket;
    SymbolInfo* nextSymbolInfo;
    SymbolInfo* prevSymbolInfo;
    //for assembly code generation
    string asmCode, asmSymbol;

public:
    SymbolInfo( string name = "",  string type = "", string opt = "", int indxOfBucket = -1, int posAtBucket = -1) {
        nextSymbolInfo = prevSymbolInfo = nullptr;
        Name = name, Type = type, DeclareType = opt;
        this->indxOfBucket = indxOfBucket, this->posAtBucket = posAtBucket;
        functionDetails = new FunctionDetails();
        this->asmCode = this->asmSymbol = "";
    }

    FunctionDetails *getFunctionDetails() {
        return functionDetails;
    }

    void setFunctionDetails(FunctionDetails *functionDetails) {
        if (SymbolInfo::functionDetails) delete (SymbolInfo::functionDetails);
        SymbolInfo::functionDetails = nullptr;
        SymbolInfo::functionDetails = functionDetails;
    }

    void setDeclareType(string decType) {
        DeclareType = decType;
    }

    void _setDeclareType(char *str) { this->DeclareType = (string)str; }

    string getDeclareType() {
        return DeclareType;
    }

    string getName()  { return Name; }

    void setName(string name) { Name = name; }

    string getType()  { return Type; }

    void setType(string type) { Type = type; }

    int getPosAtBucket()  { return posAtBucket; }

    int getIndxOfBucket()  { return indxOfBucket; }

    SymbolInfo *getNextSymbolInfo()  { return nextSymbolInfo; }

    void setNextSymbolInfo(SymbolInfo *nextSymbolInfo) { SymbolInfo::nextSymbolInfo = nextSymbolInfo; }

    bool operator==( SymbolInfo rhs)  { return Name == rhs.Name; }

    SymbolInfo *getPrevSymbolInfo()  { return prevSymbolInfo; }

    void setPrevSymbolInfo(SymbolInfo *prevSymbolInfo) { SymbolInfo::prevSymbolInfo = prevSymbolInfo; }

    string getAsmCode() { return this->asmCode; }

    void setAsmCode(string code) { this->asmCode = code; }

    string getAsmSymbol() { return this->asmSymbol; }

    void setAsmSymbol(string symbol) { this->asmSymbol = symbol; }

    friend ostream &operator<<(ostream &os, const SymbolInfo &info) {
        os << "functionDetails: " << info.functionDetails << " Name: " << info.Name << " Type: " << info.Type
           << " DeclareType: " << info.DeclareType << " indxOfBucket: " << info.indxOfBucket << " posAtBucket: "
           << info.posAtBucket << " nextSymbolInfo: " << info.nextSymbolInfo << " prevSymbolInfo: "
           << info.prevSymbolInfo;
        return os;
    }

    virtual ~SymbolInfo() {
        if (nextSymbolInfo) delete (nextSymbolInfo);
        if (prevSymbolInfo) delete (prevSymbolInfo);
        if (functionDetails) delete (functionDetails);
        nextSymbolInfo = prevSymbolInfo = nullptr;
        functionDetails = nullptr;
        indxOfBucket = posAtBucket = 0;
        Name.clear(), Type.clear(), DeclareType.clear();
    }
};
