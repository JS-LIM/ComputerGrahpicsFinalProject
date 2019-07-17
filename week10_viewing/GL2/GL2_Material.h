/*
Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
for Introduction to Computer Graphics, 2017 Spring
*/

#pragma once

#include <glm/glm.hpp>

class GL2_Material
{
public:
	glm::vec4 ambient_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 diffuse_    = glm::vec4(1.0f, 0.3f, 0.3f, 1.0f);
	glm::vec4 specular_ = glm::vec4(0.2, 0.2, 0.2, 1.0);
	glm::vec4 emission_  = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	float shininess_ = 5.0;

	GL2_Material()
	{
	}

	~GL2_Material()
	{
	}

	void setRed()
	{
		ambient_ = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
		diffuse_ = glm::vec4(1.0f, 0.1f, 0.1f, 1.0f);
		specular_ = glm::vec4(0.2, 0.2, 0.2, 1.0);
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ = 5.0;
	}

	void setGold()
	{
		// http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
		ambient_ = glm::vec4(0.24725f, 0.2245f, 0.00645f, 1.0f);
		diffuse_ = glm::vec4(0.8f, 0.4f, 0.001f, 1.0f);
		specular_ = glm::vec4(0.797357f, 0.523991f, 0.00208006f, 1.0f);
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ = 83.2;
	}

	void seBrass()
	{
		ambient_ = { 0.329412f, 0.223529f, 0.027451f,1.0f };
		diffuse_ = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
		specular_ = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
		shininess_ = 27.8974f;
	}

	void setBronze()
	{
		ambient_ = { 0.2125f, 0.1275f, 0.054f, 1.0f };
		diffuse_ = { 0.714f, 0.4284f, 0.18144f, 1.0f };
		specular_ = { 0.393548f, 0.271906f, 0.166721f, 1.0f };
		shininess_ = 25.6f;
	}

	void setChrome()
	{
		ambient_ = { 0.25f, 0.25f, 0.25f, 1.0f };
		diffuse_ = { 0.4f, 0.4f, 0.4f, 1.0f };
		specular_ = { 0.774597f, 0.774597f, 0.774597f, 1.0f };
		shininess_ = 76.8f;
	}

	void setTin()
	{
		ambient_ = { 0.105882f, 0.058824f, 0.113725f, 1.0f };
		diffuse_ = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
		specular_ = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
		shininess_ = 9.84615f;
	}

	void setEmerald()
	{
		ambient_ = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
		diffuse_ = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
		specular_ = { 0.633f, 0.727811f, 0.633f, 0.55f };
		shininess_ = 76.8f;
	}

	void setPerl()
	{
		ambient_ = { 0.25f, 0.20725f, 0.20725f, 0.922f };
		diffuse_ = { 1.0f, 0.829f, 0.829f, 0.922f };
		specular_ = { 0.296648f, 0.296648f, 0.296648f, 0.922f };
		shininess_ = 11.264f;
	}

	void setCyan()
	{
		ambient_ = { 0.0f,0.1f,0.06f ,1.0f };
		diffuse_ = { 0.0f,0.50980392f,0.50980392f,1.0f };
		specular_ = { 0.50196078f,0.50196078f,0.50196078f,1.0f };
		shininess_ = 32.0f;
	}

	void setBlack()
	{
		ambient_ = { 0.0f, 0.0f, 0.0f, 1.0f };
		diffuse_ = { 0.01f, 0.01f, 0.01f, 1.0f };
		specular_ = { 0.50f, 0.50f, 0.50f, 1.0f };
		shininess_ = 32.0f;
	}

	void setObsidian()
	{
		ambient_ = { 0.05375f, 0.05f, 0.06625f, 0.82f };
		diffuse_ = { 0.18275f, 0.17f, 0.22525f, 0.82f };
		specular_ = { 0.332741f, 0.328634f, 0.346435f, 0.82f };
		shininess_ = 38.4f;
	}

	void setPolished()
	{
		ambient_ = { 0.2295f, 0.08825f, 0.0275f, 1.0f };
		diffuse_ = { 0.5508f, 0.2118f, 0.066f, 1.0f };
		specular_ = { 0.580594f, 0.223257f, 0.0695701f, 1.0f };
		shininess_ = 51.2f;
	}

	void setYellow()
	{
		ambient_ = { 0.05f,0.05f,0.0f,1.0f };
		diffuse_ = { 0.5f,0.5f,0.4f,1.0f };
		specular_ = { 0.7f,0.7f,0.04f,1.0f };
		shininess_ = 10.0f;

	}
};
