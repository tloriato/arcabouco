/**********************************************************************
*
*  $MCD Módulo de definição: Módulo dado
*
*  Arquivo gerado:              dado.c
*  Letras identificadoras:      DAD
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor             Data       Observações
*       1.00  gbo, gapm, tdn    18/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Gera dois números aleatórios.
*
***********************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   "dado.h"
#include   <time.h>
#include   <assert.h>


/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: DAD Jogar Dados
*  ****/

   DAD_tpCondRet DAD_JogarDados( int* pDado1 , int* pDado2 )
   {

      assert ( pDado1 != NULL && pDado2 != NULL ) ;

      * pDado1 = ( rand ( ) % 6 ) +1 ;
      * pDado2 = ( rand ( ) % 6 ) +1 ;

      return DAD_CondRetOK ;

   } /* Fim função: DAD Jogar Dados */


/*****  Código das funções encapsuladas pelo módulo  *****/


/********** Fim do módulo de implementação: Módulo dado **********/

