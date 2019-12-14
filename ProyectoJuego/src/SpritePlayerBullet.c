
#include "Banks/SetBank2.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Scroll.h"

struct PlayerBulletInfo{
    INT8 vx;
};
UINT8 bulletX = 0;
void Start_SpritePlayerBullet(){
    struct PlayerBulletInfo *data= (struct PlayerBulletInfo *)THIS->custom_data;
    data->vx= bulletX;
}
void Update_SpritePlayerBullet(){
    struct PlayerBulletInfo *data = (struct PlayerBulletInfo *)THIS->custom_data;
    THIS->x += data->vx << delta_time;
}
void Destroy_SpritePlayerBullet(){
    bulletcount--;
}