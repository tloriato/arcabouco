/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              testtabuleiro.c
*  Letras identificadoras:      TTAB
*
*  Projeto: Disciplina INF 1301
*  Autores:
*
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00  ???    19/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo tabuleiro.
*
*  $EIU Interface com o usuário
*     Comandos de teste específicos para testar o módulo tabuleiro:
*
*     =criar - chama a função TAB_Criar( )
*
*     =destruir - chama a função TAB_Destruir( )
*
*     =incluir <int, int> - chama a função TAB_IncluirPeca( )
*         Parâmetros:
*         1 - posicao: Posição do tabuleiro aonde será incluída a peça
*         2 - pPeca: Peça a ser incluída
*
*     =mover <int, int> - chama a função TAB_MoverPeca( )
*         Parâmetros:
*         1 - de: Posição de origem da peça
*         2 - para: Posição de destino da peça
*
*     =remover <int, int> - chama a função TAB_RemoverPeca( )
*         Parâmetros:
*         1 - posicao: Posição da peça
*         2 - peca: Parâmetro para retorno da peça removida
*                   Esse parâmetro é passado por referência
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tst_espc.h"
#include "generico.h"
#include "lerparam.h"
#include "tabuleiro.h"

/* Tabela os nomes dos comandos de teste específicos */

const char CMD_CRIAR        [] = "=criar" ;
const char CMD_DESTRUIR     [] = "=destruir" ;
const char CMD_INCLUIR_PECA [] = "=incluir" ;
const char CMD_MOVER_PECA   [] = "=mover" ;
const char CMD_REMOVER_PECA [] = "=remover" ;


