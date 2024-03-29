#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum TokenType
{
    PLUS,
    MINUS,
    MUL,
    DIV,
    EQUALS,
    LPAREN,
    RPAREN
};

class Token
{
    TokenType type;
    string value;

public:
    Token(TokenType type_, string value_)
    {
        type = type_;
        value = value_;
    }
    TokenType getType()
    {
        return type;
    }
    string getValue() {
        return value;
    }
};

class Lexer
{
    string src;
    int len;

public:
    Lexer(string src_)
    {
        src = src_;
        len = src_.size();
    }
    vector<Token> tokenize()
    {
        vector<Token> tokens;
        int i = 0;
        while (i < len)
        {
            switch (src[i])
            {
            case ' ':
                while (i < len && src[i] == ' ')
                {
                    i++;
                }
                break;
            case '+':
                tokens.push_back(Token(PLUS, "+"));
                i++;
                break;
            case '-':
                tokens.push_back(Token(MINUS, "-"));
                i++;
                break;
            case '*':
                tokens.push_back(Token(MUL, "*"));
                i++;
                break;
            case '/':
                tokens.push_back(Token(DIV, "/"));
                i++;
                break;
            case '=':
                tokens.push_back(Token(EQUALS, "="));
                i++;
                break;
            case '(':
                tokens.push_back(Token(LPAREN, "("));
                i++;
                break;
            case ')':
                tokens.push_back(Token(RPAREN, ")"));
                i++;
                break;
            case '$':
                while(i<len && src[i]!='$'){
                    i++;
                }
                break;
            default:
                printf("INVALID CHARACTER");
                break;
            }
        }
        return tokens;
    }
};

int main()
{
    string src = "+-/**=()";
    Lexer lexer(src);
    vector<Token> tokens = lexer.tokenize();
    for (Token token : tokens)
    {
        cout << "<" << token.getType() << "," << token.getValue() << ">";
    }
    return 0;
}