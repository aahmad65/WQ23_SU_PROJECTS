#include<iostream>
#include "player.h"

class Board{
    private:
        char **squares;
        int board_size;
    public:
        Board(int size);
        ~Board();
        void display();
        bool isFull();
        bool isWinner(player input);
        int getSize();
        void placeSymbol(int row, int column, player user);
        void initialize();
        char getSpace(int x, int);
};