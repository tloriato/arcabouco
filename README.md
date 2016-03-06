# Arcabouço de Testes
##### Esse projeto é um port pra linux / mac / windows com cygwin do arcaboço de testes da PUC-Rio utilizado na matéria **Programação modular**.
##### Utilizando o compilador do mingw (i686-w64-mingw32-gcc) é possível compilar os executáveis de windows a partir do linux / mac
###### Esse repositório também contém os fontes para os dois trabalhos feitos pelo meu grupo: Um jogo de gamão e o teste de todas as arestas do módulo lista.
* O Visual studio não é utilizado nesse projeto.
* Nesse texto tudo o que se aplica ao linux também é válido para mac e cygwin (e provavelmente outros unix, mas não testei).
* Todos os fontes e arquivos do arcabouço foram incluídos nesse repositório.
* Poucas modificações foram feitas nos fontes para poder compila-los, apenas foram trocados os nomes dos arquivos para caixa baixa e os *includes* correspondentes.
* Também foram criados alguns arquivos, como o malloc.h, que não existe no linux.
* Vale notar que algumas vezes em que compilei no mac para windows o executável não funcionou.
* Os executáveis de windows serão compilados com a codificação de strings ISO-8859-1 / Latin 1 para que os acentos apareçam corretamente. Os de linux utilizam UTF-8 pelo mesmo motivo.

##### Veja também o [meu outro repositório](https://github.com/naves-thiago/gerador_arcabouco) com scripts em Lua para gerar um *esqueleto* de módulo no formato esperado pela matéria programação modular

#### **TESTE NO WINDOWS OS EXECUTÁVEIS GERADOS ANTES DE ENVIAR**
## Instruções
* Compilando:
  * Os Makefiles desse repositório geram as dependências entre os fontes de cada projeto automaticamente (utilizando o gcc).
  * Em qualquer dos casos abaixo, use **make win** para compilar para windows a partir do linux ou **make clean** para deletar todos os arquivos gerados na compilação.
  * Para compilar os trabalhos, basta entar na pasta e dar make. O executável será gerado na mesma pasta.
  * Para compilar os testes primeiro é preciso compilar o arcabouço: Entre na pasta *arcabouc* e de make. A biblioteca será gerada na pasta *Produto*. Depois basta dar make na pasta do teste. O executável será gerado na mesma pasta.
* Novo módulo / trabalho:
  * Utilize um dos módulos ou trabalhos já existentes como modelo. Altere o **Makefile** para utilizar os novos arquivos fontes e gerar o executável com o nome desejado. Em geral só é preciso alterar as linhas anteriores a linha '########################################' no Makefile.
  * No Makefile, as variáveis terminadas em **_WIN** são utilizadas na compilação para windows a partir do linux em vez das variáveis de mesmo nome sem sufixo.
  * Os fontes devem ser escritos com a codificação **UTF-8** (padrão no linux).
* Convertendo arquivos fonte:
  * Os scripts converte.sh e converte_para_dos.sh permitem converter entre os formatos de texto do windows / DOS (Latin 1 com \r\n) e unix (UTF-8 com \n).
  * O script converte_para_dos.sh requer que o programa **unix2dos** esteja instalado.
  * Ambos os scripts podem converter apenas 1 arquivo (ex: ./converte.sh fontes/arquivo.c) ou uma pasta inteira de arquivos (ex: ./converte.sh fontes). **Não utilize _./converte.sh pasta/*_ ou _./converte.sh pasta/*.c_, apenas _./converte.sh pasta_**
