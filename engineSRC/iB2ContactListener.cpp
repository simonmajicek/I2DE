#include "iB2ContactListener.h"
#ifdef BOX2D_ENGINE_ON

void IB2ContactListener::BeginContact(b2Contact *contact){
	void *bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void *bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if(bodyUserData1){
		((IB2Entity*)contact->GetFixtureA()->GetBody()->GetUserData())->startContact(contact);
	}
	if(bodyUserData2){
		((IB2Entity*)contact->GetFixtureB()->GetBody()->GetUserData())->startContact(contact);
	}
}

void IB2ContactListener::EndContact(b2Contact *contact){
	void *bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void *bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if(bodyUserData1){
		((IB2Entity*)contact->GetFixtureA()->GetBody()->GetUserData())->endContact(contact);
	}
	if(bodyUserData2){
		((IB2Entity*)contact->GetFixtureB()->GetBody()->GetUserData())->endContact(contact);
	}
}

void IB2ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData1) {
		((IB2Entity*)contact->GetFixtureA()->GetBody()->GetUserData())->preSolve(contact, oldManifold);
	}
	if (bodyUserData2) {
		((IB2Entity*)contact->GetFixtureB()->GetBody()->GetUserData())->preSolve(contact, oldManifold);
	}
}

void IB2ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData1) {
		((IB2Entity*)contact->GetFixtureA()->GetBody()->GetUserData())->postSolve(contact, impulse);
	}
	if (bodyUserData2) {
		((IB2Entity*)contact->GetFixtureB()->GetBody()->GetUserData())->postSolve(contact, impulse);
	}
}

#endif