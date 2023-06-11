#include "iB2Joint.h"

unsigned int IB2Joint::idCount = 0;

IB2Joint::IB2Joint(b2World* b2world) {
	this->b2world = b2world;
}

IB2Joint::~IB2Joint() {
	this->b2world->DestroyJoint(this->dJoint);
	this->b2world->DestroyJoint(this->rJoint);
	this->b2world->DestroyJoint(this->wJoint);
}


void IB2Joint::createDistanceJoint(b2Body* bodyObjectA, b2Body* bodyObjectB, b2Vec2 localAnchorA, b2Vec2 localAnchorB) {
	b2DistanceJointDef* distanceJointDef = new b2DistanceJointDef();
	distanceJointDef->bodyA = bodyObjectA;
	distanceJointDef->bodyB = bodyObjectB;
	distanceJointDef->collideConnected = false;
	distanceJointDef->localAnchorA = localAnchorA;
	distanceJointDef->localAnchorB = localAnchorB;
	distanceJointDef->length = 0.00000f;
	distanceJointDef->frequencyHz = 0.0f;
	distanceJointDef->dampingRatio = 0.0f;
	distanceJointDef->userData = &this->jointID;
	//ropeJointDef->dampingRatio = 0.3f;		//zele, zelatina :D
	//jointMouseDef->frequencyHz = 666.0f;

	//create the joint
	this->dJoint = (b2DistanceJoint*)b2world->CreateJoint(distanceJointDef);

	this->jointID = IB2Joint::idCount;
	IB2Joint::idCount++;
}

void IB2Joint::createRevoluteJoint(b2Body* bodyObjectA, b2Body* bodyObjectB, b2Vec2 localAnchorA, b2Vec2 localAnchorB) {
	b2RevoluteJointDef* revoluteJointDef = new b2RevoluteJointDef();
	revoluteJointDef->bodyA = bodyObjectA;
	revoluteJointDef->bodyB = bodyObjectB;
	revoluteJointDef->collideConnected = false;
	revoluteJointDef->localAnchorA = localAnchorA;
	revoluteJointDef->localAnchorB = localAnchorB;
	revoluteJointDef->userData = &this->jointID;
	this->rJoint = (b2RevoluteJoint*)b2world->CreateJoint(revoluteJointDef);

	this->jointID = IB2Joint::idCount;
	IB2Joint::idCount++;
}


void IB2Joint::createWeldJoint(b2Body* bodyObjectA, b2Body* bodyObjectB, b2Vec2 localAnchorA, b2Vec2 localAnchorB) {
	b2WeldJointDef* weldJointDef = new b2WeldJointDef();
	weldJointDef->bodyA = bodyObjectA;
	weldJointDef->bodyB = bodyObjectB;
	weldJointDef->collideConnected = false;
	weldJointDef->localAnchorA = localAnchorA;
	weldJointDef->localAnchorB = localAnchorB;
	weldJointDef->userData = &this->jointID;
	this->wJoint = (b2WeldJoint*)b2world->CreateJoint(weldJointDef);

	this->jointID = IB2Joint::idCount;
	IB2Joint::idCount++;
}


void IB2Joint::grabObject(b2World* b2world, b2Body* bodyObject, IPointF originPoint) {
	//create body cursor
	//create mouseJoint

	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->position.Set(originPoint.x, originPoint.y);
	//this->bodyDef->linearDamping = 0;

	this->body = b2world->CreateBody(bodyDef);
	this->body->SetUserData(this);


	b2MouseJointDef* jointMouseDef = new b2MouseJointDef();
	jointMouseDef->bodyA = this->body;
	jointMouseDef->bodyB = bodyObject;
	jointMouseDef->maxForce = 1000 * bodyObject->GetMass();
	jointMouseDef->target = b2Vec2(originPoint.x, originPoint.y);
	//jointMouseDef->target = bodyObject->GetPosition();
	jointMouseDef->collideConnected = false;
	//jointMouseDef->frequencyHz = 0.0f;
	jointMouseDef->dampingRatio = 1.0f;
	//jointMouseDef->dampingRatio = 0.3f;		//zele, zelatina :D
	//jointMouseDef->frequencyHz = 666.0f;

	//create the joint
	this->mJoint = (b2MouseJoint*)b2world->CreateJoint(jointMouseDef);
	//this->mj->
	this->mJoint->SetTarget(b2Vec2(originPoint.x, originPoint.y));


}

bool IB2Joint::tryGrabObject(b2World* b2world, b2Body* bodyObject, IPointF originPoint) {
	/*

			if(this->vecOfB2Dynamic->at(i)->isPointInside(this->GV->cursor->getSelectedLoc()) && this->GV->cursor->getCanInteractive()){
				this->GV->cursor->setCanInteractive(false);
				this->GV->cursor->grabObject(this->b2world, this->vecOfB2Dynamic->at(i)->getBody());
			}

	*/

	bool isInside = false;
	for (b2Fixture* f = bodyObject->GetFixtureList(); f; f = f->GetNext()) {
		if (f->TestPoint(b2Vec2(originPoint.x, originPoint.y))) {
			isInside = true;
			break;
		}
	}
	if (isInside) {
		this->grabObject(b2world, bodyObject, originPoint);
		return true;
	}

	return false;
}

void IB2Joint::releaseObject(b2World* b2world) {
	if (this->mJoint != NULL) {
		b2world->DestroyJoint(this->mJoint);
		this->mJoint = NULL;
	}
	if (this->body != NULL) {
		b2world->DestroyBody(this->body);
		this->body = NULL;
	}
}



