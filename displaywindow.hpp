#ifndef DISPLAYWINDOW_HPP
#define DISPLAYWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class DisplayWindow;
}

class DisplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisplayWindow(QWidget *parent = 0);
    ~DisplayWindow();

private:
    Ui::DisplayWindow *ui;
};

#endif // DISPLAYWINDOW_HPP
