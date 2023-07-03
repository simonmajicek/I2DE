#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"
#include "i2DE.h"
#include "iB2Entity.h"
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
public:
public:
	//----------------------------------------------------------------------------------------------------------
	IB2Joint(b2World* b2world);
	~IB2Joint();
	void createDistanceJoint(b2Body* bodyObjectA, b2Body* bodyObjectB, b2Vec2 localAnchorA, b2Vec2 localAnchorB);	//vraci jointID
	void createRevoluteJoint(b2Body* bodyObjectA, b2Body* bodyObjectB, b2Vec2 localAnchorA, b2Vec2 localAnchorB);	//vraci jointID
	void createWeldJoint(b2Body* bodyObjectA, b2Body* bodyObjectB, b2Vec2 localAnchorA, b2Vec2 localAnchorB);		//vraci jointID

};

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

struct IB2MouseJoint {
protected:
	b2World* b2world = {NULL};
	b2Body* mouseBody = { NULL };
	IPointF* cursorOriginPoint = { NULL };
public :
	b2MouseJoint* mJoint = { NULL };
	IPointF cursorOriginToBox2DOrigin;		//zapocet box2dratio
public :
	IB2MouseJoint(b2World* b2world, IPointF* cursorOriginPoint);
	~IB2MouseJoint();
	void update();
	void grabObject(b2Body* bodyObject);
	bool tryGrabObject(b2Body* bodyObject);
	void releaseObject();
};

#endif
