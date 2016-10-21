#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP
#include <deque>
#include <map>
#include <memory>
#include <iostream>
#include <string>
using std::ostream;
using std::string;
using std::istream;
using std::deque;
using std::shared_ptr;


class Closure;
class Token;
class JSonScanner;
class JSonParser;
typedef deque<Token> Lexemes;

enum TokenName
{
    left_italic_bracket, const_str, const_int, left_square_bracket, right_italic_bracket, right_square_bracket, proj
};
class Closure
{
    shared_ptr<long long> int_v;
    shared_ptr<string> str_v;
public:
    Closure() = default;
    Closure(const Closure & rhs) = default;
    Closure(Closure && rhs) = default;
    Closure(const string & rhs);
    Closure(const long long rhs);
    bool valid() const;
    long long & get_int() const;
    string & get_str() const;
    bool operator<(const TClosure & rhs);
};
class DynamicClass
{
    shared_ptr<map<Closure, Closure> table;
public:
    Closure & operator[](const Closure & title);
};

class Token
{
public:
    TokenName token_name;
    Closure attribute_value;
    Token(TokenName _token_name, const Closure & _attribute_value)
        : token_name(_token_name), attribute_value(_attribute_value) {}
};
class JSonScanner
{
    bool skip_char(char c);
public:
    JSonScanner(Lexemes & opt, istream & ipt);
};

class JSonParser
{

public:
    JSonParser();
};

#endif // JSONPARSER_HPP
