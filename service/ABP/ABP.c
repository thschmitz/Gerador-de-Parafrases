#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABP.h"

// Insere um novo elemento na árvore ABP
NodoA* inserir_ABP(NodoA *raiz, char *chave) {
    if (raiz == NULL) {
        NodoA *novo = malloc(sizeof(NodoA));
        novo->info = strdup(chave);
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (strcmp(chave, raiz->info) < 0) {
        raiz->esq = inserir_ABP(raiz->esq, chave);
    } else if (strcmp(chave, raiz->info) > 0) {
        raiz->dir = inserir_ABP(raiz->dir, chave);
    }

    return raiz;
}

// Consulta um elemento na árvore ABP e conta comparações
NodoA* consulta_ABP(NodoA *raiz, char *chave, int *comparacoes) {
    while (raiz != NULL) {
        (*comparacoes)++;
        if (strcmp(raiz->info, chave) == 0) {
            return raiz;
        } else if (strcmp(chave, raiz->info) < 0) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }
    return NULL;
}

// Libera a memória da árvore ABP
void liberar_ABP(NodoA *raiz) {
    if (raiz == NULL) return;
    liberar_ABP(raiz->esq);
    liberar_ABP(raiz->dir);
    free(raiz->info);
    free(raiz);
}

// Calcula a altura da árvore ABP
int altura_ABP(NodoA *raiz) {
    if (raiz == NULL) return 0;
    int altura_esq = altura_ABP(raiz->esq);
    int altura_dir = altura_ABP(raiz->dir);
    return 1 + (altura_esq > altura_dir ? altura_esq : altura_dir);
}

// Conta o número de nodos na árvore ABP
int contar_nodos_ABP(NodoA *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar_nodos_ABP(raiz->esq) + contar_nodos_ABP(raiz->dir);
}


// Função para salvar estatísticas da ABP em um arquivo
void salvar_estatisticas_ABP(const char *arquivo_estatisticas, const char *arquivo_entrada, const char *arquivo_dicionario, NodoA *raiz, int comparacoes) {
    FILE *fp = fopen(arquivo_estatisticas, "w");
    if (!fp) {
        perror("Erro ao abrir o arquivo de estatísticas");
        return;
    }

    fprintf(fp, "========  ESTATÍSTICAS ABP ============\n");
    fprintf(fp, "Arq Entrada: %s\n", arquivo_entrada);
    fprintf(fp, "Arq Dicionário: %s\n", arquivo_dicionario);
    fprintf(fp, "Numero de Nodos: %d\n", contar_nodos_ABP(raiz));
    fprintf(fp, "Altura: %d\n", altura_ABP(raiz));
    fprintf(fp, "Rotações: 0\n"); // ABP não utiliza rotações.
    fprintf(fp, "Comparações: %d\n", comparacoes);
    fclose(fp);
}

void carregar_dicionario(const char *arquivo, NodoA **raiz) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo do dicionário");
        exit(EXIT_FAILURE);
    }

    char palavra[100];
    while (fscanf(fp, "%s", palavra) != EOF) {
        *raiz = inserir_ABP(*raiz, palavra);
    }
    fclose(fp);
}

void parafrasear(FILE *entrada, FILE *saida, NodoA *dicionario, int *comparacoes) {
    char palavra[100];

    while (fscanf(entrada, "%s", palavra) != EOF) {
        NodoA *sinonimo = consulta_ABP(dicionario, palavra, comparacoes);
        if (sinonimo) {
            fprintf(saida, "%s ", sinonimo->info);
        } else {
            fprintf(saida, "%s ", palavra);
        }
    }
}