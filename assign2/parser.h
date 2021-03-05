#include <vector>
#include "lexer.h"

class Parser {
    public:

    private:
        string parseProgram(LexicalAnalyzer lexer);
        string parseGlobalVars(LexicalAnalyzer lexer);
        string parseVarList(LexicalAnalyzer lexer);
        string parseScope(LexicalAnalyzer lexer);
        string parsePublicVars(LexicalAnalyzer lexer);
        string parsePrivateVars(LexicalAnalyzer lexer);
        string parseStmtList(LexicalAnalyzer lexer);
        string parseStmt(LexicalAnalyzer lexer);
}