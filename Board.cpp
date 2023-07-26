#include "Board.h"

// using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole) : m_holes(nHoles), m_InitialBeansPerHole(nInitialBeansPerHole)
{
    // If nHoles is not positive, act as if it were 1;
    if (nHoles < 1)
    {
        m_holes = 1;
    }

    // if nInitialBeansPerHole is negative, act as if it were 0.
    if (nInitialBeansPerHole < 0)
    {
        m_InitialBeansPerHole = 0;
    }

    for (int i = 0; i < NSIDES; ++i)
    {
        // Initialize North's pot
        m_HolesPot_vec.push_back(POT);

        // Initialize all holes on South side
        for (int i = 0; i < m_holes; ++i)
        {
            m_HolesPot_vec.push_back(m_InitialBeansPerHole);
        }
    }
}

// Return the number of holes on a side (not counting the pot).
int Board::holes() const
{
    return m_holes;
}

// Return the number of initial beans in a hole
int Board::initialBeansPerHole() const
{
    return m_InitialBeansPerHole;
}

// Return the number of beans in the indicated hole or pot
int Board::beans(Side s, int hole) const
{
    // check if hole is invalid
    if (hole < 0 || hole > m_holes)
    {
        return -1;
    }

    if (s)
    { // South
        // if SOUTH pot
        if (hole == 0)
        {
            hole = m_holes + 1;
        }
        return m_HolesPot_vec[hole];
    }
    else
    { // North
        // if not NORTH pot
        if (hole != 0)
        {
            hole = m_HolesPot_vec.size() - hole;
        }
        return m_HolesPot_vec[hole];
    }
}

// Return the total number of beans in all the holes on the indicated side
// not counting the beans in the pot.
int Board::beansInPlay(Side s) const
{
    int beansOnSide = 0;

    for (int i = 1; i <= m_holes; ++i)
    {
        beansOnSide += beans(s, i);
    }

    return beansOnSide;
}

// Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const
{
    int total = 0;

    // Sum up all of the holes and pots
    for (int i = 0; i < m_HolesPot_vec.size(); ++i)
    {
        total += m_HolesPot_vec[i];
    }

    return total;
}

// Return true after sowing the beans:
// 1) the beans are removed from hole (s,hole) and sown counterclockwise, including
// s's pot if encountered, but skipping s's opponent's pot.
// 2) The function sets the parameters endSide and endHole to the side
// and hole where the last bean was placed.
// (This function does not make captures or multiple turns; different Kalah variants have
// different rules about these issues, so dealing with them should not
// be the responsibility of the Board class.)
bool Board::sow(Side s, int hole, Side &endSide, int &endHole)
{

    // SOUTH
    if (s)
    {
        // If the hole indicated by (s,hole) is empty or invalid or a pot
        if (m_HolesPot_vec[hole] == 0 || hole > m_holes || hole <= 0 || hole == m_holes + 1)
        {
            return false;
        }
    }
    // NORTH
    else
    {
        // If the hole indicated by (s,hole) is empty or invalid or a pot
        if (m_HolesPot_vec[m_HolesPot_vec.size() - hole] == 0 || hole > m_holes || hole <= 0 || hole == m_holes + 1)
        {

            return false;
        }
    }

    // sow beans

    int inHand = 0; // beans in hand

    if (s)
    { // South

        inHand = m_HolesPot_vec[hole];
        m_HolesPot_vec[hole] = 0; // took all beans in hand, empty hole

        int current_hole = hole + 1;
        while (inHand > 0)
        {

            // if current_hole is NOT NORTH's pot
            if (current_hole != 0)
            {

                ++m_HolesPot_vec[current_hole]; // add one bean to current_hole
                --inHand;                       // take one bean out of hand
                if (inHand != 0)
                {

                    ++current_hole; // go to next hole
                }
            }
            else
            { // skip North's pot

                ++current_hole; // go to next hole
            }

            // loop back around to the beginning of board
            if ((current_hole >= m_HolesPot_vec.size()) && (inHand != 0))
            {

                current_hole = 0;
            }
        }

        // end side and end hole
        // in SOUTH
        if (current_hole > 0 && current_hole <= m_holes + 1)
        {

            endSide = SOUTH;

            if (current_hole == m_holes + 1)
            { // at SOUTH's pot

                endHole = 0;
            }
            else // not at SOUTH's pot
            {

                endHole = current_hole;
            }
        }
        // in NORTH
        else
        {
            endSide = NORTH;

            if (current_hole == 0)
            { // at North's pot
                endHole = 0;
            }
            else
            { // not at North's pot
                endHole = m_HolesPot_vec.size() - current_hole;
            }
        }
    }
    else
    { // North

        inHand = m_HolesPot_vec[m_HolesPot_vec.size() - hole];
        m_HolesPot_vec[m_HolesPot_vec.size() - hole] = 0; // took all beans in hand, empty hole

        int current_hole;
        if (hole == 1)
        { // reset current hole to beginning

            current_hole = 0;
        }
        else
        { // dont need to reset to beginning

            current_hole = m_HolesPot_vec.size() - hole + 1;
        }

        while (inHand > 0)
        {

            // if current_hole is not SOUTH's pot pot
            if (current_hole != m_holes + 1)
            {

                ++m_HolesPot_vec[current_hole]; // add one bean to current_hole
                --inHand;                       // take one bean out of hand
                if (inHand != 0)
                {
                    ++current_hole; // go to next hole
                }
            }
            else
            { // skip SOUTH's pot

                ++current_hole; // go to next hole
            }

            // loop back around to the beginning of board
            if ((current_hole >= m_HolesPot_vec.size()) && (inHand != 0))
            {

                current_hole = 0;
            }
        }

        // end side and end hole
        if (current_hole > 0 && current_hole <= m_holes + 1)
        {
            endSide = SOUTH;

            if (current_hole == m_holes + 1)
            { // at SOUTH's pot
                endHole = 0;
            }
            else // not at SOUTH's pot
            {
                endHole = current_hole;
            }
        }
        else
        {

            endSide = NORTH;

            if (current_hole == 0)
            { // at North's pot
                endHole = 0;
            }
            else
            { // not at North's pot
                endHole = m_HolesPot_vec.size() - current_hole;
            }
        }
    }

    return true; // successful sow
}

// If the indicated hole is invalid or a pot, return false without changing anything.
// Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner
// and return true.
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    // invalid
    if (hole == 0 || hole == m_holes + 1                      // if hole is a pot
        || hole > m_holes || hole < 0 || beans(s, hole) == 0) // if hole is invalid or empty
    {
        return false;
    }
    // valid
    else
    {
        // SOUTH pot
        if (potOwner)
        {
            // SOUTH hole
            if (s)
            {
                m_HolesPot_vec[m_holes + 1] += m_HolesPot_vec[hole]; // add beans from hole to pot
                m_HolesPot_vec[hole] = 0;                            // empty hole
            }
            // NORTH hole
            else
            {
                m_HolesPot_vec[m_holes + 1] += m_HolesPot_vec[m_HolesPot_vec.size() - hole]; // add beans from hole to pot
                m_HolesPot_vec[m_HolesPot_vec.size() - hole] = 0;                            // empty hole
            }
        }
        // NORTH pot
        else
        {
            // SOUTH hole
            if (s)
            {
                m_HolesPot_vec[0] += m_HolesPot_vec[hole]; // add beans from hole to pot
                m_HolesPot_vec[hole] = 0;                  // empty hole
            }
            // NORTH hole
            else
            {
                m_HolesPot_vec[0] += m_HolesPot_vec[m_HolesPot_vec.size() - hole]; // add beans from hole to pot
                m_HolesPot_vec[m_HolesPot_vec.size() - hole] = 0;                  // empty hole
            }
        }

        return true; // move successful
    }
}

// Otherwise, it will return true after setting the number
// of beans in the indicated hole or pot to the value of
// the third parameter. (This could change what beansInPlay
// and totalBeans return if they are called later.) This
// function exists solely so that we and you can more easily
// test your program: None of your code that implements the
// member functions of any class is allowed to call this function
// directly or indirectly. (We'll show an example of its use below.)
bool Board::setBeans(Side s, int hole, int beans)
{
    // invalid
    if (hole > m_holes || hole < 0 // if hole is invalid
        || beans < 0               // beans are negative
    )
    {
        return false;
    }
    // valid
    else
    {
        // SOUTH
        if (s)
        {
            // if SOUTH pot
            if (hole == 0)
            {
                m_HolesPot_vec[m_holes + 1] = beans;
            }
            // not SOUTH pot
            else
            {
                m_HolesPot_vec[hole] = beans;
            }
        }
        // NORTH
        else
        {
            // if NORTH pot
            if (hole == 0)
            {
                m_HolesPot_vec[hole] = beans;
            }
            // not NORTH pot
            else
            {
                m_HolesPot_vec[m_HolesPot_vec.size() - hole] = beans;
            }
        }

        return true;
    }
}