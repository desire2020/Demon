#include "displaywindow.hpp"
#include "ui_displaywindow.h"
#include <iostream>
#include <QThread>
#include <QPropertyAnimation>
#include <iomanip>
using namespace std;

QApplication * thisui;
int can_eat(int a, int b) {
    if(b == 0) return 1;
    a = abs(a), b = abs(b);
    if(a == 11 || b == 11 || a == b) return 0;
    if(b == 10) {
        if (a == 9) return 1;
        else return -1;
    }
    if (b == 12) return -1;
    if (a < b) {
        return 1;
    } else {
        return -1;
    }
}

void DisplayWindow::set_control() {
    if(step_now == step_total) {
        pause = true;
        continueB -> setEnabled(false);
    } else {
        continueB -> setEnabled(true);
        //continueB -> setEnabled(false);
    }
    if(pause) {
        continueB -> setText("Start");
        if(step_now + 1 <= step_total) {
            nextB -> setEnabled(true);
        } else {
            nextB -> setEnabled(false);
        }
        if(step_now - 1 >= 0) {
            lastB -> setEnabled(true);
        } else  {
            lastB -> setEnabled(false);
        }
    } else {
        continueB -> setText("Stop");
        nextB -> setEnabled(false);
        lastB -> setEnabled(false);
    }
}

void DisplayWindow::last_click() {
    --step_now;
    show_board();
}

void DisplayWindow::continue_click() {
    if(pause) {
        pause = false;
    } else {
        pause = true;
    }
    while(pause == false) {
        QThread :: msleep(time_interval);
        thisui -> processEvents();
        ++step_now;
        show_board();
    }
}

void DisplayWindow::next_click() {
    ++step_now;
    show_board();
}

void DisplayWindow::show_board() {
    set_control();
    char s[100];
    if(step_now == 0) {
        sprintf(s, "Total Step : %d", step_total);
    } else {
        bool flag = false;
        try { targetjson["step"][step_now - 1]["err"]; } catch(...) {flag = true; }
        if (flag) {
            sprintf(s, "[Step %d]AI %d Error: %s",
                    step_now,
                    (step_now - 1) % 2,
                    targetjson["step"][step_now - 1]["err"].get_str().c_str());
        } else {
            sprintf(s, "[Step %d]AI %d Moved: (%d, %d) to (%d, %d)",
                    step_now,
                    (step_now - 1) % 2,
                    targetjson["step"][step_now - 1]["posx"].get_int(),
                    targetjson["step"][step_now - 1]["posy"].get_int(),
                    targetjson["step"][step_now - 1]["tox"].get_int(),
                    targetjson["step"][step_now - 1]["toy"].get_int());
        }
    }

//    QPropertyAnimation animation(nextB, "geometry");

//    animation.setDuration(10000);

//    animation.setStartValue(QRect(0, 0, 0, 0));

//    animation.setEndValue(QRect(250, 250, 100, 30));

//    animation.start();

    text -> setText(s);
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            chess[i][j] -> setGeometry(QRect(37 + j * 45, i * 33 + 66, 45, 33));
            char s[100];
            if (boards[step_now][i][j] > 0) {
                sprintf(s, "background-image: url(:/image/blueChess.png);"
                           "margin-left: -%dpx;"
                           "margin-top:  -0px;", boards[step_now][i][j] * 50 - 50);
            } else if (boards[step_now][i][j] < 0) {
                sprintf(s, "background-image: url(:/image/redChess.png);"
                           "margin-left: -%dpx;"
                           "margin-top:  -0px;", -50 * boards[step_now][i][j] - 50);

            } else {
                sprintf(s, "");
            }
            chess[i][j] -> setStyleSheet(s);
        }
    }
}

DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);
    //ui->label0->setText(targetjson["user"][0].get_str().c_str());
    //ui->label1->setText(targetjson["user"][1].get_str().c_str());
    text = new QLineEdit(this);
    text -> setGeometry(QRect(0, 33, 300, 33));
    text -> setEnabled(false    );
    lastB = new QPushButton(this);
    lastB -> setGeometry(QRect(0, 0, 45, 33));
    lastB -> setText("Last");
    continueB = new QPushButton(this);
    continueB -> setGeometry(QRect(90, 0, 45, 33));
    continueB -> setText("Start");
    nextB = new QPushButton(this);
    nextB -> setGeometry(QRect(180, 0, 45, 33));
    nextB -> setText("Next");
    connect(lastB, SIGNAL(clicked()), this, SLOT(last_click()));
    connect(continueB, SIGNAL(clicked()), this, SLOT(continue_click()));
    connect(nextB, SIGNAL(clicked()), this, SLOT(next_click()));
    for(int i = 0; i < ROW; ++i) {
        for(int j = 0; j < COL; ++j) {
            chess[i][j] = new QWidget(this);
        }
    }
    int curBoard[17][5];
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (targetjson["init-board"][i][j]["color"].get_int() == 0) {
                curBoard[i][j] = targetjson["init-board"][i][j]["kind"].get_int() + 1;
            } else if (targetjson["init-board"][i][j]["color"].get_int() == 1) {
                curBoard[i][j] = -1 * targetjson["init-board"][i][j]["kind"].get_int() - 1;
            } else {
                curBoard[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < ROW; ++i) {
        for(int j = 0; j < COL; ++j) {
            boards[0][i][j] = curBoard[i][j];
        }
    }
    //show_board();
    step_total = targetjson["step"].get_list().size();
    for (int i = 1; i <= step_total; ++i) {
        //if (!('err' in Demo.data.step[i]))
        {
            int start_x = targetjson["step"][i - 1]["posx"].get_int();
            int start_y = targetjson["step"][i - 1]["posy"].get_int();
            int end_x = targetjson["step"][i - 1]["tox"].get_int();
            int end_y = targetjson["step"][i - 1]["toy"].get_int();
            if(start_x != end_x || start_y != end_y) {
                int flag = can_eat(curBoard[start_x][start_y], curBoard[end_x][end_y]);
                if(flag == 1) {
                    curBoard[end_x][end_y] = curBoard[start_x][start_y];
                    curBoard[start_x][start_y] = 0;
                }
                if(flag == 0) {
                    curBoard[end_x][end_y] = 0;
                    curBoard[start_x][start_y] = 0;
                }
                if(flag == -1) {
                    curBoard[start_x][start_y] = 0;
                }
            }
        }
        for(int k = 0; k < ROW; ++k) {
            for(int j = 0; j < COL; ++j) {
                boards[i][k][j] = curBoard[k][j];
            }
        }
    }
    step_now = 0;
    pause = true;
    time_interval = 200;
    show_board();
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::show_mess(const std::string & _post)
{
    //ui->message_box->setText(_post.c_str());
}
