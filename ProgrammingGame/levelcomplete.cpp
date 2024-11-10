#include "levelcomplete.h"
#include <QPainter>
#include <QDebug>

levelcomplete::levelcomplete(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this),
    image(":/res/sprites/levelCompleted.png")
{
    // Seed random
    srand(time(NULL));

    // Create ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 50.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(10000.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, -10.0f);
    completeImage = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 20.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.4f;
    completeImage->CreateFixture(&fixtureDef);


    // Confetti
    confettiImg.load(":/res/tiles/amethyst_shard.png");
    confettiImg = confettiImg.transformed(QTransform().scale(1.5, 1.5));
    b2BodyDef confettiDef;
    confettiDef.type = b2_dynamicBody;
    confettiDef.position.Set(25.0f, 49.0f);

    b2PolygonShape confettiPoly;
    confettiPoly.SetAsBox(0.1f, 0.1f);

    b2FixtureDef confettiFixtureDef;
    confettiFixtureDef.shape = &confettiPoly;
    confettiFixtureDef.density = .5f;
    confettiFixtureDef.restitution = 0.55f;

    // Generate confetti
    for (int i = 0; i < CONFETTI_COUNT; i++) {

        b2Body* tempConfetti = world.CreateBody(&confettiDef);
        tempConfetti->CreateFixture(&confettiFixtureDef);
        confetti.push_back(tempConfetti);

    }

    connect(&timer, &QTimer::timeout, this, &levelcomplete::updateWorld);

}

levelcomplete::~levelcomplete()
{

}

void levelcomplete::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    b2Vec2 position = completeImage->GetPosition();
    painter.drawImage((position.x * 20), (position.y * 20), image);

    // Draw Confetti
    for (unsigned long i = 0; i < confetti.size(); i++) {
        b2Vec2 position = confetti.at(i)->GetPosition();
        painter.rotate(confetti.at(i)->GetAngle());
        painter.drawPixmap((position.x * 20), (position.y * 20), confettiImg);
        painter.resetTransform();
    }

    painter.end();
}


void levelcomplete::updateWorld()
{

    world.Step(1.0/60.0, 6, 2);
    update();

}

void levelcomplete::resetAnimation()
{
    b2Vec2 force(0, 10000);

    // Draw Random force confetti
    for (unsigned long i = 0; i < confetti.size(); i++) {

        confetti.at(i)->SetLinearVelocity(b2Vec2(0, 0));
        confetti.at(i)->SetAngularVelocity(0);
        confetti.at(i)->SetAwake(true);

        float randX = (rand() % 60) - 30;

        b2Vec2 confettiForce(0, 50);

        confetti.at(i)->SetTransform(b2Vec2(32.0f + randX, -35.0f - randX), 0);
        confetti.at(i)->ApplyForceToCenter(confettiForce, true);

    }

    completeImage->SetTransform(b2Vec2(14, -20.f), completeImage->GetAngle());
    completeImage->ApplyForceToCenter(force, true);
    timer.start(16);
}

void levelcomplete::stopAnimation()
{
    timer.stop();
}
