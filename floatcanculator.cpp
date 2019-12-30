#include "floatcanculator.h"
#include "ui_floatcanculator.h"
#include "mainwindow.h"
#include "Beh.hpp"
#include "Expression.hpp"
#include "Stack.hpp"

FloatCanculator::FloatCanculator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FloatCanculator)
{
    ui->setupUi(this);
    Time = new QLabel(this);
    LabelExpression = new QLabel(this);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    Flag = EMPTY;
}

FloatCanculator::~FloatCanculator()
{
    delete ui;
}

void FloatCanculator::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    Time->setText(str);
    Time->setAlignment(Qt::AlignLeft);
    Time->setGeometry(0,0,580,80);
    QFont font;
    font.setItalic(true);
    font.setPixelSize(30);
    Time->setFont(font);
    Time->show();
}
void FloatCanculator::on_SinButton_clicked()
{
    if(Flag != EMPTY)
        return;
    LabelExpression->clear();
    ui->Display->insert("sin()");
    if(JudgeIllgalInput())
    {
        Flag = SIN;
        moveCursor();
        ui->Display->setFocusPolicy(Qt::NoFocus);
    }
}

void FloatCanculator::on_CosButton_clicked()
{
    if(Flag != EMPTY)
        return;
    LabelExpression->clear();
    ui->Display->insert("cos()");
    JudgeIllgalInput();
    if(JudgeIllgalInput())
    {
        Flag = COS;
        moveCursor();
        ui->Display->setFocusPolicy(Qt::NoFocus);
    }
}

void FloatCanculator::on_TanButton_clicked()
{
    if(Flag != EMPTY)
        return;
    LabelExpression->clear();
    ui->Display->insert("tan()");
    if(JudgeIllgalInput())
    {
        Flag = TAN;
        moveCursor();
        ui->Display->setFocusPolicy(Qt::NoFocus);
    }
}

void FloatCanculator::on_lnButton_clicked()
{
    if(Flag != EMPTY)
        return;
    LabelExpression->clear();
    ui->Display->insert("ln()");
    if(JudgeIllgalInput())
    {
        Flag = LN;
        moveCursor();
        ui->Display->setFocusPolicy(Qt::NoFocus);
    }
}

void FloatCanculator::on_SevenButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("7");
}

void FloatCanculator::on_FourButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("4");
}

void FloatCanculator::on_OneButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("1");
}

void FloatCanculator::on_EightButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("8");
}

void FloatCanculator::on_FiveButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("5");
}

void FloatCanculator::on_TwoButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("2");
}

void FloatCanculator::on_ZeroButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("0");
}

void FloatCanculator::on_NineButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("9");
}

void FloatCanculator::on_SixButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("6");
}

void FloatCanculator::on_ThreeButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("3");
}

void FloatCanculator::on_DotButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert(".");
}

void FloatCanculator::on_DivisionButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("/");
}

void FloatCanculator::on_MultiplyButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("*");
}

void FloatCanculator::on_SubtractionButton_clicked()
{

    LabelExpression->clear();
    ui->Display->insert("-");
}

void FloatCanculator::on_PlusButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("+");
}

void FloatCanculator::on_EqualButton_clicked()
{
    double Answer = 0;
    LabelExpression->clear();
    // 按下等号获取当前QLineEdit中的字符串，并转化为string类型
    QString QExpression = ui->Display->text();
    string expressions = QExpression.toStdString();
    // 判断表达式是否合法
    LegalExpression Judger(expressions);
    if(Judger.isLegal())
    {
        if(Flag != EMPTY)
        {
            // 在这里直接进入函数泰勒计算
            // enum FunctionSituation{EMPTY = 0,POWER,SQRT,LG,FAC,SIN,COS,TAN,LN,EXP};
            switch (Flag)
            {
                case POWER:
                {
                    int Length = QExpression.length();
                    int position = QExpression.indexOf("∧");

                    QString QbaseNumber = QExpression;
                    QbaseNumber.chop(Length - position);
                    double baseNumber = QbaseNumber.toDouble();

                    QString QpowNumber = QExpression.mid(position+2);
                    QpowNumber.chop(1);
                    double powNumber = QpowNumber.toDouble();

                    Answer = getPow(baseNumber , powNumber);
                    break;
                }
                case SQRT:
                {
                    QString Qnumber = QExpression.mid(2);
                    Qnumber.chop(1);
                    double number = Qnumber.toDouble();

                    Answer = getSqrt(number);
                    break;
                }
                case LG:
                {
                    QString Qnumber = QExpression.mid(3);
                    Qnumber.chop(1);
                    double number = Qnumber.toDouble();

                    Answer = getLg(number);
                    break;
                }
                case FAC:
                {
                    QString Qnumber = QExpression;
                    Qnumber.chop(1);
                    double number = Qnumber.toDouble();

                    Answer = getFac(number);
                    break;
                }
                case SIN:
                {
                    QString Qnumber = QExpression.mid(4);
                    Qnumber.chop(1);
                    double number = Qnumber.toDouble();

                    Answer = getSin(number);
                    break;
                }
                case COS:
                {
                    QString Qnumber = QExpression.mid(4);
                    Qnumber.chop(1);
                    double number = Qnumber.toDouble();

                    Answer = getCos(number);
                    break;
                }
                case TAN:
                {
                    QString Qnumber = QExpression.mid(4);
                    Qnumber.chop(1);
                    double number = Qnumber.toDouble();

                    Answer = getTan(number);
                    break;
                }
                case LN:
                {
                    QString Qnumber = QExpression.mid(3);
                    Qnumber.chop(1);
                    double number = Qnumber.toDouble();

                    Answer = getLn(number);
                    break;
                }
                case EXP:
                {
                    QString Qnumber = QExpression.mid(4);
                    Qnumber.chop(1);
                    double number = Qnumber.toDouble();

                    Answer = getExp(number);
                    break;
                }
                default:
                    break;
            }
        }
        else
        {
            //接口留在这里，串联后端构建表达式以及输出表达式Q
            expressions += "#";
            Expression *get = strToTree( expressions );
            ui->Display->clear();
            Answer = getResult( get );             // 用这个参数接返回的计算值
        }


        QString QAnswer = QString::number(Answer , 10 , 6);
        ui->Display->setText(QAnswer);

        LabelExpression->setText(QExpression);
        LabelExpression->setAlignment(Qt::AlignRight);
        LabelExpression->setGeometry(581 , 0 , 580 , 80);

        QFont font;
        font.setPixelSize(30);

        LabelExpression->setFont(font);
        LabelExpression->show();
    }
    else
    {
        LabelExpression->setText("错误计算格式，请修改");
        LabelExpression->setAlignment(Qt::AlignRight);
        LabelExpression->setGeometry(581 , 0 , 580 , 80);

        QFont font;
        font.setPixelSize(30);

        LabelExpression->setFont(font);
        LabelExpression->show();
    }

}

void FloatCanculator::on_ClearButton_clicked()
{
    LabelExpression->clear();
    ui->Display->clear();
    Flag = EMPTY;
    ui->Display->setEnabled(true);
}

void FloatCanculator::on_RightBracketButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("(");
    JudgeIllgalInput();
    Flag = NUM;
}


void FloatCanculator::on_LeftBrakerButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert(")");
    Flag = NUM;
}

bool FloatCanculator::JudgeIllgalInput()
{
    bool ReturnJudge = true;


    QString expression = ui->Display->text();
    string stdExpression = expression.toStdString();
    //接口
    //返回值
    LegalExpression Judger(stdExpression);
    ReturnJudge = Judger.isLegal();
    if(!ReturnJudge)
    {
        LabelExpression->setText("错误计算格式，请修改");
        LabelExpression->setAlignment(Qt::AlignRight);
        LabelExpression->setGeometry(581 , 0 , 580 , 80);

        QFont font;
        font.setPixelSize(30);

        LabelExpression->setFont(font);
        LabelExpression->show();
    }
    return ReturnJudge;
}

void FloatCanculator::moveCursor()
{
    QString text = ui->Display->text();
    int position = text.indexOf(")");

    if(position != -1)
        ui->Display->setCursorPosition(position);
}

void FloatCanculator::on_ExpButton_clicked()
{
    if(Flag != EMPTY)
        return;
    LabelExpression->clear();
    ui->Display->insert("exp()");
    if(JudgeIllgalInput())
    {
        Flag = EXP;
        moveCursor();
        ui->Display->setFocusPolicy(Qt::NoFocus);
    }
}


void FloatCanculator::on_DoubleZeroButton_clicked()
{
    LabelExpression->clear();
    ui->Display->insert("00");
    JudgeIllgalInput();
    Flag = NUM;
}

void FloatCanculator::on_BackUpButton_clicked()
{
    QString text;
    text = ui->Display->text();

    int Length = text.length();
    text = text.mid(0,Length-1);
    ui->Display->setText(text);
    LabelExpression->clear();
    if(Flag != NUM)
        Flag = EMPTY;
    ui->Display->setEnabled(true);
}

void FloatCanculator::on_PowerButton_clicked()
{
    if(Flag != EMPTY)
        return;
    LabelExpression->clear();
    ui->Display->insert("∧()");

    QString text;
    text = ui->Display->text();

    QString preString = text;
    preString.chop(3);

    bool isNumber = true;
    double tempTest = preString.toDouble(&isNumber);

    if(!isNumber)
    {
        LabelExpression->setText("错误计算格式，请修改");
        LabelExpression->setAlignment(Qt::AlignRight);
        LabelExpression->setGeometry(581 , 0 , 580 , 80);

        QFont font;
        font.setPixelSize(30);

        LabelExpression->setFont(font);
        LabelExpression->show();
    }
    else
    {
        Flag = POWER;
        moveCursor();
        ui->Display->setFocusPolicy(Qt::NoFocus);
    }
}

void FloatCanculator::on_SqrtButton_clicked()
{
    if(Flag != EMPTY)
        return;
    LabelExpression->clear();
    ui->Display->insert("√()");

    QString text = ui->Display->text();

    if(text.at(0) != "√")
    {
        LabelExpression->setText("错误计算格式，请修改");
        LabelExpression->setAlignment(Qt::AlignRight);
        LabelExpression->setGeometry(581 , 0 , 580 , 80);

        QFont font;
        font.setPixelSize(30);

        LabelExpression->setFont(font);
        LabelExpression->show();
    }
    else
    {
        Flag = SQRT;
        moveCursor();
        ui->Display->setFocusPolicy(Qt::NoFocus);
    }
}

void FloatCanculator::on_LgButton_clicked()
{
    if(Flag != EMPTY)
        return;
    LabelExpression->clear();
    ui->Display->insert("lg()");

    QString text = ui->Display->text();

    if(text.at(1) != "g")
    {
        LabelExpression->setText("错误计算格式，请修改");
        LabelExpression->setAlignment(Qt::AlignRight);
        LabelExpression->setGeometry(581 , 0 , 580 , 80);

        QFont font;
        font.setPixelSize(30);

        LabelExpression->setFont(font);
        LabelExpression->show();
    }
    else
    {
        Flag = LG;
        moveCursor();
        ui->Display->setFocusPolicy(Qt::NoFocus);
    }
}

void FloatCanculator::on_FactorialButton_clicked()
{
    if(Flag != EMPTY)
        return;
    LabelExpression->clear();
    ui->Display->insert("!");

    QString text = ui->Display->text();

    QString preString = text;
    preString.chop(1);
    bool isNumber = true;

    double temp = preString.toDouble(&isNumber);

    if(!isNumber)
    {
        LabelExpression->setText("错误计算格式，请修改");
        LabelExpression->setAlignment(Qt::AlignRight);
        LabelExpression->setGeometry(581 , 0 , 580 , 80);

        QFont font;
        font.setPixelSize(30);

        LabelExpression->setFont(font);
        LabelExpression->show();
    }
    else
    {
        Flag = FAC;
        moveCursor();
        ui->Display->setFocusPolicy(Qt::NoFocus);
    }
}
