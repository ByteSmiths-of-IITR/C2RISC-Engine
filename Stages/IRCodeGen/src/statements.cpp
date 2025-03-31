#include "header.h"
#include "utility.h"

//=====================[ Statements ]=========================================================================================

void statement_H(ASTNode *node)
{
    *handlerLog << "statement_H" << std::endl;
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

void compound_statement_H(ASTNode* node, bool earlyScopeEntry){
    return;
}