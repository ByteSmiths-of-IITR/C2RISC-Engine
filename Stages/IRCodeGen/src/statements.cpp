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
    else if (whichProduction == P7)
    {
        // Call the declaration handler
        declaration_H(node->children[0]);
    }
    else
    {
        // Wrong Production
    }
    return;
}

void statement_list_H(ASTNode *node){
    ENTRY_MSG << "statement_list_H" << std::endl;
    lastFuncCalled = "statement_list_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "statement";
    std::string P2 = "statement_list statement";

    if(whichProduction == P1){
        // Call the statement handler
        statement_H(node->children[0]);
    }
    else if(whichProduction == P2){
        // Call the statement list handler
        statement_list_H(node->children[0]);
        // Call the statement handler
        statement_H(node->children[1]);
    }
    else{
        // Wrong Production
    }
    return;
}

void compound_statement_H(ASTNode *node, bool earlyScopeEntry)
{
    ENTRY_MSG << "compound_statement_H" << std::endl;
    lastFuncCalled = "compound_statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "LCURLY RCURLY";
    std::string P2 = "LCURLY statement_list RCURLY";
    std::string P3 = "LCURLY declaration_list RCURLY";
    std::string P4 = "LCURLY declaration_list statement_list RCURLY";

    if(whichProduction==P1){

    }
    else if(whichProduction == P2){
        // For Now Just Call Statement List
        statement_list_H(node->children[1]);
    }
    else if(whichProduction == P3){
        // For Now Just Call Declaration List
        declaration_list_H(node->children[1]);
    }
    else if(whichProduction == P4){
        // For Now Just Call Declaration List
        declaration_list_H(node->children[1]);
    }
    else{
        // Wrong Production
    }

    return;
}