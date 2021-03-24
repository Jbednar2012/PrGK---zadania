#pragma once

struct Point3D {
	float x;
	float y;
	float z;
};

struct particleVector {
	Point3D currentPosition;
	Point3D newPosition;
};

struct Particle {
	particleVector vector;
	float alpha;
};