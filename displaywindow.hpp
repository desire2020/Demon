#ifndef DISPLAYWINDOW_HPP
#define DISPLAYWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <string>
#include "jsonparser.hpp"
#include <QApplication>
using std::string;

extern Closure targetjson;

extern QApplication * thisui;
namespace Ui {
    class DisplayWindow;
}

class DisplayWindow : public QMainWindow
{
    Q_OBJECT
    const int ROW = 17;
    const int COL = 5;
    QWidget* chess[17][5];
    QPushButton *lastB, *continueB, *nextB;
    QLineEdit *text;
    int boards[1000][17][5];
    int step_now;
    int step_total;
    int time_interval;
    bool pause;
public:
    explicit DisplayWindow(QWidget *parent = 0);
    ~DisplayWindow();
    void show_mess(const string & _post);
    void show_board();
    void set_control();
private slots:
    void last_click();
    void continue_click();
    void next_click();
private:
    Ui::DisplayWindow *ui;
};

#endif // DISPLAYWINDOW_HPP
