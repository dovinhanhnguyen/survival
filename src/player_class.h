#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <cstdlib>
using namespace std;

enum player_status { NOT_PLAYING = 0, BUILDING = 1, EATING = 2, SLEEPING = 3 };

class player {
  public:
    long boat, stamina, sanity, time_left;
    bool alive, escaped;
    player_status status;
    
    player();
    ~player();
    void update (void);
  private:
};

#endif
