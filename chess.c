#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include "chess.h"
#include "moves.h"

char *file_chars = "abcdefgh";

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
      this_game->board[rank][file]->rank = rank + 1;
      this_game->board[rank][file]->file = file_chars[file];
    }
  }

  this_game->white_capt_pieces = malloc(sizeof(enum type*) * 16);
  this_game->black_capt_pieces = malloc(sizeof(enum type*) * 16);

  return this_game;
}

piece_t *new_piece(enum color player, enum type type) {
  piece_t *piece = malloc(sizeof(piece_t));
  piece->player = player;
  piece->type = type;
  if (type == PAWN) {
    piece->pawn_en_passant = 1;
    piece->pawn_double = 1;
  }
  else {
    piece->pawn_en_passant = 0;
    piece->pawn_double = 0;
  }
  return piece;
}

void set_default_board(game_t *this_game) {
  int file;
  for (file = 0; file < 8; file++) {
    this_game->board[1][file]->piece = new_piece(WHITE, PAWN);
    this_game->board[6][file]->piece = new_piece(BLACK, PAWN);

    this_game->board[0][file]->occupied = 1;
    this_game->board[1][file]->occupied = 1;
    this_game->board[6][file]->occupied = 1;
    this_game->board[7][file]->occupied = 1;
  }

  this_game->board[0][0]->piece = new_piece(WHITE, ROOK);
  this_game->board[0][1]->piece = new_piece(WHITE, KNIGHT);
  this_game->board[0][2]->piece = new_piece(WHITE, BISHOP);
  this_game->board[0][3]->piece = new_piece(WHITE, QUEEN);
  this_game->board[0][4]->piece = new_piece(WHITE, KING);
  this_game->board[0][5]->piece = new_piece(WHITE, BISHOP);
  this_game->board[0][6]->piece = new_piece(WHITE, KNIGHT);
  this_game->board[0][7]->piece = new_piece(WHITE, ROOK);

  this_game->board[7][0]->piece = new_piece(BLACK, ROOK);
  this_game->board[7][1]->piece = new_piece(BLACK, KNIGHT);
  this_game->board[7][2]->piece = new_piece(BLACK, BISHOP);
  this_game->board[7][3]->piece = new_piece(BLACK, QUEEN);
  this_game->board[7][4]->piece = new_piece(BLACK, KING);
  this_game->board[7][5]->piece = new_piece(BLACK, BISHOP);
  this_game->board[7][6]->piece = new_piece(BLACK, KNIGHT);
  this_game->board[7][7]->piece = new_piece(BLACK, ROOK);
}

void print_game_state(game_t *this_game) {
  char *player = "Empty";
  if (this_game->player == WHITE) {
    player = "White";
  }
  else if (this_game->player == BLACK) {
    player = "Black";
  }

  printf("Turn %d (%s)\n\n\n", this_game->turn, player);
  printf("   a b c d e f g h  \n\n");
  int rank;
  int file;
  char to_print;
  for (rank = 7; rank >= 0; rank--) {
    printf("%d  ", rank + 1);
    for (file = 0; file < 8; file++) {
      if (this_game->board[rank][file]->occupied) {
        switch (this_game->board[rank][file]->piece->type) {
          case PAWN:
            to_print = 'p';
            break;
          case BISHOP:
            to_print = 'b';
            break;
          case KNIGHT:
            to_print = 'n';
            break;
          case ROOK:
            to_print = 'r';
            break;
          case QUEEN:
            to_print = 'q';
            break;
          case KING:
            to_print = 'k';
            break;
        }
        if (this_game->board[rank][file]->piece->player) {
          to_print = toupper(to_print);
        }
      }
      else {
        to_print = '.';
      }
      printf("%c ", to_print);
    }
    printf(" %d\n", rank + 1);
  }
  printf("\n   a b c d e f g h  \n");
}

void get_user_input(char *prompt, char *dest) {
  if (prompt != NULL && strlen(prompt) > 0) {
    printf("%s", prompt);
    fflush(stdout);
  }
  while (fgets(dest, 1000, stdin) == NULL) {
    printf("No command given. Enter \"help\" for a list of commands.\n");
  }
  dest[strlen(dest) - 1] = '\0';
}

int main() {
  int game_over = 0;
  int advance = 0;
  char user_str[1000];

  game_t *this_game = new_game();
  set_default_board(this_game);

  while (!game_over) {
    print_game_state(this_game);
    move_t *****all_valid_moves = get_all_valid_moves(this_game);
    get_user_input("Enter command:\n", user_str);
    if (!(strcmp(user_str, "quit"))) {
      get_user_input("Are you sure? (y/n)\n", user_str);
      if (!(strcmp(user_str, "y"))) {
        printf("Exiting.\n");
        exit(0);
      }
    }
    if (this_game->player == WHITE) {
      this_game->player = BLACK;
    }
    else {
      this_game->turn += 1;
      this_game->player = WHITE;
    }
  }
}
