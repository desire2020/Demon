#include "displaywindow.hpp"
#include "jsonparser.hpp"
#include <QApplication>
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::fstream;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    DisplayWindow w;
    w.show();
    Lexemes test;
    ifstream fin("W:\\acm\\TA Work\\Prog2016\\AI\\judger\\ACM-2015-AI-Server\\result.json");
    JSonScanner(test, fin);
    ofstream fout("W:\\acm\\TA Work\\Prog2016\\AI\\judger\\ACM-2015-AI-Server\\opt.txt");
    for (auto i = test.begin(); i != test.end(); ++i)
    {
        fout << *i;
        fout << '\n';
    }
    fout.close();
    fin.close();
    return a.exec();
}
