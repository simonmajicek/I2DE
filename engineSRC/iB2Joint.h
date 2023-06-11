#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
#include "i2DE.h"
#ifdef BOX2D_ENGINE_ON
using namespace std;
using namespace zelpMath;

struct IB2Joint {
protected:
	b2World* b2world;
	static unsigned int idCount;
	unsigned jointID;
	b2DistanceJoint* dJoint;
	b2RevoluteJoint* rJoint;
	b2WeldJoint* wJoint;
	b2MouseJoint* mJoint;
public:
	b2Body* body;
public:
	//----------------------------------------------------------------------------------------------------------
	IB2Joint(b2World* b2world);
	~IB2Joint();
	void createDistanceJoint(b2Body* bodyObjectA, b2Body* bodyObjectB, b2Vec2 localAnchorA, b2Vec2 localAnchorB);	//vraci jointID
	void createRevoluteJoint(b2Body* bodyObjectA, b2Body* bodyObjectB, b2Vec2 localAnchorA, b2Vec2 localAnchorB);	//vraci jointID
	void createWeldJoint(b2Body* bodyObjectA, b2Body* bodyObjectB, b2Vec2 localAnchorA, b2Vec2 localAnchorB);		//vraci jointID
	void grabObject(b2World* b2world, b2Body* bodyObject, IPointF originPoint);			//originPoint muze byt treba kde cursor kliknul
	bool tryGrabObject(b2World* b2world, b2Body* bodyObject, IPointF originPoint);
	void releaseObject(b2World* b2world);

};

#endif
