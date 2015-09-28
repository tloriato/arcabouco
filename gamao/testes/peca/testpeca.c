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
#include "lerparm.h"
#include "peca.h"

/* Tabela os nomes dos comandos de teste específicos */

const char CMD_CRIAR     [] = "=criar" ;
const char CMD_DESTRUIR  [] = "=destruir" ;
const char CMD_OBTER_COR [] = "=obtercor" ;

#define VAL_PEC( id ) do { if ( ( ( id ) > 1 ) || ( ( id ) < 0 ) ) { return TST_CondRetParm ; } } while ( 0 )

/*****  Variáveis globais à este módulo  *****/

/***************************************************************************
*
*  Ponteiro: Peca
*  Descrição: Ponteiro para o struct tpPeca usado nos testes
*
*  ****/

static PEC_tppPeca pecas[2]  = { NULL } ;


TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
   int numLidos   = -1 ,
       idPec      = -1 ,
       CondRetEsp = -1 ,
       cor        = -1 ,
       corPec     = -1 ;

   PEC_tpCondRet ret ;

   /* Testar a Criar Peça */
   if ( strcmp( ComandoTeste, CMD_CRIAR) == 0 )
   {
      numLidos = LER_LerParametros ( "iii" ,
                        &idPec, &cor, &CondRetEsp ) ;

      if ( numLidos != 3 )
      {
         return TST_CondRetParm ;
      } /* if */

      VAL_PEC( idPec ) ;
      return TST_CompararInt ( CondRetEsp , PEC_Criar( &pecas[ idPec ], cor ) ,
               "Retorno diferente do esperado." ) ;
    } /* Fim da ativa: Criar Peça */

    /* Testar Destruir Peça */
   else if ( strcmp( ComandoTeste, CMD_DESTRUIR ) == 0 )
   {
      numLidos = LER_LerParametros ( "ii" ,
                     &idPec , &CondRetEsp ) ;

      if ( numLidos != 2 )
      {
         return TST_CondRetParm ;
      } /* if */

      VAL_PEC( idPec ) ;
      return TST_CompararInt ( CondRetEsp , PEC_Destruir( pecas[ idPec ] ) ,
            "Retorno diferente do esperado." ) ;
   } /* Fim da ativa: Destruir Peça */

   /* Testar Obter cor */
   else if ( strcmp( ComandoTeste, CMD_OBTER_COR ) == 0 )
   {
      numLidos = LER_LerParametros ( "iii" ,
                     &idPec, &cor, &CondRetEsp ) ;

      if ( numLidos != 3 )
      {
         return TST_CondRetParm ;
      } /* if */

      VAL_PEC( idPec ) ;
      ret = PEC_ObterCor( pecas[ idPec ], &corPec ) ;

      if ( ret == PEC_CondRetOK )
      {
         return TST_CompararInt( cor , corPec , "Cor da peça diferente da esperada." ) ;
      }

      return TST_CompararInt ( CondRetEsp , ret , "Retorno diferente do esperado." ) ;
   } /* Fim da ativa: Obter pontos */

   return TST_CondRetNaoConhec ;

}

/********** Fim do módulo de implementação: TDPO Teste Dados Pontos **********/
