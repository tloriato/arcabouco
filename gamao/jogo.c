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
#include   <string.h>
#include   <assert.h>
#include   "tabuleiro.h"
#include   "dado_pontos.h"
#include   "dado.h"
#include   "peca.h"
#include   "cores.h"

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

   static int InserirPecas( unsigned int qtd , unsigned int pos , int cor ) ;

   static void Sair( void ) ;

   static void MenuNovaPartida( void ) ;


/*****  Variáveis globais ao módulo  *****/

   static TAB_tppTabuleiro tabuleiro = NULL ; /* Tabuleiro do jogo */
   static DPO_tpJogador vez = DPO_Jogador1 ;  /* Indica de qual jogador é
                                               * a vez de jogar */
   static int Dado1 , Dado2 ;                 /* Resultado da última jogada
                                                 de dados */

/*****  Constantes globais ao módulo  *****/

   /* Caracteres que representam as peças de cada jogador */
   static const char CharPeca[ 2 ]  = { 'O' , '@' } ;

   /* Fundo de uma posição do tabuleiro */
   static const char StrFundo[] = "------------------" ;

   /* Arrumação das peças no início de uma partida */
   static const struct
   {
      unsigned int pos;
      unsigned int qtd;
      int cor;
   } ArrumacaoInicial[] = { { 0  , 2 , 0 } , { 5  , 5 , 1 } , { 7  , 3 , 1 } ,
                            { 11 , 5 , 0 } , { 12 , 5 , 1 } , { 16 , 3 , 0 } ,
                            { 18 , 5 , 0 } , { 23 , 2 , 1 } } ;


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

      #define LARGURA 18  /* 15 peças + 3 traços '-' */
      int pos , cor , fundo ;
      unsigned int qtd ;
      char linha[ LARGURA + 1 ] ;
      char * cor_fundo[ 2 ] = { COR_BG1 , COR_BG2 } ;

      fundo = 0 ;
      for ( pos = 0 ; pos < TAB_QUANTIDADE_POS / 2 ; pos ++ )
      {
         /* Insere uma linha em branco dividindo o tabuleiro ao meio */
         if ( pos == TAB_QUANTIDADE_POS / 4 )
         {
            printf( "\n" ) ;
         } /* if */

         if ( TAB_ContarPecas( tabuleiro , pos , &qtd , &cor ) != TAB_CondRetOK )
         {
            printf( "\nPosição inválida ao imprimir o tabuleiro\n" ) ;
            return ;
         } /* if */

         /* Exemplo: A  @@@@@@------------> */
         memset( linha , CharPeca[ cor ] , qtd ) ;
         linha[ qtd ] = '\0' ;

         printf( COR_LETRA_POS "%c  " COR_PADRAO , 'A' + pos ) ;
         printf( cor_fundo[ fundo ] ) ;
         printf( "%s%s>" COR_PADRAO "     " , linha , &StrFundo[ qtd ] ) ;

         if ( TAB_ContarPecas( tabuleiro , TAB_QUANTIDADE_POS - pos - 1 , &qtd , &cor ) != TAB_CondRetOK )
         {
            printf( "\nPosição inválida ao imprimir o tabuleiro\n" ) ;
            return ;
         } /* if */

         /* Exemplo: <--------------OOOO  X */
         memset( linha , CharPeca[ cor ] , qtd ) ;
         linha[ qtd ] = '\0' ;

         fundo = ! fundo ;
         printf( cor_fundo[ fundo ] ) ;
         printf( "<%s%s" COR_PADRAO , &StrFundo[ qtd ] , linha ) ;
         printf( "  " COR_LETRA_POS "%c" COR_PADRAO "\n" , 'X' - pos ) ;
      } /* for */

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

      int i , qtd ;

      /* Arrumação inicial do tabuleiro */
      if ( tabuleiro != NULL )
      {
         TAB_Destruir( tabuleiro ) ;
      } /* if */

      if ( TAB_Criar( &tabuleiro ) != TAB_CondRetOK )
      {
         printf( "Erro ao criar o tabuleiro\n" ) ;
         Sair( ) ;
      } /* if */

      qtd = sizeof( ArrumacaoInicial ) / sizeof( ArrumacaoInicial[0] ) ;

      for ( i = 0 ; i < qtd ; i ++ )
      {
         if ( ! InserirPecas( ArrumacaoInicial[ i ].qtd ,
                              ArrumacaoInicial[ i ].pos ,
                              ArrumacaoInicial[ i ].cor ) )
         {
            printf( "Erro ao inserir as peças no tabuleiro\n" ) ;
            TAB_Destruir( tabuleiro ) ;
            Sair( ) ;
         } /* if */
      } /* for */

      ImprimirTabuleiro( ) ;

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

      int i , p ;
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

      /* Todos os dados foram lidos sem erro, altera os parâmetros do
       * jogo */

      /* Cria um novo tabuleiro */
      if ( tabuleiro != NULL )
      {
         TAB_Destruir( tabuleiro ) ;
      } /* if */

      if ( TAB_Criar( &tabuleiro ) != TAB_CondRetOK )
      {
         printf( "Erro ao criar o tabuleiro\n" ) ;
         Sair( ) ;
      } /* if */

      /* Adiciona as peças */
      for ( i = 0 ; i < TAB_QUANTIDADE_POS ; i ++ )
      {
         if ( ! InserirPecas( qtd[ i ] , i , cor[ i ] ) )
         {
            printf( "Erro ao criar a peça\n" ) ;
            Sair( ) ;
         } /* if */
      } /* for */

      /* TODO Preencher peças finalizadas e na barra */

      DPO_DefinirPontosVez( pontos , podeDobrar ) ;

      if ( ( idVez != (int) DPO_Jogador1 )
        && ( idVez != (int) DPO_Jogador2 ) )
      {
         printf( "Jogador inválido no arquivo.\n" ) ;
         Sair( ) ;
      } /* if */

      vez = idVez ;

      ImprimirTabuleiro( ) ;

   } /* Fim função: JOG Carregar partida */


/***********************************************************************
*
*  $FC Função: JOG Jogar dados
*
*  $ED Descrição da função
*     Joga os dados para determinar o número de movimentos do jogador e
*     inicia a próxima jogada.
*
***********************************************************************/

   static void JogarDados( void )
   {

      DAD_JogarDados( &Dado1 , &Dado2 ) ;
      // TODO tratar BAR
      MoverPeca( ) ;

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

      /* No máximo haverá peças em 23 posições do tabuleiro */
      tpOpcaoMenu opcoes[ 24 ] ;
      char txtOps[4][23] ;


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
*     - Índice da opção escolhida retornado.
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
*  $FC Função: JOG Inserir Peças
*
*  $ED Descrição da função
*     Cria qtd peças na posição pos do tabuleiro
*
*  $EP Parâmetros
*     qtd - Quantidade de peças a adicionar
*     pos - Posição na qual adicionar as peças
*     cor - Cor das peças a adicionar
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro
*     - pos dever ser uma posição válida de tabuleiro
*
*  Assertivas de saída:
*     - qtd peças inseridas na posição pos do tabuleiro e retorno 1 ou
*       retorno 0 em caso de falha.
*
*  $FV Valor retornado
*     1 se as peças foram inseridas corretamente, 0 caso contrário.
*
***********************************************************************/

   static int InserirPecas( unsigned int qtd , unsigned int pos , int cor )
   {

      unsigned int i ;
      PEC_tppPeca peca ;

      for ( i = 0 ; i < qtd ; i ++ )
      {
         if ( PEC_Criar( &peca , cor ) != PEC_CondRetOK )
         {
            return 0 ;
         } /* if */

         if ( TAB_IncluirPeca( tabuleiro , pos , peca ) != TAB_CondRetOK )
         {
            PEC_Destruir( peca ) ;
            return 0 ;
         } /* if */
      } /* for */

      return 1 ;

   } /* Fim função: JOG Inserir Peças */


/***********************************************************************
*
*  $FC Função: JOG Menu Nova Partida
*
*  $ED Descrição da função
*     Mostra o menu no início de uma nova partida
*
*  Assertivas de saída:
*     - Dados jogados ou partida salva carregada ou jogo finalizado,
*       de acordo com a opção escolhida pelo usuário.
*
***********************************************************************/

   static void MenuNovaPartida( void )
   {
      static const tpOpcaoMenu opcoes[] = {
                  { "Jogar dados"      , JogarDados      , 'j' } ,
                  { "Carregar partida" , CarregarPartida , 'c' } ,
                  { "Sair"             , Sair            , 's' } ,
                  { NULL               , NULL            , 0   } } ;

      Menu( opcoes ) ;

   } /* Fim função: JOG Menu Nova Partida */


/***********************************************************************
*
*  $FC Função: JOG Sair
*
*  $ED Descrição da função
*     Libera a memória alocada pelos módulos do programa e termina
*     imediatamente a execução.
*
*  Assertivas de entrada:
*     - tabuleiro deve ser uma instância válida de tabuleiro
*     - Bar1 e Bar2 devem ser instâncias válidas de PeçasCapturadas
*     - Final1 e Final2 devem ser instâncias válidas de PeçasFinalizadas
*
*  Assertivas de saída:
*     Memória alocada dinâmicamente pela aplicação liberada e execução
*     finalizada.
*
***********************************************************************/

   static void Sair( void )
   {

      TAB_Destruir( tabuleiro ) ;
      // BAR_Destruir( Bar1 ) ;
      // BAR_Destruir( Bar2 ) ;
      // FIN_Destruir( Final1 ) ;
      // FIN_Destruir( Final2 ) ;
      exit( 0 ) ;

   } /* Fim Função: JOG Sair */


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

//      if ( TAB_Criar( &tabuleiro ) != TAB_CondRetOK )
//      {
//         printf( "Erro ao criar o tabuleiro\n" ) ;
//         return 1 ;
//      } /* if */

      NovaPartida( ) ;
//      SalvarPartida( ) ;
//      CarregarPartida( ) ;

      return 0 ;

   } /* Fim função: Main */


/********** Fim do módulo de implementação: Módulo jogo **********/

