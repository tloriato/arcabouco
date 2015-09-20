/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              testpeca.c
*  Letras identificadoras:      TPEC
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
*     módulo Peça.
*
*  $EIU Interface com o usuário
*     Comandos de teste específicos para testar o módulo Peça:
*
*     =criar <int> - chama a função PEC_Criar( )
*         Parâmetros:
*         1 - cor: Cor da peça
*
*     =destruir - chama a função PEC_Destruir( )
*
*     =obtercor <int> - chama a função PEC_ObterCor( )
*         Parâmetros:
*         1 - Cor: Cor esperada
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tst_espc.h"
#include "generico.h"
#include "lerparam.h"
#include "peca.h"

/* Tabela os nomes dos comandos de teste específicos */

const char CMD_CRIAR     [] = "=criar" ;
const char CMD_DESTRUIR  [] = "=destruir" ;
const char CMD_OBTER_COR [] = "=obtercor" ;


