%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "ast.h"  // Ensure this is included
// #include "sym.h" 

extern char *yytext;
extern int DEBUGMODE;
void yyerror(const char *s);
extern int yylex();
extern FILE *yyin;

#define YYDEBUG 1

ASTNode *root;

%}

%union {
    char *str;
    struct ASTNode *node;
}

//keywords

%token ALIGNAS ALIGNOF ASM AUTO BOOL BREAK CASE CATCH CHAR CHAR16_T CHAR32_T CLASS CONST CONSTEXPR CONST_CAST
%token CONTINUE DECLTYPE DEFAULT DELETE DO DOUBLE DYNAMIC_CAST ELSE ENUM EXPLICIT EXPORT EXTERN FALSE FLOAT FOR FRIEND
%token GOTO IF INLINE INT LONG MUTABLE NAMESPACE NEW NOEXCEPT NULLPTR OPERATOR PRIVATE PROTECTED PUBLIC REGISTER
%token REINTERPRET_CAST RETURN SHORT SIGNED SIZEOF STATIC STATIC_ASSERT STATIC_CAST STRUCT SWITCH TEMPLATE THIS
%token THREAD_LOCAL THROW TRUE TRY TYPEDEF TYPEID TYPENAME UNION UNSIGNED USING VIRTUAL VOID VOLATILE WCHAR_T WHILE

//operators
%token AND AND_EQ BITAND BITOR COMPL NOT NOT_EQ OR OR_EQ XOR XOR_EQ
%token PLUS PLUS_EQ MINUS MINUS_EQ MULTIPLY MULTIPLY_EQ DIVIDE DIVIDE_EQ MODULO MODULO_EQ

%token <str> IDENTIFIER NUMBER STRING_LITERAL CHAR_LITERAL
%token ASSIGN SEMICOLON COMMA
%token EQUAL NOT_EQUAL LESS GREATER LESS_EQUAL GREATER_EQUAL
%token PRINTF SCANF
%token AMPERSAND LBRACKET RBRACKET LPAREN RPAREN LBRACE RBRACE COLON COLONCOLON TILDE

%token UNKNOWN 

//literal
%token DECIMAL_LITERAL OCTAL_LITERAL HEXADECIMAL_LITERAL NONZERO_DIGIT OCTAL_DIGIT HEXADECIMAL_DIGIT INTEGER_SUFFIX UNSIGNED_SUFFIX LONG_SUFFIX LONG_LONG_SUFFIX

//for all keyword in c++

%token <str> GT LT DOT DOTSTAR ARROW ARROWSTAR PLUSPLUS MINUSMINUS ELLIPSIS OVERRIDE FINAL PIPE




//left and right shift
%left LEFT_SHIFT RIGHT_SHIFT

%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS GREATER LESS_EQUAL GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT

%type <node> function_definition function_body compound_statement
%type <node> declaration_statement statement_seq  statement
%type <node> simple_declaration static_assert_declaration empty_declaration attribute_declaration
%type <node> block_declaration declaration declaration_seq
%type <node>  decl_specifier_seq decl_specifier
%type <node>  init_declarator_list init_declarator
%type <node> declarator template
%type <node>  attribute_specifier_seq attribute_specifier
%type <node> type_specifier
%type <node> simple_type_specifier
%type <node> constant_expression
%type <node> assignment_expression
%type <node> primary_expression
%type <node> postfix_expression
%type <node> multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression
%type <node> logical_and_expression logical_or_expression conditional_expression 
%type <node> assignment_operator expression 
%type <node> labeled_statement expression_statement 
%type <node> selection_statement condition iteration_statement jump_statement
%type <node> for_init_statement for_range_declaration for_range_initializer
%type <node> literal integer_literal character_literal floating_literal string_literal boolean_literal pointer_literal user_defined_literal user_defined_integer_literal
%type <node> decimal_literal octal_literal hexadecimal_literal nonzero_digit octal_digit hexadecimal_digit integer_suffix unsigned_suffix long_suffix long_long_suffix
%type <node> c_char_sequence c_char escape_sequence simple_escape_sequence octal_escape_sequence hexadecimal_escape_sequence
%type <node> fractional_constant exponent_part sign digit_sequence floating_suffix
%type <node> encoding_prefix s_char_sequence s_char raw_string r_char_sequence r_char d_char_sequence d_char
%type <node> ud_suffix alias_declaration endif_line group_part if_section elif_group else_group 
%type <node>  id_expression unqualified_id qualified_id nested_name_specifier
%type <node> lambda_expression lambda_introducer lambda_declarator lambda_capture capture_default capture_list capture
%type <node>  expression_list pseudo_destructor_name unary_expression unary_operator
%type <node> new_expression new_placement new_type_id new_declarator noptr_new_declarator new_initializer
%type <node> delete_expression noexcept_expression cast_expression pm_expression

%type <node> hex_quad universal_character_name
%type <node> preprocessing_token header_name h_char_sequence h_char q_char_sequence q_char
%type <node> pp_number noptr_abstract_declarator parameter_declaration_clause parameter_declaration_list parameter_declaration
%type <node> identifier identifier_nondigit nondigit digit
%type <node> keyword type_id abstract_declarator class_name class_key class_specifier 
%type <node> operator_token punctuator preprocessing_op_or_punc
%type <node> operator_function_id overloadable_operator literal_operator_id conversion_function_id template_declaration template_parameter_list template_parameter type_parameter
%type <node> template_argument_list template_argument simple_template_id typename_specifier template_name template_id
%type <node> explicit_instantiation explicit_specialization try_block function_try_block handler_seq handler exception_declaration exception_specification
%type <node> type_id_list throw_expression dynamic_exception_specification noexcept_specification

%type <node>  storage_class_specifier function_specifier typedef_name  trailing_type_specifier type_specifier_seq trailing_type_specifier_seq 
%type <node> type_name decltype_specifier elaborated_type_specifier enum_name enum_specifier enum_head opaque_enum_declaration enum_key enum_base
%type <node> enumerator_list enumerator_definition enumerator namespace_name original_namespace_name namespace_definition named_namespace_definition
%type <node> original_namespace_definition extension_namespace_definition unnamed_namespace_definition namespace_body namespace_alias namespace_alias_definition
%type <node> qualified_namespace_specifier using_declaration using_directive asm_definition linkage_specification alignment_specifier attribute_list attribute
%type <node> attribute_token attribute_scoped_token attribute_namespace attribute_argument_clause balanced_token_seq balanced_token
%type <node> user_defined_floating_literal user_defined_string_ brace_or_equal_initializer user_defined_character_literal ptr_declarator noptr_declarator parameters_and_qualifiers trailing_return_type
%type <node> ptr_operator cv_qualifier_seq cv_qualifier ref_qualifier  declarator_id ptr_abstract_declarator
%type <node> member_specification initializer initializer_clause initializer_list braced_init_list user_defined_string_literal
%type <node> class_head class_head_name class_virt_specifier base_clause class_or_decltype member_declaration member_declarator_list member_declarator
%type <node> virt_specifier_seq virt_specifier class_virt_specifier_seq pure_specifier base_specifier_list base_specifier base_type_specifier access_specifier conversion_type_id conversion_declarator mem_initializer_list conversion_type_id_list mem_initializer mem_initializer_id
//all optional
%type <node> template_opt template_argument_list_opt template_argument_opt exception_specification_opt type_id_list_opt
%type <node> init_declarator_list_opt attribute_specifier_seq_opt ref_qualifier_opt expression_opt expression_list_opt assignment_expression_opt constant_expression_opt digit_sequence_opt sign_opt encoding_prefix_opt s_char_sequence_opt r_char_sequence_opt d_char_sequence_opt
%type <node> statement_seq_opt decl_specifier_seq_opt lambda_declarator_opt lambda_capture_opt capture_default_opt capture_list_opt expression_seq_opt expression_statement_opt
%type <node> member_specification_opt parameter_declaration_list_opt abstract_declarator_opt noptr_abstract_declarator_opt ptr_abstract_declarator_opt nested_name_specifier_opt cv_qualifier_seq_opt init_declarator_opt declaration_seq_opt declaration_opt  decl_specifier_opt conversion_declarator_opt mem_initializer_list_opt mem_initializer_opt conversion_type_id_list_opt conversion_type_id_opt access_specifier_opt
%type <node> long_suffix_opt long_long_suffix_opt unsigned_suffix_opt exponent_part_opt floating_suffix_opt
%type <node> initializer_opt group_opt if_group elif_groups_opt else_group_opt
%type <node> integer_suffix_opt virt_specifier_opt class_virt_specifier_opt base_clause_opt member_declaration_opt member_declarator_list_opt member_declarator_opt virt_specifier_seq_opt class_virt_specifier_seq_opt pure_specifier_opt base_specifier_list_opt base_specifier_opt
%type <node> identifier_list_opt replacement_list  ctor_initializer ctor_initializer_opt brace_or_equal_initializer_opt identifier_opt
%type <node> attribute_argument_clause_opt attribute_opt typename_opt pp_tokens_opt braced_init_list_opt condition_opt new_declarator_opt new_initializer_opt new_placement_opt new_type_id_opt mutable_opt trailing_return_type_opt
%type <node> enum_base_opt enumerator_list_opt enumerator_definition_opt enumerator_opt namespace_definition_opt named_namespace_definition_opt


%token <str> VIRTUAL_opt EXTERN_opt COMMA_opt COLONCOLON_opt ELLIPSIS_opt AMPERSAND_opt IDENTIFIER_opt SEMICOLON_opt INLINE_opt CONSTEXPR_opt CONSTEVAL_opt CONSTINIT_opt CONSTDINIT_opt
%%

/* -------------------------------- */

hex_quad:
    hexadecimal_digit hexadecimal_digit hexadecimal_digit hexadecimal_digit
;

universal_character_name:
    '\\' 'u' hex_quad
    | '\\' 'U' hex_quad hex_quad
;

preprocessing_token:
    header_name
    | identifier
    | pp_number
    | character_literal
    | user_defined_character_literal
    | string_literal
    | user_defined_string_literal
    | preprocessing_op_or_punc
    /* | any_non_white_space_character */
;

token:
    identifier
    | keyword
    | literal
    | operator_token
    | punctuator
;

header_name:
    '<' h_char_sequence '>'
    | '"' q_char_sequence '"'
;

h_char_sequence:
    h_char
    | h_char_sequence h_char
;

h_char:
    /* any_member_of_source_character_set_except_new_line_and_greater_than */
;

q_char_sequence:
    q_char
    | q_char_sequence q_char
;

q_char:
    /* any_member_of_source_character_set_except_new_line_and_double_quote */
;

pp_number:
    digit
    | '.' digit
    | pp_number digit
    | pp_number identifier_nondigit
    | pp_number 'e' sign
    | pp_number 'E' sign
    | pp_number '.'
;

identifier:
    identifier_nondigit
    | identifier identifier_nondigit
    | identifier digit
;

identifier_nondigit:
    nondigit
    | universal_character_name
    /* | other_implementation_defined_characters */
;

nondigit:
    'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z'
    | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z'
    | '_'
;

digit:
    '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
;

keyword:
    ALIGNAS { $$ = new ASTNode("keyword"); $$->createChild("name", "alignas"); }
    | ALIGNOF { $$ = new ASTNode("keyword"); $$->createChild("name", "alignof"); }
    | ASM { $$ = new ASTNode("keyword"); $$->createChild("name", "asm"); }
    | AUTO { $$ = new ASTNode("keyword"); $$->createChild("name", "auto"); }
    | BOOL { $$ = new ASTNode("keyword"); $$->createChild("name", "bool"); }
    | BREAK { $$ = new ASTNode("keyword"); $$->createChild("name", "break"); }
    | CASE { $$ = new ASTNode("keyword"); $$->createChild("name", "case"); }
    | CATCH { $$ = new ASTNode("keyword"); $$->createChild("name", "catch"); }
    | CHAR { $$ = new ASTNode("keyword"); $$->createChild("name", "char"); }
    | CHAR16_T { $$ = new ASTNode("keyword"); $$->createChild("name", "char16_t"); }
    | CHAR32_T { $$ = new ASTNode("keyword"); $$->createChild("name", "char32_t"); }
    | CLASS { $$ = new ASTNode("keyword"); $$->createChild("name", "class"); }
    | CONST { $$ = new ASTNode("keyword"); $$->createChild("name", "const"); }
    | CONSTEXPR { $$ = new ASTNode("keyword"); $$->createChild("name", "constexpr"); }
    | CONST_CAST { $$ = new ASTNode("keyword"); $$->createChild("name", "const_cast"); }
    | CONTINUE { $$ = new ASTNode("keyword"); $$->createChild("name", "continue"); }
    | DECLTYPE { $$ = new ASTNode("keyword"); $$->createChild("name", "decltype"); }
    | DEFAULT { $$ = new ASTNode("keyword"); $$->createChild("name", "default"); }
    | DELETE { $$ = new ASTNode("keyword"); $$->createChild("name", "delete"); }
    | DO { $$ = new ASTNode("keyword"); $$->createChild("name", "do"); }
    | DOUBLE { $$ = new ASTNode("keyword"); $$->createChild("name", "double"); }
    | DYNAMIC_CAST { $$ = new ASTNode("keyword"); $$->createChild("name", "dynamic_cast"); }
    | ELSE { $$ = new ASTNode("keyword"); $$->createChild("name", "else"); }
    | ENUM { $$ = new ASTNode("keyword"); $$->createChild("name", "enum"); }
    | EXPLICIT { $$ = new ASTNode("keyword"); $$->createChild("name", "explicit"); }
    | EXPORT { $$ = new ASTNode("keyword"); $$->createChild("name", "export"); }
    | EXTERN { $$ = new ASTNode("keyword"); $$->createChild("name", "extern"); }
    | FALSE { $$ = new ASTNode("keyword"); $$->createChild("name", "false"); }
    | FLOAT { $$ = new ASTNode("keyword"); $$->createChild("name", "float"); }
    | FOR { $$ = new ASTNode("keyword"); $$->createChild("name", "for"); }
    | FRIEND { $$ = new ASTNode("keyword"); $$->createChild("name", "friend"); }
    | GOTO { $$ = new ASTNode("keyword"); $$->createChild("name", "goto"); }
    | IF { $$ = new ASTNode("keyword"); $$->createChild("name", "if"); }
    | INLINE { $$ = new ASTNode("keyword"); $$->createChild("name", "inline"); }
    | INT { $$ = new ASTNode("keyword"); $$->createChild("name", "int"); }
    | LONG { $$ = new ASTNode("keyword"); $$->createChild("name", "long"); }
    | MUTABLE { $$ = new ASTNode("keyword"); $$->createChild("name", "mutable"); }
    | NAMESPACE { $$ = new ASTNode("keyword"); $$->createChild("name", "namespace"); }
    | NEW { $$ = new ASTNode("keyword"); $$->createChild("name", "new"); }
    | NOEXCEPT { $$ = new ASTNode("keyword"); $$->createChild("name", "noexcept"); }
    | NULLPTR { $$ = new ASTNode("keyword"); $$->createChild("name", "nullptr"); }
    | OPERATOR { $$ = new ASTNode("keyword"); $$->createChild("name", "operator"); }
    | PRIVATE { $$ = new ASTNode("keyword"); $$->createChild("name", "private"); }
    | PROTECTED { $$ = new ASTNode("keyword"); $$->createChild("name", "protected"); }
    | PUBLIC { $$ = new ASTNode("keyword"); $$->createChild("name", "public"); }
    | REGISTER { $$ = new ASTNode("keyword"); $$->createChild("name", "register"); }
    | REINTERPRET_CAST { $$ = new ASTNode("keyword"); $$->createChild("name", "reinterpret_cast"); }
    | RETURN { $$ = new ASTNode("keyword"); $$->createChild("name", "return"); }
    | SHORT { $$ = new ASTNode("keyword"); $$->createChild("name", "short"); }
    | SIGNED { $$ = new ASTNode("keyword"); $$->createChild("name", "signed"); }
    | SIZEOF { $$ = new ASTNode("keyword"); $$->createChild("name", "sizeof"); }
    | STATIC { $$ = new ASTNode("keyword"); $$->createChild("name", "static"); }
    | STATIC_ASSERT { $$ = new ASTNode("keyword"); $$->createChild("name", "static_assert"); }
    | STATIC_CAST { $$ = new ASTNode("keyword"); $$->createChild("name", "static_cast"); }
    | STRUCT { $$ = new ASTNode("keyword"); $$->createChild("name", "struct"); }
    | SWITCH { $$ = new ASTNode("keyword"); $$->createChild("name", "switch"); }
    | TEMPLATE { $$ = new ASTNode("keyword"); $$->createChild("name", "template"); }
    | THIS { $$ = new ASTNode("keyword"); $$->createChild("name", "this"); }
    | THREAD_LOCAL { $$ = new ASTNode("keyword"); $$->createChild("name", "thread_local"); }
    | THROW { $$ = new ASTNode("keyword"); $$->createChild("name", "throw"); }
    | TRUE { $$ = new ASTNode("keyword"); $$->createChild("name", "true"); }
    | TRY { $$ = new ASTNode("keyword"); $$->createChild("name", "try"); }
    | TYPEDEF { $$ = new ASTNode("keyword"); $$->createChild("name", "typedef"); }
    | TYPEID { $$ = new ASTNode("keyword"); $$->createChild("name", "typeid"); }
    | TYPENAME { $$ = new ASTNode("keyword"); $$->createChild("name", "typename"); }
    | UNION { $$ = new ASTNode("keyword"); $$->createChild("name", "union"); }
    | UNSIGNED { $$ = new ASTNode("keyword"); $$->createChild("name", "unsigned"); }
    | USING { $$ = new ASTNode("keyword"); $$->createChild("name", "using"); }
    | VIRTUAL { $$ = new ASTNode("keyword"); $$->createChild("name", "virtual"); }
    | VOID { $$ = new ASTNode("keyword"); $$->createChild("name", "void"); }
    | VOLATILE { $$ = new ASTNode("keyword"); $$->createChild("name", "volatile"); }
    | WCHAR_T { $$ = new ASTNode("keyword"); $$->createChild("name", "wchar_t"); }
    | WHILE { $$ = new ASTNode("keyword"); $$->createChild("name", "while"); }
;

operator_token:
    preprocessing_op_or_punc
;

punctuator:
    preprocessing_op_or_punc
;

preprocessing_op_or_punc:
    '{' { $$ = new ASTNode("NAME"); $$->createChild("action", "{"); }
    | '}' { $$ = new ASTNode("NAME"); $$->createChild("action", "}"); }
    | '[' { $$ = new ASTNode("NAME"); $$->createChild("action", "["); }
    | ']' { $$ = new ASTNode("NAME"); $$->createChild("action", "]"); }
    | '#' { $$ = new ASTNode("NAME"); $$->createChild("action", "#"); }
    | '##' { $$ = new ASTNode("NAME"); $$->createChild("action", "##"); }
    | '(' { $$ = new ASTNode("NAME"); $$->createChild("action", "("); }
    | ')' { $$ = new ASTNode("NAME"); $$->createChild("action", ")"); }
    | '<:' { $$ = new ASTNode("NAME"); $$->createChild("action", "<:"); }
    | ':>' { $$ = new ASTNode("NAME"); $$->createChild("action", ":>"); }
    | '<%' { $$ = new ASTNode("NAME"); $$->createChild("action", "<%"); }
    | '%>' { $$ = new ASTNode("NAME"); $$->createChild("action", "%>"); }
    | '%:' { $$ = new ASTNode("NAME"); $$->createChild("action", "%:"); }
    | '%:%:' { $$ = new ASTNode("NAME"); $$->createChild("action", "%:%:"); }
    | ';' { $$ = new ASTNode("NAME"); $$->createChild("action", ";"); }
    | ':' { $$ = new ASTNode("NAME"); $$->createChild("action", ":"); }
    | '...' { $$ = new ASTNode("NAME"); $$->createChild("action", "..."); }
    | 'new' { $$ = new ASTNode("NAME"); $$->createChild("action", "new"); }
    | 'delete' { $$ = new ASTNode("NAME"); $$->createChild("action", "delete"); }
    | '?' { $$ = new ASTNode("NAME"); $$->createChild("action", "?"); }
    | '::' { $$ = new ASTNode("NAME"); $$->createChild("action", "::"); }
    | '.' { $$ = new ASTNode("NAME"); $$->createChild("action", "."); }
    | '.*' { $$ = new ASTNode("NAME"); $$->createChild("action", ".*"); }
    | '+' { $$ = new ASTNode("NAME"); $$->createChild("action", "+"); }
    | '-' { $$ = new ASTNode("NAME"); $$->createChild("action", "-"); }
    | '*' { $$ = new ASTNode("NAME"); $$->createChild("action", "*"); }
    | '/' { $$ = new ASTNode("NAME"); $$->createChild("action", "/"); }
    | '%' { $$ = new ASTNode("NAME"); $$->createChild("action", "%"); }
    | '^' { $$ = new ASTNode("NAME"); $$->createChild("action", "^"); }
    | '&' { $$ = new ASTNode("NAME"); $$->createChild("action", "&"); }
    | '|' { $$ = new ASTNode("NAME"); $$->createChild("action", "|"); }
    | '~' { $$ = new ASTNode("NAME"); $$->createChild("action", "~"); }
    | '!' { $$ = new ASTNode("NAME"); $$->createChild("action", "!"); }
    | '=' { $$ = new ASTNode("NAME"); $$->createChild("action", "="); }
    | '<' { $$ = new ASTNode("NAME"); $$->createChild("action", "<"); }
    | '>' { $$ = new ASTNode("NAME"); $$->createChild("action", ">"); }
    | '+=' { $$ = new ASTNode("NAME"); $$->createChild("action", "+="); }
    | '-=' { $$ = new ASTNode("NAME"); $$->createChild("action", "-="); }
    | '*=' { $$ = new ASTNode("NAME"); $$->createChild("action", "*="); }
    | '/=' { $$ = new ASTNode("NAME"); $$->createChild("action", "/="); }
    | '%=' { $$ = new ASTNode("NAME"); $$->createChild("action", "%="); }
    | '^=' { $$ = new ASTNode("NAME"); $$->createChild("action", "^="); }
    | '&=' { $$ = new ASTNode("NAME"); $$->createChild("action", "&="); }
    | '|=' { $$ = new ASTNode("NAME"); $$->createChild("action", "|="); }
    | '<<' { $$ = new ASTNode("NAME"); $$->createChild("action", "<<"); }
    | '>>' { $$ = new ASTNode("NAME"); $$->createChild("action", ">>"); }
    | '<<=' { $$ = new ASTNode("NAME"); $$->createChild("action", "<<="); }
    | '>>=' { $$ = new ASTNode("NAME"); $$->createChild("action", ">>="); }
    | '==' { $$ = new ASTNode("NAME"); $$->createChild("action", "=="); }
    | '!=' { $$ = new ASTNode("NAME"); $$->createChild("action", "!="); }
    | '<=' { $$ = new ASTNode("NAME"); $$->createChild("action", "<="); }
    | '>=' { $$ = new ASTNode("NAME"); $$->createChild("action", ">="); }
    | '&&' { $$ = new ASTNode("NAME"); $$->createChild("action", "&&"); }
    | '||' { $$ = new ASTNode("NAME"); $$->createChild("action", "||"); }
    | '++' { $$ = new ASTNode("NAME"); $$->createChild("action", "++"); }
    | '--' { $$ = new ASTNode("NAME"); $$->createChild("action", "--"); }
    | ',' { $$ = new ASTNode("NAME"); $$->createChild("action", ","); }
    | '->*' { $$ = new ASTNode("NAME"); $$->createChild("action", "->*"); }
    | '->' { $$ = new ASTNode("NAME"); $$->createChild("action", "->"); }
    | 'and' { $$ = new ASTNode("NAME"); $$->createChild("action", "and"); }
    | 'and_eq' { $$ = new ASTNode("NAME"); $$->createChild("action", "and_eq"); }
    | 'bitand' { $$ = new ASTNode("NAME"); $$->createChild("action", "bitand"); }
    | 'bitor' { $$ = new ASTNode("NAME"); $$->createChild("action", "bitor"); }
    | 'compl' { $$ = new ASTNode("NAME"); $$->createChild("action", "compl"); }
    | 'not' { $$ = new ASTNode("NAME"); $$->createChild("action", "not"); }
    | 'not_eq' { $$ = new ASTNode("NAME"); $$->createChild("action", "not_eq"); }
    | 'or' { $$ = new ASTNode("NAME"); $$->createChild("action", "or"); }
    | 'or_eq' { $$ = new ASTNode("NAME"); $$->createChild("action", "or_eq"); }
    | 'xor' { $$ = new ASTNode("NAME"); $$->createChild("action", "xor"); }
    | 'xor_eq' { $$ = new ASTNode("NAME"); $$->createChild("action", "xor_eq"); }
;

// Literals
literal:
    integer_literal { $$ = $1; }
    | character_literal { $$ = $1; }
    | floating_literal { $$ = $1; }
    | string_literal { $$ = $1; }
    | boolean_literal { $$ = $1; }
    | pointer_literal { $$ = $1; }
    | user_defined_literal { $$ = $1; }
;

// Integer Literals
integer_literal:
    decimal_literal integer_suffix_opt { $$ = new ASTNode("integer_literal"); $$->addChild($1); $$->addChild($2); }
    | octal_literal integer_suffix_opt { $$ = new ASTNode("integer_literal"); $$->addChild($1); $$->addChild($2); }
    | hexadecimal_literal integer_suffix_opt { $$ = new ASTNode("integer_literal"); $$->addChild($1); $$->addChild($2); }
;

decimal_literal:
    nonzero_digit { $$ = new ASTNode("decimal_literal"); $$->createChild("digit", $1); }
    | decimal_literal digit { $$ = $1; $$->createChild("digit", $2); }
;

octal_literal:
    '0' { $$ = new ASTNode("octal_literal"); $$->createChild("digit", "0"); }
    | octal_literal octal_digit { $$ = $1; $$->createChild("digit", $2); }
;

hexadecimal_literal:
    '0' 'x' hexadecimal_digit { $$ = new ASTNode("hexadecimal_literal"); $$->createChild("digit", $3); }
    | '0' 'X' hexadecimal_digit { $$ = new ASTNode("hexadecimal_literal"); $$->createChild("digit", $3); }
    | hexadecimal_literal hexadecimal_digit { $$ = $1; $$->createChild("digit", $2); }
;

nonzero_digit:
    '1' { $$ = new ASTNode("nonzero_digit"); $$->createChild("digit", "1"); }
    | '2' { $$ = new ASTNode("nonzero_digit"); $$->createChild("digit", "2"); }
    | '3' { $$ = new ASTNode("nonzero_digit"); $$->createChild("digit", "3"); }
    | '4' { $$ = new ASTNode("nonzero_digit"); $$->createChild("digit", "4"); }
    | '5' { $$ = new ASTNode("nonzero_digit"); $$->createChild("digit", "5"); }
    | '6' { $$ = new ASTNode("nonzero_digit"); $$->createChild("digit", "6"); }
    | '7' { $$ = new ASTNode("nonzero_digit"); $$->createChild("digit", "7"); }
    | '8' { $$ = new ASTNode("nonzero_digit"); $$->createChild("digit", "8"); }
    | '9' { $$ = new ASTNode("nonzero_digit"); $$->createChild("digit", "9"); }
;

octal_digit:
    '0' { $$ = new ASTNode("octal_digit"); $$->createChild("digit", "0"); }
    | '1' { $$ = new ASTNode("octal_digit"); $$->createChild("digit", "1"); }
    | '2' { $$ = new ASTNode("octal_digit"); $$->createChild("digit", "2"); }
    | '3' { $$ = new ASTNode("octal_digit"); $$->createChild("digit", "3"); }
    | '4' { $$ = new ASTNode("octal_digit"); $$->createChild("digit", "4"); }
    | '5' { $$ = new ASTNode("octal_digit"); $$->createChild("digit", "5"); }
    | '6' { $$ = new ASTNode("octal_digit"); $$->createChild("digit", "6"); }
    | '7' { $$ = new ASTNode("octal_digit"); $$->createChild("digit", "7"); }
;

hexadecimal_digit:
    '0' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "0"); }
    | '1' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "1"); }
    | '2' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "2"); }
    | '3' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "3"); }
    | '4' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "4"); }
    | '5' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "5"); }
    | '6' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "6"); }
    | '7' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "7"); }
    | '8' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "8"); }
    | '9' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "9"); }
    | 'a' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "a"); }
    | 'b' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "b"); }
    | 'c' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "c"); }
    | 'd' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "d"); }
    | 'e' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "e"); }
    | 'f' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "f"); }
    | 'A' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "A"); }
    | 'B' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "B"); }
    | 'C' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "C"); }
    | 'D' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "D"); }
    | 'E' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "E"); }
    | 'F' { $$ = new ASTNode("hexadecimal_digit"); $$->createChild("digit", "F"); }
;

integer_suffix:
    unsigned_suffix long_suffix_opt { $$ = new ASTNode("integer_suffix"); $$->addChild($1); $$->addChild($2); }
    | unsigned_suffix long_long_suffix_opt { $$ = new ASTNode("integer_suffix"); $$->addChild($1); $$->addChild($2); }
    | long_suffix unsigned_suffix_opt { $$ = new ASTNode("integer_suffix"); $$->addChild($1); $$->addChild($2); }
    | long_long_suffix unsigned_suffix_opt { $$ = new ASTNode("integer_suffix"); $$->addChild($1); $$->addChild($2); }
;

unsigned_suffix:
    'u' { $$ = new ASTNode("unsigned_suffix"); $$->createChild("suffix", "u"); }
    | 'U' { $$ = new ASTNode("unsigned_suffix"); $$->createChild("suffix", "U"); }
;

long_suffix:
    'l' { $$ = new ASTNode("long_suffix"); $$->createChild("suffix", "l"); }
    | 'L' { $$ = new ASTNode("long_suffix"); $$->createChild("suffix", "L"); }
;

long_long_suffix:
    'll' { $$ = new ASTNode("long_long_suffix"); $$->createChild("suffix", "ll"); }
    | 'LL' { $$ = new ASTNode("long_long_suffix"); $$->createChild("suffix", "LL"); }
;

// Character Literals
character_literal:
    '\'' c_char_sequence '\'' { $$ = new ASTNode("character_literal"); $$->addChild($2); }
    | 'u' '\'' c_char_sequence '\'' { $$ = new ASTNode("character_literal"); $$->addChild($3); }
    | 'U' '\'' c_char_sequence '\'' { $$ = new ASTNode("character_literal"); $$->addChild($3); }
    | 'L' '\'' c_char_sequence '\'' { $$ = new ASTNode("character_literal"); $$->addChild($3); }
;

c_char_sequence:
    c_char { $$ = new ASTNode("c_char_sequence"); $$->createChild("char", $1); }
    | c_char_sequence c_char { $$ = $1; $$->createChild("char", $2); }
;

c_char:
    // any member of the source character set except the single quote ', backslash \, or new-line character
    // escape-sequence
    // universal-character-name
    // Placeholder for actual implementation
    { $$ = new ASTNode("c_char"); }
;

escape_sequence:
    simple_escape_sequence { $$ = $1; }
    | octal_escape_sequence { $$ = $1; }
    | hexadecimal_escape_sequence { $$ = $1; }
;

simple_escape_sequence:
    '\\' '\'' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\'"); }
    | '\\' '\"' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\\""); }
    | '\\' '\?' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\?"); }
    | '\\' '\\' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\\\"); }
    | '\\' 'a' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\a"); }
    | '\\' 'b' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\b"); }
    | '\\' 'f' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\f"); }
    | '\\' 'n' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\n"); }
    | '\\' 'r' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\r"); }
    | '\\' 't' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\t"); }
    | '\\' 'v' { $$ = new ASTNode("simple_escape_sequence"); $$->createChild("escape", "\\v"); }
;

octal_escape_sequence:
    '\\' octal_digit { $$ = new ASTNode("octal_escape_sequence"); $$->createChild("escape", "\\" + std::string(1, $2)); }
    | '\\' octal_digit octal_digit { $$ = new ASTNode("octal_escape_sequence"); $$->createChild("escape", "\\" + std::string(1, $2) + std::string(1, $3)); }
    | '\\' octal_digit octal_digit octal_digit { $$ = new ASTNode("octal_escape_sequence"); $$->createChild("escape", "\\" + std::string(1, $2) + std::string(1, $3) + std::string(1, $4)); }
;

hexadecimal_escape_sequence:
    '\\' 'x' hexadecimal_digit { $$ = new ASTNode("hexadecimal_escape_sequence"); $$->createChild("escape", "\\x" + std::string(1, $3)); }
    | hexadecimal_escape_sequence hexadecimal_digit { $$ = $1; $$->createChild("escape", std::string(1, $2)); }
;

// Floating Literals
floating_literal:
    fractional_constant exponent_part_opt floating_suffix_opt { $$ = new ASTNode("floating_literal"); $$->addChild($1); $$->addChild($2); $$->addChild($3); }
    | digit_sequence exponent_part floating_suffix_opt { $$ = new ASTNode("floating_literal"); $$->addChild($1); $$->addChild($2); $$->addChild($3); }
;

fractional_constant:
    digit_sequence_opt '.' digit_sequence { $$ = new ASTNode("fractional_constant"); $$->addChild($1); $$->addChild($3); }
    | digit_sequence '.' { $$ = new ASTNode("fractional_constant"); $$->addChild($1); }
;

exponent_part:
    'e' sign_opt digit_sequence { $$ = new ASTNode("exponent_part"); $$->addChild($2); $$->addChild($3); }
    | 'E' sign_opt digit_sequence { $$ = new ASTNode("exponent_part"); $$->addChild($2); $$->addChild($3); }
;

sign:
    '+' { $$ = new ASTNode("sign"); $$->createChild("sign", "+"); }
    | '-' { $$ = new ASTNode("sign"); $$->createChild("sign", "-"); }
;

digit_sequence:
    digit { $$ = new ASTNode("digit_sequence"); $$->createChild("digit", $1); }
    | digit_sequence digit { $$ = $1; $$->createChild("digit", $2); }
;

floating_suffix:
    'f' { $$ = new ASTNode("floating_suffix"); $$->createChild("suffix", "f"); }
    | 'l' { $$ = new ASTNode("floating_suffix"); $$->createChild("suffix", "l"); }
    | 'F' { $$ = new ASTNode("floating_suffix"); $$->createChild("suffix", "F"); }
    | 'L' { $$ = new ASTNode("floating_suffix"); $$->createChild("suffix", "L"); }
;

// String Literals
string_literal:
    encoding_prefix_opt '"' s_char_sequence_opt '"' { $$ = new ASTNode("string_literal"); $$->addChild($1); $$->addChild($3); }
    | encoding_prefix_opt 'R' raw_string { $$ = new ASTNode("string_literal"); $$->addChild($1); $$->addChild($3); }
;

encoding_prefix:
    'u8' { $$ = new ASTNode("encoding_prefix"); $$->createChild("prefix", "u8"); }
    | 'u' { $$ = new ASTNode("encoding_prefix"); $$->createChild("prefix", "u"); }
    | 'U' { $$ = new ASTNode("encoding_prefix"); $$->createChild("prefix", "U"); }
    | 'L' { $$ = new ASTNode("encoding_prefix"); $$->createChild("prefix", "L"); }
;

s_char_sequence:
    s_char { $$ = new ASTNode("s_char_sequence"); $$->createChild("char", $1); }
    | s_char_sequence s_char { $$ = $1; $$->createChild("char", $2); }
;

s_char:
    // any member of the source character set except the double-quote ", backslash \, or new-line character
    // escape-sequence
    // universal-character-name
    // Placeholder for actual implementation
    { $$ = new ASTNode("s_char"); }
;

raw_string:
    '"' d_char_sequence_opt LPAREN r_char_sequence_opt RPAREN d_char_sequence_opt '"' { $$ = new ASTNode("raw_string"); $$->addChild($2); $$->addChild($4); $$->addChild($6); }
;

r_char_sequence:
    r_char { $$ = new ASTNode("r_char_sequence"); $$->createChild("char", $1); }
    | r_char_sequence r_char { $$ = $1; $$->createChild("char", $2); }
;

r_char:
    // any member of the source character set, except a right parenthesis ) followed by the initial d_char-sequence (which may be empty) followed by a double quote ".
    // Placeholder for actual implementation
    { $$ = new ASTNode("r_char"); }
;

d_char_sequence:
    d_char { $$ = new ASTNode("d_char_sequence"); $$->createChild("char", $1); }
    | d_char_sequence d_char { $$ = $1; $$->createChild("char", $2); }
;

d_char:
    // any member of the basic source character set, except: space, the left parenthesis (, the right parenthesis ), the backslash \, and the control characters representing horizontal tab, vertical tab, form feed, and newline.
    // Placeholder for actual implementation
    { $$ = new ASTNode("d_char"); }
;

// Boolean Literals
boolean_literal:
    FALSE { $$ = new ASTNode("boolean_literal"); $$->createChild("value", "false"); }
    | TRUE { $$ = new ASTNode("boolean_literal"); $$->createChild("value", "true"); }
;

// Pointer Literals
pointer_literal:
    NULLPTR { $$ = new ASTNode("pointer_literal"); $$->createChild("value", "nullptr"); }
;

// User-Defined Literals
user_defined_literal:
    user_defined_integer_literal { $$ = $1; }
    | user_defined_floating_literal { $$ = $1; }
    | user_defined_string_literal { $$ = $1; }
    | user_defined_character_literal { $$ = $1; }
;

user_defined_integer_literal:
    decimal_literal ud_suffix { $$ = new ASTNode("user_defined_integer_literal"); $$->addChild($1); $$->addChild($2); }
    | octal_literal ud_suffix { $$ = new ASTNode("user_defined_integer_literal"); $$->addChild($1); $$->addChild($2); }
    | hexadecimal_literal ud_suffix { $$ = new ASTNode("user_defined_integer_literal"); $$->addChild($1); $$->addChild($2); }
;

user_defined_floating_literal:
    fractional_constant exponent_part_opt ud_suffix { $$ = new ASTNode("user_defined_floating_literal"); $$->addChild($1); $$->addChild($2); $$->addChild($3); }
    | digit_sequence exponent_part ud_suffix { $$ = new ASTNode("user_defined_floating_literal"); $$->addChild($1); $$->addChild($2); $$->addChild($3); }
;

user_defined_string_literal:
    string_literal ud_suffix { $$ = new ASTNode("user_defined_string_literal"); $$->addChild($1); $$->addChild($2); }
;

user_defined_character_literal:
    character_literal ud_suffix { $$ = new ASTNode("user_defined_character_literal"); $$->addChild($1); $$->addChild($2); }
;

ud_suffix:
    IDENTIFIER { $$ = new ASTNode("ud_suffix"); $$->createChild("suffix", $1); }



// Expressions/////////////////////////////////////////////////////


// Primary Expressions
primary_expression:
    literal { $$ = $1; }
    | THIS { $$ = new ASTNode("this"); }
    | LPAREN expression RPAREN { $$ = $2; }
    | id_expression { $$ = $1; }
    /* | lambda_expression { $$ = new ASTNode("lambda_expression"); } // Placeholder */
;

// ID Expressions
id_expression:
    unqualified_id { $$ = $1; }
    /* | qualified_id { $$ = $1; } */
;

unqualified_id:
    IDENTIFIER { $$ = new ASTNode("identifier"); $$->createChild("name", $1); }
    | operator_function_id { $$ = new ASTNode("operator_function_id"); } // Placeholder
    | conversion_function_id { $$ = new ASTNode("conversion_function_id"); } // Placeholder
    | literal_operator_id { $$ = new ASTNode("literal_operator_id"); } // Placeholder
    | '~' class_name { $$ = new ASTNode("destructor"); $$->createChild("class", $2); }
    | '~' decltype_specifier { $$ = new ASTNode("destructor"); $$->createChild("decltype", $2); } // Placeholder
    /* | template_id { $$ = new ASTNode("template_id"); } // Placeholder */
;

/* qualified_id:
    COLONCOLON_opt nested_name_specifier template_opt unqualified_id { $$ = new ASTNode("qualified_id"); $$->addChild($2); $$->addChild($4); }
    | COLONCOLON IDENTIFIER { $$ = new ASTNode("qualified_id"); $$->createChild("name", $2); }
    | COLONCOLON operator_function_id { $$ = new ASTNode("qualified_operator_function_id"); } // Placeholder
    | COLONCOLON literal_operator_id { $$ = new ASTNode("qualified_literal_operator_id"); } // Placeholder
    | COLONCOLON template_id { $$ = new ASTNode("qualified_template_id"); } // Placeholder
;

nested_name_specifier:
    type_name COLONCOLON { $$ = new ASTNode("nested_name_specifier"); $$->createChild("type", $1); }
    | namespace_name COLONCOLON { $$ = new ASTNode("nested_name_specifier"); $$->createChild("namespace", $1); }
    | decltype_specifier COLONCOLON { $$ = new ASTNode("nested_name_specifier"); $$->createChild("decltype", $1); } // Placeholder
    | nested_name_specifier IDENTIFIER COLONCOLON { $$ = $1; $$->createChild("name", $2); }
    | nested_name_specifier template_opt simple_template_id COLONCOLON { $$ = $1; $$->addChild($3); }
; */

// Lambda Expressions/////////////////////////////////
/*
lambda_expression:
    lambda_introducer lambda_declarator_opt compound_statement { $$ = new ASTNode("lambda_expression"); $$->addChild($1); $$->addChild($2); $$->addChild($3); }
;

lambda_introducer:
    LBRACKET lambda_capture_opt RBRACKET { $$ = new ASTNode("lambda_introducer"); $$->addChild($2); }
;

lambda_capture:
    capture_default { $$ = $1; }
    | capture_list { $$ = $1; }
    | capture_default COMMA capture_list { $$ = new ASTNode("lambda_capture"); $$->addChild($1); $$->addChild($3); }
;

capture_default:
    '&' { $$ = new ASTNode("capture_default"); $$->createChild("type", "&"); }
    | '=' { $$ = new ASTNode("capture_default"); $$->createChild("type", "="); }
;

capture_list:
    capture ELLIPSIS_opt { $$ = new ASTNode("capture_list"); $$->addChild($1); }
    | capture_list COMMA capture ELLIPSIS_opt { $$ = $1; $$->addChild($3); }
;

capture:
    IDENTIFIER { $$ = new ASTNode("capture"); $$->createChild("name", $1); }
    | '&' IDENTIFIER { $$ = new ASTNode("capture"); $$->createChild("name", $2); $$->createChild("type", "&"); }
    | THIS { $$ = new ASTNode("capture"); $$->createChild("type", "this"); }
;

lambda_declarator:
    LPAREN parameter_declaration_clause RPAREN mutable_opt exception_specification_opt attribute_specifier_seq_opt trailing_return_type_opt { $$ = new ASTNode("lambda_declarator"); $$->addChild($2); $$->addChild($4); $$->addChild($5); $$->addChild($6); $$->addChild($7); }
;*/
//LAMBDA END/////////////////////////////////////////


// Postfix Expressions
postfix_expression:
    primary_expression { $$ = $1; }
    | postfix_expression LBRACKET expression RBRACKET { $$ = new ASTNode("array_access"); $$->addChild($1); $$->addChild($3); }
    | postfix_expression LBRACKET braced_init_list_opt RBRACKET { $$ = new ASTNode("array_access"); $$->addChild($1); $$->addChild($3); }
    | postfix_expression LPAREN expression_list_opt RPAREN { $$ = new ASTNode("function_call"); $$->addChild($1); $$->addChild($3); }
    | simple_type_specifier LPAREN expression_list RPAREN { $$ = new ASTNode("type_cast"); $$->addChild($1); $$->addChild($3); }
    | typename_specifier LPAREN expression_list RPAREN { $$ = new ASTNode("type_cast"); $$->addChild($1); $$->addChild($3); }
    | simple_type_specifier braced_init_list { $$ = new ASTNode("type_cast"); $$->addChild($1); $$->addChild($2); }
    | typename_specifier braced_init_list { $$ = new ASTNode("type_cast"); $$->addChild($1); $$->addChild($2); }
    | postfix_expression DOT template_opt id_expression { $$ = new ASTNode("member_access"); $$->addChild($1); $$->addChild($3); }
    | postfix_expression ARROW template_opt id_expression { $$ = new ASTNode("member_access"); $$->addChild($1); $$->addChild($3); }
    | postfix_expression DOT pseudo_destructor_name { $$ = new ASTNode("pseudo_destructor"); $$->addChild($1); $$->addChild($3); }
    | postfix_expression ARROW pseudo_destructor_name { $$ = new ASTNode("pseudo_destructor"); $$->addChild($1); $$->addChild($3); }
    | postfix_expression PLUSPLUS { $$ = new ASTNode("post_increment"); $$->addChild($1); }
    | postfix_expression MINUSMINUS { $$ = new ASTNode("post_decrement"); $$->addChild($1); }
    /* | DYNAMIC_CAST LT type_id GT LPAREN expression RPAREN { $$ = new ASTNode("dynamic_cast"); $$->addChild($3); $$->addChild($6); }
    | STATIC_CAST LT type_id GT LPAREN expression RPAREN { $$ = new ASTNode("static_cast"); $$->addChild($3); $$->addChild($6); }
    | REINTERPRET_CAST LT type_id GT LPAREN expression RPAREN { $$ = new ASTNode("reinterpret_cast"); $$->addChild($3); $$->addChild($6); }
    | CONST_CAST LT type_id GT LPAREN expression RPAREN { $$ = new ASTNode("const_cast"); $$->addChild($3); $$->addChild($6); }
    | TYPEID LPAREN expression RPAREN { $$ = new ASTNode("typeid"); $$->addChild($3); }
    | TYPEID LPAREN type_id RPAREN { $$ = new ASTNode("typeid"); $$->addChild($3); } */
;

expression_list:
    initializer_list { $$ = $1; }
;

// Pseudo Destructor Name
pseudo_destructor_name:
    COLONCOLON_opt nested_name_specifier_opt type_name COLONCOLON TILDE type_name { $$ = new ASTNode("pseudo_destructor_name"); $$->addChild($2); $$->addChild($3); $$->addChild($6); }
    | COLONCOLON_opt nested_name_specifier template simple_template_id COLONCOLON TILDE type_name { $$ = new ASTNode("pseudo_destructor_name"); $$->addChild($2); $$->addChild($3); $$->addChild($6); }
    | COLONCOLON_opt nested_name_specifier_opt TILDE type_name { $$ = new ASTNode("pseudo_destructor_name"); $$->addChild($2); $$->addChild($4); }
    | TILDE decltype_specifier { $$ = new ASTNode("pseudo_destructor_name"); $$->addChild($2); }
;

// Unary Expressions
unary_expression:
    postfix_expression { $$ = $1; }
    | PLUSPLUS cast_expression { $$ = new ASTNode("pre_increment"); $$->addChild($2); }
    | MINUSMINUS cast_expression { $$ = new ASTNode("pre_decrement"); $$->addChild($2); }
    | unary_operator cast_expression { $$ = new ASTNode("unary_operator"); $$->createChild("operator", $1); $$->addChild($2); }
    | SIZEOF unary_expression { $$ = new ASTNode("sizeof"); $$->addChild($2); }
    | SIZEOF LPAREN type_id RPAREN { $$ = new ASTNode("sizeof"); $$->addChild($3); }
    | SIZEOF ELLIPSIS LPAREN IDENTIFIER RPAREN { $$ = new ASTNode("sizeof_pack"); $$->createChild("identifier", $4); }
    | ALIGNOF LPAREN type_id RPAREN { $$ = new ASTNode("alignof"); $$->addChild($3); }
    | noexcept_expression { $$ = $1; }
    | new_expression { $$ = $1; }
    | delete_expression { $$ = $1; }
;

unary_operator:
    MULTIPLY { $$ = "*"; }
    | AMPERSAND { $$ = "&"; }
    | PLUS { $$ = "+"; }
    | MINUS { $$ = "-"; }
    | NOT { $$ = "!"; }
    | TILDE { $$ = "~"; }
;

// New Expressions
new_expression:
    COLONCOLON_opt NEW new_placement_opt new_type_id new_initializer_opt { $$ = new ASTNode("new_expression"); $$->addChild($3); $$->addChild($4); $$->addChild($5); }
    | COLONCOLON_opt NEW new_placement_opt LPAREN type_id RPAREN new_initializer_opt { $$ = new ASTNode("new_expression"); $$->addChild($3); $$->addChild($5); $$->addChild($7); }
;

new_placement:
    LPAREN expression_list RPAREN { $$ = new ASTNode("new_placement"); $$->addChild($2); }
;

new_type_id:
    type_specifier_seq new_declarator_opt { $$ = new ASTNode("new_type_id"); $$->addChild($1); $$->addChild($2); }
;

new_declarator:
    ptr_operator new_declarator_opt { $$ = new ASTNode("new_declarator"); $$->addChild($1); $$->addChild($2); }
    | noptr_new_declarator { $$ = $1; }
;

noptr_new_declarator:
    LBRACKET expression RBRACKET attribute_specifier_seq_opt { $$ = new ASTNode("noptr_new_declarator"); $$->addChild($2); $$->addChild($4); }
    | noptr_new_declarator LBRACKET constant_expression RBRACKET attribute_specifier_seq_opt { $$ = $1; $$->addChild($3); $$->addChild($5); }
;

new_initializer:
    LPAREN expression_list_opt RPAREN { $$ = new ASTNode("new_initializer"); $$->addChild($2); }
    | braced_init_list { $$ = $1; }
;

// Delete Expressions
delete_expression:
    COLONCOLON_opt DELETE cast_expression { $$ = new ASTNode("delete_expression"); $$->addChild($3); }
    | COLONCOLON_opt DELETE LBRACKET RBRACKET cast_expression { $$ = new ASTNode("delete_array_expression"); $$->addChild($5); }
;

// Noexcept Expressions
noexcept_expression:
    NOEXCEPT LPAREN expression RPAREN { $$ = new ASTNode("noexcept_expression"); $$->addChild($3); }
;

// Cast Expressions
cast_expression:
    unary_expression { $$ = $1; }
    | LPAREN type_id RPAREN cast_expression { $$ = new ASTNode("cast_expression"); $$->addChild($2); $$->addChild($4); }
;

// Pointer-to-Member Expressions
pm_expression:
    cast_expression { $$ = $1; }
    | pm_expression DOTSTAR cast_expression { $$ = new ASTNode("pm_expression"); $$->addChild($1); $$->addChild($3); }
    | pm_expression ARROWSTAR cast_expression { $$ = new ASTNode("pm_expression"); $$->addChild($1); $$->addChild($3); }
;

multiplicative_expression:
    pm_expression { $$ = $1; }
    | multiplicative_expression MULTIPLY pm_expression { $$ = new ASTNode("*"); $$->addChild($1); $$->addChild($3); }
    | multiplicative_expression DIVIDE pm_expression { $$ = new ASTNode("/"); $$->addChild($1); $$->addChild($3); }
    | multiplicative_expression MODULO pm_expression { $$ = new ASTNode("%"); $$->addChild($1); $$->addChild($3); }
;

additive_expression:
    multiplicative_expression { $$ = $1; }
    | additive_expression PLUS multiplicative_expression { $$ = new ASTNode("+"); $$->addChild($1); $$->addChild($3); }
    | additive_expression MINUS multiplicative_expression { $$ = new ASTNode("-"); $$->addChild($1); $$->addChild($3); }
;

shift_expression:
    additive_expression { $$ = $1; }
    | shift_expression LEFT_SHIFT additive_expression { $$ = new ASTNode("<<"); $$->addChild($1); $$->addChild($3); }
    | shift_expression RIGHT_SHIFT additive_expression { $$ = new ASTNode(">>"); $$->addChild($1); $$->addChild($3); }
;

relational_expression:
    shift_expression { $$ = $1; }
    | relational_expression LESS shift_expression { $$ = new ASTNode("<"); $$->addChild($1); $$->addChild($3); }
    | relational_expression GREATER shift_expression { $$ = new ASTNode(">"); $$->addChild($1); $$->addChild($3); }
    | relational_expression LESS_EQUAL shift_expression { $$ = new ASTNode("<="); $$->addChild($1); $$->addChild($3); }
    | relational_expression GREATER_EQUAL shift_expression { $$ = new ASTNode(">="); $$->addChild($1); $$->addChild($3); }
;

equality_expression:
    relational_expression { $$ = $1; }
    | equality_expression EQUAL relational_expression { $$ = new ASTNode("=="); $$->addChild($1); $$->addChild($3); }
    | equality_expression NOT_EQUAL relational_expression { $$ = new ASTNode("!="); $$->addChild($1); $$->addChild($3); }
;

and_expression:
    equality_expression { $$ = $1; }
    | and_expression AND equality_expression { $$ = new ASTNode("&"); $$->addChild($1); $$->addChild($3); }
;

exclusive_or_expression:
    and_expression { $$ = $1; }
    | exclusive_or_expression '^' and_expression { $$ = new ASTNode("^"); $$->addChild($1); $$->addChild($3); }
;

inclusive_or_expression:
    exclusive_or_expression { $$ = $1; }
    | inclusive_or_expression '|' exclusive_or_expression { $$ = new ASTNode("|"); $$->addChild($1); $$->addChild($3); }
;

logical_and_expression:
    inclusive_or_expression { $$ = $1; }
    | logical_and_expression AND inclusive_or_expression { $$ = new ASTNode("&&"); $$->addChild($1); $$->addChild($3); }
;

logical_or_expression:
    logical_and_expression { $$ = $1; }
    | logical_or_expression OR logical_and_expression { $$ = new ASTNode("||"); $$->addChild($1); $$->addChild($3); }
;

conditional_expression:
    logical_or_expression { $$ = $1; }
    | logical_or_expression '?' expression ':' assignment_expression { $$ = new ASTNode("?:"); $$->addChild($1); $$->addChild($3); $$->addChild($5); }
;

assignment_expression:
    conditional_expression { $$ = $1; }
    | logical_or_expression assignment_operator initializer_clause { $$ = new ASTNode("assignment"); $$->addChild($1); $$->addChild($3); }
    | throw_expression { $$ = new ASTNode("throw_expression"); } // Placeholder
;


assignment_operator:
    ASSIGN { $$ = new ASTNode("="); }
    | MULTIPLY ASSIGN { $$ = new ASTNode("*="); }
    | DIVIDE ASSIGN { $$ = new ASTNode("/="); }
    | MODULO ASSIGN { $$ = new ASTNode("%="); }
    | PLUS ASSIGN { $$ = new ASTNode("+="); }
    | MINUS ASSIGN { $$ = new ASTNode("-="); }
    | LEFT_SHIFT ASSIGN { $$ = new ASTNode("<<="); }
    | RIGHT_SHIFT ASSIGN { $$ = new ASTNode(">>="); }
    | AND ASSIGN { $$ = new ASTNode("&="); }
    | '^' ASSIGN { $$ = new ASTNode("^="); }
    | '|' ASSIGN { $$ = new ASTNode("|="); }
;

expression:
    assignment_expression { $$ = $1; }
    | expression COMMA assignment_expression { $$ = new ASTNode(","); $$->addChild($1); $$->addChild($3); }
;

constant_expression:
    conditional_expression { $$ = $1; }
;

// Statements//////////////////////////////////////////////////////////

statement:
    labeled_statement { $$ = $1; }
    | attribute_specifier_seq_opt expression_statement { $$ = $2; }
    | attribute_specifier_seq_opt compound_statement { $$ = $2; }
    | attribute_specifier_seq_opt selection_statement { $$ = $2; }
    | attribute_specifier_seq_opt iteration_statement { $$ = $2; }
    | attribute_specifier_seq_opt jump_statement { $$ = $2; }
    | declaration_statement { $$ = $1; }
    | attribute_specifier_seq_opt try_block { $$ = new ASTNode("try_block"); } // Placeholder
;

labeled_statement:
    attribute_specifier_seq_opt IDENTIFIER COLON statement { $$ = new ASTNode("labeled_statement"); $$->createChild("label", $2); $$->addChild($4); }
    | attribute_specifier_seq_opt CASE constant_expression COLON statement { $$ = new ASTNode("case_statement"); $$->addChild($3); $$->addChild($5); }
    | attribute_specifier_seq_opt DEFAULT COLON statement { $$ = new ASTNode("default_statement"); $$->addChild($4); }
;

expression_statement:
    expression_opt SEMICOLON { $$ = new ASTNode("expression_statement"); $$->addChild($1); }
;

compound_statement:
    LBRACE statement_seq_opt RBRACE { $$ = new ASTNode("compound_statement"); $$->addChild($2); }
;

statement_seq:
    statement { $$ = new ASTNode("statement_seq"); $$->addChild($1); }
    | statement_seq statement { $$ = $1; $$->addChild($2); }
;

selection_statement:
    IF LPAREN condition RPAREN statement { $$ = new ASTNode("if_statement"); $$->addChild($3); $$->addChild($5); }
    | IF LPAREN condition RPAREN statement ELSE statement { $$ = new ASTNode("if_else_statement"); $$->addChild($3); $$->addChild($5); $$->addChild($7); }
    | SWITCH LPAREN condition RPAREN statement { $$ = new ASTNode("switch_statement"); $$->addChild($3); $$->addChild($5); }
;

condition:
    expression { $$ = $1; }
    | attribute_specifier_seq_opt decl_specifier_seq declarator ASSIGN initializer_clause { $$ = new ASTNode("condition"); $$->addChild($2); $$->addChild($3); $$->addChild($5); }
    | attribute_specifier_seq_opt decl_specifier_seq declarator braced_init_list { $$ = new ASTNode("condition"); $$->addChild($2); $$->addChild($3); $$->addChild($4); }
;

iteration_statement:
    WHILE LPAREN condition RPAREN statement { $$ = new ASTNode("while_statement"); $$->addChild($3); $$->addChild($5); }
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON { $$ = new ASTNode("do_while_statement"); $$->addChild($2); $$->addChild($5); }
    | FOR LPAREN for_init_statement condition_opt SEMICOLON expression_opt RPAREN statement { $$ = new ASTNode("for_statement"); $$->addChild($3); $$->addChild($4); $$->addChild($6); $$->addChild($8); }
    | FOR LPAREN for_range_declaration COLON for_range_initializer RPAREN statement { $$ = new ASTNode("for_range_statement"); $$->addChild($3); $$->addChild($5); $$->addChild($7); }
;

for_init_statement:
    expression_statement { $$ = $1; }
    | simple_declaration { $$ = $1; }
;

for_range_declaration:
    attribute_specifier_seq_opt type_specifier_seq declarator { $$ = new ASTNode("for_range_declaration"); $$->addChild($2); $$->addChild($3); }
;

for_range_initializer:
    expression { $$ = $1; }
    | braced_init_list { $$ = new ASTNode("braced_init_list"); } // Placeholder
;

jump_statement:
    BREAK SEMICOLON { $$ = new ASTNode("break_statement"); }
    | CONTINUE SEMICOLON { $$ = new ASTNode("continue_statement"); }
    | RETURN expression_opt SEMICOLON { $$ = new ASTNode("return_statement"); $$->addChild($2); }
    | RETURN braced_init_list_opt SEMICOLON { $$ = new ASTNode("return_statement"); $$->addChild($2); }
    | GOTO IDENTIFIER SEMICOLON { $$ = new ASTNode("goto_statement"); $$->createChild("label", $2); }
;









//---------------------------------------//
declaration_seq:
    declaration { $$ = new ASTNode("declaration_seq"); $$->addChild($1); }
    | declaration_seq declaration { $$ = $1; $$->addChild($2); }
;

declaration:
    block_declaration { $$ = $1; }
    | function_definition { $$ = $1; }
    /* | template_declaration { $$ = new ASTNode("template_declaration"); } // Placeholder */
    /* | explicit_instantiation { $$ = new ASTNode("explicit_instantiation"); } // Placeholder */
    /* | explicit_specialization { $$ = new ASTNode("explicit_specialization"); } // Placeholder */
    /* | linkage_specification { $$ = new ASTNode("linkage_specification"); } // Placeholder */
    /* | namespace_definition { $$ = new ASTNode("namespace_definition"); } // Placeholder */
    | empty_declaration { $$ = new ASTNode("empty_declaration"); }
    | attribute_declaration { $$ = new ASTNode("attribute_declaration"); }
;

block_declaration:
    simple_declaration { $$ = $1; }
    | asm_definition { $$ = new ASTNode("asm_definition"); } // Placeholder
    | namespace_alias_definition { $$ = new ASTNode("namespace_alias_definition"); } // Placeholder
    | using_declaration { $$ = new ASTNode("using_declaration"); } // Placeholder
    | using_directive { $$ = new ASTNode("using_directive"); } // Placeholder
    | static_assert_declaration { $$ = new ASTNode("static_assert_declaration"); }
    | alias_declaration { $$ = new ASTNode("alias_declaration"); }
    /* | opaque_enum_declaration { $$ = new ASTNode("opaque_enum_declaration"); } // Placeholder */
;

alias_declaration:
    USING IDENTIFIER ASSIGN type_id SEMICOLON { $$ = new ASTNode("alias_declaration"); $$->createChild("alias", $2); $$->addChild($4); }
;

simple_declaration:
    attribute_specifier_seq_opt decl_specifier_seq_opt init_declarator_list_opt SEMICOLON { $$ = new ASTNode("simple_declaration"); }
;

static_assert_declaration:
    STATIC_ASSERT LPAREN constant_expression COMMA STRING_LITERAL RPAREN SEMICOLON { $$ = new ASTNode("static_assert_declaration"); $$->createChild("expression", $3); $$->createChild("message", $5); }
;

empty_declaration:
    SEMICOLON { $$ = new ASTNode("empty_declaration"); }
;

attribute_declaration:
    attribute_specifier_seq SEMICOLON { $$ = new ASTNode("attribute_declaration"); }
;


//----------------------------------

decl_specifier:
    storage_class_specifier { $$ = $1; }
    | type_specifier { $$ = $1; }
    | function_specifier { $$ = $1; }
    | FRIEND { $$ = new ASTNode("friend"); }
    | TYPEDEF { $$ = new ASTNode("typedef"); }
    | CONSTEXPR { $$ = new ASTNode("constexpr"); }
;

decl_specifier_seq:
    decl_specifier attribute_specifier_seq_opt { $$ = new ASTNode("decl_specifier_seq"); $$->addChild($1); $$->addChild($2); }
    | decl_specifier decl_specifier_seq { $$ = $1; $$->addChild($2); }
;

storage_class_specifier:
    AUTO { $$ = new ASTNode("auto"); }
    | REGISTER { $$ = new ASTNode("register"); }
    | STATIC { $$ = new ASTNode("static"); }
    | THREAD_LOCAL { $$ = new ASTNode("thread_local"); }
    | EXTERN { $$ = new ASTNode("extern"); }
    | MUTABLE { $$ = new ASTNode("mutable"); }
;

function_specifier:
    INLINE { $$ = new ASTNode("inline"); }
    | VIRTUAL { $$ = new ASTNode("virtual"); }
    | EXPLICIT { $$ = new ASTNode("explicit"); }
;

typedef_name:
    IDENTIFIER { $$ = new ASTNode("typedef_name"); $$->createChild("name", $1); }
;

type_specifier:
    trailing_type_specifier { $$ = $1; }
    | class_specifier { $$ = $1; }
    | enum_specifier { $$ = $1; }
;

trailing_type_specifier:
    simple_type_specifier { $$ = $1; }
    | elaborated_type_specifier { $$ = $1; }
    | typename_specifier { $$ = $1; }
    | cv_qualifier { $$ = $1; }
;

type_specifier_seq:
    type_specifier attribute_specifier_seq_opt { $$ = new ASTNode("type_specifier_seq"); $$->addChild($1); $$->addChild($2); }
    | type_specifier type_specifier_seq { $$ = $1; $$->addChild($2); }
;

trailing_type_specifier_seq:
    trailing_type_specifier attribute_specifier_seq_opt { $$ = new ASTNode("trailing_type_specifier_seq"); $$->addChild($1); $$->addChild($2); }
    | trailing_type_specifier trailing_type_specifier_seq { $$ = $1; $$->addChild($2); }
;

simple_type_specifier:
    COLONCOLON_opt nested_name_specifier_opt type_name { $$ = new ASTNode("simple_type_specifier"); $$->addChild($2); $$->addChild($3); }
    | COLONCOLON_opt nested_name_specifier template simple_template_id { $$ = new ASTNode("simple_type_specifier"); $$->addChild($2); $$->addChild($3); $$->addChild($4); }
    | CHAR { $$ = new ASTNode("char"); }
    | CHAR16_T { $$ = new ASTNode("char16_t"); }
    | CHAR32_T { $$ = new ASTNode("char32_t"); }
    | WCHAR_T { $$ = new ASTNode("wchar_t"); }
    | BOOL { $$ = new ASTNode("bool"); }
    | SHORT { $$ = new ASTNode("short"); }
    | INT { $$ = new ASTNode("int"); }
    | LONG { $$ = new ASTNode("long"); }
    | SIGNED { $$ = new ASTNode("signed"); }
    | UNSIGNED { $$ = new ASTNode("unsigned"); }
    | FLOAT { $$ = new ASTNode("float"); }
    | DOUBLE { $$ = new ASTNode("double"); }
    | VOID { $$ = new ASTNode("void"); }
    | AUTO { $$ = new ASTNode("auto"); }
    | decltype_specifier { $$ = $1; }
;

type_name:
    class_name { $$ = $1; }
    | enum_name { $$ = $1; }
    | typedef_name { $$ = $1; }
    | simple_template_id { $$ = $1; }
;

decltype_specifier:
    DECLTYPE LPAREN expression RPAREN { $$ = new ASTNode("decltype_specifier"); $$->addChild($3); }
;

elaborated_type_specifier:
    class_key attribute_specifier_seq_opt COLONCOLON_opt nested_name_specifier_opt IDENTIFIER { $$ = new ASTNode("elaborated_type_specifier"); $$->addChild($2); $$->addChild($4); $$->createChild("name", $5); }
    | class_key COLONCOLON_opt nested_name_specifier_opt template_opt simple_template_id { $$ = new ASTNode("elaborated_type_specifier"); $$->addChild($2); $$->addChild($3); $$->addChild($4); }
    | ENUM COLONCOLON_opt nested_name_specifier_opt IDENTIFIER { $$ = new ASTNode("elaborated_type_specifier"); $$->addChild($2); $$->addChild($3); $$->createChild("name", $4); }
;


//ENUM////////////////////////////////////////
enum_name:
    IDENTIFIER { $$ = new ASTNode("enum_name"); $$->createChild("name", $1); }
;

enum_specifier:
    enum_head LBRACE enumerator_list_opt RBRACE { $$ = new ASTNode("enum_specifier"); $$->addChild($1); $$->addChild($3); }
    | enum_head LBRACE enumerator_list COMMA RBRACE { $$ = new ASTNode("enum_specifier"); $$->addChild($1); $$->addChild($3); }
;

enum_head:
    enum_key attribute_specifier_seq_opt IDENTIFIER_opt enum_base_opt { $$ = new ASTNode("enum_head"); $$->addChild($2); $$->createChild("name", $3); $$->addChild($4); }
    | enum_key attribute_specifier_seq_opt nested_name_specifier IDENTIFIER enum_base_opt { $$ = new ASTNode("enum_head"); $$->addChild($2); $$->addChild($3); $$->createChild("name", $4); $$->addChild($5); }
;

opaque_enum_declaration:
    enum_key attribute_specifier_seq_opt IDENTIFIER enum_base_opt SEMICOLON { $$ = new ASTNode("opaque_enum_declaration"); $$->addChild($2); $$->createChild("name", $3); $$->addChild($4); }
;

enum_key:
    ENUM { $$ = new ASTNode("enum"); }
    | ENUM CLASS { $$ = new ASTNode("enum_class"); }
    | ENUM STRUCT { $$ = new ASTNode("enum_struct"); }
;

enum_base:
    COLON type_specifier_seq { $$ = new ASTNode("enum_base"); $$->addChild($2); }
;

enumerator_list:
    enumerator_definition { $$ = new ASTNode("enumerator_list"); $$->addChild($1); }
    | enumerator_list COMMA enumerator_definition { $$ = $1; $$->addChild($3); }
;

enumerator_definition:
    enumerator { $$ = $1; }
    | enumerator ASSIGN constant_expression { $$ = new ASTNode("enumerator_definition"); $$->addChild($1); $$->addChild($3); }
;

enumerator:
    IDENTIFIER { $$ = new ASTNode("enumerator"); $$->createChild("name", $1); }
;
//ENUM END////////////////////////////////////////





//NAMESPACE////////////////////////////////////////
/*
namespace_name:
    original_namespace_name { $$ = $1; }
    | namespace_alias { $$ = $1; }
;

original_namespace_name:
    IDENTIFIER { $$ = new ASTNode("original_namespace_name"); $$->createChild("name", $1); }
;

namespace_definition:
    named_namespace_definition { $$ = $1; }
    | unnamed_namespace_definition { $$ = $1; }
;

named_namespace_definition:
    original_namespace_definition { $$ = $1; }
    | extension_namespace_definition { $$ = $1; }
;

original_namespace_definition:
    INLINE_opt NAMESPACE IDENTIFIER LBRACE namespace_body RBRACE { $$ = new ASTNode("original_namespace_definition"); $$->addChild($1); $$->createChild("name", $3); $$->addChild($5); }
;

extension_namespace_definition:
    INLINE_opt NAMESPACE original_namespace_name LBRACE namespace_body RBRACE { $$ = new ASTNode("extension_namespace_definition"); $$->addChild($1); $$->createChild("name", $3); $$->addChild($5); }
;

unnamed_namespace_definition:
    INLINE_opt NAMESPACE LBRACE namespace_body RBRACE { $$ = new ASTNode("unnamed_namespace_definition"); $$->addChild($1); $$->addChild($4); }
;

namespace_body:
    declaration_seq_opt { $$ = $1; }
;

namespace_alias:
    IDENTIFIER { $$ = new ASTNode("namespace_alias"); $$->createChild("name", $1); }
;

namespace_alias_definition:
    NAMESPACE IDENTIFIER ASSIGN qualified_namespace_specifier SEMICOLON { $$ = new ASTNode("namespace_alias_definition"); $$->createChild("alias", $2); $$->addChild($4); }
;

qualified_namespace_specifier:
    COLONCOLON_opt nested_name_specifier_opt namespace_name { $$ = new ASTNode("qualified_namespace_specifier"); $$->addChild($2); $$->addChild($3); }
;

using_declaration:
    USING typename_opt COLONCOLON_opt nested_name_specifier unqualified_id SEMICOLON { $$ = new ASTNode("using_declaration"); $$->addChild($2); $$->addChild($4); $$->addChild($5); }
    | USING COLONCOLON unqualified_id SEMICOLON { $$ = new ASTNode("using_declaration"); $$->addChild($3); }
;

using_directive:
    attribute_specifier_seq_opt USING NAMESPACE COLONCOLON_opt nested_name_specifier_opt namespace_name SEMICOLON { $$ = new ASTNode("using_directive"); $$->addChild($1); $$->addChild($5); $$->addChild($6); }
;
*/
//NAMESPACE END////////////////////////////////////////




asm_definition:
    ASM LPAREN STRING_LITERAL RPAREN SEMICOLON { $$ = new ASTNode("asm_definition"); $$->createChild("literal", $3); }
;

linkage_specification:
    EXTERN STRING_LITERAL LBRACE declaration_seq_opt RBRACE { $$ = new ASTNode("linkage_specification"); $$->createChild("literal", $2); $$->addChild($4); }
    | EXTERN STRING_LITERAL declaration { $$ = new ASTNode("linkage_specification"); $$->createChild("literal", $2); $$->addChild($3); }
;

attribute_specifier_seq:
    attribute_specifier { $$ = new ASTNode("attribute_specifier_seq"); $$->addChild($1); }
    | attribute_specifier_seq attribute_specifier { $$ = $1; $$->addChild($2); }
;

attribute_specifier:
    LBRACKET LBRACKET attribute_list RBRACKET RBRACKET { $$ = new ASTNode("attribute_specifier"); $$->addChild($3); }
    | alignment_specifier { $$ = $1; }
;

alignment_specifier:
    ALIGNAS LPAREN type_id ELLIPSIS_opt RPAREN { $$ = new ASTNode("alignment_specifier"); $$->addChild($3); $$->addChild($4); }
    | ALIGNAS LPAREN assignment_expression ELLIPSIS_opt RPAREN { $$ = new ASTNode("alignment_specifier"); $$->addChild($3); $$->addChild($4); }
;

attribute_list:
    attribute_opt { $$ = new ASTNode("attribute_list"); $$->addChild($1); }
    | attribute_list COMMA attribute_opt { $$ = $1; $$->addChild($3); }
    | attribute ELLIPSIS { $$ = new ASTNode("attribute_list"); $$->addChild($1); $$->createChild("ellipsis", "..."); }
    | attribute_list COMMA attribute ELLIPSIS { $$ = $1; $$->addChild($3); $$->createChild("ellipsis", "..."); }
;

attribute:
    attribute_token attribute_argument_clause_opt { $$ = new ASTNode("attribute"); $$->addChild($1); $$->addChild($2); }
;

attribute_token:
    IDENTIFIER { $$ = new ASTNode("attribute_token"); $$->createChild("name", $1); }
    | attribute_scoped_token { $$ = $1; }
;

attribute_scoped_token:
    attribute_namespace COLONCOLON IDENTIFIER { $$ = new ASTNode("attribute_scoped_token"); $$->createChild("namespace", $1); $$->createChild("name", $3); }
;

attribute_namespace:
    IDENTIFIER { $$ = new ASTNode("attribute_namespace"); $$->createChild("name", $1); }
;

attribute_argument_clause:
    LPAREN balanced_token_seq RPAREN { $$ = new ASTNode("attribute_argument_clause"); $$->addChild($2); }
;

balanced_token_seq:
    balanced_token { $$ = new ASTNode("balanced_token_seq"); $$->addChild($1); }
    | balanced_token_seq balanced_token { $$ = $1; $$->addChild($2); }
;

balanced_token:
    LPAREN balanced_token_seq RPAREN { $$ = new ASTNode("balanced_token"); $$->addChild($2); }
    | LBRACKET balanced_token_seq RBRACKET { $$ = new ASTNode("balanced_token"); $$->addChild($2); }
    | LBRACE balanced_token_seq RBRACE { $$ = new ASTNode("balanced_token"); $$->addChild($2); }
    | token { $$ = $1; }
;


init_declarator_list:
    init_declarator { $$ = new ASTNode("init_declarator_list"); $$->addChild($1); }
    | init_declarator_list COMMA init_declarator { $$ = $1; $$->addChild($3); }
;

init_declarator:
    declarator initializer_opt { $$ = new ASTNode("init_declarator"); $$->addChild($1); $$->addChild($2); }
;

declarator:
    ptr_declarator { $$ = $1; }
    | noptr_declarator parameters_and_qualifiers trailing_return_type { $$ = new ASTNode("declarator"); $$->addChild($1); $$->addChild($2); $$->addChild($3); }
;

ptr_declarator:
    noptr_declarator { $$ = $1; }
    | ptr_operator ptr_declarator { $$ = new ASTNode("ptr_declarator"); $$->addChild($1); $$->addChild($2); }
;

noptr_declarator:
    declarator_id attribute_specifier_seq_opt { $$ = new ASTNode("noptr_declarator"); $$->addChild($1); $$->addChild($2); }
    | noptr_declarator parameters_and_qualifiers { $$ = $1; $$->addChild($2); }
    | noptr_declarator LBRACKET constant_expression_opt RBRACKET attribute_specifier_seq_opt { $$ = $1; $$->addChild($3); $$->addChild($5); }
    | LPAREN ptr_declarator RPAREN { $$ = $2; }
;

parameters_and_qualifiers:
    LPAREN parameter_declaration_clause RPAREN attribute_specifier_seq_opt cv_qualifier_seq_opt ref_qualifier_opt exception_specification_opt { $$ = new ASTNode("parameters_and_qualifiers"); $$->addChild($2); $$->addChild($4); $$->addChild($5); $$->addChild($6); }
;

trailing_return_type:
    ARROW trailing_type_specifier_seq abstract_declarator_opt { $$ = new ASTNode("trailing_return_type"); $$->addChild($2); $$->addChild($3); }
;

ptr_operator:
    MULTIPLY attribute_specifier_seq_opt cv_qualifier_seq_opt { $$ = new ASTNode("ptr_operator"); $$->addChild($2); $$->addChild($3); }
    | AMPERSAND attribute_specifier_seq_opt { $$ = new ASTNode("ptr_operator"); $$->addChild($2); }
    | AND attribute_specifier_seq_opt { $$ = new ASTNode("ptr_operator"); $$->addChild($2); }
    | COLONCOLON_opt nested_name_specifier MULTIPLY attribute_specifier_seq_opt cv_qualifier_seq_opt { $$ = new ASTNode("ptr_operator"); $$->addChild($2); $$->addChild($4); $$->addChild($5); }
;

cv_qualifier_seq:
    cv_qualifier { $$ = new ASTNode("cv_qualifier_seq"); $$->addChild($1); }
    | cv_qualifier_seq cv_qualifier { $$ = $1; $$->addChild($2); }
;

cv_qualifier:
    CONST { $$ = new ASTNode("const"); }
    | VOLATILE { $$ = new ASTNode("volatile"); }
;

ref_qualifier:
    AMPERSAND { $$ = new ASTNode("ref_qualifier"); $$->createChild("type", "&"); }
    | AND { $$ = new ASTNode("ref_qualifier"); $$->createChild("type", "&&"); }
;

declarator_id:
    ELLIPSIS_opt id_expression { $$ = new ASTNode("declarator_id"); $$->addChild($2); }
    | COLONCOLON_opt nested_name_specifier_opt class_name { $$ = new ASTNode("declarator_id"); $$->addChild($2); }
;

type_id:
    type_specifier_seq abstract_declarator_opt { $$ = new ASTNode("type_id"); $$->addChild($1); $$->addChild($2); }
;

abstract_declarator:
    ptr_abstract_declarator { $$ = $1; }
    | noptr_abstract_declarator_opt parameters_and_qualifiers trailing_return_type { $$ = new ASTNode("abstract_declarator"); $$->addChild($1); $$->addChild($2); $$->addChild($3); }
    | ELLIPSIS { $$ = new ASTNode("ellipsis"); }
;

ptr_abstract_declarator:
    noptr_abstract_declarator { $$ = $1; }
    | ptr_operator ptr_abstract_declarator_opt { $$ = new ASTNode("ptr_abstract_declarator"); $$->addChild($1); $$->addChild($2); }
;

noptr_abstract_declarator:
    noptr_abstract_declarator_opt parameters_and_qualifiers { $$ = $1; $$->addChild($2); }
    | noptr_abstract_declarator_opt LBRACKET constant_expression RBRACKET attribute_specifier_seq_opt { $$ = $1; $$->addChild($3); $$->addChild($5); }
    | LPAREN ptr_abstract_declarator RPAREN { $$ = $2; }
;

parameter_declaration_clause:
    parameter_declaration_list_opt ELLIPSIS_opt { $$ = new ASTNode("parameter_declaration_clause"); $$->addChild($1); $$->addChild($2); }
    | parameter_declaration_list COMMA ELLIPSIS { $$ = new ASTNode("parameter_declaration_clause"); $$->addChild($1); }
;

parameter_declaration_list:
    parameter_declaration { $$ = new ASTNode("parameter_declaration_list"); $$->addChild($1); }
    | parameter_declaration_list COMMA parameter_declaration { $$ = $1; $$->addChild($3); }
;

parameter_declaration:
    attribute_specifier_seq_opt decl_specifier_seq declarator { $$ = new ASTNode("parameter_declaration"); $$->addChild($2); $$->addChild($3); }
    | attribute_specifier_seq_opt decl_specifier_seq declarator ASSIGN initializer_clause { $$ = new ASTNode("parameter_declaration"); $$->addChild($2); $$->addChild($3); $$->addChild($5); }
    | attribute_specifier_seq_opt decl_specifier_seq abstract_declarator_opt { $$ = new ASTNode("parameter_declaration"); $$->addChild($2); $$->addChild($3); }
    | attribute_specifier_seq_opt decl_specifier_seq abstract_declarator_opt ASSIGN initializer_clause { $$ = new ASTNode("parameter_declaration"); $$->addChild($2); $$->addChild($3); $$->addChild($5); }
;

function_definition:
    attribute_specifier_seq_opt decl_specifier_seq_opt declarator function_body { $$ = new ASTNode("function_definition"); $$->addChild($1); $$->addChild($2); $$->addChild($3); $$->addChild($4); }
    | attribute_specifier_seq_opt decl_specifier_seq_opt declarator ASSIGN DEFAULT SEMICOLON { $$ = new ASTNode("function_definition"); $$->addChild($1); $$->addChild($2); $$->addChild($3); $$->createChild("default", ""); }
    | attribute_specifier_seq_opt decl_specifier_seq_opt declarator ASSIGN DELETE SEMICOLON { $$ = new ASTNode("function_definition"); $$->addChild($1); $$->addChild($2); $$->addChild($3); $$->createChild("delete", ""); }
;

function_body:
    ctor_initializer_opt compound_statement { $$ = new ASTNode("function_body"); $$->addChild($1); $$->addChild($2); }
    | function_try_block { $$ = new ASTNode("function_try_block"); } // Placeholder
;

initializer:
    brace_or_equal_initializer { $$ = $1; }
    | LPAREN expression_list RPAREN { $$ = new ASTNode("initializer"); $$->addChild($2); }
;

brace_or_equal_initializer:
    ASSIGN initializer_clause { $$ = new ASTNode("brace_or_equal_initializer"); $$->addChild($2); }
    | braced_init_list { $$ = $1; }
;

initializer_clause:
    assignment_expression { $$ = $1; }
    | braced_init_list { $$ = $1; }
;

initializer_list:
    initializer_clause ELLIPSIS_opt { $$ = new ASTNode("initializer_list"); $$->addChild($1); }
    | initializer_list COMMA initializer_clause ELLIPSIS_opt { $$ = $1; $$->addChild($3); }
;

braced_init_list:
    LBRACE initializer_list COMMA_opt RBRACE { $$ = new ASTNode("braced_init_list"); $$->addChild($2); }
    | LBRACE RBRACE { $$ = new ASTNode("braced_init_list"); }
;



// CLASS//////////////////////////////////////////////////////

class_name:
    identifier { $$ = $1; }
    | simple_template_id { $$ = $1; }
;

class_specifier:
    class_head LBRACE member_specification_opt RBRACE { $$ = new ASTNode("class_specifier"); $$->addChild($1); $$->addChild($3); }
;

class_head:
    class_key attribute_specifier_seq_opt class_head_name class_virt_specifier_seq_opt base_clause_opt { $$ = new ASTNode("class_head"); $$->addChild($2); $$->addChild($3); $$->addChild($4); $$->addChild($5); }
    | class_key attribute_specifier_seq_opt base_clause_opt { $$ = new ASTNode("class_head"); $$->addChild($2); $$->addChild($3); }
;

class_head_name:
    nested_name_specifier_opt class_name { $$ = new ASTNode("class_head_name"); $$->addChild($2); }
;

class_virt_specifier_seq:
    class_virt_specifier { $$ = new ASTNode("class_virt_specifier_seq"); $$->addChild($1); }
    | class_virt_specifier_seq class_virt_specifier { $$ = $1; $$->addChild($2); }
;

class_virt_specifier:
    FINAL { $$ = new ASTNode("final"); }
;

class_key:
    /* CLASS { $$ = new ASTNode("class"); } */
    | STRUCT { $$ = new ASTNode("struct"); }
    /* | UNION { $$ = new ASTNode("union"); } */
;

member_specification:
    member_declaration member_specification_opt { $$ = new ASTNode("member_specification"); $$->addChild($1); $$->addChild($2); }
    | access_specifier COLON member_specification_opt { $$ = new ASTNode("member_specification"); $$->addChild($1); $$->addChild($3); }
;

member_declaration:
    attribute_specifier_seq_opt decl_specifier_seq_opt member_declarator_list_opt SEMICOLON { $$ = new ASTNode("member_declaration"); $$->addChild($2); $$->addChild($3); }
    | function_definition SEMICOLON_opt { $$ = new ASTNode("member_declaration"); $$->addChild($1); }
    | using_declaration { $$ = new ASTNode("member_declaration"); $$->addChild($1); }
    | static_assert_declaration { $$ = new ASTNode("member_declaration"); $$->addChild($1); }
    | template_declaration { $$ = new ASTNode("member_declaration"); $$->addChild($1); }
    | alias_declaration { $$ = new ASTNode("member_declaration"); $$->addChild($1); }
;

member_declarator_list:
    member_declarator { $$ = new ASTNode("member_declarator_list"); $$->addChild($1); }
    | member_declarator_list COMMA member_declarator { $$ = $1; $$->addChild($3); }
;

member_declarator:
    declarator virt_specifier_seq_opt pure_specifier_opt { $$ = new ASTNode("member_declarator"); $$->addChild($1); $$->addChild($2); $$->addChild($3); }
    | declarator virt_specifier_seq_opt brace_or_equal_initializer_opt { $$ = new ASTNode("member_declarator"); $$->addChild($1); $$->addChild($2); $$->addChild($3); }
    | identifier_opt attribute_specifier_seq_opt virt_specifier_seq_opt COLON constant_expression { $$ = new ASTNode("member_declarator"); $$->addChild($2); $$->addChild($3); $$->addChild($5); }
;

virt_specifier_seq:
    virt_specifier { $$ = new ASTNode("virt_specifier_seq"); $$->addChild($1); }
    | virt_specifier_seq virt_specifier { $$ = $1; $$->addChild($2); }
;

virt_specifier:
    OVERRIDE { $$ = new ASTNode("override"); }
    | FINAL { $$ = new ASTNode("final"); }
    | NEW { $$ = new ASTNode("new"); }
;

pure_specifier:
    ASSIGN NUMBER { $$ = new ASTNode("pure_specifier"); $$->createChild("value", $2); }
;

base_clause:
    COLON base_specifier_list { $$ = new ASTNode("base_clause"); $$->addChild($2); }
;

base_specifier_list:
    base_specifier ELLIPSIS_opt { $$ = new ASTNode("base_specifier_list"); $$->addChild($1); }
    | base_specifier_list COMMA base_specifier ELLIPSIS_opt { $$ = $1; $$->addChild($3); }
;

base_specifier:
    attribute_specifier_seq_opt base_type_specifier { $$ = new ASTNode("base_specifier"); $$->addChild($1); $$->addChild($2); }
    | attribute_specifier_seq_opt VIRTUAL access_specifier_opt base_type_specifier { $$ = new ASTNode("base_specifier"); $$->addChild($1); $$->createChild("virtual", "true"); $$->addChild($3); $$->addChild($4); }
    | attribute_specifier_seq_opt access_specifier VIRTUAL_opt base_type_specifier { $$ = new ASTNode("base_specifier"); $$->addChild($1); $$->addChild($2); $$->createChild("virtual", "true"); $$->addChild($4); }
;

class_or_decltype:
    COLONCOLON_opt nested_name_specifier_opt class_name { $$ = new ASTNode("class_or_decltype"); $$->addChild($2); $$->addChild($3); }
    | decltype_specifier { $$ = new ASTNode("class_or_decltype"); $$->addChild($1); }
;

base_type_specifier:
    class_or_decltype { $$ = new ASTNode("base_type_specifier"); $$->addChild($1); }
;

access_specifier:
    PRIVATE { $$ = new ASTNode("access_specifier"); $$->createChild("specifier", "private"); }
    | PROTECTED { $$ = new ASTNode("access_specifier"); $$->createChild("specifier", "protected"); }
    | PUBLIC { $$ = new ASTNode("access_specifier"); $$->createChild("specifier", "public"); }
;

conversion_function_id:
    OPERATOR conversion_type_id { $$ = new ASTNode("conversion_function_id"); $$->addChild($2); }
;

conversion_type_id:
    type_specifier_seq conversion_declarator_opt { $$ = new ASTNode("conversion_type_id"); $$->addChild($1); $$->addChild($2); }
;

conversion_declarator:
    ptr_operator conversion_declarator_opt { $$ = new ASTNode("conversion_declarator"); $$->addChild($1); $$->addChild($2); }
;

ctor_initializer:
    COLON mem_initializer_list { $$ = new ASTNode("ctor_initializer"); $$->addChild($2); }
;

mem_initializer_list:
    mem_initializer ELLIPSIS_opt { $$ = new ASTNode("mem_initializer_list"); $$->addChild($1); $$->addChild($2); }
    | mem_initializer_list COMMA mem_initializer ELLIPSIS_opt { $$ = $1; $$->addChild($3); $$->addChild($4); }
;

mem_initializer:
    mem_initializer_id LPAREN expression_list_opt RPAREN { $$ = new ASTNode("mem_initializer"); $$->addChild($1); $$->addChild($3); }
    | mem_initializer_id braced_init_list { $$ = new ASTNode("mem_initializer"); $$->addChild($1); $$->addChild($2); }
;

mem_initializer_id:
    class_or_decltype { $$ = new ASTNode("mem_initializer_id"); $$->addChild($1); }
    | IDENTIFIER { $$ = new ASTNode("mem_initializer_id"); $$->createChild("name", $1); }
;
//CLASS END//////////////////////////////////////////////////////






operator_function_id:
    OPERATOR overloadable_operator { $$ = new ASTNode("operator_function_id"); $$->addChild($2); }
    | OPERATOR overloadable_operator LT template_argument_list_opt GT { $$ = new ASTNode("operator_function_id"); $$->addChild($2); $$->addChild($4); }
;

overloadable_operator:
    NEW { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "new"); }
    | DELETE { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "delete"); }
    | NEW LBRACKET RBRACKET { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "new[]"); }
    | DELETE LBRACKET RBRACKET { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "delete[]"); }
    | PLUS { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "+"); }
    | MINUS { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "-"); }
    | MULTIPLY { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "*"); }
    | DIVIDE { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "/"); }
    | MODULO { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "%"); }
    | '^' { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "^"); }
    | AMPERSAND { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "&"); }
    | '|' { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "|"); }
    | TILDE { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "~"); }
    | NOT { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "!"); }
    | ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "="); }
    | LESS { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "<"); }
    | GREATER { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", ">"); }
    | PLUS ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "+="); }
    | MINUS ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "-="); }
    | MULTIPLY ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "*="); }
    | DIVIDE ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "/="); }
    | MODULO ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "%="); }
    | '^' ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "^="); }
    | AMPERSAND ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "&="); }
    | '|' ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "|="); }
    | LEFT_SHIFT { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "<<"); }
    | RIGHT_SHIFT { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", ">>"); }
    | LEFT_SHIFT ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "<<="); }
    | RIGHT_SHIFT ASSIGN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", ">>="); }
    | EQUAL { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "=="); }
    | NOT_EQUAL { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "!="); }
    | LESS_EQUAL { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "<="); }
    | GREATER_EQUAL { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", ">="); }
    | AND { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "&&"); }
    | OR { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "||"); }
    | PLUSPLUS { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "++"); }
    | MINUSMINUS { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "--"); }
    | ',' { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", ","); }
    | ARROWSTAR { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "->*"); }
    | ARROW { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "->"); }
    | LPAREN RPAREN { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "()"); }
    | LBRACKET RBRACKET { $$ = new ASTNode("overloadable_operator"); $$->createChild("operator", "[]"); }
;

literal_operator_id:
    OPERATOR STRING_LITERAL IDENTIFIER { $$ = new ASTNode("literal_operator_id"); $$->createChild("literal", $2); $$->createChild("identifier", $3); }
;


//TEMPLATE//////////////////////////////////////////////////////
/*

template_declaration:
    TEMPLATE LT template_parameter_list GT declaration { $$ = new ASTNode("template_declaration"); $$->addChild($3); $$->addChild($5); }
;

template_parameter_list:
    template_parameter { $$ = new ASTNode("template_parameter_list"); $$->addChild($1); }
    | template_parameter_list COMMA template_parameter { $$ = $1; $$->addChild($3); }
;

template_parameter:
    type_parameter { $$ = new ASTNode("template_parameter"); $$->addChild($1); }
    | parameter_declaration { $$ = new ASTNode("template_parameter"); $$->addChild($1); }
;

type_parameter:
    CLASS ELLIPSIS_opt IDENTIFIER_opt { $$ = new ASTNode("type_parameter"); $$->createChild("class", "true"); $$->addChild($2); $$->createChild("identifier", $3); }
    | CLASS IDENTIFIER_opt ASSIGN type_id { $$ = new ASTNode("type_parameter"); $$->createChild("class", "true"); $$->createChild("identifier", $2); $$->addChild($4); }
    | TYPENAME ELLIPSIS_opt IDENTIFIER_opt { $$ = new ASTNode("type_parameter"); $$->createChild("typename", "true"); $$->addChild($2); $$->createChild("identifier", $3); }
    | TYPENAME IDENTIFIER_opt ASSIGN type_id { $$ = new ASTNode("type_parameter"); $$->createChild("typename", "true"); $$->createChild("identifier", $2); $$->addChild($4); }
    | TEMPLATE LT template_parameter_list GT CLASS ELLIPSIS_opt IDENTIFIER_opt { $$ = new ASTNode("type_parameter"); $$->createChild("template", "true"); $$->addChild($3); $$->createChild("class", "true"); $$->addChild($6); $$->createChild("identifier", $7); }
    | TEMPLATE LT template_parameter_list GT CLASS IDENTIFIER_opt ASSIGN id_expression { $$ = new ASTNode("type_parameter"); $$->createChild("template", "true"); $$->addChild($3); $$->createChild("class", "true"); $$->createChild("identifier", $6); $$->addChild($8); }
;

simple_template_id:
    template_name LT template_argument_list_opt GT { $$ = new ASTNode("simple_template_id"); $$->createChild("template_name", $1); $$->addChild($3); }
;

template_id:
    simple_template_id { $$ = new ASTNode("template_id"); $$->addChild($1); }
    | operator_function_id LT template_argument_list_opt GT { $$ = new ASTNode("template_id"); $$->addChild($1); $$->addChild($3); }
    | literal_operator_id LT template_argument_list_opt GT { $$ = new ASTNode("template_id"); $$->addChild($1); $$->addChild($3); }
;

template_name:
    IDENTIFIER { $$ = new ASTNode("template_name"); $$->createChild("name", $1); }
;

template_argument_list:
    template_argument ELLIPSIS_opt { $$ = new ASTNode("template_argument_list"); $$->addChild($1); $$->addChild($2); }
    | template_argument_list COMMA template_argument ELLIPSIS_opt { $$ = $1; $$->addChild($3); $$->addChild($4); }
;

template_argument:
    constant_expression { $$ = new ASTNode("template_argument"); $$->addChild($1); }
    | type_id { $$ = new ASTNode("template_argument"); $$->addChild($1); }
    | id_expression { $$ = new ASTNode("template_argument"); $$->addChild($1); }
;

typename_specifier:
    TYPENAME COLONCOLON_opt nested_name_specifier IDENTIFIER { $$ = new ASTNode("typename_specifier"); $$->addChild($3); $$->createChild("name", $4); }
    | TYPENAME COLONCOLON_opt nested_name_specifier template_opt simple_template_id { $$ = new ASTNode("typename_specifier"); $$->addChild($3); $$->addChild($5); }
;

explicit_instantiation:
    EXTERN_opt TEMPLATE declaration { $$ = new ASTNode("explicit_instantiation"); $$->addChild($1); $$->addChild($3); }
;

explicit_specialization:
    TEMPLATE LT GT declaration { $$ = new ASTNode("explicit_specialization"); $$->addChild($4); }
;
*/
//TEMPLATE END//////////////////////////////////////////////////////




//TRY BLOCK//////////////////////////////////////////////////////
/*
try_block:
    TRY compound_statement handler_seq { $$ = new ASTNode("try_block"); $$->addChild($2); $$->addChild($3); }
;

function_try_block:
    TRY ctor_initializer_opt compound_statement handler_seq { $$ = new ASTNode("function_try_block"); $$->addChild($2); $$->addChild($3); $$->addChild($4); }
;

handler_seq:
    handler { $$ = new ASTNode("handler_seq"); $$->addChild($1); }
    | handler_seq handler { $$ = $1; $$->addChild($2); }
;

handler:
    CATCH LPAREN exception_declaration RPAREN compound_statement { $$ = new ASTNode("handler"); $$->addChild($3); $$->addChild($5); }
;

exception_declaration:
    attribute_specifier_seq_opt type_specifier_seq declarator { $$ = new ASTNode("exception_declaration"); $$->addChild($2); $$->addChild($3); }
    | attribute_specifier_seq_opt type_specifier_seq abstract_declarator_opt { $$ = new ASTNode("exception_declaration"); $$->addChild($2); $$->addChild($3); }
    | ELLIPSIS { $$ = new ASTNode("exception_declaration"); $$->createChild("ellipsis", "..."); }
;

throw_expression:
    THROW assignment_expression_opt { $$ = new ASTNode("throw_expression"); $$->addChild($2); }
;

exception_specification:
    dynamic_exception_specification { $$ = new ASTNode("exception_specification"); $$->addChild($1); }
    | noexcept_specification { $$ = new ASTNode("exception_specification"); $$->addChild($1); }
;

dynamic_exception_specification:
    THROW LPAREN type_id_list_opt RPAREN { $$ = new ASTNode("dynamic_exception_specification"); $$->addChild($3); }
;
type_id_list_opt:
    { $$ = new ASTNode("type_id_list_opt"); }
    | type_id_list { $$ = $1; }

type_id_list:
    type_id ELLIPSIS_opt { $$ = new ASTNode("type_id_list"); $$->addChild($1); $$->addChild($2); }
    | type_id_list COMMA type_id ELLIPSIS_opt { $$ = $1; $$->addChild($3); $$->addChild($4); }
;

noexcept_specification:
    NOEXCEPT LPAREN constant_expression RPAREN { $$ = new ASTNode("noexcept_specification"); $$->addChild($3); }
    | NOEXCEPT { $$ = new ASTNode("noexcept_specification"); }
;
*/
//TRY BLOCK END//////////////////////////////////////////////////////



//preprocessing file /////////////////////////////////////////////////////////////
/* preprocessing_file:
    group_opt { $$ = new ASTNode("preprocessing_file"); $$->addChild($1); }
;

group:
    group_part { $$ = new ASTNode("group"); $$->addChild($1); }
    | group group_part { $$ = $1; $$->addChild($2); }
;

group_part:
    if_section { $$ = new ASTNode("group_part"); $$->addChild($1); }
    | control_line { $$ = new ASTNode("group_part"); $$->addChild($1); }
    | text_line { $$ = new ASTNode("group_part"); $$->addChild($1); }
    | '#' non_directive { $$ = new ASTNode("group_part"); $$->createChild("non_directive", $2); }
;

if_section:
    if_group elif_groups_opt else_group_opt endif_line { $$ = new ASTNode("if_section"); $$->addChild($1); $$->addChild($2); $$->addChild($3); $$->addChild($4); }
;

if_group:
    '#' IF constant_expression new_line group_opt { $$ = new ASTNode("if_group"); $$->addChild($3); $$->addChild($5); }
    | '#' IFDEF IDENTIFIER new_line group_opt { $$ = new ASTNode("if_group"); $$->createChild("identifier", $3); $$->addChild($5); }
    | '#' IFNDEF IDENTIFIER new_line group_opt { $$ = new ASTNode("if_group"); $$->createChild("identifier", $3); $$->addChild($5); }
;

elif_groups:
    elif_group { $$ = new ASTNode("elif_groups"); $$->addChild($1); }
    | elif_groups elif_group { $$ = $1; $$->addChild($2); }
;

elif_group:
    '#' ELIF constant_expression new_line group_opt { $$ = new ASTNode("elif_group"); $$->addChild($3); $$->addChild($5); }
;

else_group:
    '#' ELSE new_line group_opt { $$ = new ASTNode("else_group"); $$->addChild($4); }
;

endif_line:
    '#' ENDIF new_line { $$ = new ASTNode("endif_line"); }
;


control_line:
    '#' INCLUDE pp_tokens new_line { $$ = new ASTNode("control_line"); $$->createChild("directive", "include"); $$->addChild($3); }
    | '#' DEFINE IDENTIFIER replacement_list new_line { $$ = new ASTNode("control_line"); $$->createChild("directive", "define"); $$->createChild("identifier", $3); $$->addChild($4); }
    | '#' DEFINE IDENTIFIER LPAREN identifier_list_opt RPAREN replacement_list new_line { $$ = new ASTNode("control_line"); $$->createChild("directive", "define"); $$->createChild("identifier", $3); $$->addChild($5); $$->addChild($7); }
    | '#' DEFINE IDENTIFIER LPAREN identifier_list COMMA ELLIPSIS RPAREN replacement_list new_line { $$ = new ASTNode("control_line"); $$->createChild("directive", "define"); $$->createChild("identifier", $3); $$->addChild($5); $$->createChild("ellipsis", "..."); $$->addChild($8); }
    | '#' UNDEF IDENTIFIER new_line { $$ = new ASTNode("control_line"); $$->createChild("directive", "undef"); $$->createChild("identifier", $3); }
    | '#' LINE pp_tokens new_line { $$ = new ASTNode("control_line"); $$->createChild("directive", "line"); $$->addChild($3); }
    | '#' ERROR pp_tokens_opt new_line { $$ = new ASTNode("control_line"); $$->createChild("directive", "error"); $$->addChild($3); }
    | '#' PRAGMA pp_tokens_opt new_line { $$ = new ASTNode("control_line"); $$->createChild("directive", "pragma"); $$->addChild($3); }
    | '#' new_line { $$ = new ASTNode("control_line"); $$->createChild("directive", "empty"); }
;

text_line:
    pp_tokens_opt new_line { $$ = new ASTNode("text_line"); $$->addChild($1); }
;

non_directive:
    pp_tokens new_line { $$ = new ASTNode("non_directive"); $$->addChild($1); }
;

lparen:
    '(' { $$ = new ASTNode("lparen"); $$->createChild("char", "("); }
;

identifier_list:
    IDENTIFIER { $$ = new ASTNode("identifier_list"); $$->createChild("identifier", $1); }
    | identifier_list COMMA IDENTIFIER { $$ = $1; $$->createChild("identifier", $3); }
;

replacement_list:
    pp_tokens_opt { $$ = new ASTNode("replacement_list"); $$->addChild($1); }
;

pp_tokens:
    preprocessing_token { $$ = new ASTNode("pp_tokens"); $$->addChild($1); }
    | pp_tokens preprocessing_token { $$ = $1; $$->addChild($2); }
;

new_line:
    '\n' { $$ = new ASTNode("new_line"); $$->createChild("char", "\n"); }
; */


%%



// main function

int main(int argc, char **argv) {


    //------------------------ cmd line arguments handling ------------------------

        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> [-d<debug_mode>] [-p [<DOTFileName>] ] [-r <recursiveOutputFile]\n";
            return 1;
        }

        std::string input_file = argv[1];
        std::string output_file = argv[2];
        std::string debug_mode;
        std::string dot_file;
        std::string recursive_output_file;
        std::string SExp_file;

        // Parse arguments
        for (int i = 3; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg[0] == '-' && arg[1] == 'd') {
                // Debug mode flag in the form of "-d<debug_mode>"
                debug_mode = arg.substr(2); // Extract the debug mode value after "-d"

                // Set the debug mode
                DEBUGMODE = std::stoi(debug_mode);

            } else if (arg == "-p") {
                // Check if there is another argument after "-p"
                if (i + 1 < argc) {
                    dot_file = argv[++i]; // Assign the next argument as the DOT file
                } else {
                    // If name is not provided after "-p"
                    // Create a default name for the DOT file
                    std::string base_name = input_file.substr(0, input_file.find_last_of("."));
                    dot_file = base_name + ".dot";
                }
            }else if(arg == "-r"){
                // Check if there is another argument after "-r"
                if (i + 1 < argc) {
                    recursive_output_file = argv[++i]; // Assign the next argument as the recursive output file
                } else {
                    std::cerr << "2Error: Invalid argument.\n";
                    return 1;
                }
            } else if(arg == "-s"){
                // Check if there is another argument after "-s"
                if (i + 1 < argc) {
                    SExp_file = argv[++i]; // Assign the next argument as the SExp output file
                }
                else {
                    std::cerr << "1Error: Invalid argument.\n";
                    return 1;
                }
            } else {
                std::cerr << "4Error: Invalid argument.\n";
                return 1;
            }
        }


    //------------------------ input file handling ------------------------
        yyin = fopen(input_file.c_str(), "r");
        if (!yyin) {
            std::cerr << "E12rror: Unable to open input file.\n";
            return 1;
        }

        freopen(output_file.c_str(), "w", stdout); // stdout will be redirected to output file
        
        //------ToDo[Later]: Redirect cerr to error.txt file------
        // cerr is not redirected to output file it will be printed to console 
        // When we need to show parser errors to the user, we can use cerr to a error.txt file (not now)

    // ------------------------ Symbol Table ------------------------
        // Create a new symbol table
        /* SymbolTable *symTable = new SymbolTable(); */


    //------------------------ Parsing ------------------------

        std::cout << "..........Starting parsing..........\n";
        yyparse();  // Call BISON's parser
        std::cout << "..........Parsing complete..........\n";




    // ------------------------- Printing Various Outputs ------------------------
    
        // Print AST as DOT file
            if(!dot_file.empty()){
                generateDOT(root, dot_file);
            }

        // Print Recursive Output
            if(!recursive_output_file.empty()){
                printASTToFile(root, recursive_output_file);
            }    

        // Print S-Expression
            if(!SExp_file.empty()){
                writeASTToSExpression(root, SExp_file);
            }

        // Print Normal AST
            if(DEBUGMODE){
                printAST(root);
            }

    //------------------------- Cleanup ------------------------
        if (yyin) fclose(yyin);  // Close the input file if opened
        return 0;
}

