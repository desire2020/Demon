#ifndef DISPLAYWINDOW_HPP
#define DISPLAYWINDOW_HPP

#include <QMainWindow>
#include <string>
#include "jsonparser.hpp"
using std::string;

extern Closure targetjson;

namespace Ui {
    class DisplayWindow;
}

class DisplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisplayWindow(QWidget *parent = 0);
    ~DisplayWindow();
    void show_mess(const string & _post);

private:
    Ui::DisplayWindow *ui;
};

#endif // DISPLAYWINDOW_HPP
