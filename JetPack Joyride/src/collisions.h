#include "main.h"
#include "semi.h"
#ifndef COLLISIONS_H
#define COLLISIONS_H

void detect_coll_coins(Player* player,Coins* coin);
void detect_coll_specialObj(Player* player, SpecialObj* special_obj);
void detect_coll_boomerang(Player* player, Boomerang* boom);
void detect_coll_fireEnemies(Player* player, FireEnemies* fire_ene);
void detect_coll_water_line(SpecialObj* water_drop, FireEnemies* fire_ene);
void detect_coll_boomerang(Player* player, Boomerang* boom);
#endif