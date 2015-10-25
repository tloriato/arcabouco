/**********************************************************************
*
*  $MCD Módulo de definição: Módulo dado pontos
*
*  Arquivo gerado:              dado_pontos.c
*  Letras identificadoras:      DPO
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           pa - Pedro Alvarez
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor               Data     Observações
*       1.00  gbo, gapm, tdn    18/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Encapsula uma estrutura DadoPontos, armazena qual jogador pode 
*     dobrar o valor da partida e informa o valor atual da partida.
*
***********************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   "dado_pontos.h"
#include   <assert.h>

#define PODE 1
#define NAO_PODE 0


typedef struct dadopontos {

   int ValorPartida;
      /* Valor da partida no momento */

   DPO_tpJogador JogadorPodeDobrar;
      /* Qual jogador que pode dobrar o valor da partida */

} DadoPontos ;


/*****  Variáveis globais ao módulo  *****/

   static DadoPontos Pontos = { 1 , DPO_Jogador1 } ;


/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: DPO Dobrar pontos
*  ****/

   DPO_tpCondRet DPO_DobrarPontos( DPO_tpJogador jogador )
   {

      if ( Pontos.ValorPartida == 64 )
      {
         return DPO_CondRetMaxPontos;
      } /* if */

      Pontos.ValorPartida *= 2;

      if ( jogador == DPO_Jogador1 )
      {
         Pontos.JogadorPodeDobrar = DPO_Jogador2 ;
      } else
      {
         Pontos.JogadorPodeDobrar = DPO_Jogador1 ;
      } /* if */

      return DPO_CondRetOK ;

   } /* Fim função: DPO Dobrar pontos */


/***************************************************************************
*
*  Função: DPO Pode dobrar
*  ****/

   DPO_tpCondRet DPO_PodeDobrar( DPO_tpJogador jogador , int * res )
   {

      assert ( res != NULL ) ;

      if ( Pontos.ValorPartida == 1 )
      {
         *res = PODE ;
      } else
      {
         if ( jogador == Pontos.JogadorPodeDobrar )
         {
            *res = PODE ;
         } else
         {
            *res = NAO_PODE ;
            return DPO_JogadorNaoPodeDobrar ;
         } /* if */
      } /* if */

      return DPO_CondRetOK ;

   } /* Fim função: DPO Pode dobrar */


/***************************************************************************
*
*  Função: DPO Obter pontos
*  ****/

   DPO_tpCondRet DPO_ObterPontos( int * pontos )
   {

      assert ( pontos != NULL ) ;

      *pontos = Pontos.ValorPartida;

      return DPO_CondRetOK ;

   } /* Fim função: DPO Obter pontos */


/***************************************************************************
*
*  Função: DPO Obter pontos
*  ****/

   DPO_tpCondRet DPO_DefinirPontosVez( int pontos , DPO_tpJogador jogador )
   {

      assert( ( pontos == 1 ) || ( pontos == 2 )  || ( pontos == 4 )  ||
              ( pontos == 8 ) || ( pontos == 16 ) || ( pontos == 32 ) || 
              ( pontos == 64 ) ) ;

      Pontos.ValorPartida = pontos ;
      Pontos.JogadorPodeDobrar = jogador ;

      return DPO_CondRetOK ;

   } /* Fim função: DPO Definir Pontos e Vez


/********** Fim do módulo de implementação: Módulo dado pontos **********/

