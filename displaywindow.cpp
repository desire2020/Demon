#include "displaywindow.hpp"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
    ui->label0->setText(targetjson["user"][0].get_str().c_str());
    ui->label1->setText(targetjson["user"][1].get_str().c_str());
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::show_mess(const std::string & _post)
{
    ui->message_box->setText(_post.c_str());
}
