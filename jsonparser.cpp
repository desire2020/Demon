#include "jsonparser.hpp"

void error(const string & info)
{
    std::cerr << info << std::endl;
    exit(0);
}

JSonScanner::JSonScanner(Lexemes & opt, std::istream & fin)
{
#define PROC_LITERAL_INT if (in_lit_int)\
                         {\
                             opt.push_back(Token(literal_int, Closure(lit_int)));\
                             in_lit_int = false;\
                             is_minus = false;\
                             lit_int = 0;\
                         }
#define PROC_LITERAL_STR(ch) if (lit_str.length() != 0)\
                             {\
                                 lit_str += ch;\
                                 continue;\
                             }
    char ch;
    string this_line;
    string lit_str;
    bool in_lit_int = false;
    bool is_minus = false;
    long long lit_int = 0;
    while (!fin.eof())
    {
        getline(fin, this_line);
        for (int i = 0; i < this_line.length(); ++i)
        {
            ch = this_line[i];
            switch(ch)
            {
            case '\"' : case '\'' :
            {
                if (lit_str.length() != 0)
                {
                    opt.push_back(Token(literal_str, lit_str.substr(1)));
                    lit_str = "";
                    continue;
                } else {
                    lit_str = ":";
                    continue;
                }
            }
            break;
            case ':' :
            {
                PROC_LITERAL_STR(':');
                PROC_LITERAL_INT;
                //opt.push_back(Token(projection));
                continue;
            }
            break;
            case '{':
            {
                PROC_LITERAL_STR('{');
                PROC_LITERAL_INT;
                opt.push_back(Token(left_italic_bracket));
                continue;
            }
            break;
            case ',':
            {
                PROC_LITERAL_STR(',');
                if (in_lit_int)
                {
                    opt.push_back(Token(literal_int, Closure(lit_int)));
                    in_lit_int = false;
                    lit_int = 0;
                    continue;
                }
                //error("Too many commas occur.");
            }
            break;
            case '}':
            {
                PROC_LITERAL_STR('}');
                PROC_LITERAL_INT;
                opt.push_back(Token(right_italic_bracket));
                continue;
            }
            break;
            case '[':
            {
                PROC_LITERAL_STR('[');
                PROC_LITERAL_INT;
                opt.push_back(Token(left_square_bracket));
                continue;
            }
            break;
            case ']':
            {
                PROC_LITERAL_STR(']');
                PROC_LITERAL_INT;
                opt.push_back(Token(right_square_bracket));
                continue;
            }
            break;
            case ' ':
            {
                PROC_LITERAL_STR(' ');
                PROC_LITERAL_INT;
                continue;
            }
            break;
            case '-':
            {
                PROC_LITERAL_STR('-');
                is_minus = !is_minus;
                continue;
            }
            default:
                PROC_LITERAL_STR(ch);
                if (ch <= '9' && ch >= '0')
                {
                    if (is_minus)
                    {
                        in_lit_int = true;
                        lit_int *= 10;
                        lit_int -= (long long) (ch - '0');
                        continue;
                    } else {
                        in_lit_int = true;
                        lit_int *= 10;
                        lit_int += (long long) (ch - '0');
                        continue;
                    }
                }
                error(string("Trying to express an integer using unrecognizable character:\'") + ch + string("\'."));
            }

        }
    }
}


std::ostream & operator<<(std::ostream & fout, const Token & _token)
{
    fout << '<';
    switch (_token.token_name)
    {
    case left_italic_bracket:
        fout << "class_begin>";
    break;
    case left_square_bracket:
        fout << "list_begin>";
    break;
    case right_italic_bracket:
        fout << "class_end>";
    break;
    case right_square_bracket:
        fout << "list_end>";
    break;
    case literal_int:
        fout << "literal int, " << _token.attribute_value.get_int() << '>';
    break;
    case literal_str:
        fout << "literal str, \"" << _token.attribute_value.get_str() << "\">";
    break;
    case projection:
        fout << "->";
    break;
    }
    return fout;
}

bool Closure::valid() const
{
    return int_v != NULL || str_v != NULL || list_v != NULL || class_v != NULL;
}

long long &Closure::get_int() const
{
    return (*int_v);
}

Closure & Closure::operator[](const std::string & key) const
{
    return (*class_v)[key];
}

Closure & Closure::operator[](size_t idx) const
{
    return (*list_v)[idx];
}

void Closure::push_back(const Closure & ins)
{
    list_v -> push_back(ins);
}

std::string &Closure::get_str() const
{
    return (*str_v);
}

bool Closure::operator<(const Closure & rhs)
{
    return (*str_v) < (*rhs.str_v);
}

ostream & operator<<(ostream & fout, const Closure & _token)
{
    if (_token.str_v != NULL)
        fout << *(_token.str_v);
    else if (_token.int_v != NULL)
        fout << *(_token.int_v);
    else if (_token.list_v != NULL)
    {
        deque<Closure> & tg(*_token.list_v);
        for (auto i = tg.begin(); i != tg.end(); ++i)
            fout << *i << "\n";
    } else if (_token.class_v != NULL)
    {
        map<string, Closure> & tg(*_token.class_v);
        for (auto i = tg.begin(); i != tg.end(); ++i)
            fout << "{" << i -> first << "}->{" << i -> second << "}\n";
    }
    return fout;
}

Closure JSonParser::get_value(int & pos)
{
    if (context[pos].token_name == left_italic_bracket)
    {
        Closure ret_v(Closure::use_as_a_class());
        ++pos;
        while (context[pos].token_name != right_italic_bracket)
        {
            string title = get_value(pos).get_str();
            Closure value = get_value(pos);
            ret_v[title] = value;
        }
        ++pos;
        return ret_v;
    } else {
        if (context[pos].token_name == left_square_bracket)
        {
            Closure ret_v(Closure::use_as_a_list());
            ++pos;
            while (context[pos].token_name != right_square_bracket)
            {
                Closure value = get_value(pos);
                ret_v.push_back(value);
            }
            ++pos;
            return ret_v;
        } else {
            return context[pos++].attribute_value;
        }
    }
}
