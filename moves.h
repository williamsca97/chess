#ifndef MOVES_H
#define MOVES_H

#include <stdint.h>
#include "chess.h"

typedef struct move_t {
  uint8_t valid;
  uint8_t dest_rank;
  uint8_t dest_file;
  uint8_t has_capture;
  uint8_t capture_rank;
  uint8_t capture_file;
  uint8_t double_pawn;
  uint8_t en_passant;
} move_t;

move_t *****get_all_valid_moves(game_t *this_game);

#endif
