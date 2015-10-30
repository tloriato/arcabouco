/***************************************************************************
*  $MCI Módulo de implementação: TPCA Teste peças capturadas
*
*  Arquivo gerado:              TestPCA.c
*  Letras identificadoras:      TPCA
*
*  Projeto: INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*           pa - Pedro Alvarez
*
*  $HA Histórico de evolução:
*     Versão    Autor               Data        Observações
*     1.00      gbo, gapm, tdn, pa  27/10/2015  Início do desenvolvimento.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "tst_espc.h"

#include    "generico.h"
#include    "lerparm.h"

#include    "PecasCapturadas.h"
#include    "peca.h"
#include    "lista.h"


static const char CRIAR_PCA_CMD           [ ] = "=criar"      ;
static const char DESTRUIR_PCA_CMD        [ ] = "=destruir"   ;
static const char INS_PECA_CMD            [ ] = "=inspeca"    ;
static const char CONTA_PECAS_CMD         [ ] = "=contapecas" ;
static const char REMOVER_PECA_CMD        [ ] = "=remover"    ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10

static PEC_tppPeca peca = { NULL } ;
PCA_tppCapturadas   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPCA &Testar pecas capturadas
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =criar                   inxLista  CondRetEsp
*     =destruir                inxLista  CondRetEsp
*     =inspeca                 inxLista  cor  CondRetEsp
*     =contapecas              inxLista  cor  ValEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista   = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
          cor        = -1 ,
          ValEsp     = -1 ,
          qtd        = -1 ;

      PCA_tpCondRet CondRet ;
      PCA_tpCondRet Ret ;

      /* Testar Criar */

      if ( strcmp( ComandoTeste , CRIAR_PCA_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &CondRetEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , VAZIO )))
         {
            return TST_CondRetParm ;
         } /* if */

         Ret = PCA_Criar ( &vtListas[ inxLista ] ) ;

         if ( Ret != PCA_CondRetOK )
         {
            return TST_CompararInt( CondRetEsp , Ret , "Retorno diferente do esperado." ) ;
         } /* if */

         return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista de pecas capturadas."  ) ;

      } /* fim ativa: Testar Criar */

      /* Testar Destruir */

      else if ( strcmp( ComandoTeste , DESTRUIR_PCA_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &CondRetEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
         {
            return TST_CondRetParm ;
         } /* if */

         Ret = PCA_Destruir( vtListas[ inxLista ] ) ;
         vtListas[ inxLista ] = NULL ;

         return TST_CompararInt( CondRetEsp , Ret , "Retorno diferente do esperado." ) ;

      } /* fim ativa: Testar Destruir */

      /* Testar inserir peca */

      else if ( strcmp( ComandoTeste , INS_PECA_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "iii" ,
               &inxLista , &cor , &CondRetEsp ) ;

         if ( ( numLidos != 3 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

         PEC_Criar ( &peca , cor ) ;

         CondRet = PCA_InserirPeca( vtListas[ inxLista ] , peca ) ;

         return TST_CompararInt( CondRetEsp , CondRet ,
               "Condicao de retorno errada ao inserir pecça." ) ;

      } /* fim ativa: Testar inserir peca */

      /* PCA  &Contar Peças */

      else if ( strcmp( ComandoTeste , CONTA_PECAS_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

       PCA_ContaPecas ( vtListas[ inxLista ] , &qtd ) ;

       return TST_CompararInt( ValEsp , qtd ,
                  "Condicao de retorno errada ao contar pecas" ) ;

      } /* fim ativa: PCA  &Contar peças */

      /* PCA  &Remover Peça */

      else if ( strcmp( ComandoTeste , REMOVER_PECA_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

       Ret = PCA_RemoverPeca ( vtListas[ inxLista ] , &peca ) ;
       PEC_Destruir( peca ) ;

       return TST_CompararInt( ValEsp , Ret ,
                  "Condicao de retorno errada ao remover a peça" ) ;

      } /* fim ativa: PCA  &Remover peça */



      return TST_CondRetNaoConhec ;

   } /* Fim função: TPCA &Testar peças capturadas */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
 *
 *  $FC Função: TPCA Validar indice de lista
 *
 ***********************************************************************/

static int ValidarInxLista( int inxLista , int Modo )
{

   if ( ( inxLista <  0 )
     || ( inxLista >= DIM_VT_LISTA ))
   {
      return FALSE ;
   } /* if */

   if ( Modo == VAZIO )
   {
      if ( vtListas[ inxLista ] != 0 )
      {
         return FALSE ;
      } /* if */
   } else
   {
      if ( vtListas[ inxLista ] == 0 )
      {
         return FALSE ;
      } /* if */
   } /* if */

   return TRUE ;

} /* Fim função: TPCA Validar indice de lista */


/********** Fim do módulo de implementação: TPCA Teste lista de símbolos **********/

