
%{
#include "utility.h"
#include "sym.h"
#include "ast.h"
#include "semantic.h"

// External Declarations
extern int yylineno;
extern char *yytext;
void yyerror(const char *s);
extern int yylex();
extern File* yyin;

#define YYDEBUG 1


%}

%union{
    struct TokenAttribute* tokenAtr;
    struct BaseData* data;
}


%token <tokenAtr> IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token <tokenAtr> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token <tokenAtr> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token <tokenAtr> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token <tokenAtr> XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token <tokenAtr> LPAREN RPAREN LCURLY RCURLY LSQUARE RSQUARE
%token <tokenAtr> DOT COMMA BIT_AND STAR PLUS MINUS BIT_NOT NOT_OP DIVIDE MOD LESSER_OP GREATER_OP XOR BIT_OR QUESTION COLON SEMI_COLON ASSIGN
%token <tokenAtr> TYPEDEF EXTERN STATIC AUTO REGISTER
%token <tokenAtr> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token <tokenAtr> STRUCT UNION ENUM ELLIPSIS
%token <tokenAtr> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN UNTIL

/* %token <tokenAtr> INVALID_TOKEN UNKNOWN_TOKEN */

/* %type <data> IDENTIFIER CONSTANT SEMI_COLON
%type <data> RPAREN RCURLY RSQUARE */

%type <data> primary_expression
%type <data> postfix_expression
%type <data> argument_expression_list
%type <data> unary_expression
%type <data> unary_operator
%type <data> cast_expression
%type <data> multiplicative_expression
%type <data> additive_expression
%type <data> shift_expression
%type <data> relational_expression
%type <data> equality_expression
%type <data> and_expression
%type <data> exclusive_or_expression
%type <data> inclusive_or_expression
%type <data> logical_and_expression
%type <data> logical_or_expression
%type <data> conditional_expression
%type <data> assignment_expression
%type <data> assignment_operator
%type <data> expression
%type <data> constant_expression
%type <data> declaration
%type <data> declaration_specifiers
%type <data> init_declarator_list
%type <data> init_declarator 
%type <data> storage_class_specifier
%type <data> type_specifier
%type <data> struct_or_union_specifier
%type <data> struct_or_union
%type <data> struct_declaration_list
%type <data> struct_declaration
%type <data> specifier_qualifier_list
%type <data> struct_declarator_list
%type <data> struct_declarator
%type <data> enum_specifier
%type <data> enumerator_list
%type <data> enumerator
%type <data> type_qualifier
%type <data> declarator
%type <data> direct_declarator
%type <data> pointer
%type <data> type_qualifier_list
%type <data> parameter_type_list
%type <data> parameter_list
%type <data> parameter_declaration
%type <data> identifier_list
%type <data> type_name
%type <data> abstract_declarator
%type <data> direct_abstract_declarator
%type <data> initializer
%type <data> initializer_list
%type <data> statement
%type <data> labeled_statement
%type <data> compound_statement
%type <data> declaration_list
%type <data> statement_list
%type <data> expression_statement
%type <data> selection_statement
%type <data> iteration_statement
%type <data> jump_statement
%type <data> translation_unit
%type <data> external_declaration
%type <data> function_definition

/* %expect-rr 96 */
/* %expect 2 */

%start translation_unit
%%
//Expressions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/* Data on all expressions
🟡 std::string varName; // This will be [Constants, CompilerTempName, VariableName or EnumConstantName]
🟡 TypeExpression type; // 
🟡 VALUE_TYPE valueType;
🟡 SPACE valueSpace;
🔴 std::string whereToSendString; // possible value .rodata, stack
*/


primary_expression
    : IDENTIFIER {
        std::string idName = $1.tokenAtr->lexeme;

        // 1. Existance Check of Identifier
            GenericSymbol* symbol;
            int lookupCheck = SYMBOL_TABLE.lookup(idName, symbol);
            if(lookupCheck == -1){
                // Error - Identifier not found
                // [📍ToDo - Error Handling]
            }

        
        // 2. 🟡 type - Create a TypeExpression from symbol found
            $$.type = createTypeExpression(symbol); 

        // 3. Find type of TypeExpression (topLevelInfo)
            Type whichType = whatIsType($$.type);

        // 4. 🟡 valueType -  Check is it's Modifiable Lvalue or Rvalue
            // All possible cases - variable (primitve or struct_union or enum), functions

            // Use getValueType to find the valueType
            $$.valueType = getValueType($$.type);

        // 5. 🟡 valueSpace - Check if it's ADDRESS or VALUE
            /*Logic 
                Array (top is arrayInfo) - must be kept in ADDRESS Space
                Struct (top is BaseInfo with recordType = STRUCT_UNION ) - must be kept in ADDRESS Space
                🧠 Think if someone else need to be in ADDRESS Space
            */
            $$.valueSpace = getSpace($$.type);

        // 6. 🔖 IRCode + 🟡 varName assigned here

            /*Logic
            If valueSpace is ADDRESS we need to fetch offset
            */

            if($$.valueSpace == SPACE::VALUE_SPACE){
                // Handling Special Cases of VALUE_SPACE (compiler time constants)
                if(whichType == Type::ENUM_CONSTANTS){
                    EnumConstant* enumVar = dynamic_cast<EnumConstant *>(&symbol)
                    int enumValue = enumVar->value;
                    $$.varName = std::to_string(enumValue);
                }
                else{
                $$.varName = idName;
                }
            }
            else if($$.valueSpace == SPACE::ADDRESS_SPACE){
                std::string address = newTemp();
                std::string id_offset = idName + ".offset";
                // To Decide how should offset need to be calculated in TAC [ToDecide ❓]

                CODE_BASE.addTAC(address, "=", id_offset, NO_ARG);

                $$.varName = address;
            }
            else{
                // [📍ToDo - Error Handling]
            }

    }
    | CONSTANT {

        // 1. 🟡 type - Create a TypeExpression from symbol found
            //Logic - as it's constant will only have BaseInfo with PrimitiveType
            // We can pass the info from lexer itself [but we still need to check for size of integral-data(int,long,longlong)]
            
        // 2. 🟡 valueType - It's a Rvalue
            $$.valueType = VALUE_TYPE::RVALUE;
        
        // 3. 🟡 valueSpace - All constant will be VALUE Space
            /*Logic 
                All constants are kept in VALUE Space
            */
            $$.valueSpace = SPACE::VALUE_SPACE;

        // 4. Assign it's varName
            $$.varName = $1.tokenAtr->lexeme;
        
        // 5. 🔖 IRCode
            // Nothing to do here

    }    
    | STRING_LITERAL { // ⚡️ Advance Feature ⚡️
        std::string strValue = $1.tokenAtr->lexeme;

        // 1. 🟡 type - Create a TypeExpression from symbol found
            BaseInfo* baseInfo = new BaseInfo();
            baseInfo->baseType = "char";
            PointerInfo* ptrInfo = new PointerInfo();
            TypeExpression tempType = new TypeExpression();
            tempType.levelStack.addOnTop(baseInfo); // add the baseInfo to the type ➕
            tempType.levelStack.addOnTop(ptrInfo); // add the pointer info to the type ➕

        // 2. 🟡 valueType - It's a NM_Lvalue
            $$.valueType = VALUE_TYPE::NM_LVALUE;

        // 3. 🟡 valueSpace - string literal plays in ADDRESS_SPACE
            $$.valueSpace = SPACE::ADDRESS_SPACE;

        // 4. 🟡 varName + 🔖IRCode
            // Check if to send the string in .rodata or stack
            if($$.whereToSendString == ".rodata"){
                // Yes
                std::string lable = newLabel();
                CODE_BASE.addTAC(lable, ":", strValue, NO_ARG);
                std::string address = newTemp();
                CODE_BASE.addTAC(address, "&", lable, NO_ARG);
                $$.varName = address;
            }
            else{
                // Not Sure how to handle this [ToDecide]
            }
        
    }
    | LPAREN expression RPAREN {
        
        // 1. Pass all syn_data up ⬆️
            $$.varName = $2.varName;
            $$.type = $2.type;
            $$.valueType = $2.valueType;
            $$.valueSpace = $2.valueSpace;

        // 2. Carry the inh_data down ⬇️
            $2.whereToSendString = $$.whereToSendString; // carry the inh_data below ⬇️
    }
    ;


/* Data on postfix_expression
    Same as primary_expression
*/
postfix_expression
    : primary_expression {
        // Pass all syn_data up ⬆️
            $$.varName = $1.varName;
            $$.type = $1.type;
            $$.valueType = $1.valueType;
            $$.valueSpace = $1.valueSpace;

        // Carry the inh_data down ⬇️
            $1.whereToSendString = $$.whereToSendString; // carry the inh_data below ⬇️

        // 🔖IRCode
            // Nothing to do here   
    }
    | postfix_expression LSQUARE expression RSQUARE // ⚡️ Advance Feature ⚡️ - ArraySup
    {
        // 1. Array Subscript Expression 🅰️TypeCheck Evaluation
            /*Logic
            - Check it's a integral value (check if top is base with primitiveType(char,short,int,long,longlong))
            */
            
            // Required Type - Integral
            if(!isIntegral($3.type)){
                // Error - not integral
                // [📍ToDo - Error Handling]
            }
            std::string index;

            // Required Space - VALUE_SPACE
            if($3.valueSpace == SPACE::ADDRESS_SPACE){
                // Need a Space🚀 Change Code
                std::string value = newTemp();
                // Put a Dereferencing code
                CODE_BASE.addTAC(value, "*", $3.varName, NO_ARG);
            }
            else{
                index = $3.varName;
            }
            
        // 2. 🅰️TypeCheck on $$ + 🟡 type - Pop a Level from $1.Type
            TypeExpression temp = $1.type;
            // Check top level is arrayInfo or pointerInfo
            Type whichType = whatIsType(temp);
            if(whichType != Type::ARRAY && whichType != Type::POINTER){
                // Error - not array or pointer
                // [📍ToDo - Error Handling]
            }
            // Pop a level
            int check = popALevel(temp);
            if(check){
                // Error - not popAble [should not happen since we checked top just now]
                // [📍ToDo - Error Handling]
            }

            $$.type = temp; // pass the type to the postfix_expression ⬆️

        // 3. 🟡 varName + 🔖IRCode + 🟡 valueSpace
            // 3.1 $1.varName can be in ADDRESS_SPACE(if array) or VALUE_SPACE(if pointer)

            // 3.2 Find the width of the type-below
            int w = width(temp);

            // 3.3 Find the base address of array/pointer
            std::string baseAddress = $1.varName;

            // 3.4 Find the jump required
            std::string jump = newTemp();
            CODE_BASE.addTAC(jump, "*", w, index); // jump = w * index

            // 3.5 Find the new address
            std::string newAddress = newTemp();
            CODE_BASE.addTAC(newAddress, "+", baseAddress, jump); // newAddress = baseAddress + jump

            // 3.6 Assign the new address to the varName 
                // We used a array[index] so it will be in ADDRESS_SPACE & will need a Space🚀 Change Code if Value is needed
                $$.varName = newAddress;
                $$.valueSpace = SPACE::ADDRESS_SPACE; // 👍👍 IMP_LOGIC 👍👍

        // 4. 🟡 valueType
            // This will be decided by type of $$.type

            $$.valueType = getValueType($$.type);

        // 5. Carry the inh_data down ⬇️
            $1.whereToSendString = $$.whereToSendString; // carry the inh_data below ⬇️

        
        
        // #### -----_RAMAN's LOGIC_----------------
            TypeExpression temp = $1.type;
            int check = popALevel(temp);
            if(check){
                // Error - not popAble 
            }

            $$.type = temp; // pass the type to the postfix_expression ⬆️
            $$.ptrName = $1.ptrName;
            
            std::string index = newTemp();

            //[📍ToThink Deep]

            // // IRCode Logic [ToThink 🧠]
            int w = width(temp);
            std::string expName = $3.varName;
            CODE_BASE.addTAC(index, "*", w, expName);
            std::string newName = newTemp();
            CODE_BASE.addTAC(newName, "+", $1.varName, index);
            $$.varName = newName; // pass the varName to the postfix_expression ⬆️
    }
    | postfix_expression LPAREN RPAREN {
        TypeExpression temp = $1.type;
        // 1. 🅰️TypeCheck of $1 is a function or function pointer
            Type whichType = whatIsType(temp);
            ParameterInfo* paramInfo;
            if(whichType == Type::FUNCTION){ // Is a function
                // Okay
                paramInfo = temp.levelStack.top();
            }
            else if(whichType == Type::POINTER){ // Is a function pointer
                // Okay BUT the below level should be function
                TypeExpression temp2 = temp;
                int check = popALevel(temp2);
                if(check){
                    // Error - not popAble [should not happen since we checked top just now]
                    // [📍ToDo - Error Handling]
                }
                Type whichType2 = whatIsType(temp2);
                if(whichType2 != Type::FUNCTION){
                    // Error - not function
                    // [📍ToDo - Error Handling]
                }
                else{
                    // Okay
                    paramInfo = temp2.levelStack.top();
                }
            }
            else{ // Neither function nor function pointer
                // Error - not function or function pointer
                // [📍ToDo - Error Handling]
            }
        
        // 2. We already have address of function call - which is mostLikely a label
            std::string functionAddress = $1.varName;

        // 3. Handling Arguments + 🅰️TypeCheck signature
            // Check if paramInfo is empty
            if(paramInfo == nullptr){
                // Error - no parameterInfo
                // [📍ToDo - Error Handling]
            }

            int argCount = 0;
            argCount = paramInfo->paramsType.size();
            if(argCount != 0){
                // Error - no arguments
                // [📍ToDo - Error Handling]
            }

            //Okay
        
        // 4. 🟡 varName + 🔖IRCode
            // We need to create a new label for the function call
            std::string returnValue = newTemp();
            CODE_BASE.addTAC(returnValue, "CALL", functionAddress, "0");

            // Assign the label to the varName
            $$.varName = returnValue;

        // 5. 🟡 type of $$
            // WE pop the level or arguments in TypeExpression
            TypeExpression returnExpr = $1.type;

            if(topIsPointer(returnExpr)){ // Function Pointer pop the pointer
                if(popALevel(returnExpr)){
                    // Error - not popAble [should not happen since we checked top just now]
                    // [📍ToDo - Error Handling]
                }
            }
            if(topIsFunction(returnExpr)){
                // Okay
                if(popALevel(returnExpr)){ // Function pop the argumentsList
                    // Error - not popAble [should not happen since we checked top just now]
                    // [📍ToDo - Error Handling]
                }
            }

            $$.type = returnExpr; // pass the type to the postfix_expression ⬆️
        
        // 6. 🟡 valueType
            // This will be decided by type of $$.type
            $$.valueType = getValueType($$.type);

        // 7. 🟡 valueSpace
            /*Logic
                A function can never return array which deal with ADDRESS_SPACE
                BUT it can return a Struct/Union which can be in ADDRESS_SPACE
            */
            $$.valueSpace = getSpace($$.type);
        
        // 8. Carry the inh_data down ⬇️
            $1.whereToSendString = $$.whereToSendString; // carry the inh_data below ⬇️
    }
    | postfix_expression LPAREN argument_expression_list LPAREN {
        // 1. 🅰️TypeCheck of $1 is a function or function pointer + Parameter
            Type whichType = whatIsType(temp);
            ParameterInfo* paramInfo;
            if(whichType == Type::FUNCTION){ // Is a function
                // Okay
                paramInfo = temp.levelStack.top();
            }
            else if(whichType == Type::POINTER){ // Is a function pointer
                // Okay BUT the below level should be function
                TypeExpression temp2 = temp;
                int check = popALevel(temp2);
                if(check){
                    // Error - not popAble [should not happen since we checked top just now]
                    // [📍ToDo - Error Handling]
                }
                Type whichType2 = whatIsType(temp2);
                if(whichType2 != Type::FUNCTION){
                    // Error - not function
                    // [📍ToDo - Error Handling]
                }
                else{
                    // Okay
                    paramInfo = temp2.levelStack.top();
                }
            }
            else{ // Neither function nor function pointer
                // Error - not function or function pointer
                // [📍ToDo - Error Handling]
            }
        
        // 2. We already have address of function call - which is mostLikely a label
            std::string functionAddress = $1.varName;

        // 3. Handling Arguments + 🅰️TypeCheck signature
            // 3.1 Find functionSign & givenArguments
            std::vector<TypeExpression> functionSign = paramInfo->paramsType;
            std::vector<TypeExpression> argList = $3.typeVector;
        
            // 3.2 Check if functionSign and givenArguments are same
            bool areSame = true;
            if(functionSign.size() != argList.size()){
                // Error - not same
                // [📍ToDo - Error Handling]
            }
            for(int i=0; i<functionSign.size(); i++){
                if(checkEquivalance(functionSign[i], argList[i]) != OKAY){
                    // Error - not same
                    // [📍ToDo - Error Handling]

                    // THINK - TYPECASTING🆎
                }
            }

            int argCount = functionSign.size();

            //Okay

        // 4. 🟡 varName + 🔖IRCode
            std::string argCountStr = std::to_string(argCount);

            // 4.1 Add TAC for parameter
            for(int i=0; i<argCount; i++){
                std::string paramName = $3.varNameVector[i];
                CODE_BASE.addTAC(NO_ARG, "param", paramName, NO_ARG);
            }

            // 4.2 Add TAC for function call 
            std::string returnValue = newTemp(); // need a new temp to pass returnValue
            CODE_BASE.addTAC(returnValue, "call", functionAddress, argCountStr);

            // Assign the label to the varName
            $$.varName = returnValue;

        // 5. 🟡 type of $$
            // WE pop the level or arguments in TypeExpression
            TypeExpression returnExpr = $1.type;

            if(topIsPointer(returnExpr)){ // Function Pointer pop the pointer
                if(popALevel(returnExpr)){
                    // Error - not popAble [should not happen since we checked top just now]
                    // [📍ToDo - Error Handling]
                }
            }
            if(topIsFunction(returnExpr)){
                // Okay
                if(popALevel(returnExpr)){ // Function pop the argumentsList
                    // Error - not popAble [should not happen since we checked top just now]
                    // [📍ToDo - Error Handling]
                }
            }

            $$.type = returnExpr; // pass the type to the postfix_expression ⬆️
        
        // 6. 🟡 valueType of $$
            // This will be decided by type of $$.type
            $$.valueType = getValueType($$.type);

        // 7. 🟡 valueSpace of $$
            /*Logic
                A function can never return array which deal with ADDRESS_SPACE
                BUT it can return a Struct/Union which can be in ADDRESS_SPACE
            */
            $$.valueSpace = getSpace($$.type);
        
        // 8. Carry the inh_data down ⬇️
            $1.whereToSendString = $$.whereToSendString; // carry the inh_data below ⬇️
    
    }
    | postfix_expression DOT IDENTIFIER{
        // member access (like in struct)
    }
    | postfix_expression PTR_OP IDENTIFIER{
        // -> access
    }
    | postfix_expression INC_OP{
        // ++ operator (constant and variable not function or string literal)
        //if type top level is array => error 
        //if type top level is ptr => pop a level , find it's width and increment as per width
        // if type top level is base level => increment by 1 see type of + operator

    }
    | postfix_expression DEC_OP{
        // ++ operator (constant and variable not function or string literal)
        //if type top level is array => error 
        //if type top level is ptr => pop a level , find it's width and increment as per width
        // if type top level is base level => increment by 1 see type of + operator
    }
    ;


/*Data on argument_expression_list

🟡 std::vector<std::string> varNameVector; // This will be a vector of variable name
🟡 std::vector<TypeExpression> typeVector; // This will be a vector of TypeExpression
*/
argument_expression_list
    : assignment_expression
    | argument_expression_list COMMA assignment_expression
    ;

unary_expression
    : postfix_expression {

    }
    | INC_OP unary_expression {
        //Work on this
        //modifiable lvalue(m-lval) => basic types, pointer, struct object element with m-lval 
        // Do not work on this
        // rvalue and non-modofiable lvalue = enum const, function name, array name, struct object
        
        // 1. 🅰️TypeCheck of $2 unary_expression
            Type whichType = whatIsType($2.type);
            // Allowed - VARIABLE, ARRAY❌,  POINTER, ENUM_CONSTANT❌, FUNCTION❌, STRUCT_UNION❌, ENUM
            // And must be M_LVALUE
            if(whichType == Type::ARRAY || whichType == Type::ENUM_CONSTANT || whichType == Type::FUNCTION || whichType == Type::STRUCT_UNION){
                // Error - not modifiable lvalue
                // [📍ToDo - Error Handling]
            }
            else{
                if($2.valueType != VALUE_TYPE::M_LVALUE){
                    // Error - not modifiable lvalue
                    // [📍ToDo - Error Handling]
                }
            }
        
        // 2. 🟡 type + 🟡 valueType
            $$.type = $2.type; // pass the type to the unary_expression ⬆️
            $$.valueType = VALUE::NM_LVALUE; // change the valueType to NM_LVALUE
            
        // 3. 🔖IRCode
            // We need to create a new label for the function call
            std::string resName = "";

            // IncBy Eval
            TypeExpression belowType = $2.type;
            int check = popALevel(belowType);
            if(check){
                // Error - not popAble [should not happen since we checked top just now]
                // [📍ToDo - Error Handling]
            }
            int incBy = width(belowType);
            std::string incByStr = std::to_string(incBy);

            SPACE reqSpace = getSpace($2.type);
            SPACE currSpace = $2.valueSpace;
            if(reqSpace != currSpace){
                // SPACE🚀 Change Code

                // Load it
                std::string value = newTemp();
                CODE_BASE.addTAC(value, RIGHT_STAR, $2.varName, NO_ARG);

                // Increment it
                std::string incValue = newTemp();
                
                CODE_BASE.addTAC(incValue, "+", value, incByStr);
                resName = incValue;

                // Store it
                CODE_BASE.addTAC($2.varName, LEFT_STAR, incValue, NO_ARG);
            }
            else{
                // No need of space change

                // Direct Increment & Store it
                CODE_BASE.addTAC($2.varName, "+", $2.varName, incByStr);
                resName = $2.varName;
            }
        
        // 4.  🟡 varName + 🟡 valueSpace   
            $$.varName = resName;
            $$.valueSpace = SPACE::VALUE_SPACE;

    }
    | DEC_OP unary_expression {
        
        // 1. 🅰️TypeCheck of $2 unary_expression
            Type whichType = whatIsType($2.type);
            // Allowed - VARIABLE, ARRAY❌,  POINTER, ENUM_CONSTANT❌, FUNCTION❌, STRUCT_UNION❌, ENUM
            // And must be M_LVALUE
            if(whichType == Type::ARRAY || whichType == Type::ENUM_CONSTANT || whichType == Type::FUNCTION || whichType == Type::STRUCT_UNION){
                // Error - not modifiable lvalue
                // [📍ToDo - Error Handling]
            }
            else{
                if($2.valueType != VALUE_TYPE::M_LVALUE){
                    // Error - not modifiable lvalue
                    // [📍ToDo - Error Handling]
                }
            }
        
        // 2. 🟡 type + 🟡 valueType
            $$.type = $2.type; // pass the type to the unary_expression ⬆️
            $$.valueType = VALUE::NM_LVALUE; // change the valueType to NM_LVALUE
            
        // 3. 🔖IRCode
            // We need to create a new label for the function call
            std::string resName = "";

            // IncBy Eval
            TypeExpression belowType = $2.type;
            int check = popALevel(belowType);
            if(check){
                // Error - not popAble [should not happen since we checked top just now]
                // [📍ToDo - Error Handling]
            }
            int incBy = width(belowType);
            std::string incByStr = std::to_string(incBy);

            SPACE reqSpace = getSpace($2.type);
            SPACE currSpace = $2.valueSpace;
            if(reqSpace != currSpace){
                // SPACE🚀 Change Code

                // Load it
                std::string value = newTemp();
                CODE_BASE.addTAC(value, RIGHT_STAR, $2.varName, NO_ARG);

                // Increment it
                std::string incValue = newTemp();
                
                CODE_BASE.addTAC(incValue, "-", value, incByStr);
                resName = incValue;

                // Store it
                CODE_BASE.addTAC($2.varName, LEFT_STAR, incValue, NO_ARG);
            }
            else{
                // No need of space change

                // Direct Increment & Store it
                CODE_BASE.addTAC($2.varName, "+", $2.varName, incByStr);
                resName = $2.varName;
            }
        
        // 4.  🟡 varName + 🟡 valueSpace   
            $$.varName = resName;
            $$.valueSpace = SPACE::VALUE_SPACE;
    }

    | unary_operator cast_expression {
        // values to pass up 
        std::string resName;
        SPACE resSpace;
        TypeExpression resType;
        VALUE_TYPE resValueType;
        // for "&" operator 
        if($1.op == "&"){
            // 1. 🅰️TypeCheck of $2 unary_expression
                // This is about finding address of operand
                // Allowed - M_LVALUE, NM_LVALUE but not RVALUE
                if($2.valueType == VALUE_TYPE::RVALUE){
                    // Error - not modifiable lvalue
                    // [📍ToDo - Error Handling]
                }

                //Okay

            // 2. 🔖IRCode
                // SPACE🚀 Change Sensitive
                if($2.valueSpace == SPACE::ADDRESS_SPACE){
                    std::string newName = newTemp();
                    CODE_BASE(newName,"=",$2.varName,NO_ARG);
                    resName = newName;
                }
                else{
                    std::string newName = newTemp();
                    CODE_BASE(newName,"&",$2.varName,NO_ARG);
                    resName = newName;
                }
            

            // 3. 🟡 type 
                resType = $2.type;
                PointerInfo* ptr = new PointerInfo();
                resType.levelStack.addOnTop(ptr);

                resSpace = SPACE::VALUE_SPACE;
        }
        // for "*" operator
        else if($1.op == "*"){
            Type whichType = whatIsType($2.type)

            if(whichType == Type::FUNCTION){

            }
            else if(whichType == Type::ARRAY || whichType == Type::POINTER){

            }
        }
        
        
        
        
        
        
        
        // END. Final Assignment
            $$.varName = resName;
            $$.type = resType;
            $$.valueSpace = resSpace;
            $$.valueType = resValueType;

    }
    | SIZEOF unary_expression {
        // 1. 🅰️TypeCheck of $2 unary_expression
    }
    | SIZEOF LPAREN type_name RPAREN {
        // 1. 🅰️TypeCheck of $2 type_name
            // NOTE - { }

        // 2. 
    }
    ;

// Data on unary_operator - std::string op
unary_operator
    : BIT_AND { $$.op = "&" }
    | STAR    { $$.op = "*" }
    | PLUS    { $$.op = "+" }
    | MINUS   { $$.op = "-" }
    | BIT_NOT { $$.op = "~" }
    | NOT_OP  { $$.op = "!" }
    ;

cast_expression
    : unary_expression
    | LPAREN type_name RPAREN cast_expression
    ;

multiplicative_expression
    : cast_expression
    | multiplicative_expression STAR cast_expression
    | multiplicative_expression DIVIDE cast_expression
    | multiplicative_expression MOD cast_expression
    ;

additive_expression
    : multiplicative_expression
    | additive_expression PLUS multiplicative_expression
    | additive_expression MINUS multiplicative_expression
    ;

shift_expression
    : additive_expression
    | shift_expression LEFT_OP additive_expression
    | shift_expression RIGHT_OP additive_expression
    ;

relational_expression
    : shift_expression
    | relational_expression LESSER_OP shift_expression
    | relational_expression GREATER_OP shift_expression
    | relational_expression LE_OP shift_expression
    | relational_expression GE_OP shift_expression
    ;

equality_expression
    : relational_expression
    | equality_expression EQ_OP relational_expression
    | equality_expression NE_OP relational_expression
    ;

and_expression
    : equality_expression
    | and_expression BIT_AND equality_expression
    ;

exclusive_or_expression
    : and_expression
    | exclusive_or_expression XOR and_expression
    ;

inclusive_or_expression
    : exclusive_or_expression
    | inclusive_or_expression BIT_OR exclusive_or_expression
    ;

logical_and_expression
    : inclusive_or_expression
    | logical_and_expression AND_OP inclusive_or_expression
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR_OP logical_and_expression
    ;

conditional_expression
    : logical_or_expression
    | logical_or_expression QUESTION expression COLON conditional_expression
    ;

assignment_expression
    : conditional_expression
    | unary_expression assignment_operator assignment_expression
    ;

assignment_operator
    : ASSIGN
    | MUL_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    | ADD_ASSIGN
    | SUB_ASSIGN
    | LEFT_ASSIGN
    | RIGHT_ASSIGN
    | AND_ASSIGN
    | XOR_ASSIGN
    | OR_ASSIGN
    ;

expression
    : assignment_expression
    | expression COMMA assignment_expression
    ;

constant_expression
    : conditional_expression
    ;

//========================== End of Expression Logic ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//========================== Declaration Logic ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/* Data on declaration

*/

/* Data from/to declaration_specifiers
    ⬆️ From - std::vector<std::string> valueVector; // This will be a vector of TypeExpression
*/

/* Data from/to init_declarator_list
    ⬇️ To - TypeExpression inh_type; // This will be a TypeExpression
    ⬇️ To - StorageClass inh_storageClass ; // This will be a StorageClass
*/

/* What to Do
    std::string ProcessDecSpecifier(std::vector<std::string> valueVector, BaseInfo *& baseInfo, StorageClass &storageClass)
        Take all std:vector<std::string> valueVector and create a BaseInfo* 
            - Check if combination of primitive possible
            - Check if typeQualifier and storageQualifier are under rule

*/
declaration
    : declaration_specifiers SEMI_COLON {
        BaseInfo* baseInfo = new BaseInfo();
        StorageClass storageClass;
        std::string check = ProcessDecSecifier($1.valueVector,baseInfo,storageClass);
        if(check!="OK"){
            // [Error Handling]
        }

        // No more processing since we have SEMI_COLOM
    }
    | declaration_specifiers init_declarator_list SEMI_COLON {
        BaseInfo* baseInfo = new BaseInfo();
        StorageClass storageClass;
        std::string check = ProcessDecSecifier($1.valueVector,baseInfo,storageClass);
        if(check!="OK"){
            // [Error Handling]
        }

        // We create a TypeExpression now
        TypeExpression tempType = new TypeExpression();
        tempType.dtype.levels.add(baseInfo); // add the baseInfo to the type ➕
        // tempType.dtype.levels is a stack of LevelInfo*

        $2.inh_type = tempType; // pass the type to the init_declarator_list ⬇️ 
        $2.inh_storageClass = storageClass; // pass the storage class to the init_declarator_list ⬇️

        // [📍ToDo - Decide where to do INITIALIZATION]
    }
    ;





/* Data on declaration_specifiers ✅
🔴 std::vector<std::string> valueVector; // This will be a vector of TypeExpression
*/
declaration_specifiers 
    : storage_class_specifier { 
        // Last Production 🚦🛑
        $$.vector = new vector<std::string>();
        $$.vector.push_back($1.value); // push the storage_class_specifier ➕
    }
    | storage_class_specifier declaration_specifiers {
        $$.vector = $2.vector; // copy the vector to pass up ⬆️
        $$.vector.push_back($1.value); // push the storage_class_specifier ➕
    }
    | type_specifier {
        // Last Production 🚦🛑
        $$.vector = new vector<std::string>();
        $$.vector.push_back($1.value); // push the type_specifier ➕
    }
    | type_specifier declaration_specifiers {
        $$.vector = $2.vector; // copy the vector to pass up ⬆️
        $$.vector.push_back($1.value); // push the type_specifier ➕
    }
    | type_qualifier  {
        // Last Production 🚦🛑
        $$.vector = new vector<std::string>();
        $$.vector.push_back($1.value); // push the type_qualifier ➕
    }
    | type_qualifier declaration_specifiers {
        $$.vector = $2.vector; // copy the vector to pass up ⬆️
        $$.vector.push_back($1.value); // push the type_qualifier ➕
    }
    ;


/* Data on init_declarator_list ✅
🔴 TypeExpression inh_type; // This will be a TypeExpression
🔴 StorageClass inh_storageClass; 
*/
init_declarator_list
    : init_declarator {
        // Last Production 🚦🛑
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
        $1.inh_storageClass = $$.inh_storageClass; // carry the inh_data below ⬇️
    }
    | init_declarator_list COMMA init_declarator {
        // Pass inh_data in both down ⬇️ ⬇️ [Since base info is same] {eg - int a,*b,(*c)[5]; - all get same base int}
        $1.inh_type = $2.inh_type; // carry the inh_data below ⬇️
        $1.inh_storageClass = $$.inh_storageClass; // carry the inh_data below ⬇️
        $2.inh_type = $1.inh_type; // carry the inh_data below ⬇️
        $2.inh_storageClass = $$.inh_storageClass; // carry the inh_data below ⬇️
    }
    ;


/* Data on init_declarator ✅
🔴 TypeExpression inh_type; // This will be a TypeExpression
🔴 StorageClass inh_storageClass;
*/
/* Data from/to declarator 
    ⬇️ to - 🔴 TypeExpression inh_type; [ This goes down keep collecting data on way as goes down ]
    ⬆️ from - 🟡 std::string varName; // This will be a string of variable name
    ⬆️ from - 🟡 TypeExpression type; // This will be a TypeExpression [after going to bottom and retrieving all information]
*/
init_declarator
    : declarator {
        // 0. Carry inh_data down
            $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
            StorageClass storageClass = $$.inh_storageClass; // no need to pass down
            // no need to pass the inh_storageClass anyfuther as symbol table entry will be created

        // 1. Reeive the syn_data from declarator
            TypeExpression tempType = $1.type;
            std::string symName = $1.varName;

        // 2.  Create Symbol (Variable or Function)
            Type whichType = whatIsType(tempType);
            GenericSymbol* symbol;
            if(whichType == Type::FUNCTION){
                // Function
                Function* func = new Function();
                func->symbolName = symName;
                func->type = tempType;
                func->isDefined = false; // not defined yet

                if(storageClass == StorageClass::STATIC){
                    // Function can only be accessed in the same file 
                    // 😵‍💫 Too Advance 😵‍💫
                }
                symbol = func;
            }
            else{
                // Variable
                Variable* var = new Variable();
                var->symbolName = symName;
                var->type = tempType;
                var->storageClass = storageClass;
                // [ 📍ToDo fill offset ]

                symbol = var;
            }


        // 3. Add Symbol to SYM_TABLE
            int check = SYM_TABLE.insertRecord($1.varName, symbol);
            if(check == -1){
                // Already Present in Current Scope
                // [Error Handling]
            }

        // Done - NO 🔖IRCode
        
    }
    | declarator ASSIGN initializer {
        // 0. Carry inh_data down 
            $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
            StorageClass storageClass = $$.inh_storageClass; // no need to pass down

        // 1. Reeive the syn_data from declarator
            TypeExpression tempType = $1.type;
            std::string symName = $1.varName;

        // 2.  Create Symbol (Variable or Function)
            Type whichType = whatIsType(tempType);
            GenericSymbol* symbol;
            if(whichType == Type::FUNCTION){
                // Should NOT HAPPEDN with INITIALIZER
                // [Error Handling - Function with Initializer]
            }
            else{
                // Variable
                Variable* var = new Variable();
                var->symbolName = symName;
                var->type = tempType;
                var->storageClass = storageClass;
                // [ 📍ToDo fill offset ]

                // [📍ToDo - Add Initializer to symbol] 🤯 Advance Logic [🧠ToDecide]
                    // Also if const - need a compile time value
                symbol = var;
            }
        
        // 3. Add Symbol to SYM_TABLE
            int check = SYM_TABLE.insertRecord($1.varName, symbol);
            if(check == -1){
                // Already Present in Current Scope
                // [Error Handling]
            }

        // Done - NO 🔖IRCode
    }
    ;



/* Data on storage_class_specifier ✅
🟡 std::string value; // This will be a string of type
*/
storage_class_specifier
    : TYPEDEF  {/* not supported*/}
    | EXTERN   { $$.value = $1.tokenAtr->lexeme; }
    | STATIC   { $$.value = $1.tokenAtr->lexeme; }
    | AUTO     { $$.value = $1.tokenAtr->lexeme; }
    | REGISTER { $$.value = $1.tokenAtr->lexeme; }
    ;

/* Data on type_specifier ☑️
🟡 std::string value; // This will be a string of type
*/ 
type_specifier
    : VOID     { $$.value = $1.tokenAtr->lexeme; }
    | CHAR     { $$.value = $1.tokenAtr->lexeme; }
    | SHORT    { $$.value = $1.tokenAtr->lexeme; }
    | INT      { $$.value = $1.tokenAtr->lexeme; }
    | LONG     { $$.value = $1.tokenAtr->lexeme; }
    | FLOAT    { $$.value = $1.tokenAtr->lexeme; }
    | DOUBLE   { $$.value = $1.tokenAtr->lexeme; }
    | SIGNED   { $$.value = $1.tokenAtr->lexeme; }
    | UNSIGNED { $$.value = $1.tokenAtr->lexeme; }
    | struct_or_union_specifier {
        $$.value = $1.value; // This will be a string of type ✅
    }
    | enum_specifier {
        $$.value = $1.value; // This will be a string of type ✅
    }
    | TYPE_NAME {
        // [Find what is this doing? 🔍 ]
    } 
    ;

/* Data on struct_or_union_specifier ✅
🟡 std::string value ; // This will be a string of type
*/
struct_or_union_specifier
    : struct_or_union IDENTIFIER LCURLY struct_declaration_list RCURLY {
        // This is point of adding UserDType to Symbol Table (named)

        // 1. Create a UserDType Unit 
            UserDType* userDType = new UserDType();
            RecordType recordType;
            if($1.value == "struct"){
                recordType = RecordType::STRUCT;
            }
            else if($1.value == "union"){
                recordType = RecordType::UNION;
            }
            else{
                // Error - not struct or union [Syntax Checked]
            }
            userDType->recordType = recordType;
            userDType->members = $4.members; // add the members to the userDType ➕

        // 2. Add it to symbol table
            std::string recordID = $2.tokenAtr->lexeme;
            int check = SYM_TABLE.insertRecord(recordID, userDType);
            if(check == -1){
                // Already Present in Current Scope
                // [Error Handling]
            }

        // 3. Pass a string up
            std::string scope = std::to_string(SYM_TABLE.scopeNo);
            std::string typeSpecifier = $1.value + " " + recordID + " " + scope;

            $$.value = typeSpecifier; // Pass the type up ⬆️
    }
    | struct_or_union LCURLY struct_declaration_list RCURLY {
        // This is point of adding UserDType to Symbol Table (unnamed)
        
        // 1. Create a UserDType Unit
            UserDType* userDType = new UserDType();
            RecordType recordType;
            if($1.value == "struct"){
                recordType = RecordType::STRUCT;
            }
            else if($1.value == "union"){
                recordType = RecordType::UNION;
            }
            else{
                // Error - not struct or union [Syntax Checked]
            }
            userDType->recordType = recordType;
            userDType->members = $3.members; // add the members to the userDType ➕
        // 2. Add it to symbol table
            std::string recordID = newRecordName();
            int check = SYM_TABLE.insertRecord(recordID, userDType);
            if(check == -1){
                // Already Present in Current Scope
                // [Error Handling]
            }

        // 3. Pass a string up
            std::string scope = std::to_string(SYM_TABLE.scopeNo);
            std::string typeSpecifier = $1.value + " " + recordID + " " + scope;

            $$.value = typeSpecifier; // Pass the type up ⬆️

    }
    | struct_or_union IDENTIFIER {
        // This point we check if such a type is there in symbol table [else Error]

        // 1. Check if UserDType is there in symbol table
            std::string recordID = $2.tokenAtr->lexeme;
            GenericSymbol* userDType;
            int check = SYM_TABLE.lookupRecord(recordID, userDType);
            if(check == -1){
                // Such a type is not there in symbol table
                // [Error Handling]
            }
            RecordType neededType = ($1.value == "struct") ? RecordType::STRUCT : RecordType::UNION;
            RecordType foundType = userDType->recordType;
            if(foundType != neededType){
                // Error - not same type 
                // [Error Handling]
            }
            
            // Okay

        // 2. Pass a string up
            std::string scope = std::to_string(userDType->scopeNo); // Scope from symbol table
            std::string typeSpecifier = $1.value + " " + recordID + " " + scope;

    }
    ;

/* Data on struct_or_union_specifier ✅
🟡 std::string value ; // This will be a string of type
*/
struct_or_union
    : STRUCT { $$.value = $1.tokenAtr->lexeme; }
    | UNION  { $$.value = $1.tokenAtr->lexeme; }
    ;


/* Data on struct_declaration_list ✅
🟡 std::map<std::string,TypeExpression> members;
*/
struct_declaration_list 
    : struct_declaration {
        // Last Production 🚦 
        $$.members = $1.members; // pass the members by adding ➕
    }
    | struct_declaration_list struct_declaration {
        // Copy the members to pass up ⬆️
        $$.members = $1.members; // copy the map to pass up ⬆️

        // Add the members of $2 to $$
        for(auto it : $2.members){
            // Check if varName is already present
            if($$.members.find(it.first) != $$.members.end()){
                // Error - duplicate variable name
                // [📍ToDo - Error Handling]
            }
            $$.members[it.first] = it.second; // add the <varName,type> to the map ➕
        }
    }
    ;



/* Data on struct_declaration ✅
🟡 std::map<std::string,TypeExpression> members;
*/
struct_declaration
    : specifier_qualifier_list struct_declarator_list SEMI_COLON {
        BaseInfo* baseInfo = new BaseInfo();
        StorageClass storageClass;// NOT ALLOWED ❌ [Will be syntax checked]
        std::string check = ProcessDecSecifier($1.valueVector,baseInfo,storageClass);
        if(check!="OK"){
            // [Error Handling]
        }

        // We create a TypeExpression now
        TypeExpression tempType = new TypeExpression();
        tempType.dtype.levels.add(baseInfo); // add the baseInfo to the type ➕

        $2.inh_type = tempType; // pass the type to the struct_declarator_list ⬇️

        // Pass the members to the struct_declaration_list ⬆️
        $$.members = $2.members;
    }
    ;


/* Data on specifier_qualifier_list ✅
🟡 std::vector<std::string> valueVector; // This will be a vector of TypeQualifier
*/
specifier_qualifier_list
    : type_specifier specifier_qualifier_list {
        $$.valueVector = $2.valueVector; // copy the vector to pass up ⬆️
        $$.valueVector.push_back($1.value); // push the type_specifier ➕
    }
    | type_specifier {
        // Last Production 🚦🛑
        $$.valueVector = new vector<std::string>();
        $$.valueVector.push_back($1.value); // push the type_specifier ➕
    }
    | type_qualifier specifier_qualifier_list {
        $$.valueVector = $2.valueVector; // copy the vector to pass up ⬆️
        $$.valueVector.push_back($1.value); // push the type_qualifier ➕
    }
    | type_qualifier {
        // Last Production 🚦🛑
        $$.valueVector = new vector<std::string>();
        $$.valueVector.push_back($1.value); // push the type_qualifier ➕
    }
    ;

/* Data on struct_declarator_list ✅
🟡 std::map<std::string,TypeExpression type> members
🔴 TypeExpression inh_type; // This will be a TypeExpression
*/
struct_declarator_list 
    : struct_declarator {
        // Carry the inh_data down ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // Last Production 🚦 
        std::map<std::string,TypeExpression> members = new std::map<std::string,TypeExpression>();

        // Check if varName is already present
        if(members.find($1.varName) != members.end()){
            // Error - duplicate variable name
            // [📍ToDo - Error Handling]
        }
        members[$1.varName] = $1.type; // add the <varName,type> to the map ➕
        $$.members = members; // pass the map to the struct_declarator_list ⬆️
    }
    | struct_declarator_list COMMA struct_declarator {
        // Carry the inh_data down ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // Check if varName is already present
        if($1.members.find($2.varName) != $1.members.end()){
            // Error - duplicate variable name
            // [📍ToDo - Error Handling]
        }
        $$.members = $1.members; // copy the map to pass up ⬆️
        $$.members[$2.varName] = $2.type; // add the <varName,type> to the map ➕
    }
    ;

/* Data on struct_declarator ✅
🟡 std::string varName; // This will be a string of variable name
🟡 TypeExpression type; // This will be a TypeExpression
🔴 TypeExpression inh_type; // This will be a TypeExpression
*/
struct_declarator
    : declarator {
        // Carry the inh_data down ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // Pass all syn_data up ⬆️
        $$.varName = $1.varName; // pass the varName up ⬆️
        $$.type = $1.type; // pass the type up ⬆️
        // These <varName, type> are used to create a UserDType member entry
    }
    | COLON constant_expression { // ⚡️ Advance Feature ⚡️ - BitField
        // Last Production 🚦🛑
        $$.varName = ""; // pass the varName up ⬆️
        $$.type = $$.inh_type; // pass the type up ⬆️
        // These <varName, type> are used to create a UserDType member entry
    }
    | declarator COLON constant_expression { // ⚡️ Advance Feature ⚡️ - BitField
        // Last Production 🚦🛑
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // Pass all syn_data up ⬆️
        $$.varName = $1.varName; // pass the varName up ⬆️
        $$.type = $1.type; // pass the type up ⬆️
        // These <varName, type> are used to create a UserDType member entry
    }
    ;

/* Data on enum_specifier ✅
🟡
*/
enum_specifier
    : ENUM LCURLY enumerator_list RCURLY {
        // 1. Create a UserDType Unit
            UserDType* userDType = new UserDType();
            userDType->recordType = RecordType::ENUM;
            userDType->members = new std::map<std::string,TypeExpression>(); // empty map
            // Empty no members in enum

        // 2. Add it to symbol table
            std::string recordID = newRecordName();
            int check = SYM_TABLE.insertRecord(recordID, userDType);
            if(check == -1){
                // Already Present in Current Scope
                // [Error Handling]
            }

        // 3. Pass a typeSpecifier up
            std::string scope = std::to_string(SYM_TABLE.scopeNo);
            std::string typeSpecifier = "enum " + recordID + " " + scope;

            $$.value = typeSpecifier; // Pass the type up ⬆️
    }
    | ENUM IDENTIFIER LCURLY enumerator_list RCURLY {
        // 1. Create a UserDType Unit
            UserDType* userDType = new UserDType();
            userDType->recordType = RecordType::ENUM;
            userDType->members = new std::map<std::string,TypeExpression>(); // empty map
            // Empty no members in enum

        // 2. Add it to symbol table
            std::string recordID = $2.tokenAtr->lexeme;
            int check = SYM_TABLE.insertRecord(recordID, userDType);
            if(check == -1){
                // Already Present in Current Scope
                // [Error Handling]
            }

        // 3. Pass a typeSpecifier up
            std::string scope = std::to_string(SYM_TABLE.scopeNo);
            std::string typeSpecifier = "enum " + recordID + " " + scope;

            $$.value = typeSpecifier; // Pass the type up ⬆️
    }
    | ENUM IDENTIFIER {
        // 1. Check if such a ENUM UserDType exists
            std::string recordID = $2.tokenAtr->lexeme;
            GenericSymbol* userDType;
            int check = SYM_TABLE.lookupRecord(recordID, userDType);
            if(check == -1){
                // Such a type is not there in symbol table
                // [Error Handling]
            }
            RecordType neededType = RecordType::ENUM;
            RecordType foundType = userDType->recordType;
            if(foundType != neededType){
                // Error - not same type 
                // [Error Handling]
            }
            
            // Okay

        // 2. Pass a typeSpecifier up
            std::string scope = std::to_string(userDType->scopeNo); // Scope from symbol table
            std::string typeSpecifier = "enum " + recordID + " " + scope;

            $$.value = typeSpecifier; // Pass the type up ⬆️
    }
    ;

/* Data on enumerator_list ✅
int lastInitValue;

*/
enumerator_list
    : enumerator {
        // Last Production 🚦🛑
        int lastInitValue = 0; // lastInitValue is 0 by default
        // 1. Check if the enumerator is explicitly initialized
            if($1.isInitialized){
                lastInitValue = $1.initValue; 
            }
            else{
                // Okay
                lastInitValue = 0; // since it's last production
            }

        // 2. Pass syn_data up ⬆️
            $$.lastInitValue = lastInitValue; // pass the lastInitValue up ⬆️

        // 3. Add a EnumConstant to the symbol table
            EnumConstant* enumConstant = new EnumConstant();
            enumConstant->value = lastInitValue;

            int check = SYM_TABLE.insert($1.varName, enumConstant);
            if(check == -1){
                // Already Present in Current Scope
                // [Error Handling]
            }
            // Okay

    }
    | enumerator_list COMMA enumerator {
        // 1. Check if the enumerator is explicitly initialized
            int lastInitValue = $1.lastInitValue; // get the lastInitValue from the enumerator_list
            if($3.isInitialized){
                lastInitValue = $3.initValue; 
            }
            else{
                // Okay
                lastInitValue++; // since it's last production
            }

        // 2. Pass syn_data up ⬆️
            $$.lastInitValue = lastInitValue; // pass the lastInitValue up ⬆️

        // 3. Add a EnumConstant to the symbol table
            EnumConstant* enumConstant = new EnumConstant();
            enumConstant->value = lastInitValue;
            int check = SYM_TABLE.insert($3.varName, enumConstant);
            if(check == -1){
                // Already Present in Current Scope
                // [Error Handling]
            }

        // Okay
    }
    ;

/* Data on enumerator ✅
🟡 std::string varName; // This will be a string of variable name
🟡 bool isInitialized;
🟡 std::string initValue; 
*/
enumerator
    : IDENTIFIER {
        $$.varName = $1.tokenAtr->lexeme; // pass the varName up ⬆️
        $$.isInitialized = false; // pass the isInitialized up ⬆️
    }
    | IDENTIFIER ASSIGN constant_expression {
        $$.varName = $1.tokenAtr->lexeme; // pass the varName up ⬆️
        $$.isInitialized = true; // pass the isInitialized up ⬆️
        $$.initValue = $3.varName; // pass the initValue up ⬆️
    }
    ;

/* Data on type_qualifier ✅
🟡 std::string value; // This will be a string of type
*/
type_qualifier
    : CONST    { $$.value = $1.tokenAtr->lexeme; }
    | VOLATILE { $$.value = $1.tokenAtr->lexeme; }
    ;

/* Data on declarator NT ✅
🟡 std::string varName; // This will be a string of variable name
🟡 TypeExpression type; // This will be a TypeExpression
🔴 TypeExpression inh_type; // This will be a TypeExpression
*/
declarator
    : pointer direct_declarator { 
        // Process the pointer and add it to the inh_data
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
        $1.inh_type.levelStack.addOnTop($1.PtrInfo); // add the pointer info to the type ➕
        // .add(std::stack<PointerInfo>) is a function to add the stack<PointerInfo*> to the levels stack 
        // Need to assure this <PointerInfo> is converted to <LevelInfo*> [📍ToDo]

        // pass the syn_data up ⬆️
        $$.type = $1.type; // pass syn_data up ⬆️
        $$.varName = $2.varName; // pass the varName up ⬆️
    }
    | direct_declarator { 
        // carry the inh_data below ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // pass the syn_data up ⬆️
        $$.type = $1.type; // pass syn_data up ⬆️
    }
    ;


/* direct_declarator syn/inh variable ✅
🟡 TypeExpression type
🟡 std::string varName \\ can be FunctionName, VariableName, EnumConstName
🔴 TypeExpression inh_type \\ this will be having baseInfo already pushed at bottom
*/
direct_declarator
    : IDENTIFIER {
        // 🚦 🛑 Last Production inh_data is rotated into a syn_data
        $$.varName = $1.tokenAtr->lexeme;
        $$.type = $$.inh_type; // just pass to syn as we have reached the last level ☯️ 
    }
    | LPAREN declarator RPAREN {
        $2.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        $$.type = $2.type; // pass syn_data up ⬆️
        $$.varName = $2.varName; // pass the varName up ⬆️
    }
    | direct_declarator LSQUARE constant_expression RSQUARE {
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
        
        $1.inh_type.levelStack.addOnTop(new ArrayInfo($3.tokenAtr->lexeme)); ➕
        // ArrayInfo(constant_expression) is a constructor 

        $$.type = $1.type; // pass syn_data up ⬆️
        $$.varName = $1.varName; // pass the varName up ⬆️
    }
    | direct_declarator LSQUARE RSQUARE {
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
        
        $1.inh_type.levelStack.addOnTop(new ArrayInfo(-1)); // add the pointer info to the type ➕
        // ArrayInfo(-1) is a constructor to indicate unknown size

        $$.type = $1.type; // pass syn_data up ⬆️
        $$.varName = $1.varName; // pass the varName up ⬆️
    }

    /* Data to/from parameter_type_list
    ⬆️ from - 🟡 std::vector<TypeExpression> paramVector;
    */
    | direct_declarator LPAREN parameter_type_list RPAREN {
        // 1. Carry the inh_data down ⬇️
            $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
            
            // 1.1 Create a ParameterInfo and add it to the inh_type
                ParameterInfo* paramInfo = new ParameterInfo();
                paramInfo->paramTypes = $3.paramVector; // add the parameter type list to the parameter info ➕
                $1.inh_type.levelStack.addOnTop(paramInfo); // add the parameter info to the type ➕

        // 2. Pass the syn_data up ⬆️
            $$.type = $1.type; // pass syn_data up ⬆️
    }
    | direct_declarator LPAREN identifier_list RPAREN {
        // What is this doing? [🧠 ToThink]
    }
    | direct_declarator LPAREN RPAREN {
        // 1. Carry the inh_data down ⬇️
            $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
        
            // 1.1 Create a ParameterInfo and add it to the inh_type
                ParameterInfo* paramInfo = new ParameterInfo();
                paramInfo->paramTypes = new vector<TypeExpression>(); // empty vector
                $1.inh_type.levelStack.addOnTop(paramInfo); // add the parameter info to the type ➕
        
        // 2. Pass the syn_data up ⬆️
            $$.type = $1.type; // pass syn_data up ⬆️
    }
    ;


/* Data on pointer ✅
🟡 std::stack<PointerInfo> PtrInfo; // This will be a stack of PointerInfo
🔴 std::stack<PointerInfo> inh_PtrInfo; 
*/
pointer 
    : STAR { 
        // Last Production 🚦🛑
        $$.PtrInfo = $$.inh_PtrInfo; // rotate inh_PtrInfo to syn_PtrInfo ☯️
        $$.PtrInfo.push(PointerInfo()); // add PointerInfo ➕
    }
    | STAR type_qualifier_list {
        // Last Production 🚦🛑
        $$.PtrInfo = $$.inh_PtrInfo; // rotate inh_PtrInfo to syn_PtrInfo ☯️
        $$.PtrInfo.push(PointerInfo($2.Qualifiers)); // add PointerInfo with Qualifiers ➕
    }
    | STAR pointer { 
        $1.inh_PtrInfo = $$.inh_PtrInfo; // carry the inh_data below ⬇️
        $1.inh_PtrInfo.push(PointerInfo()); // add PointerInfo ➕

        $$.PtrInfo = $1.PtrInfo; // pass syn_data up ⬆️
    }
    | STAR type_qualifier_list pointer {
        $1.inh_PtrInfo = $$.inh_PtrInfo; // carry the inh_data below ⬇️
        $1.inh_PtrInfo.push(PointerInfo($2.Qualifiers)); // add PointerInfo with Qualifiers ➕

        $$.PtrInfo = $1.PtrInfo; // pass syn_data up ⬆️
    }
    ;


/* Data on type_qualifier_list ✅
🟡 std::vector<TypeQualifier> Qualifiers; // [syn] This will be a vector of TypeQualifier
*/
//👍
type_qualifier_list
    : type_qualifier { 
        // Last Production
        $$.Qualifiers = new vector<TypeQualifier>();
        TypeQualifier qualifier = convertToTypeQualifier($1.value); // convert the string to TypeQualifier

        $$.Qualifiers.push_back(qualifier); // push the type_qualifier
    }
    | type_qualifier_list type_qualifier { 
        $$.Qualifiers = $1.Qualifiers; // copy the vector
        TypeQualifier qualifier = convertToTypeQualifier($2.value); // convert the string to TypeQualifier
        $$.Qualifiers.push_back(qualifier); // push the type_qualifier
    }
    ;

/* Data on parameter_type_list ✅
🟡 std::vector<TypeExpression> paramVector; // This will be a vector of TypeExpression
*/
parameter_type_list
    : parameter_list {
        // Last Production 🚦🛑
        $$.paramVector = $$.paramVector; // pass the paramVector up ⬆️
    }
    | parameter_list COMMA ELLIPSIS {
        // Error: ELLIPSIS not supported
        // [📍ToDo - Error Handling] 
    }
    ;


/* Data on parameter_list ✅
🟡 std::vector<TypeExpression> paramVector; // This will be a vector of TypeExpression
*/
parameter_list
    : parameter_declaration {
        // Last Production 🚦🛑
        $$.paramVector = new vector<TypeExpression>();
        $$.paramVector.push_back($1.type); // push the parameter type
    }
    | parameter_list COMMA parameter_declaration
    ;



//~~~~~~~~~~ Parameter Declaration Logic ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* Data on parameter_declaration ✅
🟡 TypeExpression type; // Type of each parameter
*/

/* Data from/to declaration_specifiers
    ⬆️ from - 🟡 std::vector<std::string> valueVector; // This will be a vector of TypeExpression
*/
parameter_declaration
    : declaration_specifiers declarator {
        // 💡 Something similar to as on node - declaration
        
        // Process the declaration_specifiers
        BaseInfo* baseInfo = new BaseInfo();
        StorageClass storageClass;
        std::string check = ProcessDecSecifier($1.valueVector,baseInfo,storageClass);

        // Function Arguments can't have storage class
        if(storageClass != NULL){
            // Report Error as per message [ 🐞 Error Handling ]
        }

        if(check!="OK"){
            // Report Error as per message
        }
        TypeExpression tempType = new TypeExpression();
        tempType.levelStack.addOnTop(baseInfo); // add the baseInfo to the type ➕


        // Carry this to the declarator down ⬇️
        $2.inh_type = tempType; // pass the type to the declarator ⬇️


        // Passing things up ⬆️
        $$.type = $2.type; // pass the type to the parameter_declaration ⬆️
        // $$.varName = $2.varName; // pass the varName to the parameter_declaration ⬆️
        // [🔍 Check if varName will be needed]

    }
    | declaration_specifiers abstract_declarator {

        // Process the declaration_specifiers
        BaseInfo* baseInfo = new BaseInfo();
        std::string check = ProcessDecSecifier($1.valueVector,baseInfo);
        if(check!="OK"){
            // Report Error as per message
        }
        TypeExpression tempType = new TypeExpression();
        tempType.levelStack.addOnTop(baseInfo); // add the baseInfo to the type ➕


        // Carry this to the abstract_declarator down ⬇️
        $2.inh_type = tempType; // pass the type to the abstract_declarator ⬇️


        // Passing things up ⬆️
        $$.type = $2.type; // pass the type to the parameter_declaration ⬆️
        // abstract don't have varName

    }
    | declaration_specifiers {

        // Process the declaration_specifiers
        BaseInfo* baseInfo = new BaseInfo();
        std::string check = ProcessDecSecifier($1.valueVector,baseInfo);
        if(check!="OK"){
            // Report Error as per message
        }
        TypeExpression tempType = new TypeExpression();
        tempType.levelStack.addOnTop(baseInfo); // add the baseInfo to the type ➕

        // Nothing to carry down 

        // Passing things up ⬆️
        $$.type = tempType; // pass the type to the parameter_declaration ⬆️

    }   
    ;


// - Don't know where it's used
identifier_list
    : IDENTIFIER
    | identifier_list COMMA IDENTIFIER
    ;


/* Data on type_name ✅
🟡 TypeExpression type;
*/
type_name 
    : specifier_qualifier_list {
        // Process the declaration_specifiers
        BaseInfo* baseInfo = new BaseInfo();
        std::string check = ProcessDecSecifier($1.valueVector,baseInfo);
        if(check!="OK"){
            // Report Error as per message
        }

        TypeExpression tempType = new TypeExpression();
        tempType.levelStack.addOnTop(baseInfo); // add the baseInfo to the type ➕

        // Nothing to carry down

        // Passing things up ⬆️
        $$.type = tempType; // pass the type to the parameter_declaration ⬆️
    }
    | specifier_qualifier_list abstract_declarator {
        // Process the declaration_specifiers
        BaseInfo* baseInfo = new BaseInfo();
        std::string check = ProcessDecSecifier($1.valueVector,baseInfo);
        if(check!="OK"){
            // Report Error as per message
        }

        TypeExpression tempType = new TypeExpression();
        tempType.levelStack.addOnTop(baseInfo); // add the baseInfo to the type ➕

        // Carry this to the abstract_declarator down ⬇️
        $2.inh_type = tempType; // pass the type to the abstract_declarator ⬇️

        // Passing things up ⬆️
        $$.type = $2.type; // pass the type to the parameter_declaration ⬆️
    }
    ;


/* Data on abstract_declarator ✅
🟡 TypeExpression type; // This will be a TypeExpression
🔴 TypeExpression inh_type; // This will be a TypeExpression
*/

abstract_declarator
    : pointer {
        // Last Production 🚦🛑 [Need Rotation]
        // Nothing to carry down 

        // Add the pointer info
        $$.inh_type.levelStack.addOnTop($1.PtrInfo); // add the pointer info to the type ➕

        $$.type = $$.inh_type; // rotate the inh_data to syn_data ☯️
    }
    | direct_abstract_declarator {
        // Carry the inh_data down ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // passing things up ⬆️
        $$.type = $1.type; // pass the type to the parameter_declaration ⬆️
    }
    | pointer direct_abstract_declarator {
        // Process the pointer and add it to the inh_data and carry it down ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
        $1.inh_type.levelStack.addOnTop($1.PtrInfo); // add the pointer info to the type ➕

        // passing things up ⬆️
        $$.type = $1.type; // pass the type to the parameter_declaration ⬆️
    }
    ;

/* Data on direct_abstract_declarator ✅
🟡 TypeExpression type; // This will be a TypeExpression
🔴 TypeExpression inh_type; // This will be a TypeExpression
*/
direct_abstract_declarator
    : LPAREN abstract_declarator RPAREN {
        // Carry the inh_data down ⬇️
        $2.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // passing things up ⬆️
        $$.type = $2.type; // pass the type to the parameter_declaration ⬆️
    }

    | LSQUARE RSQUARE {
        // Last Production 🚦🛑 [Need Rotation]

        // Add the array info to the type & pass it up ⬆️
        $$.inh_type.levelStack.addOnTop(new ArrayInfo(-1)); // add the array info to the type ➕

        $$.type = $$.inh_type; // rotate the inh_data to syn_data ☯️

    }
    | LSQUARE constant_expression RSQUARE {
        // Last Production 🚦🛑 [Need Rotation]

        // Add the array info to the type & pass it up ⬆️
        $$.inh_type.levelStack.addOnTop(new ArrayInfo($2)); // add the array info to the type ➕

        $$.type = $$.inh_type; // rotate the inh_data to syn_data ☯️
    }

    | direct_abstract_declarator LSQUARE RSQUARE {
        // Carry the inh_data down ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // Add the array info to the type
        $1.inh_type.levelStack.addOnTop(new ArrayInfo(-1)); // add the array info to the type ➕

        // passing things up ⬆️
        $$.type = $1.type; // pass the type to the parameter_declaration ⬆️
    }
    | direct_abstract_declarator LSQUARE constant_expression RSQUARE {
        // Carry the inh_data down ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // Add the array info to the type
        $1.inh_type.levelStack.addOnTop(new ArrayInfo($3)); // add the array info to the type ➕

        // passing things up ⬆️
        $$.type = $1.type; // pass the type to the parameter_declaration ⬆️
    }
    
    | LPAREN RPAREN {
        // Last Production 🚦🛑 [Need Rotation]

        // Add the function info to the type & pass it up ⬆️
        ParameterInfo* paramInfo = new ParameterInfo();
        paramInfo->paramTypes = new vector<TypeExpression>();
        $$.inh_type.levelStack.addOnTop(paramInfo); // add the parameter info to the type ➕
        // No need of void as dummy

        $$.type = $$.inh_type; // rotate the inh_data to syn_data ☯️
    }
    | LPAREN parameter_type_list RPAREN {
        // Last Production 🚦🛑 [Need Rotation]

        // Add the function info to the type & pass it up ⬆️
        ParameterInfo* paramInfo = new ParameterInfo();
        paramInfo->paramTypes = $2.paramVector; // copy the parameter type list
        $$.inh_type.levelStack.addOnTop(paramInfo); // add the parameter info to the type ➕

        $$.type = $$.inh_type; // rotate the inh_data to syn_data ☯️
    }

    | direct_abstract_declarator LPAREN RPAREN {
        // Carry the inh_data down ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // Add the function info to the type
        ParameterInfo* paramInfo = new ParameterInfo();
        paramInfo->paramTypes = new vector<TypeExpression>();
        $1.inh_type.levelStack.addOnTop(paramInfo); // add the parameter info to the type ➕

        // passing things up ⬆️
        $$.type = $1.type; // pass the type to the parameter_declaration ⬆️
    }
    | direct_abstract_declarator LPAREN parameter_type_list RPAREN {
        // Carry the inh_data down ⬇️
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // Add the function info to the type
        ParameterInfo* paramInfo = new ParameterInfo();
        paramInfo->paramTypes = $2.paramVector; // copy the parameter type list
        $1.inh_type.levelStack.addOnTop(paramInfo); // add the parameter info to the type ➕

        // passing things up ⬆️
        $$.type = $1.type; // pass the type to the parameter_declaration ⬆️
    }
    ;

// == Will Think of it later ==
initializer
    : assignment_expression
    | LCURLY initializer_list RCURLY
    | LCURLY initializer_list COMMA RCURLY
    ;

initializer_list
    : initializer
    | initializer_list COMMA initializer
    ;

//========================== End of declaration_logic ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

statement
    : labeled_statement
    | compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | declaration
    ;

labeled_statement
    : IDENTIFIER COLON statement
    | CASE constant_expression COLON statement
    | DEFAULT COLON statement
    ;

compound_statement
    : LCURLY RCURLY
    | LCURLY statement_list RCURLY
    | LCURLY declaration_list RCURLY
    | LCURLY declaration_list statement_list RCURLY
    ;

declaration_list
    : declaration
    | declaration_list declaration
    ;

statement_list
    : statement
    | statement_list statement
    ;

expression_statement
    : SEMI_COLON
    | expression SEMI_COLON
    ;

selection_statement
    : IF LPAREN expression RPAREN statement
    | IF LPAREN expression RPAREN statement ELSE statement
    | SWITCH LPAREN expression RPAREN statement
    ;

iteration_statement
    : WHILE LPAREN expression RPAREN statement
    | UNTIL LPAREN expression RPAREN statement
    | DO statement WHILE LPAREN expression RPAREN SEMI_COLON
    | FOR LPAREN expression_statement expression_statement RPAREN statement
    | FOR LPAREN expression_statement expression_statement expression RPAREN statement
    | FOR LPAREN declaration expression_statement expression RPAREN statement
    ;

jump_statement 
    : GOTO IDENTIFIER SEMI_COLON
    | CONTINUE SEMI_COLON
    | BREAK SEMI_COLON
    | RETURN SEMI_COLON
    | RETURN expression SEMI_COLON
    ;

translation_unit
    : external_declaration
    | translation_unit external_declaration
    ;

external_declaration
    : function_definition
    | declaration
    ;

function_definition
    : declaration_specifiers declarator declaration_list compound_statement
    | declaration_specifiers declarator compound_statement
    | declarator declaration_list compound_statement
    | declarator compound_statement // Pre-ASCII C [To be checked in Semantic Phase]
    ;
