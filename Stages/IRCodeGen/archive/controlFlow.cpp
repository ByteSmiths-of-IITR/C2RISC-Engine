#include "header.h"
#include "utility.h"

//=====================[ Control Flow ]=========================================================================================

// if else ✅(int char ptr function_name array_name float double enum_const enum_name) ❌(struct_object union_object)
// goto
// while ✅(int char ptr function_name array_name float double enum_const enum_name) ❌(struct_object union_object)
// do while ✅(int char ptr function_name array_name float double enum_const enum_name) ❌(struct_object union_object)
// for
// switch case ✅(int char enum_const) ❌( float double   ptr function_name array_name struct_object union_object)
// until

// break : can come only in loop and switch
// continue : can come only in loop statement
// goto : GOTO label is funtion scoped not statement scoped

// working principle
// 1. check posiible types that can come in expression inside

// BACKPATCHING
// backpatching list attribute for non-terminal A is created when it is in right side of production
// and then passed to the children
// e.g: S -> AB //here we will create list associated to A and B and do backpatching
// 1. makelist(i) creates a new list containing only i, an index into the arrayof
//  instructions; makelist returns a pointer to the newly created list.

// 2. merge(p1;p2) concatenates the lists pointed to by p1 and p2, and returns
//  a pointer to the concatenated list.

// 3. backpatch(p;i) inserts i as the target label for each of the instructions on
//  the list pointed to by p.

// CONCEPT : Whenever we start a statement and want to jump there then bind address there as start is fixed and
// for jumping to end of statement we need backpatch

// expression will return four things and take one thing
/* Data on all expressions
🟡 std::string varName; // This will be [Constants, CompilerTempName, VariableName or EnumConstantName]
🟡 TypeExpression type; //
🟡 VALUE_TYPE valueType;
🟡 SPACE valueSpace;
🔴 std::string whereToSendString; // possible value .rodata, stack
*/

void selection_statement_H(ASTNode *node)
{
    ENTRY_MSG << "selection_statement_H" << std::endl;
    lastFuncCalled = "selection_statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "IF LPAREN expression RPAREN statement";
    std::string P2 = "IF LPAREN expression RPAREN statement ELSE statement";
    std::string P3 = "SWITCH LPAREN expression RPAREN statement";

    // output inherited and synthesised attributes

    if (whichProduction == P1)
    {
        // S-> if ( E ) S1
        //  we need to get the backpatching list of selection_statement_H

        // create a backpatch list for E (truelist, falselist)
        // We need to call the expression pass its list but here we only call expression not pass list as we do not use short-circuiting

        // check possible types of expression allowed
        // generate IR code to check expression value == 1 and create goto with unfilled jump label
        //  line a : if value==1 goto __
        //  line b : goto __
        //  E.truelist = merge(E.truelist, a) and E.falselist = merge(E.falselist ,b)
        //  find the next address in IR code
        //  generate a S1.start label and backpatch(E.truelist, S.start)

        // create S1.nextlist
        //  call statement pass S1.nextlist
        //  S.nextlist = merge(E.falselist, S1.nextlist)
    }

    else if (whichProduction == P2)
    {

        // S -> if ( E ) S1 else S2
        // Get the backpatching list of selection_statement_H

        // create a backpatch list for E (truelist, falselist)
        // Evaluate the expression E
        // check type is allowed inside "if ()"
        // Generate IR code to check if the expression evaluates to true or false
        // Example:
        // line a: if value == 1 goto __
        // line b: goto __
        // E.truelist = merge(E.truelist, a)
        // E.falselist = merge(E.falselist, b)

        // Backpatch E.truelist to point to the start of S1
        // Generate a label for S1.start and backpatch E.truelist with S1.start

        // Step 3: Create S1.nextlist and call statement_H for S1 with passing list

        // Step 4: Generate a goto statement to skip S2 after S1
        // Example:
        // line c: goto __
        // S.nextlist = merge(S.nextList, c)

        // Step 5: Generate a label for S2.start and backpatch E.falselist with S2.start

        // Step 6: Create S2.nextlist and call S2 and pass S2.nextlist to the statement handler

        // Step 7: Merge the next lists of S1 and S2 to create S.nextlist
        // S.nextlist = merge(S1.nextlist, S2.nextlist)
    }
    else if (whichProduction == P3)
    {
        // switch ( E ) statement
        // create
    }
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
}

void jump_statement_H(ASTNode *node)
{
    ENTRY_MSG << "jump_statement_H" << std::endl;
    lastFuncCalled = "jump_statement_H";
    std::string whichProduction = getProduction(node);
    std::string P1 = "GOTO IDENTIFIER SEMI_COLON";
    std::string P2 = "CONTINUE SEMI_COLON";
    std::string P3 = "BREAK SEMI_COLON";
    std::string P4 = "RETURN SEMI_COLON";
    std::string P5 = "RETURN expression SEMI_COLON";
}
