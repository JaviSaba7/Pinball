#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"
#include "p2Point.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)



enum body_type{b_dynamic,b_static,b_kinematic};

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	PhysBody::PhysBody(b2Body* body, const SDL_Rect& rect, body_type type) : body(body), rect(rect), type(type), listener(NULL)
	{}


	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;
	void Push(float x, float y);



public:
	int width, height;
	b2Body* body;
	Module* listener;
	SDL_Rect rect;

private:
	
	body_type type;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, b2BodyType type);
	PhysBody* CreateCircleSensor(int x, int y, int radius, b2BodyType type);
	PhysBody* CreateRectangle(int x, int y, int width, int height, b2BodyType type);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateStaticChain(int x, int y, int* points, int size);

	PhysBody* AddBody(int x, int y, int* points, uint count, float density, float restitution, b2BodyType type);
	PhysBody* CreateFlipper(int x, int y, int* points, uint count, float density, float restitution, bool isSensor);
	PhysBody* AddCircularBody(int x, int y, int diameter, body_type type, float density, float restitution, bool ccd, bool isSensor);

	void CreateRevoluteJoint(PhysBody* body_1, PhysBody* body_2, int x_pivot_1, int y_pivot_1, int x_pivot_2, int y_pivot_2, int max_angle, int min_angle);
	void CreateLineJoint(PhysBody* body_1, PhysBody* body_2, int x_pivot_1, int y_pivot_1, int x_pivot_2, int y_pivot_2, float frequency, float damping);
	void CreateJoint(PhysBody* flipbody, PhysBody* circlbody);

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);


	// b2ContactListener ---
	//void BeginContact(b2Contact* contact);

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
	
	p2List<PhysBody*> bodies;

};