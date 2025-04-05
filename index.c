#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 8

void inicializarTabuleiro(char tabuleiro[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tabuleiro[i][j] = '-';
        }
    }
}

void imprimirTabuleiro(char tabuleiro[SIZE][SIZE]) {
    printf("\n  A B C D E F G H\n");
    for (int i = SIZE - 1; i >= 0; i--) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            // Usando cores no terminal
            if (tabuleiro[i][j] == '*') {
                printf("\033[1;32m%c \033[0m", tabuleiro[i][j]);  // Verde para movimentos
            } else if (tabuleiro[i][j] != '-') {
                printf("\033[1;33m%c \033[0m", tabuleiro[i][j]);  // Amarelo para a peça
            } else {
                printf("- ");  // Para casas vazias
            }
        }
        printf("\n");
    }
}

int estaDentro(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

int validarPosicao(char colunaLetra, int linha) {
    int col = toupper(colunaLetra) - 'A';
    return (col >= 0 && col < SIZE && linha >= 1 && linha <= SIZE) ? col : -1;
}

void movimentoTorre(char tabuleiro[SIZE][SIZE], int row, int col) {
    for (int i = 0; i < SIZE; i++) {
        if (i != row) tabuleiro[i][col] = '*';  // vertical
        if (i != col) tabuleiro[row][i] = '*';  // horizontal
    }
}

void movimentoBispo(char tabuleiro[SIZE][SIZE], int row, int col) {
    int i = 1;
    while (estaDentro(row + i, col + i)) { tabuleiro[row + i][col + i] = '*'; i++; }
    i = 1;
    while (estaDentro(row + i, col - i)) { tabuleiro[row + i][col - i] = '*'; i++; }
    i = 1;
    while (estaDentro(row - i, col + i)) { tabuleiro[row - i][col + i] = '*'; i++; }
    i = 1;
    while (estaDentro(row - i, col - i)) { tabuleiro[row - i][col - i] = '*'; i++; }
}

void movimentoRainha(char tabuleiro[SIZE][SIZE], int row, int col) {
    int i;

    // Diagonais
    i = 1;
    do {
        if (!estaDentro(row + i, col + i)) break;
        tabuleiro[row + i][col + i] = '*';
        i++;
    } while (1);

    i = 1;
    do {
        if (!estaDentro(row + i, col - i)) break;
        tabuleiro[row + i][col - i] = '*';
        i++;
    } while (1);

    i = 1;
    do {
        if (!estaDentro(row - i, col + i)) break;
        tabuleiro[row - i][col + i] = '*';
        i++;
    } while (1);

    i = 1;
    do {
        if (!estaDentro(row - i, col - i)) break;
        tabuleiro[row - i][col - i] = '*';
        i++;
    } while (1);

    // Verticais e horizontais
    i = 0;
    do {
        if (i != row) tabuleiro[i][col] = '*';
        i++;
    } while (i < SIZE);

    i = 0;
    do {
        if (i != col) tabuleiro[row][i] = '*';
        i++;
    } while (i < SIZE);
}

void salvarTabuleiroEmArquivo(char tabuleiro[SIZE][SIZE]) {
    FILE *file = fopen("tabuleiro.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    fprintf(file, "  A B C D E F G H\n");
    for (int i = SIZE - 1; i >= 0; i--) {
        fprintf(file, "%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            fprintf(file, "%c ", tabuleiro[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("\nTabuleiro salvo em 'tabuleiro.txt'.\n");
}

int main() {
    char tabuleiro[SIZE][SIZE];
    int row, col;
    char colunaLetra, peca;
    char repetir;

    do {
        inicializarTabuleiro(tabuleiro);

        printf("Escolha uma peça (T = Torre, B = Bispo, R = Rainha): ");
        scanf(" %c", &peca);
        peca = toupper(peca);

        printf("Digite a posição inicial (ex: D4): ");
        scanf(" %c%d", &colunaLetra, &row);
        col = validarPosicao(colunaLetra, row);
        row -= 1;  // Ajuste para 0-based

        if (col == -1 || !estaDentro(row, col)) {
            printf("Posição inválida!\n");
            continue;
        }

        tabuleiro[row][col] = peca;

        switch (peca) {
            case 'T':
                movimentoTorre(tabuleiro, row, col);
                break;
            case 'B':
                movimentoBispo(tabuleiro, row, col);
                break;
            case 'R':
                movimentoRainha(tabuleiro, row, col);
                break;
            default:
                printf("Peça inválida!\n");
                continue;
        }

        imprimirTabuleiro(tabuleiro);
        salvarTabuleiroEmArquivo(tabuleiro);

        printf("\nDeseja jogar novamente? (S/N): ");
        scanf(" %c", &repetir);
        repetir = toupper(repetir);

    } while (repetir == 'S');

    return 0;
}
