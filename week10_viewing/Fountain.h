#pragma once
#include "DataStructure/Vector3D.h"
#include <vector>

typedef Vector3D<float> TV;

class Fountain
{
public:
	Vector3D<float> pos;
	Vector3D<float> vel;
	float mass = 1.0;
	TV center;
	float radius = 0.1;
};

class FountainSystem
{
public:
	std::vector<Fountain> fountain;

	void initParticleSystem()
	{
		const int num_particles = 1000;
		fountain.resize(num_particles);

		float pi = 3.14;

		for (int p = 0; p < fountain.size(); ++p)
		{
			TV& pos(fountain[p].pos);
			TV& vel(fountain[p].vel);
			float& m = fountain[p].mass;

			pos.x_ = -3.0;
			pos.y_ = 2.0;
			pos.z_ = -3.0;

			float theta = 2 * pi * ((float)rand() / (float)RAND_MAX);
			float x = 2.0 * cos(theta);
			float z = 2.0 * sin(theta);

			vel = TV(x, 1.5f, z);
		}
	}

	void advanceOneTimeStep(const float& dt)
	{

		const TV g = TV(0.0, -9.8, 0.0);
		int randome = rand() % fountain.size();

		for (int p = 0; p < fountain.size(); ++p)
		{
			if (fountain[randome].pos.x_ && 0 || fountain[randome].pos.y_ == 0 && fountain[randome].pos.z_ == 0)
			{
				fountain[randome].vel += g * dt;
				fountain[randome].pos += fountain[randome].vel * dt;
			}
		}

		for (int p = 0; p < fountain.size(); ++p)
		{
			if (fountain[p].pos.x_ != 0 && fountain[p].pos.y_ != 0 && fountain[p].pos.z_ != 0)
			{
				fountain[p].vel += g * dt;
				fountain[p].pos += fountain[p].vel * dt;
			}
		}

		// ground collision
		for (int p = 0; p < fountain.size(); ++p)
		{
			if (fountain[p].pos.y_ < 0.0f)
			{
				fountain[p].vel.y_ = 0.0;

			}
		}
	}
};