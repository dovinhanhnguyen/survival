#include "player_class.h"

player::player() {
  boat = 0;
  stamina = 80;
  sanity = 80;
  time_left = 30;
  status = NOT_PLAYING;
  alive = true;
  escaped = false;
}

player::~player() {}

void player::update (void) {
  switch (status) {
    case NOT_PLAYING:
      break;
    case BUILDING:
      time_left --;
      if ((boat + int(10*(stamina/100.0 + sanity/100.0)/2.0))<=100) boat += int(10*(stamina/100.0 + sanity/100.0)/2.0);
      else if ((boat + int(10*(stamina/100.0 + sanity/100.0)/2.0))>100) boat = 100;
      stamina -= 10;
      sanity -= 5;
      if (sanity == 0) stamina -= 10;
      break;
    case EATING:
      time_left --;
      if ((stamina + int(10 * (sanity/100.0)))<=100) (stamina += int(10 * (sanity/100.0)));
      else if ((stamina + int(10 * (sanity/100.0)))>100) stamina = 100;
      break;
    case SLEEPING:
      time_left --;
      stamina -= 2;
      if ((sanity + int(10*stamina/100.0))<=100) (sanity += int(10*stamina/100.0));
      else if ((sanity + int(10*stamina/100.0))>100) sanity = 100;
      break;
  }
  alive = (stamina>=0) && (time_left>=0) && (sanity>=0);
  escaped = (boat>=100) && alive;
}
