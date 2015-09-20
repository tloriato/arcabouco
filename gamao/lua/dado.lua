m=require("modulo")

-- Códigos de retorno possíveis para o arcabouço
--ret= {{"Nome", 'Descrição'}}
ret = {{"OK", "Rodou sem erros"}}

-- param = {"Nome", "Tipo", "Descrição", Oculto do teste (default false)}
params = {{"pDado1", "int*", "Resultado do dado 1.\nEste parâmetro é passado por referência.", true},
          {"pDado2", "int*", "Resultado do dado 2.\nEste parâmetro é passado por referência.", true}}
--func {'Nome da função', 'Descrição',                                  Retornos,  Parâmetros, Nome Teste}
func = {{"Jogar Dados",    "Gera dois números aleatórios entre 1 e 6.", {"OK"},    params,     "jogar"}}

autores = {"Gabriel Barbosa de Oliveira", "Guilherme de Azevedo Pereira Marques", "Thiago Duarte Naves"}

--criar_modulo(nome,   id,    testes, mult_instâncias, cond_ret, funcoes, autores, arq_code,   arq_head,   arq_test,     arq_script)
m.criar_modulo("dado", "DAD", true,   false,           ret,      func,    autores, "dado.c",   "dado.h",   "testdado.c", "TesteDado.script")
