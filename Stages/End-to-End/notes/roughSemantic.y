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


primary_expression
    : IDENTIFIER
    | CONSTANT
    | STRING_LITERAL
    | LPAREN expression RPAREN
    ;

postfix_expression
    : primary_expression
    | postfix_expression LSQUARE expression RSQUARE
    | postfix_expression LPAREN RPAREN
    | postfix_expression LPAREN argument_expression_list RPAREN
    | postfix_expression DOT IDENTIFIER
    | postfix_expression PTR_OP IDENTIFIER
    | postfix_expression INC_OP
    | postfix_expression DEC_OP
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

// End of Expressions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

declaration
    : declaration_specifiers SEMI_COLON
    | declaration_specifiers init_declarator_list SEMI_COLON
    ;

//👍
/*This will pass a vector<string> of all info below it. They can be [TypeSpecifier, TypeQualifier, StorageClassSpecifier]*/
declaration_specifiers 
    : storage_class_specifier { $$.vector.push_back($1); }
    | storage_class_specifier declaration_specifiers { $$.vector = $2.vector; $$.vector.push_back($1); }
    | type_specifier    { $$.vector.push_back($1); }
    | type_specifier declaration_specifiers { $$.vector = $2.vector; $$.vector.push_back($1); }
    | type_qualifier    { $$.vector.push_back($1); }
    | type_qualifier declaration_specifiers { $$.vector = $2.vector; $$.vector.push_back($1); }
    ;

init_declarator_list
    : init_declarator
    | init_declarator_list COMMA init_declarator
    ;




// At this point we will be creating a VarSymbol and storing it in the symbol table
init_declarator
    : declarator
    | declarator ASSIGN initializer
    ;




storage_class_specifier
    : TYPEDEF {/* not supported*/}
    | EXTERN
    | STATIC 
    | AUTO
    | REGISTER
    ;

type_specifier
    : VOID
    | CHAR
    | SHORT
    | INT
    | LONG
    | FLOAT
    | DOUBLE
    | SIGNED
    | UNSIGNED
    | struct_or_union_specifier
    | enum_specifier
    | TYPE_NAME
    ;

struct_or_union_specifier
    : struct_or_union IDENTIFIER LCURLY struct_declaration_list RCURLY
    | struct_or_union LCURLY struct_declaration_list RCURLY
    | struct_or_union IDENTIFIER
    ;

struct_or_union
    : STRUCT
    | UNION
    ;

// Vector of [(TypeExpression) & (varName)]
struct_declaration_list 
    : struct_declaration // This must return (TypeExpression) & (varName)
    | struct_declaration_list struct_declaration
    ;

struct_declaration
    : specifier_qualifier_list struct_declarator_list SEMI_COLON
    ;


// This will return a vector<string> [ That can be typeSpecifier or typeQualifier ]
specifier_qualifier_list
    : type_specifier specifier_qualifier_list
    | type_specifier
    | type_qualifier specifier_qualifier_list
    | type_qualifier
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

type_qualifier
    : CONST
    | VOLATILE
    ;

// This will recieve stack<LevelInfo> from direct_declarator
declarator
    : pointer direct_declarator { 
        $$.stack = new stack; 
        $$.stack.copy_push($1.stack);
        $$.stack.copy_push($2.stack);
        $$.vaName = $2.vaName; // to think
        }
    | direct_declarator { 
        $$.stack = $1.stack; 
        $$.vaName = $1.vaName;
        }
    ;



/* direct_declarator syn/inh variable
TypeExpression type

*/
direct_declarator
    : IDENTIFIER { $$.vaName = $1; }
    | LPAREN declarator RPAREN { $$.stack = $2.stack; $$.vaName = $2.vaName; }
    | direct_declarator LSQUARE constant_expression RSQUARE {
        // Logic first we push the currentArray Info and then recursive push
        std::stack<LevelInfo> newStack;
        newStack.push(ArrayInfo($3));
        $$.stack = newStack;
        $$.stack.copy_push($1.stack);
        $$vaName = $1.vaName;
    }
    | direct_declarator LSQUARE RSQUARE 
        {
        // Logic first we push the currentArray Info and then recursive push
        std::stack<LevelInfo> newStack;
        newStack.push(ArrayInfo(-1 /*This is to show no size was given*/));
        $$.stack = newStack;
        $$.stack.copy_push($1.stack);
        $$vaName = $1.vaName;
        }
    | direct_declarator LPAREN parameter_type_list RPAREN
    | direct_declarator LPAREN identifier_list RPAREN
    | direct_declarator LPAREN RPAREN
    ;

// This will give it's parent a stack<LevelInfo> to be specific PointerInfo
// LevelInfo() 👍
pointer 
    : STAR { $$.stack.push_back(PointerInfo(EMPTY_TYPEQUALIFIER_VECTOR)); }
    | STAR type_qualifier_list { $$.stack.push_back(PointerInfo($2.Qualifiers)); }
    | STAR pointer { /*First we create a new stack and push new PointerInfo in bottom and then the stack given by pointer1 of production*/
        std::stack<LevelInfo> newStack;
        newStack.push(PointerInfo(EMPTY_TYPEQUALIFIER_VECTOR));
        $$.stack = newStack;
        $$.stack.copy_push($2.stack);
    }
    | STAR type_qualifier_list pointer {
        std::stack<LevelInfo> newStack;
        newStack.push(PointerInfo($2.Qualifiers));
        $$.stack = newStack;
        $$.stack.copy_push($3.stack);
    }
    ;

// This will give a vector<TypeQualifier> to it's parent 
//👍
type_qualifier_list
    : type_qualifier { $$.Qualifiers.push_back($1); }
    | type_qualifier_list type_qualifier { $$.Qualifiers = $1.Qualifiers; $$.Qualifiers.push_back($2); }
    ;

parameter_type_list
    : parameter_list
    | parameter_list COMMA ELLIPSIS {/*not supported*/}
    ;

parameter_list
    : parameter_declaration
    | parameter_list COMMA parameter_declaration
    ;
//this will make a variable (name and level) and return to it's parent
parameter_declaration
    : declaration_specifiers declarator
    | declaration_specifiers abstract_declarator
    | declaration_specifiers
    ;

identifier_list
    : IDENTIFIER
    | identifier_list COMMA IDENTIFIER
    ;

type_name
    : specifier_qualifier_list
    | specifier_qualifier_list abstract_declarator
    ;

abstract_declarator
    : pointer
    | direct_abstract_declarator
    | pointer direct_abstract_declarator
    ;

direct_abstract_declarator
    : LPAREN abstract_declarator RPAREN

    | LSQUARE RSQUARE
    | LSQUARE constant_expression RSQUARE

    | direct_abstract_declarator LSQUARE RSQUARE
    | direct_abstract_declarator LSQUARE constant_expression RSQUARE
    
    | LPAREN RPAREN
    | LPAREN parameter_type_list RPAREN

    | direct_abstract_declarator LPAREN RPAREN
    | direct_abstract_declarator LPAREN parameter_type_list RPAREN
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

// Done with Declarations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
