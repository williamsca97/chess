#ifndef CHESS_H
#define CHESS_H

#include <stdint.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef enum type {KING, QUEEN, KNIGHT, ROOK, BISHOP, PAWN} type;
typedef enum color {WHITE, BLACK} color;

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
