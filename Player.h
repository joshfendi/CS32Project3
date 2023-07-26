#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>
#include <algorithm>

#include <iostream>

// PLAYER CLASS
class Player
{
private:
    std::string m_name;

public:
    // Create a Player with the indicated name.
    Player(std::string name);

    // Return the name of the player.
    std::string name() const;

    // Return false if the player is a computer player
    // Return true if the player is human
    // Most kinds of players will be computer players.
    virtual bool isInteractive() const;

    // Every concrete class derived from this class must implement
    // this function so that if the player were to be playing
    // side s and had to make a move given board b, the function
    // returns the move the player would choose. If no move is possible, return −1.
    virtual int chooseMove(const Board &b, Side s) const = 0;

    // Since this class is designed as a base class, it should have a virtual destructor.
    virtual ~Player();

    // Each concrete class derived from Player will implement the chooseMove function in
    // its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true.
    // (When testing, we may supply other kinds of interactive players.) Each of the three classes
    // listed here must have a constructor taking a string representing the name of the player.
};

// ---------------------------------------------------------------------------------------------------

// HUMAN PLAYER CLASS
class HumanPlayer : public Player
{
private:
public:
    HumanPlayer(std::string name);

    // Return false if the player is a computer player
    // Return true if the player is human
    virtual bool isInteractive() const;

    // function returns the move the player would choose
    // If no move is possible, return −1.
    virtual int chooseMove(const Board &b, Side s) const;
};

// ---------------------------------------------------------------------------------------------------

// BAD PLAYER CLASS
class BadPlayer : public Player
{
private:
public:
    BadPlayer(std::string name);

    // function returns the move the player would choose
    // If no move is possible, return −1.
    virtual int chooseMove(const Board &b, const Side s) const;
};

// ---------------------------------------------------------------------------------------------------

// SMART PLAYER CLASS
class SmartPlayer : public Player
{
private:
    // evaluate board
    int evaluate(const Board &b, Side s) const;
    
    // helper function for chooseMove
    int chooseMoveHelper(const Board &b, Side s, Side originalSide, int depth, int &maxvalue) const;

public:
    SmartPlayer(std::string name);

    // function returns the move the player would choose
    // If no move is possible, return −1.
    virtual int chooseMove(const Board &b, Side s) const;
};

#endif // PLAYER_H
