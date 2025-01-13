Aplicação de geração de paráfrases através de um dicionário de sinônimos, feita em C. Feito por Thomas Schmitz e Eduardo Drumm Menezes durante o período 2024/2 da UFRGS para o trabalho final da cadeira de Estrutura de Dados, sob tutela da professora Viviane Moreira.

O programa recebe dois arquivos de texto como entrada: um contendo um dicionário de sinônimos e outro com o texto a ser transformado. Com base nesses dados, são construídas duas árvores binárias de pesquisa: uma convencional e outra do tipo AVL (auto-balanceada). Em seguida, o programa gera um arquivo de saída contendo a paráfrase do texto original e exibe estatísticas detalhadas sobre o desempenho das duas árvores binárias durante o processamento.


## Para buildar o arquivo, segue o comando:

gcc main.c -Iservice/ABP -Iservice/AVL service/ABP/ABP.c service/AVL/AVL.c -o gerador -lm

## Para rodar o executável via CMD, segue o comando:

- ./{nomeArquivoExecutável} source/dict_10k.txt source/Alienista_cap1.txt -> exemplo
- ./{nomeArquivoExecutável} {DicionarioUsadoParaParafrasear} {TextoDeEntradaASerParafraseado}


