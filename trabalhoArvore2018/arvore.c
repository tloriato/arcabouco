/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include <malloc.h>
#include <stdio.h>

#define ARVORE_OWN
#include "arvore.h"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

typedef struct tgNoArvore
{

    struct tgNoArvore *pNoPai;
    /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

    struct tgNoArvore *pNoEsq;
    /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

    struct tgNoArvore *pNoDir;
    /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */

    char Valor;
    /* Valor do nó */

} tpNoArvore;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabeça da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

typedef struct tgArvore
{

    tpNoArvore *pNoRaiz;
    /* Ponteiro para a raiz da árvore */

    tpNoArvore *pNoCorr;
    /* Ponteiro para o nó corrente da árvore */

} tpArvore;

/*****  Dados encapsulados no módulo  *****/

// static tpArvore *pArvore = NULL;
/* Ponteiro para a cabea da árvore */

/***** Protótipos das funções encapuladas no módulo *****/

static tpNoArvore *CriarNo(char ValorParm);

static ARV_tpCondRet CriarNoRaiz(void *pontArvore, char ValorParm);

static void DestroiArvore(tpNoArvore *pNo);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

ARV_tpCondRet ARV_CriarArvore(void *pontArvore)
{

    if (pontArvore != NULL)
    {
        ARV_DestruirArvore(pontArvore);
    } /* if */

    pontArvore = (tpArvore *)malloc(sizeof(tpArvore));
    if (pontArvore == NULL)
    {
        return ARV_CondRetFaltouMemoria;
    } /* if */

    ((tpArvore *)pontArvore)->pNoRaiz = NULL;
    ((tpArvore *)pontArvore)->pNoCorr = NULL;

    return ARV_CondRetOK;

} /* Fim função: ARV Criar árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

void ARV_DestruirArvore(void *pontArvore)
{

    if (pontArvore != NULL)
    {
        if (((tpArvore *)pontArvore)->pNoRaiz != NULL)
        {
            DestroiArvore(((tpArvore *)pontArvore)->pNoRaiz);
        } /* if */
        free(pontArvore);
        pontArvore = NULL;
    } /* if */

} /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

ARV_tpCondRet ARV_InserirEsquerda(void *pontArvore, char ValorParm)
{

    ARV_tpCondRet CondRet;

    tpNoArvore *pCorr;
    tpNoArvore *pNo;

    /* Tratar vazio, esquerda */

    CondRet = CriarNoRaiz(pontArvore, ValorParm);
    if (CondRet != ARV_CondRetNaoCriouRaiz)
    {
        return CondRet;
    } /* if */

    /* Criar nó à esquerda de folha */

    pCorr = ((tpArvore *)pontArvore)->pNoCorr;
    if (pCorr == NULL)
    {
        return ARV_CondRetErroEstrutura;
    } /* if */

    if (pCorr->pNoEsq == NULL)
    {
        pNo = CriarNo(ValorParm);
        if (pNo == NULL)
        {
            return ARV_CondRetFaltouMemoria;
        } /* if */
        pNo->pNoPai = pCorr;
        pCorr->pNoEsq = pNo;
        ((tpArvore *)pontArvore)->pNoCorr = pNo;

        return ARV_CondRetOK;
    } /* if */

    /* Tratar não folha à esquerda */

    return ARV_CondRetNaoEhFolha;

} /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

ARV_tpCondRet ARV_InserirDireita(void *pontArvore, char ValorParm)
{

    ARV_tpCondRet CondRet;

    tpNoArvore *pCorr;
    tpNoArvore *pNo;

    /* Tratar vazio, direita */

    CondRet = CriarNoRaiz(pontArvore, ValorParm);
    if (CondRet != ARV_CondRetNaoCriouRaiz)
    {
        return CondRet;
    } /* if */

    /* Criar nó à direita de folha */

    pCorr = ((tpArvore *)pontArvore)->pNoCorr;
    if (pCorr == NULL)
    {
        return ARV_CondRetErroEstrutura;
    } /* if */

    if (pCorr->pNoDir == NULL)
    {
        pNo = CriarNo(ValorParm);
        if (pNo == NULL)
        {
            return ARV_CondRetFaltouMemoria;
        } /* if */
        pNo->pNoPai = pCorr;
        pCorr->pNoDir = pNo;
        ((tpArvore *)pontArvore)->pNoCorr = pNo;

        return ARV_CondRetOK;
    } /* if */

    /* Tratar não folha à direita */

    return ARV_CondRetNaoEhFolha;

} /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

ARV_tpCondRet ARV_IrPai(void *pontArvore)
{

    if (pontArvore == NULL)
    {
        return ARV_CondRetArvoreNaoExiste;
    } /* if */
    if (((tpArvore *)pontArvore)->pNoCorr == NULL)
    {
        return ARV_CondRetArvoreVazia;
    } /* if */

    if (((tpArvore *)pontArvore)->pNoCorr->pNoPai != NULL)
    {
        ((tpArvore *)pontArvore)->pNoCorr = ((tpArvore *)pontArvore)->pNoCorr->pNoPai;
        return ARV_CondRetOK;
    }
    else
    {
        return ARV_CondRetNohEhRaiz;
    } /* if */

} /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
*  ****/

ARV_tpCondRet ARV_IrNoEsquerda(void *pontArvore)
{

    if (pontArvore == NULL)
    {
        return ARV_CondRetArvoreNaoExiste;
    } /* if */

    if (((tpArvore *)pontArvore)->pNoCorr == NULL)
    {
        return ARV_CondRetArvoreVazia;
    } /* if */

    if (((tpArvore *)pontArvore)->pNoCorr->pNoEsq == NULL)
    {
        return ARV_CondRetNaoPossuiFilho;
    } /* if */

    ((tpArvore *)pontArvore)->pNoCorr = ((tpArvore *)pontArvore)->pNoCorr->pNoEsq;
    return ARV_CondRetOK;

} /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

ARV_tpCondRet ARV_IrNoDireita(void *pontArvore)
{

    if (pontArvore == NULL)
    {
        return ARV_CondRetArvoreNaoExiste;
    } /* if */

    if (((tpArvore *)pontArvore)->pNoCorr == NULL)
    {
        return ARV_CondRetArvoreVazia;
    } /* if */

    if (((tpArvore *)pontArvore)->pNoCorr->pNoDir == NULL)
    {
        return ARV_CondRetNaoPossuiFilho;
    } /* if */

    ((tpArvore *)pontArvore)->pNoCorr = ((tpArvore *)pontArvore)->pNoCorr->pNoDir;
    return ARV_CondRetOK;

} /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

ARV_tpCondRet ARV_ObterValorCorr(void *pontArvore, char *ValorParm)
{

    if (pontArvore == NULL)
    {
        return ARV_CondRetArvoreNaoExiste;
    } /* if */
    if (((tpArvore *)pontArvore)->pNoCorr == NULL)
    {
        return ARV_CondRetArvoreVazia;
    } /* if */
    *ValorParm = ((tpArvore *)pontArvore)->pNoCorr->Valor;

    return ARV_CondRetOK;

} /* Fim função: ARV Obter valor corrente */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

tpNoArvore *CriarNo(char ValorParm)
{

    tpNoArvore *pNo;

    pNo = (tpNoArvore *)malloc(sizeof(tpNoArvore));
    if (pNo == NULL)
    {
        return NULL;
    } /* if */

    pNo->pNoPai = NULL;
    pNo->pNoEsq = NULL;
    pNo->pNoDir = NULL;
    pNo->Valor = ValorParm;
    return pNo;

} /* Fim função: ARV Criar nó da árvore */

/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

ARV_tpCondRet CriarNoRaiz(void *pontArvore, char ValorParm)
{

    ARV_tpCondRet CondRet;
    tpNoArvore *pNo;

    if (pontArvore == NULL)
    {
        CondRet = ARV_CriarArvore(pontArvore);

        if (CondRet != ARV_CondRetOK)
        {
            return CondRet;
        } /* if */
    }     /* if */

    if (((tpArvore *)pontArvore)->pNoRaiz == NULL)
    {
        pNo = CriarNo(ValorParm);
        if (pNo == NULL)
        {
            return ARV_CondRetFaltouMemoria;
        } /* if */
        ((tpArvore *)pontArvore)->pNoRaiz = pNo;
        ((tpArvore *)pontArvore)->pNoCorr = pNo;

        return ARV_CondRetOK;
    } /* if */

    return ARV_CondRetNaoCriouRaiz;

} /* Fim função: ARV Criar nó raiz da árvore */

/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

void DestroiArvore(tpNoArvore *pNo)
{

    if (pNo->pNoEsq != NULL)
    {
        DestroiArvore(pNo->pNoEsq);
    } /* if */

    if (pNo->pNoDir != NULL)
    {
        DestroiArvore(pNo->pNoDir);
    } /* if */

    free(pNo);

} /* Fim função: ARV Destruir a estrutura da árvore */

/********** Fim do módulo de implementação: Módulo árvore **********/
