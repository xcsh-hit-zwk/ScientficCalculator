#ifndef MATRIXFUNCTION_H
#define MATRIXFUNCTION_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include <QHeaderView>

#define MAXROW 20
#define MAXCOLUMN 20

namespace Ui {
class MatrixFunction;
}

class MatrixFunction : public QDialog
{
    Q_OBJECT

public:
    explicit MatrixFunction(QWidget *parent = nullptr);
    ~MatrixFunction();

    typedef struct noname{
        double value[MAXROW][MAXCOLUMN];
        int row;
        int column;
    }QMatrix;

    QMatrix left;
    QMatrix right;
    QMatrix answer;


public slots:

    void timerUpdate(void);
    void makeTable();


private slots:

    void on_PlusButton_clicked();

    void on_SubstractButton_clicked();

    void on_MultiplyButton_clicked();

    void on_ClearButton_clicked();

    void on_EqualsButton_clicked();

private:
    Ui::MatrixFunction *ui;

    QLabel *Time;
    QLabel *LabelExpression;

    QTimer *timer;
    QTimer *readTimer;

    enum Function{EMPTY , PLUS , SUB , MUL};

    int Flag;

    void setWrongLabel(QString message);

    void getAdd();
    void getSub();
    void getMul();
};

#endif // MATRIXFUNCTION_H
