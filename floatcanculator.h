#ifndef FLOATCANCULATOR_H
#define FLOATCANCULATOR_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <string>
#include "legalexpression.h"
#include "Function.h"
#include <QDebug>

using namespace std;

namespace Ui {
class FloatCanculator;
}

class FloatCanculator : public QDialog
{
    Q_OBJECT

public:
    explicit FloatCanculator(QWidget *parent = nullptr);
    ~FloatCanculator();
public slots:
    void timerUpdate(void);

private slots:
    void on_SinButton_clicked();

    void on_CosButton_clicked();

    void on_TanButton_clicked();

    void on_lnButton_clicked();

    void on_SevenButton_clicked();

    void on_FourButton_clicked();

    void on_OneButton_clicked();

    void on_EightButton_clicked();

    void on_FiveButton_clicked();

    void on_TwoButton_clicked();

    void on_ZeroButton_clicked();

    void on_NineButton_clicked();

    void on_SixButton_clicked();

    void on_ThreeButton_clicked();

    void on_DotButton_clicked();

    void on_DivisionButton_clicked();

    void on_MultiplyButton_clicked();

    void on_SubtractionButton_clicked();

    void on_PlusButton_clicked();

    void on_EqualButton_clicked();

    void on_ClearButton_clicked();

    void on_RightBracketButton_clicked();

    void on_LeftBrakerButton_clicked();

    void on_ExpButton_clicked();

    void on_DoubleZeroButton_clicked();

    void on_BackUpButton_clicked();

    void on_PowerButton_clicked();

    void on_SqrtButton_clicked();

    void on_LgButton_clicked();

    void on_FactorialButton_clicked();

signals:
    void FloatToMain();

private:
    Ui::FloatCanculator *ui;
    QLabel *Time;
    QLabel *LabelExpression;
    enum FunctionSituation{EMPTY = 0,POWER,SQRT,LG,FAC,SIN,COS,TAN,LN,EXP,NUM};
    int Flag;

    bool JudgeIllgalInput();
    void moveCursor();
};

#endif // FLOATCANCULATOR_H
