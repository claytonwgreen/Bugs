#include "Actor.h"
#include "StudentWorld.h"

/*
 
                    Graph Object
                        Actor
            Energy												NonEnergy (pebbles+)
 food+					Active								pools of water+ & poison+
 pheromones+   	  	ants   baby grasshoppers+
 anthills				   adult grasshoppers+
 
 */

/*
 
 isEatable: Food
 isBitable: Ant, BabyGrasshopper, AdultGrasshopper
 isStunablePoisonable: Ant, BabyGrasshopper
 isAlive: ALL
 isChecked: ALL     //for making sure an actor gets its dosomething called once per tick
 isMovaeable: all but rock
 isDangerous: poison, grasshoppers, ants
 */


//ACTOR
Actor::Actor(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : GraphObject(imgID, x, y)
{
    m_world = studentWorld;             //initialize all member variable to their common state
    m_isMoveable = true;
    m_isAlive = true;
    m_isBitable = false;
    m_isEatable = false;
    m_isStunablePoisonable = false;
    m_checked = false;
    m_isDangerous = false;
}


Actor::~Actor()
{}

bool Actor::getChecked()
{
    return m_checked;
}

bool Actor::setChecked(bool v)
{
    m_checked = v;
    return true;
}

bool Actor::isMovable()
{
    return m_isMoveable;
}

void Actor::setMovable(bool v)
{
    m_isMoveable = v;
}

StudentWorld * Actor::getWorld()
{
    return m_world;
}

void Actor::setIsAlive(bool b)
{
    m_isAlive = b;
}

bool Actor::isAlive()
{
    return m_isAlive;
}

bool Actor::isEatable()
{
    return m_isEatable;
}

void Actor::setIsEatable(bool b)
{
    m_isEatable = b;
}
bool Actor::isStunablePoisonable()
{
    return m_isStunablePoisonable;
}
void Actor::setIsStunablePoisonable(bool b)
{
    m_isStunablePoisonable = b;
}
bool Actor::isBitable()
{
    return m_isBitable;
}
void Actor::setIsBitable(bool b)
{
    m_isBitable = b;
}

bool Actor::isDangerous()
{
    return m_isDangerous;
}

void Actor::setIsDangerous(bool b)
{
    m_isDangerous = b;
}


// ENERGY
Energy::Energy(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Actor(imgID, x, y, studentWorld)
{}

void Energy::setEnergy(int num)
{
    m_energy = num;
}

int Energy::getEnergy()
{
    return m_energy;
}

bool Energy::eat(int amount)
{
    if (getWorld() -> findFood(getX(), getY()) != nullptr)//called studentworld's findFood function which returns actor pointer to the food object on a square if there is one
    {
        Food* h = dynamic_cast<Food*>(getWorld() -> findFood(getX(), getY()));//dynamic cast the actor pointer to make it a food pointer so you can call energy functions which cant be called by any actor
        if (h -> getEnergy() > amount)//check if the insect trying to eat will eat all energy left in the food object or not
        {
            h -> setEnergy(h -> getEnergy() - amount);//if not decrease food energy by amount and increase the insect calling eat()'s energy by amount
            setEnergy(getEnergy() + amount);
            return true;
        }
        else if (h -> getEnergy() > 0 && h -> getEnergy() <= amount)//if so increase the insect calling eat()'s energy to however much energy is left in the food and set the food to dead to get cleaned up
        {
            setEnergy(getEnergy() + h -> getEnergy());
            h -> setEnergy(0);
            h -> setIsAlive(false);
            return true;
        }
    }
    return false;
}

bool Energy::checkDead()//function used in almost all characters to see if their energy has gotten <= 0
{
    if (getEnergy() <= 0 && isAlive())
    {
        setIsAlive(false);
        Active* a = dynamic_cast<Active*>(this);//if the the actor is an active then drop 100 food (carcus)
        if (a != nullptr)
            a->addFood(100);
        return true;
    }
    return false;
}

//ANTHILL

Anthill::Anthill(int colonyNum, Compiler* compilerForEntrant, int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Energy(imgID, x, y, studentWorld)
{
    setEnergy(8999);        //set all variables
    m_colNum = colonyNum;
    m_pointerToCompiler = compilerForEntrant;
}

Anthill::~Anthill()
{
    delete m_pointerToCompiler;//must delete the dynamically allocated compiler made in compiler class
}


void Anthill::doSomething()
{
    setEnergy(getEnergy() - 1); //decreases its hit points by 1 unit
    
    if (checkDead())
    { // the anthill’s hit points reaches zero units, then
        return; // must immediately return
    }
    
    // eat
    if (eat(10000))
    { // if there's food and it eats
        return; // immediately return
    }
    
    // produce ants
    if (getEnergy() >= 2000){ // checks to see if it has enough energy - at least 2,000 hit points - to produce a new ant of the same colony number to its square in the simulation adds it and reduces its own hit points by 1500 and increments the count of new ants for this anthill and adds it simulation
        Actor * temp = new Ant(getX(), getY(), getColonyNum(), getPointerToCompiler(), IID_ANT_TYPE0 + getColonyNum(), getX(), getY(), getWorld());
        getWorld() -> addActor(getX(), getY(), temp);
        setEnergy(getEnergy() - 1500);
        getWorld() -> addAnt(getColonyNum());
    }
}

int Anthill::getColonyNum(){
    return m_colNum;
}

Compiler* Anthill::getPointerToCompiler()
{
    return m_pointerToCompiler;
}


// ACTIVE
Active::Active(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Energy(imgID, x, y, studentWorld)
{
    setIsBitable(true);     //set new member vaiables to intial state and adjust ones that need to be changed for actives
    setWet(false);
    setIsDangerous(true);
}

int Active::getStunnedAsleep()
{
    return m_stunnedAsleep;
}

void Active::setStunnedAsleep(int num)
{
    m_stunnedAsleep = num;
}

void Active::setRandomDir()
{
    int i = randInt(0, 3);
    if (i == 0)
    {       //get random number from 0 to 3 and set direction based on the number
        setDirection(up);
    } else if (i == 1)
    {
        setDirection(down);
    } else if (i == 2)
    {
        setDirection(right);
    } else if (i == 3)
    {
        setDirection(left);
    }
}

void Active::addFood(int amount)
{
    if (amount <= 0)//cheeck amount
        return;
    if (getWorld() -> findFood(getX(), getY()) == nullptr)
    {           //or else add a new food and set energy to the amount
        Food * p = new Food(IID_FOOD, getX(), getY(), getWorld());
        p -> setEnergy(amount);
        getWorld() -> addActor(getX(), getY(), p);
        return;
    }
    else
    {   //see if there is food already on this square and if so just add energy to that food object
        Food* q = dynamic_cast<Food*>(getWorld() -> findFood(getX(), getY()));
        q -> setEnergy(getEnergy() + amount);
        return;
    }
}

void Active::setWet(bool v)
{
    m_wet = v;
}

bool Active::getWet()
{
    return m_wet;
}

bool Active::move()
{   //get direction and if rock ahead then dont move and return false otherwise return true and chang position of object
    if (getDirection() == up){
        if ((getWorld() -> isRock(getX(), getY() + 1)))
        {
            return false;
        }
        moveTo(getX(), getY() + 1);
    }
    else if (getDirection() == down)
    {
        if ((getWorld() -> isRock(getX(), getY() - 1)))
        {
            return false;
        }
        moveTo(getX(), getY() - 1);
    }
    else if (getDirection() == right)
    {
        if ((getWorld() -> isRock(getX() + 1, getY())))
        {
            return false;
        }
        moveTo(getX() + 1, getY());
    }
    else if (getDirection() == left)
    {
        if ((getWorld() -> isRock(getX() - 1, getY())))
        {
            return false;
        }
        moveTo(getX() - 1, getY());
    }
    setWet(false);  //set wet to false becuase if an active moves off of water then it can again get stunned by water
    return true;
    
}


bool Active::bite(int damage)
{
    Ant* p = dynamic_cast<Ant*>(this);//check if this object is an ant
    Actor* rand;
    if(p!=nullptr)//if it is an ant then set rand to that ant to make sure it wont bite its own colony
    {
        rand = getWorld() -> getRandomInsect(getX(), getY(),this, p->getColonyNum());
    }
    else//if it isnt an ant then find a random insect on this square to bite
    {
        rand = getWorld() -> getRandomInsect(getX(), getY(), this);
    }
    if(rand!=nullptr && rand -> isAlive())//make sure there is an insect to bite and it is still alive
    {
        Active* a = dynamic_cast<Active*>(rand);//make this rand pointer to the insect to bite to an active
        if(a!=nullptr)
        {
            a -> setEnergy(a->getEnergy() - damage);//take energy from insect bitten and see if it died
            if(a->checkDead())
            {
                return true;
            }
            Ant* c = dynamic_cast<Ant*>(a);//if it was an ant then make sure the bool bitten is set to true
            if (c != nullptr)
            {
                c->setWasBitten(true);
            }
        AdultGrasshopper* b = dynamic_cast<AdultGrasshopper*>(a);//if what was bitten was an adult grasshopper then 50% chance it randomly bites another insect on the square
        if(b!=nullptr)
        {
            if(randInt(0, 1)==1)
            {
                b->bite(50);
            }
        }
        return true;//return true if something was bitten
        }
    }
    return false;//or else return false
}



// ANT
Ant::Ant(int homeX, int homeY, int antColonyNum, Compiler* pointerToCompiler, int imgID, int x, int y, StudentWorld * studentWorld, Direction, int depth) : Active(imgID, x, y, studentWorld)
{
    m_antColonyNum = antColonyNum;              //set all ant special member variable to intial state and change other base
    setStunnedAsleep(0);                        //class member variables
    m_pointerToCompiler = pointerToCompiler;
    m_wasBitten = false;
    m_wasBlocked = false;
    setRandomDir();
    m_instructionCounter = 0;
    m_homeX = homeX;
    m_homeY = homeY;
    setIsStunablePoisonable(true);
    setEnergy(1500);
}

void Ant::doSomething()
{
    int counter = 0;        //craete counter to make sure no more than 10 operations taken every turn
    bool flag = false;      //make flag for checking if command is operated for this tick
    Compiler::Command cmd;
    
    setEnergy(getEnergy()-1);   //decrement energy
    
    if (checkDead())        //check if dead
    {
        return;
    }
    
    if (getStunnedAsleep() > 0)     //if ant is stunned/as;eep then decrease count of stunned/asleep turns and return
    {
        setStunnedAsleep(getStunnedAsleep()-1);
        return;
    }
    
    while(!flag)    //only loop through while a command hasnt been executed this tick
    {
        if(!m_pointerToCompiler->getCommand(m_instructionCounter, cmd))//if there is problem loading command then kill ant
        {
            setIsAlive(false);
            return;
        }
        counter++;  //incrememnt counter of operations performed this tick
        switch (cmd.opcode)
        {
            case Compiler::moveForward:
            {//set flag to true becuase command executed and if it does move then set blocken and bit to false but if it doesnt move then set the blocked bool to true and increment the number of command from bug file
                flag = true;
                if(move())
                {
                    m_wasBlocked = false;
                    m_wasBitten = false;
                }
                else
                {
                    m_wasBlocked = true;
                }
                m_instructionCounter++;
                break;
            }
            case Compiler::eatFood:
            {//set flag to true and call ant's special eat function and increase the number of command from bug file
                flag = true;
                eat();
                m_instructionCounter++;
                break;
            }
            case Compiler::dropFood:
            {//set flag to true and add a food object with energy oh how much food the ant is carrying and set amount of food an ant is carrying to 0 and increase the number of command from bug file
                flag = true;
                addFood(m_foodCarrying);
                m_foodCarrying = 0;
                m_instructionCounter++;
                break;
            }
            case Compiler::bite:
            {//set flag to true and call the bite fuction with damage 15 and increase the number of command from bug file
                flag = true;
                bite(15);
                m_instructionCounter++;
                break;
            }
            case Compiler::pickupFood:
            {//set flag to true and then call energy's eat function for up to 400 food and then take that found out of the ant's energy and put it in the ant's foodCarring variable and then increase number of command from bug file
                flag = true;
                int previous = getEnergy();
                if (m_foodCarrying <= 1400)
                {
                    Energy::eat(400);
                }
                else
                {
                    Energy::eat(1800-m_foodCarrying);
                }
                int After = getEnergy();
                m_foodCarrying = m_foodCarrying + (After - previous);
                setEnergy(previous);
                m_instructionCounter++;
                break;
            }
            case Compiler::emitPheromone:
            {//set flag to true and call the addPheromone functioin and increase the number of the command from bug file
                flag = true;
                addPheromone();
                m_instructionCounter++;
                break;
            }
            case Compiler::faceRandomDirection:
            {//set flag to true and call the setRandomDir function and increase the number of the command from bug file
                flag = true;
                setRandomDir();
                m_instructionCounter++;
                break;
            }
            case Compiler::rotateClockwise:
            {//set flag to true and figure out direction the ant is currently facing and then change the direction to whatever is clockwise of that and then increase number of command from bug file
                flag = true;
                if(getDirection() == up)
                    setDirection(right);
                else if(getDirection() == right)
                    setDirection(down);
                else if(getDirection() == down)
                    setDirection(left);
                else if(getDirection() == left)
                    setDirection(up);
                m_instructionCounter++;
                break;
            }
            case Compiler::rotateCounterClockwise:
            {//set flag to true and figure out direction the ant is currently facing and then change the direction to whatever is counterclockwise of that and then increase number of command from bug file
                flag = true;
                if(getDirection() == up)
                    setDirection(left);
                else if(getDirection() == right)
                    setDirection(up);
                else if(getDirection() == down)
                    setDirection(right);
                else if(getDirection() == left)
                    setDirection(down);
                m_instructionCounter++;
                break;
            }
            case Compiler::generateRandomNumber:
            {//if random number is 0 then set lastRand to 0 otherwise set last rand to something else and increase the number of command from bug file
                if(stoi(cmd.operand1) == 0)
                {
                    m_lastRand = 0;
                }
                else
                {
                    m_lastRand = randInt(0, stoi(cmd.operand1)-1);
                }
                m_instructionCounter++;
                break;
            }
            case Compiler::goto_command:
            {//if command is goto then just set command number to the one at operand1
                m_instructionCounter = stoi(cmd.operand1);
                break;
            }
            case Compiler::if_command:
            {//set the next integer to the command the if statement says to go to if it is true
                flag = false;
                int next = stoi(cmd.operand2);
                switch(stoi(cmd.operand1))
                {
                    case Compiler::Condition::last_random_number_was_zero:
                    {//if lastRand equals 0 then go to command at next otherwise just increment command
                        if(m_lastRand==0)
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                    case Compiler::Condition::i_am_carrying_food:
                    {//if the amount of food an ant is carring is > 0 then go to command at next otherwise just increment command
                        if(m_foodCarrying>0)
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                    case Compiler::Condition::i_am_hungry:
                    {//if ant is below 26 energy then go to command at next otherwise increment command
                        if(getEnergy()<=25)
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                    case Compiler::Condition::i_am_standing_with_an_enemy:
                    {//if there are enermies aka insects on same square as the ant then go to command at next otherwise just increment command
                        Actor* rand = getWorld()->getRandomInsect(getX(), getY(), this, getColonyNum());
                        if(rand!=nullptr)
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                    case Compiler::Condition::i_am_standing_on_food:
                    {//if findFood returns a pointer to a food object then go to command at next otherwise just increment command
                        Actor* object = getWorld()->findFood(getX(), getY());
                        Food* c_food = dynamic_cast<Food*>(object);
                        if(c_food!=nullptr)
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                    case Compiler::Condition::i_am_standing_on_my_anthill:
                    {//if ant's coordinates are the same as its home coordinates then go to command at next otherwise just increment command
                        if((getX()==m_homeX)&&(getY()==m_homeY))
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                    case Compiler::Condition::i_smell_pheromone_in_front_of_me:
                    {//if smellPheromoneAhead function returns true then go to command at next otherwise just increment command
                        if(getWorld()->smellPheromoneAhead(this))
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                    case Compiler::Condition::i_smell_danger_in_front_of_me:
                    {//if smellDanger function returns true then go to command at next otherwise just increment command
                        if(getWorld()->smellDanger(this))
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                    case Compiler::Condition::i_was_bit:
                    {//if the ant's wasBitten member bool is true then go to command at next otherwise just increment command
                        if(m_wasBitten)
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                    case Compiler::Condition::i_was_blocked_from_moving:
                    {//if the ant's wasBlocked member bool is true then go to command at next otherwise just increment command
                        if(m_wasBlocked)
                            m_instructionCounter = next;
                        else
                            m_instructionCounter++;
                        break;
                    }
                        break;

                }
            }
        }
        if(counter >= 10)//if more the 10 commands have been interpretted then break from loop
            flag = true;
    }
    return;
}

void Ant::addPheromone()
{
    if (getWorld() -> findPheromone(this) == nullptr)//if find pheromone returns a nullptr becuase there is no pheromone on this square then create new pheromone with this ant's colony num and add it to world
    {
        Pheromone * p = new Pheromone(IID_PHEROMONE_TYPE0+getColonyNum(), getColonyNum(), getX(), getY(), getWorld());
        getWorld() -> addActor(getX(), getY(), p);
        return;
    }
    else
    {//if findPheromone returns a pointer to a pheromone then add energy to that pheromone up to a max of 768
        Pheromone* q = dynamic_cast<Pheromone*>(getWorld() -> findPheromone(this));
        q -> setEnergy(getEnergy() + 256);
        if(q->getEnergy() > 768)
            q->setEnergy(768);
        return;
    }
}

void Ant::setWasBitten(bool b)
{
    m_wasBitten = b;
}



bool Ant::eat()
{
    if(m_foodCarrying > 0)//if an ant has any food it is carrying
    {
        if (m_foodCarrying < 100)//if it has less than 100 food then it will eat all food taht it is carrying
        {
            setEnergy(getEnergy()+m_foodCarrying);
            m_foodCarrying = 0;
        }
        else
        {//or else it will eat 100 food and increase its energy and decrease the amount of food it is carrying by 100
            setEnergy(getEnergy()+100);
            m_foodCarrying = m_foodCarrying - 100;
        }
        return true;
    }
    return false;
}

int Ant::getColonyNum()
{
    return m_antColonyNum;
}

Compiler* Ant::getPointerToCompiler()
{
    return m_pointerToCompiler;
}

// PEBBLE
Pebble::Pebble(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Actor(IID_ROCK, x, y, studentWorld,  dir, depth)
{
    setMovable(false);//only actore that isnt movable
}

void Pebble::doSomething(){}

// FOOD

Food::Food(int imgID, int x, int y, StudentWorld* studentWorld, Direction dir , int depth) : Energy(IID_FOOD, x, y, studentWorld, dir, depth)
{
    setEnergy(6000);        //set all variable to what they need to be for food
    setIsEatable(true);
}

void Food::doSomething()
{
    checkDead();
}


// BABY GRASSHOPPER
BabyGrasshopper::BabyGrasshopper(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : Active(IID_BABY_GRASSHOPPER, x, y, studentWorld)
{
    setEnergy(500);             //set all variables to what they need to be
    setMovable(true);
    setMoveDis(randInt(2, 10));
    setStunnedAsleep(0);
    setRandomDir();
    setIsStunablePoisonable(true);
}

void BabyGrasshopper::setMoveDis(int n)
{
    m_moveDist = n;
}

int BabyGrasshopper::getMoveDis()
{
    return m_moveDist;
}

void BabyGrasshopper::doSomething()
{
    setEnergy(getEnergy()-1);//decrement energy
    
    if (checkDead())//check if grasshopper has died
    {
        return;
    }
    
    if (getStunnedAsleep() > 0)//if greasshopper is stunned/asleep then decrement stunned/asleep and return
    {
        
        setStunnedAsleep(getStunnedAsleep()-1);
        return;
    }
    
    if (getEnergy() >= 1600)//if has enough energy then kill this grasshopper, add 100 food to this square for the carcus, and add a new adult grasshoppper to this square
    {
        AdultGrasshopper* G = new AdultGrasshopper(IID_ADULT_GRASSHOPPER, getX(), getY(), getWorld());
        getWorld()->addActor(getX(), getY(), G);
        setIsAlive(false);
        addFood(100);
        return;
    }
    
    
    
    if(eat(200))//tries to eat up to 200 food and then 50% chance it will sleep for two more ticks after if it does eat
    {
        int i = randInt(0, 1);
        if (i == 1)
        {
            setStunnedAsleep(getStunnedAsleep()+2);
            return;
        }
    }
    
    if (getMoveDis() <= 0)//if it is done walking in its current direction then get new direction and distance
    {
        setMoveDis(randInt(2, 10));
        setRandomDir();
    }
    
    setMoveDis(getMoveDis()-1);//try to move and if it cant set move dis to 0 so it will get new distance and direction to walk next tick
    if(move() == false)
        setMoveDis(0);
    
    setStunnedAsleep(getStunnedAsleep()+2);//must sleep for two ticks between doing anything
}




//ADULT GRASSHOPPER
AdultGrasshopper::AdultGrasshopper(int imgID, int x, int y, StudentWorld * studentWorld, Direction dir, int depth) : BabyGrasshopper(IID_ADULT_GRASSHOPPER, x, y, studentWorld)
{
    setEnergy(1600);                //set all variables to what they need to be for an adult grasshopper
    setStunnedAsleep(0);
    setMoveDis(randInt(2, 10));
    setRandomDir();
    setIsStunablePoisonable(false);
}

void AdultGrasshopper::doSomething()
{
    setEnergy(getEnergy() - 1); //The adult grasshopper loses one hit point
    
    if (checkDead())
    { // must check to see if its hit points have reached zero
        return;
    }
    
    if (getStunnedAsleep() > 0)//if greasshopper is stunned/asleep then decrement stunned/asleep and return
    {
        setStunnedAsleep(getStunnedAsleep() - 1);
        return;
    }
    
    //one third chance that the adult grasshopper will try to bite another insect
    int rand = randInt(1, 3);
    if (rand == 1)
    {
        bite(50);
    }
    
    //one tenth chance that the adult grasshopper will decide to jump to another square
    rand = randInt(1, 10);
    int radius; double angle;
    int xCoor; int yCoor;
    
    if (rand == 1)//if it happens to be 1
    {
        bool foundEmpty = false, wentToEmpty;
        
        for (int x = 0; x < 10; x++)//go through to make sure that there is a space in 10 square radius that is empty that it can jump to
        {
            for (int y = 0; y < 10; y++)
            {
                if (sqrt(x*x + y*y) <= 10 && !getWorld() -> isRock(getX() + x, getY() + y))
                {
                    foundEmpty = true;
                }
            }
        }
        if (foundEmpty)//if there is an empty square
        {
            while (!wentToEmpty)
            {
                radius = randInt(1, 10);//get randum radius, angle
                angle = randInt(1, 360) * M_PI/180;
                xCoor = radius * cos(angle); //calculate xcoordinate
                yCoor = radius * sin(angle); //calculate y coordinate
                
                if (getWorld() -> isRock(getX() + xCoor, getY() + yCoor)){ // if it's a rock then loop back and look for different square
                    continue;
                }
                else
                {//move to that ranodm empty square and set wentToEmpty to exit loop
                    wentToEmpty = true;
                    moveTo(getX() + xCoor, getY() + yCoor);
                }
            }
            setStunnedAsleep(getStunnedAsleep() + 2);//if it jumped then add 2 to stunnedAsleep and return
            return;
        }
    }
    
    // eat up to 200 food
    if (eat(200))
    {
        int rand = randInt(0, 1);
        if (rand == 1)
        {
            setStunnedAsleep(getStunnedAsleep() + 2);
            return;
        }
    }
    
    //see if the adult grasshopper has finished walking and if it has give it new random direction and distance
    if (getMoveDis() <= 0)
    {
        setRandomDir();
        setMoveDis(randInt(2, 10));
    }
    
    //The adult grasshopper attempts to move one square in its currently facing direction
    if(move() == false)
    {
        setMoveDis(0);
        setStunnedAsleep(getStunnedAsleep() + 2);
        return;
    }
    
    //Otherwise, the adult grasshopper decreases its desired distance to walk in the current direction by one.
    setMoveDis(getMoveDis() - 1);
    setStunnedAsleep(getStunnedAsleep() + 2);
}



//POISON

Poison::Poison(int imgID, int x, int y, StudentWorld* studentWorld, Direction dir, int depth) : Actor(IID_POISON, x, y, studentWorld, dir, depth)
{
    setIsDangerous(true);//only variable change is that it is dangerous
}


void Poison::doSomething()
{
    getWorld()->poison(getX(), getY());//call the poison functino in student world
}


//WATERPOOL

WaterPool::WaterPool(int imgID, int x, int y, StudentWorld* studentWorld, Direction dir, int depth) : Actor(IID_WATER_POOL, x, y, studentWorld, dir, depth)
{
    setIsDangerous(true);
}

void WaterPool::doSomething()//call the stun function in studentworld
{
    getWorld()->stun(getX(), getY());
    return;
}


//PHEROMONE

Pheromone::Pheromone(int imgID, int colonyNum, int x, int y, StudentWorld* studentWorld, Direction dir, int depth) : Energy(imgID, x, y, studentWorld, dir, depth)
{
    setEnergy(256);                     //set energy to 256 and match colonyNum with that of ant that dropped it
    m_colonyNum = colonyNum;
}

void Pheromone::doSomething()
{
    setEnergy(getEnergy()-1);           //decrement energy and check if it is out of energy yet
    checkDead();
}

int Pheromone::getColonyNum()
{
    return m_colonyNum;
}















