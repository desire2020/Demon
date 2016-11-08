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
    thisui = &a;
    Lexemes test;
    ifstream fin("result.json");
    ofstream fout("opt.txt");
    if (!fin.is_open())
        throw -1;
    JSonScanner(test, fin);
    JSonParser json_parser(test);
    int pos = 0;
    targetjson = json_parser.get_value(pos);
    fout << targetjson;
    DisplayWindow w;
    w.show();
    fout.close();
    fin.close();
    return a.exec();
}
