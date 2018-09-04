#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "Compiler.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
/*
 
                                    Graph Object
                                          |
                                        Actor
 
                Energy                                      pools of water, poison, pebbles (non-energy)
                   |
       food, pheromones, anthills, Active
                                      |
                                ants    baby grasshoppers
                                                |
                                        adult grasshoppers
 
 */


class StudentWorld;

class Actor : public GraphObject {
public:
    Actor(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    virtual void doSomething() = 0;
    virtual ~Actor();
    bool getChecked();
    bool setChecked(bool v);
    bool isMovable();
    void setMovable(bool v);
    StudentWorld * getWorld() ;
    bool isAlive();
    void setIsAlive(bool b);
    bool isEatable();
    void setIsEatable(bool b);
    bool isStunablePoisonable();
    void setIsStunablePoisonable(bool b);
    bool isBitable();
    void setIsBitable(bool b);
    bool isDangerous();
    void setIsDangerous(bool b);
private:
    bool m_checked;
    bool m_isMoveable;
    StudentWorld * m_world;
    bool m_isEatable;
    bool m_isStunablePoisonable;
    bool m_isBitable;
    bool m_isAlive;
    bool m_isDangerous;

};


// ENERGY
class Energy : public Actor
{
public:
    Energy(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    virtual void setEnergy(int num);
    int getEnergy();
    bool checkDead();
    virtual bool eat(int amount);
private:
    int m_energy = 0;
};

class Anthill : public Energy
{
public:
    Anthill(int colonyNum, Compiler* compilerForEntrant, int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 2);
    virtual ~Anthill();
    void doSomething();
    int getColonyNum();
    Compiler* getPointerToCompiler();
private:
    int m_colNum;
    Compiler* m_pointerToCompiler;
};

class Active : public Energy
{
public:
    Active(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    int getStunnedAsleep();
    void setStunnedAsleep(int num);
    void setRandomDir();
    void diedSoAddFood();
    bool move();
    void setWet(bool v);
    bool getWet();
    bool bite(int amount);
    void addFood(int amount);
private:
    int m_stunnedAsleep;
    bool m_wet;
};

class BabyGrasshopper : public Active
{
public:
    BabyGrasshopper(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void doSomething();
    void setMoveDis(int n);
    int getMoveDis();
private:
    int m_moveDist;
};

class Ant : public Active
{
public:
    Ant(int homeX, int homeY, int antColonyNum, Compiler* pointerToCompiler, int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    virtual void doSomething();
    virtual bool eat();
    int getColonyNum();
    Compiler* getPointerToCompiler();
    void setWasBitten(bool b);
    void addPheromone();
private:
    int m_antColonyNum;
    int m_foodCarrying;
    Compiler* m_pointerToCompiler;
    int m_instructionCounter;
    bool m_wasBlocked;
    bool m_wasBitten;
    int m_lastRand;
    int m_homeX, m_homeY;
};

class AdultGrasshopper : public BabyGrasshopper
{
public:
    AdultGrasshopper(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void doSomething();
private:
};

class Food : public Energy
{
public:
    Food(int imgID, int x, int y, StudentWorld* studentWorld, Direction dir = right, int depth =2);
    void doSomething();
private:
};

class Pheromone : public Energy
{
public:
    Pheromone(int imgID, int ColonyNum, int x, int y, StudentWorld* studentWorld, Direction dir = right, int depth = 2);
    void doSomething();
    int getColonyNum();
private:
    int m_colonyNum;
};





// NON ENERGY
class Pebble : public Actor
{
public:
    Pebble(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir = right, int depth = 1);
    void doSomething();
private:
};

class Poison : public Actor
{
public:
    Poison(int imgID, int x, int y, StudentWorld* studentWorld, Direction dir = right, int depth = 2);
    void doSomething();
};

class WaterPool : public Actor
{
public:
    WaterPool(int imgID, int x, int y, StudentWorld* studentWorld, Direction dir = right, int depth = 2);
    void doSomething();
};


#endif // ACTOR_H_
