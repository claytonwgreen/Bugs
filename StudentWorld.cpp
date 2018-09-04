#include "StudentWorld.h"
#include "Field.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "Compiler.h"
#include "GraphObject.h"
using namespace std;


string setDisplay(int ticks, int antArr[], string names[], int winner, int NumOfPlayers);//declaring function

GameWorld * createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

int StudentWorld::getCurrentTicks() const
{
    return ticks;
}

int StudentWorld::init()
{
    //create two arrays that are use to store the x and y coordinates where anthills should be created
    int anthillX[4];
    int anthillY[4];
    
    int numberOfAnthills = 0;
    
        string name = getFieldFilename();
        Field fld;
        string issues = "";
    
        //load files and a string where error can be returned if there is an error
        Field::LoadResult result = fld.loadField(name, issues);
    
        if (result == Field::load_fail_file_not_found)//return the error if there is one for no file
        {
            return GWSTATUS_PLAYER_WON;
        }
        else if (result == Field::load_fail_bad_format)//return the error if there is one for bad formatting in the file
        {
            return GWSTATUS_LEVEL_ERROR;
        }
        else {//if no errors then loop through all points on the filed file
            for (int i = 0; i < VIEW_WIDTH; i++)
            {
                for (int j = 0; j < VIEW_HEIGHT; j++)
                {
                    Field::FieldItem item = fld.getContentsOf(i, j);
                    switch (item)//checking each space to see what is supposed to be there, if anything, and add that actor to the vector for those coordinates (anthills dealt with after)
                    {
                        case Field::grasshopper:
                            m_ActorList[j][i].push_back(new BabyGrasshopper(IID_BABY_GRASSHOPPER, i, j, this));
                            break;
                        case Field::rock:
                            m_ActorList[j][i].push_back(new Pebble(IID_ROCK, i, j, this));
                            break;
                  
                        case Field::food:
                            m_ActorList[j][i].push_back(new Food(IID_FOOD, i, j, this));
                            break;
                        case Field::water:
                            m_ActorList[j][i].push_back(new WaterPool(IID_WATER_POOL, i, j, this));
                            break;
                        case Field::poison:
                            m_ActorList[j][i].push_back(new Poison(IID_POISON, i, j, this));
                            break;
                        case Field::anthill0:
                            anthillX[0] = i;
                            anthillY[0] = j;
                            numberOfAnthills++;
                            break;
                        case Field::anthill1:
                            anthillX[1] = i;
                            anthillY[1] = j;
                            numberOfAnthills++;
                            break;
                        case Field::anthill2:
                            anthillX[2] = i;
                            anthillY[2] = j;
                            numberOfAnthills++;
                            break;
                        case Field::anthill3:
                            anthillX[3] = i;
                            anthillY[3] = j;
                            numberOfAnthills++;
                            break;

                    }
                }
            }
        }
    
    //create all the compilers, pointer to compilers, and the vector of strings for the filenames loaded in as bug programs
    Compiler *compilerForAnthill0, *compilerForAnthill1, *compilerForAnthill2, *compilerForAnthill3;
    Anthill *anthill0, *anthill1, *anthill2, *anthill3;
    std::vector<std::string> fileNames = getFilenamesOfAntPrograms();
    std::string error;
    
    
    // compile the source file... If the compile function returns false, there was a syntax error during compilation and the program returns the error
    for(int k = 0; k < numberOfAnthills; k++)
    {
        switch (k) {
            case 0:
            {
                compilerForAnthill0 = new Compiler;
                if ( ! compilerForAnthill0->compile(fileNames[0], error) )
                {
                    setError(fileNames[0] + " " + error);
                    return GWSTATUS_LEVEL_ERROR;
                }
                break;
            }
            case 1:
            {
                compilerForAnthill1 = new Compiler;
                if ( ! compilerForAnthill1->compile(fileNames[1], error) )
                {
                    setError(fileNames[1] + " " + error);
                    return GWSTATUS_LEVEL_ERROR;
                }
                break;
            }
            case 2:
            {
                compilerForAnthill2 = new Compiler;
                if ( ! compilerForAnthill2->compile(fileNames[2], error) )
                {
                    setError(fileNames[2] + " " + error);
                    return GWSTATUS_LEVEL_ERROR;
                }
                break;
            }
            case 3:
            {
                compilerForAnthill3 = new Compiler;
                if ( ! compilerForAnthill3->compile(fileNames[3], error) )
                {
                    setError(fileNames[3] + " " + error);
                    return GWSTATUS_LEVEL_ERROR;
                }
                break;
            }
        }
    }
    
    //loop through the filenames vector and for each file loaded add an anthill with the poionter to that compiler and the coordinates of where the field file said this anthill should go as stored in the anthillX and anthillY arrays
    for (int k = 0; k < numberOfAnthills; k++)
    {
        switch (k)
        {
            case 0:
                anthill0 = new Anthill(0, compilerForAnthill0, IID_ANT_HILL, anthillX[0], anthillY[0], this);
                names[0] = compilerForAnthill0 -> getColonyName();
                antHill0Num = 0;
                break;
            case 1:
                anthill1 = new Anthill(1, compilerForAnthill1, IID_ANT_HILL, anthillX[1], anthillY[1], this);
                names[1] = compilerForAnthill1 -> getColonyName();
                antHill1Num = 0;
                break;
            case 2:
                anthill2 = new Anthill(2, compilerForAnthill2, IID_ANT_HILL, anthillX[2], anthillY[2], this);
                names[2] = compilerForAnthill2 -> getColonyName();
                antHill2Num = 0;
                break;
            case 3:
                anthill3 = new Anthill(3, compilerForAnthill3, IID_ANT_HILL, anthillX[3], anthillY[3], this);
                names[3] = compilerForAnthill3 -> getColonyName();
                antHill3Num = 0;
                break;
        }
    }

    //if-ladder for checking adding the anthills. Must only add how many files are loaded so first case is if 4 were loaded and last case is if only 1 was loaded
    if (numberOfAnthills == 4)
    {
        addActor(anthillX[0], anthillY[0], anthill0);
        addActor(anthillX[1], anthillY[1], anthill1);
        addActor(anthillX[2], anthillY[2], anthill2);
        addActor(anthillX[3], anthillY[3], anthill3);
    }
    else if (numberOfAnthills == 3)
    {
        addActor(anthillX[0], anthillY[0], anthill0);
        addActor(anthillX[1], anthillY[1], anthill1);
        addActor(anthillX[2], anthillY[2], anthill2);
    }
    else if (numberOfAnthills == 2)
    {
        addActor(anthillX[0], anthillY[0], anthill0);
        addActor(anthillX[1], anthillY[1], anthill1);
    }
    else if (numberOfAnthills == 1)
    {
        addActor(anthillX[0], anthillY[0], anthill0);
    }
    
    numOfAnthills = numberOfAnthills;//for use in move()
    return GWSTATUS_CONTINUE_GAME;//if there were no errors then let the game begin
}

int StudentWorld::move()
{
    //loop through entire actorlist and store the coordinates of each actor before if is asked to do something. then ask it to do something. then check coordiantes again and if they have changed then store the pointer to that object in the vector at the new coordinates and delete the old pointer from the vector at the old coordinates. set checked to true so that no object is asked to do something twice in one tick
    for (int x = 0; x < VIEW_WIDTH; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT; y++)
        {
            for (int k = 0; k < m_ActorList[y][x].size(); k++)
            {
                if (!m_ActorList[y][x][k] -> getChecked())
                {
                    int oldX = m_ActorList[y][x][k] -> getX();
                    int oldY = m_ActorList[y][x][k] -> getY();
                    
                    m_ActorList[y][x][k] -> doSomething();
                    
                    int newX = m_ActorList[y][x][k] -> getX();
                    int newY = m_ActorList[y][x][k] -> getY();
                    
                    if (oldX != newX || oldY != newY)
                    {
                        Actor * temp = m_ActorList[y][x][k];
                        m_ActorList[y][x][k] -> setChecked(true);
                        m_ActorList[y][x].erase(m_ActorList[y][x].begin() + k);
                        m_ActorList[newY][newX].push_back(temp);
                        k--;
                    }
                }
            }
        }
    }
    
    //loop through actorList and set checked to false so that all objects are checked next tick. then delete any objects that are now dead and remove their pointer from the vector
    for (int x = 0; x < VIEW_WIDTH; x++)
    {
        for (int y = 0; y < VIEW_HEIGHT; y++)
        {
            for (int k = 0; k < m_ActorList[x][y].size(); k++)
            {
                m_ActorList[x][y][k] -> setChecked(false);
                if (m_ActorList[x][y][k] -> isAlive() == false)
                {
                    delete m_ActorList[x][y][k];
                    m_ActorList[x][y].erase(m_ActorList[x][y].begin() + k);
                }
            }
        }
    }
    
    //increment ticks
    ticks++;
    
    int n_ants[4] = {antHill0Num,antHill1Num,antHill2Num,antHill3Num};//create an array with the numbers of the anthills that can be passed into the setGameStatText function
    
    setGameStatText(setDisplay(ticks, n_ants, names, winner, numOfAnthills));//set the text with updated game stats
    
    if (ticks == 2000)//if the simulation is over then check to see if there is a winner. If there is then return the name declared in that bug file. otherwise return that there is no winner
    {
        if (winner != -1)
        {
            setWinner(names[winner]);
            return GWSTATUS_PLAYER_WON;
        }
            
        return GWSTATUS_NO_WINNER;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}


void StudentWorld::cleanUp()
{
    //loop through entire student list and call delete on the pointers in every vector and then pop the pointer off of the vector
    for (int y = 0; y < VIEW_WIDTH; y++)
    {
        for (int x = 0; x < VIEW_HEIGHT; x++)
        {
            while (!m_ActorList[y][x].empty())
            {
                delete m_ActorList[y][x].back();
                m_ActorList[y][x].back() = nullptr;
                m_ActorList[y][x].pop_back();
            }
        }
    }
    
}

void StudentWorld::addActor(int x, int y, Actor* p)
{//add the actor pointer to the back of the vector at the coordinates indeicated
    m_ActorList[y][x].push_back(p);
}

bool StudentWorld::isRock(int x, int y)
{
        if (x >= VIEW_WIDTH || y >= VIEW_HEIGHT || x <= 0 || y <= 0){ // if it's out of bounds it is treated as a rock because adult grasshoppers can jump up to 10 units which can sometimes be out of the array bounds and so it must think that all those locations are occupied by rocks
            return true;
        }
        
        for (int i = 0; i < m_ActorList[y][x].size(); i++)
        {//loop through the vector at the coordinates and see if any of the objects are movable meaning they are a rock
            if (m_ActorList[y][x][i] != nullptr)
            {
                if (!m_ActorList[y][x][i] -> isMovable())
                {
                    return true;
                }
            }
        }
        return false;
    
}


Actor * StudentWorld::findFood(int x, int y) 
{
    //loop through the vector at the coordinates indicated and if an object is edible then it is food. return the pointer to that food if there is food and the nullptr if there is none
    for (int i = 0; i < m_ActorList[y][x].size(); i++)
    {
        if (m_ActorList[y][x][i] != nullptr)
        {
            if(m_ActorList[y][x][i]->isEatable())
            {
                return m_ActorList[y][x][i];
            }
        }
    }
    return nullptr;
}

Actor * StudentWorld::findPheromone(Ant* a)
{
    //loop through the vector at the coordinates indicated. for every object in the vector dynamic cast it and see if it is a pheromone. if it is a pheromone then check to make sure it is from the saem colony. if it is then return the pointer to it. otherwise return nullptr
    for (int i = 0; i < m_ActorList[a->getY()][a->getX()].size(); i++)
    {
        if (m_ActorList[a->getY()][a->getX()][i] != nullptr)
        {
            Pheromone* r = dynamic_cast<Pheromone*>(m_ActorList[a->getY()][a->getX()][i]);
            if(r != nullptr && r->getColonyNum() == a->getColonyNum())
            {
                return m_ActorList[a->getY()][a->getX()][i];
            }
        }
    }
    return nullptr;
}

void StudentWorld::stun(int x, int y)
{
        //loop through the vector at the coordiantes provided. if the object being checked is stunnable, then check to see if the object is wet meaning it has already been stunned by this water pool without leabing it. if it is not wet, then set wet to true and stun the object for 2 more turns.
        for (int i = 0; i < m_ActorList[y][x].size(); i++)
        {
            if(m_ActorList[y][x][i]->isStunablePoisonable())
            {
                Active* t = dynamic_cast<Active*>(m_ActorList[y][x][i]);
                if(t != nullptr)
                {
                    if (! t->getWet())
                    {
                        t->setWet(true);
                        t->setStunnedAsleep(t->getStunnedAsleep() + 2);
                    }
                }
            }
        }
}


void StudentWorld::poison(int x, int y)
{
    //loop through the vector at the given point. dynamic cast it as an active and if it is an active then decrement its energy by 150 and then check if that active is now dead.
    for (int i = 0; i < m_ActorList[y][x].size(); i++)
    {
        if(m_ActorList[y][x][i]->isStunablePoisonable())
        {
            Active* t = dynamic_cast<Active*>(m_ActorList[y][x][i]);
            if(t != nullptr)
            {
                t->setEnergy(t->getEnergy() - 150);
                t->checkDead();
            }
        }
    }
}


Actor* StudentWorld::getRandomInsect(int x, int y, Actor* p, int colony)
{
    //loop through the vector at the given coordinates. if the object found is bitable and it is not the object that is calling the function, then check to see if it is an ant. if it is an ant, then check to colony to see if it is the same as the ant calling this function, becuase ants cannot bite ants from its own colony. if the object is bitable and not an ant, or is an ant from another colony, then add that object to a temporary vector. then calculate a random number from 0 to the size of the temporary vector and return a pointer to the object in that position of the vector. if the vector is empty then return the nullptr.
    std::vector<Actor*> v;
    for (int i = 0; i < m_ActorList[y][x].size(); i++)
    {
        if (m_ActorList[y][x][i] != nullptr)
        {
            if (m_ActorList[y][x][i] -> isBitable() && m_ActorList[y][x][i] != p)
            {
                Ant* option = dynamic_cast<Ant*>(m_ActorList[y][x][i]);
                Ant* original = dynamic_cast<Ant*>(p);
                if(option == nullptr)
                    v.push_back(m_ActorList[y][x][i]);
                else
                {
                    if(original!=nullptr)
                    {
                        if(!(option->getColonyNum() == original->getColonyNum()))
                        {
                            v.push_back(m_ActorList[y][x][i]);
                        }
                    }
                }
            }
            
        }
    }
    if (v.size() == 0)
    {
        return nullptr;
    }
    int rand = randInt(0, v.size() - 1); // size - 1 stays in bounds
    return v[rand];
}

void StudentWorld::addAnt(int colony)
{
    //determine the anthill that should add an ant. then it increments the count of ants produced for that anthill and checks to see if that anthill has produced more ants than all others. if it has then set winner equal to that anthill
    if (colony == antHill0)
    {
        antHill0Num ++;
        if (ticks > 5 && antHill0Num > antHill1Num && antHill0Num > antHill2Num && antHill0Num > antHill3Num)
            winner = 0;
    }
    else if (colony == antHill1)
    {
        antHill1Num ++;
        if (ticks > 5 && antHill1Num > antHill0Num && antHill1Num > antHill2Num && antHill1Num > antHill3Num)
            winner = 1;
    }
    else if (colony == antHill2)
    {
        antHill2Num ++;
        if (ticks > 5 && antHill2Num > antHill1Num && antHill2Num > antHill0Num && antHill2Num > antHill3Num)
            winner = 2;
    }
    else if (colony == antHill3)
    {
        antHill3Num ++;
        if (ticks > 5 && antHill3Num > antHill1Num && antHill3Num > antHill2Num && antHill3Num > antHill0Num)
            winner = 3;
    }
}

bool StudentWorld::smellDanger(Ant* a)
{
    //create pointer to vector of actors that can be used to point to whichever square the ant is facing and find out which coordinate should be used based on the ants direction
    vector<Actor*> pos;
    if (a -> getDirection() == Active::Direction::up)
    {
        pos = m_ActorList[a -> getY() + 1][a -> getX()];
    }
    else if (a -> getDirection() == Active::Direction::down)
    {
        pos = m_ActorList[a -> getY() - 1][a -> getX()];
    }
    else if (a -> getDirection() == Active::Direction::left)
    {
        pos = m_ActorList[a -> getY()][a -> getX() - 1];
    }
    else if (a -> getDirection() == Active::Direction::right)
    {
        pos = m_ActorList[a -> getY()][a -> getX() + 1];
    }
    //loop through all actors in that vector and if one is dangerous, then check if it is an ant and if it is, then check if its from the same colony. if it is an ant from the same colony then continue searching the vector and if it is an ant from another colony or it is a different active then return true. if none are found return false.
    for (int k = 0; k < pos.size(); k++)
    {
        if (pos[k]->isDangerous())
        {
            Ant* b = dynamic_cast<Ant*>(pos[k]); //changes to ant
            if(b != nullptr)// if it is an ant
            {
                if(b -> getColonyNum() == a -> getColonyNum()) // if they are in the same colony, it is not dangerous
                    continue;
                else
                    return true; // if it is in another colony, it is dangerous
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::smellPheromoneAhead(Ant* a)
{//exact same implementation as smell danger except it checks the vector to see if the object is a pheromone and if if it is a pheromone then it checks if its from the saem colony and if it is then it returns true. otherwise it keeps looking through the vector and if it doesnt find any pheromones from the same colony in that vector then it returns false
    vector<Actor*> pos;
    if (a -> getDirection() == Active::Direction::up)
    {
        pos = m_ActorList[a -> getY() + 1][a -> getX()];
    }
    else if (a -> getDirection() == Active::Direction::down)
    {
        pos = m_ActorList[a -> getY() - 1][a -> getX()];
    }
    else if (a -> getDirection() == Active::Direction::left)
    {
        pos = m_ActorList[a -> getY()][a -> getX() - 1];
    }
    else if (a -> getDirection() == Active::Direction::right)
    {
        pos = m_ActorList[a -> getY()][a -> getX() + 1];
    }
    
    for (int k = 0; k < pos.size(); k++)
    {
        Pheromone* p = dynamic_cast<Pheromone*>(pos[k]);
        if (p != nullptr && p->getColonyNum() == a->getColonyNum())
            return true;
    }
    return false;
}


string setDisplay(int ticks, int antArr[], string names[], int winner, int numOfPlayers)
{
    //creates a stringstream that first displays the ticks counting down from 2000 and then shows all names of the ant colonies and how many ants its anthill has produced. it places an * next to the anthill that is in the lead.
    ostringstream oss;
    oss << "Ticks:";
    oss << setw(5) << (2000-ticks);
    oss << " -  ";
    for(int i = 0; i< numOfPlayers ;i++)
    {
        string player;
        player = player + names[i];
        if(i == winner)
        {
            player = "*" + player;
        }
        string num;
        if(antArr[i]<10)
            num = "0" + to_string(antArr[i]);
        else
            num = to_string(antArr[i]);
        
        player = player + ": " + num;
        
        if(i<numOfPlayers-1)
            oss << player << "  ";
        else
            oss << player;
    }
    return oss.str();
}




