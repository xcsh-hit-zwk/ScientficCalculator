#include "LegalExpression.h"

LegalExpression::LegalExpression()
{
    c_expression = NULL;
}

LegalExpression::LegalExpression(string expression)
{
    this->expression = expression;
    c_expression = this->expression.c_str();
    // 初始化栈
    stack.basePointer = (char*)malloc(sizeof(char) * INIT_STACK_SIZE);
    if (!stack.basePointer)
        exit(OVERFLOW);
    stack.topPointer = stack.basePointer;

    stack.stackSize = INIT_STACK_SIZE;
}

LegalExpression::~LegalExpression()
{
    stack.topPointer = NULL;
    delete[] stack.basePointer;
}

bool LegalExpression::isLegal()
{
    bool ReturnJudge = true;

    int Length = expression.length();

    // 0为无操作正在等待，1为有特殊操作等待
    int Flag = 0;

    for (int i = 0; i < Length; ++i)
    {
        switch (Flag)
        {
            case 0:
            {
                if (c_expression[i] == ')')
                {
                    Flag = 1;
                    continue;
                }
                else if (c_expression[i] == 'l')
                {
                    Flag = 2;
                }
                else if (c_expression[i] == 's')
                {
                    Flag = 2;
                }
                else if (c_expression[i] == 'c')
                {
                    Flag = 2;
                }
                else if (c_expression[i] == 't')
                {
                    Flag = 2;
                }
                Push(c_expression[i]);
                break;
            }
            case 1:
            {
                char out;
                Pop(out);
                while (out != '(')
                {
                    Pop(out);
                }
                // 括号连续并且没有符号作为间隔
                if (c_expression[i] == '(')
                {
                    ReturnJudge = false;
                    return ReturnJudge;
                }
                else if (c_expression[i] >= 'a' && c_expression[i] <= 'z')
                {
                    ReturnJudge = false;
                    return ReturnJudge;
                }
                Push(c_expression[i]);
                break;
            }
            case 2:
            {
                if (c_expression[i] == ')')
                {
                    Flag = 3;
                    continue;
                }
                Push(c_expression[i]);
                break;
            }
            case 3:
            {
                char out;
                Pop(out);
                while (out != '(')
                {
                    Pop(out);
                }
                if (c_expression[i] >= 'a' && c_expression[i] <= 'z')
                {
                    ReturnJudge = false;
                    return ReturnJudge;
                }
                else if (c_expression[i] == '(')
                {
                    ReturnJudge = false;
                    return ReturnJudge;
                }
                Push(c_expression[i]);
                Flag = 2;
                break;
            }
            default:
                break;
        }
    }

    return ReturnJudge;
}

void LegalExpression::Push(char in)
{
    *stack.topPointer++ = in;
}

void LegalExpression::Pop(char& out)
{
    out = *--stack.topPointer;
}
