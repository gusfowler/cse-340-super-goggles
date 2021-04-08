#include <string>
#include "lexer.h"

class Parser {
    struct scopeResolve {
        char* scope;
        scopeResolve* next;
    };

    struct sTableEntry {
        char* name;
        char* scope;
        int pubpriv;
        // int binNo;
    };

    struct sTable {
        sTableEntry* item;
        sTable *prev;
        sTable *next;
    };

    sTable* symbolTable;
    char* currentScope;
    char* lResolve;
    char* rResolve;
    scopeResolve* scopeTable;
    int currentPrivPub = 0;

    public:
        void addScope(void);
        void deleteScope(void);
        void printList(void);
        void addList(char* lexeme);
        void deleteList(void);
        void printScope(void);
        void searchList(char* iD, int lR);
        int parse_program(void);

    private:
        Token token;
        Token token1;
        TokenType tempTokenType;
        LexicalAnalyzer lexer;
        std::string global = "::";
        int parse_body(void);
        int parse_varlist(void);
        int parse_unaryOperator(void);
        int parse_binaryOperator(void);
        int parse_primary(void);
        int parse_expression(void);
        int parse_assstmt(void);
        int parse_case(void);
        int parse_caselist(void);
        int parse_switchstmt(void);
        int parse_whilestmt(void);
        int parse_ifstmt(void);
        int parse_stmt(void);
        int parse_stmtlist(void);
        int parse_typename(void);
        int parse_vardecl(void);
        int parse_vardecllist(void);
        int parse_globalVars(void);
};