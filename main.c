#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service/ABP/ABP.h"
#include "service/AVL/AVL.h"

#define ESTATISTICAS_ABP "output/ABP/estatisticas_abp.txt"
#define ESTATISTICAS_AVL "output/AVL/estatisticas_avl.txt"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <dicionario.txt> <entrada.txt>\n", argv[0]);
        fprintf(stderr, "Uso: %s <dicionario.txt> <entrada.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int comparacoes_abp = 0, comparacoes_avl = 0;

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
        fclose(arquivo_dicionario);
        return EXIT_FAILURE;
    }


    char arquivo_saida_abp_path[256], arquivo_saida_avl_path[256];
    snprintf(arquivo_saida_abp_path, sizeof(arquivo_saida_abp_path), "output/ABP/%s", "textoParafraseado_ABP");
    snprintf(arquivo_saida_avl_path, sizeof(arquivo_saida_avl_path), "output/AVL/%s", "textoParafraseado_AVL");

    // Abre os arquivos de saída para ABP e AVL
    FILE *arquivo_saida_abp = fopen(arquivo_saida_abp_path, "w");
    FILE *arquivo_saida_avl = fopen(arquivo_saida_avl_path, "w");
    if (!arquivo_saida_abp || !arquivo_saida_avl) { 
        perror("Erro ao abrir os arquivos de saída");
        fclose(arquivo_entrada);
        fclose(arquivo_dicionario);
        if (arquivo_saida_abp) fclose(arquivo_saida_abp);
        if (arquivo_saida_avl) fclose(arquivo_saida_avl);
        return EXIT_FAILURE;
    }

    // ABP - Carregamento do dicionário e processamento
    pNodoA *dicionario_abp = NULL;
    carregar_dicionario(argv[1], &dicionario_abp);
    parafrasear(arquivo_entrada, arquivo_saida_abp, dicionario_abp);
    salvar_estatisticas_ABP(ESTATISTICAS_ABP, argv[2], argv[1], dicionario_abp);

    // Resetando o ponteiro do arquivo de entrada para reutilização
    rewind(arquivo_entrada);

    // AVL - Carregamento do dicionário e processamento
    NodoAVL *dicionario_avl = NULL;
    carregar_dicionario_AVL(argv[1], &dicionario_avl);
    parafrasear_AVL(arquivo_entrada, arquivo_saida_avl, dicionario_avl, &comparacoes_avl);
    salvar_estatisticas_AVL(ESTATISTICAS_AVL, argv[2], argv[1], dicionario_avl, comparacoes_avl);

    // Liberação das árvores
    liberar_ABP(dicionario_abp);
    liberar_AVL(dicionario_avl);

    // Fechamento dos arquivos
    fclose(arquivo_entrada);
    fclose(arquivo_dicionario);
    fclose(arquivo_saida_abp);
    fclose(arquivo_saida_avl);

    printf("Estatísticas salvas em:\n");
    printf(" - ABP: %s\n", ESTATISTICAS_ABP);
    printf("Texto parafraseado ABP salvo em %s\n", arquivo_saida_abp_path);
    printf(" - AVL: %s\n", ESTATISTICAS_AVL);
    printf("Texto parafraseado AVL salvo em %s\n", arquivo_saida_avl_path);

    return EXIT_SUCCESS;
}
