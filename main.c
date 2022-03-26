#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 10

enum Cell {
    Dead = 0,
    Alive = 1
};

void print_board(int *board) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i * SIZE + j] == Alive) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int count_neighbours(int *board, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int x_ = x + i;
            int y_ = y + j;
            if (x_ < 0 || x_ >= SIZE || y_ < 0 || y_ >= SIZE) {
                continue;
            }
            count += board[x_ * SIZE + y_];
        }
    }
    return count;
}

void next_generation(int *board) {
    int next_board[SIZE * SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int neighbours = count_neighbours(board, i, j);
            if (board[i * SIZE + j] == Alive) {
                if (neighbours < 2 || neighbours > 3) {
                    next_board[i * SIZE + j] = Dead;
                } else {
                    next_board[i * SIZE + j] = Alive;
                }
            } else {
                if (neighbours == 3) {
                    next_board[i * SIZE + j] = Alive;
                } else {
                    next_board[i * SIZE + j] = Dead;
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i * SIZE + j] = next_board[i * SIZE + j];
        }
    }
}

int main() {

    int board[SIZE * SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i * SIZE + j] = rand() % 2;
        }
    }

    for (int i = 0; i < 50; i++) {
        print_board(board);
        next_generation(board);
        sleep(1);
        system("clear");
    }

    return 0;
}