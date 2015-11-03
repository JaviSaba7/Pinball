#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleRender.h"
#include "Module.h"
#include "Application.h"



struct Object
{
	PhysBody* body;
	SDL_Texture* object_tex;
	uint fx;

	Object() : object_tex(NULL), body(NULL)
	{}
};


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	uint GetLives();
	uint GetFinalScore();


public:

	Object ball;
	Object left_flipper;
	Object right_flipper;
	Object spring;


	PhysBody* spring_wheel;
	PhysBody* support;
	PhysBody* left_wheel;
	PhysBody* right_wheel;

	uint lives = 3;
	uint score;
	uint final_score;

	Object newball;
	Object losemusic;

};