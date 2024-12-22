#ifndef ABP_H
#define ABP_H

typedef struct NodoA {
    char *info;
    struct NodoA *esq, *dir;
} NodoA;

// Funções da árvore ABP
NodoA* inserir_ABP(NodoA *raiz, char *chave);
NodoA* consulta_ABP(NodoA *raiz, char *chave, int *comparacoes);
void liberar_ABP(NodoA *raiz);
void salvar_estatisticas_ABP(const char *arquivo_estatisticas, const char *arquivo_entrada, const char *arquivo_dicionario, NodoA *raiz, int comparacoes);
void carregar_dicionario(const char *arquivo, NodoA **raiz);
void parafrasear(FILE *entrada, FILE *saida, NodoA *dicionario, int *comparacoes);

// Funções auxiliares
int altura_ABP(NodoA *raiz);
int contar_nodos_ABP(NodoA *raiz);

#endif // ABP_H
