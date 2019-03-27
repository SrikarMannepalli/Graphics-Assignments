#include "main.h"
#include "powerups.h"
#include "obstacles.h"
#include "player.h"
#include "collisions.h"
#include "semi.h"

extern float min_height;
extern float leftmost;
extern float rightmost;
int here = 0;
extern bool inSemi;

extern glm::mat4 VP;
void detect_coll_coins(Player* player, Coins* coin) {
	if((abs(player->position.x + player->width*0.5- coin->position.x) * 2 < (player->width + 2*coin->radius)) && (abs(player->position.y+player->height*0.5 - coin->position.y) * 2 < (player->height + 2*coin->radius))){
		player->score += coin->score;
		system("aplay ../src/mb_coin.wav &");
		coin->destroyed = true;
	}
}

void detect_coll_specialObj(Player* player, SpecialObj* special_obj) {
	if(!inSemi){
	if((abs(player->position.x + player->width*0.5- special_obj->position.x) * 2 < (player->width + 2*special_obj->radius)) && (abs(player->position.y+player->height*0.5 - special_obj->position.y) * 2 < (player->height + 2*special_obj->radius))){
		if(special_obj->ice_ball) {
			if(player->health!=0) {
				player->health -=20;
				player->position.y = min_height;
			}
			else {
				player->health = 100;
				player->lives -= 1;
				player->position.x = leftmost;
				player->position.y = min_height;
			}
			special_obj->destroyed = true;
		}
		else if(special_obj->speedup) {
			player->velocity+=0.04f;
			special_obj->destroyed = true;
		}
		else if(special_obj->more_coins) {
			player->lives +=1;
			special_obj->destroyed = true;
		}

	}
	}
}

void detect_coll_fireEnemies(Player* player, FireEnemies* fire_ene) {
	if(!inSemi) {
	float x1 = player->position.x+player->width;
	float x2 = player->position.x;
	float y1 = player->position.y;
	float y2 = player->position.y+player->height;
	float a,b;
	int check =0;
	float m = (fire_ene->position_cyl1.y - fire_ene->position_cyl2.y)/(fire_ene->position_cyl1.x-fire_ene->position_cyl2.x);
	if(!fire_ene->line_destroyed) {
		if((fire_ene->enemy_type == 0 && fire_ene->angle>0) || fire_ene->enemy_type == 1) {
			if((fire_ene->position_cyl2.x-x2 > 0) && (fire_ene->position_cyl1.x - x1 < 0) && (fire_ene->position_cyl1.y-y2<0) && (fire_ene->position_cyl2.y - y1>0)) {
				a = y1 - fire_ene->position_cyl1.y -m*(x1-fire_ene->position_cyl1.x);
				b = y2 - fire_ene->position_cyl1.y -m*(x2-fire_ene->position_cyl1.x);    
				if(a*b<=0) {
					check = 1;
				}    
			}
		}
		else if(fire_ene->enemy_type == 0 && fire_ene->angle<0) {
			if((fire_ene->position_cyl2.x-x2 > 0) && (fire_ene->position_cyl1.x - x1 < 0) && (fire_ene->position_cyl2.y-y2<0) && (fire_ene->position_cyl1.y - y1>0)) {
				a = y1 - fire_ene->position_cyl1.y -m*(x2-fire_ene->position_cyl1.x);
				b = y2 - fire_ene->position_cyl1.y -m*(x1-fire_ene->position_cyl1.x);    
				if(a*b<=0) {
					check = 1;
				}    
			} 
		}
	}      
	if((abs(player->position.x + player->width*0.5- fire_ene->position_cyl1.x) * 2 < (player->width + 2*fire_ene->radius)) && (abs(player->position.y+player->height*0.5 - fire_ene->position_cyl1.y) * 2 < (player->height + 2*fire_ene->radius))){
		check = 1;
	}
	if((abs(player->position.x + player->width*0.5- fire_ene->position_cyl2.x) * 2 < (player->width + 2*fire_ene->radius)) && (abs(player->position.y+player->height*0.5 - fire_ene->position_cyl2.y) * 2 < (player->height + 2*fire_ene->radius))){
		check = 1;
	}
	if(check) {
		if(player->health!=0) {
			player->health -=20;
			player->position.y = min_height;
		}
		else {
			player->health = 100;
			player->lives -= 1;
			// system(" mb_die.wav &");
			player->position.x = leftmost;
			player->position.y = min_height;
		}
	}
	}
}

void detect_coll_water_line(SpecialObj* water_drop, FireEnemies* fire_ene) {
if(!inSemi) {
	float x1 = water_drop->position.x;
	float y1 = water_drop->position.y;
	float m = (fire_ene->position_cyl1.y - fire_ene->position_cyl2.y)/(fire_ene->position_cyl1.x-fire_ene->position_cyl2.x);
	float a,b;	
	if((fire_ene->enemy_type == 0 && fire_ene->angle>0)) {
		if((fire_ene->position_cyl2.x-x1 > 0) && (fire_ene->position_cyl1.x - x1 < 0) && (fire_ene->position_cyl1.y-y1<0) && (fire_ene->position_cyl2.y - y1>0)) {
			a = y1 - fire_ene->position_cyl1.y -m*(x1-fire_ene->position_cyl1.x);
			if(abs(a)<=0.03) {
				system("aplay ../src/mb_touch.wav &");
				fire_ene->line_destroyed = true;
				water_drop->destroyed = true;
			}    
		}
	}
	else if(fire_ene->enemy_type == 0 && fire_ene->angle<0) {
		if((fire_ene->position_cyl2.x-x1 > 0) && (fire_ene->position_cyl1.x - x1 < 0) && (fire_ene->position_cyl2.y-y1<0) && (fire_ene->position_cyl1.y - y1>0)) {
			a = y1 - fire_ene->position_cyl1.y -m*(x1-fire_ene->position_cyl1.x);
			if(abs(a)<=0.03) {
				system("aplay ../src/mb_touch.wav &");
				fire_ene->line_destroyed = true;
				water_drop->destroyed = true;
			}    
		} 
	}
	else if((fire_ene->enemy_type==1 || fire_ene->angle==0)&& water_drop->position.x>fire_ene->position_cyl1.x && water_drop->position.x<fire_ene->position_cyl2.x) {
		a = y1 - fire_ene->position_cyl1.y;
		if(abs(a)<=0.09) {
				system("aplay ../src/mb_touch.wav &");
			fire_ene->line_destroyed = true;
			water_drop->destroyed = true;
		} 
	}
}
}

void detect_coll_boomerang(Player* player, Boomerang* boom) {
	// boom->draw(VP);
	// std::cout<<"player "<<player->position.x + player->width*0.5<<" "<<player->position.y+player->height*0.5<<std::endl;
	// std::cout<<"boom "<<boom->position.x+boom->width*0.5<<" "<<boom->position.y+boom->height*0.5<<std::endl;
	// std::cout<<"diff "<<abs(player->position.x + player->width*0.5- boom->position.x-boom->width*0.5)<<""
	if(!inSemi && (abs(player->position.x+player->width*0.5 - boom->position.x)*2 < (player->width + 2*boom->radius)) && (abs(player->position.y+player->height*0.5 - boom->position.y) * 2 < (player->height + 2*boom->radius))){
		player->health = 100;
		player->lives -= 1;
		system("aplay ../src/mb_die.wav &");
		player->position.x = leftmost;
		player->position.y = min_height;
		boom->destroyed = true;
	}
}

