#pragma once
#include "cube.h"
struct eoh
{
	int _eoh[4096];
	eoh();
	int get_eoh(cube& state); 
};
