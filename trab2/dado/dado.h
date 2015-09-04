#if ! defined( DADO_ )
#define DADO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo dado
*
*  Arquivo gerado:              dado.h
*  Letras identificadoras:      DAD
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   tdn   03/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa uma função para simular a jogada de
*     dois dados de 6 faces.
*
***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados: DAD Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0
               /* Executou correto */

   } DAD_tpCondRet ;


/***********************************************************************
*
*  $FC Função: DAD Jogar Dados
*
*  $ED Descrição da função
*     Sorteia dois números aleatórios entre 1 e 6 cada.
*
*  $EP Parâmetros
*     $P pD1 - parâmetro para retorno do resultado do primeiro dado.
*              esse parâmetro é passado por referência.
*     $P pD2 - parâmetro para retorno do resultado do segundo dado.
*              esse parâmetro é passado por referência.
*
*  $FV Valor retornado
*     DAD_CondRetOK
*
***********************************************************************/

   DAD_tpCondRet DAD_JogarDados( int * pD1 , int * pD2 ) ;


/********** Fim do módulo de definição: Módulo Dado **********/

#endif
