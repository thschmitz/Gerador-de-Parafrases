#ifndef ABP_H
#define ABP_H

typedef struct pNodoA {
    char *chave;
    char *sinonimo;
    struct pNodoA *esq;
    struct pNodoA *dir;
} pNodoA;


// Funções públicas
pNodoA* inserir_ABP(pNodoA *raiz, char *chave, char *sinonimo);
pNodoA* consulta_ABP(pNodoA *raiz, char *chave);
void liberar_ABP(pNodoA *raiz);
int altura_ABP(pNodoA *raiz);
int contar_nodos_ABP(pNodoA *raiz);
void salvar_estatisticas_ABP(const char *arquivo_estatisticas, const char *arquivo_entrada, const char *arquivo_dicionario, pNodoA *raiz);
void carregar_dicionario(const char *arquivo, pNodoA **raiz);
void parafrasear(FILE *entrada, FILE *saida, pNodoA *dicionario);

#endif // ABP_H
