#include "board.h"

using namespace std;
// Desc: Constructs an object of type board based on the size input and initializes it
// Pre: Receives size
Board::Board(int size) {
    board_size = size;
    squares    = new char *[board_size];
    for (int i = 0; i < board_size; i++) { // Allocating memory
        squares[i] = new char[board_size];
    }
    for (int j = 0; j < board_size; j++) {
        for (int i = 0; i < board_size; i++) { // Initializes grid
            squares[i][j] = ' ';
        }
    }
}
// Desc: Deconstructs an object of type board
// Post: All memory is freed, no leaks
Board::~Board() {
    for (int i = 0; i < board_size; i++) {
        delete[] squares[i];
    }
    delete[] squares;
}
// Desc: Displays the current state of the board object
void Board::display() {
    int x_axis = 0;
    int y_axis = 0;
    for (int k = -1; k < board_size; k++) {
        if (k == -1) {
            cout << "   ";
        } else {
            cout << "  " << x_axis << " "; // X_axis numbers to call upon during play
            x_axis++;
        }
    }
    for (int i = 0; i < board_size; i++) {
        cout << endl;
        for (int i = -1; i < board_size; i++) {
            if (i == -1) {
                cout << "    "; // Horizontal lines of the grid
            } else {
                cout << "----";
            }
        }
        cout << endl;
        for (int j = 0; j < board_size; j++) {
            if (j == 0) {
                cout << "  " << y_axis << " | " << squares[i][j] << " | ";
                y_axis++; // Y_axis numbers as well as vertical lines of grid
            } else {
                cout << squares[i][j] << " | ";
            }
        }
    }
    cout << endl;
    for (int i = -1; i < board_size; i++) {
        if (i == -1) {
            cout << "    "; // Last line of the grid
        } else {
            cout << "----";
        }
    }
    cout << endl;
}
// Desc: Decides whether or not the board object is full of chars
// Post: Returns true or false
bool Board::isFull() {
    int count = 0;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (squares[i][j] == 'X' || squares[i][j] == 'O') { // Checking if grid is full of symbols
                count++;
            }
        }
    }
    if (count == (board_size * board_size)) {
        return true;
    } else {
        return false;
    }
}
// Desc: Decides whether or not a player has won upon call
// Pre: Receives object of class player
// Post: Returns true or false
bool Board::isWinner(player input) {
    char symbol      = input.getSymbol();
    int  h_count     = 0;
    int  v_count     = 0;
    int  diag1_count = 0;
    int  diag2_count = 0;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (squares[i][j] == symbol) {
                h_count++;
            }                              // Checking if grid has 3 vertical or horizontal
            if (squares[j][i] == symbol) { // symbols of the same for a win check
                v_count++;
            }
        }
        if (h_count == board_size) {
            return true;
        } else {
            h_count = 0;
        }
        if (v_count == board_size) {
            return true;
        } else {
            v_count = 0;
        }
    }
    int col1 = 0;
    for (int i = 0; i < board_size; i++) {

        if (squares[i][col1] == symbol) {
            diag1_count++; // Checking if grid has 3 diagonal from left to right
        }
        col1++;
    }
    if (diag1_count == board_size) {
        return true;
    } else {
        diag1_count = 0;
    }
    int col2 = board_size - 1;
    for (int i = 0; i < board_size; i++) {
        if (squares[i][col2] == symbol) { // Checking if grid has 3 diagonal from right to left
            diag2_count++;
        }
        col2--;
    }
    if (diag2_count == board_size) {
        return true;
    } else {
        diag2_count = 0;
    }
    cout << endl;
    return false;
}
// Desc: Returns the size of the object of class board
// Post: Returns board_size
int Board::getSize() {
    return board_size;
}
// Desc: Places symbol upon call
// Pre: Receives x, y and the player for their symbol
// Post: Board object receives a new char
void Board::placeSymbol(int row, int column, player user) {
    char symbol          = user.getSymbol();
    squares[row][column] = symbol;
}
// Desc: Initializes the board object to empty space
void Board::initialize() {
    for (int j = 0; j < board_size; j++) {
        for (int i = 0; i < board_size; i++) {
            squares[i][j] = ' '; // Initializing board object to empty space
        }
    }
}
// Desc: Gets the called space
// Pre: Receives x and y
// Post: Returns char
char Board::getSpace(int x, int y) {
    return squares[x][y];
}