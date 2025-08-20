#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3

int main()
{
    // Coordenadas iniciais dos navios
    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 4;
    int linhaNavioVertical = 6;
    int colunaNavioVertical = 0;

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

    // ===== Posicionando navio horizontal =====
    if (linhaNavioHorizontal < 0 || linhaNavioHorizontal >= TAMANHO_TABULEIRO)
    {
        printf("Linha do navio horizontal está fora do tabuleiro!\n");
    }
    else if (colunaNavioHorizontal + TAMANHO_NAVIO > TAMANHO_TABULEIRO)
    {
        printf("Navio horizontal não cabe na linha!\n");
    }
    else
    {
        int podeColocar = 1;
        // Verifica sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] == NAVIO)
            {
                podeColocar = 0;
                printf("Já há um navio posicionado horizontalmente nessa linha!\n");
                break;
            }
        }
        // Coloca o navio se possível
        if (podeColocar)
        {
            for (int i = 0; i < TAMANHO_NAVIO; i++)
            {
                tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] = NAVIO;
            }
        }
    }

    // ===== Posicionando navio vertical =====
    if (colunaNavioVertical < 0 || colunaNavioVertical >= TAMANHO_TABULEIRO)
    {
        printf("Coluna do navio vertical está fora do tabuleiro!\n");
    }
    else if (linhaNavioVertical + TAMANHO_NAVIO > TAMANHO_TABULEIRO)
    {
        printf("Navio vertical não cabe na coluna!\n");
    }
    else
    {
        int podeColocar = 1;
        // Verifica sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++)
        {
            if (tabuleiro[linhaNavioVertical + i][colunaNavioVertical] == NAVIO)
            {
                podeColocar = 0;
                printf("Já há um navio posicionado verticalmente nessa coluna!\n");
                break;
            }
        }
        // Coloca o navio se possível
        if (podeColocar)
        {
            for (int i = 0; i < TAMANHO_NAVIO; i++)
            {
                tabuleiro[linhaNavioVertical + i][colunaNavioVertical] = NAVIO;
            }
        }
    }

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
