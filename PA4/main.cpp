#include "Robot.h"

const int GRID_SIZE = 10;  // Define the size of the grid as 10x10
std::vector<std::vector<Robot *>> grid(GRID_SIZE, std::vector<Robot *>(GRID_SIZE, nullptr));  // Create a 2D vector to hold pointers to Robots

// Function to generate a random integer between min and max
int randomInt(int min, int max)
{
    static std::random_device rd;  // Non-deterministic random number generator
    static std::mt19937 gen(rd());  // Seeded with rd to produce deterministic results
    std::uniform_int_distribution<> dis(min, max);  // Distribute results uniformly between min and max
    return dis(gen);
}

// Function to print the result of a hit during combat
void printHitMessage(const Robot *attacker, const Robot *victim, int damage)
{
    int newHitPoints = victim->getHitpoints() - damage;  // Calculate new hitpoints after damage
    std::cout << attacker->getName() << "(" << attacker->getHitpoints() << ") hits "
              << victim->getName() << "(" << victim->getHitpoints() << ") with " << damage << "\n"
              << "The new hitpoints of " << victim->getName() << " is " << (newHitPoints > 0 ? newHitPoints : 0) << std::endl;
}

// Function to control movement and combat of robots on the grid
void moveAndFight(Robot *robot, int x, int y, std::vector<std::vector<Robot *>> &grid)
{
    if (robot->getMoved())  // Check if robot has already moved
        return;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);  // Random direction generator

    int dx[4] = {0, 0, 1, -1};  // X-axis movements
    int dy[4] = {1, -1, 0, 0};  // Y-axis movements

    int direction = dis(gen);  // Get random direction
    int newX = x + dx[direction];  // Calculate new X position
    int newY = y + dy[direction];  // Calculate new Y position

    if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE)  // Check grid bounds
    {
        if (grid[newX][newY] == nullptr)  // If the new position is empty
        {
            grid[newX][newY] = robot;
            grid[x][y] = nullptr;
            robot->setMoved();
        }
        else  // If there is another robot, combat ensues
        {
            Robot *opponent = grid[newX][newY];
            int damage = robot->getDamage();
            printHitMessage(robot, opponent, damage);  // Display combat result
            opponent->setHitpoints(opponent->getHitpoints() - damage);  // Apply damage
            if (opponent->getHitpoints() <= 0)  // Check if the robot is dead
            {
                std::cout << opponent->getName() << " is dead.\n";
                delete opponent;
                grid[newX][newY] = robot;
                grid[x][y] = nullptr;
                robot->setMoved();
            }
            else  // If not, opponent strikes back
            {
                damage = opponent->getDamage();
                printHitMessage(opponent, robot, damage);
                robot->setHitpoints(robot->getHitpoints() - damage);
                if (robot->getHitpoints() <= 0)  // Check if the attacking robot dies
                {
                    std::cout << robot->getName() << " is dead.\n";
                    delete robot;
                    grid[x][y] = nullptr;
                }
            }
        }
    }
}

// Main simulation function to execute the robot fights
void simulate(std::vector<std::vector<Robot *>> &grid)
{
    while (true)
    {
        for (int x = 0; x < GRID_SIZE; x++)  // Reset movement status for all robots
        {
            for (int y = 0; y < GRID_SIZE; y++)
            {
                if (grid[x][y] != nullptr)
                {
                    grid[x][y]->resetMovement();
                }
            }
        }
        for (int x = 0; x < GRID_SIZE; x++)  // Allow each robot to move or fight
        {
            for (int y = 0; y < GRID_SIZE; y++)
            {
                if (grid[x][y] != nullptr)
                {
                    moveAndFight(grid[x][y], x, y, grid);
                }
            }
        }
        // Check if only one robot remains
        int count = 0;
        Robot *lastRobot = nullptr;
        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                if (grid[i][j])
                {
                    count++;
                    lastRobot = grid[i][j];
                }
            }
        }
        if (count == 1)
        {
            std::cout << "The last robot standing is " << lastRobot->getName() << "!\n";
            break;
        }
    }
}

int main()
{
    std::vector<std::string> types = {"OptimusPrime", "Robocop", "Kamikaze", "Bulldozer", "Roomba"};
    int counts[5] = {0};  // Counter for each type of robot
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, GRID_SIZE - 1);

    // Create 5 robots of each type and place them randomly on the grid
    for (int t = 0; t < 5; t++)
    {
        for (int i = 0; i < 5; i++)
        {
            int x, y;
            do
            {
                x = dis(gen);
                y = dis(gen);
            } while (grid[x][y] != nullptr);  // Find an empty cell

            std::string name = types[t] + "_" + std::to_string(counts[t]++);
            Robot *robot = nullptr;
            if (types[t] == "OptimusPrime")
            {
                robot = new OptimusPrime();
            }
            else if (types[t] == "Robocop")
            {
                robot = new Robocop();
            }
            else if (types[t] == "Kamikaze")
            {
                robot = new Kamikaze();
            }
            else if (types[t] == "Bulldozer")
            {
                robot = new Bulldozer();
            }
            else if (types[t] == "Roomba")
            {
                robot = new Roomba();
            }

            robot->setName(name);
            grid[x][y] = robot;
        }
    }

    simulate(grid);  // Start the simulation

    // Clean up memory after simulation ends
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j])
            {
                delete grid[i][j];
            }
        }
    }

    return 0;
}
