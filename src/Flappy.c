#include "Flappy.h"
#include <stdlib.h>

void draw_pillar(Canvas *canvas, Pillar* pillar){

    for (int y =0 ; y < canvas->height-7; y++) {
        for (int x =0 ; x < pillar->width; x++) {
            if((y < pillar->end) || y > pillar->start){
                if(x == 0 || x == pillar->width-1)
                    setPixel(canvas, pillar->x+x, y, "# ",BLACK,BG_GREEN);
                else
                setPixel(canvas, pillar->x+x, y, BG,GREEN,BG_GREEN);
            }
        }
    }
}


void move_pillars(Pillar *pillar, int width, int height){
    if(pillar->x+pillar->width <= 0 ){
        pillar->x = (width*1.5)-pillar->width;

        int min = pillar->gap;
        int start = rand() % ((height*5)/6-min + 1 - min) + min;
        pillar->start = start;
        pillar->end = start-pillar->gap;

    }
    pillar->x-= 1;
}

int is_colliding(Bird* bird, Pillar pillar){
    return ((bird->x >= pillar.x && bird->x <= (pillar.x+pillar.width))
        && (bird->y < pillar.end || bird->y > pillar.start));
}
