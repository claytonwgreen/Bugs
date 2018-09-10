# Bugs

### Dependencies 
* [XQuartz](https://www.xquartz.org/releases/index.html)
	* Built using v 2.7.11 

---

### Running
```bash
./[Executable] [FieldFile] [AntFile] [AntFile] [AntFile] [AntFile]
```
- Executable:
	* The binary executable made from building this repo ("Bugs" in this repo) 	
- FieldFile:
	* The file used to create the playing field (provided in "FieldFiles" folder)
- AntFile:
	* File that each player creates with the logic for their ant colony
	* 2-4 of these required 
 
Ex:
```bash
./Bugs ./FieldFiles/fieldFileMain.txt ./Ants/dumbant1.ant.txt ./Ants/dumbant2.ant.txt ./Ants/dumbant3.ant.txt ./Ants/smartant.ant.txt -raw
```



---

### How the Game Works

Once the field-file has been loaded, the simulation begins and runs for 2,000 units or “ticks” of time, with each tick
occupying roughly 1/10th of a second. During each tick of the simulation, all of the ants in the simulation are given an opportunity to
do something. 

During each of the first five ticks of a competition simulation, each anthill will produce one new
ant. Each anthill produces a different type of ant, and is controlled by one of the ant control files designated
when starting up the simulation (see "Running" section above). For example, if we ran the command line:
Anthill #0 will produce ants that are controlled by the sillyant.bug program. The second anthill,
#1, will produce ants that are controlled by the killer.bug program, and so on.

Once an anthill has given birth to an ant, the ant’s behavior is entirely controlled by its Bugs!
program (e.g., the instructions found inside of sillyant.bug), and this program’s unique
instructions cause it to forage around the virtual field looking for food. When an ant finds food, it
can pick it and bring it back to its anthill for consumption by the anthill/queen ant. The moment
the ant drops food upon the same square as an anthill, the anthill will eat the food, increasing its
own hit point count, and removing the food from the virtual field. Once the anthill/queen ant
consumes enough food, it will then produce yet another new ant (and that ant will also use the
exact same Bugs program), which can forage for even more food.


Every anthill starts with enough food to produce five initial ants, but to produce additional ants,
an anthill needs to be provided with more food by its ant colony. That’s where the ant programs
(written in the Bugs! language) come in – their instructions ideally direct each individual ant to
find and pick up this food and bring it back to the hill. The more efficient an ant’s Bugs! program
is at foraging for food and bringing it back to its anthill, the more ants will be added to the
colony, and the more likely the entrant is to win the competition.
Entrants are judged based on the total number of ants their colony produces over the course of
the entire simulation. For an entrant to win the competition, its colony must meet three
requirements:
1. Its anthill must produce at least 6 total ants (each anthill starts with enough food to
produce 5 ants, but if the colony’s ants can bring food back to feed the hill/queen, then
the anthill/queen can produce even more ants. The anthill must produce at least 6 ants
for an entrant to qualify to win.).
2. The anthill must produce more total new ants across the complete simulation’s 2,000
ticks than the competitors’ anthills.
3. If two or more colonies produce the same total number of ants by the end of the
simulation, then the colony that reached this count earliest in the simulation wins.


Each insect (ants, baby grasshoppers, and adult grasshoppers) has a health level, measured in
“hit points”. Ants start out with 1500 hit points, baby grasshoppers start out with 500 hit points,
and adult grasshoppers start out with 1600 hit points. Each insect uses up one hit point of health
during each tick of the simulation. Each insect can gain more hit points by eating food, which is
dispersed throughout the field. Insects can also lose hit points if they are bitten by other insects
or they step onto a square with poison. When an insect reaches zero or fewer hit points, it dies,
is removed from the virtual world, and is replaced by 100 units of food (after all, another insect
might want to come around and eat the dead carcass).
A given ant can eat and eat and eat, and there is no bound to the maximum hit points an ant
can have. Similarly, adult grasshoppers can eat and eat and eat, and have an unbounded
number of hit points. However, baby grasshoppers have a limited capacity to eat. The moment
they reach 1600 or more total hit points, they instantly transform into an adult grasshopper with
exactly 1600 hit points (that is, the baby grasshopper dies and is replaced by a newly minted
adult grasshopper).
Each anthill has a health level as well. Each anthill starts with 8999 hit points, and loses one hit
point during each tick of the game. If an anthill has 2000 or more hit points, it will give birth to a
new ant. Giving birth causes the anthill to lose 1500 hit points, since when a new ant is born, it
starts with 1500 hit points. Anthills gain hit points only when food is dropped onto them. If food is
dropped onto a square with an anthill, the anthill will immediately consume the food and
increase its hit points. If an anthill reaches zero hit points, it will immediately die and be removed
from the field, and therefore not be able to produce any new ants.
If an ant or a baby grasshopper steps onto poison, it will cause 150 hit points of damage to the
insect. Adult grasshoppers, however, are immune to the effects of poison, and it will do no
damage to them.
Ants and adult grasshoppers are capable of biting other insects if they are on the same square.
When ants bite another insect, they cause 15 hit points of damage. Adult grasshoppers are
much nastier, and when they bite another insect they cause 50 hit points of damage. Baby
grasshoppers can’t bite, so they can never cause any damage to other insects.
If an ant or a baby grasshopper steps on a pool of water, the pool of water will temporarily stun
it, making it do nothing for two whole ticks before the insect can act again. Once an insect has 
been stunned by a pool of water, it will not be stunned again by the same pool of water unless it
moves off of the square containing the pool, then moves back to this square again.
Ants are able to release pheromones (a scent produced by a gland in the ant) into the virtual
world - release of such pheromones is controlled, like all other ant behaviors, by the ant’s
programming instructions. Each pheromone has a starting strength of 256 units (Hint: a unit is
like a hit point), and will lose one unit of strength during each tick. After a pheromone reaches 0
units, it disappears from the virtual field. Ants can increase the total strength of their colony’s
pheromones in a square up to 768 units by releasing pheromones in that square more than one
time. Every ant from within a given colony can smell the pheromones released by every other
ant within the same colony. However ants are unable to smell the pheromones produced by
ants of other colonies. An ant can only smell a pheromone if the pheromone is in the square
directly in front of the ant. Pheromones are useful tools for ants, as they can be used to help the
ants find their antill, or potentially help them to avoid locations where they’ve sensed danger in
the past. While real ants can release multiple different types of pheromones, each colony of our
ants can only release a single type of pheromone.
Food is distributed throughout the virtual field, and each food object initially contains 6,000 units
of energy (Hint: a unit of energy is like a hit point), enough to provide insects that eat all of it up
to 6,000 hit points. If an ant steps onto the same square as food, it may pick up to 400 units of
food up at a time, and can hold up to a total of 1800 units of food. Once an ant is holding one or
more units of food, it can eat this food at any time (to increase its own hit points by an amount
proportional to the units of food eaten). It can also carry this food back to its anthill, then drop it
to feed the anthill/queen. Once the anthill eats enough, as mentioned above, it will then give
birth to a new ant.
Grasshoppers, as mentioned above, come in two different varieties: babies and adults. All
grasshoppers only move once every two ticks - they’re slower than ants, who can do something
every single tick of the simulation. So, in essence, grasshoppers sleep two out of every three
ticks. Unlike the ants, all grasshoppers have hard-coded logic that controls their behavior.
During their active ticks, baby grasshoppers simply walk
around randomly and eat when they land on the same square as food. Adult grasshoppers are
far nastier. In addition to wandering randomly and eating (during their active ticks), if they land
up on the same square as one or more enemy insects (which includes all ants and all other
baby and adult grasshoppers) there’s a 1 in 3 chance that they’ll bite one random enemy on the
same square. And when adult grasshoppers are bit, there’s a 50% chance that they’ll
immediately bite back. Finally, in addition to simply walking around like baby grasshoppers,
there’s a 1 in 10 chance that adult grasshoppers will jump to another square within a 10-square
radius during an active tick. 
