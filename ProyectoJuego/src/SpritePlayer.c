
#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"

const UINT8 anim_run[]= {4,2,3,4,3};
const UINT8 anim_idle[]={2,0,1};
const UINT8 anim_jump[]= {1,6};
const UINT8 anim_shoot[] = {1,5};


typedef enum{
    PLAYER_STATE_IDLE,
    PLAYER_STATE_NORMAL,
    PLAYER_STATE_JUMPING
}PLAYER_STATE;

PLAYER_STATE player_state;
INT16 player_accel_y;

struct Sprite* sprite_player = 0;
struct Sprite* player_parent = 0;

UINT16 player_old_x, player_old_y;
UINT8 bg_hidden = 0;
UINT8 moving = 0;
UINT16 playerX,playerY;
BOOLEAN shooting;
UINT8 bulletcount;
UINT8 shootFrameCount;
UINT8 tile_collision;




void Start_SpritePlayer() {
    player_accel_y = 0;

    scroll_target = THIS;
    sprite_player = THIS;
    bg_hidden = 0;
    bulletcount=0;
    shooting= FALSE;

}

void CheckCollisionTile(){
    switch(tile_collision){
        case 25u:

        break;
    }
}

//Metodo para definir los movimientos del personaje
void MovePlayer(){
    if(KEY_PRESSED(J_LEFT)){
        tile_collision =TranslateSprite(THIS, -1<<delta_time,0);
        SPRITE_SET_VMIRROR(THIS);
        if(player_state != PLAYER_STATE_JUMPING){
            SetSpriteAnim(THIS, anim_run, 9);
        }
    }
    if(KEY_PRESSED(J_RIGHT)){
        tile_collision = TranslateSprite(THIS, 1 << delta_time,0);
        THIS->flags = 0u;
        if(player_state != PLAYER_STATE_JUMPING){
            SetSpriteAnim(THIS, anim_run, 9);
        }
    }
}

//Metodo para el salto del personaje
void PlayerJump(){
    if(player_state != PLAYER_STATE_JUMPING){
        SetSpriteAnim(THIS, anim_jump, 9);
        player_accel_y = -40;
        player_state = PLAYER_STATE_JUMPING;
        player_parent = 0;
    }
}

void Update_SpritePlayer(){
    playerX = THIS->x;
    playerY = THIS->y;

    switch(player_state){
        case PLAYER_STATE_IDLE:
           SetSpriteAnim(THIS, anim_idle, 2);
            
        case PLAYER_STATE_NORMAL:
        MovePlayer();
        if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT)){
            player_state = PLAYER_STATE_NORMAL;
        }else{
            player_state = PLAYER_STATE_IDLE;
        }

        if(KEY_TICKED(J_A)){
            PlayerJump();
        }

        break;

        case PLAYER_STATE_JUMPING:
            if((player_accel_y<0) && !KEY_PRESSED(J_A)){
                player_accel_y = 0;
            }
            MovePlayer();
            break;

    }

    //GRAVEDAD
    if(player_parent == 0){
        if(player_accel_y < 60){
            player_accel_y +=2;
        }
        tile_collision = TranslateSprite(THIS, 0, (player_accel_y >> 4));
        if(!tile_collision && delta_time != 0 && player_accel_y < 40){
            player_accel_y +=2;
            tile_collision = TranslateSprite(THIS, 0, (player_accel_y >> 4));

        }
        if(tile_collision){
            if(tile_collision != 3u && tile_collision != 4u){
                player_accel_y = 0;
                if(player_state == PLAYER_STATE_JUMPING){
                    player_state = PLAYER_STATE_NORMAL;
                }
            }
            CheckCollisionTile();
        }
    }
    if(player_parent && player_state == PLAYER_STATE_JUMPING){
        player_accel_y = 0;
        player_state = PLAYER_STATE_NORMAL;
    }


    if(KEY_TICKED(J_B)){
        shooting = TRUE;
        if(!KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && player_state == PLAYER_STATE_IDLE ){
            //AQUI VA LA ANIMACION DE DISPARAR
            SetSpriteAnim(THIS,anim_shoot,2);
        }
    }else if(shooting){
        shooting = FALSE;
    }

    if(shooting){
        if(shootFrameCount % 20 == 0){
            if(bulletcount < 70){
                if(SPRITE_GET_VMIRROR(THIS)){
                    bulletX=-4;
                    SpriteManagerAdd(SpritePlayerBullet,playerX - 5u,playerY +13u);
                }else{
                    bulletX=4;
                    SpriteManagerAdd(SpritePlayerBullet, playerX+7u,playerY+13u
                    );
                }
                bulletcount++;
            }
        }
        shootFrameCount++;
    }else if(shootFrameCount % 20 > 0){
        shootFrameCount++;
        if(shootFrameCount % 20 == 0){
            shootFrameCount = 0;
        }
    }
    if(shootFrameCount == 100){
        shootFrameCount = 0;
    }

}

void Destroy_SpritePlayer(){
    sprite_player = 0;
}
