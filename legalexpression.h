#ifndef LEGAL_EXPRESSION_H
#define LEGAL_EXPRESSION_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

#define INIT_STACK_SIZE 101

class LegalExpression
{

public:

    LegalExpression();
    LegalExpression(string expression);
    virtual ~LegalExpression();

    bool isLegal();		// 如果合法，返回true
    void Push(char in);
    void Pop(char& out);

    struct ExpressionStack
    {
        char* topPointer;
        char* basePointer;
        int stackSize;
    };

private:

    string expression;
    const char* c_expression = NULL;
    ExpressionStack stack;

};


#endif // !LEGAL_EXPRESSION_H


