#include "matrixfunction.h"
#include "ui_matrixfunction.h"

MatrixFunction::MatrixFunction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatrixFunction)
{
    ui->setupUi(this);

    Time = new QLabel(this);
    LabelExpression = new QLabel(this);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    readTimer = new QTimer(this);
    connect(readTimer , SIGNAL(timeout()) , this , SLOT(makeTable()));
    readTimer->start(1000);

    for(int i = 0 ; i < MAXROW ; ++i)
    {
        for(int j = 0 ; j < MAXCOLUMN ; ++j)
        {
            left.value[i][j] = 0;
            right.value[i][j] = 0;
            answer.value[i][j] = 0;
        }
    }
    left.row = right.row = answer.row =  0;
    left.column = right.column = answer.column = 0;

    Flag = EMPTY;
}

MatrixFunction::~MatrixFunction()
{
    delete ui;
}

void MatrixFunction::timerUpdate()
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

void MatrixFunction::makeTable()
{
    LabelExpression->clear();
    int Row , Column;
    bool judgeRow = true , judgeColumn = true;
    Row = ui->RowMatrix->text().toInt(&judgeRow);
    Column = ui->ColumnMatrix->text().toInt(&judgeColumn);

    if(judgeRow && judgeColumn)
    {
        ui->Display->verticalHeader()->hide();
        ui->Display->horizontalHeader()->hide();
        ui->Display->setRowCount(Row+1);
        ui->Display->setColumnCount(Column+1);
        for(int i = 0 ; i < Row ; i++)
        {
            ui->Display->setItem(i+1,0,new QTableWidgetItem(QString::number(i+1 , 10)));
        }
        for(int i = 0 ; i < Column ; ++i)
        {
            ui->Display->setItem(0,i+1,new QTableWidgetItem(QString::number(i+1 , 10)));
        }

        for(int i = 0 ; i <= Row ; ++i)
            ui->Display->setRowHeight(i,50);
        for(int i = 0 ; i <= Column ; ++i)
            ui->Display->setColumnWidth(i,50);
    }
    else if(ui->RowMatrix->text() == NULL && ui->ColumnMatrix->text() == NULL)
    {
    }
    else
    {
        ui->Display->clear();
        setWrongLabel("错误行列数目格式，请修改");
    }


}

void MatrixFunction::setWrongLabel(QString message)
{
    LabelExpression->setText(message);
    LabelExpression->setAlignment(Qt::AlignRight);
    LabelExpression->setGeometry(581 , 0 , 580 , 80);

    QFont font;
    font.setPixelSize(30);

    LabelExpression->setFont(font);
    LabelExpression->show();
}

void MatrixFunction::MatrixFunction::getAdd()
{
    for(int i = 0 ; i <= answer.row ; ++i)
    {
        for(int j = 0 ; j <= answer.column ; ++j)
        {
            answer.value[i][j] = left.value[i][j] + right.value[i][j];
        }
    }
}

void MatrixFunction::getSub()
{
    for(int i = 0 ; i <= answer.row ; ++i)
    {
        for(int j = 0 ; j <= answer.column ; ++j)
        {
            answer.value[i][j] = left.value[i][j] - right.value[i][j];
        }
    }
}

void MatrixFunction::getMul()
{
    int limit = left.column;
    for(int i = 0 ; i <= answer.row ; ++i)
    {
        for(int j = 0 ; j <= answer.column ; ++j)
        {
            double sum = 0;
            for ( int k = 0; k <= limit; k++ )
            {
                sum += left.value[i][k] * right.value[k][j];
            }
            answer.value[i][j] = sum;
        }
    }
}

void MatrixFunction::on_PlusButton_clicked()
{
    readTimer->stop();
    int row = ui->RowMatrix->text().toInt();
    int column = ui->ColumnMatrix->text().toInt();
    bool Judge = true;              //true说明填满了

    for(int i = 1 ; i <= row ; ++i)
    {
        for(int j = 1 ; j <= column ; ++j)
        {
            if(ui->Display->item(i,j) == NULL || ui->Display->item(i,j)->text() == "")
            {
                Judge = false;
                break;
            }
            else
                left.value[i-1][j-1] = ui->Display->item(i,j)->text().toDouble();
        }
        if(!Judge)
            break;
    }
    if(Judge)
    {
        left.row = row-1;
        left.column = column-1;

        ui->Display->clear();

        makeTable();
        ui->RowMatrix->clear();
        ui->ColumnMatrix->clear();

        Flag = PLUS;
    }
    else
    {
        setWrongLabel("矩阵未写满，请填满后点击操作符");
    }

}

void MatrixFunction::on_SubstractButton_clicked()
{
    readTimer->stop();
    int row = ui->RowMatrix->text().toInt();
    int column = ui->ColumnMatrix->text().toInt();
    bool Judge = true;

    for(int i = 1 ; i <= row ; ++i)
    {
        for(int j = 1 ; j <= column ; ++j)
        {
            if(ui->Display->item(i,j) == NULL || ui->Display->item(i,j)->text() == "")
            {
                Judge = false;
                break;
            }
            else
                left.value[i-1][j-1] = ui->Display->item(i,j)->text().toDouble();
        }
        if(!Judge)
            break;
    }
    if(Judge)
    {
        left.row = row-1;
        left.column = column-1;

        ui->Display->clear();

        makeTable();
        ui->RowMatrix->clear();
        ui->ColumnMatrix->clear();

        Flag = SUB;
    }
    else
    {
        setWrongLabel("矩阵未写满，请填满后点击操作符");
    }
}

void MatrixFunction::on_MultiplyButton_clicked()
{
    readTimer->stop();
    int row = ui->RowMatrix->text().toInt();
    int column = ui->ColumnMatrix->text().toInt();
    bool Judge = true;

    for(int i = 1 ; i <= row ; ++i)
    {
        for(int j = 1 ; j <= column ; ++j)
        {
            if(ui->Display->item(i,j) == NULL || ui->Display->item(i,j)->text() == "")
            {
                Judge = false;
                break;
            }
            else
                left.value[i-1][j-1] = ui->Display->item(i,j)->text().toDouble();
        }
        if(!Judge)
            break;
    }
    if(Judge)
    {
        left.row = row-1;
        left.column = column-1;

        ui->Display->clear();

        LabelExpression->clear();
        int Row , Column;
        Column = ui->RowMatrix->text().toInt();
        Row = ui->ColumnMatrix->text().toInt();
        ui->Display->verticalHeader()->hide();
        ui->Display->horizontalHeader()->hide();
        ui->Display->setRowCount(Row+1);
        ui->Display->setColumnCount(Column+1);
        for(int i = 0 ; i < Row ; i++)
        {
            ui->Display->setItem(i+1,0,new QTableWidgetItem(QString::number(i+1 , 10)));
        }
        for(int i = 0 ; i < Column ; ++i)
        {
            ui->Display->setItem(0,i+1,new QTableWidgetItem(QString::number(i+1 , 10)));
        }
        for(int i = 0 ; i <= Row ; ++i)
            ui->Display->setRowHeight(i,50);
        for(int i = 0 ; i <= Column ; ++i)
            ui->Display->setColumnWidth(i,50);
        Flag = MUL;
    }
    else
    {
        setWrongLabel("矩阵未写满，请填满后点击操作符");
    }
}

void MatrixFunction::on_ClearButton_clicked()
{
    ui->Display->clear();
    ui->RowMatrix->clear();
    ui->ColumnMatrix->clear();

    for(int i = 0 ; i < left.row ; ++i)
    {
        for(int j = 0 ; j < left.column ; ++j)
        {
            left.value[i][j] = 0;
        }
    }

    left.row = 0;
    left.column = 0;

    for(int i = 0 ; i < right.row ; ++i)
    {
        for(int j = 0 ; j < right.column ; ++j)
        {
            right.value[i][j] = 0;
        }
    }

    right.row = 0;
    right.column = 0;

    for(int i = 0 ; i < answer.row ; ++i)
    {
        for(int j = 0 ; j < answer.column ; ++j)
        {
            answer.value[i][j] = 0;
        }
    }

    answer.row = 0;
    answer.column = 0;

    readTimer->start();
}

void MatrixFunction::on_EqualsButton_clicked()
{
    int row = 0;
    int column = 0;
    bool Judge = true;

    switch (Flag)
    {
        case EMPTY:
        {

            break;
        }
        case PLUS:
        {
            row = left.row+1;
            column = left.column+1;


            for(int i = 1 ; i <= row ; ++i)
            {
                for(int j = 1 ; j <= column ; j++)
                {
                    if(ui->Display->item(i,j) == NULL || ui->Display->item(i,j)->text() == "")
                    {
                        Judge = false;
                        break;
                    }
                    right.value[i-1][j-1] = ui->Display->item(i,j)->text().toDouble();
                }
                if(!Judge)
                    break;
            }
            if(Judge)
            {
                right.row = left.row;
                right.column = right.row;
                //在这里执行加法操作，结构体看.h文件，在public里面,返回值赋值给answer
                answer.row = left.row;
                answer.column = left.column;
                getAdd();
            }
            else
            {
                setWrongLabel("矩阵未写满，请填满后点击操作符");
            }
            break;
        }
        case MUL:
        {
            row = left.column+1;
            column = left.row+1;


            for(int i = 1 ; i <= row ; ++i)
            {
                for(int j = 1 ; j <= column ; j++)
                {
                    if(ui->Display->item(i,j) == NULL || ui->Display->item(i,j)->text() == "")
                    {
                        Judge = false;
                        break;
                    }
                    right.value[i-1][j-1] = ui->Display->item(i,j)->text().toDouble();
                }
                if(!Judge)
                    break;
            }
            if(Judge)
            {
                right.row = row;
                right.column = column;
                //在这里执行乘法操作，结构体看.h文件，在public里面,返回值赋值给answer
                answer.row = left.row;
                answer.column = left.row;
                getMul();
            }
            else
            {
                setWrongLabel("矩阵未写满，请填满后点击操作符");
            }
            break;
        }
        case SUB:
        {
            row = left.row+1;
            column = left.column+1;


            for(int i = 1 ; i <= row ; ++i)
            {
                for(int j = 1 ; j <= column ; j++)
                {
                    if(ui->Display->item(i,j) == NULL || ui->Display->item(i,j)->text() == "")
                    {
                        Judge = false;
                        break;
                    }
                    right.value[i-1][j-1] = ui->Display->item(i,j)->text().toDouble();
                }
                if(!Judge)
                    break;
            }
            if(Judge)
            {
                right.row = row;
                right.column = column;
                //在这里执行减法操作，结构体看.h文件，在public里面,返回值赋值给answer
                answer.row = left.row;
                answer.column = left.column;
                getSub();
            }
            else
            {
                setWrongLabel("矩阵未写满，请填满后点击操作符");
            }
            break;
        }
        default:
            break;
     }

    ui->Display->clear();
    row = answer.row+1;
    column = answer.column+1;
    ui->Display->verticalHeader()->hide();
    ui->Display->horizontalHeader()->hide();
    ui->Display->setRowCount(row+1);
    ui->Display->setColumnCount(column+1);
    for(int i = 0 ; i < row ; i++)
    {
        ui->Display->setItem(i+1,0,new QTableWidgetItem(QString::number(i+1 , 10)));
    }
    for(int i = 0 ; i < column ; ++i)
    {
        ui->Display->setItem(0,i+1,new QTableWidgetItem(QString::number(i+1 , 10)));
    }
    for(int i = 0 ; i < row ; ++i)
        ui->Display->setRowHeight(i,50);
    for(int i = 0 ; i < column ; ++i)
        ui->Display->setColumnWidth(i,50);

    for(int i = 0 ; i <= answer.row ; ++i)
    {
        for(int j = 0 ; j <= answer.column ; ++j)
        {
            ui->Display->setItem(i+1,j+1,new QTableWidgetItem(QString::number(answer.value[i][j])));
        }
    }
    readTimer->start();
}

