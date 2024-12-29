## Para buildar o arquivo, segue o comando:

- gcc main.c -Iservice/ABP service/ABP/ABP.c -o  gerador -lm
- gcc main.c -Iservice/ABP service/ABP/ABP.c -o {nomeArquivoExecutável} -lm

## Para rodar o executável via CMD, segue o comando:

- ./{nomeArquivoExecutável} source/dict_10k.txt source/Alienista_cap1.txt -> exemplo
- ./{nomeArquivoExecutável} {DicionarioUsadoParaParafrasear} {TextoDeEntradaASerParafraseado}
