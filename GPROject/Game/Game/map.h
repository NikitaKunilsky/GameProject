#ifndef _MAP_HEADER_H_
#define _MAP_HEADER_H_

#include <SFML\Graphics.hpp>


const int HEIGHT_MAP = 12;//������ ����� �� ������
const int WIDTH_MAP = 16;//������ ����� �� ������ 

std::string TileMap[HEIGHT_MAP] = {
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

void MapTraps();

#endif