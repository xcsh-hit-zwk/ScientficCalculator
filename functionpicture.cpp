#include "functionpicture.h"
#include "ui_functionpicture.h"

FunctionPicture::FunctionPicture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunctionPicture)
{
    ui->setupUi(this);
}

FunctionPicture::~FunctionPicture()
{
    delete ui;
}
