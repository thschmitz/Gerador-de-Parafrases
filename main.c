#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service/ABP/ABP.h"

#define ESTATISTICAS_ABP "output/ABP/estatisticas_abp.txt"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <dicionario.txt> <entrada.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Arquivo de dicionário (argv[1])
    FILE *arquivo_dicionario = fopen(argv[1], "r");
    if (!arquivo_dicionario) {
        perror("Erro ao abrir o arquivo do dicionário");
        return EXIT_FAILURE;
    }

    // Arquivo de entrada (argv[2])
    FILE *arquivo_entrada = fopen(argv[2], "r");
    if (!arquivo_entrada) {
        perror("Erro ao abrir o arquivo de entrada");
        fclose(arquivo_dicionario);
        return EXIT_FAILURE;
    }

    // Caminho para o arquivo de saída
    char arquivo_saida_path[256];
    snprintf(arquivo_saida_path, sizeof(arquivo_saida_path), "output/%s", "textoParafraseado.txt");

    FILE *arquivo_saida = fopen(arquivo_saida_path, "w");
    if (!arquivo_saida) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(arquivo_dicionario);
        fclose(arquivo_entrada);
        return EXIT_FAILURE;
    }

    // Carregar o dicionário na árvore
    pNodoA *dicionario = NULL;
    carregar_dicionario(argv[1], &dicionario);

    // Parafrasear o texto de entrada
    parafrasear(arquivo_entrada, arquivo_saida, dicionario);

    // Salvar estatísticas
    salvar_estatisticas_ABP(ESTATISTICAS_ABP, argv[2], argv[1], dicionario);

    // Liberação de memória e fechamento de arquivos
    liberar_ABP(dicionario);
    fclose(arquivo_dicionario);
    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    printf("Estatísticas salvas em %s\n", ESTATISTICAS_ABP);
    printf("Texto parafraseado salvo em %s\n", arquivo_saida_path);

    return EXIT_SUCCESS;
}