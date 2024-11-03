// Aidan Ahmad
// Desc: Emulate the game Tic Tac Toe.

#include <iostream>

int const  P1TURN = 1;
int const  P2TURN = 2;
char const YES    = 'y';

using namespace std;
// desc: Send welcome message upon call.
void welcome() {
    cout << endl;
    cout << "Welcome to Tic-Tac-Toe! You and another player will take turns back and forth placing a " << endl;
    cout << "symbol on the board. The goal is to get three of your symbol in a row. This means in a column, " << endl;
    cout << "row or diagonal. Player one is X's and player two is O's. Player one will go first." << endl;
    cout << "Decide who will be which. Good luck!" << endl;
    cout << "Press enter to continue... ";
    cin.ignore();
}
// desc: Initialize the board for the tic-tac-toe game.
// pre: char array 11 x 11.
// post: empty array with grid.
void setup_board(char (&grid)[12][12]) {
    for (int j = 0; j < 12; j++) {
        for (int k = 0; k < 12; k++) {
            grid[j][k] = ' ';
        }
    }
    grid[0][2]  = 'A';
    grid[0][6]  = 'B';
    grid[0][10] = 'C'; // Setting up the system for the user to decide on the row/column they want
    grid[2][0]  = 'D'; // their symbol to be placed in.
    grid[6][0]  = 'E';
    grid[10][0] = 'F';
    for (int i = 1; i < 12; i++) {
        grid[i][4] = '|';
        grid[i][8] = '|'; // Setting up grid for the tic-tac-toe game.
        grid[4][i] = '-';
        grid[8][i] = '-';
    }
}
// desc: Print board upon call.
// pre: Array is initialized.
// post: Board is printed.
void print_board(char board[12][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}
// desc: Take the turn for each player.
// pre: Board is initialized and turn is 1 or 2.
// post: Takes turn of the player.
void take_turn(char board[12][12], int turn) {
    char symbol;
    char choice1;
    char choice2;
    int  col;
    int  row;
    bool column_ok   = false;
    bool row_ok      = false;
    bool turn_finish = false;
    if (turn == 1) {
        symbol = 'X';
    } else if (turn == 2) {
        symbol = 'O';
    }
    while (turn_finish == false) {
        while (column_ok == false) {
            cout << "Choose the column you would like to place your symbol on(a/b/c): ";
            cin >> choice1;
            if (choice1 == 'a') {
                col       = 2;
                column_ok = true;
            } else if (choice1 == 'b') {
                col       = 6;
                column_ok = true; // Validating the input and assigning the column to the user's choice.
            } else if (choice1 == 'c') {
                col       = 10;
                column_ok = true;
            } else {
                column_ok = false;
            }
        }
        while (row_ok == false) {
            cout << "Choose the row you would like to place your symbol on(d/e/f): ";
            cin >> choice2;
            if (choice2 == 'd') {
                row    = 2;
                row_ok = true;
            } else if (choice2 == 'e') {
                row    = 6;
                row_ok = true;
            } else if (choice2 == 'f') { // Validing the input and assigning the row to the user's choice.
                row    = 10;
                row_ok = true;
            } else {
                row_ok = false;
            }
        }
        if (board[row][col] != ' ') {
            cout << "Please pick another space. This one is taken." << endl;
            column_ok = false;
            row_ok    = false;
        } else {
            board[row][col] = symbol;
            turn_finish     = true;
        }
    }
}
// desc: Switches turns upon call.
// pre: Receives integer of 1 or 0.
// post: Returns integer of 1 or 0.
int p_turn(int turn) {
    if (turn == 2) {
        return 1;
    } else if (turn == 1) {
        return 2;
    }
    return 0;
}
// desc: Checks if there has been three symbols in a row.
// pre: Receives board of symbols.
// post: Returns winner of 1 or 2 or tie.
int win_check(char board[12][12]) {
    int winner = 0;
    if (board[2][2] == 'X' && board[6][6] == 'X' && board[10][10] == 'X') {
        winner = 1;
    } else if (board[2][2] == 'X' && board[2][6] == 'X' && board[2][10] == 'X') {
        winner = 1;
    } else if (board[6][2] == 'X' && board[6][6] == 'X' && board[6][10] == 'X') {
        winner = 1;
    } else if (board[10][2] == 'X' && board[10][6] == 'X' && board[10][10] == 'X') {
        winner = 1;
    } else if (board[2][2] == 'X' && board[6][2] == 'X' && board[10][2] == 'X') { // Checking horizontal and vertical
        winner = 1;                                                               // and diagonal win conditions.
    } else if (board[2][6] == 'X' && board[6][6] == 'X' && board[10][6] == 'X') {
        winner = 1;
    } else if (board[2][10] == 'X' && board[6][10] == 'X' && board[10][10] == 'X') {
        winner = 1;
    } else if (board[10][2] == 'X' && board[6][6] == 'X' && board[2][10] == 'X') {
        winner = 1;
    }

    if (board[2][2] == 'O' && board[6][6] == 'O' && board[10][10] == 'O') {
        winner = 2;
    } else if (board[2][2] == 'O' && board[2][6] == 'O' && board[2][10] == 'O') {
        winner = 2;
    } else if (board[6][2] == 'O' && board[6][6] == 'O' && board[6][10] == 'O') {
        winner = 2;
    } else if (board[10][2] == 'O' && board[10][6] == 'O' && board[10][10] == 'O') {
        winner = 2;
    } else if (board[2][2] == 'O' && board[6][2] == 'O' && board[10][2] == 'O') { // Checking horizontal and vertical
        winner = 2;                                                               // and diagonal win conditions.
    } else if (board[2][6] == 'O' && board[6][6] == 'O' && board[10][6] == 'O') {
        winner = 2;
    } else if (board[2][10] == 'O' && board[6][10] == 'O' && board[10][10] == 'O') {
        winner = 2;
    } else if (board[10][2] == 'O' && board[6][6] == 'O' && board[2][10] == 'O') {
        winner = 2;
    }

    return winner;
}
int main() {
    int  turn_num = 1;
    int  turn     = 1;
    bool win      = false;
    char again    = YES;
    char grid[12][12];
    int  winner;
    int  x_wins = 0;
    int  o_wins = 0;
    int  ties   = 0;

    cout << endl;
    welcome();

    while (again == YES) {
        cout << "X Wins: " << x_wins << endl;
        cout << "O Wins: " << o_wins << endl;
        setup_board(grid);
        while (win != true) {
            print_board(grid);
            take_turn(grid, turn);
            turn   = p_turn(turn);

            winner = win_check(grid);

            if (winner == 1) {
                cout << "X's has won!" << endl;
                x_wins++;
                win = true;
            } else if (winner == 2) { // Printing winner based on win_check functions.
                cout << "O's has won!" << endl;
                o_wins++;
                win = true;
            } else if (winner == 0 && turn_num == 9) {
                cout << "It's a tie!" << endl;
                ties++;
                win = true;
            }
            turn_num++;
        }
        win = false;
        cout << "Would you like to play another round?(y/n): ";
        cin >> again;
    }

    cout << endl;
    return 0;
}
