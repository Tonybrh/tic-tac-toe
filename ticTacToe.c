#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Estrutura para armazenar informações do jogador
typedef struct {
    char nome[50];
    int vitorias;
} Jogador;

void displayBoard(char **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void freeBoard(char **board, int size) {
    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}

// Função para verificar se há um vencedor

int checkWinner(char **board, int size, char symbol) {
    // Verificar linhas e colunas
    for (int i = 0; i < size; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return 1; // Vitória na linha
        }
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
            return 1; // Vitória na coluna
        }
    }

    // Verificar diagonais
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return 1; // Vitória na diagonal principal
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return 1; // Vitória na diagonal secundária
    }

    return 0; // Nenhum vencedor encontrado
}

// Função para jogar
void jogar(Jogador *jogadores, int *quantidadeJogadores) {
    int line, column;
    int movement = 1;

    // Tamanho do tabuleiro
    int size = 3;

    // Alocar dinamicamente memória para o tabuleiro
    char **board = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        board[i] = (char *)malloc(size * sizeof(char));
    }

    // Inicializar o tabuleiro
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '-';
        }
    }

    // Variáveis para rastrear os símbolos dos jogadores
    char player1Symbol, player2Symbol;

    // Solicitar aos jogadores que escolham X ou O
    printf("Jogador 1, escolha X ou O: ");
    scanf(" %c", &player1Symbol);

    // Validar a escolha do jogador 1 (aceitar tanto maiúsculas quanto minúsculas)
    while (toupper(player1Symbol) != 'X' && toupper(player1Symbol) != 'O') {
        printf("Escolha invalida. Por favor, escolha X ou O: ");
        scanf(" %c", &player1Symbol);
    }

    // Atribuir o símbolo oposto ao jogador 2
    player2Symbol = (toupper(player1Symbol) == 'X') ? 'O' : 'X';

    printf("Jogador 2, voce ficara com %c\n", player2Symbol);

    displayBoard(board, size);

    while (movement <= size * size) {
        int currentPlayer = (movement % 2) + 1;
        printf("Jogador %d, digite o numero em linha em que você deseja marcar: \n", currentPlayer);
        scanf("%d", &line);
        printf("Jogador %d, digite o numero em coluna em que você deseja marcar: \n", currentPlayer);
        scanf("%d", &column);

        line -= 1;
        column -= 1;

        while (board[line][column] != '-') {
            printf("Este espaço ja foi selecionado, escolha outro.\n");
            printf("Numero da linha: \n");
            scanf("%d", &line);
            printf("Numero da coluna: \n");
            scanf("%d", &column);
            line -= 1;
            column -= 1;
        }

        // Marcar com o símbolo do jogador atual
        char currentSymbol = (currentPlayer == 1) ? player1Symbol : player2Symbol;
        board[line][column] = currentSymbol;
        movement++;

        displayBoard(board, size);

        // Verificar se há um vencedor após cada movimento
        if (checkWinner(board, size, currentSymbol)) {
            printf("Jogador %d (simbolo %c) venceu!\n", currentPlayer, currentSymbol);

            // Atualizar o número de vitórias do jogador no array de jogadores
            if (currentPlayer == 1) {
                jogadores[0].vitorias++;
            } else {
                jogadores[1].vitorias++;
            }

            break;
        }
    }

    // Se nenhum vencedor for encontrado após todas as jogadas
    if (movement > size * size) {
        printf("O jogo terminou em empate.\n");
    }

    // Liberar memória alocada para o tabuleiro
    freeBoard(board, size);
}

// Função para exibir o ranking
void verRanking(Jogador *jogadores, int quantidadeJogadores) {
    printf("\nRanking:\n");

    // Ordenar jogadores por número de vitórias (em ordem decrescente)
    for (int i = 0; i < quantidadeJogadores - 1; i++) {
        for (int j = i + 1; j < quantidadeJogadores; j++) {
            if (jogadores[i].vitorias < jogadores[j].vitorias) {
                Jogador temp = jogadores[i];
                jogadores[i] = jogadores[j];
                jogadores[j] = temp;
            }
        }
    }

    // Exibir ranking
    for (int i = 0; i < quantidadeJogadores; i++) {
        printf("%d. %s - Vitorias: %d\n", i + 1, jogadores[i].nome, jogadores[i].vitorias);
    }
}

// Função para exibir os créditos
void creditos() {
    printf("\nDesenvolvido por: \n Antonio Eduardo \n Pedro Lucas Honorato \n David Guimarães \n Eraldo Neto \n João Henrique\n");
}

int main() {
    // Inicializar jogadores
    Jogador jogadores[2]; // Inicialmente, dois jogadores
    int quantidadeJogadores = 2;

    // Inicializar informações dos jogadores
    for (int i = 0; i < quantidadeJogadores; i++) {
        printf("Digite o nome do Jogador %d: ", i + 1);
        scanf("%s", jogadores[i].nome);
        jogadores[i].vitorias = 0; // Inicializar o número de vitórias como zero
    }

    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Jogar\n");
        printf("2. Ver Ranking\n");
        printf("3. Creditos\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogar(jogadores, &quantidadeJogadores);
                break;
            case 2:
                verRanking(jogadores, quantidadeJogadores);
                break;
            case 3:
                creditos();
                break;
            case 4:
                printf("Saindo do jogo. Obrigado por jogar!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    return 0;
}
