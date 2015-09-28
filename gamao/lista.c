/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão        Autor              Data           Observações
*     2.00          gbo, gapm, tdn     20/09/2015     Lista de ponteiros de void.
*     1.00          gbo, gapm, tdn     28/08/2015     Início do desenvolvimento.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void *  pValor ;
               /* valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         void (* pExcluir)( void * pValor) ;
               /* Ponteiro para a função usada para
                * desalocar um elemento */

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   lista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista lista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista lista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * pLista,
                                 void (* pExcluir)( void * pValor))
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      *pLista = ( LIS_tppLista ) malloc( sizeof( LIS_tpLista )) ;
      if ( *pLista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      LimparCabeca( *pLista ) ;
      (*pLista)->pExcluir = pExcluir ;

      return LIS_CondRetOK;

   } /* Fim função: LIS &Criar lista */


/***************************************************************************
*
*  Função: LIS &Definir Função Excluir
*  ****/

   LIS_tpCondRet LIS_DefinirFuncaoExcluir( LIS_tppLista lista,
                                 void (* pExcluir)( void * pValor))
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      lista->pExcluir = pExcluir ;

      return LIS_CondRetOK;

   } /* Fim função: LIS &Definir Função Excluir */


/***************************************************************************
*
*  Função: LIS &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista lista )
   {

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      LIS_EsvaziarLista( lista ) ;

      free( lista ) ;

     return LIS_CondRetOK;
   } /* Fim função: LIS &Destruir lista */

/***************************************************************************
*
*  Função: LIS &Esvaziar lista
*  ****/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista lista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      pElem = lista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( lista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( lista ) ;

     return LIS_CondRetOK;

   } /* Fim função: LIS &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista lista ,
                                           void * pValor )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( lista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( lista->pElemCorr == NULL )
         {
            lista->pOrigemLista = pElem ;
            lista->pFimLista = pElem ;
         } else
         {
            if ( lista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = lista->pElemCorr->pAnt ;
               lista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               lista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = lista->pElemCorr ;
            lista->pElemCorr->pAnt = pElem ;
         } /* if */

         lista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista lista ,
                                          void * pValor )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( lista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( lista->pElemCorr == NULL )
         {
            lista->pOrigemLista = pElem ;
            lista->pFimLista = pElem ;
         } else
         {
            if ( lista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = lista->pElemCorr->pProx ;
               lista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               lista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = lista->pElemCorr ;
            lista->pElemCorr->pProx = pElem ;

         } /* if */

         lista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista lista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista  != NULL ) ;
      #endif

      if ( lista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = lista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            lista->pElemCorr    = pElem->pAnt ;
         } else {
            lista->pElemCorr    = pElem->pProx ;
            lista->pOrigemLista = lista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            lista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( lista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS &Excluir elemento */

/***************************************************************************
*
*  Função: LIS &Obter referência para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor(LIS_tppLista lista, void ** pValor)
   {

      #ifdef _DEBUG
         assert( lista != NULL ) ;
         assert( pValor != NULL ) ;
      #endif

      if ( lista->pElemCorr == NULL )
      {
         return LIS_CondRetNaoAchou;
      } /* if */

      *pValor = lista->pElemCorr->pValor;

      return LIS_CondRetOK;

   } /* Fim função: LIS &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS &Ir para o elemento inicial
*  ****/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista lista )
   {

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      lista->pElemCorr = lista->pOrigemLista ;

      return LIS_CondRetOK;

   } /* Fim função: LIS &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS &Ir para o elemento final
*  ****/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista lista )
   {

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      lista->pElemCorr = lista->pFimLista ;

      return LIS_CondRetOK;

   } /* Fim função: LIS &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista  lista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( lista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = lista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               lista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            lista->pElemCorr = lista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = lista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               lista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            lista->pElemCorr = lista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS &Avançar elemento */

/***************************************************************************
*
*  Função: LIS &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista lista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( lista  != NULL ) ;
      #endif

      if ( lista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = lista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            lista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS &Procurar elemento contendo valor */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

 static void LiberarElemento( LIS_tppLista   lista ,
                              tpElemLista  * pElem   )
   {

      if ( lista->pExcluir )
      {
         lista->pExcluir( pElem->pValor ) ;
      }

      free( pElem ) ;

      lista->numElem-- ;

   } /* Fim função: LIS Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS Criar o elemento
*
***********************************************************************/

   static tpElemLista * CriarElemento( LIS_tppLista lista ,
                                       void * pValor )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      lista->numElem ++ ;

      return pElem;

   } /* Fim função: LIS Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS Limpar a cabeça da lista
*
***********************************************************************/

   static void LimparCabeca( LIS_tppLista lista )
   {

      lista->pOrigemLista = NULL ;
      lista->pFimLista = NULL ;
      lista->pElemCorr = NULL ;
      lista->numElem   = 0 ;
      lista->pExcluir = NULL ;

   } /* Fim função: LIS Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

