#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleWindow.h"
#include "ModulePlayer.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	
	
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	App->audio->PlayMusic("pinball/PokemonSong.wav");
	pinball_texture = App->textures->Load("pinball/Pinball.png");



	left_bouncer.bouncer_tex = App->textures->Load("pinball/LeftBouncer.png");
	right_bouncer.bouncer_tex = App->textures->Load("pinball/RightBouncer.png");

	volt1_bouncer.bouncer_tex = App->textures->Load("pinball/Volt1Bouncer.png");
	volt2_bouncer.bouncer_tex = App->textures->Load("pinball/Volt1Bouncer.png");
	volt3_bouncer.bouncer_tex = App->textures->Load("pinball/Volt1Bouncer.png");
	

	light = App->textures->Load("pinball/Light.png");
	

	left1.texture = App->textures->Load("pinball/Arrow1.png");
	right1.texture = App->textures->Load("pinball/Arrow2.png");



	left_bouncer.fx = App->audio->LoadFx("pinball/Sound1.wav");
	left1.fx = App->audio->LoadFx("pinball/Sound3.wav");
	
	circle = App->textures->Load("pinball/wheel.png");

	

	map = App->textures->Load("nom");



	int ExteriorBox[90] = {
		146, 649,
		273, 649,
		166, 583,
		164, 483,
		169, 471,
		175, 464,
		183, 459,
		190, 458,
		201, 456,
		201, 408,
		205, 398,
		212, 390,
		209, 381,
		196, 361,
		187, 334,
		178, 301,
		172, 271,
		168, 217,
		169, 150,
		176, 126,
		186, 103,
		208, 76,
		230, 59,
		251, 45,
		273, 37,
		293, 30,
		322, 29,
		343, 29,
		363, 29,
		390, 29,
		416, 38,
		435, 46,
		450, 53,
		471, 67,
		486, 82,
		500, 98,
		512, 120,
		523, 141,
		532, 166,
		538, 198,
		540, 647,
		579, 649,
		580, 0,
		146, 0,
		144, 641
	};

	pinballObjects.add(App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), ExteriorBox, 90));


	int InteriorLargePiece[82] = {
		384, 650,
		508, 648,
		509, 198,
		502, 164,
		488, 130,
		468, 103,
		436, 79,
		399, 62,
		364, 54,
		326, 53,
		298, 55,
		272, 66,
		241, 90,
		236, 100,
		267, 84,
		286, 78,
		339, 72,
		368, 78,
		398, 87,
		418, 100,
		438, 116,
		461, 141,
		480, 174,
		486, 196,
		486, 224,
		486, 242,
		482, 266,
		478, 296,
		470, 334,
		460, 364,
		444, 386,
		443, 394,
		455, 412,
		454, 456,
		468, 462,
		479, 467,
		487, 476,
		490, 490,
		490, 594,
		461, 595,
		390, 646
	};
	pinballObjects.add(App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), InteriorLargePiece, 82));

	
//	pinballObjects.add(App->physics->AddBody({ 0, 0, 400, 400 },RightFlipper,24,b_dynamic,1.0f,1.0f,false));

	//////////////////////////
	int Piece3[82] = {
		271, 302,
		280, 303,
		288, 296,
		295, 287,
		294, 274,
		287, 260,
		267, 242,
		254, 216,
		253, 192,
		263, 171,
		277, 162,
		303, 150,
		320, 140,
		340, 135,
		352, 132,
		369, 136,
		380, 144,
		390, 161,
		395, 169,
		394, 196,
		392, 218,
		386, 256,
		382, 273,
		394, 285,
		405, 261,
		408, 232,
		405, 122,
		386, 109,
		357, 103,
		332, 101,
		313, 105,
		295, 116,
		281, 127,
		267, 142,
		255, 162,
		247, 185,
		244, 214,
		246, 252,
		251, 278,
		259, 295,
		264, 300
	};
	pinballObjects.add(App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), Piece3, 82));

	/////////////////
	int Piece4[50] = {
		442, 224,
		439, 158,
		445, 169,
		447, 176,
		451, 187,
		452, 193,
		453, 205,
		453, 215,
		453, 232,
		454, 250,
		454, 267,
		451, 280,
		447, 296,
		443, 315,
		436, 330,
		420, 352,
		408, 342,
		409, 333,
		415, 321,
		423, 309,
		429, 295,
		433, 281,
		436, 268,
		442, 246,
		441, 229
	


	};
	pinballObjects.add(App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), Piece4, 50));

	////////////////////////////
	int Piece5[38] = { 
		215, 199,
		217, 202,
		217, 212,
		213, 222,
		212, 236,
		215, 260,
		219, 275,
		225, 300,
		235, 316,
		249, 334,
		248, 343,
		240, 349,
		236, 354,
		225, 340,
		213, 311,
		206, 285,
		201, 261,
		201, 225,
		209, 204

	};
	pinballObjects.add(App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), Piece5, 38));
	
	/////////////////////////////////

	int Piece6[12] = {
		227, 490,
		227, 529,
		258, 550,
		259, 542,
		238, 498,
		232, 488

	};
	pinballObjects.add(App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), Piece6, 12));


	int Piece7[12] = {
		423, 488,
		429, 489,
		430, 528,
		414, 545,
		397, 550,
		420, 492

	};
	pinballObjects.add(App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), Piece7, 12));

	////////////////////////
	int Piece8[20] = {
		194, 484,
		201, 483,
		201, 534,
		204, 541,
		211, 551,
		241, 572,
		241, 597,
		200, 569,
		193, 560,
		194, 489

	};
	pinballObjects.add(App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), Piece8, 20));

	int Piece9[16] = {
		456, 483,
		464, 483,
		463, 560,
		408, 600,
		408, 579,
		444, 552,
		456, 537,
		456, 488

	};
	pinballObjects.add(App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), Piece9, 16));
	
	///////////////////



	//volt1_bouncer.body = App->physics->AddBody(-2, 2, Voltorb3, 30, 1.0f, 1.0f, b2_staticBody);
	volt1_bouncer.body = App->physics->CreateCircle(352, 180, 18, b2_staticBody);
	volt1_bouncer.body->listener = this;

	volt2_bouncer.body = App->physics->CreateCircle(295, 203, 18, b2_staticBody);
	volt2_bouncer.body->listener = this;

	volt3_bouncer.body = App->physics->CreateCircle(338, 246, 18, b2_staticBody);
	volt3_bouncer.body->listener = this;
	

	
	int bouncerL[8] = {
		234, 489,
		261, 545,
		267, 542,
		240, 488
	};

	left_bouncer.body = App->physics->AddBody(-2, 2, bouncerL, 8, 1.0f, 1.0f, b2_staticBody);
	left_bouncer.body->listener = this;


	int bouncerR[8] = {
		424, 488,
		396, 543,
		389, 540,
		418, 484
	};

	right_bouncer.body = App->physics->AddBody(4, 2, bouncerR, 8, 1.0f, 1.0f,b2_staticBody);
	right_bouncer.body->listener = this;


	lights.PushBack(Light(this, 244, 401, 8));
	lights.PushBack(Light(this, 230, 377, 8));
	lights.PushBack(Light(this, 217, 354, 8));
	lights.PushBack(Light(this, 273, 334, 8));
	lights.PushBack(Light(this, 385, 334, 8));
	lights.PushBack(Light(this, 411, 401, 8));
	lights.PushBack(Light(this, 425, 380, 8));
	lights.PushBack(Light(this, 438, 356, 8));



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	static int puntuation = 0;


	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, b2_dynamicBody));
		// TODO 8: Make sure to add yourself as collision callback to the circle you creates
	}

	////////////////////////////////////////////////////////////////
		

		iPoint mouse;
		mouse.x = App->input->GetMouseX();
		mouse.y = App->input->GetMouseY();
		int ray_hit = ray.DistanceTo(mouse);

		fVector normal(0.0f, 0.0f);

		// All draw functions ------------------------------------------------------
		p2List_item<PhysBody*>* c = circles.getFirst();

		while (c != NULL)
		{
			int x, y;
			c->data->GetPosition(x, y);

			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
			c = c->next;
		}


		

		c = pinballObjects.getFirst();
		while (c != NULL)
		{
			int x, y;
			c->data->GetPosition(x, y);
			App->renderer->Blit(pinball_texture, x, y, NULL, 1.0f, c->data->GetRotation());
			c = c->next;
		}

		int x, y;
		App->player->support->GetPosition(x, y);
		App->renderer->Blit(pivot, x, y, NULL, 1.0f, App->player->support->GetRotation());


		// ray -----------------
		if (ray_on == true)
		{
			fVector destination(mouse.x - ray.x, mouse.y - ray.y);
			destination.Normalize();
			destination *= ray_hit;

			App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

			if (normal.x != 0.0f)
				App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
		}


		if (left_bouncer.hit_timer > 0)
		{
			if (SDL_TICKS_PASSED(SDL_GetTicks(), left_bouncer.hit_timer) == false)
				App->renderer->Blit(left_bouncer.bouncer_tex, 228, 487);
			else
			{
				left_bouncer.hit_timer = 0;
				score += 10;
			}
		}

		if (right_bouncer.hit_timer > 0)
		{
			if (SDL_TICKS_PASSED(SDL_GetTicks(), right_bouncer.hit_timer) == false)
				App->renderer->Blit(right_bouncer.bouncer_tex, 397, 487);
			else
			{
				right_bouncer.hit_timer = 0;
				score += 10;
			}
		}

		if (volt1_bouncer.hit_timer > 0)
		{
			if (SDL_TICKS_PASSED(SDL_GetTicks(), volt1_bouncer.hit_timer) == false)
				App->renderer->Blit(volt1_bouncer.bouncer_tex, 333, 160);
			else
			{
				right_bouncer.hit_timer = 0;
				score += 10;
			}
		}

		if (volt2_bouncer.hit_timer > 0)
		{
			if (SDL_TICKS_PASSED(SDL_GetTicks(), volt2_bouncer.hit_timer) == false)
				App->renderer->Blit(volt2_bouncer.bouncer_tex, 278, 183);
			else
			{
				right_bouncer.hit_timer = 0;
				score += 10;
			}
		}

		if (volt3_bouncer.hit_timer > 0)
		{
			if (SDL_TICKS_PASSED(SDL_GetTicks(), volt3_bouncer.hit_timer) == false)
				App->renderer->Blit(volt3_bouncer.bouncer_tex, 320, 225);
			else
			{
				right_bouncer.hit_timer = 0;
				score += 10;
			}
		}


		for (uint i = 0; i < lights.Count(); ++i)
		{
			if (lights[i].check == true)
			{
				App->renderer->Blit(light, lights[i].x - 9, lights[i].y - 9);
			}
		}

		


		char title[50];
		sprintf_s(title, "Balls: %d, Score: %d  ", App->player->GetLives(), score);
		App->window->SetTitle(title);
		
		return UPDATE_CONTINUE;
}



// TODO 8: Now just define collision callback for the circle and play bonus_fx audio
void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	if (left_bouncer.body == bodyA)
	{
		left_bouncer.hit_timer = SDL_GetTicks() + 100;
		App->audio->PlayFx(left_bouncer.fx);
		
		return;
	}

	if (right_bouncer.body == bodyA)
	{
		right_bouncer.hit_timer = SDL_GetTicks() + 600;
		App->audio->PlayFx(left_bouncer.fx);
		return;
	}

	if (volt1_bouncer.body == bodyA)
	{
		volt1_bouncer.hit_timer = SDL_GetTicks() + 600;
		App->audio->PlayFx(left_bouncer.fx);
		return;
	}

	if (volt2_bouncer.body == bodyA)
	{
		volt2_bouncer.hit_timer = SDL_GetTicks() + 100;
		App->audio->PlayFx(left_bouncer.fx);
		return;
	}

	if (volt3_bouncer.body == bodyA)
	{
		volt3_bouncer.hit_timer = SDL_GetTicks() + 100;
		App->audio->PlayFx(left_bouncer.fx);
		return;
	}

	for (uint i = 0; i < lights.Count(); ++i)
	{
		if (bodyA == lights[i].body)
		{
			if (lights[i].check == false)
			{
				lights[i].check = true;
				App->audio->PlayFx(left1.fx);
			}
			return;
		}
	}

	
}

Light::Light(ModuleSceneIntro* scene, int x, int y, uint radius)
{

	this->x = x;
	this->y = y;

	body = scene->App->physics->CreateCircleSensor(x, y, radius, b2_staticBody);
	body->listener = scene;
	check = false;
}
