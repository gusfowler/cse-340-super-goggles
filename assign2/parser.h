#include "lexer.h"

class Parser {
    public:
        void startParse(LexicalAnalyzer lexer);

    private:
        string parseProgram(Token t);
        string parseGlobalVars(Token t);
        string parseVarList(Token t);
        string parseScope(Token t);
        string parsePublicVars(Token t);
        string parsePrivateVars(Token t);
        string parseStmtList(Token t);
        string parseStmt(Token t);
}