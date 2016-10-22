#include "displaywindow.hpp"
#include "jsonparser.hpp"
#include <QApplication>
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::endl;
using std::fstream;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    DisplayWindow w;
    w.show();
    Lexemes test;
    ifstream fin("W:\\acm\\TA Work\\Prog2016\\AI\\judger\\ACM-2015-AI-Server\\result.json");
    ofstream fout("W:\\acm\\TA Work\\Prog2016\\AI\\judger\\ACM-2015-AI-Server\\opt.txt");
    JSonScanner(test, fin);
    JSonParser json_parser(test);
    int pos = 0;
    auto json = json_parser.get_value(pos);
    fout << json["user"][0] << endl;
    fout << json["user"][1] << endl;
    fout.close();
    fin.close();
    return a.exec();
}
