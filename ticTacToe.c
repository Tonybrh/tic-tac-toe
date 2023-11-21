#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()  {
    int line, column;
    int movement = 1;
    char crossCircle[5];
    // matriz de caracteres 3 por 3
    char board[3][3] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}};
    system("cls");

    // Você precisa usar loops para imprimir a matriz
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n"); // Pule para a próxima linha após imprimir uma linha da matriz
    }
    while (movement <= 9)
    {
        printf("Digite o numero em linha em que vc deseja marcar \n");
        scanf("%d", &line);
        printf("Digite o numero em coluna em que vc deseja marcar \n");
        scanf("%d", &column);

        printf("Digite o que vc deseja marcar (X ou O) \n");
        scanf("%s", &crossCircle);

        line -= 1;
        column -= 1;

        while (board[line][column] != '-')
        {
            printf("Esse espaco ja foi selecionado, escolha outro.\n");
            printf("Numero da linha: \n");
            scanf("%d", &line);
            printf("Numero da coluna: \n");
            scanf("%d", &column);
            printf("Digite o que vc deseja marcar (X ou O) \n");
            scanf("%s", &crossCircle);
            line -= 1;
            column -= 1;
        }

        if (strcasecmp(crossCircle, "X") == 0)
        {
            // Check if the chosen cell is already occupied
            if (board[line][column] == '-')
            {
                board[line][column] = 'X';
                movement++;
            }
        }
        else if (strcasecmp(crossCircle, "O") == 0)
        {
            // Check if the chosen cell is already occupied {
            if (board[line][column] == '-')
            {
                board[line][column] = 'O';
                movement++;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("%c ", board[i][j]);
            }
            printf("\n"); // Pule para a próxima linha após imprimir uma linha da matriz
        }
    }
    return 0;
}