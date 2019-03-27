#include "main.h"
#include "plane.h"
#include "powerups.h"
#include "missile.h"
#include "enemies.h"
#include "bomb.h"
#include "arrow.h"
#include "para.h"
#include "checkpoints.h"
#include "smokering.h"

#ifndef COLLISIONS_H
#define COLLISIONS_H

// void detect_coll_powerups_plane(Plane* plane, Powerups* powerup);
// void detect_coll_enebull_plane(Plane* plane, Missile* enebull);
int detect_coll(bounding_box_t* box1, bounding_box_t* box2);
void detect_coll_powerups_plane(Plane* plane, Powerups* pow);
void detect_coll_enebull_plane(Plane* plane, Missile* enebull);
void detect_coll_enemy_missile(Enemies* enemy, Missile* missile, Arrow* arrow);
void detect_coll_enemy_bomb(Enemies* enemy, Bomb* bomb, Arrow* arrow);
void detect_coll_plane_vol(Plane* plane, Checkpoint* volcano);
void detect_coll_paras_missile(Para* para, Missile* missile);
void detect_coll_paras_bomb(Para* para, Bomb* bomb);
void detect_coll_para_plane(Plane* plane,Para*para);
void detect_coll_plane_smokering(Plane* plane,Smokering* smokering);
#endif //COLLISIONS_H