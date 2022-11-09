#pragma once
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#define DEBUG_MODE true
#define PLAYER_MOVEMENT_SPEED 400

//011(2)  //player bit(16)
#define PLAYER_MASK 0x00000003

//110(2)  //enemy bit(16)
#define ENEMY_MASK 0x00000006

//100(2) // player bullet bit(16)
#define PLAYER_BULLET_MASK 0x00000004

//001(2) / enemy bullet bit(16)
#define ENEMY_BULLET_MASK 0x00000001


// tag - distinguish Units
#define TAG_PLAYER 1
#define TAG_ENEMY 2
#define TAG_PLAYER_BULLET 3
#define TAG_ENEMY_BULLET 4

#define ENEMY_BULLET_SPEED 500

#endif