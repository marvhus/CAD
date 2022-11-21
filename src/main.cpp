#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "CAD.hpp"

int main()
{
	CAD instance;
	if (instance.Construct(1280, 720, 1, 1))
	    instance.Start();

	return 0;
}
