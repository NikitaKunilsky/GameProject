#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include "map.h"

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