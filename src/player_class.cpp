#include "player_class.h"

player::player() {
  boat = 0;
  stamina = 100;
  sanity = 100;
  time_left = 100;
  status = NOT_PLAYING;
}

player::~player() {}

void player::update (player_status input_status) {
  switch (input_status) {
    case NOT_PLAYING:
      break;
    case BUILDING:
      break;
    case EATING:
      break;
    case SLEEPING:
      break;
    case DEAD:
      break;
    case ALIVE:
      break;
  }
}
