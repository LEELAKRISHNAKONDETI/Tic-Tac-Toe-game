#include <stdio.h>
#include <string.h>

#define SIZE 3

// ANSI COLOR CODES
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

void initBoard(char board[SIZE][SIZE]) {
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            board[i][j] = ' ';
}

void printBoard(char board[SIZE][SIZE], char s1, char s2) {
    printf("\n");
    printf(BLUE BOLD"     0   1   2\n"RESET);
    printf(BLUE BOLD"   -------------\n"RESET);

    for(int i=0;i<SIZE;i++) {
        printf(BLUE BOLD" %d |"RESET, i);
        for(int j=0;j<SIZE;j++) {

            if(board[i][j] == s1)
                printf(GREEN BOLD" %c "RESET"|", board[i][j]);
            else if(board[i][j] == s2)
                printf(RED BOLD" %c "RESET"|", board[i][j]);
            else
                printf(" %c |", board[i][j]);
        }
        printf("\n"BLUE BOLD"   -------------\n"RESET);
    }
    printf("\n");
}

int checkWin(char board[SIZE][SIZE], char ch) {
    for(int i=0;i<SIZE;i++)
        if(board[i][0]==ch && board[i][1]==ch && board[i][2]==ch)
            return 1;

    for(int j=0;j<SIZE;j++)
        if(board[0][j]==ch && board[1][j]==ch && board[2][j]==ch)
            return 1;

    if(board[0][0]==ch && board[1][1]==ch && board[2][2]==ch)
        return 1;

    if(board[0][2]==ch && board[1][1]==ch && board[2][0]==ch)
        return 1;

    return 0;
}

int isFull(char board[SIZE][SIZE]) {
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            if(board[i][j]==' ')
                return 0;
    return 1;
}

int main() {
    char board[SIZE][SIZE];
    char player1[20], player2[20];
    char symbol1, symbol2;
    int row, col;
    int turn = 1;

    initBoard(board);

    printf(CYAN BOLD"============= TIC - TAC - TOE =============\n\n"RESET);

    printf(YELLOW "Enter Player 1 Name: "RESET);
    fgets(player1, sizeof(player1), stdin);
    player1[strcspn(player1, "\n")] = 0;

    while(1) {
        printf(YELLOW "Enter Player 2 Name: "RESET);
        fgets(player2, sizeof(player2), stdin);
        player2[strcspn(player2, "\n")] = 0;

        if(strcmp(player1, player2) == 0)
            printf(RED "Names cannot be same! Enter again.\n"RESET);
        else
            break;
    }

    printf(YELLOW "\nChoose Player 1 Symbol (X or O): "RESET);
    scanf(" %c", &symbol1);

    symbol1 = (symbol1=='O' || symbol1=='o') ? 'O' : 'X';
    symbol2 = (symbol1=='O') ? 'X' : 'O';

    printf(GREEN BOLD"\n%s = %c\n"RESET, player1, symbol1);
    printf(RED   BOLD"%s = %c\n\n"RESET, player2, symbol2);

    printf(CYAN BOLD"=========== GAME START ===========\n"RESET);
    printBoard(board, symbol1, symbol2);

    while(1) {
        char currentSymbol = (turn % 2 != 0) ? symbol1 : symbol2;
        char *currentPlayer = (turn % 2 != 0) ? player1 : player2;
        char *color = (turn % 2 != 0) ? GREEN : RED;

        printf("%s%s (%c)%s enter your move (row col): ",
               color, currentPlayer, currentSymbol, RESET);

        scanf("%d %d", &row, &col);

        if(row<0 || row>=SIZE || col<0 || col>=SIZE) {
            printf(RED "Invalid position! Use 0-2.\n"RESET);
            continue;
        }

        if(board[row][col] != ' ') {
            printf(RED "Position already taken! Try again.\n"RESET);
            continue;
        }

        board[row][col] = currentSymbol;
        printBoard(board, symbol1, symbol2);

        if(checkWin(board, currentSymbol)) {
            printf("\n🎉 %s%s YOU WIN! 🎉%s\n",
                   color, currentPlayer, RESET);
            break;
        }

        if(isFull(board)) {
            printf(YELLOW BOLD"\nIt's a DRAW! No winner.\n"RESET);
            break;
        }

        turn++;
    }

    return 0;
}
