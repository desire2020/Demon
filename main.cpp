#include "displaywindow.hpp"
#include "jsonparser.hpp"
#include <QApplication>
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::endl;
using std::fstream;
Closure targetjson;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    Lexemes test;
    DisplayWindow w;
    ifstream fin("W:\\acm\\TA Work\\Prog2016\\AI\\judger\\ACM-2015-AI-Server\\result.json");
    ofstream fout("W:\\acm\\TA Work\\Prog2016\\AI\\judger\\ACM-2015-AI-Server\\opt.txt");
    JSonScanner(test, fin);
    JSonParser json_parser(test);
    int pos = 0;
    targetjson = json_parser.get_value(pos);
    fout << targetjson;
    w.show();
    if (!fin.is_open())
        w.show_mess("Open JSon file failed.");

    fout.close();
    fin.close();
    return a.exec();
}
