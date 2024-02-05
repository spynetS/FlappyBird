
#include "printer.h"

#ifndef FLAPPY_H_
#define FLAPPY_H_

typedef struct bird{
    int x,y;
    int near_x, near_y;
    double gravity;
}Bird;

typedef struct pillar{
    double x;
    int gap,width,end,start;
}Pillar;


void set_distance_to_pillar(Bird* bird, Pillar *pillar);
void draw_pillar(Canvas *canvas, Pillar* pillar);
int is_colliding(Bird* bird, Pillar pillar);
void move_pillars(Pillar *pillar, int width, int height);

#endif // FLAPPY_H_
