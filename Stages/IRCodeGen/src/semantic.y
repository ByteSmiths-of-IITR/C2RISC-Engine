// File: grammarOnly.y

%{
    %}

%union{
    struct TokenAttribute* tokenAtr;
    struct ASTNode* astNode;
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

/* %type <astNode> IDENTIFIER CONSTANT SEMI_COLON
%type <astNode> RPAREN RCURLY RSQUARE */

%type <astNode> primary_expression
%type <astNode> postfix_expression
%type <astNode> argument_expression_list
%type <astNode> unary_expression
%type <astNode> unary_operator
%type <astNode> cast_expression
%type <astNode> multiplicative_expression
%type <astNode> additive_expression
%type <astNode> shift_expression
%type <astNode> relational_expression
%type <astNode> equality_expression
%type <astNode> and_expression
%type <astNode> exclusive_or_expression
%type <astNode> inclusive_or_expression
%type <astNode> logical_and_expression
%type <astNode> logical_or_expression
%type <astNode> conditional_expression
%type <astNode> assignment_expression
%type <astNode> assignment_operator
%type <astNode> expression
%type <astNode> constant_expression
%type <astNode> declaration
%type <astNode> declaration_specifiers
%type <astNode> init_declarator_list
%type <astNode> init_declarator 
%type <astNode> storage_class_specifier
%type <astNode> type_specifier
%type <astNode> struct_or_union_specifier
%type <astNode> struct_or_union
%type <astNode> struct_declaration_list
%type <astNode> struct_declaration
%type <astNode> specifier_qualifier_list
%type <astNode> struct_declarator_list
%type <astNode> struct_declarator
%type <astNode> enum_specifier
%type <astNode> enumerator_list
%type <astNode> enumerator
%type <astNode> type_qualifier
%type <astNode> declarator
%type <astNode> direct_declarator
%type <astNode> pointer
%type <astNode> type_qualifier_list
%type <astNode> parameter_type_list
%type <astNode> parameter_list
%type <astNode> parameter_declaration
%type <astNode> identifier_list
%type <astNode> type_name
%type <astNode> abstract_declarator
%type <astNode> direct_abstract_declarator
%type <astNode> initializer
%type <astNode> initializer_list
%type <astNode> statement
%type <astNode> labeled_statement
%type <astNode> compound_statement
%type <astNode> declaration_list
%type <astNode> statement_list
%type <astNode> expression_statement
%type <astNode> selection_statement
%type <astNode> iteration_statement
%type <astNode> jump_statement
%type <astNode> translation_unit
%type <astNode> external_declaration
%type <astNode> function_definition

/* %expect-rr 96 */
/* %expect 2 */

%start translation_unit
%%
//Expressions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/* Data on all expressions
🟡 std::string varName; // This will be [Constants, CompilerTempName, VariableName or EnumConstantName]
🟡 TypeExpression type; // 
*/

primary_expression
    : IDENTIFIER {
        $$.varName = $1.tokenAtr->lexeme;
        // Check from symbol table if the identifier is declared
        // If not declared, throw error
        // If declared, get the type from symbol table
        $$.type = getTypeFromSymbolTable($1.tokenAtr->lexeme); // a highWrapper Function [📍ToDo]

        // IRCode Login [📍ToDo]
    }
    | CONSTANT {
        // [📍ToDo - Make changes in Grammar so all constants can be identified at Lexer Stage itself]
        $$.varName = newTemp();
        $$.type = getType("int"); // [📍ToDo - Get the type from tokenAtr]
        // [📍ToDo - Get the type from tokenAtr]
    }
    
    | STRING_LITERAL {
        // TO THINK 🧠

        // [📍ToDo - Get the type from tokenAtr]

        // IRCode Login [ToThink 🧠]
        // We directly use string literals in IRCode
        // CODE_BASE.addTAC($$.varName, "=", $1.tokenAtr->lexeme, NULL);
    }
    | LPAREN expression RPAREN {
        // Pass syn_data up ⬆️
        $$.varName = $2.varName;
        $$.type = $2.type;

        // IRCode Login [ToThink 🧠]
        //NO CODE
    }
    ;

postfix_expression
    : primary_expression {
        // Pass syn_data up ⬆️
        $$.varName = $1.varName;
        $$.type = $1.type;

        // IRCode Logic
        //NO CODE
    }
    | postfix_expression LSQUARE expression RSQUARE {
        // Pass syn_data up ⬆️
        TypeExpression temp = $1.type;
        
        //[📍ToThink Deep]

        // IRCode Logic
        
    }
    | postfix_expression LPAREN RPAREN {
        // Function call
    }
    | postfix_expression LPAREN argument_expression_list LPAREN {
        // function call
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

argument_expression_list
    : assignment_expression
    | argument_expression_list COMMA assignment_expression
    ;

unary_expression
    : postfix_expression
    | INC_OP unary_expression
    | DEC_OP unary_expression
    | unary_operator cast_expression
    | SIZEOF unary_expression
    | SIZEOF LPAREN type_name RPAREN
    ;

unary_operator
    : BIT_AND
    | STAR
    | PLUS
    | MINUS
    | BIT_NOT
    | NOT_OP
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
            // Report Error as per message
        }

        // No more processing size we have SEMI_COLOM
    }
    | declaration_specifiers init_declarator_list SEMI_COLON {
        BaseInfo* baseInfo = new BaseInfo();
        StorageClass storageClass;
        std::string check = ProcessDecSecifier($1.valueVector,baseInfo,storageClass);
        if(check!="OK"){
            // Report Error as per message
        }

        // We create a TypeExpression now
        TypeExpression tempType = new TypeExpression();
        tempType.dtype.levels.add(baseInfo); // add the baseInfo to the type ➕
        // tempType.dtype.levels is a stack of LevelInfo*

        $2.inh_type = tempType; // pass the type to the init_declarator_list ⬇️ 
        $2.inh_storageClass = storageClass; // pass the storage class to the init_declarator_list ⬇️

        // [🧠 Think if anything else is needed to be done here]
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

// To think about intializer 🧠
init_declarator
    : declarator {
        // Last Production 🚦
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
        // no need to pass the inh_storageClass anyfuther as symbol table entry will be created

        // Now we recieve type [syn] from declarator and we process this to create a symbol table entry
        TypeExpression tempType = $1.type;
        // [📍ToDo - Create a symbol table entry] ☢️SYMBOL_ADD
        // Available - varName, type, inh_storageClass

    }
    | declarator ASSIGN initializer {
        // Last Production 🚦
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️

        // Now we recieve type [syn] from declarator and we process this to create a symbol table entry
        TypeExpression tempType = $1.type;
        // [📍ToDo - Create a symbol table entry] ☢️SYMBOL_ADD
        // Available - varName, type, inh_storageClass

    }
    ;



/* Data on storage_class_specifier ✅
🟡 std::string value; // This will be a string of type
*/
storage_class_specifier
    : TYPEDEF {/* not supported*/}
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
        // [📍ToDo - Think]
    }
    | enum_specifier {
        // [📍ToDo - Think]
    }
    | TYPE_NAME {
        // [Find what is this doing? 🔍 ]
    } 
    ;

struct_or_union_specifier
    : struct_or_union IDENTIFIER LCURLY struct_declaration_list RCURLY
    | struct_or_union LCURLY struct_declaration_list RCURLY
    | struct_or_union IDENTIFIER
    ;

/* Data on struct_or_union_specifier ✅
🟡 std::string value ; // This will be a string of type
*/
struct_or_union
    : STRUCT { $$.value = $1.tokenAtr->lexeme; }
    | UNION  { $$.value = $1.tokenAtr->lexeme; }
    ;

// Vector of [(TypeExpression) & (varName)]
struct_declaration_list 
    : struct_declaration // This must return (TypeExpression) & (varName)
    | struct_declaration_list struct_declaration
    ;

struct_declaration
    : specifier_qualifier_list struct_declarator_list SEMI_COLON
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

// map<string, TypeExpression> [varName, TypeExpression]
struct_declarator_list 
    : struct_declarator
    | struct_declarator_list COMMA struct_declarator
    ;

struct_declarator
    : declarator // Will return a [(TypeExpression) & (varName)]
    | COLON constant_expression // Similar to initializer
    | declarator COLON constant_expression // LeftRecursive version of above
    ;

enum_specifier
    : ENUM LCURLY enumerator_list RCURLY //On-Spot Usage
    | ENUM IDENTIFIER LCURLY enumerator_list RCURLY //Identifier given can also be used later as a type
    | ENUM IDENTIFIER // Forward Declaration of Enum, can be used later as a type
    ;

enumerator_list
    : enumerator
    | enumerator_list COMMA enumerator
    ;

enumerator
    : IDENTIFIER
    | IDENTIFIER ASSIGN constant_expression
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
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
        
        $1.inh_type.paramTypes = $3.paramVector; // pass the parameter type list to the type

        $$.type = $1.type; // pass syn_data up ⬆️
    }
    | direct_declarator LPAREN identifier_list RPAREN {
        // What is this doing? [🧠 ToThink]
    }
    | direct_declarator LPAREN RPAREN {
        $1.inh_type = $$.inh_type; // carry the inh_data below ⬇️
        
        ParameterInfo* paramInfo = new ParameterInfo();
        paramInfo->paramTypes = new vector<TypeExpression>("void");
        $1.inh_type.levelStack.addOnTop(paramInfo); // add the parameter info to the type ➕
        
        // 🤯 To differentiate from var/function - we put a dummy type [ToDecide if needed 🤔]
        

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
        $$.Qualifiers.push_back($1); // push the type_qualifier
    }
    | type_qualifier_list type_qualifier { 
        $$.Qualifiers = $1.Qualifiers; // copy the vector
        $$.Qualifiers.push_back($2); // push the type_qualifier
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
        paramInfo->paramTypes = new vector<TypeExpression>("void");
        $$.inh_type.levelStack.addOnTop(paramInfo); // add the parameter info to the type ➕
        // 🤯 To differentiate from var/function - we put a dummy type

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
        paramInfo->paramTypes = new vector<TypeExpression>("void");
        $1.inh_type.levelStack.addOnTop(paramInfo); // add the parameter info to the type ➕
        // 🤯 To differentiate from var/function - we put a dummy type

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
