#ifndef CHESS_H
#define CHESS_H

#include <stdint.h>

typedef enum type {EMPTY, KING, QUEEN, KNIGHT, ROOK, BISHOP, PAWN} type;
typedef enum color {NONE, WHITE, BLACK} color;

typedef struct piece_t {
  enum type type;
  enum color player;
  uint8_t pawn_en_passant;
  uint8_t pawn_double;
} piece_t;

typedef struct square_t {
  uint8_t occupied;
  uint8_t rank;
  char file;
  piece_t *piece;
} square_t;

typedef struct game_t {
  uint32_t turn;
  enum color player;
  square_t ***board;
  uint8_t white_capt_num;
  uint8_t black_capt_num;
  enum type **white_capt_pieces;
  enum type **black_capt_pieces;
} game_t;

#endif
