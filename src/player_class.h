#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
using namespace std;

enum player_status { NOT_PLAYING = 0, BUILDING = 1, EATING = 2, SLEEPING = 3, DEAD = 4, ALIVE = 5 };

class player {
  public:
    long boat, stamina, sanity, time_left;
    player_status status;
    
    player();
    ~player();
    void update (player_status input_status);
  private:
};

#endif
