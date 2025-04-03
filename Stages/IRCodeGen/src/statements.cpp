#include "header.h"
#include "utility.h"

//=====================[ Statements ]=========================================================================================

void statement_H(ASTNode *node, std::vector<int> &S_nextList)
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

    A_PTree node->addAttribute("⬇️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

    if (whichProduction == P1)
    {
        // Call the labeled statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        labeled_statement_H(node->children[0], S_nextList);

        // Pass the data up
        S_nextList = S1_nextList;
    }
    else if (whichProduction == P2)
    {
        // Call the compound statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        compound_statement_H(node->children[0], S1_nextList);

        // Pass the data up
        S_nextList = S1_nextList;
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

        // Pass the data up
        S_nextList = std::vector<int>(); // No Next List
    }
    else if (whichProduction == P4)
    {
        // Call the selection statement handler
        std::vector<int> S1_nextList;
        selection_statement_H(node->children[0], S1_nextList);

        // Pass the data up
        S_nextList = S1_nextList;
    }
    else if (whichProduction == P5)
    {
        // Call the iteration statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        iteration_statement_H(node->children[0], S1_nextList);

        // Pass the data up
        S_nextList = S1_nextList;
    }
    else if (whichProduction == P6)
    {
        // Call the jump statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        jump_statement_H(node->children[0], S1_nextList);

        // Pass the data up
        S_nextList = S1_nextList;
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

    A_PTree node->addAttribute("⬆️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

    EXIT_H;
}

void statement_list_H(ASTNode *node, std::vector<int> &S_nextList)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "statement";
    std::string P2 = "statement_list statement";

    A_PTree node->addAttribute("⬇️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

    if (whichProduction == P1)
    {
        // Call the statement handler
        std::vector<int> S1_nextList;
        statement_H(node->children[0], S1_nextList);

        // Pass the data up
        S_nextList = S1_nextList;
    }
    else if (whichProduction == P2)
    {
        // Call the statement list handler
        std::vector<int> S1_nextList;
        statement_list_H(node->children[0], S1_nextList);

        // BackPatch the next list
        int aLabel = CODE_BASE.nextIndex();
        CODE_BASE.backpatch(node, S1_nextList, aLabel);

        // Call the statement handler
        std::vector<int> S2_nextList;
        statement_H(node->children[1], S2_nextList);

        // Pass the data up
        S_nextList = S2_nextList;
    }
    else
    {
        ERROR_EXIT_H;
        // Setup Dummy Data
        S_nextList = std::vector<int>(); // No Next List
        return;
    }

    A_PTree node->addAttribute("⬆️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

    EXIT_H;
}

void compound_statement_H(ASTNode *node, std::vector<int> &S_nextList)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "LCURLY RCURLY";
    std::string P2 = "LCURLY statement_list RCURLY";
    std::string P3 = "LCURLY declaration_list RCURLY";
    std::string P4 = "LCURLY declaration_list statement_list RCURLY";

    A_PTree node->addAttribute("⬇️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4)
    {
        ERROR_EXIT_H;
        S_nextList = std::vector<int>();
        return;
    }

    int enteredScope = SYM_TABLE.enterScope();                                             // [👌 Default Scope Handling]
    A_PTree node->addAttribute("Scope Entered : S" + std::to_string(enteredScope) + " ⤵️"); // 🌴 Adding syn_attr

    if (whichProduction == P1)
    {
        S_nextList = std::vector<int>();
    }
    else if (whichProduction == P2)
    {
        // For Now Just Call Statement List
        std::vector<int> S1_nextList;
        statement_list_H(node->children[1], S1_nextList);

        S_nextList = S1_nextList;
    }
    else if (whichProduction == P3)
    {
        // For Now Just Call Declaration List
        declaration_list_H(node->children[1]);

        S_nextList = std::vector<int>(); // No Next List
    }
    else if (whichProduction == P4)
    {
        // For Now Just Call Declaration List
        declaration_list_H(node->children[1]);

        // For Now Just Call Statement List
        std::vector<int> S1_nextList;
        statement_list_H(node->children[2], S1_nextList);

        S_nextList = S1_nextList; // This was last statement - can't backpatch here send UP
    }
    else
    {
        ERROR_EXIT_H;
        return;
    }

    // Backpatch the next list
    A_PTree node->addAttribute("⬆️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr
    
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

    }
    else if (whichProduction == P2)
    {
        // Nothing to do
        varName = NO_ARG;
        type = TypeExpression(); // Can be empty
        valueType = VALUE_TYPE::UNKNOWN;
        valueSpace = SPACE::UNKNOWN_SPACE;
    }
    else
    {
        ERROR_EXIT_H;
        varName = PASS_ERROR;
        return;
    }

    A_PTree node->addAttribute("❣️ varName : " + varName);                 
    A_PTree node->addAttribute("❣️ type : " + toString(type));             
    A_PTree node->addAttribute("❣️ valueType : " + toString(valueType));   
    A_PTree node->addAttribute("❣️ valueSpace : " + toString(valueSpace)); 

    EXIT_H;
}

//==================== [Control Flow Statements] =========================================================================================

void selection_statement_H(ASTNode *node, std::vector<int> &S_nextList)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "IF LPAREN expression RPAREN statement";
    std::string P2 = "IF LPAREN expression RPAREN statement ELSE statement";
    std::string P3 = "SWITCH LPAREN expression RPAREN statement";

    A_PTree node->addAttribute("⬇️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

    if (whichProduction == P1)
    {
        // Backpatching list for expression
        std::vector<int> E_truelist, E_falselist;

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

        // 🅱️ TypeChecking of Expression
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type1);
        if (whichType == Type::STRUCT_UNION)
        {
            ERROR_EXIT_H;
            semanticLOG.push_back("🚨 Type Error: Expression inside if statement cannot be of type STRUCT_UNION");
            return;
        }

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName1, NO_ARG);  // if (varName != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        mergeList(E_truelist,aLabel);
        mergeList(E_falselist, bLabel);
        
        int nextLabel = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, E_truelist, nextLabel);

        std::vector<int> S1_nextList; // This value will be fetchec
        // Next we evaluate the statement
        statement_H(node->children[4], S1_nextList);

        mergeList(S_nextList,E_falselist);
        mergeList(S_nextList,S1_nextList);
    }
    else if (whichProduction == P2)
    {
        // Backpatching list for expression
        std::vector<int> E_truelist, E_falselist;

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

        // 🅱️ TypeChecking of Expression
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type1);
        if (whichType == Type::STRUCT_UNION)
        {
            ERROR_EXIT_H;
            semanticLOG.push_back("🚨 Type Error: Expression inside if statement cannot be of type STRUCT_UNION");
            return;
        }

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName1, NO_ARG);  // if (varName != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        mergeList(E_truelist,aLabel);
        mergeList(E_falselist, bLabel);

        int nextLabel = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, E_truelist, nextLabel);

        std::vector<int> S1_nextList; // This value will be fetchec
        // Next we evaluate the statement
        statement_H(node->children[4], S1_nextList);

        int cLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto cLabel

        mergeList(S_nextList, cLabel);

        int d_index = CODE_BASE.nextIndex();

        int check2 = CODE_BASE.backpatch(node, E_falselist, d_index);

        std::vector<int> S2_nextList; // This value will be fetchec
        // Next we evaluate the statement
        statement_H(node->children[6], S2_nextList);
        // aptLOG("s2 okay");

        mergeList(S_nextList, S1_nextList);
        mergeList(S_nextList, S2_nextList);
        // S_nextList = mergeList(S1_nextList, S2_nextList);
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
        S_nextList = std::vector<int>();
        return;
    }

    A_PTree node->addAttribute("⬆️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

    EXIT_H;
}

std::stack<std::string> CONTINUE_LABELS;   // Jumps to the next iteration
std::set<std::string> USER_DEFINED_LABELS; // used by goto statement
std::stack<std::string> SWITCH_ARG;        // used by switch statement to make comparison

void iteration_statement_H(ASTNode *node, std::vector<int> &S_nextList)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "WHILE LPAREN expression RPAREN statement";
    std::string P2 = "UNTIL LPAREN expression RPAREN statement";
    std::string P3 = "DO statement WHILE LPAREN expression RPAREN SEMI_COLON";
    std::string P4 = "FOR LPAREN expression_statement expression_statement RPAREN statement";
    std::string P5 = "FOR LPAREN expression_statement expression_statement expression RPAREN statement";
    std::string P6 = "FOR LPAREN declaration expression_statement expression RPAREN statement";

    A_PTree node->addAttribute("⬇️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

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
        std::vector<int> S1_nextList;
        statement_H(node->children[4], S1_nextList);

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
        std::vector<int> S1_nextList;
        statement_H(node->children[1], S1_nextList);

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
        std::vector<int> S1_nextList;
        statement_H(node->children[4], S1_nextList); // [IRCode of statement will be generated]

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
        int exitedScope = SYM_TABLE.earlyExit();                                                       //  [☀️ EarlyScope Entry] [IT's POSSIBLE that the early scope entry was never used in here]
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

    A_PTree node->addAttribute("⬆️ S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

    EXIT_H;
}

void jump_statement_H(ASTNode *node, std::vector<int> &S_nextList)
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
        S_nextList = std::vector<int>();
        return;
    }

    A_PTree node->addAttribute("S_nextList = " + toString(S_nextList)); // 🌴 Adding syn_attr

    EXIT_H;
}

void labeled_statement_H(ASTNode *node, std::vector<int> &S_nextList)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER COLON statement";
    std::string P2 = "CASE constant_expression COLON statement";
    std::string P3 = "DEFAULT COLON statement";

    A_PTree node->addAttribute("⬇️ S_nextList = " + toString(S_nextList)); 

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
        S_nextList = std::vector<int>();
        return;
    }

    A_PTree node->addAttribute("⬆️ S_nextList = " + toString(S_nextList)); 

    EXIT_H;
}
