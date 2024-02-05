#include "printer.h"
#include <stdio.h>
#include "./Flappy.h"
#include <string.h>

#define WIDTH 30
#define HEIGHT 30

// TODO
// make pillors move faster
// Start screen and die screen
// animate background


void draw_background(Canvas* canvas){
    for (int y = 0 ; y < canvas->height; y++) {
        for (int x = 0; x < canvas->width; x++) {
            setPixel(canvas,x,y,"# ",YELLOW,BG_YELLOW);
            if(y < (canvas->height*5)/6){
                setPixel(canvas,x,y,"  ",BLACK,BG_GREEN);
            }
            if(y < (canvas->height*2)/3){
                setPixel(canvas,x,y,"# ",WHITE,BG_BLUE);
            }
            if(y < canvas->height/3 ){
                setPixel(canvas,x,y,BG,BLUE,BG_RED);
            }
        }
    }
}

void draw_bird(Canvas *canvas, Bird *bird){
    //fals fornd
    if(bird->gravity > 0){
        setPixel(canvas,bird->x,    bird->y,BG,RED,BG_BLUE);
        setPixel(canvas,bird->x-1  ,bird->y,BG,YELLOW,BG_BLUE);
        setPixel(canvas,bird->x  ,bird->y-1,BG,YELLOW,BG_BLUE);
        setPixel(canvas,bird->x-1,bird->y-1,BG,YELLOW,BG_BLUE);
        setPixel(canvas,bird->x-2,bird->y-1,BG,YELLOW,BG_BLUE);
    }
    else if(bird->gravity < 0){
        setPixel(canvas,bird->x,    bird->y,BG,RED,BG_BLUE);
        setPixel(canvas,bird->x-1  ,bird->y,BG,YELLOW,BG_BLUE);
        setPixel(canvas,bird->x  ,bird->y+1,BG,YELLOW,BG_BLUE);
        setPixel(canvas,bird->x-1,bird->y+1,BG,YELLOW,BG_BLUE);
        setPixel(canvas,bird->x-2,bird->y+1,BG,YELLOW,BG_BLUE);
    }
    else{
        setPixel(canvas,bird->x,    bird->y,BG,RED,BG_BLUE);
        setPixel(canvas,bird->x-1  ,bird->y,BG,YELLOW,BG_BLUE);
        setPixel(canvas,bird->x-2  ,bird->y,BG,YELLOW,BG_BLUE);
        setPixel(canvas,bird->x-1,bird->y-1,BG,YELLOW,BG_BLUE);
    }
}

void play(){
    int score = 0;
    int high_score = 0;
    Canvas *canvas = newCanvas(WIDTH, HEIGHT, "  ", BLACK, BG_BLUE);

    Bird b;
    b.x = 5;
    b.y = canvas->height/2;
    b.near_x = 100;
    b.near_y = 5;
    b.gravity = 0;

    Pillar pillar1;
    pillar1.x = canvas->width;
    pillar1.gap = 5;
    pillar1.width = canvas->width/10;
    pillar1.end = 5;
    pillar1.start = 10;

    Pillar pillar2;
    pillar2.x = canvas->width*1.5;
    pillar2.gap = 5;
    pillar2.width = canvas->width/10;
    pillar2.end = 5;
    pillar2.start = 10;

    Pillar pillars[2];
    int pillars_length = 2;
    pillars[0] = pillar1;
    pillars[1] = pillar2;

    while(1){
        draw_background(canvas);
        char ch = getKeyPressed();
        if(ch == ' '){
            b.gravity = -1.5;
        }
        if(ch == 'q'){
            freeCanvas(canvas);
            return;
        }


        b.gravity+= 0.5f;
        b.y += b.gravity;

        Pillar *nearest = &pillars[0];
        for(int i = 0; i < pillars_length; i ++){
            if(pillars[i].x == b.x){
                score++;
                //puts("ASDASD");
            }
            if(nearest->x > pillars[i].x) nearest = &pillars[i];

            move_pillars(&pillars[i],canvas->width,canvas->height);
            draw_pillar(canvas, &pillars[i]);

            if(is_colliding(&b, pillars[i])){
                high_score = (score > high_score) ? score : high_score;
                score = 0;

                //reset game
                b.x = 5;
                b.y = canvas->height/2;

                for (int i = 0; i < pillars_length; i++) {
                    pillars[i].x = pillars[i].x + canvas->width;
                }

            }

        }

        b.near_x = nearest->x - b.x;
        b.near_y =  nearest->end+nearest->gap/2 - b.y;

        //draw bird
        draw_bird(canvas,&b);

        setPixel(canvas,b.near_x+b.x,b.near_y+b.y, BG, BLACK,BG_BLACK);


        draw_pillar(canvas,&pillars[0]);


        char score_str[20];
        sprintf(score_str,"HIGHSCORE IS %d", high_score);
        setCenterText(canvas,canvas->width/2,0,score_str,BLACK,BG_BLUE);

        sprintf(score_str,"SCORE IS %d", score);
        setCenterText(canvas,canvas->width/2,1,score_str,BLACK,BG_BLUE);

        draw(canvas);
        clearPixels(canvas);

        msleep(70);
    }

    freeCanvas(canvas);
    canvas=NULL;
}

int main(){
    int loop = 1;
    play();
    return 0;
}
