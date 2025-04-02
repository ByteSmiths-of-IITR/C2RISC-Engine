#include "header.h"
#include "utility.h"

//=====================[ Statements ]=========================================================================================

void statement_H(ASTNode *node)
{
    ENTRY_MSG << "statement_H" << std::endl;
    lastFuncCalled = "statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "labeled_statement";
    std::string P2 = "compound_statement";
    std::string P3 = "expression_statement";
    std::string P4 = "selection_statement";
    std::string P5 = "iteration_statement";
    std::string P6 = "jump_statement";
    std::string P7 = "declaration";

    CERR << "Production: " << whichProduction << std::endl;

    A_PTree node->addAttribute("🥺 No Attributes"); // 🌴 Adding syn_attr

    if (whichProduction == P1)
    {
        // Call the labeled statement handler
        labeled_statement_H(node->children[0]);
    }
    else if (whichProduction == P2)
    {
        // Call the compound statement handler
        compound_statement_H(node->children[0]);
    }
    else if (whichProduction == P3)
    {
        // Call the expression statement handler
        expression_statement_H(node->children[0]);
    }
    else if (whichProduction == P4)
    {
        // Call the selection statement handler
        selection_statement_H(node->children[0]);
    }
    else if (whichProduction == P5)
    {
        // Call the iteration statement handler
        iteration_statement_H(node->children[0]);
    }
    else if (whichProduction == P6)
    {
        // Call the jump statement handler
        jump_statement_H(node->children[0]);
    }
    else if (whichProduction == P7)
    {
        // Call the declaration handler
        declaration_H(node->children[0]);
    }
    else
    {
        // Wrong Production
        CERR << "Wrong Production in statement_H" << std::endl;
    }
    return;
}

void statement_list_H(ASTNode *node){
    ENTRY_MSG << "statement_list_H" << std::endl;
    lastFuncCalled = "statement_list_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "statement";
    std::string P2 = "statement_list statement";

    A_PTree node->addAttribute("🥺 No Attributes"); // 🌴 Adding syn_attr

    if (whichProduction == P1)
    {
        // Call the statement handler
        statement_H(node->children[0]);
    }
    else if (whichProduction == P2)
    {
        // Call the statement list handler
        statement_list_H(node->children[0]);
        // Call the statement handler
        statement_H(node->children[1]);
    }
    else
    {
        // Wrong Production
    }
    return;
}

void compound_statement_H(ASTNode *node)
{
    ENTRY_MSG << "compound_statement_H" << std::endl;
    lastFuncCalled = "compound_statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "LCURLY RCURLY";
    std::string P2 = "LCURLY statement_list RCURLY";
    std::string P3 = "LCURLY declaration_list RCURLY";
    std::string P4 = "LCURLY declaration_list statement_list RCURLY";

    // NO ATTRIBUTES

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4)
    {
        // Wrong Production
        CERR << "Wrong Production in compound_statement_H" << std::endl;
        return;
    }

    int enteredScope = SYM_TABLE.enterScope();                                                   // [👌 Default Scope Handling]
    // CERR << "Production: " << whichProduction << std::endl;
    A_PTree node->addAttribute("Scope Entered : S" + std::to_string(enteredScope) + " ⤵️"); // 🌴 Adding syn_attr

    if (whichProduction == P1)
    {
    }
    else if (whichProduction == P2)
    {
        // For Now Just Call Statement List
        statement_list_H(node->children[1]);
    }
    else if (whichProduction == P3)
    {
        // For Now Just Call Declaration List
        declaration_list_H(node->children[1]);
    }
    else if (whichProduction == P4)
    {
        // For Now Just Call Declaration List
        declaration_list_H(node->children[1]);
    }
    else
    {
        // Wrong Production
    }

    // SCOPE EXIT
    int exitedScope = SYM_TABLE.exitScope();                                        // [👌 Default Scope Handling]
    A_PTree node->addAttribute("Scope (Global) S" + std::to_string(exitedScope) + " Exited ↙️"); // 🌴 Adding syn_attr

    return;
}

void expression_statement_H(ASTNode *node)
{
    ENTRY_MSG << "expression_statement_H" << std::endl;
    lastFuncCalled = "expression_statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "expression SEMI_COLON";
    std::string P2 = "SEMI_COLON";

    CERR << "Production:  |" << whichProduction << "|" << std::endl;

    if (whichProduction == P1)
    {
        // Call the expression handler
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1 = TypeExpression();
        VALUE_TYPE valueType1 = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace1 = SPACE::UNKNOWN_SPACE;
        expression_H(node->children[0], "NONE", varName1, type1, valueType1, valueSpace1);

        A_PTree node->addAttribute("🟡 varName = " + varName1);                 // 🌴 Adding syn_attr
        A_PTree node->addAttribute("🟡 type = " + toString(type1));             // 🌴 Adding syn_attr
        A_PTree node->addAttribute("🟡 valueType = " + toString(valueType1));   // 🌴 Adding syn_attr
        A_PTree node->addAttribute("🟡 valueSpace = " + toString(valueSpace1)); // 🌴 Adding syn_attr
    }
    else if (whichProduction == P2)
    {
        // Nothing to do
    }
    else
    {
        // Wrong Production
        CERR << "Wrong Production in expression_statement_H" << std::endl;
    }
    return;
}

//==================== [Control Flow Statements] =========================================================================================

void selection_statement_H(ASTNode *node)
{
    ENTRY_MSG << "selection_statement_H" << std::endl;
    lastFuncCalled = "selection_statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "IF LPAREN expression RPAREN statement";
    std::string P2 = "IF LPAREN expression RPAREN statement ELSE statement";
    std::string P3 = "SWITCH LPAREN expression RPAREN statement";

    if (whichProduction == P1)
    {
    }
    else if (whichProduction == P2)
    {
    }
    else if (whichProduction == P3)
    {
    }
    else
    {
        // Wrong Production
        CERR << "Wrong Production in selection_statement_H" << std::endl;
    }
    return;
}

void iteration_statement_H(ASTNode *node)
{
    ENTRY_MSG << "iteration_statement_H" << std::endl;
    lastFuncCalled = "iteration_statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "WHILE LPAREN expression RPAREN statement";
    std::string P2 = "UNTIL LPAREN expression RPAREN statement";
    std::string P3 = "DO statement WHILE LPAREN expression RPAREN SEMI_COLON";
    std::string P4 = "FOR LPAREN expression_statement expression_statement RPAREN statement";
    std::string P5 = "FOR LPAREN expression_statement expression_statement expression RPAREN statement";
    std::string P6 = "FOR LPAREN declaration expression_statement expression RPAREN statement";

    if (whichProduction == P1)
    {
    }
    else if (whichProduction == P2)
    {
    }
    else if (whichProduction == P3)
    {
    }
    else if (whichProduction == P4)
    {
    }
    else if (whichProduction == P5)
    {
    }
    else if (whichProduction == P6)
    {
    }
    else
    {
        // Wrong Production
        CERR << "Wrong Production in iteration_statement_H" << std::endl;
    }
    return;
}

void jump_statement_H(ASTNode *node)
{
    ENTRY_MSG << "jump_statement_H" << std::endl;
    lastFuncCalled = "jump_statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "GOTO IDENTIFIER SEMI_COLON";
    std::string P2 = "CONTINUE SEMI_COLON";
    std::string P3 = "BREAK SEMI_COLON";
    std::string P4 = "RETURN expression SEMI_COLON";
    std::string P5 = "RETURN SEMI_COLON";

    if (whichProduction == P1)
    {
    }
    else if (whichProduction == P2)
    {
    }
    else if (whichProduction == P3)
    {
    }
    else if (whichProduction == P4)
    {
    }
    else if (whichProduction == P5)
    {
    }
    else
    {
        // Wrong Production
        CERR << "Wrong Production in jump_statement_H" << std::endl;
    }
}

void labeled_statement_H(ASTNode *node)
{
    ENTRY_MSG << "labeled_statement_H" << std::endl;
    lastFuncCalled = "labeled_statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER COLON statement";
    std::string P2 = "CASE constant_expression COLON statement";
    std::string P3 = "DEFAULT COLON statement";

    if (whichProduction == P1)
    {
        // []
    }
    else if (whichProduction == P2)
    {
    }
    else if (whichProduction == P3)
    {
    }
    else
    {
        // Wrong Production
        CERR << "Wrong Production in labeled_statement_H" << std::endl;
    }
    return;
}
