#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 160
#define HEIGHT 40
#define TRUE 1
#define FALSE 0
#define PROBABILITY 30
#define ALIVE '#'
#define DEAD ' '

int main(int argc, char *argv[]) {
  int symmetry = FALSE;
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (!strcmp(argv[i], "-s"))
        symmetry = TRUE;
    }
  }

  srand(time(NULL));
  char map[HEIGHT][WIDTH];
  char tmpMap[HEIGHT][WIDTH];

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH / ((symmetry) ? 2 : 1); j++) {
      if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) {
        if (symmetry)
          map[i][WIDTH - j - 1] = DEAD;
        map[i][j] = DEAD;
      } else {
        int tmp_perc = rand() % 100 > (100 - PROBABILITY);
        if (symmetry)
          map[i][WIDTH - j - 1] = (tmp_perc) ? ALIVE : DEAD;
        map[i][j] = (tmp_perc) ? ALIVE : DEAD;
      }
    }
  }

  while (TRUE) {
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        tmpMap[i][j] = DEAD;
      }
    }

    for (int i = 1; i < HEIGHT - 1; i++) {
      for (int j = 1; j < WIDTH - 1; j++) {
        int neighbors =
            (map[i - 1][j - 1] == '#') + (map[i - 1][j + 0] == '#') +
            (map[i - 1][j + 1] == '#') + (map[i + 0][j - 1] == '#') +
            (map[i + 0][j + 1] == '#') + (map[i + 1][j - 1] == '#') +
            (map[i + 1][j + 0] == '#') + (map[i + 1][j + 1] == '#');

        if ((map[i][j] == ALIVE && (neighbors == 2 || neighbors == 3)) ||
            map[i][j] == DEAD && neighbors == 3)
          tmpMap[i][j] = ALIVE;
        else
          tmpMap[i][j] = DEAD;
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

    usleep(120000);
  }
  return 0;
}
