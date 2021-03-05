#include <list>
#include <string>
#include <cctype>
#include <iostream>

#include "parser.h"
#include "lexer.h"
#include "inputbuf.h"

using namespace std;

void Parser::syntax_error() {
    cout << "Syntax Error\n";
    exit(1);
}

string Parser::parseStmt(LexicalAnalyzer &lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == ID){
        out += t.lexeme;
        Token u = lexer.GetToken();
        if (u.token_type == EQUAL) {
            out += " = ";
            t = lexer.GetToken();
            if (t.token_type == ID) {
                out += t.lexeme;
                t = lexer.GetToken();
                if (t.token_type == SEMICOLON) {
                    out += "\n";
                } else {
                    syntax_error();
                }
            } else {
                syntax_error();
            }
        } else if (u.token_type == LBRAC) {
            lexer.UngetToken(u);
            lexer.UngetToken(t);
            out += parseScope(lexer);
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }

    return out;
}

string Parser::parseStmtList(LexicalAnalyzer &lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == ID) {
        lexer.UngetToken(t);
        out += parseStmt(lexer);
        t = lexer.GetToken();
        if (t.token_type == ID) {
            lexer.UngetToken(t);
            out += parseStmtList(lexer);
        } else {
            lexer.UngetToken(t);
        }
    } else {
        syntax_error();
    }

    return out;
}

string Parser::parseVarList(LexicalAnalyzer &lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == ID) {
        t = lexer.GetToken();
        //out += "var_list -> ID\n";
        if (t.token_type == COMMA) {
            out += parseVarList(lexer);
            //out += "var_list -> ID COMMA var_list\n";
        } else if (t.token_type == SEMICOLON) {
            lexer.UngetToken(t);
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }

    return out;
}

string Parser::parsePrivateVars(LexicalAnalyzer &lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == PRIVATE) {
        t = lexer.GetToken();
        if (t.token_type == COLON) {
            out += parseVarList(lexer);
            t = lexer.GetToken();
            if (t.token_type == SEMICOLON) {
                //out += "private_vars -> PRIVATE COLON var_list SEMICOLON\n";
            } else {
                syntax_error();
            }
        } else {
            syntax_error();
        }
    } else if (t.token_type == ID) {
        lexer.UngetToken(t);
        out += "?";
    } else {
        syntax_error();
    }

    return out;
}

string Parser::parsePublicVars(LexicalAnalyzer &lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == PUBLIC) {
        t = lexer.GetToken();
        if (t.token_type == COLON) {
            out += parseVarList(lexer);
            t = lexer.GetToken();
            if (t.token_type == SEMICOLON) {
                out += "\n";
            } else {
                syntax_error();
            }
        }
    } else /*if (t.token_type == PRIVATE || t.token_type == ID)*/ {
        lexer.UngetToken(t);
        out += "." + t.lexeme;
    } /*else {
        t.Print();
        out += "Syntax Error - parsePublicVars_2\n";
    }*/

    return out;
}

string Parser::parseScope(LexicalAnalyzer &lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == ID) {
        t = lexer.GetToken();
        if (t.token_type == LBRAC) {
            out += parsePublicVars(lexer);
            out += parsePrivateVars(lexer);
            out += parseStmtList(lexer);
            t = lexer.GetToken();
            if (t.token_type == RBRAC) {
                out += "\n";
            } else {
                syntax_error();
            }
        } else {
            syntax_error();
        }
    }

    return out;
}

string Parser::parseGlobalVars(LexicalAnalyzer &lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == ID) {
        lexer.UngetToken(t);
        out += parseVarList(lexer);
        t = lexer.GetToken();
        if (t.token_type == SEMICOLON) {
            //out += "global_vars -> var_list SEMICOLON\n";
        } else {
            syntax_error();
        }
    } else {
        syntax_error();
    }

    return out;
}

string Parser::parseProgram(LexicalAnalyzer &lexer) {
    Token t = lexer.GetToken();
    string out;
    
    if (t.token_type == ID) {
        lexer.UngetToken(t);
        out += parseGlobalVars(lexer);
        out += parseScope(lexer);
        //out += "program -> global_vars scope\n";
    } else if (t.token_type == END_OF_FILE) {
        out += "eof\n";
    } else {
        syntax_error();
    }

    return out;
}

void Parser::startParse(LexicalAnalyzer &lexer) {
    cout << parseProgram(lexer) << endl;
}

int main() {
    LexicalAnalyzer lexer;
    Parser parser;
    parser.startParse(lexer);
}