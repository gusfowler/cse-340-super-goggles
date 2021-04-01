#include <vector>
#include "lexer.h"

class Parser {
    public:
        void startParse(LexicalAnalyzer &lexer);

    private:
        std::string parseProgram(LexicalAnalyzer &lexer);
        std::string parseGlobalVars(LexicalAnalyzer &lexer);
        std::string parseVarList(LexicalAnalyzer &lexer);
        std::string parseScope(LexicalAnalyzer &lexer);
        std::string parsePublicVars(LexicalAnalyzer &lexer);
        std::string parsePrivateVars(LexicalAnalyzer &lexer);
        std::string parseStmtList(LexicalAnalyzer &lexer);
        std::string parseStmt(LexicalAnalyzer &lexer);
        void syntax_error();
};