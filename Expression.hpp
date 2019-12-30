#pragma once
#define _EXPRESSION_HPP_

#include <stdio.h>
#include <stdlib.h>

class Expression {

public:
    Expression() {
        leftChild = rightChild = NULL;
    }
    Expression(
        Expression* theLeftChild, Expression* theRightChild
    ) {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    } // 构造函数的重载

public:
    Expression* leftChild; Expression* rightChild;

};

class Operand : public Expression { // 操作数类 
    friend double getResult( Expression* ptr );
    friend void OutputInorder( Expression* out );

public:
    Operand( double value ) {
        leftChild = rightChild = NULL;
        this ->value = value;
    }

private:
    double value;

};

class Operator : public Expression { // 运算符类

    friend double getResult( Expression* ptr );
    friend void OutputInorder( Expression* out );

public:
    Operator(
        Expression* theLeftChild, Expression* theRightChild, char Type
    ) {
        leftChild = theLeftChild;
        rightChild = theRightChild;
        type = Type;
    } // 基类的指针实现多态

private:
    char type;
    
};

double getResult( Expression* ptr ) { // 对二叉树后序遍历
    double leftResult = 0, rightResult=0;
    
    if ( ptr ->leftChild )
        leftResult = getResult(ptr ->leftChild);
    else
        return ((Operand*)ptr) ->value;

    if ( ptr ->rightChild )
        rightResult = getResult(ptr ->rightChild);
    else
        return ((Operand*)ptr) ->value;

    switch (
        ((Operator*)ptr) ->type
    ) {
        case '+': return leftResult + rightResult;
        case '-': return leftResult - rightResult;
        case '*': return leftResult * rightResult;
        case '/': return leftResult / rightResult;
    }
    return 0;
}

void OutputInorder( Expression* out ) {
    if ( out ->leftChild )
        OutputInorder(out ->leftChild);
    else
        printf("%lf", ((Operand*)out) ->value);

    printf("%c", ((Operator*)out) ->type);

    if ( out ->rightChild )
        OutputInorder(out ->rightChild);
    else
        printf("%lf", ((Operand*)out) ->value);
}