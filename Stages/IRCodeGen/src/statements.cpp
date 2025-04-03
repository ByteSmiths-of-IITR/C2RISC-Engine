#include "header.h"
#include "utility.h"

//=====================[ Statements ]=========================================================================================

void statement_H(ASTNode *node)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "labeled_statement";
    std::string P2 = "compound_statement";
    std::string P3 = "expression_statement";
    std::string P4 = "selection_statement";
    std::string P5 = "iteration_statement";
    std::string P6 = "jump_statement";
    std::string P7 = "declaration";

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
        // Data to be fetched
        std::string varName = "Just a Dummy";
        TypeExpression type;
        VALUE_TYPE valueType = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace = SPACE::UNKNOWN_SPACE;
        expression_statement_H(node->children[0], "NONE", varName, type, valueType, valueSpace);
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
        ERROR_EXIT_H;
        return;
    }

    EXIT_H;
}

void statement_list_H(ASTNode *node)
{
    ENTRY_H;

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
        ERROR_EXIT_H;
        return;
    }

    EXIT_H;
}

void compound_statement_H(ASTNode *node)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "LCURLY RCURLY";
    std::string P2 = "LCURLY statement_list RCURLY";
    std::string P3 = "LCURLY declaration_list RCURLY";
    std::string P4 = "LCURLY declaration_list statement_list RCURLY";

    // NO ATTRIBUTES

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4)
    {
        ERROR_EXIT_H;
        return;
    }

    int enteredScope = SYM_TABLE.enterScope();                                             // [👌 Default Scope Handling]
    A_PTree node->addAttribute("Scope Entered : S" + std::to_string(enteredScope) + " ⤵️"); // 🌴 Adding syn_attr

    if (whichProduction == P1)
    {
        // Nothing to do
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
        ERROR_EXIT_H;
        return;
    }

    // SCOPE EXIT // [👌 Default Scope Handling]
    int exitedScope = SYM_TABLE.exitScope();
    A_PTree node->addAttribute("Scope S" + std::to_string(exitedScope) + " Exited ↙️");

    EXIT_H;
}

void expression_statement_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "expression SEMI_COLON";
    std::string P2 = "SEMI_COLON";

    if (whichProduction == P1)
    {
        // Call the expression handler
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1 = TypeExpression();
        VALUE_TYPE valueType1 = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace1 = SPACE::UNKNOWN_SPACE;
        expression_H(node->children[0], "NONE", varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // Pass the data up
        varName = varName1;
        type = type1;
        valueType = valueType1;
        valueSpace = valueSpace1;

        A_PTree node->addAttribute("❣️ varName    : " + varName1);              // 🌴 Adding syn_attr
        A_PTree node->addAttribute("❣️ type       : " + toString(type1));       // 🌴 Adding syn_attr
        A_PTree node->addAttribute("❣️ valueType  : " + toString(valueType1));  // 🌴 Adding syn_attr
        A_PTree node->addAttribute("❣️ valueSpace : " + toString(valueSpace1)); // 🌴 Adding syn_attr
    }
    else if (whichProduction == P2)
    {
        // Nothing to do
        varName = NO_ARG;
        type = TypeExpression();
        valueType = VALUE_TYPE::UNKNOWN;
        valueSpace = SPACE::UNKNOWN_SPACE;
    }
    else
    {
        ERROR_EXIT_H;
        return;
    }

    EXIT_H;
}

//==================== [Control Flow Statements] =========================================================================================

void selection_statement_H(ASTNode *node)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "IF LPAREN expression RPAREN statement";
    std::string P2 = "IF LPAREN expression RPAREN statement ELSE statement";
    std::string P3 = "SWITCH LPAREN expression RPAREN statement";

    if (whichProduction == P1)
    {
        // Get Ready to call expression
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;

        expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        aptLOG("e1 okay");

        PASS_THE_ERROR(varName1);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // Now we can use the expression
        std::string trueEnd = CODE_BASE.newLabel();
        CODE_BASE.addTAC(node, trueEnd, IF_FALSE, varName1, NO_ARG);

        // Next we evaluate the statement
        statement_H(node->children[4]);
        aptLOG("e2 okay");

        // Now we put the label
        CODE_BASE.addTAC(node, trueEnd, LABEL, NO_ARG, NO_ARG);
    }
    else if (whichProduction == P2)
    {
        // Get Ready to call expression
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;

        expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);
        aptLOG("e1 okay");

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);
        aptLOG("SPACE okay");

        // Now we can use the expression
        std::string trueEnd = CODE_BASE.newLabel();
        aptLOG("trueEnd okay");
        CODE_BASE.addTAC(node, trueEnd, IF_FALSE, varName1, NO_ARG);
        aptLOG("IR Code+ okay");

        // Next we evaluate the statement
        statement_H(node->children[4]);
        aptLOG("s1 okay");

        // Now we put the label
        CODE_BASE.addTAC(node, trueEnd, LABEL, NO_ARG, NO_ARG);

        // Now we can evaluate the else statement
        std::string elseEnd = CODE_BASE.newLabel();
        CODE_BASE.addTAC(node, elseEnd, GOTO_LABEL, NO_ARG, NO_ARG);

        // Evaluate the else statement
        statement_H(node->children[6]);
        aptLOG("s2 okay");

        // Now we put the label
        CODE_BASE.addTAC(node, elseEnd, LABEL, NO_ARG, NO_ARG);
    }
    else if (whichProduction == P3)
    {
        // Get Ready to call expression
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;

        expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // [🔴🔴🔴 TOTHINK 🔴🔴🔴]

        ERROR_EXIT_H;
    }
    else
    {
        // Wrong Production
        ERROR_EXIT_H;
        return;
    }
    return;
}

std::stack<std::string> CONTINUE_LABELS;   // Jumps to the next iteration
std::stack<std::string> BREAK_LABELS;      // Exits the loop or switch's end
std::set<std::string> USER_DEFINED_LABELS; // used by goto statement
std::stack<std::string> SWITCH_ARG;        // used by switch statement to make comparison

void iteration_statement_H(ASTNode *node)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "WHILE LPAREN expression RPAREN statement";
    std::string P2 = "UNTIL LPAREN expression RPAREN statement";
    std::string P3 = "DO statement WHILE LPAREN expression RPAREN SEMI_COLON";
    std::string P4 = "FOR LPAREN expression_statement expression_statement RPAREN statement";
    std::string P5 = "FOR LPAREN expression_statement expression_statement expression RPAREN statement";
    std::string P6 = "FOR LPAREN declaration expression_statement expression RPAREN statement";

    if (whichProduction == P1)
    {
        // put the loopStart label
        std::string loopStart = CODE_BASE.newLabel();
        CODE_BASE.addTAC(node, loopStart, LABEL, NO_ARG, NO_ARG);

        // Get Ready to call expression
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // Compare then jump to loopEnd
        std::string loopEnd = CODE_BASE.newLabel();
        CODE_BASE.addTAC(node, loopEnd, IF_FALSE, varName1, NO_ARG);

        // Now we can evaluate the statement
        statement_H(node->children[4]);

        // We go back to the start of the loop
        CODE_BASE.addTAC(node, loopStart, GOTO_LABEL, NO_ARG, NO_ARG);

        // Put loopEnd label
        CODE_BASE.addTAC(node, loopEnd, LABEL, NO_ARG, NO_ARG);
    }
    else if (whichProduction == P2)
    {
        // [🔴🔴🔴 TOTHINK 🔴🔴🔴]

        ERROR_EXIT_H;
    }
    else if (whichProduction == P3)
    {
        // Do while statement
        // put the loopStart label
        std::string loopStart = CODE_BASE.newLabel();
        CODE_BASE.addTAC(node, loopStart, LABEL, NO_ARG, NO_ARG);

        // Now we can evaluate the statement
        statement_H(node->children[1]);

        // Get Ready to call expression
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        expression_H(node->children[4], "NONE", varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(varName1);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // Compare then jump to loopEnd
        std::string loopEnd = CODE_BASE.newLabel();
        CODE_BASE.addTAC(node, loopEnd, IF_FALSE, varName1, NO_ARG);

        // We go back to the start of the loop
        CODE_BASE.addTAC(node, loopStart, GOTO_LABEL, NO_ARG, NO_ARG);

        // Put loopEnd label
        CODE_BASE.addTAC(node, loopEnd, LABEL, NO_ARG, NO_ARG);
    }
    else if (whichProduction == P4)
    {
        // Also need to think about Early Scope Entry
        int scopeNo = SYM_TABLE.earlyEntry(); //  [☀️ EarlyScope Entry] [IT's POSSIBLE that the early scope entry was never used in here]
        A_PTree node->addAttribute("Early Scope Entry : S" + std::to_string(scopeNo) + " ☀️");
    
    
        // Handle EarlyEnter's Exit
        int exitedScope = SYM_TABLE.earlyExit(); //  [☀️ EarlyScope Entry] [IT's POSSIBLE that the early scope entry was never used in here]
        A_PTree node->addAttribute("Exit due to EarlyEntry : S" + std::to_string(exitedScope) + " ☀️");
    }
    else if (whichProduction == P5)
    {
        // Early Scope Entry
        int scopeNo = SYM_TABLE.earlyEntry();                                                 //  [☀️ EarlyScope Entry]                                                         // This will tell the symbol table to ignore the next entry by compound_statement
        A_PTree node->addAttribute("Early Scope Entry : S" + std::to_string(scopeNo) + " ☀️"); // 🌴 Adding syn_att

        // Get Ready to call expression
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1); // [It's IRCode]
        PASS_THE_ERROR(varName1);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // Create LoopStart Label
        std::string loopStart = CODE_BASE.newLabel();
        CODE_BASE.addTAC(node, loopStart, LABEL, NO_ARG, NO_ARG);

        // Put a Condition to jump to loopEnd
        std::string loopEnd = CODE_BASE.newLabel();
        CODE_BASE.addTAC(node, loopEnd, IF_FALSE, varName1, NO_ARG); // ifFlase(E1.value) goto loopEnd

        // Now we can evaluate the statement
        statement_H(node->children[4]); // [IRCode of statement will be generated]

        // Then we put code of expression3 - which is updation code

        // Data to be fetched
        std::string varName2 = "Just a Dummy";
        TypeExpression type2;
        VALUE_TYPE valueType2;
        SPACE valueSpace2;
        expression_H(node->children[2], "NONE", varName2, type2, valueType2, valueSpace2); // [It's IRCode]
        PASS_THE_ERROR(varName2);

        // We won't be using the value of expression3 [just it's SIDE EFFECTS]

        // Then we go back to the start of the loop [Unconditional Jump]
        CODE_BASE.addTAC(node, loopStart, GOTO_LABEL, NO_ARG, NO_ARG);

        // Put loopEnd label
        CODE_BASE.addTAC(node, loopEnd, LABEL, NO_ARG, NO_ARG);

        // Handle EarlyEnter's Exit
        int exitedScope = SYM_TABLE.earlyExit(); //  [☀️ EarlyScope Entry] [IT's POSSIBLE that the early scope entry was never used in here]
        A_PTree node->addAttribute("Exit due to EarlyEntry : S" + std::to_string(exitedScope) + " ☀️"); // 🌴 Adding syn_attr


    }
    else if (whichProduction == P6)
    {
    }
    else
    {
        // Wrong Production
        ERROR_EXIT_H;
        return;
    }
    return;
}

void jump_statement_H(ASTNode *node)
{
    ENTRY_H;
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
        ERROR_EXIT_H;
        return;
    }
}

void labeled_statement_H(ASTNode *node)
{
    ENTRY_H;
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
        ERROR_EXIT_H;
        return;
    }
    return;
}
