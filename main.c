#include <stdio.h>

//Declare global variables
char board[3][3] = { {' ','_','_'}, {' ','_','_'}, {' ','_','_'} };

//Declare prototypes
void showBoard();
void playerTurn(int, int*);
int winCondition();

int main()
{
    //Declare variables
    int menu,
        player,
        quit = 0;

    //Loops the game until user wants to quit
    while(menu != 2)
    {
        //Display menu and take input from user
        printf("TIC-TAC-WHOA \n-------------------------- \n1.NEW GAME \n2.EXIT \n\nChoose an option: ");
        scanf("%d", &menu);

        //Terminates program
        if(menu == 2)
        break;
        printf("\n");
        printf("'qu' to resign \n");    //Lets the user how to resign

        //Loop till no more spaces on the board
        for(int i = 1; i <= 9; i++)
        {
            //Checks if player resigned
            if(quit == 1)
                break;

            //Calculates which player's turn it is
            player = i % 2;
            if(player == 1)
            {
                playerTurn(player, &quit);
            }
            else
            {
                player += 2;
                playerTurn(player, &quit);
            }

            //Checks if win conditions are met
            if(winCondition() == 0)
            {
                showBoard();
                printf("Player %d Wins!\n\n", player);
                break;
            }

        }

        //Display resignation message
        if(quit == 1)
        {
            printf("Player %d Resigns!\n\n", player);
        }

        //Display win message
        else if(winCondition() == 1)
        {
            showBoard();
            printf("It's a TIE!\n\n");
        }

        //Resets the board for the next game
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(j == 0)
                    board[i][0] = ' ';
                else
                    board[i][j] = '_';
            }
        }
    }

    return 0;
}

///Displays the board
void showBoard()
{
    printf("3 _%c_|_%c_|_%c_  \n2 _%c_|_%c_|_%c_  \n1  %c | %c | %c   \n   A   B   C\n\n",
    board[0][2],board[1][2],board[2][2],
    board[0][1],board[1][1],board[2][1],
    board[0][0],board[1][0],board[2][0]);
}

///Takes the player's input for where they want to place their tile
void playerTurn(int player, int *quit)
{
    //Declare variables
    char column = '+';
    char row = '+';

    //Show board and prompts the player to enter where they want to place their tile
    showBoard();
    printf("Player %d's Move: ", player);
    scanf(" %c%c", &column, &row);
    printf("\n");

    //Check if the player resigns
    if(column == 'q' && row == 'u')
    {
        *quit = 1;
        return;
    }

    ///Tests for errors
    //If the row is not entered
    while(row == '\n')
    {
        printf("Invalid move, please specify both column and row.\n");
        showBoard();
        printf("Player %d's Move: ", player);
        scanf(" %c%c", &column, &row);
        printf("\n");
    }

    //If the columns and rows are not in range
    while( ((column < 'A') || (column > 'C')) || ((row < '1') || (row > '3')) )
    {
        printf("Invalid move, please pick a viable spot.\n");
        showBoard();
        printf("Player %d's Move: ", player);
        scanf(" %c%c", &column, &row);
        printf("\n");
    }

    //If the space is already occupied
    while((board[column - 65][row - 49] == 'X') || (board[column - 65][row - 49] == 'O'))
    {
        printf("Invalid move, please choose another spot.\n");
        showBoard();
        printf("Player %d's Move: ", player);
        scanf(" %c%c", &column, &row);
        printf("\n");
    }

    //Converts to data compatible with the board
    column -= 65;
    row -= 49;

    //Determines which tile is placed
    if(player == 1)
    {
        board[column][row] = 'X';
    }
    else
    {
        board[column][row] = 'O';
    }
}

///Checks whether the player has made a winning move
int winCondition()
{
    int win = 1;

    for(int i = 0; i < 3; i++)
    {
        if( ((board[0][i] == 'X') && (board[1][i] == 'X') && (board[2][i] == 'X')) || ((board[0][i] == 'O') && (board[1][i] == 'O') && (board[2][i] == 'O')) )
        return 0;

        else if( ((board[i][0] == 'X') && (board[i][1] == 'X') && (board[i][2] == 'X')) || ((board[i][0] == 'O') && (board[i][1] == 'O') && (board[i][2] == 'O')) )
        return 0;

        else if( ((board[2][2] == 'X') && (board[1][1] == 'X') && (board[0][0] == 'X')) || ((board[2][2] == 'O') && (board[1][1] == 'O') && (board[0][0] == 'O')) )
        return 0;

        else if( ((board[0][2] == 'X') && (board[1][1] == 'X') && (board[2][0] == 'X')) || ((board[0][2] == 'O') && (board[1][1] == 'O') && (board[2][0] == 'O')) )
        return 0;
    }

    return win;
}
