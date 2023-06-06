#pragma once
#include "allStaticLib.h"
#include "iB2Entity.h"
#ifdef BOX2D_ENGINE_ON

struct IB2ContactListener : public b2ContactListener{
public:		
	IB2ContactListener(){};
	~IB2ContactListener(){};
	void BeginContact(b2Contact *contact);
	void EndContact(b2Contact *contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif

