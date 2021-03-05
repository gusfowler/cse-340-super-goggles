#include <list>
#include <string>
#include <cctype>

#include "parser.h"
#include "lexer.h"
#include "inputbuf.h"

using namespace std;

string Parser::parseStmt(LexicalAnalyzer lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == TokenType.ID){
        Token u = lexer.GetToken();
        if (u.token_type == TokenType.EQUALS) {
            t = lexer.GetToken();
            if (t.token_type == TokenType.ID) {
                t = lexer.GetToken();
                if (t.token_type == TokenType.SEMICOLON) {
                    out += "stmt -> ID EQUAL ID SEMICOLON\n";
                } else {
                    out += "Syntax Error\n";
                }
            } else {
                out += "Syntax Error\n";
            }
        } else if (u.token_type == TokenType.LBRACE) {
            lexer.UngetToken(t);
            lexer.UngetToken(u);
            out += "stmt -> scope\n";
        } else {
            out += "Syntax Error\n";
        }
    } else {
        out += "Syntax Error\n";
    }

    return out;
}

string Parser::parseStmtList(LexicalAnalyzer lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == TokenType.ID) {
        lexer.UngetToken(t);
        out += parseStmt(lexer);
        t = lexer.GetToken();
        out += "stmt_list -> stmt\n";
        if (t.token_type == TokenType.ID) {
            lexer.UngetToken(t);
            out += parseStmtList(lexer);
            out += "stmt_list -> stmt stmt_list\n";
        } else {
            lexer.UngetToken(t);
        }
    } else {
        out += "Syntax Error\n";
    }

    return out;
}

string Parser::parseVarList(LexicalAnalyzer lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == TokenType.ID) {
        t = lexer.GetToken();
        out += "var_list -> ID\n";
        if (t.token_type == TokenType.COMMA) {
            out += parseVarList(lexer);
            out += "var_list -> ID COMMA var_list\n";
        } else if (t.token_type == TokenType.SEMICOLON) {
            lexer.UngetToken(t);
        } else {
            out += "Syntax Error\n";
        }
    } else {
        out += "Syntax Error\n";
    }

    return out;
}

string Parser::parsePrivateVars(LexicalAnalyzer lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == TokenType.PRIVATE) {
        t = lexer.GetToken();
        if (t.token_type == TokenType.COLON) {
            out += parseVarList(lexer);
            t = lexer.GetToken();
            if (t.token_type == TokenType.SEMICOLON) {
                out += "private_vars -> PRIVATE COLON var_list SEMICOLON\n"
            } else {
                out += "Syntax Error\n";
            }
        } else {
            out += "Syntax Error\n";
        }
    } else {
        out += "Syntax Error\n";
    }

    return out;
}

string Parser::parsePublicVars(LexicalAnalyzer lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == TokenType.PUBLIC) {
        t = lexer.GetToken();
        if (t.token_type == TokenType.COLON) {
            out += parseVarList(lexer);
            t = lexer.GetToken();
            if (t.token_type == TokenType.SEMICOLON) {
                out += "public_vars -> PUBLIC COLON var_list SEMICOLON\n";
            } else {
                out += "Syntax Error\n";
            }
        }
    } else if (t.token_type == TokenType.PRIVATE) {
        lexer.UngetToken(t);
        out += "public_vars -> *\n";
    }

    return out;
}

string Parser::parseScope(LexicalAnalyzer lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == TokenType.ID) {
        t = lexer.GetToken();
        if (t.token_type == TokenType.LBRACE) {
            out += parsePublicVars(lexer);
            out += parsePrivateVars(lexer);
            out += parseStmtList(lexer);
            t = lexer.GetToken(t);
            if (t.token_type == TokenType.RBRACE) {
                out += "scope -> ID LBRACE public_vars private_vars stmt_list RBRACE\n";
            } else {
                out += "Syntax Error\n";
            }
        } else {
            out += "Syntax Error\n";
        }
    }

    return out;
}

string Parser::parseGlobalVars(LexicalAnalyzer lexer) {
    Token t = lexer.GetToken();
    string out;

    if (t.token_type == TokenType.ID) {
        lexer.UngetToken(t);
        out += parseVarList(lexer);
        t = lexer.GetToken();
        if (t.token_type == TokenType.SEMICOLON) {
            out += "global_vars -> var_list SEMICOLON\n";
        } else {
            out += "Syntax Error\n";
        }
    } else {
        out += "Syntax Error\n";
    }

    return out;
}

string Parser::parseProgram(LexicalAnalyzer lexer) {
    Token t = lexer.GetToken()
    string out;
    
    if (t.token_type == TokenType.ID) {
        lexer.UngetToken(t);
        parseGlobalVars(lexer);
        parseScope(lexer);
        out += "program -> global_vars scope\n";
    } else if (t.token_type == TokenType.END_OF_FILE) {
        out += "eof\n";
    } else {
        out += "Syntax Error\n";
    }

    return out;
}

int main() {
    LexicalAnalyzer lexer;
    cout << parseProgram(lexer) << endl;
}