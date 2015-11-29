#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301
*  Autores: gbo - Gabriel Barbosa de Oliveira
*           gapm - Guilherme de Azevedo Pereira Marques
*           tdn - Thiago Duarte Naves
*           pa - Pedro Alvarez
*
*  $HA Histórico de evolução:
*     Versão   Autor               Data           Observações
*       2.00   gbo, gapm, tdn      20/09/2015     Lista de ponteiros de void.
*       1.00   gbo, gapm, tdn, pa  30/08/2015     Início do desenvolvimento.
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK = 0,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia = 1 ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista =2,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou = 3,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria = 4 ,
               /* Faltou memória ao tentar criar um elemento de lista */

       LIS_CondRetErroEstrutura = 5
               /* Estrutura da lista está errada */

   } LIS_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

      LIS_DeturpaPtrProx = 0,
         /* Faz ponteiro para o próximo 
         elemento da lista apontar para lixo*/
      LIS_DeturpaPtrAnt = 1,
         /* Faz ponteiro para o próximo 
         elemento da lista apontar para lixo*/
      LIS_DeturpaPtrOrigem = 2,
         /* Faz ponteiro para a origem 
         da lista apontar para nulo */
      LIS_DeturpaCorrNulo = 3
         /* Anula ponteiro corrente */

   } LIS_tpDeturpa ;

#endif


/***********************************************************************
*
*  $TC Tipo de dados: LIS Tipo de dado
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

      LIS_tpInteiro = 0 ,
         /* Tipo de dados inteiro */

      LIS_tpChar = 1 ,
         /* Tipo de dados caracter */

      LIS_tpFloat = 2 ,
         /* Tipo de dados ponto flutuante */

      LIS_tpDouble = 3
         /* Tipo de dados ponto flutuante de precisão dupla */

   } LIS_tpTipo ;

#endif


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada
*     e a retorna através do ponteiro passado como 
*     parâmetro.
*
*
*  $EP Parâmetros
*     pLista    -   ponteiro para o retorno da lista
*     pExcluir  -   ponteiro para uma função chamada ao desalocar um
*                   elemento
*
*  Assertivas de entrada:
*     - pLista deve ser um ponteiro válido.
*     - pExcluir deve ser um ponteiro de função válido ou NULL.
*
*  Assertivas de saída:
*     - *pLista deve conter uma instância válida de lista com a função
*       de desalocação igual a pExcluir.
*
*  $FV Valor retornado
*    LIS_CondRetOK - Criou sem problemas
*    LIS_CondRetFaltouMemoria  -  Ocorreu um erro por falta de memória
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * pLista,
                                 void (* pExcluir)( void * pValor)) ;


/***********************************************************************
*
*  $FC Função: LIS  &Definir Função Excluir
*
*  $ED Descrição da função
*     Define a função que será chamada ao excluir um elemento da lista.
*     Essa função substitui a função definida pelo parâmetro pExcluir
*     da função LIS_CriarLista( ).
*
*  $EP Parâmetros
*     lista     -   Lista cuja função deve ser redefinida
*     pExcluir  -   ponteiro para uma função chamada ao desalocar um
*                   elemento
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*     - pExcluir deve ser um ponteiro de função válido ou NULL.
*
*  Assertivas de saída:
*     - A função de desalocação de dados da lista passada passa a ser
*       a função apontada por pExcluir ou NULL.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - definiu sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_DefinirFuncaoExcluir( LIS_tppLista lista,
                                 void (* pExcluir)( void * pValor)) ;


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     lista  -  Lista a ser destruída
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*
*  Assertivas de saída:
*     - A memória ocupada pela lista passada deve ser liberada.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     lista - ponteiro para a lista a ser esvaziada
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*
*  Assertivas de saída:
*     - Todos os elementos contidos na lista devem ser removidos e a
*       memória ocupada por eles liberada.
*
*  $FV Valor retornado
*     LIS_CondRetOK  -  Esvaziou sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     lista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - valor do novo elemento
*     tipo - tipo de dado armazenado no elemento
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*
*  Assertivas de saída:
*     - Um novo elemento deve ser alocado e este deve conter o dado
*       pValor. Este elemento será inserido na posição anterior ao
*       elemente corrente na lista passada.
*
*  $FV Valor retornado
*     LIS_CondRetOK  -  inseriu sem problemas
*     LIS_CondRetFaltouMemoria  -  ocorreu um erro por falta de memória
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista lista , void * pValor
                                           #ifdef _DEBUG
                                           , LIS_tpTipo tipo
                                           #endif
                                         ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     lista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - valor do novo elemento
*     tipo - tipo de dado armazenado no elemento
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*
*  Assertivas de saída:
*     - Um novo elemento deve ser alocado e este deve conter o dado
*       pValor. Este elemento será inserido na posição seguinte ao
*       elemente corrente na lista passada.
*
*  $FV Valor retornado
*     LIS_CondRetOK  -  inseriu sem problemas
*     LIS_CondRetFaltouMemoria  -  ocorreu um erro por falta de memória
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista lista , void * pValor
                                           #ifdef _DEBUG
                                           , LIS_tpTipo tipo
                                           #endif
                                         ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento a esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará
*     corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     lista    - lista na qual deve excluir.
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*     - A lista deve conter ao menos 1 elemento.
*
*  Assertivas de saída:
*     - O elemento corrente da lista deve ser excluído e a memória
*       utilizada pelo elemento deve ser liberada.
*
*  $FV Valor retornado
*     LIS_CondRetOK  -  excluído sem problemas
*     LIS_CondRetListaVazia  -  a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da
*     lista
*
*  $EP Parâmetros
*     lista - lista de onde se quer o valor
*     ppValor - ponteiro para retorno do elemento
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*     - A lista deve conter ao menos 1 elemento.
*     - ppValor deve ser um ponteiro válido.
*
*  Assertivas de saída:
*     - *ppValor irá conter o valor armazenado no elemento corrente da
*       lista.
*
*  $FV Valor retornado
*     LIS_CondRetOk -  se o elemento corrente existe
*     LIS_CondRetNaoAchou -  se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista lista, void ** ppValor ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     lista - ponteiro para a lista a manipular
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*
*  Assertivas de saída:
*     - O elemento corrente da lista passa a ser o primeiro elemento
*       da lista ou NULL, caso a lista esteja vazia.
*
*  $FV Valor retornado
*     LIS_CondRetOk - função executou sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     lista - ponteiro para a lista a manipular
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*
*  Assertivas de saída:
*     - O elemento corrente da lista passa a ser o último elemento
*       da lista ou NULL, caso a lista esteja vazia.
*
*  $FV Valor retornado
*     LIS_CondRetOk - função executou sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista lista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     lista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*     - lista deve conter ao menos 'numElem' elementos na direção
*       desejada contados a partir do elemento corrente.
*
*  Assertivas de saída:
*     - O elemento corrente da lista passa a ser o elemento distante
*       'numElem' posições do elemento corrente atual na direção
*       indicada pelo sinal de 'numElem'.
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista lista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     lista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  Assertivas de entrada:
*     - lista deve ser uma instância válida de lista.
*     - lista deve conter ao menos um elemento com o dado igual a
*       pValor.
*
*  Assertivas de saída:
*     - O elemento corrente da lista passa a ser o elemento cujo
*       valor é igual a 'pValor'.
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                               O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista lista ,
                                    void * pValor        ) ;
									
/***********************************************************************
*
*  $FC Função: LIS  &Verificar uma lista
*
*  $ED Descrição da função
*     Verifica completamente uma determinada lista duplamente encadeada.
*     Também marca todos os espaços por ela ocupados.
*  $EP Parâmetros
*     lista  - ponteiro para a lista
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarLista( LIS_tppLista lista ) ;

#endif

/***********************************************************************
*
*  $FC Função: LIS  &Verificar um nó cabeça
*
*  $ED Descrição da função
*     Verifica a integridade de um nó cabeça da lista.
*
*  $EP Parâmetros
*     lista  - ponteiro para a lista
*
*  $FV Valor retornado
*     Condição de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_VerificarCabeca( LIS_tppLista lista ) ;

#endif


/***********************************************************************
*
*  $FC Função: LIS  &Deturpar lista
*
*  $ED Descrição da função
*     Corrompe elementos específicos da estrutura da lista.
*     Essa função destina-se a preparar os cenários de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da lista.
*
*  $EP Parâmetros
*     $P lista  - lista a ser deturpada
*     $P ModoDeturpar - identifica como deve ser feita a deturpação
*                       LIS_tpDeturpa identifica os modos de
*                       deturpação conhecidos
*
***********************************************************************/

#ifdef _DEBUG

   void LIS_Deturpar( LIS_tppLista lista ,
                      LIS_tpDeturpa modoDeturpar ) ;

#endif


/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
