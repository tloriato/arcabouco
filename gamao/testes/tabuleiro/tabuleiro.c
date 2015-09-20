/**********************************************************************
*
*  $MCD Módulo de definição: Módulo tabuleiro
*
*  Arquivo gerado:              tabuleiro.c
*  Letras identificadoras:      TAB
*
*  Projeto: Disciplina INF 1301
*  Autores: gbdo - Gabriel Barbosa de Oliveira
*           gdapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor                Data     Observações
*       1.00  gbdo, gdapm, tdn   19/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Descrição...
*
***********************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   "tabuleiro.h"
#include   "lista.h"


/***********************************************************************
*
*  Definição: MAT Quantidade de posições no tabuleiro
*
***********************************************************************/

#define QUANTIDADE_POS 24


/***********************************************************************
*
*  $TC Tipo de dados: TAB Estrutura tabuleiro
*
*
***********************************************************************/

typedef struct
{
   LIS_tppLista posicoes ;
      /* Lista de posições do tabuleiro.
       * Cada posição dessa lista contém uma lista com as peças
       * presentes da respectiva posição
       */
} tpTabuleiro ;


/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: TAB Criar
*  ****/

   TAB_tpCondRet Criar( TAB_tppTabuleiro * pTabuleiro )
   {

      tpTabuleiro * tab = ( tpTabuleiro *) malloc( sizeof( tpTabuleiro )) ;
      if ( tab == NULL )
         return TAB_CondRetFaltaMemoria ;

      tab->posicoes = 

   } /* Fim função: TAB Criar */


/***************************************************************************
*
*  Função: TAB Destruir
*  ****/

   TAB_tpCondRet Destruir( TAB_tppTabuleiro tabuleiro )
   {

   } /* Fim função: TAB Destruir */


/***************************************************************************
*
*  Função: TAB Incluir peça
*  ****/

   TAB_tpCondRet IncluirPeca( TAB_tppTabuleiro tabuleiro , unsigned int posicao , PEC_tppPeca pPeca )
   {

   } /* Fim função: TAB Incluir peça */


/***************************************************************************
*
*  Função: TAB Mover peça
*  ****/

   TAB_tpCondRet MoverPeca( TAB_tppTabuleiro tabuleiro , unsigned int de , unsigned int para )
   {

   } /* Fim função: TAB Mover peça */


/***************************************************************************
*
*  Função: TAB Remover peça
*  ****/

   TAB_tpCondRet RemoverPeca( TAB_tppTabuleiro tabuleiro , unsigned int posicao , PEC_tppPeca * peca )
   {

   } /* Fim função: TAB Remover peça */


/*****  Código das funções encapsuladas pelo módulo  *****/


/********** Fim do módulo de implementação: Módulo tabuleiro **********/

