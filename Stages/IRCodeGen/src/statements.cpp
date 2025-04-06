#include "header.h"
#include "utility.h"

//=====================[ Statements ]=========================================================================================

int statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap)
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

    aptLOG("⬇️ S_nextList = " + toString(S_nextList));

    if (whichProduction == P1)
    {
        // Call the labeled statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        int ls_check = labeled_statement_H(node->children[0], S1_nextList, breakList, continueList, caseMap);
        PASS_THE_ERROR(ls_check);

        // Pass the data up
        S_nextList = S1_nextList;
    }
    else if (whichProduction == P2)
    {
        // Call the compound statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        int cs_check = compound_statement_H(node->children[0], S1_nextList, breakList, continueList, caseMap);
        PASS_THE_ERROR(cs_check);

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
        int est_check = expression_statement_H(node->children[0], "NONE", varName, type, valueType, valueSpace);
        PASS_THE_ERROR(est_check);

        // Pass the data up
        S_nextList = std::vector<int>(); // No Next List
    }
    else if (whichProduction == P4)
    {
        // Call the selection statement handler
        std::vector<int> S1_nextList;
        int sst_check = selection_statement_H(node->children[0], S1_nextList, breakList, continueList, caseMap);
        PASS_THE_ERROR(sst_check);

        // Pass the data up
        S_nextList = S1_nextList;
    }
    else if (whichProduction == P5)
    {
        // Call the iteration statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        int ist_check = iteration_statement_H(node->children[0], S1_nextList, breakList, continueList, caseMap);
        PASS_THE_ERROR(ist_check);
        // Pass the data up
        S_nextList = S1_nextList;
    }
    else if (whichProduction == P6)
    {
        // Call the jump statement handler
        // Data to be fetched
        std::vector<int> S1_nextList;
        int jst_check = jump_statement_H(node->children[0], S1_nextList, breakList, continueList, caseMap);
        PASS_THE_ERROR(jst_check);

        // Pass the data up
        S_nextList = S1_nextList;
    }
    else if (whichProduction == P7)
    {
        // Call the declaration handler
        int dcl_check = declaration_H(node->children[0]);
        PASS_THE_ERROR(dcl_check);
    }   
    else
    {
        compilerError("")
        BUG_H;
        return BUG;
    }

    aptLOG("⬆️ S_nextList = " + toString(S_nextList));

    EXIT_H;
    return OKAY;
}

int statement_list_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "statement";
    std::string P2 = "statement_list statement";

    aptLOG("⬇️ S_nextList = " + toString(S_nextList));

    if (whichProduction == P1)
    {
        // Call the statement handler
        std::vector<int> S1_nextList;
        int s_check = statement_H(node->children[0], S1_nextList, breakList, continueList, caseMap);
        RECOVER_THE_ERROR(s_check);

        // Pass the data up
        S_nextList = S1_nextList;
    }
    else if (whichProduction == P2)
    {
        // Call the statement list handler
        std::vector<int> S1_nextList;
        int sl_check = statement_list_H(node->children[0], S1_nextList, breakList, continueList, caseMap);
        RECOVER_THE_ERROR(sl_check);

        // BackPatch the next list
        int aLabel = CODE_BASE.nextIndex();
        CODE_BASE.backpatch(node, S1_nextList, aLabel);

        // Call the statement handler
        std::vector<int> S2_nextList;
        int s_check = statement_H(node->children[1], S2_nextList, breakList, continueList, caseMap);
        RECOVER_THE_ERROR(s_check);

        // Pass the data up
        S_nextList = S2_nextList;
    }
    else
    {
        compilerError("Wrong Production in statement_list_H");
        BUG_H;
        // Setup Dummy Data
        S_nextList = std::vector<int>(); // No Next List
        return BUG;
    }

    aptLOG("⬆️ S_nextList = " + toString(S_nextList));

    EXIT_H;
    return OKAY;
}

int compound_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "LCURLY RCURLY";
    std::string P2 = "LCURLY statement_list RCURLY";
    std::string P3 = "LCURLY declaration_list RCURLY";
    std::string P4 = "LCURLY declaration_list statement_list RCURLY";

    if (whichProduction != P1 && whichProduction != P2 && whichProduction != P3 && whichProduction != P4)
    {
        compilerError("Wrong Production in compound_statement_H");
        BUG_H;
        S_nextList = std::vector<int>();
        return BUG;
    }

    int enteredScope = SYM_TABLE.enterScope();
    if (enteredScope != IGNORED)
    { // [👌 Default Scope Handling]
        aptLOG("Scope Entered : S" + std::to_string(enteredScope) + " ⤵️");
    }
    else
    {
        aptLOG("Scope Entry IGNORED 🫣, Current Scope - " + std::to_string(SYM_TABLE.scopeNo));
    }

    aptLOG("⬇️ S_nextList = " + toString(S_nextList));
    aptLOG("⬇️ breakList = " + toString(breakList));
    aptLOG("⬇️ continueList = " + toString(continueList));

    if (whichProduction == P1)
    {
        S_nextList = std::vector<int>();
        breakList = std::vector<int>();
        continueList = std::vector<int>();
    }
    else if (whichProduction == P2)
    {
        // For Now Just Call Statement List
        std::vector<int> S1_nextList;
        std::vector<int> S1_breakList;
        std::vector<int> S1_continueList;
        int sl_check = statement_list_H(node->children[1], S1_nextList, S1_breakList, S1_continueList, caseMap);
        RECOVER_THE_ERROR(sl_check);

        // Pass the data up
        S_nextList = S1_nextList;
        breakList = S1_breakList;
        continueList = S1_continueList;
    }
    else if (whichProduction == P3)
    {
        // For Now Just Call Declaration List
        int dcl_check = declaration_list_H(node->children[1]);
        RECOVER_THE_ERROR(dcl_check);

        S_nextList = std::vector<int>(); // No Next List
    }
    else if (whichProduction == P4)
    {
        // For Now Just Call Declaration List
        int dcl_check = declaration_list_H(node->children[1]);
        RECOVER_THE_ERROR(dcl_check);

        // For Now Just Call Statement List
        std::vector<int> S1_nextList;
        std::vector<int> S1_breakList;
        std::vector<int> S1_continueList;
        int sl_check = statement_list_H(node->children[2], S1_nextList, S1_breakList, S1_continueList, caseMap);
        RECOVER_THE_ERROR(sl_check);

        S_nextList = S1_nextList; // This was last statement - can't backpatch here send UP
        breakList = S1_breakList;
        continueList = S1_continueList;
    }
    else
    {
        compilerError("Wrong Production in compound_statement_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⬆️ S_nextList = " + toString(S_nextList));
    aptLOG("⬆️ breakList = " + toString(breakList));
    aptLOG("⬆️ continueList = " + toString(continueList));

    // SCOPE EXIT // [👌 Default Scope Handling]
    if (enteredScope != IGNORED)
    {
        int exitedScope = SYM_TABLE.exitScope();
        aptLOG("Scope S" + std::to_string(exitedScope) + " Exited ↙️");
    }
    else
    {
        aptLOG("Scope Exit IGNORED 🫣, Current Scope - " + std::to_string(SYM_TABLE.scopeNo));
    }

    EXIT_H;
    return OKAY;
}

int expression_statement_H(ASTNode *node, std::string inh_whereToSendString, std::string &varName, TypeExpression &type, VALUE_TYPE &valueType, SPACE &valueSpace)
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
        int e_check = expression_H(node->children[0], "NONE", varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(e_check);

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
        compilerError("Wrong Production in expression_statement_H");
        BUG_H;
        return BUG;
    }

    aptLOG("🔵 varName : " + varName);
    aptLOG("🔵 type : " + toString(type));
    aptLOG("🔵 valueType : " + toString(valueType));
    aptLOG("🔵 valueSpace : " + toString(valueSpace));

    EXIT_H;
    return OKAY;
}

//==================== [Control Flow Statements] =========================================================================================

std::string DEFAULT_CASE = "DEFAULT_CASE";

int selection_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "IF LPAREN expression RPAREN statement";
    std::string P2 = "IF LPAREN expression RPAREN statement ELSE statement";
    std::string P3 = "SWITCH LPAREN expression RPAREN statement";

    aptLOG("⬇️ S_nextList = " + toString(S_nextList));
    aptLOG("⬇️ breakList = " + toString(breakList));
    aptLOG("⬇️ continueList = " + toString(continueList));

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

        int e_check = expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(e_check);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // 🅱️ TypeChecking of Expression
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type1);
        if (whichType == Type::STRUCT_UNION)
        {
            semanticError("Expression inside if statement cannot be of type STRUCT_UNION");
            FAIL_H;
            return FAIL;
        }

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName1, NO_ARG);  // if (varName != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        mergeList(E_truelist, aLabel);
        mergeList(E_falselist, bLabel);

        int nextLabel = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, E_truelist, nextLabel);

        std::vector<int> S1_nextList; // This value will be fetchec
        // Next we evaluate the statement
        int s_check = statement_H(node->children[4], S1_nextList, breakList, continueList, caseMap);
        RECOVER_THE_ERROR(s_check);

        mergeList(S_nextList, E_falselist);
        mergeList(S_nextList, S1_nextList);
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

        int e_check = expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(e_check);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // 🅱️ TypeChecking of Expression
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type1);
        if (whichType == Type::STRUCT_UNION)
        {
            semanticError("Type Error: Expression inside if statement cannot be of type STRUCT_UNION");
            FAIL_H;
            return FAIL;
        }

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName1, NO_ARG);  // if (varName != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        mergeList(E_truelist, aLabel);
        mergeList(E_falselist, bLabel);

        int nextLabel = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, E_truelist, nextLabel);

        std::vector<int> S1_nextList; // This value will be fetchec
        // Next we evaluate the statement
        int s_check = statement_H(node->children[4], S1_nextList, breakList, continueList, caseMap);
        RECOVER_THE_ERROR(s_check);

        int cLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto cLabel

        mergeList(S_nextList, cLabel);

        int d_index = CODE_BASE.nextIndex();

        int check2 = CODE_BASE.backpatch(node, E_falselist, d_index);

        std::vector<int> S2_nextList; // This value will be fetchec
        // Next we evaluate the statement
        int s_check2 = statement_H(node->children[6], S2_nextList, breakList, continueList, caseMap);
        RECOVER_THE_ERROR(s_check2);
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

        int e_check = expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(e_check);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // 🅱️ TypeChecking of Expression
        // MAX size allowed is INT - TYPE_CHAR,TYPE_SHORT,TYPE_INT,TYPE_ENUM,ENUMCONST

        std::string baseType = isPrimitive(type1); //[ ENUM & ENUM_CONSTANT are given as TYPE_INT]
        if (!(baseType == TYPE_CHAR || baseType == TYPE_SHORT || baseType == TYPE_INT || baseType == "ENUM" || baseType == "ENUM_CONSTANT"))
        {
            semanticError("SEMANTIC ERROR ‼️: Expression inside switch statement cannot be of type " + baseType);
        }

        // 🔖 IRCode Gen

        breakAllowed++;
        int jumpToMAP = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto jumpToMAP

        std::map<std::string, int> caseMap1;

        std::vector<int> S1_nextList;     // This value will be fetchec
        std::vector<int> S1_breakList;    // This value will be fetchec
        std::vector<int> S1_continueList; // This value will be fetchec
        caseAllowed++;
        breakAllowed++;
        int s_check = statement_H(node->children[4], S1_nextList, S1_breakList, S1_continueList, caseMap1);
        RECOVER_THE_ERROR(s_check);
        caseAllowed--;
        breakAllowed--;
        int defaultExit = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto defaultExit

        bool isDefault = false;
        int defaultJumpAddress;

        int mapStart = CODE_BASE.nextIndex();
        int check = CODE_BASE.backpatch(node, {jumpToMAP}, mapStart);

        if (caseMap1.find(DEFAULT_CASE) != caseMap1.end())
        {
            isDefault = true;
            defaultJumpAddress = caseMap1[DEFAULT_CASE];
            caseMap1.erase(DEFAULT_CASE);
        }
        else
        {
            defaultJumpAddress = -1;
        }

        for (auto it : caseMap1)
        {
            if (it.first == DEFAULT_CASE)
            {
                // Should not happen
            }
            else
            {
                std::string caseIndex = "L(" + std::to_string(it.second) + ")";
                CODE_BASE.addTAC(node, caseIndex, GOTO_EQUAL, varName1, it.first); // if (varName1 == it.first) goto it.second
            }
        }

        if (isDefault)
        {
            std::string defaultIndex = "L(" + std::to_string(defaultJumpAddress) + ")";
            CODE_BASE.addTAC(node, defaultIndex, GOTO_LABEL, NO_ARG, NO_ARG); // goto defaultJumpAddress
        }

        mergeList(S_nextList, S1_nextList);
        mergeList(S_nextList, S1_breakList);
        mergeList(S_nextList, defaultExit);
        continueList = S1_continueList; // Pass it up since switch is not a loop
    }
    else
    {
        compilerError("Wrong Production in selection_statement_H");
        BUG_H;
        S_nextList = std::vector<int>();
        return BUG;
    }

    aptLOG("⬆️ S_nextList = " + toString(S_nextList));
    aptLOG("⬆️ breakList = " + toString(breakList));
    aptLOG("⬆️ continueList = " + toString(continueList));

    EXIT_H;
    return OKAY;
}

int iteration_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap)
{
    ENTRY_H;

    std::string whichProduction = getProduction(node);
    std::string P1 = "WHILE LPAREN expression RPAREN statement";
    std::string P2 = "UNTIL LPAREN expression RPAREN statement";
    std::string P3 = "DO statement WHILE LPAREN expression RPAREN SEMI_COLON";
    std::string P4 = "FOR LPAREN expression_statement expression_statement RPAREN statement";
    std::string P5 = "FOR LPAREN expression_statement expression_statement expression RPAREN statement";
    std::string P6 = "FOR LPAREN declaration expression_statement expression RPAREN statement";

    // Early Scope Entry
    int enteredScope = SYM_TABLE.enterScope(); // This will tell the symbol table to ignore the next entry by compound_statement
    aptLOG("Scope Entered : S" + std::to_string(enteredScope) + " ⤵️");

    aptLOG("⬇️ S_nextList = " + toString(S_nextList));
    aptLOG("⬇️ breakList = " + toString(breakList));
    aptLOG("⬇️ continueList = " + toString(continueList));

    if (whichProduction == P1)
    {
        // Find Loop's Start position
        int loopStart = CODE_BASE.nextIndex();
        std::string loopStartLabel = "L(" + std::to_string(loopStart) + ")";

        std::vector<int> E_truelist, E_falselist;
        // Get Ready to call expression
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int e_check = expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(e_check);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // while ✅(int char ptr function_name array_name float double enum_const enum_name) ❌(struct_object union_object)
        // 🅱️ TypeChecking of Expression
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type1);
        if (whichType == Type::STRUCT_UNION)
        {
            semanticError("SEMANTIC ERROR ‼️: Expression inside while statement cannot be of type STRUCT_UNION");
            FAIL_H;
            return FAIL;
        }

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName1, NO_ARG);  // if (varName1 != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        mergeList(E_truelist, aLabel);
        mergeList(E_falselist, bLabel);

        int s_Start = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, E_truelist, s_Start);

        std::vector<int> S1_nextList;   // This value will be fetchec
        std::vector<int> breakList1;    // This value will be fetchec
        std::vector<int> continueList1; // This value will be fetchec
        breakAllowed++;
        continueAllowed++;
        // Next we evaluate the statement
        int s_check = statement_H(node->children[4], S1_nextList, breakList1, continueList1, caseMap);
        RECOVER_THE_ERROR(s_check);

        breakAllowed--;
        continueAllowed--;

        // Backpatch the S1_nextList
        mergeList(S1_nextList, continueList1); // As S_nextList is a syn_attribute we don't send this below
        int check2 = CODE_BASE.backpatch(node, S1_nextList, loopStart);

        CODE_BASE.addTAC(node, loopStartLabel, GOTO_LABEL, NO_ARG, NO_ARG); // goto loopStart

        mergeList(S_nextList, E_falselist);
        mergeList(S_nextList, breakList1);
    }
    else if (whichProduction == P2)
    {
        // Find Loop's Start position
        int loopStart = CODE_BASE.nextIndex();
        std::string loopStartLabel = "L(" + std::to_string(loopStart) + ")";

        std::vector<int> E_truelist, E_falselist;
        // Get Ready to call expression
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int e_check = expression_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(e_check);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // while ✅(int char ptr function_name array_name float double enum_const enum_name) ❌(struct_object union_object)
        // 🅱️ TypeChecking of Expression
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type1);
        if (whichType == Type::STRUCT_UNION)
        {
            semanticError("SEMANTIC ERROR ‼️: Expression inside while statement cannot be of type STRUCT_UNION");
            FAIL_H;
            return FAIL;
        }

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName1, NO_ARG);  // if (varName1 != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        // SWAP of E_truelist and E_falselist [🥹🥹🥹 Relative to WHILE 🤪🤪🤪]

        mergeList(E_falselist, aLabel); // 🦉
        mergeList(E_truelist, bLabel);  // 😅

        int s_Start = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, E_falselist, s_Start);

        std::vector<int> S1_nextList;   // This value will be fetchecd
        std::vector<int> breakList1;    // This value will be fetchecd
        std::vector<int> continueList1; // This value will be fetchecd
        breakAllowed++;
        continueAllowed++;
        // Next we evaluate the statement
        int s_check = statement_H(node->children[4], S1_nextList, breakList1, continueList1, caseMap);
        RECOVER_THE_ERROR(s_check);
        breakAllowed--;
        continueAllowed--;

        // Backpatch the S1_nextList
        mergeList(S1_nextList, continueList1); // As S_nextList is a syn_attribute we don't send this below
        int check2 = CODE_BASE.backpatch(node, S1_nextList, loopStart);

        CODE_BASE.addTAC(node, loopStartLabel, GOTO_LABEL, NO_ARG, NO_ARG); // goto loopStart

        mergeList(S_nextList, E_truelist);
        mergeList(S_nextList, breakList1);
    }
    else if (whichProduction == P3)
    {

        int firstSkip = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto firstSkip

        int loopStart = CODE_BASE.nextIndex();
        std::string loopStartLabel = "L(" + std::to_string(loopStart) + ")";

        std::vector<int> E_truelist, E_falselist;
        // Get Ready to call expression
        // Data to be fetched
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int e_check = expression_H(node->children[4], "NONE", varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(e_check);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // DO while ✅(int char ptr function_name array_name float double enum_const enum_name) ❌(struct_object union_object)

        // 🅱️ TypeChecking of Expression
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type1);
        if (whichType == Type::STRUCT_UNION)
        {
            compilerError("Expression inside do while statement cannot be of type STRUCT_UNION");
            FAIL_H;
            return FAIL;
        }

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName1, NO_ARG);  // if (varName1 != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        mergeList(E_truelist, aLabel);
        mergeList(E_falselist, bLabel);

        mergeList(E_truelist, firstSkip); // FIRST SKIP added to E_truelist ?

        int s_Start = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, E_truelist, s_Start);

        std::vector<int> S1_nextList;   // This value will be fetchecd
        std::vector<int> breakList1;    // This value will be fetchecd
        std::vector<int> continueList1; // This value will be fetchecd
        // Next we evaluate the statement
        breakAllowed++;
        continueAllowed++;
        int s_check = statement_H(node->children[1], S1_nextList, breakList1, continueList1, caseMap);
        RECOVER_THE_ERROR(s_check);
        breakAllowed--;
        continueAllowed--;

        // Backpatch the S1_nextList
        mergeList(S1_nextList, continueList1);
        int check2 = CODE_BASE.backpatch(node, S1_nextList, loopStart);

        CODE_BASE.addTAC(node, loopStartLabel, GOTO_LABEL, NO_ARG, NO_ARG); // goto loopStart

        mergeList(S_nextList, E_falselist);
        mergeList(S_nextList, breakList1);
    }
    else if (whichProduction == P4)
    {
        // Call the first ExpressionStatement_1 [since it is only executed once]
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1 = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace1 = SPACE::UNKNOWN_SPACE;
        int est_check = expression_statement_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(est_check);

        int loopStart = CODE_BASE.nextIndex();
        std::string loopStartLabel = "L(" + std::to_string(loopStart) + ")";

        std::vector<int> ES2_truelist, ES2_falselist;
        // Next we evaluate the ExpressionStatement_2
        std::string varName2 = "Just a Dummy";
        TypeExpression type2;
        VALUE_TYPE valueType2 = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace2 = SPACE::UNKNOWN_SPACE;
        int est_check2 = expression_statement_H(node->children[3], "NONE", varName2, type2, valueType2, valueSpace2);
        RECOVER_THE_ERROR(est_check2);

        // TypeChecking of ExpressionStatement_2
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type2);
        if (whichType == Type::STRUCT_UNION)
        {
            semanticError("🚨 Type Error: Expression inside for statement cannot be of type STRUCT_UNION");
            FAIL_H;
            return FAIL;
        }

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName2, NO_ARG);  // if (varName2 != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        mergeList(ES2_truelist, aLabel);
        mergeList(ES2_falselist, bLabel);

        int s_Start = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, ES2_truelist, s_Start);

        std::vector<int> S1_nextList;   // This value will be fetched
        std::vector<int> breakList1;    // This value will be fetched
        std::vector<int> continueList1; // This value will be fetched
        breakAllowed++;
        continueAllowed++;
        // Next we evaluate the statement
        int s_check = statement_H(node->children[5], S1_nextList, breakList1, continueList1, caseMap);
        RECOVER_THE_ERROR(s_check);
        breakAllowed--;
        continueAllowed--;

        // Backpatch the S1_nextList
        mergeList(S1_nextList, continueList1); // As S_nextList is a syn_attribute we don't send this below
        int check2 = CODE_BASE.backpatch(node, S1_nextList, loopStart);

        CODE_BASE.addTAC(node, loopStartLabel, GOTO_LABEL, NO_ARG, NO_ARG); // goto loopStart

        mergeList(S_nextList, ES2_falselist);
        mergeList(S_nextList, breakList1);
    }
    else if (whichProduction == P5)
    {
        // Call the first ExpressionStatement_1 [since it is only executed once]
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1 = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace1 = SPACE::UNKNOWN_SPACE;
        int est_check = expression_statement_H(node->children[2], "NONE", varName1, type1, valueType1, valueSpace1);
        PASS_THE_ERROR(est_check);

        int loopStart = CODE_BASE.nextIndex();
        std::string loopStartLabel = "L(" + std::to_string(loopStart) + ")";

        std::vector<int> ES2_truelist, ES2_falselist;
        // Next we evaluate the ExpressionStatement_2
        std::string varName2 = "Just a Dummy";
        TypeExpression type2;
        VALUE_TYPE valueType2 = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace2 = SPACE::UNKNOWN_SPACE;
        int est_check2 = expression_statement_H(node->children[3], "NONE", varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(est_check2);

        // TypeChecking of ExpressionStatement_2
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type2);
        if (whichType == Type::STRUCT_UNION)
        {
            semanticError("🚨 Type Error: Expression inside for statement cannot be of type STRUCT_UNION");
            FAIL_H;
            return FAIL;
        }

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName2, NO_ARG);  // if (varName2 != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        mergeList(ES2_truelist, aLabel);
        mergeList(ES2_falselist, bLabel);

        int s_Start = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, ES2_truelist, s_Start);

        std::vector<int> S1_nextList;   // This value will be fetched
        std::vector<int> breakList1;    // This value will be fetched
        std::vector<int> continueList1; // This value will be fetched
        breakAllowed++;
        continueAllowed++;
        // Next we evaluate the statement
        int st_check = statement_H(node->children[6], S1_nextList, breakList1, continueList1, caseMap);
        PASS_THE_ERROR(st_check);
        breakAllowed--;
        continueAllowed--;

        // Backpatch the S1_nextList
        mergeList(S1_nextList, continueList1); // As S_nextList is a syn_attribute we don't send this below
        int nextAddress = CODE_BASE.nextIndex();
        int check2 = CODE_BASE.backpatch(node, S1_nextList, nextAddress);

        // Call the third Expression_3
        std::string varName3 = "Just a Dummy";
        TypeExpression type3;
        VALUE_TYPE valueType3 = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace3 = SPACE::UNKNOWN_SPACE;
        int e_check = expression_H(node->children[4], "NONE", varName3, type3, valueType3, valueSpace3);
        PASS_THE_ERROR(e_check);

        CODE_BASE.addTAC(node, loopStartLabel, GOTO_LABEL, NO_ARG, NO_ARG); // goto loopStart

        mergeList(S_nextList, ES2_falselist);
        mergeList(S_nextList, breakList1);
    }
    else if (whichProduction == P6)
    {

        // Call the Declaration Statement [since it is only executed once]
        int dcl_check = declaration_H(node->children[2]);
        PASS_THE_ERROR(dcl_check);

        int loopStart = CODE_BASE.nextIndex();
        std::string loopStartLabel = "L(" + std::to_string(loopStart) + ")";

        std::vector<int> ES2_truelist, ES2_falselist;
        // Next we evaluate the ExpressionStatement_2
        std::string varName2 = "Just a Dummy";
        TypeExpression type2;
        VALUE_TYPE valueType2 = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace2 = SPACE::UNKNOWN_SPACE;
        int est_check = expression_statement_H(node->children[3], "NONE", varName2, type2, valueType2, valueSpace2);
        PASS_THE_ERROR(est_check);

        // TypeChecking of ExpressionStatement_2
        //  Type NOT allowed - STRUCT_UNION
        Type whichType = whatIsType(type2);
        if (whichType == Type::STRUCT_UNION)
        {
            semanticError("🚨 Type Error: Expression inside for statement cannot be of type STRUCT_UNION");
            FAIL_H;
            return FAIL;
        }

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName2, type2, valueSpace2, node);

        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, IF_TRUE, varName2, NO_ARG);  // if (varName2 != 0) goto aLabel
        int bLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto bLabel

        mergeList(ES2_truelist, aLabel);
        mergeList(ES2_falselist, bLabel);

        int s_Start = CODE_BASE.nextIndex();

        int check = CODE_BASE.backpatch(node, ES2_truelist, s_Start);

        std::vector<int> S1_nextList;   // This value will be fetched
        std::vector<int> breakList1;    // This value will be fetched
        std::vector<int> continueList1; // This value will be fetched
        breakAllowed++;
        continueAllowed++;
        // Next we evaluate the statement
        int st_check = statement_H(node->children[6], S1_nextList, breakList1, continueList1, caseMap);
        PASS_THE_ERROR(st_check);
        continueAllowed--;

        // Backpatch the S1_nextList
        mergeList(S1_nextList, continueList1);
        int nextAddress = CODE_BASE.nextIndex();
        int check2 = CODE_BASE.backpatch(node, S1_nextList, nextAddress);

        // Call the third Expression_3
        std::string varName3 = "Just a Dummy";
        TypeExpression type3;
        VALUE_TYPE valueType3 = VALUE_TYPE::UNKNOWN;
        SPACE valueSpace3 = SPACE::UNKNOWN_SPACE;
        int e_check = expression_H(node->children[4], "NONE", varName3, type3, valueType3, valueSpace3);
        PASS_THE_ERROR(e_check);
        CODE_BASE.addTAC(node, loopStartLabel, GOTO_LABEL, NO_ARG, NO_ARG); // goto loopStart

        mergeList(S_nextList, ES2_falselist);
        mergeList(S_nextList, breakList1);
    }
    else
    {
        compilerError("Wrong Production in iteration_statement_H");
        BUG_H;
        return BUG;
    }

    // EXIT of Early Entry
    int exitedScope = SYM_TABLE.exitScope(); //
    aptLOG("Scope Exited : S" + std::to_string(exitedScope) + " ↙️");

    aptLOG("⬆️ S_nextList = " + toString(S_nextList));
    aptLOG("⬆️ breakList = " + toString(breakList));
    aptLOG("⬆️ continueList = " + toString(continueList));

    EXIT_H;
    return OKAY;
}

int breakAllowed = 0;
int continueAllowed = 0;
int caseAllowed = 0;

int jump_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "GOTO IDENTIFIER SEMI_COLON";
    std::string P2 = "CONTINUE SEMI_COLON";
    std::string P3 = "BREAK SEMI_COLON";
    std::string P4 = "RETURN expression SEMI_COLON"; // [TOWRITE]
    std::string P5 = "RETURN SEMI_COLON";            // [TOWRITE]

    if (whichProduction == P1)
    {
        std::string labelUsed = node->children[1]->value;
        int index = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto labelUsed
        if (labelList.find(labelUsed) == labelList.end())
        {
            std::vector<int> perLabelList = {index};
            labelList[labelUsed] = perLabelList;
        }
        else
        {
            labelList[labelUsed].push_back(index);
        }
    }
    else if (whichProduction == P2)
    {
        if (continueAllowed <= 0)
        {
            semanticError("\'continue\' statement not in loop statement");
            FAIL_H; 
            return FAIL;
        }
        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto aLabel

        mergeList(continueList, aLabel);
    }
    else if (whichProduction == P3)
    {
        if (breakAllowed <= 0)
        {
            semanticError("\'break\' statement not in loop or switch statement");
            FAIL_H;
            return FAIL;
        }
        int aLabel = CODE_BASE.addTAC(node, TO_BACKPATCH, GOTO_LABEL, NO_ARG, NO_ARG); // goto aLabel

        mergeList(breakList, aLabel);
    }
    else if (whichProduction == P4)
    {
        std::string currFuncName = SYM_TABLE.currnetScope;
        aptLOG("Current Function Name : " + currFuncName);

        // Find the function name
        GenericSymbol *sym;
        int lookupCheck = SYM_TABLE.lookup(currFuncName, sym);
        if (lookupCheck == LOOKUP_FAILURE)
        {
            semanticError("\'return\' statement use in non-function scope - " + currFuncName);
            FAIL_H;
            ;
            return FAIL;
        }
        TypeExpression funcType = ((Function *)sym)->type;

        // WE evaluate the expression
        std::string varName1 = "Just a Dummy";
        TypeExpression type1;
        VALUE_TYPE valueType1;
        SPACE valueSpace1;
        int e_check = expression_H(node->children[1], "NONE", varName1, type1, valueType1, valueSpace1);
        RECOVER_THE_ERROR(e_check);

        // 🚀 USAGE 🤫 SPACE CHANGE 🚀
        USAGE_SPACE_CHANGE(varName1, type1, valueSpace1, node);

        // 🅱️ TypeChecking of Expression
        TypeExpression returnType = funcType;
        if (popALevel(returnType))
        {
            compilerError("Error in popALevel");
            BUG_H;
            return BUG;
        }

        // We check if the return type is same as the function type
        // 🆎 TypeCasting
        TypeExpression source = type1;
        TypeExpression dest = returnType;

        bool isNum = isNumeric(source);
        bool isNum2 = isNumeric(dest);
        if (!(isNum && isNum2))
        {
            // Check if the types are same
            int check = ourEquivalent(source, dest);
            if (check != OKAY)
            {
                // SEMANTIC ERROR 🚨 : Assignment expression's operand \"" + varName1 + "\" and \"" + varName2 + "\" are not compatible
                semanticError("Return type mismatch - Expected : \'" + toString(dest) + "\' Found : \'" + toString(source) + "\'");
                FAIL_H;
                return FAIL;
            }
        }
        else
        {
            // Implicit Type Casting
            int equal = ourEquivalent(source, dest);
            if (equal != OKAY)
            {
                std::string castedVarNam = newTemp();
                CODE_BASE.addTAC(node, castedVarNam, CAST, toString(dest), varName1); // Cast it
                varName1 = castedVarNam;                                              // Change the name to the address
            }
        }

        CODE_BASE.addTAC(node, NO_ARG, RETURN_FUNCTION, varName1, NO_ARG); // return varName1
    }
    else if (whichProduction == P5)
    {
        std::string currFuncName = SYM_TABLE.currnetScope;
        aptLOG("Current Function Name : " + currFuncName);

        // Find the function name
        GenericSymbol *sym;
        int check = SYM_TABLE.lookup(currFuncName, sym);
        if (check == LOOKUP_FAILURE)
        {
            semanticError("\'return\'' statement use in non-function scope - " + currFuncName);
            FAIL_H;
            ;
            return FAIL;
        }
        TypeExpression funcType = ((Function *)sym)->type;

        // 🅱️ TypeChecking of Expression
        TypeExpression returnTypeExpr = funcType;
        if (popALevel(returnTypeExpr))
        {
            compilerError("Error in popALevel");
            BUG_H;
            return BUG;
        }
        aptLOG("Return Type : " + toString(returnTypeExpr));

        Type whichType = whatIsType(returnTypeExpr);
        if(whichType != Type::VARIABLE){
            semanticError("Return type mismatch - Expected : \'" + toString(returnTypeExpr) + "\' Found : \'void\'");
            FAIL_H;
            return FAIL;
        }

        // We check if the return type is same as the function type
        BaseInfo *base = (BaseInfo *)returnTypeExpr.levelStack[0];

        std::string voidType = base->baseType;
        bool check2 = (voidType == TYPE_VOID);
        if (check2 == 0)
        {
            semanticError("Return type mismatch - Expected : \'" + toString(returnTypeExpr) + "\' Found : \'void\'");
            FAIL_H;
            return FAIL;
        }

        CODE_BASE.addTAC(node, NO_ARG, RETURN_FUNCTION, NO_ARG, NO_ARG); // return varName1
    }
    else
    {
        compilerError("Wrong Production in jump_statement_H");
        BUG_H;
        return BUG;
    }

    aptLOG("S_nextList = " + toString(S_nextList));

    EXIT_H;
    return OKAY;
}

int labeled_statement_H(ASTNode *node, std::vector<int> &S_nextList, std::vector<int> &breakList, std::vector<int> &continueList, std::map<std::string, int> &caseMap)
{
    ENTRY_H;
    std::string whichProduction = getProduction(node);
    std::string P1 = "IDENTIFIER COLON statement";
    std::string P2 = "CASE constant_expression COLON statement";
    std::string P3 = "DEFAULT COLON statement";

    aptLOG("⬇️ S_nextList = " + toString(S_nextList));

    if (whichProduction == P1)
    {
        int labelIndex = CODE_BASE.nextIndex();
        std::string label = node->children[0]->value;
        if (labelMap.find(label) != labelMap.end())
        {
            semanticError("Label already defined");
            FAIL_H;
            return FAIL;
        }
        labelMap[label] = labelIndex;

        // Call the statement
        std::vector<int> S1_nextList;
        std::vector<int> S1_breakList;
        std::vector<int> S1_continueList;
        int s_check = statement_H(node->children[2], S1_nextList, S1_breakList, S1_continueList, caseMap);
        RECOVER_THE_ERROR(s_check);

        // Pass the data up
        S_nextList = S1_nextList;
        breakList = S1_breakList;
        continueList = S1_continueList;
    }
    else if (whichProduction == P2)
    {
        if (caseAllowed <= 0)
        {
            semanticError("\'case\' statement not in any switch statement");
            FAIL_H; return FAIL;
        }

        std::string constExpr;
        // call the constant_expression
        int cex_check = constant_expression_H(node->children[1], constExpr);
        RECOVER_THE_ERROR(cex_check);

        if(constExpr == NOT_CONSTANT){
            aptLOG("Constant Expression is not constant");
        }

        // TypeCheck for constExpr

        if (caseMap.find(constExpr) != caseMap.end())
        {
            semanticError("case - \'" + constExpr + "\' already exists");
            FAIL_H; return FAIL;
        }
        int caseIndex = CODE_BASE.nextIndex();
        caseMap[constExpr] = caseIndex;

        // Call the statement
        int s_check = statement_H(node->children[3], S_nextList, breakList, continueList, caseMap);
        RECOVER_THE_ERROR(s_check);
    }
    else if (whichProduction == P3)
    {
        if (caseAllowed <= 0)
        {
            semanticError("\'default\' statement not in any switch statement");
            FAIL_H; return FAIL;
        }

        aptHERE;

        std::string constExpr = DEFAULT_CASE;

        if (caseMap.find(constExpr) != caseMap.end())
        {
            semanticError("default already exists");
            FAIL_H; return FAIL;
        }
        int defaultIndex = CODE_BASE.nextIndex();
        caseMap[constExpr] = defaultIndex;
        aptHERE;
        // Call the statement
        int s_check = statement_H(node->children[2], S_nextList, breakList, continueList, caseMap);
        RECOVER_THE_ERROR(s_check);
        aptHERE;
    }
    else
    {
        compilerError("Wrong Production in labeled_statement_H");
        BUG_H;
        return BUG;
    }

    aptLOG("⬆️ S_nextList = " + toString(S_nextList));

    EXIT_H;
    return OKAY;
}
