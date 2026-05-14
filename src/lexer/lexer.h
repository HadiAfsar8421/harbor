#ifndef LEXER_H
#define LEXER_H

#include<stddef.h>
#include <stdint.h>

typedef enum {
    VAL_NONE,
    VAL_SLICE,
    VAL_INT,
    VAL_FLOAT
} ValueKind;

typedef enum {

    // special
    TOKEN_EOF,

    // identifiers
    TOKEN_IDENTIFIER,

    // literals
    TOKEN_INT_LITERAL,
    TOKEN_FLOAT_LITERAL,
    TOKEN_STRING_LITERAL,
    TOKEN_CHAR_LITERAL,

    // keywords
    TOKEN_LOCAL,
    TOKEN_UNIVERSAL,
    TOKEN_DEFAULT,
    TOKEN_PRIVATE,
    TOKEN_PUBLIC,
    TOKEN_NAMESPACE,
    TOKEN_FN,
    TOKEN_STRUCT,
    TOKEN_ENUM,
    TOKEN_PACKED,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_RETURN,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_VAR,
    TOKEN_CONST,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,

    // types (base keywords)
    TOKEN_INT,
    TOKEN_UINT,
    TOKEN_FLOAT,
    TOKEN_BOOL,
    TOKEN_CHAR,
    TOKEN_STRING,
    TOKEN_LIST,
    TOKEN_VOID,

    // operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,

    TOKEN_EQUAL,

    TOKEN_PLUS_EQUAL,
    TOKEN_MINUS_EQUAL,
    TOKEN_STAR_EQUAL,
    TOKEN_SLASH_EQUAL,
    TOKEN_PERCENT_EQUAL,

    TOKEN_EQUAL_EQUAL,
    TOKEN_NOT_EQUAL,

    TOKEN_LESS,
    TOKEN_GREATER,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER_EQUAL,

    TOKEN_AND_AND,
    TOKEN_OR_OR,
    TOKEN_NOT,

    TOKEN_AND,
    TOKEN_OR,
    TOKEN_XOR,
    TOKEN_TILDE,

    TOKEN_SHIFT_LEFT,
    TOKEN_SHIFT_RIGHT,

    TOKEN_PLUS_PLUS,
    TOKEN_MINUS_MINUS,

    // special syntax
    TOKEN_ARROW,
    TOKEN_ELLIPSIS,   // ...

    TOKEN_DOT,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_SEMICOLON,

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET

} TokenType; 

struct {
    const char *start;
    size_t length;
} Slice;

typedef union {

        SLice slice;

        int64_t i64;
        double f64;

} Value;

typedef struct
{
    TokenType type;
    int line;
    
    Value value;

    ValueKind kind;
} Token;

Token* tokenize(const char* input);

#endif
