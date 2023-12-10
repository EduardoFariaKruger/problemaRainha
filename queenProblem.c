#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

#define N 8


/*
    checa se a casa (i, j) está contida na matriz T.
*/
int isContained(int i, int j)
{
    return ((i >= 0 && i < N) && (j >= 0 && j < N));
}

/*
 * percorre toda a matriz T inicializando todos os seus valores como 0.
*/
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

/*
    faz a impressao de todo o tabuleiro usando o caracter "+" para as casas nao ocupadas e "Q" para as casas que possuem uma rainha
*/
void printBoard(int T[N][N])
{
    printf("\e[1;1H\e[2J"); // comando para limpar o terminal antes de fazer a próxima impressão 
    usleep(300000); // pausa de 300ms

    /*
     * loops que percorrem toda a matriz verificando se a casa esta ocupada por uma rainha
    */
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(T[i][j] == 1)
            {
                printf(" Q ");
            }
            else
            {
                printf(" + ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * checa se a casa (row, column) esta segura para ser colocada uma rainha. Entende-se que 2 rainhas nao podem ser colocadas na mesma coluna, entao o programa
 * tenta apenas colocar 1 rainha por coluna, logo, resta fazer a verificacao da linha e das diagonais. A funcao retorna 1 caso a casa seja segura, ou seja, 
 * nao tenha nenhuma outra rainha na mesma linha ou diagonal, e 0 caso haja pelo menos uma rainha na mesma linha ou diagonal. 
*/
int isSafe(int T[N][N], int row, int column)
{
    /*
     * faz a verificacao da linha
    */
    for(int i = 0; i < N; i++)
    {
        if (T[row][i] == 1)
        {
            return 0;
        }
    }

   /*
    * faz a verificacao da diagonal inferior esquerda a partir da casa onde a peca esta sendo colocada
   */
    for (int i = row, j = column; isContained(i, j); i++, j--)
    {
        if(T[i][j] == 1)
        {
            return 0;
        }
    }

    /*
     * faz a verificacao da diagonal inferior direita a partir da casa onde a peca esta sendo colocada
    */
    for (int i = row, j = column; isContained(i, j); i++, j++)
    {
        if(T[i][j] == 1)
        {
            return 0;
        }
    }

    /*
     * faz a verificacao da diagonal superior esquerda a partir da casa onde a peca esta sendo colocada
    */
    for (int i = row, j = column; isContained(i, j); i--, j--)
    {
        if(T[i][j] == 1)
        {
            return 0;
        }
    }

    /*
     * faz a verificacao da diagonal superior direita a partir da casa onde a peca esta sendo colocada
    */
    for (int i = row, j = column; isContained(i, j); i--, j++)
    {
        if(T[i][j] == 1)
        {
            return 0;
        }
    }
    return 1;
}


/*
 * faz as tentativas usando da estrategia de backtracking e retorna 1 caso tenha sido encontrada uma possibilidade para resolver o prooblema
 * e 0 caso nao tenha sido encontrada pelo menos uma possibilidade
*/
int try(int T[N][N], int column)
{
    printBoard(T); /*faz a impressao do tabuleiro atual antes da impressao*/

    /*
     * caso base, verifica se o programa ja colocou todas as rainhas no tabuleiro com seguranca, nesse caso imprime o tabuleiro atual e retorna 1,
     * pois todas as rainhas foram colocadas com sucesso 
    */
    if(column == N)
    {
        printBoard(T);
        return 1;
    }

    
    int isit = 0; /*cria uma variavel de controle*/

    /*percorre todas as casas da primeira linha e verifica se a partir dessa casa (i, column) eh possivel achar um caminho que resulte em todas as rainhas
     * estando no tabuleiro de forma segura
    */
    for(int i = 0; i < N; i++)
    {
        if (isSafe(T, i, column))
        {
            T[i][column] = 1; /*caso seja seguro colocar na casa (i, column), coloque uma rainha lá*/
            isit = isit || try(T, column + 1); /*verifique se eh possivel colocar todas as rainhas nas demais colunas de tal maneira que nenhuma se enxergue (de forma segura)*/
            
            
            if (isit) /*caso seja possivel, retorne 1*/
            {
                return 1;
            }


            else /*caso nao seja possivel, desfaca o movimento. Dessa forma o laco for vai continuar e o programa vai tentar a casa (i + 1, column)*/
            {
                T[i][column] = 0;
            }
        }
    }
    return isit; /*caso o programa nao tenha encontrado uma solucao nas tentativas, retorne 0, que esta guardado na variavel de controle*/
}

/*
 * funcao que resolve o problema das 8 rainhas tentando por forca bruta as possibilidades ate achar alguma.
 * retorna 1 caso o programa tenha encontrado 1 caminho e 0 caso nao tenha encontrado nenhum caminho.
*/
int solve()
{
    int T[N][N];
    initializeBoard(T);
    return try(T, 0);
}


int main()
{  
    /*caso o problema tenha sido resolvido, imprima que a solucao foi encontrada*/
    if(solve() == 1)
    {
        printf("solução encontrada\n");
    }

    /*caso contrario, imprima que nao existe uma solucao para o problema das 8 rainhas*/
    else
    {
        printf("não existe solução\n");
    }
    return 0;
}