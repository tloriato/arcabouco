/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              testdado_pontos.c
*  Letras identificadoras:      TDPO
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
*     Este módulo contém as funções específicas para o teste do
*     módulo dado pontos.
*
*  $EIU Interface com o usuário
*     Comandos de teste específicos para testar o módulo dado pontos:
*
*     =dobrar - chama a função DPO_DobrarPontos( )
*
*     =podedobrar <int, int> - chama a função DPO_PodeDobrar( )
*         Parâmetros:
*         1 - jogador: Jogador
*         2 - res: Resposta: 1 se o jogador pode dobrar. 0 caso contrário
*                  Esse parâmetro é passado por referência
*
*     =obterpontos <int> - chama a função DPO_ObterPontos( )
*         Parâmetros:
*         1 - pontos: Retorno do valor da partida
*                     Esse parâmetro é passado por referência
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tst_espc.h"
#include "generico.h"
#include "lerparam.h"
#include "dado_pontos.h"

/* Tabela os nomes dos comandos de teste específicos */

const char CMD_DOBRAR_PONTOS [] = "=dobrar" ;
const char CMD_PODE_DOBRAR   [] = "=podedobrar" ;
const char CMD_OBTER_PONTOS  [] = "=obterpontos" ;


