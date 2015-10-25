/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              testdado_pontos.c
*  Letras identificadoras:      TDPO
*
*  Projeto: Disciplina INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           pa - Pedro Alvarez
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor             Data       Observações
*       1.00  gbo, gapm, tdn    18/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo dado pontos.
*
*  $EIU Interface com o usuário
*     Comandos de teste específicos para testar o módulo dado pontos:
*
*     =dobrar < int > - chama a função DPO_DobrarPontos( )
*        Parâmetros:
*        1 - jogador: jogador que irá dobrar a partida
*
*     =podedobrar < int, int > - chama a função DPO_PodeDobrar( )
*        Parâmetros:
*        1 - jogador: Jogador
*        2 - res: Resposta: 1 se o jogador pode dobrar. 0 caso contrário
*
*     =obterpontos < int > - chama a função DPO_ObterPontos( )
*        Parâmetros:
*        1 - pontos: Valor da partida esperado
*
*     =definirpontosvez < int , int > - chama a função DPO_DefinirPontosVez( )
*        Parâmetros:
*        1 - pontos: Novo valor da partida
*        2 - jogador: Jogador de quem será a próxima vez de dobrar os pontos
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tst_espc.h"
#include "generico.h"
#include "lerparm.h"
#include "dado_pontos.h"

/* Tabela os nomes dos comandos de teste específicos */

const char CMD_DOBRAR_PONTOS      [] = "=dobrar" ;
const char CMD_PODE_DOBRAR        [] = "=podedobrar" ;
const char CMD_OBTER_PONTOS       [] = "=obterpontos" ;
const char CMD_DEFINIR_PONTOS_VEZ [] = "=definirpontosvez" ;


TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
   int numLidos   = -1 ,
       paramLido  = -1 ,
       paramLido2 = -1 ,
       CondRetEsp = -1 ,
       Res        = -1 ;

   DPO_tpCondRet Ret = DPO_CondRetOK ;

   /* Testar Dobrar pontos */
   if ( strcmp( ComandoTeste, CMD_DOBRAR_PONTOS) == 0 ) 
   {
      numLidos = LER_LerParametros ( "ii" , 
                        &paramLido, &CondRetEsp ) ;

      if ( numLidos != 2 )
      {
         return TST_CondRetParm ;
      } /* if */

      return TST_CompararInt ( CondRetEsp , DPO_DobrarPontos ( ( DPO_tpJogador ) paramLido ) , 
               "Retorno diferente do esperado." ) ;
   } /* Fim da ativa: Dobrar pontos */

   /* Testar Pode dobrar */
   else if ( strcmp( ComandoTeste, CMD_PODE_DOBRAR ) == 0 )
   {
      numLidos = LER_LerParametros ( "ii" ,
                     &paramLido , &CondRetEsp ) ;

      if ( numLidos != 2 ) 
      {
         return TST_CondRetParm ;
      } /* if */

      return TST_CompararInt ( CondRetEsp , DPO_PodeDobrar ( ( DPO_tpJogador ) paramLido , &Res ) ,
               "Retorno diferente do esperado." ) ;
   } /* Fim da ativa: Pode dobrar */

   /* Testar Obter pontos */
   else if ( strcmp( ComandoTeste, CMD_OBTER_PONTOS ) == 0 )
   {
      numLidos = LER_LerParametros ( "ii" , &paramLido ,
                        &CondRetEsp ) ;

      if ( numLidos != 2 )
      {
         return TST_CondRetParm ;
      } /* if */

      Ret = DPO_ObterPontos ( &Res ) ;

      if ( ( Ret == DPO_CondRetOK ) && ( Res != paramLido ) )
      {
         TST_NotificarFalha( "Pontos obtidos diferentes do esperado." ) ;
      }

      return TST_CompararInt ( CondRetEsp , Ret  ,
               "Retorno diferente do esperado." ) ;
   } /* Fim da ativa: Obter pontos */

   /* Testar Definir Pontos e Vez */
   else if ( strcmp( ComandoTeste , CMD_DEFINIR_PONTOS_VEZ ) == 0 )
   {
      numLidos = LER_LerParametros ( "iii" , &paramLido , &paramLido2 , &CondRetEsp ) ;

      if ( numLidos != 3 ) 
      {
         return TST_CondRetParm ;
      } /* if */

      return TST_CompararInt ( CondRetEsp , DPO_DefinirPontosVez ( paramLido , ( DPO_tpJogador ) paramLido2 ) ,
               "Retorno diferente do esperado." ) ;
   } /* Fim da ativa: Pode dobrar */


   return TST_CondRetNaoConhec ;

} /* Fim função: TST Efetuar Comando */

/********** Fim do módulo de implementação: TDPO Teste Dados Pontos **********/
