## Para buildar o arquivo, segue o comando:

gcc main.c -Iservice/ABP -Iservice/AVL service/ABP/ABP.c service/AVL/AVL.c -o gerador -lm

## Para rodar o executável via CMD, segue o comando:

- ./{nomeArquivoExecutável} source/Alienista_cap1.txt Teste.txt -> exemplo
- ./{nomeArquivoExecutável} {TextoOriginalASerTraduzido} {TextoFinalParafraseado}
