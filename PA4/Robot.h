#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

// Base class for all types of robots
class Robot {
protected:
    int strength;       // The attack strength of the robot
    int hitpoints;      // Current health points of the robot
    std::string name;   // Name identifier for the robot
    bool hasMoved;      // Flag to check if the robot has moved in the current turn

public:
    Robot(int newStrength, int newHitpoints, std::string newName);
    virtual ~Robot();
    virtual int getDamage() = 0;  // Calculate damage this robot can deal
    int getHitpoints() const;     // Get current hitpoints
    void setHitpoints(int newHitpoints); // Set new hitpoints after taking damage
    std::string getName() const;  // Get the name of the robot
    void setName(const std::string &newName); // Set the name of the robot
    void resetMovement();         // Reset the movement flag for the new turn
    void setMoved();              // Mark as moved this turn
    bool getMoved() const;        // Check if the robot has moved
};

// Humanic class derived from Robot, serves as base for human-like robots
class Humanic : public Robot {
public:
    Humanic(int strength, int hitpoints, std::string name);
    int getDamage() override;  // Calculate damage with a chance for a special attack
};

// OptimusPrime class derived from Humanic
class OptimusPrime : public Humanic {
public:
    OptimusPrime();
    int getDamage() override;  // Calculate damage with a chance for a double damage attack
};

// Robocop class derived from Humanic
class Robocop : public Humanic {
public:
    Robocop();
    int getDamage() override;  // Calculate damage normally
};

// Kamikaze class derived from Robot, self-destructs on attack
class Kamikaze : public Robot {
public:
    Kamikaze();
    int getDamage() override;  // Damage equal to its own hitpoints, then dies
};

// Bulldozer class derived from Robot, has high strength
class Bulldozer : public Robot {
public:
    Bulldozer();
    int getDamage() override;  // Calculate damage with additional fixed damage
};

// Roomba class derived from Robot, attacks twice per turn
class Roomba : public Robot {
public:
    Roomba();
    int getDamage() override;  // Calculate damage, can attack twice
};

// Function to handle movement and combat mechanics
void moveAndFight(Robot* robot, int x, int y, std::vector<std::vector<Robot*>>& grid);

// Function to print the result of an attack
void printHitMessage(const Robot* attacker, const Robot* victim, int damage);

// Function to simulate the robot combat until one remains
void simulate(std::vector<std::vector<Robot*>>& grid);

// Utility function to generate a random integer between min and max
int randomInt(int min, int max);

#endif
