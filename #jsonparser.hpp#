#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP
#include <deque>
#include <map>
#include <memory>
#include <iostream>
#include <string>
using std::iostream;
using std::ostream;
using std::string;
using std::istream;
using std::deque;
using std::shared_ptr;
using std::map;

class Closure;
class Token;
class JSonScanner;
class JSonParser;
typedef deque<Token> Lexemes;

enum TokenName
{
    left_italic_bracket, literal_str, literal_int, left_square_bracket, right_italic_bracket, right_square_bracket, projection
};
ostream & operator<<(ostream & fout, const Closure & _token);
ostream & operator<<(ostream & fout, const Token & _token);
class Closure
{
    shared_ptr<long long> int_v;
    shared_ptr<string> str_v;
    shared_ptr<deque<Closure>> list_v;
    shared_ptr<map<string, Closure>> class_v;
public:
    class UseAsAClass {};
    class UseAsAList {};
    static UseAsAClass use_as_a_class()
    {
        return UseAsAClass();
    }
    static UseAsAList use_as_a_list()
    {
        return UseAsAList();
    }

    Closure() = default;
    Closure(const Closure & rhs) = default;
    Closure(Closure && rhs) = default;
    Closure & operator=(const Closure & rhs) = default;
    Closure(UseAsAClass a) : class_v(new map<string, Closure>) {}
    Closure(UseAsAList a) : list_v(new deque<Closure>) {}
    Closure(const string & rhs) : str_v(new string(rhs)) {}
    explicit Closure(const long long rhs) : int_v(new long long(rhs)) {}
    bool valid() const;
    long long & get_int() const;
    Closure & operator[](const string & key) const;
    Closure & operator[](size_t idx) const;
    deque<Closure> & get_list() const;
    void push_back(const Closure & ins);
    string & get_str() const;
    bool operator<(const Closure & rhs);
    friend ostream & operator<<(ostream & fout, const Closure & _token);
};
class Token
{
public:
    TokenName token_name;
    Closure attribute_value;
    Token(TokenName _token_name, const Closure & _attribute_value = Closure())
        : token_name(_token_name), attribute_value(_attribute_value) {}
    friend ostream & operator<<(ostream & fout, const Token & _token);
};
class JSonScanner
{
public:
    JSonScanner(Lexemes & opt, istream & fin);
};

class JSonParser
{
    Lexemes & context;
public:
    JSonParser(Lexemes & tg) : context(tg) {}
    Closure get_value(int & pos);
};

#endif // JSONPARSER_HPP
