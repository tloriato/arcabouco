/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista duplamente encadeada
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Projeto: INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão    Autor              Data        Observações
*     2.00      gbo, gapm, tdn     20/09/2015  Lista de ponteiros de void.
*     1.00      gbo, gapm, tdn     28/08/2015  Início do desenvolvimento.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "tst_espc.h"

#include    "generico.h"
#include    "lerparm.h"

#include    "lista.h"


static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"   ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;
static const char DEF_FUNC_EXCLUIR_CMD    [ ] = "=funcexcluir"    ;
static const char PROCURAR_CMD            [ ] = "=procurar"       ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

static LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;
static char caracteres[10] = { '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' } ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxLista( int inxLista , int Modo ) ;
   static void LiberarValor( void * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  caracter  CondRetEsp
*     =inselemapos                  inxLista  caracter  CondRetEsp
*     =obtervalorelem               inxLista  caracter  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*     =funcexcluir                  inxLista  CondRetEsp
*     =procurar                     inxLista  caracter especial CondRetEsp
*
*     Nota: Caracteres especiais: '0' .. '9'. Para estes caracteres não
*           será alocada uma nova área de memória e sim reutilizado o
*           vetor estático caracteres. Dessa forma podemos comparar
*           o elemento apenas comparando o seu ponteiro. Esse comportamento
*           é necessário para testar a função LIS_ProcurarValor.
*           Não utilize esses caracteres junto com os demais
*           (não especiais) e nem em uma lista aonde foi chamado o
*           comando =funcexcluir.
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista   = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      LIS_tpCondRet CondRet ;
      LIS_tpCondRet Ret ;

      char StringDado[ DIM_VALOR ] ;
      char dado = '\0' ;
      char * pDado = NULL ;
      char teste = '\0' ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

      if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
      {

         for( i = 0 ; i < DIM_VT_LISTA ; i++ )
         {
            vtListas[ i ] = NULL ;
         } /* for */

         return TST_CondRetOK ;

      } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

      else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , VAZIO )))
         {
            return TST_CondRetParm ;
         } /* if */

         Ret = LIS_CriarLista( &vtListas[ inxLista ] , NULL ) ;

         if ( Ret != LIS_CondRetOK )
         {
            return TST_CompararInt( ValEsp , Ret , "Retorno diferente do esperado." ) ;
         } /* if */

         return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

      } /* fim ativa: Testar CriarLista */

      /* Testar Definir Função Excluir */
      else if ( strcmp( ComandoTeste, DEF_FUNC_EXCLUIR_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
         {
            return TST_CondRetParm ;
         } /* if */

         return TST_CompararInt( ValEsp , LIS_DefinirFuncaoExcluir( vtListas[ inxLista ] , LiberarValor ) ,
               "Retorno diferente do esperado." ) ;

      } /* fim ativa: Testar Definir Função Excluir */

      /* Testar Esvaziar lista */

      else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
         {
            return TST_CondRetParm ;
         } /* if */

         return TST_CompararInt( ValEsp , LIS_EsvaziarLista( vtListas[ inxLista ] ) ,
               "Retorno diferente do esperado." ) ;

      } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

      else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
         {
            return TST_CondRetParm ;
         } /* if */

         Ret = LIS_DestruirLista( vtListas[ inxLista ] ) ;
         vtListas[ inxLista ] = NULL ;

         return TST_CompararInt( ValEsp , Ret , "Retorno diferente do esperado." ) ;

      } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

      else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ici" ,
               &inxLista , &dado , &CondRetEsp ) ;

         if ( ( numLidos != 3 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

         if ( ( dado < '0' ) || ( dado > '9' ) )
         {
            pDado = ( char * ) malloc( sizeof( char )) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria;
            }
         } else
         {
            /* Caracteres especiais */
            pDado = &( caracteres[ dado - '0' ] ) ;
         } /* if */

         *pDado = dado;
         CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , pDado
                                             #ifdef _DEBUG
                                             , LIS_tpChar
                                             #endif
                                           ) ;

         return TST_CompararInt( CondRetEsp , CondRet ,
               "Condicao de retorno errada ao inserir antes." ) ;

      } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

      else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ici" ,
               &inxLista , &dado , &CondRetEsp ) ;

         if ( ( numLidos != 3 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

         if ( ( dado < '0' ) || ( dado > '9' ) )
         {
            pDado = ( char * ) malloc( sizeof( char )) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria;
            }
         } else
         {
            /* Caracteres especiais */
            pDado = &( caracteres[ dado - '0' ] ) ;
         } /* if */

         *pDado = dado;
         CondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , pDado
                                             #ifdef _DEBUG
                                             , LIS_tpChar
                                             #endif
                                           ) ;

         return TST_CompararInt( CondRetEsp , CondRet ,
               "Condicao de retorno errada ao inserir apos." ) ;

      } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir simbolo */

      else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" ,
               &inxLista , &CondRetEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

         return TST_CompararInt( CondRetEsp ,
               LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
               "Condição de retorno errada ao excluir."   ) ;

      } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

      else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ici" ,
               &inxLista , &teste, &ValEsp ) ;

         if ( ( numLidos != 3 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

         Ret = LIS_ObterValor( vtListas[ inxLista ], ( void ** ) &pDado ) ;

         if ( Ret != LIS_CondRetOK )
         {
            return TST_CompararInt( ValEsp , Ret , "Retorno diferente do esperado." ) ;
         } /* if */

         if ( pDado == NULL )
         {
            TST_NotificarFalha( "Valor do elemento errado." ) ;
            return TST_CondRetErro ;
         }

         return TST_CompararChar( teste  , *pDado ,
               "Valor do elemento errado." ) ;

      } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

      else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

         Ret = LIS_IrInicioLista( vtListas[ inxLista ] ) ;

         return TST_CompararInt( ValEsp , Ret , "Retorno diferente do esperado." ) ;

      } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

      else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ii" , &inxLista , &ValEsp ) ;

         if ( ( numLidos != 2 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

         Ret = LIS_IrFinalLista( vtListas[ inxLista ] ) ;

         return TST_CompararInt( ValEsp , Ret , "Retorno diferente do esperado." ) ;

      } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avançar elemento */

      else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
               &CondRetEsp ) ;

         if ( ( numLidos != 3 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
         {
            return TST_CondRetParm ;
         } /* if */

         return TST_CompararInt( CondRetEsp ,
               LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
               "Condicao de retorno errada ao avancar" ) ;

      } /* fim ativa: LIS  &Avançar elemento */

      /* LIS  &Procurar elemento */

      else if ( strcmp( ComandoTeste , PROCURAR_CMD ) == 0 )
      {

         numLidos = LER_LerParametros( "ici" , &inxLista , &dado ,
               &CondRetEsp ) ;

         if ( ( numLidos != 3 )
           || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) 
           || ( dado < '0' )
           || ( dado > '9' ) )
         {
            return TST_CondRetParm ;
         } /* if */

         return TST_CompararInt( CondRetEsp ,
               LIS_ProcurarValor( vtListas[ inxLista ] , &( caracteres[ dado - '0' ] ) ) ,
               "Condicao de retorno errada ao procurar" ) ;

      } /* fim ativa: LIS  &Procurar elemento */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


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

