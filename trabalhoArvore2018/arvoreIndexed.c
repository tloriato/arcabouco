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
*       4.00   tls   28/03/2018 Adicionado à possibilidade de múltiplas árvores.
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

#define ARV_MAX_INDEX 5

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

static tpArvore *vetorArvores[ARV_MAX_INDEX];
/* Vetor de ponteiros de Arvores */

static tpArvore *(*pVetArvores)[] = &vetorArvores;
/* Ponteiro explicito para um vetor de ponteiros de arvores */

static tpArvore *pArvore = NULL;
/* Ponteiro para a cabeça da árvore */

/***** Protótipos das funções encapuladas no módulo *****/

static tpNoArvore *CriarNo(char ValorParm);

static ARV_tpCondRet CriarNoRaiz(int indexParam, char ValorParm);

static void DestroiArvore(tpNoArvore *pNo);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

ARV_tpCondRet ARV_CriarArvore(int indexParam)
{
    /* Legacy 
    if (pArvore != NULL)
    {
        ARV_DestruirArvore();
    } /* if */
    /* 
    pArvore = (tpArvore *)malloc(sizeof(tpArvore));
    if (pArvore == NULL)
    {
        return ARV_CondRetFaltouMemoria;
    } /* if */
    /*
    pArvore->pNoRaiz = NULL;
    pArvore->pNoCorr = NULL;
    */

    if ((*pVetArvores)[indexParam] != NULL)
    {
        return ARV_CondRetJaOcupada;
    }

    (*pVetArvores)[indexParam] = (tpArvore *)malloc(sizeof(tpArvore));

    if ((*pVetArvores)[indexParam] == NULL) 
    {
        return ARV_CondRetFaltouMemoria;
    }

    (*pVetArvores)[indexParam]->pNoRaiz = NULL;
    (*pVetArvores)[indexParam]->pNoCorr = NULL;



    return ARV_CondRetOK;

} /* Fim função: ARV Criar árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

void ARV_DestruirArvore(int indexParam)
{
    if ((*pVetArvores)[indexParam] != NULL)
    {
        if ((*pVetArvores)[indexParam]->pNoRaiz != NULL)
        {
            DestroiArvore((*pVetArvores)[indexParam]->pNoRaiz);
        }
        free((*pVetArvores)[indexParam]);
        (*pVetArvores)[indexParam] = NULL;
    }

    /* Legacy
    if (pArvore != NULL)
    {
        if (pArvore->pNoRaiz != NULL)
        {
            DestroiArvore(pArvore->pNoRaiz);
        } /* if *//*
        free(pArvore);
        pArvore = NULL;
    } /* if */

} /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

ARV_tpCondRet ARV_InserirEsquerda(int indexParam, char ValorParm)
{

    ARV_tpCondRet CondRet;

    tpNoArvore *pCorr;
    tpNoArvore *pNo;

    /* Tratar vazio, esquerda */

    CondRet = CriarNoRaiz(indexParam, ValorParm);
    if (CondRet != ARV_CondRetNaoCriouRaiz) // Eu não acho que isso faça sentido, mas
    {                                       // já esta aqui desde 2003
        return CondRet;
    } /* if */

    /* Criar nó à esquerda de folha */

    pCorr = (*pVetArvores)[indexParam]->pNoCorr;
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
        (*pVetArvores)[indexParam]->pNoCorr = pNo;

        return ARV_CondRetOK;
    } /* if */

    /* Tratar não folha à esquerda */

    return ARV_CondRetNaoEhFolha;

} /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

ARV_tpCondRet ARV_InserirDireita(int indexParam, char ValorParm)
{

    ARV_tpCondRet CondRet;

    tpNoArvore *pCorr;
    tpNoArvore *pNo;

    /* Tratar vazio, direita */

    CondRet = CriarNoRaiz(indexParam, ValorParm);
    if (CondRet != ARV_CondRetNaoCriouRaiz)
    {
        return CondRet;
    } /* if */

    /* Criar nó à direita de folha */

    pCorr = (*pVetArvores)[indexParam]->pNoCorr;
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
        (*pVetArvores)[indexParam]->pNoCorr = pNo;

        return ARV_CondRetOK;
    } /* if */

    /* Tratar não folha à direita */

    return ARV_CondRetNaoEhFolha;

} /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

ARV_tpCondRet ARV_IrPai(int indexParam)
{

    if ((*pVetArvores)[indexParam] == NULL)
    {
        return ARV_CondRetArvoreNaoExiste;
    } /* if */
    if ((*pVetArvores)[indexParam]->pNoCorr == NULL)
    {
        return ARV_CondRetArvoreVazia;
    } /* if */

    if ((*pVetArvores)[indexParam]->pNoCorr->pNoPai != NULL)
    {
        (*pVetArvores)[indexParam]->pNoCorr = (*pVetArvores)[indexParam]->pNoCorr->pNoPai;
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

ARV_tpCondRet ARV_IrNoEsquerda(int indexParam)
{

    if ((*pVetArvores)[indexParam] == NULL)
    {
        return ARV_CondRetArvoreNaoExiste;
    } /* if */

    if ((*pVetArvores)[indexParam]->pNoCorr == NULL)
    {
        return ARV_CondRetArvoreVazia;
    } /* if */

    if ((*pVetArvores)[indexParam]->pNoCorr->pNoEsq == NULL)
    {
        return ARV_CondRetNaoPossuiFilho;
    } /* if */

    (*pVetArvores)[indexParam]->pNoCorr = (*pVetArvores)[indexParam]->pNoCorr->pNoEsq;
    return ARV_CondRetOK;

} /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

ARV_tpCondRet ARV_IrNoDireita(int indexParam)
{

    if ((*pVetArvores)[indexParam] == NULL)
    {
        return ARV_CondRetArvoreNaoExiste;
    } /* if */

    if ((*pVetArvores)[indexParam]->pNoCorr == NULL)
    {
        return ARV_CondRetArvoreVazia;
    } /* if */

    if ((*pVetArvores)[indexParam]->pNoCorr->pNoDir == NULL)
    {
        return ARV_CondRetNaoPossuiFilho;
    } /* if */

    (*pVetArvores)[indexParam]->pNoCorr = (*pVetArvores)[indexParam]->pNoCorr->pNoDir;
    return ARV_CondRetOK;

} /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

ARV_tpCondRet ARV_ObterValorCorr(int indexParam, char *ValorParm)
{

    if ((*pVetArvores)[indexParam] == NULL)
    {
        return ARV_CondRetArvoreNaoExiste;
    } /* if */
    if ((*pVetArvores)[indexParam]->pNoCorr == NULL)
    {
        return ARV_CondRetArvoreVazia;
    } /* if */
    *ValorParm = (*pVetArvores)[indexParam]->pNoCorr->Valor;

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

ARV_tpCondRet CriarNoRaiz(int indexParam, char ValorParm)
{

    ARV_tpCondRet CondRet;
    tpNoArvore *pNo;

    if ((*pVetArvores)[indexParam] == NULL)
    {
        CondRet = ARV_CriarArvore(indexParam);

        if (CondRet != ARV_CondRetOK)
        {
            return CondRet;
        } /* if */
    }     /* if */

    if ((*pVetArvores)[indexParam]->pNoRaiz == NULL)
    {
        pNo = CriarNo(ValorParm);
        if (pNo == NULL)
        {
            return ARV_CondRetFaltouMemoria;
        } /* if */
        (*pVetArvores)[indexParam]->pNoRaiz = pNo;
        (*pVetArvores)[indexParam]->pNoCorr = pNo;

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
