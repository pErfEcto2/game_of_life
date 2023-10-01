#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 130
#define HEIGHT 40
#define TRUE 1
#define FALSE 0
#define PROBABILITY 30

int main() {
  srand(time(NULL));
  char map[HEIGHT][WIDTH];
  char tmpMap[HEIGHT][WIDTH];

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
        map[i][j] = ' ';
      else
        map[i][j] = (rand() % 100 > (100 - PROBABILITY)) ? '#' : ' ';
    }
  }

  while (TRUE) {
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        tmpMap[i][j] = ' ';
      }
    }

    for (int i = 1; i < HEIGHT - 1; i++) {
      for (int j = 1; j < WIDTH - 1; j++) {
        int neighbors =
            (map[i - 1][j - 1] == '#') + (map[i - 1][j + 0] == '#') +
            (map[i - 1][j + 1] == '#') + (map[i + 0][j - 1] == '#') +
            (map[i + 0][j + 1] == '#') + (map[i + 1][j - 1] == '#') +
            (map[i + 1][j + 0] == '#') + (map[i + 1][j + 1] == '#');

        if ((map[i][j] == '#' && (neighbors == 2 || neighbors == 3)) ||
            map[i][j] == ' ' && neighbors == 3)
          tmpMap[i][j] = '#';
        else
          tmpMap[i][j] = ' ';
      }
    }

    for (int i = 1; i < HEIGHT - 1; i++) {
      for (int j = 1; j < WIDTH - 1; j++) {
        map[i][j] = tmpMap[i][j];
      }
    }

    system("clear");
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        printf("%c", map[i][j]);
      }
      printf("\n");
    }

    usleep(150000);
  }
  return 0;
}
