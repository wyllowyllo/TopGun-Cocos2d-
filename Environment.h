#pragma once
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#define DEBUG_MODE true

#define PLAYER_MOVEMENT_SPEED 400
#define ENEMY_BULLET_SPEED 500

/*충돌 판정을 위한 bit mask 설정*/
// 011(2)
#define PLAYER_MASK 0x00000003

// 110(2)
#define ENEMY_MASK 0x00000006

//100(2)
#define PLAYER_BULLET_MASK 0x00000004

//001(2)
#define ENEMY_BULLET_MASK 0x00000001


//구분을 위한 tag지정
#define TAG_PLAYER 1
#define TAG_ENEMY 2
#define TAG_PLAYER_BULLET 3
#define TAG_ENEMY_BULLET 4
#endif