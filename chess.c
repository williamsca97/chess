#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "chess.h"

game_t *new_game() {
  game_t *this_game = malloc(sizeof(game_t));
  this_game->turn = 1;
  this_game->player = WHITE;
  this_game->white_capt_num = 0;
  this_game->black_capt_num = 0;

  this_game->board = malloc(8 * sizeof(square_t**));
  int rank;
  int file;
  for (rank = 0; rank < 8; rank++) {
    this_game->board[rank] = malloc(8 * sizeof(square_t*));
    for (file = 0; file < 8; file++) {
      this_game->board[rank][file] = malloc(sizeof(square_t));
      this_game->board[rank][file]->occupied = 0;
      this_game->board[rank][file]->piece = EMPTY;
      this_game->board[rank][file]->player = NONE;
    }
  }

  this_game->white_capt_pieces = malloc(sizeof(enum type*) * 16);
  this_game->black_capt_pieces = malloc(sizeof(enum type*) * 16);
  int i;
  for (i = 0; i < 16; i++) {
    this_game->white_capt_pieces[i] = EMPTY;
    this_game->black_capt_pieces[i] = EMPTY;
  }

  return this_game;
}

void set_default_board(game_t *this_game) {
  int file;
  for (file = 0; file < 8; file++) {
    this_game->board[0][file]->player = WHITE;
    this_game->board[1][file]->player = WHITE;
    this_game->board[6][file]->player = BLACK;
    this_game->board[7][file]->player = BLACK;

    this_game->board[1][file]->piece = PAWN;
    this_game->board[6][file]->piece = PAWN;
  }

  this_game->board[0][0]->piece = ROOK;
  this_game->board[0][1]->piece = KNIGHT;
  this_game->board[0][2]->piece = BISHOP;
  this_game->board[0][3]->piece = QUEEN;
  this_game->board[0][4]->piece = KING;
  this_game->board[0][5]->piece = BISHOP;
  this_game->board[0][6]->piece = KNIGHT;
  this_game->board[0][7]->piece = ROOK;

  this_game->board[7][0]->piece = ROOK;
  this_game->board[7][1]->piece = KNIGHT;
  this_game->board[7][2]->piece = BISHOP;
  this_game->board[7][3]->piece = QUEEN;
  this_game->board[7][4]->piece = KING;
  this_game->board[7][5]->piece = BISHOP;
  this_game->board[7][6]->piece = KNIGHT;
  this_game->board[7][7]->piece = ROOK;
}

void print_game_state(game_t *this_game) {
  char *player = "Empty";
  if (this_game->player = WHITE) {
    player = "White";
  }
  else if (this_game->player = BLACK) {
    player = "Black";
  }

  printf("Turn: %d (%s)\n", this_game->turn, player);
}

int main() {
  game_t *this_game = new_game();
  set_default_board(this_game);
  print_game_state(this_game);
}
