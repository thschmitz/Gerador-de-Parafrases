#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ABP.h"

int comparacoes = 0;

pNodoA* inserir_ABP(pNodoA *raiz, char *chave, char *sinonimo) {
    if (raiz == NULL) {
        pNodoA *novo = malloc(sizeof(pNodoA));
        novo->chave = strdup(chave);
        novo->sinonimo = strdup(sinonimo);
        novo->esq = novo->dir = NULL;
        return novo;
    }

    int cmp = strcmp(chave, raiz->chave);
    if (cmp < 0) {
        raiz->esq = inserir_ABP(raiz->esq, chave, sinonimo);
    } else if (cmp > 0) {
        raiz->dir = inserir_ABP(raiz->dir, chave, sinonimo);
    }
    return raiz;
}

pNodoA* consulta_ABP(pNodoA *raiz, char *chave) {
    while (raiz != NULL) {
        comparacoes++;
        if (!strcmp(raiz->chave, chave)) {
            return raiz;
        } else if (strcmp(raiz->chave, chave) > 0) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }
    return NULL;
}

void liberar_ABP(pNodoA *raiz) {
    if (raiz == NULL) return;
    liberar_ABP(raiz->esq);
    liberar_ABP(raiz->dir);
    free(raiz->chave);
    free(raiz->sinonimo);
    free(raiz);
}

int altura_ABP(pNodoA *raiz) {
    if (raiz == NULL) return 0;
    int altura_esq = altura_ABP(raiz->esq);
    int altura_dir = altura_ABP(raiz->dir);
    return 1 + (altura_esq > altura_dir ? altura_esq : altura_dir);
}

int contar_nodos_ABP(pNodoA *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar_nodos_ABP(raiz->esq) + contar_nodos_ABP(raiz->dir);
}

void salvar_estatisticas_ABP(const char *arquivo_estatisticas, const char *arquivo_entrada, const char *arquivo_dicionario, pNodoA *raiz) {
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
    fprintf(fp, "Comparações: %d\n", comparacoes);
    fclose(fp);
}

void carregar_dicionario(const char *arquivo, pNodoA **raiz) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo do dicionário");
        exit(EXIT_FAILURE);
    }

    char chave[100], sinonimo[100];
    while (fscanf(fp, "%s %s", chave, sinonimo) != EOF) {
        *raiz = inserir_ABP(*raiz, chave, sinonimo);
    }
    fclose(fp);
}

void parafrasear(FILE *entrada, FILE *saida, pNodoA *dicionario) {
    char palavra[100];
    int c;

    while ((c = fgetc(entrada)) != EOF) {
        if (isspace(c)) {
            // Preserva o espaço ou quebra de linha no arquivo de saída
            fputc(c, saida);
        } else if (ispunct(c)) {
            // Ignora pontuações como vírgulas e pontos
            continue;
        } else {
            // Volta o caractere lido, pois faz parte de uma palavra
            ungetc(c, entrada);

            // Lê a palavra completa
            fscanf(entrada, "%99s", palavra);

            // Remove pontuações no final da palavra, se existirem
            int len = strlen(palavra);
            while (len > 0 && ispunct(palavra[len - 1])) {
                palavra[--len] = '\0';
            }

            // Converte a palavra para letras minúsculas
            for (int i = 0; palavra[i]; i++) {
                palavra[i] = tolower((unsigned char)palavra[i]);
            }

            // Consulta o sinônimo na árvore
            pNodoA *sinonimo = consulta_ABP(dicionario, palavra);

            // Escreve o sinônimo ou a palavra original no arquivo de saída
            if (sinonimo) {
                fprintf(saida, "%s", sinonimo->sinonimo);
            } else {
                fprintf(saida, "%s", palavra);
            }
        }
    }
}