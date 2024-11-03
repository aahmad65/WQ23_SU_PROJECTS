// Author: Aidan Ahmad
// Desc: To emulate the game tic-tac-toe using classes

#include "board.h"
#include <iostream>

using namespace std;

// Desc: Welcome the user to the program
void welcome() {
    cout << "Welcome to Tic-Tac-Toe again! In this game, you will play tic-tac-toe through\n";
    cout << "inputting the square you want to place your symbol in through numbers and letters.\n";
    cout << "Enjoy!";
}
// Desc: Bid the user goodbye
void goodbye() {
    cout << "Thanks for playing. Have a great day!";
}
// Desc: Take turn for the player
// Pre: Receives player
void take_turn(Board game, player user) {
    int  x_axis;
    int  y_axis;
    bool valid_placement = false;
    bool valid_x         = false;
    bool valid_y         = false;
    cout << endl;
    while (valid_placement == false) {
        valid_y = false;
        valid_x = false;
        while (valid_y == false) {
            cout << "Which row would you like to choose? (Number): ";
            cin >> y_axis;
            if (y_axis > -1 && y_axis < game.getSize()) { // Verifying row input
                valid_y = true;
            }
        }
        while (valid_x == false) {
            cout << "Which column would you like to choose? (Number): ";
            cin >> x_axis;
            if (x_axis > -1 && x_axis < game.getSize()) { // Verifying column input
                valid_x = true;
            }
        }
        if (game.getSpace(y_axis, x_axis) != ' ') { // Verifying space choice
            cout << "There is already a symbol there. Please choose another space." << endl;
        } else {
            valid_placement = true;
        }
    }
    game.placeSymbol(y_axis, x_axis, user);
    cout << endl;
}
// Desc: Emulate the game tic-tac-toe
int main() {
    player x('X');
    player o('O');
    int    turn    = 1;
    char   play    = 'Y';
    bool   running = true;
    int    input   = 3;
    bool   valid   = false;
    cout << endl;
    welcome();
    cout << endl;
    while (valid == false) {
        cout << "How wide/tall would you like the board to be?\n";
        cout << "Enter a single whole number bigger than 3: "; // Getting board size
        cin >> input;
        if (input >= 3) {
            valid = true;
        }
        cout << endl;
    }
    Board grid(input);
    while (play == 'Y') {
        running = true;
        turn    = 1;
        while (running == true) {
            cout << "Player 1 (X's) Points: " << x.getPoints() << endl; // Outputting player points
            cout << "Player 2 (O's) Points: " << o.getPoints() << endl;
            grid.display();
            if (turn == 1) {
                take_turn(grid, x);
                turn++;
            } else {
                take_turn(grid, o);
                turn--;
            }
            if (grid.isWinner(x) == true) {
                x.awardPoint();
                grid.display();
                running = false;
                cout << "Player 1 is the winner. Would you like to play another round? (Y/N): ";
                cin >> play;
            } else if (grid.isWinner(o) == true) { // Checking win conditions for both players
                running = false;
                grid.display();
                o.awardPoint();
                cout << "Player 2 is the winner. Would you like to play another round? (Y/N): ";
                cin >> play;
            }
            if (grid.isFull() == true) { // Checking if board is full
                if (grid.isWinner(x) == true) {
                    x.awardPoint();
                    running = false;
                    grid.display();
                    cout << "Player 1 is the winner. Would you like to play another round? (Y/N): ";
                    cin >> play;
                } else if (grid.isWinner(o) == true) {
                    running = false; // Checking on win just in case
                    grid.display();
                    o.awardPoint();
                    cout << "Player 2 is the winner. Would you like to play another round? (Y/N): ";
                    cin >> play;
                } else {
                    running = false; // Checking on win just in case
                    grid.display();
                    cout << "It's a tie! Would you like to play another round? (Y/N): ";
                    cin >> play;
                }
            }
        }
        grid.initialize(); // Reinitializing grid upon end of round and they want to keep playing
    }
    goodbye();

    cout << endl;
    return 0;
}