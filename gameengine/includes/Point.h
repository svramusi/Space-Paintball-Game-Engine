#ifndef POINT_H
#define POINT_H

typedef struct point_t {
	int x;
	int y;
	int z;
} Point;

typedef struct force_t{
	float x;
	float y;
	float z;
} Force;

typedef struct velocity_t{
	float x;
	float y;
	float z;
} Velocity ;
#endif
