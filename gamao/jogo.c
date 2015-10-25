/**********************************************************************
*
*  $MCD Módulo de definição: Módulo jogo
*
*  Arquivo gerado:              jogo.c
*  Letras identificadoras:      JOG
*
*  Projeto: Disciplina INF 1301
*  Autores: gbdo - Gabriel Barbosa de Oliveira
*           gdapm - Guilherme de Azevedo Pereira Marques
*           pa - Pedro Alvarez
*           tdn - Thiago Duarte Naves
*
*  $HA Histórico de evolução:
*     Versão  Autor                  Data       Observações
*       1.00  gbdo, gdapm, pa, tdn   22/10/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo é responsável por interagir com o usuário e garantir
*     que as regras do gamão sejam seguidas.
*
***********************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   <assert.h>
#include   "tabuleiro.h"
#include   "dado_pontos.h"
#include   "dado.h"
#include   "peca.h"

/***********************************************************************
*
*  $TC Tipo de dados: JOG Opção de menu
*
*
***********************************************************************/

   typedef struct {

         char * texto ;
            /* Texto correspondente a esta opção que será impresso */

         void ( * funcao )( void ) ;
            /* Função que será chamada se o usuário escolher essa
             * opção */

         char tecla ;
            /* Tecla que será usada pelo usuário para selecionar
             * essa opção */

   } tpOpcaoMenu ;


/***** Protótipos das funções encapuladas no módulo *****/

   static void ImprimirTabuleiro( void ) ;

   static void NovaPartida( void ) ;

   static void SalvarPartida( void ) ;

   static void CarregarPartida( void ) ;

   static void JogarDados( void ) ;

   static void MoverPeca( void ) ;

   static int Menu( tpOpcaoMenu * pOpcoes ) ;


/*****  Variáveis globais ao módulo  *****/

   static TAB_tppTabuleiro tabuleiro = NULL ; /* Tabuleiro do jogo */
   static DPO_tpJogador vez = DPO_Jogador1 ; /* Indica de qual jogador é
                                              * a vez de jogar */


/*****  Código das funções encapsuladas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: JOG Imprimir tabuleiro
*
*  $ED Descrição da função
*     Imprime o estado atual do tabuleiro em ASCII na tela.
*
***********************************************************************/

   static void ImprimirTabuleiro( void )
   {

   } /* Fim função: JOG Imprimir tabuleiro */


/***********************************************************************
*
*  $FC Função: JOG Nova partida
*
*  $ED Descrição da função
*     Inicia uma nova partida de jogo.
*
***********************************************************************/

   static void NovaPartida( void )
   {

   } /* Fim função: JOG Nova partida */


/***********************************************************************
*
*  $FC Função: JOG Salvar partida
*
*  $ED Descrição da função
*     Salva a partida atual em um arquivo.
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro.
*     - essa função só pode ser chamada entre as jogadas de um jogador
*       e outro, nunca durante uma jogada.
*
*  Assertivas de saída:
*     - estado atual do jogo salvo no arquivo.
*
***********************************************************************/

   static void SalvarPartida( void )
   {

      int i ;
      int pontos ;
      int podeDobrar ; /* Jogador 1 pode dobrar se 64 > pontos > 1 */
      FILE * f = fopen( "partida.txt" , "w" ) ;

      if ( f == NULL )
      {
         printf( "Não foi possível criar o arquivo!\n" ) ;
         return ;
      } /* if */

      /* Grava tabuleiro */
      for ( i = 0 ; i < TAB_QUANTIDADE_POS ; i ++ )
      {
         unsigned int quantidade ;
         int cor ;
         TAB_ContarPecas( tabuleiro, i , &quantidade , &cor ) ;
         fprintf( f , "%d %X\n" , cor , quantidade ) ;
      } /* for */

      /* TODO Grava a quantidade de peças finalizadas de cada jogador */
      fprintf( f , "0 0\n" ) ; /* dummy */

      /* TODO Grava a quantidade de peças na barra de cada jogador */
      fprintf( f , "0 0\n" ) ; /* dummy */

      /* Grava valor da partida (dado pontos) */
      DPO_ObterPontos( &pontos ) ;
      DPO_PodeDobrar( DPO_Jogador1 , &podeDobrar ) ;
      fprintf( f, "%d %d\n" , pontos , podeDobrar ) ;

      /* Grava de qual jogador é a vez */
      fprintf( f , "%d\n" , vez == DPO_Jogador1 ) ;

      fclose( f ) ;

   } /* Fim função: JOG Salvar partida */


/***********************************************************************
*
*  $FC Função: JOG Carregar partida
*
*  $ED Descrição da função
*     Carrega a partida salva de um arquivo.
*
***********************************************************************/

   static void CarregarPartida( void )
   {

      int i ;
      int pontos , idVez ;
      int podeDobrar ; /* Jogador 1 pode dobrar se 64 > pontos > 1 */
      unsigned int qtd[ TAB_QUANTIDADE_POS ] ;
      int cor[ TAB_QUANTIDADE_POS ] ;
      unsigned int bar1 , bar2, fin1 , fin2 ;
      FILE * f = fopen( "partida.txt" , "r" ) ;

      if ( f == NULL )
      {
         printf( "Não foi possível abrir o arquivo!\n" ) ;
         return ;
      } /* if */

      /* Lê a quantidade de peças e a cor de cada posição do tabuleiro */
      for ( i = 0 ; i < TAB_QUANTIDADE_POS ; i ++ )
      {
         if ( fscanf( f , "%u %x\n" , &cor[ i ] , &qtd[ i ] ) != 2 )
         {
            printf( "Erro ao ler o arquivo\n" ) ;
            fclose( f ) ;
            return ;
         } /* if */
      } /* for */

      if ( fscanf( f , "%u %u\n" , &fin1 , &fin2 ) != 2 )
      {
         printf( "Erro ao ler o arquivo\n" ) ;
         fclose( f ) ;
         return ;
      } /* if */

      if ( fscanf( f , "%u %u\n" , &bar1 , &bar2 ) != 2 )
      {
         printf( "Erro ao ler o arquivo\n" ) ;
         fclose( f ) ;
         return ;
      } /* if */

      if ( fscanf( f , "%d %d\n" , &pontos , &podeDobrar ) != 2 )
      {
         printf( "Erro ao ler o arquivo\n" ) ;
         fclose( f ) ;
         return ;
      } /* if */

      if ( fscanf( f , "%d\n" , &idVez ) != 1 )
      {
         printf( "Erro ao ler o arquivo\n" ) ;
         fclose( f ) ;
         return ;
      } /* if */

   } /* Fim função: JOG Carregar partida */


/***********************************************************************
*
*  $FC Função: JOG Jogar dados
*
*  $ED Descrição da função
*     Joga os dados para determinar o número de movimentos do jogador
*
***********************************************************************/

   static void JogarDados( void )
   {

   } /* Fim função: JOG Jogar dados */


/***********************************************************************
*
*  $FC Função: JOG Mover peça
*
*  $ED Descrição da função
*     Move uma peça do jogador atual.
*
***********************************************************************/

   static void MoverPeca( void )
   {

   } /* Fim função: JOG Mover peça */


/***********************************************************************
*
*  $FC Função: JOG Menu
*
*  $ED Descrição da função
*     Imprime o menu, aguarda a escolha da opção e chama a função
*     correspondente
*
*  $EP Parâmetros
*     pOpcoes - Vetor de opções do menu.
*
*  Assertivas de entrada:
*     - Vetor pOpcoes deve existir.
*     - A última posição do vetor deve conter NULL no campo texto.
*
*  Assertivas de saída:
*     - Menu impresso e função correspondente à opção escolhida pelo
*       usuário chamada (se existir).
*     - Índice da opção escolhida retornado..
*
*  $FV Valor retornado
*     Índice da opção escolhida.
*
***********************************************************************/

   static int Menu( tpOpcaoMenu * pOpcoes )
   {

      assert( pOpcoes != NULL ) ;

      tpOpcaoMenu * pOp = pOpcoes ;
      while ( pOp->texto != NULL )
      {
         printf( "%c - %s\n" , pOp->tecla , pOp->texto ) ;
         pOp ++ ;
      } /* while */

      /* Garante que o usuário escolha uma opção válida */
      while ( 1 )
      {
         char t = 0 ;
         int indice = 0 ;

         printf( "Escolha uma opção: " ) ;
         scanf( "%c" , &t ) ;

         pOp = pOpcoes ;
         while ( pOp->texto != NULL )
         {
            if ( pOp->tecla == t )
            {
               if ( pOp->funcao )
               {
                  pOp->funcao( ) ;
               } /* if */

               return indice ;
            } /* if */

            indice ++ ;
            pOp ++ ;
         } /* while */

         printf( "Opção inválida: %c\n" , t ) ;
      } /* while */

   } /* Fim função: JOG Menu */


/***********************************************************************
*
*  $FC Função: Main
*
*  $ED Descrição da função
*     Ponto de entrada do programa.
*
***********************************************************************/

   int main( void )
   {

      return 0 ;

   } /* Fim função: Main */


/********** Fim do módulo de implementação: Módulo jogo **********/

