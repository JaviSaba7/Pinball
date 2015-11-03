#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"



ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	

	ball.body = App->physics->CreateCircle(524, 417, 10, b2_dynamicBody);
	ball.object_tex = App->textures->Load("pinball/Ball.png");
	ball.body->listener = this;

	left_flipper.object_tex = App->textures->Load("pinball/FlipperLeft.png");
	right_flipper.object_tex = App->textures->Load("pinball/FlipperRight.png");
	spring.object_tex = App->textures->Load("pinball/Pivot.png");
	losemusic.fx = App->audio->LoadFx("pinball/LoseMusic.wav");
	newball.fx = App->audio->LoadFx("pinball/NewBall.wav");




	int LeftFlipper[14] = {
		
		270, 596,
		280, 595,
		313, 622,
		315, 628,
		308, 629,
		271, 612,
		265, 603
	};

	/*left_flipper.body = App->physics->CreatePolygon({ 138, 592, 0, 0 }, LeftFlipper, 14, b2_staticBody, 10.0, 1.0, false);
	left_wheel = App->physics->AddCircularBody(148, 587, 4, b_static, 1.0, 1.0, false, false);
	App->physics->CreateRevoluteJoint(left_flipper.body, left_wheel, 5, 5, 0, 0, 30, -30);*/

	left_flipper.body = App->physics->CreateFlipper(10, 2, LeftFlipper, 14, 10.0f, 0.0f, false);
	left_wheel = App->physics->CreateCircle(272, 603, 2, b2_staticBody);
	//App->physics->CreateRevoluteJoint(left_flipper.body, left_wheel, 4, 4, 0, 0, 30, -30);
	App->physics->CreateJoint(left_flipper.body, left_wheel);


	int RightFlipper[14] = {
		381, 596,
		393, 598,
		394, 610,
		352, 630,
		345, 629,
		347, 622,
		377, 599
	};

	right_flipper.body = App->physics->CreateFlipper(10, 2, RightFlipper, 14, 10.0f, 0.0f, false);
	right_wheel = App->physics->CreateCircle(377, 603, 2, b2_staticBody);
	App->physics->CreateJoint(right_flipper.body, right_wheel);

	

	int Pusher[8] = {
		512, 615,
		538, 615,
		538, 644,
		511, 643

	};

	int Support[8] = {
		517, 632,
		529, 631,
		529, 638,
		519, 637
	};

	spring.body = App->physics->CreateRectangle(525, 530, 30, 50, b2_dynamicBody);
	spring_wheel = App->physics->CreateCircle(505, 470, 5, b2_staticBody);
	App->physics->CreateLineJoint(spring.body, spring_wheel, 1, 1, 0, 0, 15, 0.5);

	support = App->physics->CreateStaticChain(App->input->GetMouseX(), App->input->GetMouseY(), Support, 8);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	static float spring_push = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		left_flipper.body->body->ApplyAngularImpulse(DEGTORAD * -160, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		right_flipper.body->body->ApplyAngularImpulse(DEGTORAD * 160, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		left_flipper.body->body->ApplyAngularImpulse(DEGTORAD * 100, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		right_flipper.body->body->ApplyAngularImpulse(DEGTORAD * -100, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		spring_push += 175.0f;
		spring.body->Push(0, spring_push);
	}
	else
		spring_push = 0.0f;



	int x, y;




	ball.body->GetPosition(x, y);
	App->renderer->Blit(ball.object_tex, x, y, NULL, 1.0f, ball.body->GetRotation());

	left_wheel->GetPosition(x, y);
	App->renderer->Blit(left_flipper.object_tex, x - 20, y - 15, NULL, 1.0f, left_flipper.body->GetRotation());

	right_wheel->GetPosition(x, y);
	App->renderer->Blit(right_flipper.object_tex, x - 25, y - 20, NULL, 1.0f, right_flipper.body->GetRotation());

	spring_wheel->GetPosition(x, y);
	App->renderer->Blit(spring.object_tex, x, y);


	ball.body->GetPosition(x, y);
	App->renderer->Blit(ball.object_tex, x, y, NULL, 1.0f, ball.body->GetRotation());

	if (y > 650)
	{
		ball.body = App->physics->CreateCircle(524, 417, 10, b2_dynamicBody);
		App->audio->PlayFx(newball.fx);

		lives--;
		if (lives <= 0)
		{
			lives = 3;
			App->audio->PlayFx(losemusic.fx);
		}
	}



	return UPDATE_CONTINUE;
}

uint ModulePlayer::GetLives()
{
	return lives;
}

uint ModulePlayer::GetFinalScore()
{
	return final_score;
}

