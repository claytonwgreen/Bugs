#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir) : GameWorld(assetDir) {}
    int getCurrentTicks() const;
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    bool isRock(int x, int y);
    bool isFood(int x, int y, int i);
    void addActor(int x, int y, Actor* p);
    Actor* findFood(int x, int y);
    void stun(int x, int y);
    Actor* getRandomInsect(int x, int y, Actor* p, int colony = -1);
    void poison(int x, int y);
    void addAnt(int colony);
    bool smellDanger(Ant* a);
    bool smellPheromoneAhead(Ant* a);
    Actor * findPheromone(Ant* a);
    ~StudentWorld()
    {
        cleanUp();
    }
private:
    std::vector<Actor*> m_ActorList [VIEW_WIDTH][VIEW_HEIGHT]; // 2D array of vectors of pointers to actors
    int ticks;
    int winner = -1;
    const int antHill0 = 0, antHill1 = 1, antHill2 = 2, antHill3 = 3;
    int antHill0Num = -1, antHill1Num = -1, antHill2Num = -1, antHill3Num = -1;
    string names[4];
    int numOfAnthills;
};


#endif // STUDENTWORLD_H_
