#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include "map.h"

TileMap[HEIGHT_MAP] = {
	"0000000000000000",
	"0    s   hh    0",
	"0              0",
	"0      00000fff0",
	"0      0r      0",
	"0      0r      0",
	"0f00000000000000",
	"0              0",
	"00000000000000f0",
	"0        s     0",
	"0          s s 0",
	"0000000000000000",
};

void MapTraps() {
	if (TileMap[3][14] == 'f')
		TileMap[3][14] = ' ';
	else TileMap[3][14] = 'f';
	if (TileMap[3][13] == 'f')
		TileMap[3][13] = ' ';
	else TileMap[3][13] = 'f';
	if (TileMap[3][12] == 'f')
		TileMap[3][12] = ' ';
	else TileMap[3][12] = 'f';
	if (TileMap[6][1] == 'f')
		TileMap[6][1] = ' ';
	else TileMap[6][1] = 'f';
	if (TileMap[8][14] == 'f')
		TileMap[8][14] = ' ';
	else TileMap[8][14] = 'f';
}