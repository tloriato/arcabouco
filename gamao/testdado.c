/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              testdado.c
*  Letras identificadoras:      TDAD
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
*     módulo dado.
*
*  $EIU Interface com o usuário
*     Comandos de teste específicos para testar o módulo dado:
*
*     =jogar - chama a função DAD_JogarDados( )
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tst_espc.h"
#include "generico.h"
#include "lerparam.h"
#include "dado.h"

/* Tabela os nomes dos comandos de teste específicos */

const char CMD_JOGAR_DADOS [] = "=jogar" ;


