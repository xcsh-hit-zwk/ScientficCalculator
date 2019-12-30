#pragma once
#define _BEH_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Stack.hpp"
#include "Expression.hpp"

double strToDouble( std::string str, int n ) {
    double ret = 0.0; int dotMarker = 0;
    for ( int i = 0; i < n; i++ ) {
        if ( '.' == str[i] ) dotMarker = i;
        else {
            ret = ret * 10 + str[i] - '0';
        }
    }
    if ( 0 != dotMarker ) {
        for ( int i = 1; i < n - dotMarker; i++ ) {
            ret /= 10;
        }
    }
    return ret;
} // 字符串转数值，支持小数

char Prior[8][8] = { // 运算符优先级表 
	//      '+'  '-'  '*'  '/'  '('  ')'  '#'  '^'
	/*'+'*/ '>', '>', '<', '<', '<', '>', '>', '<', 
	/*'-'*/ '>', '>', '<', '<', '<', '>', '>', '<', 
	/*'*'*/ '>', '>', '>', '>', '<', '>', '>', '<', 
	/*'/'*/ '>', '>', '>', '>', '<', '>', '>', '<', 
	/*'('*/ '<', '<', '<', '<', '<', '=', ' ', '<', 
	/*')'*/ '>', '>', '>', '>', ' ', '>', '>', '>', 
	/*'#'*/ '<', '<', '<', '<', '<', ' ', '=', '<', 
	/*'^'*/ '>', '>', '>', '>', '<', '>', '>', '>' 
};

char getPrior( char prev, char curr ) {
    int i; int j; // 前一个操作已在栈中 // 当前运算符
    switch (prev) {
        case '+': i = 0; break;
        case '-': i = 1; break;
        case '*': i = 2; break;
        case '/': i = 3; break;
        case '(': i = 4; break;
        case ')': i = 5; break;
        case '#': i = 6; break;
        case '^': i = 7; break;
        default: break;
    }
    switch (curr) {
        case '+': j = 0; break;
        case '-': j = 1; break;
        case '*': j = 2; break;
        case '/': j = 3; break;
        case '(': j = 4; break;
        case ')': j = 5; break;
        case '#': j = 6; break;
        case '^': j = 7; break;
        default: break;
    }
    return Prior[i][j];
}

Expression* strToTree( std::string& str ) {
    Stack<char> optrStack; // 运算符栈
    Stack<Expression*> opndStack; // 运算数栈

    PushIntoStack( &optrStack, '#' ); // 先将#入栈，优先级最低，结尾必有#

    int i = 0;
    while ( i < str.length() ) {
        if ( str[i] >= '0' && str[i] <= '9' ) {
            std::string temp;
            while ( true ) {
                if ( !(str[i] >= '0' && str[i] <= '9') && str[i] != '.' ) {
                    break;
                }
                temp.push_back(str[i]);
                i++;
            }
            Expression* ptr = new Operand( strToDouble( temp, temp.length() ) );
            PushIntoStack( &opndStack, ptr );
        } // 为数字，建立叶子节点并暂存
        else {

            // 总原则
            // 高优先级的二叉树先建立：后入栈，先出栈
            // 低优先级的二叉树后建立：先入栈，后出栈
            // 栈顶元素 ： 当前元素

            switch (
                getPrior( DisplayTopItem( &optrStack ), str[i] )
            ) {
                case '<': {
                    PushIntoStack( &optrStack, str[i] );
                    i++;
                    break;
                }
                case '=': {
                    char temp;
                    PopFromStack( &optrStack, &temp );
                    i++;
                    break;
                } // 脱括号或者#
                case '>': {
                    char temp;
                    PopFromStack( &optrStack, &temp );
                    Expression* rptr; PopFromStack( &opndStack, &rptr );
                    Expression* lptr; PopFromStack( &opndStack, &lptr );
                    Expression* ptr = new Operator( lptr, rptr, temp );
                    PushIntoStack( &opndStack, ptr );
                    break;
                }
                default: break;
            }
        }
    }
    Expression* ptr;
    PopFromStack( &opndStack, &ptr );
    return ptr;
}
