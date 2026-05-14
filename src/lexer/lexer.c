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

void lex_identifier(int* position, )

Token* tokenize(const char* input)
{
    int capacity = 10;
    Token* tokens = malloc(capacity * sizeof(Token));
    if(!tokens){
        fprintf(stderr, "Memory allocation failed :(\n");
        return NULL;
    }

    int count = 0;
    int position = 0;
    int line = 1;
    char current_char;
    
    while(input[position] != '\0'){
        current_char = input[position];

        if(count >= capacity){
            capacity *= 2;
            Token* new_tokens = realloc(tokens, capacity * sizeof(Token));
            if(!new_tokens){
                fprintf(stderr, "Memory allocation failed :(\n");
                free(tokens);
                return NULL;
            }
        }
        
        if(current_char == '\n'){
            position++;
            line++;
            continue;
        }
        
        if(isspace(current_char)){
            position++;
            continue;
        }

        if(isalpha(current_char) || current_char == '_'){
            int start = position;
            while(isalnum(input[position]) || input[position] == '_'){
                position++;
            }
            int length = position - start;
            const char* identifier = &input[start];
            TokenType type = lookup_keyword(identifier, length);
            tokens[count++] = (Token){type, line, {identifier, length}};
        }

        if(isdigit(input[position])){
            
        }
    }

}
