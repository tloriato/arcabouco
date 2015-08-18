/***************************************************************************
*  $MCI MÃ³dulo de implementaÃ§Ã£o: PRNC MÃ³dulo principal
*
*  Arquivo gerado:              PRINCIPc
*
*  Nome da base de software:    ArcabouÃ§o para a automaÃ§Ã£o de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\ARCABOUC.BSW
*
*  Projeto: INF 1301 / 1628 AutomatizaÃ§Ã£o dos testes de mÃ³dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA HistÃ³rico de evoluÃ§Ã£o:
*     VersÃ£o  Autor    Data     ObservaÃ§Ãµes
*     4       avs   01/fev/2006 criar linguagem script simbÃ³lica
*     3       avs   08/dez/2004 uniformizaÃ§Ã£o dos exemplos
*     2       avs   07/jul/2003 unificaÃ§Ã£o de todos os mÃ³dulos em um sÃ³ projeto
*     1       avs   16/abr/2003 inÃ­cio desenvolvimento
*
*  $ED DescriÃ§Ã£o do mÃ³dulo
*     Este mÃ³dulo contÃ©m o programa principal do arcabouÃ§o ("framework")
*     de apoio ao teste automatizado de mÃ³dulos escritos em C.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>

#include   "Generico.h"

#define  DIM_PARM_BUFFER   250
#define  DIM_NOME_ARQUIVO  250

      static char NomeArqScript[ DIM_NOME_ARQUIVO ] = "" ;
            /* Nome do arquivo script linha de comando */

      static char NomeArqLog[ DIM_NOME_ARQUIVO ] = "" ;
            /* Nome do arquivo log linha de comando */

      static char NomeArqAcum[ DIM_NOME_ARQUIVO ] = "" ;
            /* Nome do arquivo de acumulaÃ§Ã£o */

/*****  CÃ³digo das funÃ§Ãµes exportadas pelo mÃ³dulo  *****/


/***********************************************************************
*
*  $FC FunÃ§Ã£o: PRNC &Programa principal
*
*  $ED DescriÃ§Ã£o da funÃ§Ã£o
*
*     O programa principal pode receber os perÃ¢metros de linha de comando:
*
*     /s<arqscript> - obrigatÃ³rio, Ã© o nome do arquivo contendo o
*                     script de teste. A sintaxe do script depende
*                     do mÃ³dulo especÃ­fico sendo testado.
*                     Veja especificaÃ§Ã£o do mÃ³dulo GENERICO para saber
*                     a extensÃ£o default de arquivos script.
*     /l<arqlog>    - opcional, Ã© o nome do arquivo log no qual devem
*                     ser escritas todas as mensagens geradas durante
*                     o teste. Se este nome de arquivo nÃ£o for
*                     fornecido a saÃ­da serÃ¡ dirigida para a tela
*                     (arquivo stdout).
*                     Veja especificaÃ§Ã£o do mÃ³dulo GENERICO para saber
*                     a extensÃ£o default de arquivos log.
*     /a<arqacum>   - opcional, se fornecido as estatÃ­sticas da execuÃ§Ã£o
*                     do programa serÃ£o adicionadas ao conteÃºdo do arquivo
*                     arqacum. Caso este nÃ£o exista, serÃ¡ criado.
*                     A extensÃ£o default do arquivo Ã© .estat
*                     Use este parÃ¢metro em batches de teste envolvendo um
*                     conjunto de massas de teste. O total acumulado
*                     pode ser exibido com o programa exbestat.exe
*     /h ou /?      - opcional, se fornecido imprime, Ã  guisa de auxÃ­lio,
*                     um resumo de como usar o programa e, apÃ³s, pÃ¡ra.
*                     Este auxÃ­lio tambÃ©m Ã© exibido no caso de erro de
*                     parÃ¢metro de linha de comando.
*
*     O programa retorna:
*
*     - 0 caso o teste tenha concluÃ­do corretamente
*     - 2 caso tenha sido solicitado auxÃ­lio.
*     - 4 caso:
*           - os parÃ¢metros de linha de comando estejam em erro
*           - um ou mais casos de teste identificaram alguma falha.
*
*  $EP ParÃ¢metros
*     $P NumParms     - nÃºmero de parÃ¢metros de linha de comando
*                       recebidos
*     $P vtValorParms - vetor de strings, cada item do vetor
*                       corresponde ao string de um parÃ¢metro.
*                       O string de Ã­ndice zero Ã© o nome do programa.
*
***********************************************************************/

   int main( int NumParm , char ** vtValorParm )
   {

      int  ScriptDefinido ,
           LogDefinido    ,
           Erro           ;

      char ParmBuffer[ DIM_PARM_BUFFER ] ;

      int inxParm ;

      /* Exibir logo do programa */

         printf( "\n\nLES - Laboratório de Engenharia de Software DI/PUC-Rio" ) ;
         printf( "\n      Arcabouço de teste de módulos C  (c) 2006\n" ) ;
         printf( "\n---------------------------------------------" ) ;
         printf( "\n      Construto sob teste: %s\n" , vtValorParm[ 0 ] ) ;

      /* Inicializar contexto */

         ScriptDefinido = 0 ;
         LogDefinido    = 0 ;
         Erro           = 0 ;

      /* Ler os parâmetros da linha de comando */

         for ( inxParm = 1 ; inxParm < NumParm ; inxParm ++ ) {

         /* Tratar parÃ¢metro sintaticamente correto */

            strcpy( ParmBuffer , vtValorParm[ inxParm ] ) ;

            if ( ( ParmBuffer[ 0 ] == '/' )
              || ( ParmBuffer[ 0 ] == '-' ))
            {

               switch ( ParmBuffer[ 1 ] ) {

               /* Tratar parÃ¢metro nome de arquivo script de teste */

                  case 's' :
                  case 'S' :
                  {

                     if ( ! ScriptDefinido )
                     {
                        ScriptDefinido = 1 ;
                        strcpy( NomeArqScript , ParmBuffer + 2 ) ;
                     } else
                     {
                        printf( "\n>>>   Arquivo de script jÃ¡ foi definido." ) ;
                        Erro = 4 ;
                     } /* if */

                     break ;

                  } /* fim ativa: Tratar parÃ¢metro nome de arquivo script de teste */

               /* Tratar parÃ¢metro nomde de arquivo log de mensagens */

                  case 'l' :
                  case 'L' :
                  {

                     if ( ! LogDefinido )
                     {
                        LogDefinido = 1 ;
                        strcpy( NomeArqLog , ParmBuffer + 2 ) ;

                     } else {
                        printf( "\n>>>   Arquivo log jÃ¡ foi definido." ) ;
                        Erro = 4 ;
                     } /* if */

                     break ;

                  } /* fim ativa: Tratar parÃ¢metro nomde de arquivo log de mensagens */

               /* Tratar parÃ¢metro arquivo de acumulaÃ§Ã£o */

                  case 'a':
                  case 'A':
                  {

                     if ( NomeArqAcum[ 0 ] == 0 )
                     {
                        strcpy( NomeArqAcum , ParmBuffer + 2 ) ;
                     } else {
                        printf( "\n>>>   Arquivo de acumulaÃ§Ã£o jÃ¡ foi definido." ) ;
                        Erro = 4 ;
                     } /* if */

                     break ;

                  } /* fim ativa: Tratar parÃ¢metro arquivo de acumulaÃ§Ã£o */

               /* Tratar solicitaÃ§Ã£o de auxÃ­lio */

                  case '?' :
                  case 'h' :
                  case 'H' :
                  {

                     Erro = 1 ;

                     break ;

                  } /* fim ativa: Tratar solicitaÃ§Ã£o de auxÃ­lio */

               /* Tratar parÃ¢metro ilegal */

                  default :
                  {

                     printf( "\n>>>   ParÃ¢metro desconhecido: %s" , ParmBuffer ) ;
                     Erro = 4 ;

                     break ;

                  } /* fim ativa: Tratar parÃ¢metro ilegal */

               } /* fim seleciona: Tratar parÃ¢metro sintaticamente correto */

            } /* fim ativa: Tratar parÃ¢metro sintaticamente correto */

         /* Tratar parÃ¢metro sintaticamente errado. */

            else
            {

               printf( "\n>>>   Sintaxe de parÃ¢metro errada: %s" , ParmBuffer ) ;
               Erro = 4 ;

            } /* fim ativa: Tratar parÃ¢metro sintaticamente errado. */

         } /* fim repete: Ler os parÃ¢metros da linha de comando */

      /* Controlar parÃ¢metros */

         /* Validar parÃ¢metros */

            if ( ( Erro != 1       )
              && ( !ScriptDefinido ))
            {
               printf( "\n>>>   Faltou arquivo de diretivas de teste" ) ;
               Erro = 4 ;
            } /* if */

         /* Terminar em caso de erro */

            if ( Erro != 0 )
            {

               printf( "\n\n!!!  Modo de uso do programa" ) ;
               printf(   "\n  TestXXX   /s<ArqScript> {/l<ArqLog>} {/a<ArqAcum> {/? | /h }" ) ;
               printf( "\n\n  <ArqScript>   - nome do arquivo contendo o script de teste. " ) ;
               printf(   "\n                  ParÃ¢metro obrigatÃ³rio, exceto se solicitado auxÃ­lio." ) ;
               printf(   "\n  <ArqLog>      - nome do arquivo contendo o script de teste. " ) ;
               printf(   "\n                  ParÃ¢metro opcional. Se nÃ£o fornecido exibe" ) ;
               printf(   "\n                  o resultado do teste na tela (stdout)" ) ;
               printf(   "\n  <ArqAcum>     - nome do arquivo acumulador." ) ;
               printf(   "\n                  ParÃ¢metro opcional. Se fornecido as" ) ;
               printf(   "\n                  estatÃ­sticas do teste serÃ£o acumuladas" ) ;
               printf(   "\n                  no arquivo ArqAcum. Caso nÃ£o exista," ) ;
               printf(   "\n                  serÃ¡ criado." ) ;
               printf(   "\n  /? ou /h      - SolicitaÃ§Ã£o de auxÃ­lio." ) ;

               if ( Erro == 1 )
               {
                  Erro = 2 ;
               } else
               {
                  Erro = 4 ;
               } /* if */
               printf( "\n\n>>>  Teste nÃ£o executado\n" ) ;

               return Erro ;

            } /* fim ativa: Terminar em caso de erro */

      /* Executar os testes */

         if ( TST_ControlarSessaoTeste( vtValorParm[ 0 ] , NomeArqScript ,
                                        NomeArqLog       , NomeArqAcum    ) != 0 )
         {
            return 4 ;
         } /* if */

         return 0 ;

   } /* Fim funÃ§Ã£o: PRNC &Programa principal */

/********** Fim do mÃ³dulo de implementaÃ§Ã£o: PRNC MÃ³dulo principal **********/

