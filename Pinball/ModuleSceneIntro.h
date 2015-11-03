#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "p2DynArray.h"



class PhysBody;

struct Bouncer
{
	PhysBody* body;
	SDL_Texture* bouncer_tex;
	uint hit_timer;
	uint fx;

};

struct Light
{
	Light() : body(NULL), texture(NULL), check(false), fx(0)
	{}

	Light(ModuleSceneIntro* physics, int x, int y, uint radius);


	PhysBody* body;
	SDL_Texture* texture;
	bool check;
	uint fx;
	int x, y;
};



class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	//void Temporizator(SDL_Texture* tex, int pos_x, int pos_y);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> pinballObjects;
	p2List<PhysBody*> bouncerObjects;

	p2DynArray<Light> lights;

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* pinball_texture;
	SDL_Texture* light;
	SDL_Texture* pivot;

	Bouncer volt1_bouncer;
	Bouncer volt2_bouncer;
	Bouncer volt3_bouncer;
	Bouncer left_bouncer;
	Bouncer right_bouncer;

	Light left1;
	Light left2;
	Light left3;
	Light mid1;
	Light mid2;
	Light right1;
	Light right2;
	Light right3;


	SDL_Texture* map;

	uint score;
	uint bonus_fx;
	uint lifes;
	p2Point<int> ray;
	bool ray_on;
};
