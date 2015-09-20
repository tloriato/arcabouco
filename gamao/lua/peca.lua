m=require("modulo")

-- Códigos de retorno possíveis para o arcabouço
--ret= {{"Nome", 'Descrição'}}
ret = {{"OK", "Rodou sem erros"}}


-- param = {"Nome", "Tipo", "Descrição", Oculto do teste (default false)}
pCriar = {{"pPeca", "PEC_tppPeca *", "Parâmetro para retorno da peça criada\nEsse parâmetro é passado por referência", true},
          {"cor", "int", "Cor da peça"}}

pDestruir = {{"pPeca", "PEC_tppPeca", "Peça a ser destruída", true}}

pObterCor = {{"pPeca", "PEC_tppPeca", "Peça", true},
             {"pCor", "int *", "Parâmetro para retorno da cor da peça\nEsse parâmetro é passado por referência"}}

--func   {'Nome da função',   'Descrição',                      Retornos,      Parâmetros, Nome Teste}
fCriar = {"Criar",             "Cria uma peça da cor indicada", {"OK"},        pCriar,     "criar"}

fDestruir = {"Destruir", "Libera a memória ocupada pela peça", {"OK"}, pDestruir, "destruir"}

fObterCor = {"Obter cor", "Obtém a cor da peça", {"OK"}, pObterCor, "obtercor"}

funcs = {fCriar, fDestruir, fObterCor}

autores = {"Gabriel Barbosa de Oliveira", "Guilherme de Azevedo Pereira Marques", "Thiago Duarte Naves"}

--criar_modulo(nome,   id,    testes, mult_instâncias, cond_ret, funcoes,  autores, arq_code, arq_head, arq_test,     arq_script)
m.criar_modulo("Peça", "PEC", true,   false,           ret,      funcs,    autores, "peca.c", "peca.h", "testpeca.c", "TestePeca.script")
