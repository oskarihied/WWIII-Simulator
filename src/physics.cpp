#include "physics.hpp"
#include <box2d/box2d.h>
#include <iostream>

Physics::Physics() : simulationWorld_(b2World(b2Vec2(0.0f, -9.81f))) {};

void Physics::SimulateWorld(float simulationStep) {
    
    // Update simulation Objects locations
    simulationWorld_.Step(simulationStep, 1, 1);

    // std::cout << "testi" << std::endl;
    // printf("test\n");
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

bool Physics::AddBox(Box box) {
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
};