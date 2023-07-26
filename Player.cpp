#include "Player.h"
#include <iostream>

// PLAYER CLASS
Player::Player(std::string name) : m_name(name) {}

// Return the name of the player.
std::string Player::name() const
{
    return m_name;
}

// Return false if the player is a computer player
// Return true if the player is human
// Most kinds of players will be computer players.
bool Player::isInteractive() const
{
    return false; // most players are computers
}

// Since this class is designed as a base class, it should have a virtual destructor.
Player::~Player() {}

// ---------------------------------------------------------------------------------------------------

// HUMAN PLAYER CLASS
HumanPlayer::HumanPlayer(std::string name) : Player(name) {}

// Return false if the player is a computer player
// Return true if the player is human
bool HumanPlayer::isInteractive() const
{
    return true; // is human
}

// function returns the move the player would choose
// If no move is possible, return −1.
int HumanPlayer::chooseMove(const Board &b, Side s) const
{
    int hole = -1;
    bool possibleMove = false;

    // check if moves are possible
    // check all holes
    for (int i = 1; i <= b.holes(); ++i)
    {
        if (b.beans(s, i) > 0)
        {
            possibleMove = true;
            break;
        }
    }

    // NO POSSIBLE MOVES
    if (!possibleMove)
    {
        return -1;
    }

    // There are possible moves
    // If the hole indicated by (s,hole) is empty or invalid or a pot
    while (b.beans(s, hole) == 0 || hole <= 0 || hole > b.holes())
    {
        std::cout << name() << " enter a hole number that you want to sow: ";
        std::cin >> hole;
    }

    return hole;
}

// ---------------------------------------------------------------------------------------------------

// BAD PLAYER CLASS
BadPlayer::BadPlayer(std::string name) : Player(name) {}

// function returns the move the player would choose
// If no move is possible, return −1.
int BadPlayer::chooseMove(const Board &b, Side s) const
{
    vector<int> validHoles; // vector to hld all valid Holes

    // check if moves are possible
    // check all holes
    for (int i = 1; i <= b.holes(); ++i)
    {
        if (b.beans(s, i) > 0)
        {
            validHoles.push_back(i); // return 1st valid move
        }
    }

    // NO POSSIBLE MOVES
    if (validHoles.size() == 0)
    {
        return -1;
    }
    // possible moves
    else
    {
        int randomIndex = rand() % validHoles.size(); // get random index
        return validHoles[randomIndex];               // return random Valid Hole
    }
}

// ---------------------------------------------------------------------------------------------------

// SMART PLAYER CLASS
// PUBLIC functions
SmartPlayer::SmartPlayer(std::string name) : Player(name) {}

// function returns the move the player would choose
// If no move is possible, return −1.
int SmartPlayer::chooseMove(const Board &b, Side s) const
{
    int depth = 4;
    int value = -999;
    return chooseMoveHelper(b, s, s, depth, value);
}


// PRIVATE functions
// evaluate board
int SmartPlayer::evaluate(const Board &b, Side s) const
{
    return b.beans(s, 0) - b.beans(opponent(s), 0);
}

// helper function for chooseMove
int SmartPlayer::chooseMoveHelper(const Board &b, Side s, Side originalSide, int depth, int &maxvalue) const
{
    // BASE CASE
    // If game over or depth reached
    if ((b.beansInPlay(NORTH) == 0 && b.beansInPlay(SOUTH) == 0) || depth == 0)
    {
        maxvalue = evaluate(b, originalSide);
        return -1;
    }

    int bestHole = -1;

    // Iterate over each possible move and evaluate its value
    for (int hole = 1; hole <= b.holes(); ++hole)
    {
        if (b.beans(s, hole) > 0)
        {
            Board boardCOPY = b; // Create a copy of the board for simulation
            Side endSide;
            int endHole;

            // "make" the move
            boardCOPY.sow(s, hole, endSide, endHole);

            int currentValue = 0;

            // if landed in own pot
            if (endSide == s && endHole == 0)
            {
                chooseMoveHelper(boardCOPY, s, originalSide, depth, currentValue);
            }
            // check if there is a capture
            if ((endSide == s) && (boardCOPY.beans(s, endHole) - 1 == 0) && (boardCOPY.beans(opponent(s), endHole) != 0))
            {
                // then that last bean and all beans in the opponent's hole directly
                // opposite from that hole are put into the player's pot, and the turn ends
                // add to SOUTH pot
                boardCOPY.moveToPot(s, endHole, s);
                boardCOPY.moveToPot(opponent(s), endHole, s);
            }

            // recurse
            chooseMoveHelper(boardCOPY, opponent(s), originalSide, depth - 1, currentValue);

            // "unmake" move
            boardCOPY = b;

            // update maxvalue to hold maximum value
            if (currentValue >= maxvalue)
            {
                maxvalue = currentValue;
                bestHole = hole;
            }
        }
    }

    return bestHole;
}