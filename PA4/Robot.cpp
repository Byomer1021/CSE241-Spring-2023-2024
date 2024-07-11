#include "Robot.h"

const int GRID_SIZE = 10; // Define grid size for the simulation

// Constructor for the Robot class
Robot::Robot(int newStrength, int newHitpoints, std::string newName)
	: strength(newStrength), hitpoints(newHitpoints), name(newName), hasMoved(false) {}

// Destructor for the Robot class
Robot::~Robot() {}

// Return the current hitpoints of the robot
int Robot::getHitpoints() const { return hitpoints; }

// Set new hitpoints for the robot
void Robot::setHitpoints(int newHitpoints) { hitpoints = newHitpoints; }

// Get the name of the robot
std::string Robot::getName() const { return name; }

// Set a new name for the robot
void Robot::setName(const std::string &newName) { name = newName; }

// Reset the movement flag for the robot
void Robot::resetMovement() { hasMoved = false; }

// Mark the robot as having moved
void Robot::setMoved() { hasMoved = true; }

// Check if the robot has moved this turn
bool Robot::getMoved() const { return hasMoved; }

// Constructor for Humanic, a subclass of Robot
Humanic::Humanic(int strength, int hitpoints, std::string name) : Robot(strength, hitpoints, name) {}

// Calculate damage for Humanic robots, with a chance for a special attack
int Humanic::getDamage()
{
	int damage = randomInt(1, strength); // Start with base damage
	if (randomInt(1, 100) <= 10)
	{
		damage += 50; // 10% chance to add a tactical nuke attack
	}
	return damage;
}

// Constructor for OptimusPrime, a subclass of Humanic
OptimusPrime::OptimusPrime() : Humanic(100, 100, "OptimusPrime") {}

// Calculate damage for OptimusPrime, with a chance to double the damage
int OptimusPrime::getDamage()
{
	int baseDamage = Humanic::getDamage(); // Start with Humanic damage
	if (randomInt(1, 100) <= 15)
	{
		baseDamage *= 2; // 15% chance to double the damage
	}
	return baseDamage;
}

// Constructor for Robocop, a subclass of Humanic
Robocop::Robocop() : Humanic(30, 40, "Robocop") {}

// Calculate damage for Robocop, identical to Humanic damage calculation
int Robocop::getDamage() { return Humanic::getDamage(); }

// Constructor for Kamikaze, a subclass of Robot
Kamikaze::Kamikaze() : Robot(10, 10, "Kamikaze") {}

// Calculate damage for Kamikaze, which results in its own destruction
int Kamikaze::getDamage()
{
	int damage = hitpoints; // Damage equals current hitpoints
	hitpoints = 0;			// Kamikaze dies after attacking
	return damage;
}

// Constructor for Bulldozer, a subclass of Robot
Bulldozer::Bulldozer() : Robot(50, 200, "Bulldozer") {}

// Calculate damage for Bulldozer, includes additional fixed damage
int Bulldozer::getDamage() { return randomInt(1, strength) + 20; }

// Constructor for Roomba, a subclass of Robot
Roomba::Roomba() : Robot(3, 10, "Roomba") {}

// Calculate damage for Roomba, which can attack twice per turn
int Roomba::getDamage()
{
	int damage = randomInt(1, strength);	// First attack
	return damage + randomInt(1, strength); // Second attack, added to first
}
