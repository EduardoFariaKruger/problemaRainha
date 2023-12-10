#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

#define N 8

int isContained(int i, int j)
{
    return ((i >= 0 && i < N) && (j >= 0 && j < N))
}

void initializeBoard(int T[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            T[i][j] = 0;
        }
    }
}

void printBoard(int T[N][N])
{
    usleep(300000); // faz uma pequena pausa de 3ms para imprimir o próximo tabuleiro, já que a tendência desse algoritmo é fazer várias e várias impressões
    printf("\e[1;1H\e[2J"); // comando para limpar o terminal antes de fazer a próxima impressão 
    /*
        percorre todas as posições do tabuleiro, verificando se a casa possui ou não uma rainha
    */
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(T[i][j] == 1)
            {
                printf("Q");
            }
            else
            {
                printf("@");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int isSafe(int T[N][N], int row, int column)
{
    /*checks if the row already has a queen*/
    for(int i = 0; i < N; i++)
    {
        if (T[row][i] == 1)
        {
            return 0;
        }
    }

    /*checks the diagonals based on the current try*/
    for (int i = row, j = column; isContained(i, j); i++, j--)
    {
        if(T[i][j] == 1)
        {
            return 0;
        }
    }
    for (int i = row, j = column; isContained(i, j); i++, j++)
    {
        if(T[i][j] == 1)
        {
            return 0;
        }
    }
    for (int i = row, j = column; isContained(i, j); i--, j--)
    {
        if(T[i][j] == 1)
        {
            return 0;
        }
    }
    for (int i = row, j = column; isContained(i, j); i--, j++)
    {
        if(T[i][j] == 1)
        {
            return 0;
        }
    }
    return 1;
}

int try(int T[N][N], int column)
{
    if(column == N)
    {
        printBoard(T);
        return 1;
    }
    int isit = 0;
    for(int i = 0; i < N; i++)
    {
        if (isSafe(T, i, column))
        {
            T[i][column] = 1;

            isit = isit || try(T, column + 1);

            T[i][column] = 0;
        }
    }
    return isit;
}

int solve()
{
    int T[N][N];
    initializeBoard(T);
    return try(T, 0);
}


int main()
{  
    if(solve() == 1)
    {
        printf("solução encontrada");
    }
    else
    {
        printf("não existe solução");
    }
    return 0;
}