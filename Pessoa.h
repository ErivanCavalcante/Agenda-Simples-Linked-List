#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <string.h>
#include <assert.h>
#define MAX_NOME 30
#define MAX_TEL 15


typedef struct
{
    unsigned int emUso; ///Id usado na agenda
    char nome[ MAX_NOME + 1 ];
    unsigned int idade;
    char telefone[ MAX_TEL + 1 ];
} Pessoa;


#endif // PESSOA_H_INCLUDED
