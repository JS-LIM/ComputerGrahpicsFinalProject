#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GL\GLU.h>
#include <GL\freeglut.h>

#include <cstring>
#include <stdlib.h>        // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GL\GLU.h>
#include <GL\freeglut.h>
#include <vector>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <Geometry\TriangularSurface\StaticTriangularSurface.h>
#include <GL2\GL2_World.h>
#include <GL2\GL2_Object.h>
#include <GL2\GL2_Light.h>
#include <GL2\GL2_Material.h>
#include <BMPImage.h>
#include "ParticleSystem.h"
#include "MissileSystem.h"
#include "Fountain.h"
#define _CRT_SECURE_NO_WARNINGS

int width_window = 640;
int height_window = 480;

GL2_World gl_world;

float move_x = 0.0;
float move_y = 0.0;
float move_z = 0.0;
float rot = 0.0;
TV move = TV(move_x, move_y, move_z);

float coll_x = 0.0;
float coll_y = 0.0;
float coll_z = 0.0;

int flag = 0;
int count = 0;
//static float proj = 0.0;
class manClass {
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	gl_world.camera_.UpdateDolly(yoffset); // zoom in & zoom out => dolly
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) //마우스 오른쪽 버튼 눌렸을 때
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos); //x와 y좌표 값 받아온다.

		gl_world.camera_.StartMouseRotation(xpos, ypos);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) //마우스 오른쪽 버튼 떼었을 때
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		gl_world.camera_.EndMouseRotation(xpos, ypos);
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) //마우스 왼쪽 버튼 눌렀을 때
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		gl_world.camera_.StartMousePan(xpos, ypos);
		flag = 1;
		count += 1;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) //마우스 왼쪽 버튼 떼었을 때
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		gl_world.camera_.EndMousePan(xpos, ypos);
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) //계속적으로 마우스의 위치를 받아온다.
{
	//std::cout << xpos << " " << ypos << std::endl;

	gl_world.camera_.ProcessMouseMotion(xpos, ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		static float proj = 0.025;
		gl_world.camera_.SetMode(proj);
		move_z = -0.01;
		coll_z += move_z;
	}

	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		static float proj = 0.0;
		move_z = 0.0;
	}

	else if (key == GLFW_KEY_W && action == GLFW_REPEAT)
	{
		static float proj = 0.025;
		gl_world.camera_.SetMode(proj);
	}

	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		static float proj = -0.025;
		gl_world.camera_.SetMode(proj);
		move_z = 0.01;
		coll_z += move_z;
	}

	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		static float proj = 0.0;
		move_z = 0.0;
	}

	else if (key == GLFW_KEY_S && action == GLFW_REPEAT)
	{
		static float proj = -0.025;
		gl_world.camera_.SetMode(proj);
	}

	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		static float proj = -0.025;
		gl_world.camera_.SetMode_2(proj);
		move_x = 0.01;
		coll_x += move_x;
	}

	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		static float proj = 0.0;
		move_x = 0.0;
	}

	else if (key == GLFW_KEY_D && action == GLFW_REPEAT)
	{
		static float proj = -0.025;
		gl_world.camera_.SetMode_2(proj);
	}

	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		static float proj = 0.025;
		gl_world.camera_.SetMode_2(proj);
		move_z = 0.0;
		move_x = -0.01;
		coll_x += move_x;
	}

	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		static float proj = 0.0;
		move_x = 0.0;
	}

	else if (key == GLFW_KEY_A && action == GLFW_REPEAT)
	{
		static float proj = 0.025;
		gl_world.camera_.SetMode_2(proj);
	}

	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		static float proj = -0.025;
		gl_world.camera_.SetMode_4(proj);
		move_y = 0.01;
	}

	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		static float proj = 0.0;
		move_y = 0.0;
	}

	else if (key == GLFW_KEY_SPACE && action == GLFW_REPEAT)
	{
		static float proj = -0.025;
		gl_world.camera_.SetMode_4(proj);
	}

	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
	static float proj = +0.025;
		gl_world.camera_.SetMode_4(proj);
		move_y = -0.01;
	}

	else if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
	{
		static float proj = 0.0;
		move_y = 0.0;
	}

	else if (key == GLFW_KEY_Q && action == GLFW_REPEAT)
	{
		static float proj = +0.025;
		gl_world.camera_.SetMode_4(proj);
	}
}

int main(void)
{
	GLFWwindow* window = nullptr;
	glm::mat4 cv;

	/* Initialize the library */
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_SAMPLES, 32);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width_window = mode->width * 0.8f;
	height_window = mode->height * 0.8f;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Texturing", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks here
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glClearColor(0, 0, 0, 1); // white background

	printf("%s\n", glGetString(GL_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	const float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glOrtho(-1.2*aspect, 1.2*aspect, -1.2, 1.2, -100.0, 100.0);
	gluLookAt(0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 0, 1, 0);

	const float zNear = 0.001, zFar = 100.0, fov = 45.0;
	gl_world.camera_.Resize(width, height, fov, zNear, zFar);
	gl_world.initShaders();

	glEnable(GL_MULTISAMPLE);

	ParticleSystem ps;
	MissileSystem ms;
	FountainSystem fs;
	fs.initParticleSystem();
	ps.initParticleSystem();
	ms.initParticleSystem();

		StaticTriangularSurface man;
	man.readObj("IronMan_Full_smooth.obj", true, true); // 파일명, object의 좌표값을 -1~1사이로 만들기, 원점으로 이동
	man.rotate(-3.14 / 2, TV(1, 0, 0));
	man.rotate(3.14, TV(0, 1, 0));

	// object setting
	man.center = TV(0.0f, 0.0f, 0.0f);
	man.radius = 0.5f;
	man.scale(0.5);

	GL2_Object gl_obj; //shadding을 해준다.
	gl_obj.initPhongSurface(man);
	gl_obj.mat_.setGold();

	StaticTriangularSurface rival[20];
	srand((unsigned int)time(NULL));
	rand() % 1;
	for (int i = 0; i < 20; i++)
	{
		float ran_num_x = ((float)rand() / (float)RAND_MAX) * 10 - ((float)rand() / (float)RAND_MAX) * 10; // [0,1)
		float ran_num_y = ((float)rand() / (float)RAND_MAX) * 10 - ((float)rand() / (float)RAND_MAX) * 8;
		float ran_num_z = ((float)rand() / (float)RAND_MAX) * 2 - 7.5;// [0,1)
		rival[i].readObj("sphere.obj", true, true);
		rival[i].scale(0.5f);
		rival[i].radius = 0.4;
		rival[i].translate(TV(ran_num_x, ran_num_y, ran_num_z));
		rival[i].center = TV(ran_num_x, ran_num_y, ran_num_z);
	}

	GL2_Object rival_obj[20];
	for (int i = 0; i < 20; i++)
	{
		rival_obj[i].initPhongSurface(rival[i]);
		if (i == 1 || i == 11) {
			rival_obj[i].mat_.setRed();
		}
		else if (i == 2 || i == 12) {
			rival_obj[i].mat_.setEmerald();
		}
		else if (i == 3 || i == 13) {
			rival_obj[i].mat_.setBronze();
		}
		else if (i == 4 || i == 14) {
			rival_obj[i].mat_.setChrome();
		}
		else if (i == 5 || i == 15) {
			rival_obj[i].mat_.setYellow();
		}
		else if (i == 6 || i == 16) {
			rival_obj[i].mat_.setPerl();
		}
		else if (i == 7 || i == 17) {
			rival_obj[i].mat_.setTin();
		}

		else if (i == 8 || i == 18) {
			rival_obj[i].mat_.setCyan();
		}

		else if (i == 9 || i == 19) {
			rival_obj[i].mat_.setObsidian();
		}

		else if (i == 10 || i == 20) {
			rival_obj[i].mat_.setPolished();
		}
	}

	StaticTriangularSurface monster[4];

	for (int i = 0; i < 4; i++)
	{
		monster[i].rotate(-3.14 / 2, TV(0, 1, 0));
		float ran_num_x = ((float)rand() / (float)RAND_MAX) * 10; // [0,1)
		float ran_num_y = ((float)rand() / (float)RAND_MAX) * 10 - ((float)rand() / (float)RAND_MAX) * 8;
		float ran_num_z = ((float)rand() / (float)RAND_MAX) * 2 - 7.5;// [0,1)
		monster[i].readObj("Dark_Star_Toad.obj", true, true);
		monster[i].scale(1.5f);
		monster[i].radius = 0.75;
		monster[i].translate(TV(ran_num_x, ran_num_y, ran_num_z));
		monster[i].center = TV(ran_num_x, ran_num_y, ran_num_z);
	}

	GL2_Object obj_monster[4];
	for (int i = 0; i < 4; i++)
	{
		obj_monster[i].initPhongSurface(monster[i]);
		if (i == 1) {
			obj_monster[i].mat_.setRed();
		}
		else if (i == 2) {
			obj_monster[i].mat_.setEmerald();
		}
		else if (i == 3) {
			obj_monster[i].mat_.setBronze();
		}
		else if (i == 4) {
			obj_monster[i].mat_.setGold();
		}
	}

	StaticTriangularSurface surface;
	surface.readObj("sphere.obj", true, true);
	surface.vertex_uv_.init(surface.vertex_positions_.num_elements_);

	float ran_num_x = ((float)rand() / (float)RAND_MAX) * 10 - ((float)rand() / (float)RAND_MAX) * 10; // [0,1)
	float ran_num_y = ((float)rand() / (float)RAND_MAX) * 10;
	float ran_num_z = ((float)rand() / (float)RAND_MAX) + 9;// [0,1)

	surface.translate(TV(ran_num_x, ran_num_y, -ran_num_z));
	surface.center = TV(ran_num_x, ran_num_y, -ran_num_z);
	surface.scale(3.0f);
	for (int i = 0; i < surface.vertex_positions_.num_elements_; i++)
	{
		float x = surface.vertex_positions_[i].x_;
		float z = surface.vertex_positions_[i].z_;

		float theta = std::atan2(z, x); // -PI ~ PI
		theta = ((theta / PI) + 1.0)*0.5f;

		// uv 좌표 설정
		surface.vertex_uv_[i].u_ = theta;
		surface.vertex_uv_[i].v_ = surface.vertex_positions_[i].y_ + 0.5;//  vertext position => 0.0 ~ 1.0

	}

	GL2_Object texture;
	texture.initPhongSurfaceWithTexture(surface);
	texture.mat_.setGold();

	GLuint textures[2];
	glGenTextures(2, textures);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	// Black/white checkerboard
	/*const float pixels[] = { 1.0f, 0.0f, 0.0f,   0.3f, 0.3f, 1.0f,   0.5f, 0.5f, 0.0f,
			   0.5f, 0.5f, 1.0f,   0.0f, 0.0f, 0.0f ,   0.1f, 0.4f, 0.3f};*/

			   //표현할 행렬 개수 3, 2로 되어있음
			   //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 3, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb_array);


	int texture_width, texture_height;
	unsigned char* rgb_array;

	//파일명 입력받아서 bmp파일 불러와서 지정되있는 width, height를 변수에 각각 저장, 1차원에 변형
	//unsigned라서 GL_FLOAT를 GL_UNSIGNED_BYTE로 변경
	readBMP24("20170108_071114.bmp", &texture_width, &texture_height, &rgb_array);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb_array);

	// do not forget these options!
	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_COLOR_MATERIAL);

	glLoadIdentity();

	GL2_Light light;

	while (!glfwWindowShouldClose(window))
	{
		gl_world.camera_.ContinueRotation();
		cv = glm::lookAt(glm::vec3(0.0, -0.2, 0.0), glm::vec3(0.0, -0.2, -2.0), glm::vec3(0, 1, -1.0));
		glm::mat4 vp = gl_world.camera_.GetWorldViewMatrix() * cv;

		gl_obj.initPhongSurface(man);

		for (int i = 0; i < 20; i++)
		{
			rival_obj[i].initPhongSurface(rival[i]);
		}

		for (int i = 0; i < 4; i++)
		{
			obj_monster[i].initPhongSurface(monster[i]);
		}

		for (int i = 0; i < surface.vertex_positions_.num_elements_; ++i)
		{
			surface.vertex_uv_[i].x_ += 0.001f;
		}

		// update particle system
		ps.advanceOneTimeStep(0.003);
		ms.advanceOneTimeStep(0.003);
		fs.advanceOneTimeStep(0.0006);

		// don't need to update if there is no change
		texture.updatePhongSurfaceWithTexture(surface);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		const TV fb = TV(0.0, 0.0, move_z);
		const TV lr = TV(move_x, 0.0, 0.0);
		const TV up = TV(0, move_y, 0.0);
		const TV sphere_move = TV(0.0f, 0.0f, 0.0f);
		const TV monster_move = TV(-0.001f, 0.0f, 0.0f);
		const TV move = TV(move_x, move_y, move_z);


		// draw with shader

		glUseProgram(gl_world.shaders_2.program_id_);
		gl_world.shaders_2.sendUniform(vp, "mvp");
		texture.applyLighting(light);
		texture.drawWithTextureShader(gl_world.shaders_2);
		glUseProgram(0);

		glUseProgram(gl_world.shaders_.program_id_);
		gl_world.shaders_.sendUniform(vp, "mvp");
		gl_obj.applyLighting(light);
		gl_obj.drawWithShader(gl_world.shaders_);

		man.translate(fb);
		man.translate(lr);
		man.translate(up);

		for (int i = 0; i < 20; i++) {
			float getSignedDistance = (man.center - rival[i].center).getMagnitude() - rival[i].radius;
			if (getSignedDistance <= 0.0f) {
				std::string tmp;
				std::string str = tmp.c_str();
				std::stringstream ss;
				ss << "운석과 충돌!! 미션에 실패했습니다..";
				printf("충돌\n");
				MessageBoxA(NULL, ss.str().c_str(), "게임 종료", MB_OK);
				exit(EXIT_SUCCESS);
			}
		}

		for (int i = 0; i < 4; i++) {
			float getSignedDistance = (man.center - monster[i].center).getMagnitude() - monster[i].radius;
			if (getSignedDistance <= 0.0f) {
				std::string tmp;
				std::string str = tmp.c_str();
				std::stringstream ss;
				ss << "몬스터와 충돌!! 미션에 실패했습니다..";
				printf("충돌\n");
				MessageBoxA(NULL, ss.str().c_str(), "게임 종료", MB_OK);
				exit(EXIT_SUCCESS);
			}
		}

		for (int i = 0; i < 20; i++)
		{
			rival[i].translate(sphere_move);
			rival_obj[i].applyLighting(light);
			rival_obj[i].drawWithShader(gl_world.shaders_);
		}

		for (int i = 0; i < 4; i++)
		{
			monster[i].translate(monster_move);
			obj_monster[i].applyLighting(light);
			obj_monster[i].drawWithShader(gl_world.shaders_);
		}
		glUseProgram(0);

		const TV red = TV(1, 0, 0);
		for (int m = 0; m < ms.missiles.size(); ++m) {
			glPointSize(ms.missiles[m].mass / 2);
			glBegin(GL_POINTS);
			glColor3fv(red.values_);
			ms.missiles[m].center = TV(ms.missiles[m].pos.x_, ms.missiles[m].pos.y_, ms.missiles[m].pos.z_);
			glVertex3fv(ms.missiles[m].pos.values_);
			if (flag == 1)
			{
				printf("발사");
				printf("%d", ms.missiles.size());
				ms.addParticle(man.center);
				flag = 0;
			}
		}
		glEnd();

		for (int m = 0; m < ms.missiles.size(); ++m) {
			for (int i = 0; i < 20; i++) {
				float getSignedDistance = (ms.missiles[m].center - rival[i].center).getMagnitude() - rival[i].radius;
				if (getSignedDistance <= 0.0f) {
					rival[i].translate(TV(0.0, -100.0, -100.0));
					rival[i].scale(0.0);
					printf("명중\n");
				}
			}

			for (int i = 0; i < 4; i++) {
				float getSignedDistance = (ms.missiles[m].center - monster[i].center).getMagnitude() - monster[i].radius;
				if (getSignedDistance <= 0.0f) {
					monster[i].translate(TV(0.0, -100.0, -100.0));
					monster[i].scale(0.0);
					printf("명중\n");
				}
			}
		}
		// Old-style rendering
		glLoadMatrixf(&vp[0][0]);

		glLineWidth(2);
		glDisable(GL_LIGHTING);

		// draw particles

		const TV green = TV(0, 1, 0);

		for (int p = 0; p < ps.particles.size(); ++p)
		{
			TV& vel(ps.particles[p].vel);

			const float alpha = vel.getMagnitude() * 1.0;
			glPointSize(ps.particles[p].mass/2);
			glBegin(GL_POINTS);
			glColor3fv(green.values_);
			ps.particles[p].center = TV(ps.particles[p].pos.x_, ps.particles[p].pos.y_, ps.particles[p].pos.z_);
			glVertex3fv(ps.particles[p].pos.values_);

		}
		glEnd();

		const TV sky = TV(204 / 255, 255 / 255, 255 / 255);
		for (int f = 0; f < fs.fountain.size(); ++f)
		{
			TV& vel(fs.fountain[f].vel);

			glPointSize(fs.fountain[f].mass);
			glBegin(GL_POINTS);
			glColor3fv(sky.values_);
			fs.fountain[f].center = TV(fs.fountain[f].pos.x_, fs.fountain[f].pos.y_, fs.fountain[f].pos.z_);
			glVertex3fv(fs.fountain[f].pos.values_);
		}
		glEnd();

		for (int p = 0; p < ps.particles.size(); ++p)
		{
			std::string tmp;
			std::string str = tmp.c_str();

			std::stringstream ss;
			ss << "미사일에 맞았습니다!! 미션에 실패했습니다..";
			float getSignedDistance = (man.center - ps.particles[p].center).getMagnitude() - ps.particles[p].radius;
			if (getSignedDistance <= 0.0f) {
				printf("충돌\n");
				MessageBoxA(NULL,ss.str().c_str(), "게임 종료", MB_OK);
				exit(EXIT_SUCCESS);
			}
		}

		for (int f = 0; f < fs.fountain.size(); ++f)
		{
			std::string tmp;
			//sprintf_s((char*)tmp.c_str(), sizeof((char*)tmp.c_str()), "%d", score);
			std::string str = tmp.c_str();

			std::stringstream ss;
			ss << "이상한 것에 맞았습니다!! 미션에 실패했습니다..";
			float getSignedDistance = (man.center - fs.fountain[f].center).getMagnitude() - fs.fountain[f].radius;
			if (getSignedDistance <= 0.0f) {
				printf("충돌\n");
				MessageBoxA(NULL, ss.str().c_str(), "게임 종료", MB_OK);
				exit(EXIT_SUCCESS);
			}
		}

		surface.radius = 1.0;
		float getSignedDistance = (man.center - surface.center).getMagnitude() - surface.radius;
		if (getSignedDistance <= 0.0f) {
			std::string tmp;
			//sprintf_s((char*)tmp.c_str(), sizeof((char*)tmp.c_str()), "%d", score);
			std::string str = tmp.c_str();

			std::stringstream ss;
			printf("도착\n");
			ss << "목적지에 도착했습니다!! 미션 성공!!";
			MessageBoxA(NULL, ss.str().c_str(), "게임 종료", MB_OK);
			exit(EXIT_SUCCESS);
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	glfwTerminate();

	return 0;
}