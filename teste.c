#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

#define N 8

// Funções protótipo
void inicializaTabuleiro(int tabuleiro[N][N]);
void imprimeTabuleiro(int tabuleiro[N][N]);
int ehSeguro(int tabuleiro[N][N], int linha, int coluna);
int tenta(int tabuleiro[N][N], int coluna);
int resolveProblema();

int main() {
    if (resolveProblema()) {
        printf("Solucao encontrada:\n");
    } else {
        printf("Nao ha solucao.\n");
    }

    return 0;
}

void inicializaTabuleiro(int tabuleiro[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void imprimeTabuleiro(int tabuleiro[N][N]) {
    usleep(300000);
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", tabuleiro[i][j] ? '1' : '0');
        }
        printf("\n");
    }
    printf("\n");
}

int ehSeguro(int tabuleiro[N][N], int linha, int coluna) {
    // Verifica a linha
    for (int i = 0; i < coluna; i++) {
        if (tabuleiro[linha][i]) {
            return 0;
        }
    }

    // Verifica diagonal superior esquerda
    for (int i = linha, j = coluna; i >= 0 && j >= 0; i--, j--) {
        if (tabuleiro[i][j]) {
            return 0;
        }
    }

    // Verifica diagonal inferior esquerda
    for (int i = linha, j = coluna; i < N && j >= 0; i++, j--) {
        if (tabuleiro[i][j]) {
            return 0;
        }
    }

    return 1;
}

int tenta(int tabuleiro[N][N], int coluna) {
    if (coluna == N) {
        // Todas as rainhas estão colocadas com segurança
        imprimeTabuleiro(tabuleiro);
        return 1;
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
        if (ehSeguro(tabuleiro, i, coluna)) {
            tabuleiro[i][coluna] = 1;

            // Recursivamente tenta colocar as rainhas nas colunas subsequentes
            res = tenta(tabuleiro, coluna + 1) || res;

            // Se a tentativa não levou a uma solução, desfaz a escolha (backtracking)
            tabuleiro[i][coluna] = 0;
        }
    }

    return res;
}

int resolveProblema() {
    int tabuleiro[N][N];
    inicializaTabuleiro(tabuleiro);
    return tenta(tabuleiro, 0);
}