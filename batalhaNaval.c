#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define esquerda -1
#define Direita 1
#define Sobe -1
#define desce 1
#define horizontal 1
#define vertical 0

// Função para colocar navio horizontal ou vertical
int colocarNavioHV(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                   int linha_inicial, int coluna_inicial,
                   int horizontalouvertical) // 1 = horizontal, 0 = vertical
{
    // Verifica limites e sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int l = linha_inicial + (horizontalouvertical ? 0 : i);
        int c = coluna_inicial + (horizontalouvertical ? i : 0);

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
        {
            printf("Navio não cabe!\n");
            return 0;
        }
        if (tabuleiro[l][c] == NAVIO)
        {
            printf("Já existe navio nessa posição!\n");
            return 0;
        }
    }

    // Posiciona navio
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int l = linha_inicial + (horizontalouvertical ? 0 : i);
        int c = coluna_inicial + (horizontalouvertical ? i : 0);
        tabuleiro[l][c] = NAVIO;
    }

    return 1;
}

// Função para posicionar navio diagonal
// esquerdaoudireita e sobeoudesce podem ser +1 ou -1
int colocarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int esquerdaoudireita, int sobeoudesce)
{

    // 1. Verifica limites
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int l = linha_inicial + i * sobeoudesce;
        int c = coluna_inicial + i * esquerdaoudireita;
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
        {
            printf("Navio não cabe na diagonal!\n");
            return 0;
        }
        if (tabuleiro[l][c] == NAVIO)
        {
            printf("Já existe navio nessa posição diagonal!\n");
            return 0;
        }
    }

    // 2. Posiciona navio
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int l = linha_inicial + i * sobeoudesce;
        int c = coluna_inicial + i * esquerdaoudireita;
        tabuleiro[l][c] = NAVIO;
    }
    return 1;
}
int main()
{
    // Coordenadas iniciais dos navios
    int linhaNavioHorizontal = 0;
    int colunaNavioHorizontal = 0;
    int linhaNavioVertical = 1;
    int colunaNavioVertical = 0;
    int linhaInicialdiagonal1 = 6, linhaInicialdiagonal2 = 0;
    int colunainicialDiagonal1 = 5, colunainicialDiagonal2 = 9;

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    char cabecalho = 'A';

    // Inicializa o tabuleiro com 0 (água)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            tabuleiro[i][j] = 0;
        }
    }
    // ===== Posicionando navio nas Diagonal =====
    colocarNavioDiagonal(tabuleiro, linhaInicialdiagonal1, colunainicialDiagonal1, Direita, Sobe);
    colocarNavioDiagonal(tabuleiro, linhaInicialdiagonal2, colunainicialDiagonal2, esquerda, desce);

    // ===== Posicionando navio horizontal =====
    colocarNavioHV(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal, horizontal);

    // ===== Posicionando navio Vertical =====
    colocarNavioHV(tabuleiro, linhaNavioVertical, colunaNavioVertical, vertical);

    // ===== Exibição do tabuleiro =====
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        printf("%c ", cabecalho++);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
