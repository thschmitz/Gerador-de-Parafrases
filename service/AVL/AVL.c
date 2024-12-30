#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Variáveis globais para estatísticas
static int rotacoes = 0; // Contador global de rotações
static int comparacoes = 0; // Contador global de comparações

// Função para criar um novo nó
NodoAVL* criar_nodo(char *palavra, char *sinonimo) {
    NodoAVL* novo = (NodoAVL*)malloc(sizeof(NodoAVL));
    strcpy(novo->palavra, palavra);
    strcpy(novo->sinonimo, sinonimo);
    novo->esq = novo->dir = NULL;
    novo->altura = 1;
    return novo;
}

// Função para calcular a altura de um nó
int altura(NodoAVL* nodo) {
    return nodo ? nodo->altura : 0;
}

// Função para calcular o fator de balanceamento de um nó
int fator_balanceamento(NodoAVL* nodo) {
    return nodo ? altura(nodo->esq) - altura(nodo->dir) : 0;
}

// Rotação à direita
NodoAVL* rotacao_direita(NodoAVL* y) {
    NodoAVL* x = y->esq;
    NodoAVL* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));
    x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));

    rotacoes++;
    return x;
}

// Rotação à esquerda
NodoAVL* rotacao_esquerda(NodoAVL* x) {
    NodoAVL* y = x->dir;
    NodoAVL* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));
    y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));

    rotacoes++;
    return y;
}

// Inserção na árvore AVL com balanceamento
NodoAVL* inserir_AVL(NodoAVL *raiz, char *palavra, char *sinonimo) {
    if (!raiz)
        return criar_nodo(palavra, sinonimo);

    if (strcmp(palavra, raiz->palavra) < 0)
        raiz->esq = inserir_AVL(raiz->esq, palavra, sinonimo);
    else if (strcmp(palavra, raiz->palavra) > 0)
        raiz->dir = inserir_AVL(raiz->dir, palavra, sinonimo);
    else
        return raiz; // Palavra já existe na árvore

    // Atualiza a altura do nó atual
    raiz->altura = 1 + (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir));

    // Calcula o fator de balanceamento e realiza rotações se necessário
    int balance = fator_balanceamento(raiz);

    // Rotação LL
    if (balance > 1 && strcmp(palavra, raiz->esq->palavra) < 0)
        return rotacao_direita(raiz);

    // Rotação RR
    if (balance < -1 && strcmp(palavra, raiz->dir->palavra) > 0)
        return rotacao_esquerda(raiz);

    // Rotação LR
    if (balance > 1 && strcmp(palavra, raiz->esq->palavra) > 0) {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    // Rotação RL
    if (balance < -1 && strcmp(palavra, raiz->dir->palavra) < 0) {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

// Consulta na árvore AVL
NodoAVL* consulta_AVL(NodoAVL *raiz, char *chave, int *comparacoes) {
    while (raiz != NULL) {
        (*comparacoes)++;
        if (!strcmp(raiz->palavra, chave)) {
            (*comparacoes)++;
            return raiz;
        } else if (strcmp(chave, raiz->palavra) < 0)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    return NULL; // Palavra não encontrada
}

// Carrega o dicionário na árvore AVL
void carregar_dicionario_AVL(const char *caminho_dicionario, NodoAVL **raiz) {
    FILE *fp = fopen(caminho_dicionario, "r");
    if (!fp) {
        perror("Erro ao abrir o dicionário");
        exit(EXIT_FAILURE);
    }

    char palavra[50], sinonimo[50];
    while (fscanf(fp, "%s %s", palavra, sinonimo) != EOF)
        *raiz = inserir_AVL(*raiz, palavra, sinonimo);

    fclose(fp);
}

// Processa o texto de entrada e gera o texto parafraseado
void parafrasear_AVL(FILE *entrada, FILE *saida, NodoAVL *raiz, int *comparacoes) {
    char palavra[100]; // Para armazenar palavras temporariamente
    int c;             // Para leitura de caracteres individuais

    while ((c = fgetc(entrada)) != EOF) {
        if (isspace(c)) {
            // Mantém espaços, tabulações e quebras de linha
            fputc(c, saida);
        } else if (ispunct(c)) {
            // Ignora pontuações como pontos e vírgulas
            continue;
        } else {
            // Recoloca o caractere no fluxo de entrada para formar a palavra
            ungetc(c, entrada);

            // Lê a palavra do fluxo de entrada
            fscanf(entrada, "%99s", palavra);

            // Remove qualquer pontuação no final da palavra
            int len = strlen(palavra);
            while (len > 0 && ispunct(palavra[len - 1])) {
                palavra[--len] = '\0';
            }

            // Converte a palavra para minúsculas (case insensitive)
            for (int i = 0; palavra[i]; i++) {
                palavra[i] = tolower((unsigned char)palavra[i]);
            }

            // Consulta a palavra na árvore AVL
            NodoAVL *sinonimo = consulta_AVL(raiz, palavra, comparacoes);

            if (sinonimo) {
                // Se encontrado, escreve o sinônimo no arquivo de saída
                fprintf(saida, "%s", sinonimo->sinonimo);
            } else {
                // Caso contrário, escreve a palavra original
                fprintf(saida, "%s", palavra);
            }
        }
    }
}

// Libera a memória da árvore AVL
void liberar_AVL(NodoAVL *raiz) {
    if (!raiz)
        return;

    liberar_AVL(raiz->esq);
    liberar_AVL(raiz->dir);

    free(raiz);
}

// Conta o número de nós na árvore AVL
int contar_nodos_AVL(NodoAVL *raiz) {
    if (!raiz)
        return 0;

    return 1 + contar_nodos_AVL(raiz->esq) + contar_nodos_AVL(raiz->dir);
}

// Retorna a altura da árvore AVL
int altura_AVL(NodoAVL *raiz) {
    return raiz ? raiz ->altura : 0;
}

// Incrementa o contador de rotações realizadas
void incrementar_rotacoes() { 
   rotacoes++;
}

// Retorna o número total de rotações realizadas na AVL
int contar_rotacoes_AVL() { 
   return rotacoes; 
}

// Salva as estatísticas da árvore AVL em um arquivo
void salvar_estatisticas_AVL(const char *caminho_estatisticas, const char *texto_entrada,
                             const char *dicionario_usado, NodoAVL *raiz, int comparacoes) {
    
	FILE *fp = fopen(caminho_estatisticas, "w");
	if (!fp){
		perror("Erro ao abrir o arquivo de estatísticas");
		return;
	}

	fprintf(fp,"======== ESTATÍSTICAS AVL ========\n");
	fprintf(fp,"Arquivo Entrada: %s\n", texto_entrada);
	fprintf(fp,"Arquivo Dicionário: %s\n", dicionario_usado);
	fprintf(fp,"Número de Nós: %d\n", contar_nodos_AVL(raiz));
	fprintf(fp,"Altura da Árvore: %d\n", altura_AVL(raiz));
	fprintf(fp,"Número de Rotações: %d\n", contar_rotacoes_AVL());
	fprintf(fp,"Número de Comparações: %d\n", comparacoes);

	fclose(fp);
}
