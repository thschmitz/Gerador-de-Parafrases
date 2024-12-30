## Para buildar o arquivo, segue o comando:

gcc main.c -I../Gerador-de-Parafrases/service/ABP -I../Gerador-de-Parafrases/service/AVL ../Gerador-de-Parafrases/service/ABP/ABP.c ../Gerador-de-Parafrases/service/AVL/AVL.c -o gerador -lm

## Para rodar o executável via CMD, segue o comando:

- ./{nomeArquivoExecutável} source/Alienista_cap1.txt Teste.txt -> exemplo
- ./{nomeArquivoExecutável} {TextoOriginalASerTraduzido} {TextoFinalParafraseado}
