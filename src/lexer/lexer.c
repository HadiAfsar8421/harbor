#include <stddef.h>
#define TABLE_SIZE 64
#define KEYWORD_COUNT (sizeof(keyword_table) / sizeof(keyword_table[0]))

#include "lexer.h"

#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    const char *name;
    TokenType type;

} Keyword;

static const Keyword keyword_table[] = {
    {"local", TOKEN_LOCAL},
    {"universal", TOKEN_UNIVERSAL},
    {"default", TOKEN_DEFAULT},
    {"private", TOKEN_PRIVATE},
    {"public", TOKEN_PUBLIC},
    {"namespace", TOKEN_NAMESPACE},
    {"fn", TOKEN_FN},
    {"struct", TOKEN_STRUCT},
    {"enum", TOKEN_ENUM},
    {"packed",TOKEN_PACKED},
    {"if", TOKEN_IF},
    {"else", TOKEN_ELSE},
    {"while", TOKEN_WHILE},
    {"for", TOKEN_FOR},
    {"return", TOKEN_RETURN},
    {"break", TOKEN_BREAK},
    {"continue", TOKEN_CONTINUE},
    {"var", TOKEN_VAR},
    {"const", TOKEN_CONST},
    {"true", TOKEN_TRUE},
    {"false", TOKEN_FALSE},
    {"null", TOKEN_NULL},
    {"int", TOKEN_INT},
    {"uint", TOKEN_UINT},
    {"float", TOKEN_FLOAT},
    {"bool", TOKEN_BOOL},
    {"char", TOKEN_CHAR},
    {"string", TOKEN_STRING},
    {"list", TOKEN_LIST},
    {"void", TOKEN_VOID}
};

typedef struct
{
    const char *input;

    size_t position;
    int line;

    Token *tokens;
    size_t count;
    size_t capacity;

} Lexer;

TokenType lookup_keyword(const char *str, int len)
{
    for (int i = 0; i < KEYWORD_COUNT; i++)
    {
        if (strlen(keyword_table[i].name) == len &&
            strncmp(keyword_table[i].name, str, len) == 0)
        {
            return keyword_table[i].type;
        }
    }

    return TOKEN_IDENTIFIER;
}

static char peek(Lexer *lexer)
{
    return lexer->input[lexer->position];
}

static char peek_next(Lexer *lexer)
{
    if (lexer->input[lexer->position] == '\0')
        return '\0';

    return lexer->input[lexer->position + 1];
}

static char advance(Lexer *lexer)
{
    return lexer->input[lexer->position++];
}

static bool match(Lexer *lexer, char expected)
{
    if (peek(lexer) != expected)
        return false;

    lexer->position++;
    return true;
}

static bool is_at_end(Lexer *lexer)
{
    return lexer->input[lexer->position] == '\0';
}

static bool add_token(Lexer *lexer, TokenType type, Value value, ValueKind kind)
{
    if(lexer->count >= lexer->capacity){
        lexer->capacity *= 2;
        Token* new_tokens = realloc(lexer->tokens, lexer->capacity * sizeof(Token));
        if(!new_tokens){
            fprintf(stderr, "Memory allocation failed :(\n");
            free(lexer->tokens);
            lexer->tokens = NULL;
            return false;
        }
        lexer->tokens = new_tokens;
    }
    lexer->tokens[lexer->count++] = (Token){type, lexer->line, value, kind};
    return true;
}

static bool add_simple_token(Lexer *lexer, TokenType type)
{
    return add_token(lexer, type, (Value){0}, VAL_NONE);
}

static bool lex_identifier(Lexer *lexer){
    int start = lexer->position;
    while(!is_at_end(lexer) &&
        (isalnum((unsigned char)peek(lexer)) || 
        peek(lexer) == '_'))
    {
        advance(lexer);
    }
    int length = lexer->position - start;
    const char *str = &lexer->input[start];
    TokenType type = lookup_keyword(str, length);
    if(type == TOKEN_IDENTIFIER){
        return add_token(
            lexer, 
            type, 
            (Value){
                .slice = (Slice){ str, length }
            }, 
            VAL_SLICE
        );
    }
    else {
        return add_simple_token(lexer, type);
    }
}

static void handle_whitespace(Lexer *lexer){
    if(peek(lexer) == '\n'){
        lexer->line++;
    }
    if(isspace(peek(lexer))){
        advance(lexer);
    }
}

static bool lex_number(Lexer *lexer){
    if(peek(lexer)=='0'){
        if(peek_next(lexer) == 'x'){

        }
    }
}

Token* tokenize(const char* input)
{
    Lexer lexer = {input, 0, 1, malloc(10 * sizeof(Token)), 0, 10};
    if(!lexer.tokens){
        fprintf(stderr, "Memory allocation failed :(\n");
        return NULL;
    }
    
    while(!is_at_end(&lexer)){
        if(!lex_token(&lexer))
        {
            return NULL;
        }
    }
    if(!add_simple_token(&lexer, TOKEN_EOF);)
    {
        return NULL;
    }
    return lexer.tokens;
}
