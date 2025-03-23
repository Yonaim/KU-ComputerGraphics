#ifndef HITRESULT_HPP
#define HITRESULT_HPP

class Surface;

typedef struct
{
	Surface *surface;
	float    t;
} hitResult;

#endif
