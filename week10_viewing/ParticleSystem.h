#pragma once
#include "DataStructure/Vector3D.h"

typedef Vector3D<float> TV;

class Particle
{
public:
	Vector3D<float> pos, vel;
	float mass = 1.0f;
	TV center;
	float radius = 0.10;
};

class Sphere {
public:
	TV center;
	float radius;

	float getSignedDistance(const TV& pos) {
		return (pos - center).getMagnitude() - radius;
	}

	TV getNormal(const TV& pos) {
		return (pos - center).getNormalized();
	}
};

class ParticleSystem
{
public:
	std::vector<Particle> particles;
	Sphere obj;
	
	void initParticleSystem()
	{
		obj.center = TV(0.0,0.0,0.0);
		obj.radius = 1.0;

		const int num_particles = 50;
		particles.resize(num_particles);

		for (int p = 0; p < particles.size(); ++p)
		{
			TV& pos(particles[p].pos);
			TV& vel(particles[p].vel);
			float& m = particles[p].mass;

			pos.x_ = ((float)rand() / (float)RAND_MAX) * 10 - ((float)rand() / (float)RAND_MAX) * 10; // [0,1)
			pos.y_ = ((float)rand() / (float)RAND_MAX) * 10 - ((float)rand() / (float)RAND_MAX) * 8;
			pos.z_ = ((float)rand() / (float)RAND_MAX) * 2 - 7.5;// [0,1)

			m = 10;//[0,1)    질량

			vel = TV(0.0,0.0,-0.7);
		}
	}

	void advanceOneTimeStep(const float& dt)
	{
		const TV g = TV(0.0, 0.0, 9.8); //중력 -9.8로 설정

		for (int p = 0; p < particles.size(); ++p) {
			TV& pos(particles[p].pos);
			TV& vel(particles[p].vel);

			//force
			TV f = particles[p].mass * g;

			//force ->velocity v = v + v*dt
			vel += (f / particles[p].mass)*dt;

			//velocity -> position
			pos += vel * dt;
		}

		//const float coef = 0.3f;
		//ground collision
			for (int p = 0; p < particles.size(); ++p) {
				TV& pos(particles[p].pos);
				TV& vel(particles[p].vel);
				float& m = particles[p].mass;

				if (pos.z_ >= -0.5f) {
					vel.z_ = -1.0;
					pos.x_ = ((float)rand() / (float)RAND_MAX) * 10 - ((float)rand() / (float)RAND_MAX) * 10; // [0,1)
					pos.y_ = ((float)rand() / (float)RAND_MAX) * 10 - ((float)rand() / (float)RAND_MAX) * 8;
					pos.z_ = ((float)rand() / (float)RAND_MAX) * 2 - 7.5;// [0,1)

					m = 10;//[0,1)    질량

					//vel = TV(0.0, 0.0, -1.7);
				}
			}
		//		if (pos.z_ >= 1)
		//			pos.z_ -= 1;
		//		if (pos.z_ <= 0)
		//			pos.z_ += 1;
			//	const float frac = 0.0;
			//	//object collision
			//	for (int p = 0; p < particles.size(); ++p) {
			//	   TV& pos(particles[p].pos);
			//	   TV& vel(particles[p].vel);

			//	   if (obj.getSignedDistance(pos) <= 0.0f)
			//	   {
			//		  const TV normal = obj.getNormal(pos);
			//		  const T v_dot_n = dotProduct(vel, normal);

			//		  if (v_dot_n < 0.0f) {
			//			 const TV v_n = v_dot_n * normal;
			//			 const TV v_t = vel - v_n;

			//			 vel = v_t*frac + (-coef) * v_n;
			//			 //printf("충돌");
			//		  }
		//	//	   }
		//		   // object normal


		//		}

		//	}
		//}
		//}
	}

	void addParticle(TV c) {
		Particle part;
		TV& pos(part.pos);
		TV& vel(part.vel);
		float& m = part.mass;
		pos.x_ = c.x_;
		pos.y_ = c.y_ + 0.1;
		pos.z_ = c.z_ - 0.5;

		m = (float)rand() / (float)RAND_MAX * 10; // [0, 10)

		vel = TV(0.0, 0.0, -0.1);
		particles.push_back(part);
	}
};