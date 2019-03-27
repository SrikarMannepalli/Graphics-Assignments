#include "main.h"
#include "plane.h"
#include "checkpoints.h"
#include "powerups.h"
#include "bomb.h"
#include "missile.h"
#include "para.h"
#include "arrow.h"
#include "enemies.h"
#include "smokering.h"

extern int score;

int detect_coll(bounding_box_t* box1, bounding_box_t* box2) {
    if(box1->width+box2->width >= abs(box1->x - box2->x) && 
        box1->height+box2->height >= abs(box1->y - box2->y) &&
        box1->depth+box2->depth >= abs(box1->z - box2->z)) {
            return 1;
    }
    return 0;
}


int detect_coll2(bounding_box_t* box1, bounding_box_t* box2) {
    if(box1->width+box2->width >= abs(box1->x - box2->x) && 
        box1->depth+box2->depth >= abs(box1->z - box2->z)) {
            return 1;
    }
    return 0;
}

void detect_coll_powerups_plane(Plane* plane, Powerups* pow) {
    bounding_box_t box1;
    bounding_box_t box2;
    bounding_box_t box3;
    bounding_box_t box4;
    box1.width = 0.5*plane->width1;
    box1.height = 0.5*plane->height1;
    box1.depth = 0.5*plane->depth1;
    box1.x = box2.x = plane->position.x;
    box1.y = box2.y = plane->position.y;
    box1.z = box2.z = plane->position.z;
    box2.width = 0.5*plane->width2;
    box2.height = 0.5*plane->height2;
    box2.depth = 0.5*plane->depth2;
    box3.width = pow->width;
    box3.height = pow->height;
    box3.depth = pow->depth;
    box3.x = pow->position.x;
    box3.y = pow->position.y;
    box3.z = pow->position.z;
    box4.width = 0.5*plane->width1;
    box4.height = 0.5*plane->height1;
    box4.depth = 0.15;
    box4.x = plane->position.x;
    box4.y = plane->position.y;
    box4.z = plane->position.z-0.5*plane->depth1-0.15;
    int coll1 = detect_coll(&box1,&box3);
    int coll2 = detect_coll(&box2,&box3);
    int coll3 = detect_coll(&box4,&box3);
    if(coll1 || coll2 || coll3) {
        pow->destroyed = true;
        if(pow->type == 0) {
            if(plane->health+20>100) plane->health=100;
            else plane->health+=20; 
        }
        else {
            if(plane->fuel+20>10000) plane->fuel = 10000;
            else plane->fuel+=20;
        }
    }
}


void detect_coll_enebull_plane(Plane* plane, Missile* enebull) {
    bounding_box_t box1;
    bounding_box_t box2;
    bounding_box_t box3;
    bounding_box_t box4;
    box1.width = 0.5*plane->width1;
    box1.height = 0.5*plane->height1;
    box1.depth = 0.5*plane->depth1;
    box1.x = box2.x = plane->position.x;
    box1.y = box2.y = plane->position.y;
    box1.z = box2.z = plane->position.z;
    box2.width = 0.5*plane->width2;
    box2.height = 0.5*plane->height2;
    box2.depth = 0.5*plane->depth2;
    box3.width = enebull->width;
    box3.height = enebull->height;
    box3.depth = enebull->depth;
    box3.x = enebull->position.x;
    box3.y = enebull->position.y;
    box3.z = enebull->position.z;
    box4.width = 0.5*plane->width1;
    box4.height = 0.5*plane->height1;
    box4.depth = 0.15;
    box4.x = plane->position.x;
    box4.y = plane->position.y;
    box4.z = plane->position.z-0.5*plane->depth1-0.15;
    int coll1 = detect_coll(&box1,&box3);
    int coll2 = detect_coll(&box2,&box3);
    int coll3 = detect_coll(&box4,&box3);
    if(coll1 || coll2 || coll3) {
            enebull->destroyed = true;
            plane->health -=5;
    }
}

void detect_coll_enemy_missile(Enemies* enemy, Missile* missile, Arrow* arrow) {
    bounding_box_t box1;
    bounding_box_t box2;
    box1.width = enemy->width;
    box1.height = enemy->height;
    box1.depth = enemy->depth;
    box1.x = enemy->position.x;
    box1.y = enemy->position.y;
    box1.z = enemy->position.z;
    box2.width = missile->width;
    box2.height = missile->height;
    box2.depth = missile->depth;
    box2.x = missile->position.x;
    box2.y = missile->position.y;
    box2.z = missile->position.z;

    int coll = detect_coll(&box1,&box2);
    if(coll) {
        enemy->destroyed = missile->destroyed = arrow->destroyed = true;
    } 
}

void detect_coll_enemy_bomb(Enemies* enemy, Bomb* bomb, Arrow* arrow) {
    bounding_box_t box1;
    bounding_box_t box2;
    box1.width = enemy->width;
    box1.height = enemy->height;
    box1.depth = enemy->depth;
    box1.x = enemy->position.x;
    box1.y = enemy->position.y;
    box1.z = enemy->position.z;
    box2.width = bomb->width;
    box2.height = bomb->height;
    box2.depth = bomb->depth;
    box2.x = bomb->position.x;
    box2.y = bomb->position.y;
    box2.z = bomb->position.z;

    int coll = detect_coll(&box1,&box2);
    if(coll) {
        enemy->destroyed = bomb->destroyed = arrow->destroyed = true;
    } 
}

void detect_coll_plane_vol(Plane* plane, Checkpoint* volcano) {
    bounding_box_t box1;
    bounding_box_t box2;
    bounding_box_t box3;
    bounding_box_t box4;
    box1.width = 0.5*plane->width1;
    box1.height = 0.5*plane->height1;
    box1.depth = 0.5*plane->depth1;
    box1.x = box2.x = plane->position.x;
    box1.y = box2.y = plane->position.y;
    box1.z = box2.z = plane->position.z;
    box2.width = 0.5*plane->width2;
    box2.height = 0.5*plane->height2;
    box2.depth = 0.5*plane->depth2;
    box3.width = volcano->width_check;
    box3.height = volcano->height_check;
    box3.depth = volcano->depth_check;
    box3.x = volcano->position.x;
    box3.y = volcano->position.y;
    box3.z = volcano->position.z;
    box4.width = 0.5*plane->width1;
    box4.height = 0.5*plane->height1;
    box4.depth = 0.15;
    box4.x = plane->position.x;
    box4.y = plane->position.y;
    box4.z = plane->position.z-0.5*plane->depth1-0.15;
    int coll1 = detect_coll2(&box1,&box3);
    int coll2 = detect_coll2(&box2,&box3);
    int coll3 = detect_coll2(&box4,&box3);
    if(coll1 || coll2 || coll3) {
        
            if(plane->health-10>0) plane->health -=1.0;
            else plane->health = 0;
            volcano->blinkmode = true;
    }
    else volcano->blinkmode = false;
}


void detect_coll_paras_missile(Para* para, Missile* missile) {
    bounding_box_t box1;
    bounding_box_t box2;
    bounding_box_t box3;
    box1.width = 0.3f;
    box1.height = 0.5*0.3f;
    box1.depth = 0.3f;
    box1.x = para->position.x;
    box1.y = para->position.y+0.5*0.3;
    box1.z = para->position.z;
    box3.width = 0.1;
    box3.height = 0.5*0.35;
    box3.depth = 0.1f;
    box3.x = para->position.x;
    box3.y = para->position.y-0.5*0.35;
    box3.z = para->position.z;

    box2.width = missile->width;
    box2.height = missile->height;
    box2.depth = missile->depth;
    box2.x = missile->position.x;
    box2.y = missile->position.y;
    box2.z = missile->position.z;
    int coll1 = detect_coll(&box1,&box2);
    int coll2 = detect_coll(&box3,&box2);
    if(coll1 || coll2) {
        missile->destroyed = true;
        para->destroyed = true;
        score+=100;
    }

}

void detect_coll_paras_bomb(Para* para, Bomb* bomb) {
    bounding_box_t box1;
    bounding_box_t box2;
    bounding_box_t box3;
    box1.width = 0.3f;
    box1.height = 0.5*0.3f;
    box1.depth = 0.3f;
    box1.x = para->position.x;
    box1.y = para->position.y+0.5*0.3;
    box1.z = para->position.z;
    box3.width = 0.1;
    box3.height = 0.5*0.35;
    box3.depth = 0.1f;
    box3.x = para->position.x;
    box3.y = para->position.y-0.5*0.35;
    box3.z = para->position.z;

    box2.width = bomb->width;
    box2.height = bomb->height;
    box2.depth = bomb->depth;
    box2.x = bomb->position.x;
    box2.y = bomb->position.y;
    box2.z = bomb->position.z;
    int coll1 = detect_coll(&box1,&box2);
    int coll2 = detect_coll(&box3,&box2);
    if(coll1 || coll2) {
        para->destroyed = true;
        bomb->destroyed = true;
        score+=100;
    }

}

void detect_coll_para_plane(Plane* plane,Para*para) {
    bounding_box_t box1;
    bounding_box_t box2;
    bounding_box_t box3;
    bounding_box_t box4;
    bounding_box_t box5;
    box1.width = 0.3f;
    box1.height = 0.5*0.3f;
    box1.depth = 0.3f;
    box1.x = para->position.x;
    box1.y = para->position.y+0.5*0.3;
    box1.z = para->position.z;
    box2.width = 0.1;
    box2.height = 0.5*0.35;
    box2.depth = 0.1f;
    box2.x = para->position.x;
    box2.y = para->position.y-0.5*0.35;
    box2.z = para->position.z;


    box3.width = 0.5*plane->width1;
    box3.height = 0.5*plane->height1;
    box3.depth = 0.5*plane->depth1;
    box3.x = box4.x = plane->position.x;
    box3.y = box4.y = plane->position.y;
    box3.z = box4.z = plane->position.z;
    box4.width = 0.5*plane->width2;
    box4.height = 0.5*plane->height2;
    box4.depth = 0.5*plane->depth2;


    box5.width = 0.5*plane->width1;
    box5.height = 0.5*plane->height1;
    box5.depth = 0.15;
    box5.x = plane->position.x;
    box5.y = plane->position.y;
    box5.z = plane->position.z-0.5*plane->depth1-0.15;

    
    int coll1 = detect_coll(&box1,&box3);
    int coll2 = detect_coll(&box1,&box4);
    int coll5 = detect_coll(&box1,&box5);
    int coll3 = detect_coll(&box2,&box3);
    int coll4 = detect_coll(&box2,&box4);
    int coll6 = detect_coll(&box2,&box5);
    if(coll1 || coll2 || coll3 || coll4 || coll5 || coll6) {
        if(plane->health-10>0) plane->health -=10.0;
        else plane->health = 0;
        para->destroyed = true;
    }
}

void detect_coll_plane_smokering(Plane* plane,Smokering* smokering) {
    bounding_box_t box1;
    bounding_box_t box2;
    bounding_box_t box3;
    bounding_box_t box4;
    box1.width = 0.5*plane->width1;
    box1.height = 0.5*plane->height1;
    box1.depth = 0.5*plane->depth1;
    box1.x = box2.x = plane->position.x;
    box1.y = box2.y = plane->position.y;
    box1.z = box2.z = plane->position.z;
    box2.width = 0.5*plane->width2;
    box2.height = 0.5*plane->height2;
    box2.depth = 0.5*plane->depth2;

    box4.width = 0.5*plane->width1;
    box4.height = 0.5*plane->height1;
    box4.depth = 0.15;
    box4.x = plane->position.x;
    box4.y = plane->position.y;
    box4.z = plane->position.z-0.5*plane->depth1-0.15;
    if((plane->position.z+0.5*plane->depth1-smokering->position.z)*(plane->position.z-0.5*plane->depth1-smokering->position.z)<0) {  
        if(smokering->position.x+smokering->rBig<=plane->position.x+0.5*plane->width2 || 
            smokering->position.x-smokering->rBig>=plane->position.x-0.5*plane->width2)
            {
                plane->health -= 0.5f;
        }
        else {
            score+=100.0f;
            smokering->checked = 1;
        }
    }
}