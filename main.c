#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"

int qtdPessoas = 0;

/*****Funcoes de operaçoes de pessoa***/

int setaNomePessoa( Pessoa *p, char n[ MAX_NOME + 1 ] )
{
    assert( p );

    strcpy( p->nome, n );

    return 1;
}

int setaIdadePessoa( Pessoa *p, unsigned int ida )
{
    assert( p );
    //testa os limites da idade
    if( ida > 120 )
        return 0;

    p->idade = ida;

    return 1;
}

int setaTelefonePessoa( Pessoa *p, char tel[ MAX_TEL + 1 ] )
{
    assert( p );
    //Testa o numero maximo
    if( strlen( tel ) > MAX_TEL )
        return 0; //numero incorreto

    strcpy( p->telefone, tel );

    return 1;
}

/*******Funcoes da agenda***********/
void zeraAgenda( Agenda *a )
{
    assert( a );

    if( a->proximo == 0 )
        return;

    Agenda *proxNo, *noAtual;

    noAtual = a->proximo;
    while( noAtual != 0 )
    {
        proxNo = noAtual->proximo;
        free( noAtual );
        noAtual = proxNo;
    }
}

int adicionaAgenda( Agenda *a, Pessoa pessoa )
{
    //Testa se a lista esta vazia
    Agenda *no = ( Agenda* )malloc( sizeof( Agenda ) );

    if( no == 0 )
    {
        printf( "Nao tem memoria disponivel" );
        return 0;
    }

    //Proximo tem q ser nulo
    no->proximo = 0;

    strcpy( no->pessoas.nome, pessoa.nome );
    no->pessoas.idade = pessoa.idade;
    strcpy( no->pessoas.telefone, pessoa.telefone );

    //Adiciona na lista
    if( a->proximo == 0 )
    {
        a->proximo = no;
    }
    else
    {
        //Pega o topo da lista
        Agenda *aux = a;

        //Percorre a lista ate achar o ultimo no
        while( aux->proximo != 0 )
        {
            aux = aux->proximo;
        }

        aux->proximo = no;
    }

    return 1;
}

int removePorNomeAgenda( Agenda *a, char nome[ MAX_NOME + 1 ] )
{
    assert( a );

    //procura na lista
    Agenda *noPai = a;
    Agenda *i = a->proximo;

    //Enquanto tem proximo
    while( i != 0 )
    {
        if( strcmp( i->pessoas.nome, nome ) == 0 )
        {
            //Achou
            break;
        }

        //Vai ao proximo
        noPai = i;
        i = i->proximo;
    }

    //Testa se achou o valor
    if( i != 0 )
    {
        noPai->proximo = i->proximo;

        qtdPessoas--;
        free( i );

        return 1;
    }

    return 0;
}

int novoContato( Agenda *a )
{
    printf( "----------Novo Contato----------\n\n" );

    char nome[ MAX_NOME + 1 ];
    char tel[ MAX_TEL + 1 ];
    int idade = 0;

    printf( "Nome: " );
    scanf( "%s", nome );
    fflush( stdin );

    printf( "\nIdade: " );
    scanf( "%d", &idade );
    fflush( stdin );

    printf( "\nTelefone: " );
    scanf( "%s", tel );
    fflush( stdin );

    //Cria a pessoa e passa os dados
    Pessoa p;

    setaNomePessoa( &p, nome );
    setaIdadePessoa( &p, idade );
    setaTelefonePessoa( &p, tel );

    if( adicionaAgenda( a, p ) )
    {
        qtdPessoas++;
        return 1;
    }

    return 0;
}

void imprimeAgenda( Agenda *a )
{
    printf( "----------Imprimir Agenda----------\n\n" );

    if( a->proximo == 0 )
        return;

    Agenda *i;
    for( i = a->proximo; i != 0; i = i->proximo )
    {
        printf( "Nome: %s \nIdade: %d \nTelefone: %s ", i->pessoas.nome, i->pessoas.idade, i->pessoas.telefone );
        printf( "\n---------------------\n" );
    }
}

void excluiContato( Agenda *a )
{
    printf( "----------Excluir Contato----------\n\n" );

    char nome[ MAX_NOME + 1 ];

    printf( "(Obs: Diferencia maiusculas de minusculas)\n\n" );

    printf( "Nome: " );
    scanf( "%s", nome );
    fflush( stdin );

    if( !removePorNomeAgenda( a, nome ) )
        printf( "Nenhum contato encontrado com esse nome.\n\n" );
}

int salvarAgenda( Agenda *a )
{
    FILE *file = fopen( "sav.txt", "wb" );

    if( !file )
    {
        printf( "Nao foi possivel abri o arquivo para gravacao.\n\n" );
        return 0;
    }

    //Salva o arquivo
    //Quantidade de pessoas
    fwrite( &qtdPessoas, sizeof( int ), 1, file );

    Agenda *no = a->proximo;
    while( no != 0 )
    {
        if( fwrite( &no->pessoas, sizeof( Pessoa ), 1, file ) == 0 )
        {
            printf( "Nao foi possivel gravar o arquivo.\n\n" );
            return 0;
        }

        no = no->proximo;
    }

    return 1;
}

int carregarAgenda( Agenda *a )
{
    FILE *file = fopen( "sav.txt", "rb" );

    if( !file )
    {
        printf( "Nao foi possivel abrir o arquivo.\n\n" );
        return 0;
    }

    //pega o numero de pessoas
    fread( &qtdPessoas, sizeof( int ), 1, file );

    unsigned int i;
    for( i = 0; i < qtdPessoas; ++i )
    {
        Pessoa p;

        if( fread( &p, sizeof( Pessoa ), 1, file ) == 0 )
        {
            printf( "Nao foi possivel carregar o arquivo.\n\n" );
            return 0;
        }

        //Adiciona na lista
        adicionaAgenda( a, p );
    }

    return 1;
}

int main()
{
    //Agenda usada em td o codigo
    Agenda *agenda = ( Agenda* )malloc( sizeof( Agenda ) );

    if( agenda == 0 )
    {
        printf( "Nao tem memoria disponivel" );
        return 0;
    }

    //O proximo aponta pra nada
    agenda->proximo = 0;

    //Controla td o fluxo do programa
    int sair = 0;

    //Controla as entradas d opcoes
    int ret = 0;

    carregarAgenda( agenda );

    while( !sair )
    {
        printf( "----------Agenda----------\n\n" );

        printf( "1) Novo Contato \n2) Excluir Contato \n3) Imprimir Agenda \n4) Sair\n\n" );

        scanf( "%d", &ret );
        fflush( stdin );

        //Testa o retorno
        switch( ret )
        {
            case 1:
                system( "cls" );
                novoContato( agenda );
                salvarAgenda( agenda );
                continue;
            case 2:
                system( "cls" );
                excluiContato( agenda );
                continue;
            case 3:
                system( "cls" );
                imprimeAgenda( agenda );
                continue;
            case 4:
                sair = 1;
                continue;
            default:
                system( "cls" );
                printf( "Inidice incorreto tente novamente.\n\n" );
                continue;
        }
    }

    zeraAgenda( agenda );
    free( agenda );

    return 0;
}
