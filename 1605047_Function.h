#include<bits/stdc++.h>
using namespace std;




struct FunctionDetails {
    FunctionDetails() {
        paramCount = 0, isDefined = false, returnType = "", argList.clear(), argTypeList.clear();
    }

    unsigned int getParamCount() const {
        return paramCount;
    }

    void setParamCount(unsigned int paramCount) {
        FunctionDetails::paramCount = paramCount;
    }

    bool isDefined1() const {
        return isDefined;
    }

    void setIsDefined(bool isDefined = true) {
        FunctionDetails::isDefined = isDefined;
    }

    const string getReturnType() const {
        return returnType;
    }

    void setReturnType(const string returnType) {
        FunctionDetails::returnType = returnType;
    }

    const deque<string> getArgList() const {
        return argList;
    }

    void setArgList(const deque<string> &argList) {
        FunctionDetails::argList = argList;
    }

    const deque<string> getArgTypeList() const {
        return argTypeList;
    }

    void setArgTypeList(const deque<string> argTypeList) {
        FunctionDetails::argTypeList = argTypeList;
    }

    void addParameter(const string argName, const string argType) {
        argList.push_back(argName), argTypeList.push_back(argType);
        setParamCount(getParamCount() + 1);
    }

    virtual ~FunctionDetails() {
        paramCount = 0, isDefined = false, returnType.clear(), argList.clear(), argTypeList.clear();
    }

private:
    unsigned paramCount;
    bool isDefined;
    string returnType;
    deque<string> argList, argTypeList;
};



