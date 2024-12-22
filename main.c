#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service/ABP/ABP.h"

#define DICIONARIO_FIXO "source/dict_10K.txt"
#define ESTATISTICAS_ABP "output/ABP/estatisticas_abp.txt"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <entrada.txt> <saida.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int comparacoes = 0;
    FILE *arquivo_entrada = fopen(argv[1], "r");
    char arquivo_saida_path[256];
    snprintf(arquivo_saida_path, sizeof(arquivo_saida_path), "output/%s", argv[2]); // Monta o meu caminho para dentro do output

    if (!arquivo_entrada) {
        perror("Erro ao abrir o arquivo de entrada");
        return EXIT_FAILURE;
    }

    // Abre o arquivo de saída para a árvore ABP
    FILE *arquivo_saida = fopen(arquivo_saida_path, "w");
    if (!arquivo_saida) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(arquivo_entrada);
        return EXIT_FAILURE;
    }

    NodoA *dicionario = NULL;
    carregar_dicionario(DICIONARIO_FIXO, &dicionario);

    parafrasear(arquivo_entrada, arquivo_saida, dicionario, &comparacoes);

    salvar_estatisticas_ABP(ESTATISTICAS_ABP, argv[1], DICIONARIO_FIXO, dicionario, comparacoes);

    // Libera a memória alocada para a árvore
    liberar_ABP(dicionario);
    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    printf("Estatísticas salvas em %s\n", ESTATISTICAS_ABP);
    return EXIT_SUCCESS;
}