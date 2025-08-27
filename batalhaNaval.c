#include <stdio.h>
#include <stdlib.h>  
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AREA_AFETADA 5
// Direções para navios diagonais
#define esquerda -1
#define Direita 1
#define Sobe -1
#define desce 1
// Tipos de posicionamento de navio
#define horizontal 1
#define vertical 0

// Função para criar a matriz de habilidade em forma de cone
void criarMatrizCone(int matriz[5][5])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j >= 2 - i && j <= 2 + i)
            {
                matriz[i][j] = 1; 
            }
            else
            {
                matriz[i][j] = 0; 
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de cruz
void criarMatrizCruz(int matriz[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == 2 || j == 2)
            {
                matriz[i][j] = 1; 
            }
            else
            {
                matriz[i][j] = 0; 
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de octaedro
void criarMatrizOctaedro(int matriz[5][5])
{
    int centro = 2;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (abs(i - centro) + abs(j - centro) <= 2)
            {
                matriz[i][j] = 1;
            }
            else
            {
                matriz[i][j] = 0; 
            }
        }
    }
}

// Função para verificar se a área da habilidade está livre e dentro dos limites do tabuleiro
int verificarAreaLivre(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int matriz[5][5], int linha, int coluna)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int l = linha + i - 2;  // Centraliza a matriz
            int c = coluna + j - 2; // Centraliza a matriz
            if (matriz[i][j] == 1)
            {
                // Verifica se a posição está dentro dos limites do tabuleiro
                if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
                {
                    return 0; // Área não está livre (fora dos limites)
                }
                // Verifica se já existe um navio na posição
                if (tabuleiro[l][c] == NAVIO)
                {
                    return 0; // Área não está livre (já existe um navio)
                }
            }
        }
    }
    return 1; // Área está livre e dentro dos limites
}

// Função para sobrepor a matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int matriz[5][5], int linha, int coluna)
{
    if (!verificarAreaLivre(tabuleiro, matriz, linha, coluna))
    {
        printf("Não é possível aplicar a habilidade na posição (%d, %d) devido a um navio ou por estar fora dos limites.\n", linha, coluna);
        return; // Não aplica a habilidade se a área não estiver livre
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int l = linha + i - 2;  // Centraliza a matriz
            int c = coluna + j - 2; // Centraliza a matriz
            if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO && matriz[i][j] == 1)
            {
                tabuleiro[l][c] = AREA_AFETADA; // Marca a área afetada
            }
        }
    }
}

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
    int colunaNavioHorizontal = 5;
    int linhaNavioVertical = 0;
    int colunaNavioVertical = 0;
    int linhaInicialdiagonal1 = 6, linhaInicialdiagonal2 = 0;
    int colunainicialDiagonal1 = 5, colunainicialDiagonal2 = 9;

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0}; // Inicializa o tabuleiro com 0 (água)
    int cabecalho = 0;

    // ===== Posicionando navio nas Diagonal =====
    colocarNavioDiagonal(tabuleiro, linhaInicialdiagonal1, colunainicialDiagonal1, Direita, Sobe);   // Direita e Sobe
    colocarNavioDiagonal(tabuleiro, linhaInicialdiagonal2, colunainicialDiagonal2, esquerda, desce); // Esquerda e Desce

    // ===== Posicionando navio horizontal =====
    colocarNavioHV(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal, horizontal); // Horizontal

    // ===== Posicionando navio Vertical =====
    colocarNavioHV(tabuleiro, linhaNavioVertical, colunaNavioVertical, vertical); // Vertical

    // Criando matrizes de habilidades
    int matrizCone[5][5];
    int matrizCruz[5][5];
    int matrizOctaedro[5][5];

    criarMatrizCone(matrizCone);
    criarMatrizCruz(matrizCruz);
    criarMatrizOctaedro(matrizOctaedro);

    // Aplicando habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, matrizCone, 2,3 );     // Aplica cone na posição (2, 2)
    aplicarHabilidade(tabuleiro, matrizCruz, 7, 7);     // Aplica cruz na posição (5, 5)
    aplicarHabilidade(tabuleiro, matrizOctaedro, 5, 2); // Aplica octaedro na posição (7, 7)

    // Exibição do tabuleiro
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        printf("%d ", cabecalho++);
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
