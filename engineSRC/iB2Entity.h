#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
#include "i2DE.h"
#ifdef BOX2D_ENGINE_ON
using namespace std;
using namespace zelpMath;

//clas type
enum{
	CLASS_GHOST = -1,		//no interaction...
	CLASS_ENTITY = 1,
	CLASS_STATIC,
	CLASS_DYNAMIC
};

//categoryBits (1, 2, 4, 8, ...)
enum{
	STATIC_COLLISSON = 1,
	DYNAMIC_COLLISSON = 2,
	//NEXT_COLLISSON_TYPE = 4
	ENTITY_COLLISSON = 65535	// 65535 je max cuint number
};

//maskBits
enum{
	COLLISSON_WITH_ENTITY = 65535,  //65535 max number of uint16
	COLLISSON_WITH_STATIC = DYNAMIC_COLLISSON,
	COLLISSON_WITH_DYNAMIC = DYNAMIC_COLLISSON | STATIC_COLLISSON
};

struct IB2Entity{
protected :		
	b2World *b2world;
	static unsigned int idCount;
	unsigned objectID;
public:
	//kolik pixelu je v 1.0f v box2D - takze vsechno renderuji render * box2Dratio a davam body o loc / box2Dratio
	//vsechny vypocty upravuji v metodach - at na box2Dratio nemusim myslet pri vytvareni sceny
	//v cestine : vypocty zmensuji o box2Dratio a render zvetsuji o box2Dratio
	static float box2Dratio;
	b2Body* body;
	b2BodyDef* bodyDef;
	//collision behavior...
	int classType;
	uint16 categoryBits;
	uint16 maskBits;
	//lambda funkce pro start / end contact
	std::function<void()> onStartCallback = {NULL};
	std::function<void()> onEndCallback = {NULL};
	std::function<void()> onPreSolveCallback = {NULL};
	std::function<void()> onPostSolveCallback = {NULL};
public:
	//----------------------------------------------------------------------------------------------------------
	IB2Entity(b2World* b2world, IPointF originLoc, b2BodyType type = b2_dynamicBody);	//b2_staticBody
	~IB2Entity();
	void setCollisionBehavior(int classType, uint16 categoryBits, uint16 maskBits);
	virtual void startContact(b2Contact *contact);
	virtual void endContact(b2Contact *contact);
	virtual void preSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void postSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	int getClassType();
	void addShape(vector<b2Vec2> *vertices, float weight, float friction, float restitution);
	void addChainShape(vector<b2Vec2>* vertices, float weight, float friction, float restitution);
	void addCircleShape(float radius, float weight, float friction, float restitution);
	void addBoxShape(float width, float height, float weight, float friction, float restitution, float offsetX = 0.0f, float offsetY = 0.0f);
	uint16 getCategoryBits();
	uint16 getMaskBits();
	IPointF getOriginLoc();
	void setAngleRad(float angleRad);	
	float getAngleRad();
	void setLocationOrigin(float originX, float originY);
	void setLocationOrigin(float originX, float originY, float angleRad);	//teleport
	bool isPointInsideBox2D(IPointF point);
	void setLinearVelocity(b2Vec2 vel);
	void setDensity(float density);
	void renderDebugBox2D();
	void bindStart(std::function<void()> func);
	void bindEnd(std::function<void()> func);
	void bindPreSolve(std::function<void()> func);
	void bindPostSolve(std::function<void()> func);

	//fasada + bonus
	static IPointF cursorOriginToBox2D(IPointF cursorOrigin);
	void debugFly(IPointF originPoint);		//cursorJoint je lepsi, ale tohle se hodi vice pro debug
};

#endif

