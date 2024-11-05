#include "physics.hpp"
#include <box2d/box2d.h>
#include <iostream>

Physics::Physics() : simulationWorld_(b2World(b2Vec2(0.0f, -9.81f))) {};

void Physics::SimulateWorld(float simulationStep) {
    
    // Update simulation Objects locations
    simulationWorld_.Step(simulationStep, 1, 1);

    // Verify that all entities match simulation bodies
    if (b2bodies_.size() != entities_.size()) {
        throw std::invalid_argument("Vectors entities and b2bodies must be the same size.");
    }

    // Update entity location from simulation bodies locations
    for (uint i = 0; i < entities_.size(); i++) {
        b2Vec2 pos = b2bodies_[i]->GetPosition();
        entities_[i].MoveTo(Pos(pos.x, pos.y));
        std::cout << "x: " << pos.x << " y: " << pos.y << std::endl;
    }
};

b2Body* Physics::AddBox(Box box) {
    entities_.push_back(box);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(box.GetPos().GetX(), box.GetPos().GetY());
    b2Body* dynamicBody = simulationWorld_.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(box.GetWidth() / 2.0, box.GetHeight() / 2.0);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    dynamicBody->CreateFixture(&fixtureDef);
    b2bodies_.push_back(dynamicBody);
    return dynamicBody;
};

b2Body* Physics::AddGround(Ground ground) {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = simulationWorld_.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    b2bodies_.push_back(groundBody);
    entities_.push_back(ground);
    return groundBody;
};

void Physics::SetVelocity(b2Body* body, float xVel, float yVel) {
    body->SetLinearVelocity(b2Vec2(xVel, yVel));
};

void Physics::SetPosition(b2Body* body, float xPos, float yPos, float rotation) {
    body->SetTransform(b2Vec2(xPos, yPos), rotation);
};

