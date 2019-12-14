#include "Banks/SetBank2.h"
#include "Math.h"
#include "ZGBMain.h"
#include "SpriteManager.h"

const UINT8 eye_bat_flying[] = {2,0,1};

UINT8 bat_movement;
UINT8 bat_move;
UINT8 up_down = 0;
UINT8 bat_count = 0;

void Start_SpriteEyeBat(){
    bat_movement = 1;
    bat_move = 0;
    up_down = 1;
    SetSpriteAnim(THIS, eye_bat_flying, 9);
}
void Update_SpriteEyeBat(){
    if(THIS->x - playerX < 100){
        bat_move = 1;
    }
    if(bat_move == 1){
        if(bat_count == 39){
            bat_count = 0;
            if(up_down == 1){
                up_down = 2;
            }else{
                up_down = 1;
            }
        }
        if(up_down == 1){
            if(bat_count < 39){
                if(bat_count < 12){
                    THIS->x--;
                }else{
                    THIS->x--;
                    THIS->y -= bat_movement;
                }
                bat_count++;
            }
        }else if (up_down == 2){
            if(bat_count < 39){
                if (bat_count < 12){
                    THIS->x -= bat_movement;
                }else{
                    THIS->x--;
                    THIS->y += bat_movement;
                }
                bat_count++;
            }
        }
    }
}
void Destroy_SpriteEyeBat(){

}