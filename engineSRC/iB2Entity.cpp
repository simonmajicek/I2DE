#include "iB2Entity.h"
#ifdef BOX2D_ENGINE_ON

float IB2Entity::box2Dratio = 100.0f;
unsigned int IB2Entity::idCount = 0;

IB2Entity::IB2Entity(b2World* b2world, IPointF originLoc, b2BodyType type){
	this->b2world = this->b2world;
	this->objectID = IB2Entity::idCount;
	IB2Entity::idCount++;
	
	this->bodyDef = new b2BodyDef();
	this->bodyDef->type = type;
	this->bodyDef->position.Set(originLoc.x, -originLoc.y);
	//this->bodyDef->allowSleep = true;
	this->body = b2world->CreateBody(this->bodyDef);
	this->setCollisionBehavior(CLASS_ENTITY, ENTITY_COLLISSON, COLLISSON_WITH_ENTITY);
	this->body->SetUserData(this);
}

IB2Entity::~IB2Entity(){
	if(this->body != NULL){
  		b2world->DestroyBody(this->body);
  		this->body = NULL;
	}
}

void IB2Entity::setCollisionBehavior(int classType, uint16 categoryBits, uint16 maskBits){
	this->classType = classType;
	this->categoryBits = categoryBits;
	this->maskBits = maskBits;
}

void IB2Entity::startContact(b2Contact *contact){
	if (this->onStartCallback) {this->onStartCallback();}
	//Nemazat, nechat jako vzor
	/*
	IndexB2Entity* tmp;
	snazim se ziskat 2.object
	if ((B2Entity*)contact->GetFixtureA()->GetBody()->GetUserData() == this) {
		tmp = (B2Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
	}
	else {tmp = (B2Entity*)contact->GetFixtureA()->GetBody()->GetUserData();}
	switch (tmp->getClassType()) {
		case CLASS_STATIC: {this->GV->musicBox->playInstance(2);break;}
	}
	*/
}

void IB2Entity::endContact(b2Contact *contact){if (this->onEndCallback) {this->onEndCallback();}}

void IB2Entity::preSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	if (this->onPreSolveCallback) {this->onPreSolveCallback();}
}

void IB2Entity::postSolve(b2Contact* contact, const b2ContactImpulse* impulse) {;
	if (this->onPostSolveCallback) {this->onPostSolveCallback();}
}

int IB2Entity::getClassType(){return this->classType;}

void IB2Entity::addShape(vector<b2Vec2> *vertices, float weight, float friction, float restitution){
   	vector<b2Vec2> *vertices2 = new vector<b2Vec2>;
   	*vertices2 = *vertices;
	b2Vec2 *tmpVertices2 = new b2Vec2[vertices2->size()];
	for(unsigned int i = 0; i < vertices2->size(); i++){
		tmpVertices2[i] = b2Vec2(vertices2->at(i).x, vertices2->at(i).y);
	}

	b2PolygonShape *shape = new b2PolygonShape();
	shape->Set(tmpVertices2, vertices2->size());

	b2FixtureDef *fixture = new b2FixtureDef();
	fixture->filter.categoryBits = this->getCategoryBits();
	fixture->filter.maskBits = this->getMaskBits();
	fixture->shape = shape;
	fixture->density = weight;
	fixture->friction = friction;
	fixture->restitution = restitution;
	this->body->CreateFixture(fixture);
}

void IB2Entity::addChainShape(vector<b2Vec2>* vertices, float weight, float friction, float restitution) {
	vector<b2Vec2>* vertices2 = new vector<b2Vec2>;
	*vertices2 = *vertices;
	b2Vec2* tmpVertices2 = new b2Vec2[vertices2->size()];
	for (unsigned int i = 0; i < vertices2->size(); i++) {
		tmpVertices2[i] = b2Vec2(vertices2->at(i).x, vertices2->at(i).y);
	}

	b2ChainShape* shape = new b2ChainShape();
	shape->CreateLoop(tmpVertices2, vertices2->size());

	b2FixtureDef* fixture = new b2FixtureDef();
	fixture->filter.categoryBits = this->getCategoryBits();
	fixture->filter.maskBits = this->getMaskBits();
	fixture->shape = shape;
	fixture->density = weight;
	fixture->friction = friction;
	fixture->restitution = restitution;
	this->body->CreateFixture(fixture);
}

void IB2Entity::addCircleShape(float radius, float weight, float friction, float restitution){
	b2CircleShape *shape = new b2CircleShape();
   	shape->m_p.Set(0.0f, 0.0f);		//pokud chci offset, musim upravit renderDebug metodu + isPointInside() + mozna dalsi?
   	shape->m_radius = radius;
	
	b2FixtureDef *fixture = new b2FixtureDef();
	fixture->filter.categoryBits = this->getCategoryBits();
	fixture->filter.maskBits = this->getMaskBits();
	fixture->shape = shape;
	fixture->density = weight;
	fixture->friction = friction;
	fixture->restitution = restitution;
	this->body->CreateFixture(fixture);
}

void IB2Entity::addBoxShape(float width, float height, float weight, float friction, float restitution, float offsetX, float offsetY){
	b2PolygonShape *shape = new b2PolygonShape();
	shape->SetAsBox(width, height, b2Vec2(offsetX, offsetY), 0.0f	);
	b2FixtureDef *fixture = new b2FixtureDef();
	fixture->filter.categoryBits = this->getCategoryBits();
	fixture->filter.maskBits = this->getMaskBits();
	fixture->shape = shape;
	fixture->density = weight;
	fixture->friction = friction;
	fixture->restitution = restitution;
	this->body->CreateFixture(fixture);
}

uint16 IB2Entity::getCategoryBits(){return this->categoryBits;}

uint16 IB2Entity::getMaskBits(){return this->maskBits;}

IPointF IB2Entity::getOriginLoc(){
	//y osa je otocena
	return IPointF(this->body->GetPosition().x, -this->body->GetPosition().y);
}

void IB2Entity::setAngleRad(float angleRad){this->body->SetTransform( body->GetPosition(), angleRad );}

float IB2Entity::getAngleRad() {return -body->GetAngle();}

void IB2Entity::setLocationOrigin(float originX, float originY){
	this->body->SetTransform(b2Vec2(originX, originY),body->GetAngle());
	this->body->SetLinearVelocity(b2Vec2(0.0f, 0.01f));
}

void IB2Entity::setLocationOrigin(float originX, float originY, float angleRad){
	this->body->SetTransform(b2Vec2(originX, originY), angleRad);
	this->body->SetLinearVelocity(b2Vec2(0.0f, 0.01f));
}

bool IB2Entity::isPointInsideBox2D(IPointF point){
	b2Vec2 tmpPoint = b2Vec2(point.x, -point.y);
	for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext()){
		if (f->TestPoint(tmpPoint)){return true;}
	}
	return false;
}

void IB2Entity::setLinearVelocity(b2Vec2 vel){this->body->SetLinearVelocity(vel);}

void IB2Entity::setDensity(float density){
	for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext()){
	  f->SetDensity(density);
	}
	this->body->ResetMassData();
}

void IB2Entity::renderDebugBox2D(){
	IPointF tmpOrigin1;
	IPointF tmpOrigin2;
	float angle = -body->GetAngle();
	
	ALLEGRO_COLOR color = al_map_rgb(0, 255, 0);
	
	b2Vec2 tmpPosCenter = this->body->GetPosition();
	for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext()){
		b2Shape *shape = f->GetShape();
		//e_circle = 0, e_edge = 1, e_polygon = 2, e_chain = 3, e_typeCount = 4
		if(shape->GetType() == 2 ){	
			for(int i=0; i<((b2PolygonShape*)shape)->GetVertexCount(); i++){
				b2Vec2 p1 = ((b2PolygonShape*)shape)->GetVertex(i);
				b2Vec2 p2 = ((b2PolygonShape*)shape)->GetVertex( (i+1>=(((b2PolygonShape*)shape)->GetVertexCount()))?(0):(i+1) );
				
				b2Vec2 p;
				float angle = body->GetAngle();
				p.x = cos(angle) * (p1.x) - sin(angle) * (p1.y);
				p.y = sin(angle) * (p1.x) + cos(angle) * (p1.y);
				p1 = p;
				p.x = cos(angle) * (p2.x) - sin(angle) * (p2.y);
				p.y = sin(angle) * (p2.x) + cos(angle) * (p2.y);
				p2 = p;
				p = body->GetPosition();
				
				tmpOrigin1.x = (p1.x + p.x) * IB2Entity::box2Dratio;
				tmpOrigin1.y = (-p1.y - p.y) * IB2Entity::box2Dratio;
				tmpOrigin2.x = (p2.x + p.x) * IB2Entity::box2Dratio;
				tmpOrigin2.y = (-p2.y - p.y) * IB2Entity::box2Dratio;
				
				al_draw_line(tmpOrigin1.x, tmpOrigin1.y, tmpOrigin2.x, tmpOrigin2.y, color, 1.0f);
			}
		}
		if(shape->GetType() == 0 ){
			al_draw_circle(this->getOriginLoc().x * IB2Entity::box2Dratio, this->getOriginLoc().y * IB2Entity::box2Dratio, shape->m_radius * IB2Entity::box2Dratio, color, 1.0f);
		}
		if (shape->GetType() == 3) {
			for (int i = 0; i < ((b2ChainShape*)shape)->GetChildCount(); i++) {
				b2EdgeShape edge;
				((b2ChainShape*)shape)->GetChildEdge(&edge, i);
				b2Vec2 p1 = edge.m_vertex0;
				b2Vec2 p2 = edge.m_vertex1;
				
				b2Vec2 p;
				float angle = body->GetAngle();
				p.x = cos(angle) * (p1.x) - sin(angle) * (p1.y);
				p.y = sin(angle) * (p1.x) + cos(angle) * (p1.y);
				p1 = p;
				p.x = cos(angle) * (p2.x) - sin(angle) * (p2.y);
				p.y = sin(angle) * (p2.x) + cos(angle) * (p2.y);
				p2 = p;
				p = body->GetPosition();

				tmpOrigin1.x = (p1.x + p.x) * IB2Entity::box2Dratio;
				tmpOrigin1.y = (-p1.y - p.y) * IB2Entity::box2Dratio;
				tmpOrigin2.x = (p2.x + p.x) * IB2Entity::box2Dratio;
				tmpOrigin2.y = (-p2.y - p.y) * IB2Entity::box2Dratio;

				al_draw_line(tmpOrigin1.x, tmpOrigin1.y, tmpOrigin2.x, tmpOrigin2.y, color, 2.0f);
			}
		}
	}
}

void IB2Entity::bindStart(std::function<void()> func) {this->onStartCallback = func;}
void IB2Entity::bindEnd(std::function<void()> func) {this->onEndCallback = func;}
void IB2Entity::bindPreSolve(std::function<void()> func) {this->onPreSolveCallback = func;}
void IB2Entity::bindPostSolve(std::function<void()> func) {this->onPostSolveCallback = func;}

//FASADA + Bonus funkce --------------------------------------------------------------------------------------
IPointF IB2Entity::cursorOriginToBox2D(IPointF cursorOrigin) {return IPointF(cursorOrigin.x / IB2Entity::box2Dratio, cursorOrigin.y / IB2Entity::box2Dratio);}
void IB2Entity::debugFly(IPointF originPoint) {
	b2Vec2 tmp;
	b2Vec2 target;
	target.x = originPoint.x;
	target.y = originPoint.y;
	b2Vec2 vel;// = target - tmp;
	tmp.x = this->getOriginLoc().x;
	tmp.y = this->getOriginLoc().y;
	vel.x = target.x - tmp.x;
	vel.y = target.y - tmp.y;

	vel *= 1.0f;
	this->setLinearVelocity(vel);

}

#endif