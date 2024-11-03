// Author: Aidan Ahmad
// Desc: To emulate an art editor through the use of commands.

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

char const QUIT   = 'Q';
int const  HEIGHT = 8;
int const  WIDTH  = 16;

struct TextGrid {
    char       **tiles;
    unsigned int height;
    unsigned int width;
};
// desc: deletes the grid provided
// pre: receives a TextGrid grid
// post: sets another grid equal to current grid
void del(TextGrid &grid) {
    for (unsigned int i = 0; i < grid.height; i++) {
        delete[] grid.tiles[i];
    }
    delete[] grid.tiles;
}
// desc: loads the grid under the name provided 'file_path'
// pre: receives a string
// post: file is opened and closed successfully
TextGrid load_grid(string file_path) {
    ifstream myfile;
    myfile.open(file_path);
    TextGrid loaded_grid;
    loaded_grid.tiles = nullptr;
    int    height     = 0;
    int    width      = 0;
    int    i          = 0;
    string temp;
    while (std::getline(myfile, temp)) {
        height++;
        width = temp.size();
    }
    loaded_grid.tiles  = new char *[height]; // Allocating grid and giving height and width
    loaded_grid.width  = width;
    loaded_grid.height = height;
    myfile.clear();
    myfile.seekg(0, std::ios::beg);
    if (myfile.is_open()) {
        while (std::getline(myfile, temp)) {
            loaded_grid.tiles[i] = new char[width];
            for (int k = 0; k < width; k++) { // Allocating grid and supplying data
                loaded_grid.tiles[i][k] = temp[k];
            }
            i++;
        }
    } else {
        cout << "Error opening file.";
    }
    myfile.close();
    return loaded_grid;
}
// desc: save the grid under the name provided 'file_path'
// pre: receives a string
// post: file is opened and closed successfully
void save_grid(TextGrid &grid, string file_path) {
    ofstream myfile;
    string   s;
    myfile.open(file_path);
    if (myfile.is_open()) {
        for (unsigned int i = 0; i < grid.height; i++) {
            for (unsigned int j = 0; j < grid.width; j++) { // Reading data onto file
                myfile << grid.tiles[i][j];
            }
            myfile << "\n";
        }
    } else {
        cout << "Error opening file.";
    }
    myfile.close();
}
// desc: prints out the grid provided
// pre: receives a 2D allocated array
//
//
void show(TextGrid &grid) {
    for (unsigned int i = 0; i < grid.height; i++) {
        for (unsigned int j = 0; j < grid.width; j++) {
            cout << grid.tiles[i][j]; // Outputting data
        }
        cout << endl;
    }
}
// desc: resize the grid upon call
// pre: receives grid and new size
// post: grid is correctly resized
void resize_grid(TextGrid &grid, unsigned int new_size, string direction) {
    TextGrid temp;
    temp.height      = grid.height;
    temp.width       = grid.width;
    temp.tiles       = nullptr;
    int height_limit = grid.height;
    int width_limit  = grid.width;
    if (direction == "col") {
        width_limit = (new_size < temp.width) ? new_size : temp.width; // Supplying limits and size based on input
        temp.width  = new_size;
    } else {
        height_limit = (new_size < temp.height) ? new_size : temp.height; // Supplying limits and size based on input
        temp.height  = new_size;
    }
    temp.tiles = new char *[temp.height];
    for (unsigned int i = 0; i < temp.height; i++) {
        temp.tiles[i] = new char[temp.width];
    }
    for (int i = 0; i < height_limit; i++) {
        for (int j = 0; j < width_limit; j++) {
            temp.tiles[i][j] = grid.tiles[i][j]; // Copying data
        }
    }
    del(grid);
    grid = temp;
}
// desc: put a character in the xth and yth slot
// pre: receives character, x value, y value and grid
void paint(TextGrid &grid, unsigned int x, unsigned int y, char fill) {
    if (y > 0 && y < grid.height) {
        if (x > 0 && x < grid.width) {
            grid.tiles[y][x] = fill;
        } else {
            cout << "X coordinate was not in the bounds of the current grid." << endl;
        }
    } else {
        cout << "Y coordinate was not in the bounds of the current grid." << endl;
    }
}
// desc: acts upon command received and gives the respective output
// pre: receives a char for a command and its respective invariants
//
void commands(TextGrid &grid, char command) {
    char         target;
    char         replace;
    unsigned int x;
    unsigned int y;
    char         character;
    string       load_file;
    string       save_file;
    TextGrid     load;
    switch (command) {
    case 'P':
        cin >> x >> y >> character;   // Paints a char "character" at xth and yth
        paint(grid, x, y, character); // spot
        break;
    case 'T':
        cin >> target >> replace;
        for (unsigned int i = 0; i < grid.height; i++) {
            for (unsigned int j = 0; j < grid.width; j++) { // Transforms all "target" onto grid into
                if (grid.tiles[i][j] == target) {           // "replace"
                    grid.tiles[i][j] = replace;
                }
            }
        }
        break;
    case 'L':
        cin >> load_file;
        load = load_grid(load_file); // Loads a grid from a file "load_file"
        del(grid);                   // and applies it to grid
        grid = load;
        break;
    case 'S':
        cin >> save_file;
        save_grid(grid, save_file); // Saves a grid to "save_file"
        break;
    case 'R':
        cin >> character;
        resize_grid(grid, grid.height + 1, "row");
        for (unsigned int i = 0; i < grid.width; i++) { // Adds a row of "character"
            grid.tiles[grid.height - 1][i] = character;
        }
        break;
    case 'r':
        resize_grid(grid, grid.height - 1, "row"); // Removes a row
        break;
    case 'C':
        cin >> character;
        resize_grid(grid, grid.width + 1, "col");
        for (unsigned int i = 0; i < grid.height; i++) { // Adds a column of "character"
            grid.tiles[i][grid.width - 1] = character;
        }
        break;
    case 'c':
        resize_grid(grid, grid.width - 1, "col"); // Removes a column
        break;
    case 'Q':
        del(grid); // Quit
        exit(0);
    default:
        cout << "Invalid Command" << endl;
    }
}
// desc: Initalizes grid, receives commands and shows grid on loop until quit
// post: All memory freed, no leaks
int main() {
    TextGrid grid;
    grid.tiles  = nullptr;
    grid.height = 8;
    grid.width  = 16;
    char again  = 'N';
    char command;
    grid.tiles = new char *[HEIGHT];

    for (int i = 0; i < HEIGHT; i++) {
        grid.tiles[i] = new char[WIDTH];
        for (int j = 0; j < WIDTH; j++) {
            grid.tiles[i][j] = '`';
        }
    }
    cout << endl;
    while (again != QUIT) {
        show(grid);
        cout << "Input command here: ";
        cin >> command;
        cout << endl;
        commands(grid, command);
        cout << endl;
    }

    del(grid);
    cout << endl;
    return 0;
}