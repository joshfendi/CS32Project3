#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Side.h"
using namespace std;

// BOARD CLASS
class Board
{
private:
    int m_holes;                // # of holes per side
    int m_InitialBeansPerHole;  // # of initial beans per hole
    vector<int> m_HolesPot_vec; // vector of the board. index 0 == NORTH pot, goes counterclockwise until NORTH #1 hole

public:
    // Construct a Board with the indicated number of holes per side
    // (not counting the pot) and initial number of beans per hole.
    Board(int nHoles, int nInitialBeansPerHole);

    // Return the number of holes on a side (not counting the pot).
    int holes() const;

    // Return the number of initial beans in a hole
    int initialBeansPerHole() const;

    // Return the number of beans in the indicated hole or pot
    int beans(Side s, int hole) const;

    // Return the total number of beans in all the holes on the indicated side
    // not counting the beans in the pot.
    int beansInPlay(Side s) const;

    // Return the total number of beans in the game, including any in the pots.
    int totalBeans() const;

    // Return true after sowing the beans:
    // 1) the beans are removed from hole (s,hole) and sown counterclockwise, including
    // s's pot if encountered, but skipping s's opponent's pot.
    // 2) The function sets the parameters endSide and endHole to the side
    // and hole where the last bean was placed.
    // (This function does not make captures or multiple turns; different Kalah variants have
    // different rules about these issues, so dealing with them should not
    // be the responsibility of the Board class.)
    bool sow(Side s, int hole, Side &endSide, int &endHole);

    // If the indicated hole is invalid or a pot, return false without changing anything.
    // Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner
    // and return true.
    bool moveToPot(Side s, int hole, Side potOwner);

    // Otherwise, it will return true after setting the number
    // of beans in the indicated hole or pot to the value of
    // the third parameter. (This could change what beansInPlay
    // and totalBeans return if they are called later.) This
    // function exists solely so that we and you can more easily
    // test your program: None of your code that implements the
    // member functions of any class is allowed to call this function
    // directly or indirectly. (We'll show an example of its use below.)
    bool setBeans(Side s, int hole, int beans);
};

#endif // BOARD_H
