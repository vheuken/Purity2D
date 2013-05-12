#include <iostream>
#include <Box2D/Box2D.h>

int main()
{
	b2Vec2 gravity;
	gravity.Set(0, -5);
	b2World * world = new b2World(gravity);
    b2BodyDef bodyDef;
	b2Body* dynamicBody;

	bodyDef.bullet = true;
	bodyDef.linearVelocity = gravity;

	dynamicBody = world->CreateBody(&bodyDef);

	std::cout << dynamicBody->GetLinearVelocity().x;
	std::cout << " ";
	std::cout << dynamicBody->GetLinearVelocity().y;
	std::cout << std::endl;

	return 0;
}