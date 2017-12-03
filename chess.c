#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "chess.h"

game_t *new_game() {
  game_t *this_game = malloc(sizeof(game_t*));
  this_game->turn = 1;
  this_game->player = WHITE;
  this_game->white_capt_num = 0;
  this_game->black_capt_num = 0;

  square_t ***this_board = malloc(sizeof(square_t*) * 64);
  int rank;
  int file;
  for (rank = 0; rank < 8; rank++) {
    for (file = 0; file < 8; file++) {
      this_board[rank][file] = malloc(sizeof(square_t));
      this_board[rank][file]->occupied = 0;
      this_board[rank][file]->piece = EMPTY;
      this_board[rank][file]->player = NONE;
    }
  }
  this_game->board = this_board;

  enum type *white_capt_arr = malloc(sizeof(enum type*) * 16);
  enum type *black_capt_arr = malloc(sizeof(enum type*) * 16);
  int i;
  for (i = 0; i < 16; i++) {
    white_capt_arr[i] = EMPTY;
    black_capt_arr[i] = EMPTY;
  }
  this_game->white_capt_pieces = white_capt_arr;
  this_game->black_capt_pieces = black_capt_arr;

  return this_game;
}

void set_default_board(game_t *this_game) {
  int file;
  for (file = 0; file < 8; file++) {
    this_game->board[0][file]->player = WHITE;
    this_game->board[1][file]->player = WHITE;
    this_game->board[7][file]->player = BLACK;
    this_game->board[8][file]->player = BLACK;

    this_game->board[1][file]->piece = PAWN;
    this_game->board[7][file]->piece = PAWN;
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

int main() {
  game_t *this_game = new_game();
  set_default_board(this_game);
}
