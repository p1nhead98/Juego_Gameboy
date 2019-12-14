#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
STATE_DEF_END


#define SPRITES \
_SPRITE_DMG(SpritePlayer, player)\
_SPRITE_DMG(SpritePlayerBullet, bullet)\
_SPRITE_DMG(SpriteEyeBat,eyebat)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"
extern UINT16 playerX;
extern UINT16 playerY;
extern UINT8 bulletX;
extern UINT8 bulletcount;
#endif