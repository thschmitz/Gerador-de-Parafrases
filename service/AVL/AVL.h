#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore AVL
typedef struct NodoAVL {
    char palavra[50];
    char sinonimo[50];
    struct NodoAVL *esq, *dir;
    int altura;
} NodoAVL;

// Funções principais
void carregar_dicionario_AVL(const char *caminho_dicionario, NodoAVL **raiz);
void parafrasear_AVL(FILE *entrada, FILE *saida, NodoAVL *raiz, int *comparacoes);
void salvar_estatisticas_AVL(const char *caminho_estatisticas, const char *texto_entrada,
                             const char *dicionario_usado, NodoAVL *raiz, int comparacoes);
void liberar_AVL(NodoAVL *raiz);

// Funções auxiliares internas
NodoAVL* inserir_AVL(NodoAVL *raiz, char *palavra, char *sinonimo);
NodoAVL* consulta_AVL(NodoAVL *raiz, char *chave, int *comparacoes);

// Funções para cálculo de estatísticas
int contar_nodos_AVL(NodoAVL *raiz);
int altura_AVL(NodoAVL *raiz);
void incrementar_rotacoes();
int contar_rotacoes_AVL();

#endif // AVL_H
