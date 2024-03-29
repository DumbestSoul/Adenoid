#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

enum TokenType
{
    PLUS,
    MINUS,
    MUL,
    DIV,
    EQUALS,
    EQUALS_EQUALS,
    INTEGER,
    FLOAT,
    ID,
    LPAREN,
    RPAREN,
    LET,
    FOR,
    WHILE,
};

unordered_map<string, TokenType> keywords = {
    {"let", LET},
    {"for", FOR},
    {"while", WHILE}
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
            if(src[i]==' '){
                while(i<len && src[i]==' '){
                    i++;
                }
            }
            if(isChar(src[i])){ // LITERALS and KEYWORDS
                string id = "";
                while(i<len && isChar(src[i]) && src[i]!=' '){
                    id+=src[i++];
                }
                if(keywords.find(id)!=keywords.end()){
                    tokens.push_back(Token(keywords[id], id));
                }else{
                    tokens.push_back(Token(ID, id));
                }
            }
            if(isNumber(src[i])){   // NUMBER && FLOAT
                string num = "";
                bool isFloat = false;
                while(i<len && isNumber(src[i])){
                    if(src[i]=='.' && !isFloat){
                        isFloat=true;
                        num+=src[i++];
                    }
                    if(src[i]=='.' && isFloat){
                        cout << "INVALID CHARACTER";
                        exit(0);
                    }
                    num+=src[i++];
                }
                if(isFloat)
                    tokens.push_back(Token(FLOAT, num));
                else
                    tokens.push_back(Token(INTEGER, num));
            }
            if(src[i]=='+'){
                tokens.push_back(Token(PLUS, "+"));
            }
            if(src[i]=='-'){
                tokens.push_back(Token(MINUS, "-"));
            }
            if(src[i]=='*'){
                tokens.push_back(Token(MUL, "*"));
            }
            if(src[i]=='/'){
                tokens.push_back(Token(DIV, "/"));
            }
            if(src[i]=='='){
                if(i<len-1 && src[i+1]=='='){
                    tokens.push_back(Token(EQUALS_EQUALS, "=="));
                    i+=2;
                }else{
                    tokens.push_back(Token(EQUALS, "="));
                }
            }
            if(src[i]=='('){
                tokens.push_back(Token(LPAREN, "("));
            }
            if(src[i]==')'){
                tokens.push_back(Token(RPAREN, ")"));
            }
            i++;
        }
        return tokens;
    }

    bool isNumber(char c){
        return (c=='0' || c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' || c=='.');
    }

    bool isChar(char c){
        return ((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_');
    }
};

int main()
{
    string src = "for  gamma = 123.4  ";
    Lexer lexer(src);
    vector<Token> tokens = lexer.tokenize();
    for (Token token : tokens)
    {
        cout << "<" << token.getType() << "," << token.getValue() << ">";
    }
    return 0;
}