/***************************************************************************
*  $MCI Módulo de implementação: TPFN Teste peças finalizadas
*
*  Arquivo gerado:              TestPFN.c
*  Letras identificadoras:      TPFN
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

#include    "PecasFinalizadas.h"
#include	"peca.h"
#include    "lista.h"


static const char CRIAR_PFN_CMD           [ ] = "=criar"      ;
static const char DESTRUIR_PFN_CMD        [ ] = "=destruir"   ;
static const char INS_PECA_CMD            [ ] = "=inspeca"    ;
static const char CONTA_PECAS_CMD         [ ] = "=contapecas" ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10

static PEC_tppPeca peca = { NULL } ;
PFN_tppFinalizadas   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxLista( int inxLista , int Modo ) ;
   static void LiberarValor( void * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPFN &Testar pecas finalizadas
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =criar                   inxLista
*     =destruir                inxLista
*     =inspeca                 inxLista  int   CondRetEsp
*     =contapecas              inxLista  CondRetEsp
*     
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista   = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
		  cor        = -1 ,
		  ValEsp     = -1 ,
		  numElem    = -1 ,
		  qtd        = -1 ;

      PFN_tpCondRet CondRet ;
      PFN_tpCondRet Ret ;

      /* Testar Criar */

      if ( strcmp( ComandoTeste , CRIAR_PFN_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , VAZIO )))
         {
            return TST_CondRetParm ;
         } /* if */

         Ret = PFN_Criar ( &vtListas[ inxLista ] ) ;

         if ( Ret != PFN_CondRetOK )
         {
            return TST_CompararInt( ValEsp , Ret , "Retorno diferente do esperado." ) ;
         } /* if */

         return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista de pecas finalizadas."  ) ;

      } /* fim ativa: Testar Criar */

      /* Testar Destruir */

      else if ( strcmp( ComandoTeste , DESTRUIR_PFN_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
         {
            return TST_CondRetParm ;
         } /* if */

         Ret = PFN_Destruir ( vtListas[ inxLista ] ) ;
         vtListas[ inxLista ] = NULL ;

         return TST_CompararInt( ValEsp , Ret , "Retorno diferente do esperado." ) ;

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

         CondRet = PFN_InserirPeca( vtListas[ inxLista ] , peca ) ;

         return TST_CompararInt( CondRetEsp , CondRet ,
               "Condicao de retorno errada ao inserir pecça." ) ;

      } /* fim ativa: Testar inserir peca */

      /* PFN  &Contar Peças */

      else if ( strcmp( ComandoTeste , CONTA_PECAS_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "iii" , &inxLista , &cor ,
               &ValEsp ) ;

         if ( ( numLidos != 3 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

		 PFN_ContaPecas ( vtListas[ inxLista ] , &qtd , cor ) ;

         return TST_CompararInt( ValEsp , qtd ,
                  "Condicao de retorno errada ao contar pecas" ) ;

      } /* fim ativa: PFN  &Contar peças */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TPFN &Testar peças finalizadas */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
 *
 *  $FC Função: TLIS Validar indice de lista
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

} /* Fim função: TLIS Validar indice de lista */

/***********************************************************************
 *
 *  $FC Função: TLIS Validar indice de lista
 *
 ***********************************************************************/

   static void LiberarValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS Liberar Valor */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

