#if ! defined( DADO_PONTOS_ )
#define DADO_PONTOS_
/**********************************************************************
*
*  $MCD Módulo de definição: Módulo dado pontos
*
*  Arquivo gerado:              dado_pontos.h
*  Letras identificadoras:      DPO
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor               Data     Observações
*       1.00  gbo, gapm, tdn    18/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Descrição...
*
***********************************************************************/


/***********************************************************************
*
*  $TC Tipo de dados: DPO Condições de retorno
*
*
***********************************************************************/

   typedef enum {

      DPO_CondRetOK = 0 ,
          /* Rodou sem erros */

      DPO_CondRetMaxPontos = 1
          /* Valor da partida já atingiu o máximo */

   } DPO_tpCondRet ;


/***********************************************************************
*
*  $FC Função: DPO Dobrar pontos
*
*  $ED Descrição da função
*     Dobra o valor da partida
*
*  $FV Valor retornado
*     DPO_CondRetOK
*     DPO_CondRetMaxPontos
*
***********************************************************************/

   DPO_tpCondRet DobrarPontos( void ) ;

/***********************************************************************
*
*  $FC Função: DPO Pode dobrar
*
*  $ED Descrição da função
*     Verifica se o jogador pode dobrar a pontuação da partida
*
*  $EP Parâmetros
*     $P jogador - Jogador
*     $P res     - Resposta: 1 se o jogador pode dobrar. 0 caso contrário
*                  Esse parâmetro é passado por referência
*
*  $FV Valor retornado
*     DPO_CondRetOK
*
***********************************************************************/

   DPO_tpCondRet PodeDobrar( DPO_tpJogador jogador , int * res ) ;

/***********************************************************************
*
*  $FC Função: DPO Obter pontos
*
*  $ED Descrição da função
*     Obtém o valor atual da partida
*
*  $EP Parâmetros
*     $P pontos - Retorno do valor da partida
*                 Esse parâmetro é passado por referência
*
*  $FV Valor retornado
*     DPO_CondRetOK
*
***********************************************************************/

   DPO_tpCondRet ObterPontos( int * pontos ) ;


#undef DADO_PONTOS_

/********** Fim do módulo de definição: Módulo dado pontos **********/

#else
#endif
