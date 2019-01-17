#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Pessoa.h"

//#define NUM_PESSOAS_MAX 100

struct _agenda
{
    //int num_pessoas;
    Pessoa pessoas;

    //Lista encadeada
    struct _agenda *proximo;
};

typedef struct _agenda Agenda;

#endif // AGENDA_H_INCLUDED
