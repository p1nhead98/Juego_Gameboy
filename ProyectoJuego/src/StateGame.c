#include "Banks/SetBank2.h"

#include "..\res\src\tiles.h"
#include "..\res\src\map.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

UINT8 collision_tiles[] = {1,0};

void Start_StateGame() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	SpriteManagerAdd(SpriteEyeBat, 160,120);
	InitScrollTiles(0, &tiles);
	InitScroll(&map, collision_tiles, 0);
	SHOW_BKG;
}

void Update_StateGame() {
}