#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 23
#define DEAD 0
#define ALIVE 1
//#define TURNS 100

void print_state(char * board);
void turn(char * board, char * new_board);

int main(int argc, char **argv) {
  char board1[SIZE*SIZE];
  char board2[SIZE*SIZE];
  int i = 0;
  int board = 1;
  int sleep_time = 1;
  char * position = 0;
  int turns = 100;

  for (i = 1; i < argc; ++i) {
    if (strncmp(argv[i], "--sleep-time=", 13) == 0) {
      if (1 != sscanf(argv[i]+13, "%d", &sleep_time)) {
	sleep_time = 1;
      }
    } else if (strncmp(argv[i], "--position=", 11) == 0) {
      size_t len = strlen(argv[i] + 11);
      position = malloc(sizeof(*position) * (len + 1));
      if (!position) exit(1);
      strcpy(position, argv[i]+11);
    } else if (strncmp(argv[i], "--turns=", 8) == 0) {
      if (1 != sscanf(argv[i]+8, "%d", &turns)) {
	turns = 100;
      }
    } 
  }

  if (sleep_time > 10 || sleep_time < 0) {
    sleep_time = 1;
  }

  if (turns < 0) {
    turns = 100;
  }

  memset(&(board1[0]), DEAD, sizeof(*board1) * SIZE * SIZE);
  memset(&(board2[0]), DEAD, sizeof(*board2) * SIZE * SIZE);
  
  // INITIAL POSITION

  printf("sleep time = %d\nturns = %d\n", sleep_time, turns);
  if (position) {
    printf("position = %s\n", position);
    //  TOAD / Period 2
    if (strcmp(position, "toad") == 0) {
      board1[4*SIZE + 4] = ALIVE;
      board1[4*SIZE + 5] = ALIVE;
      board1[4*SIZE + 6] = ALIVE;
      board1[5*SIZE + 3] = ALIVE;
      board1[5*SIZE + 4] = ALIVE;
      board1[5*SIZE + 5] = ALIVE;
    } else if (strcmp(position, "blinker") == 0) {
      // BLINKER / Period 2
      board1[4*SIZE + 4] = ALIVE;
      board1[4*SIZE + 5] = ALIVE;
      board1[4*SIZE + 6] = ALIVE;
    } else if (strcmp(position, "r-pentomino") == 0) {
      // R-PENTOMINO
      board1[8*SIZE + 8] = ALIVE;
      board1[9*SIZE + 8] = ALIVE;
      board1[10*SIZE + 8] = ALIVE;
      board1[8*SIZE + 9] = ALIVE;
      board1[9*SIZE + 7] = ALIVE;
    } else if (strcmp(position, "beacon") == 0) {
      board1[8*SIZE + 8] = ALIVE;
      board1[8*SIZE + 9] = ALIVE;
      board1[9*SIZE + 8] = ALIVE;
      board1[9*SIZE + 9] = ALIVE;
      
      board1[10*SIZE + 10] = ALIVE;
      board1[10*SIZE + 11] = ALIVE;
      board1[11*SIZE + 11] = ALIVE;
      board1[11*SIZE + 10] = ALIVE;
    } else if (strcmp(position, "pulsar") == 0) {
      board1[8*SIZE + 8] = ALIVE;
      board1[9*SIZE + 8] = ALIVE;
      board1[10*SIZE + 8] = ALIVE;
      board1[11*SIZE + 7] = ALIVE;
      board1[11*SIZE + 6] = ALIVE;
      board1[11*SIZE + 5] = ALIVE;
      board1[6*SIZE + 7] = ALIVE;
      board1[6*SIZE + 6] = ALIVE;
      board1[6*SIZE + 5] = ALIVE;
      board1[8*SIZE + 3] = ALIVE;
      board1[9*SIZE + 3] = ALIVE;
      board1[10*SIZE + 3] = ALIVE;

      board1[8*SIZE + 10] = ALIVE;
      board1[9*SIZE + 10] = ALIVE;
      board1[10*SIZE + 10] = ALIVE;      
      board1[11*SIZE + 11] = ALIVE;
      board1[11*SIZE + 12] = ALIVE;
      board1[11*SIZE + 13] = ALIVE;
      board1[10*SIZE + 15] = ALIVE;
      board1[9*SIZE + 15] = ALIVE;
      board1[8*SIZE + 15] = ALIVE;
      board1[6*SIZE + 13] = ALIVE;
      board1[6*SIZE + 12] = ALIVE;
      board1[6*SIZE + 11] = ALIVE;

      board1[14*SIZE + 8] = ALIVE;
      board1[15*SIZE + 8] = ALIVE;
      board1[16*SIZE + 8] = ALIVE;
      board1[13*SIZE + 7] = ALIVE;
      board1[13*SIZE + 6] = ALIVE;
      board1[13*SIZE + 5] = ALIVE;
      board1[18*SIZE + 7] = ALIVE;
      board1[18*SIZE + 6] = ALIVE;
      board1[18*SIZE + 5] = ALIVE;
      board1[16*SIZE + 3] = ALIVE;
      board1[15*SIZE + 3] = ALIVE;
      board1[14*SIZE + 3] = ALIVE;      

      board1[14*SIZE + 10] = ALIVE;
      board1[15*SIZE + 10] = ALIVE;
      board1[16*SIZE + 10] = ALIVE;
      board1[13*SIZE + 11] = ALIVE;
      board1[13*SIZE + 12] = ALIVE;
      board1[13*SIZE + 13] = ALIVE;
      board1[18*SIZE + 11] = ALIVE;
      board1[18*SIZE + 12] = ALIVE;
      board1[18*SIZE + 13] = ALIVE;
      board1[16*SIZE + 15] = ALIVE;
      board1[15*SIZE + 15] = ALIVE;
      board1[14*SIZE + 15] = ALIVE;
    } else {
      printf("Starting positions: toad, blinker, beacon, r-pentomino\n");
      exit(0);
    }
  } else {
      board1[8*SIZE + 8] = ALIVE;
      board1[9*SIZE + 8] = ALIVE;
      board1[10*SIZE + 8] = ALIVE;
      board1[8*SIZE + 9] = ALIVE;
      board1[9*SIZE + 7] = ALIVE;
  }

  for (i = 0; i < turns; ++i) {
    if (board) {
      print_state(&(board1[0]));
      turn(&(board1[0]), &(board2[0]));
    } else {
      print_state(&(board2[0]));
      turn(&(board2[0]), &(board1[0]));
    }
    board ^= 1;
    sleep(sleep_time);
  }

  if (position) {
    free(position);
  }
  
  return 0;
}

void print_state(char * board) {
  int i = 0;
  int j = 0;

  char line[SIZE*4+2];
  memset(&(line[0]), '-', sizeof(char) * (SIZE*4 + 1));
  line[SIZE*4+1] = '\0';
  printf("%s\n", line);
  for ( ; i < SIZE; ++i) {
    printf("|");
    for (j = 0; j < SIZE; ++j) {
      if (board[i*SIZE + j] == ALIVE) {
	printf(" X |");
      } else {
	printf("   |");
      }
    }
    printf("\n%s\n", line);
  }
}

void turn(char * board, char * new_board) {
  int i = 0;
  int j;
  int neighbors;

  for ( ; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      neighbors = 0;

      // not efficient at all, but doesn't really matter
      if (i + 1 < SIZE && board[(i+1)*SIZE + j] == ALIVE) {
	++neighbors;
      }
      if (i - 1 >= 0 && board[(i-1)*SIZE + j] == ALIVE) {
	++neighbors;
      }
      if (j + 1 < SIZE && board[i*SIZE + j + 1] == ALIVE) {
	++neighbors;
      }
      if (j - 1 >= 0 && board[i*SIZE + j - 1] == ALIVE) {
	++neighbors;
      }
      if (i + 1 < SIZE && j + 1 < SIZE && board[(i+1)*SIZE + j + 1] == ALIVE) {
	++neighbors;
      }
      if (i - 1 >= 0 && j - 1 >= 0 && board[(i-1)*SIZE + j - 1] == ALIVE) {
	++neighbors;
      }
      if (i - 1 >= 0 && j + 1 < SIZE && board[(i-1)*SIZE + j + 1] == ALIVE) {
	++neighbors;
      }
      if (i + 1 < SIZE && j - 1 >= 0 && board[(i+1)*SIZE + j - 1] == ALIVE) {
	++neighbors;
      }

      if (board[i*SIZE + j] == DEAD) {
	if (neighbors == 3) {
	  new_board[i*SIZE + j] = ALIVE;
	} else {
	  new_board[i*SIZE + j] = DEAD;
	}
      } else if (board[i*SIZE + j] == ALIVE) {
	if (neighbors < 2 || neighbors > 3) {
	  new_board[i*SIZE + j] = DEAD;
	} else {
	  new_board[i*SIZE + j] = ALIVE;
	}
      }
    }
  }
}
