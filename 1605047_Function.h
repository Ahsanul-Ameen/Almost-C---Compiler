#include<bits/stdc++.h>
using namespace std;




struct FunctionDetails {
    FunctionDetails() {
        paramCount = scopeID = 0, isDefined = false, returnType = "", argList.clear(), argTypeList.clear(), funcVarList.clear();
    }

    unsigned int getParamCount() {
        return paramCount;
    }

    void setParamCount(unsigned int paramCount) {
        FunctionDetails::paramCount = paramCount;
    }

    unsigned getScopeID() { return this->scopeID; }

    void setScopeID(unsigned scopeID) { FunctionDetails::scopeID = scopeID; }

    bool isDefined1() {
        return isDefined;
    }

    void setIsDefined(bool isDefined = true) {
        FunctionDetails::isDefined = isDefined;
    }

    string getReturnType() {
        return this->returnType;
    }

    void setReturnType(string retType) {
      	returnType = retType;
    }

    const deque<string> getArgList() {
        return argList;
    }

    void setArgList(deque<string> argList) {
        FunctionDetails::argList = argList;
    }

    deque<string> getArgTypeList() {
        return argTypeList;
    }

    void setArgTypeList(deque<string> argTypeList) {
        FunctionDetails::argTypeList = argTypeList;
    }

    deque<string> getFuncVarList() {
        return funcVarList;
    }

    void setFuncVarList(deque<string> var_list) {
        FunctionDetails::funcVarList = var_list;
    }

    void addFuncVar(string variable) {
      funcVarList.push_back(variable);
    }

    void addParameter(string argName, string argType) {
        argList.push_back(argName), argTypeList.push_back(argType);
        setParamCount(getParamCount() + 1);
    }

    void clearFunction() {
      argList.clear();
      argTypeList.clear();
      paramCount = 0;
    }

    virtual ~FunctionDetails() {
        paramCount = scopeID = 0, isDefined = false, returnType.clear(), argList.clear(), argTypeList.clear(), funcVarList.clear();
    }

private:
    unsigned paramCount, scopeID;
    bool isDefined;
    string returnType;
    deque<string> argList, argTypeList, funcVarList;
};
