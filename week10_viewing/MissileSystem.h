#pragma once
#include "DataStructure/Vector3D.h"
#include <vector>

typedef Vector3D<float> TV;

class Missile
{
public:
	Vector3D<float> pos, vel;
	float mass = 1.0f;
	TV center;
	float radius = 0.10;
};

class MissileSystem
{
public:
	std::vector<Missile> missiles;
	void initParticleSystem()
	{
		const int num_particles = 1;
		missiles.resize(num_particles);

		for (int p = 0; p < missiles.size(); ++p)
		{
			TV& pos(missiles[p].pos);
			TV& vel(missiles[p].vel);
			float& m = missiles[p].mass;

			//pos.x_ = ((float)rand() / (float)RAND_MAX) * 10 - ((float)rand() / (float)RAND_MAX) * 10; // [0,1)
			//pos.y_ = (float)rand() / (float)RAND_MAX;// [0,1)
			//pos.z_ = (float)rand() / (float)RAND_MAX - 10.0;// [0,1)

			pos.x_ = 0.0;
			pos.y_ = -100.0;
			pos.z_ = -10.0;

			m = 10;//[0,1)    질량

			vel = TV(0.0, 0.0, -0.7);
		}
	}

	void advanceOneTimeStep(const float& dt)
	{
		const TV g = TV(0.0, 0.0, -9.8); //중력 -9.8로 설정

		for (int p = 0; p < missiles.size(); ++p) {
			TV& pos(missiles[p].pos);
			TV& vel(missiles[p].vel);

			//force
			TV f = missiles[p].mass * g;

			//force ->velocity v = v + v*dt
			vel += (f / missiles[p].mass)*dt;

			//velocity -> position
			pos += vel * dt;
		}
	}

	void addParticle(TV c) {
		Missile part;
		TV& pos(part.pos);
		TV& vel(part.vel);
		float& m = part.mass;
		pos.x_ = c.x_;
		pos.y_ = c.y_ + 0.3;
		pos.z_ = c.z_ - 0.5;

		m = (float)rand() / (float)RAND_MAX * 10; // [0, 10)

		vel = TV(0.0, 0.0, -1.0);
		missiles.push_back(part);

	}
};