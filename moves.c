#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "chess.h"
#include "moves.h"

move_t *check_pawn_move(game_t *this_game, int rank, int file, int protect_king, enum color player) {
  if (rank >= 0 && rank < 8) {
    if (file >= 0 && file < 8) {
      if (this_game->board[rank][file]->occupied) {
        if (this_game->board[rank][file]->piece->player != player) {
          move_t *this_move = malloc(sizeof(move_t));
          this_move->has_capture = 1;
          this_move->double_pawn = 0;
          this_move->en_passant = 0;
          if ((player == WHITE && rank == 7) ||
              (player == BLACK && rank == 0)) {
            this_move->promotion = 1;
          }
          else {
            this_move->promotion = 0;
          }
          return this_move;
        }
      }
    }
  }
  return NULL;
}

move_t ***get_moves_pawn(game_t *this_game, int rank, int file, int protect_king) {
  enum color player;
  int direction;
  int move_count = 0;
  if (protect_king == 1) {
    player = this_game->player;
  }
  else if (protect_king == 0) {
    if (this_game->player == WHITE) {
      player = BLACK;
    }
    else if (this_game->player == BLACK) {
      player = WHITE;
    }
  }
  if (player == WHITE) {
    direction = 1;
  }
  else if (player == BLACK) {
    direction = -1;
  }
  move_t ***piece_moves = malloc(8 * sizeof(move_t**));
  int i;
  for (i = 0; i < 8; i++) {
    piece_moves[i] = malloc(8 * sizeof(move_t*));
  }
  piece_moves[rank + direction][file - 1] = check_pawn_move(this_game, rank + direction, file - 1, protect_king, player);
  piece_moves[rank + direction][file + 1] = check_pawn_move(this_game, rank + direction, file + 1, protect_king, player);

  return piece_moves;
}

move_t ***get_moves_bishop(game_t *this_game, int rank, int file, int protect_king) {

}

move_t ***get_moves_knight(game_t *this_game, int rank, int file, int protect_king) {

}

move_t ***get_moves_rook(game_t *this_game, int rank, int file, int protect_king) {

}

move_t ***get_moves_queen(game_t *this_game, int rank, int file, int protect_king) {

}

move_t ***get_moves_king(game_t *this_game, int rank, int file, int protect_king) {

}

move_t ***get_moves_for_piece(game_t *this_game, int rank, int file, int protect_king) {
  move_t ***moves_for_piece;
  if (this_game->board[rank][file]->occupied) {
    if (this_game->board[rank][file]->piece->player == this_game->player) {
      switch (this_game->board[rank][file]->piece->type) {
        case PAWN:
          moves_for_piece = get_moves_pawn(this_game, rank, file, protect_king);
          break;
        case BISHOP:
          moves_for_piece = get_moves_bishop(this_game, rank, file, protect_king);
          break;
        case KNIGHT:
          moves_for_piece = get_moves_knight(this_game, rank, file, protect_king);
          break;
        case ROOK:
          moves_for_piece = get_moves_rook(this_game, rank, file, protect_king);
          break;
        case QUEEN:
          moves_for_piece = get_moves_queen(this_game, rank, file, protect_king);
          break;
        case KING:
          moves_for_piece = get_moves_king(this_game, rank, file, protect_king);
          break;
      }
    }
    else {
      return NULL;
    }
  }
  return moves_for_piece;
}

move_t *****get_all_valid_moves(game_t *this_game) {
  int i;
  int j;
  move_t *****all_moves = malloc(8 * sizeof(move_t****));
  for (i = 0; i < 8; i++) {
    all_moves[i] = malloc(8 * sizeof(move_t***));
    for (j = 0; j < 8; j++) {
      all_moves[i][j] = get_moves_for_piece(this_game, i, j, 1);
    }
  }
  return all_moves;
}

// do stuff here
