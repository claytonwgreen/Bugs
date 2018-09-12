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
ant. Each anthill produces ants that are controlled by one of the ant control files designated
when starting up the simulation (see "Running" section above). 

Once an anthill has given birth to an ant, the ant’s behavior is entirely controlled by its control file (see "Programming Your Ants" section below). This file’s unique
instructions (created by a player) cause the ant to forage around the virtual field looking for food. When an ant finds food, it
can pick it and bring it back to its anthill for consumption by the anthill/queen ant. The moment
the ant drops food on its anthill, the anthill will eat the food, increasing its
own hit point count, and removing the food from the virtual field. Once the anthill/queen ant
consumes enough food, it will then produce yet another new ant (and that ant will also use the
exact same ant control file for its logic), which can forage for even more food.


Every anthill starts with enough food to produce five initial ants, but to produce additional ants,
an anthill needs to be provided with more food by its ant colony. That’s where the ant programs
(written by the players) come in – their instructions ideally direct each individual ant to
find and pick up this food and bring it back to the hill. The more efficient an ant’s programming
is at foraging for food and bringing it back to its anthill, the more ants will be added to the
colony, and the more likely the player is to win the competition.
A player wins by having the most ants produced by their colony at the end of the game. For a player to win the competition, their colony must meet three
requirements:

1. Their anthill must produce at least 6 total ants (each anthill must produce at least one ant besides the 5 created at the beginning of the game
for the player to qualify to win.).
2. The anthill must produce more total ants during the complete simulation’s 2,000
ticks than the other competitors’ anthills.
3. If two or more colonies produce the same total number of ants by the end of the
simulation, then the colony that reached this count earliest in the simulation wins.


Each insect (ants, baby grasshoppers, and adult grasshoppers) has a health level, measured in
“hit points”. Ants start out with 1500 hit points, baby grasshoppers start out with 500 hit points,
and adult grasshoppers start out with 1600 hit points. Each insect uses up one hit point of health
during each tick of the simulation. Each insect can gain more hit points by eating food, which is
dispersed throughout the field. Insects can also lose hit points if they are bitten by other insects
or they step onto a square with poison. When an insect reaches zero or fewer hit points, it dies,
is removed from the virtual world, and is replaced by 100 units of food (after all, another insect
might want to come around and eat the dead carcass). Ants and adult grasshoppers can eat, thereby gaining hit points, without bound.
However, baby grasshoppers have a limited capacity to eat. The moment
they reach 1600 or more total hit points, they instantly transform into an adult grasshopper with
exactly 1600 hit points.

Each anthill has a health level as well, starting with 8999 hit points, and losing one hit
point during each tick of the game. If an anthill has 2000 or more hit points, it will give birth to a
new ant. Giving birth causes the anthill to lose 1500 hit points, since when a new ant is born, it
starts with 1500 hit points. Anthills gain hit points only when food is dropped onto them. If food is
dropped onto a square with an anthill, the anthill will immediately consume the food and
increase its own hit points. If an anthill reaches zero hit points, it will immediately die and be removed
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
programming instructions. Each pheromone has a starting strength of 256 units (a unit is
like a hit point), and will lose one unit of strength during each tick. After a pheromone reaches 0
units, it disappears from the virtual field. Ants can increase the total strength of their colony’s
pheromones in a square up to 768 units by releasing pheromones in that square more than one
time. Every ant from within a given colony can smell the pheromones released by every other
ant within the same colony. However, ants are unable to smell the pheromones produced by
ants of other colonies. An ant can only smell a pheromone if the pheromone is in the square
directly in front of the ant. Pheromones are useful tools for ants, as they can be used to help the
ants find their antill, or potentially help them to avoid locations where they’ve sensed danger in
the past. 

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

---

### Building Field File

- The field file details how the game field will be set up when the simulation is run. There are only three requirements for this file:
	* The file must be a 64x64 character text file 
	* The edges of the field must be filled occupied with pebbles 
	* The number of anthills must match the number of ant program files passed in (2-4)
- The rest of the layout is completely up to you
- It is recommended that you place a good amount of food in the playing field, or else the game will often end with no winner
- The labelse for each element you can place in the field are listed below
	* ( * ) pebbles which block movement of all insects1
	* ( g ) starting locations of baby grasshoppers.
	* ( 0, 1, 2, 3 ) the location of the ant colonies’ anthills.
	* ( w ) pools of water.
	* ( f ) piles of food.
	* ( p ) poison.
	* ( space ) empty locations
- See FieldFiles folder above for examples

---

### Programming Your Ants

- The programming for each ant has been simplified to allow virtually anyone to "code" the behavior of a colony, using a specified set of possible commands (see below)
- The ant control file is made up of different sections which you can jump to using the "goto" command
	* The first section is called "start" and is the set of instructions that each ant from your colony will perform when they are first created, or when the command "goto start" is run
	* After the "start" section, you may have as many or few additional sections, but make sure to put a "goto" command at the end of each section or else your ant will stop moving once control reaches the end of the section 
	* You can also use "if" commands to check if certain conditions are true, such as your ant being on top of food which it can then pick up
- The first line of your ant control file should be in the form "colony: *name*" so that you can see how your anthill is doing throughout the game (change *name* to whatever you want your ant colony name to be)
- List of all possible "if" statements:
	* i_smell_danger_in_front_of_me
	* i_smell_pheromone_in_front_of_me
	* i_was_bit
	*  i_am_carrying_food
	* i_am_hungry
	* i_am_standing_on_my_anthill
	* i_am_standing_on_food
	* i_am_standing_with_an_enemy
	* i_was_blocked_from_moving
	* last_random_number_was_zero 	
		* you can use this command to inject some randomness into your ants behavior such as "if last_random_number_was_zero then goto move_left" 
- List of all commands:
 	* emitPheromone
	* faceRandomDirection
	* rotateClockwise
	* rotateCounterClockwise
	* moveForward
	* bite
	* pickupFood
	* dropFood
	* eatFood
	* generateRandomNumber
		* this takes an argurment that is an integer, the random number produced will be between 0 and that number, inlcusive

- Look at the files in the Ants folder to see examples for inspiration and to get the syntax down


---

# HAVE FUN