#include "Game.h"
#include "Side.h"

// Construct a Game to be played with the indicated players on a copy of the board b
// The player on the south side always moves first
Game::Game(const Board &b, Player *south, Player *north) : m_b(b), m_south(south), m_north(north) {}

// Display the game's board in a manner of your choosing, provided you show the
// names of the players and a reasonable representation of the state of the board.
void Game::display() const
{
    int spacing = 2;            // spacing
    int numHoles = m_b.holes(); // # of holes per side
    int m_northLength = m_north->name().length();
    int numOfLines = (numHoles - 1) * 3 + 1;

    // NORTH's HOLES
    // blank spaces
    for (int i = 0; i < spacing + m_northLength + 2; ++i)
    {
        std::cout << " ";
    }
    // hole #s
    for (int i = 1; i <= numHoles; ++i)
    {
        std::cout << i << "  ";
    }
    std::cout << std::endl;

    // spacing
    for (int i = 0; i < spacing + m_northLength + 2; ++i)
    {
        std::cout << " ";
    }
    // lines
    for (int i = 1; i <= numOfLines; ++i)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    // spacing
    for (int i = 0; i < spacing + m_northLength + 2; ++i)
    {
        std::cout << " ";
    }
    // bean #s
    for (int i = 1; i <= numHoles; ++i)
    {
        std::cout << m_b.beans(NORTH, i) << "  ";
    }
    std::cout << std::endl; // print line

    // NORTH & SOUTH POTS
    std::cout << m_north->name() << "  "; // NORTH's name
    std::cout << m_b.beans(NORTH, 0);     // NORTH pot

    // spacing
    for (int i = 1; i <= numOfLines + 2; ++i)
    {
        std::cout << " ";
    }

    std::cout << m_b.beans(SOUTH, 0);     // SOUTH pot
    std::cout << "  " << m_south->name(); // SOUTH's name
    std::cout << std::endl;               // print line

    // SOUTH's HOLES
    // spacing
    for (int i = 0; i < spacing + m_northLength + 2; ++i)
    {
        std::cout << " ";
    }
    // bean #s
    for (int i = 1; i <= numHoles; ++i)
    {
        std::cout << m_b.beans(SOUTH, i) << "  ";
    }
    std::cout << std::endl;

    // spacing
    for (int i = 0; i < spacing + m_northLength + 2; ++i)
    {
        std::cout << " ";
    }
    // lines
    for (int i = 1; i <= numOfLines; ++i)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    // spacing
    for (int i = 0; i < spacing + m_northLength + 2; ++i)
    {
        std::cout << " ";
    }
    // hole #s
    for (int i = 1; i <= numHoles; ++i)
    {
        std::cout << i << "  ";
    }
    std::cout << std::endl;

    // bean #s
    std::cout << std::endl
              << std::endl; // print line
}

// IF ONE SIDE IS EMPTY SOW EVERYTHING INTO POT

// If the game is over (i.e., the move member function has been called and returned false),
// set over to true; otherwise, set over to false and do not change anything else.
// If the game is over, set hasWinner to true if the game has a winner, or false if it
// resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise,
// set it to the winning side.
void Game::status(bool &over, bool &hasWinner, Side &winner) const
{
    // CHECK IF (Side s) HOLES ARE EMPTY
    // go through (Side s) and OPPONENTS holes
    for (int i = 1; i <= m_b.holes(); ++i)
    { // if no holes with beans on (Side s) & OPPONENT's side
        if (m_b.beans(SOUTH, i) > 0 || m_b.beans(NORTH, i) > 0)
        {
            over = false; // more beans on either eide
            return;       // dont change enything else
        }
    }

    // GAME IS OVER
    over = true; // got past the for loop, so game is over

    if (m_b.beans(NORTH, 0) == m_b.beans(SOUTH, 0))
    {
        hasWinner = false;
    }
    // there is a winner
    else
    {
        hasWinner = true;
        // NORTH pot > SOUTH pot
        if (m_b.beans(NORTH, 0) > m_b.beans(SOUTH, 0))
        {
            winner = NORTH;
        }
        // SOUTH pot > NORTH pot
        else
        {
            winner = SOUTH;
        }
    }
}

// Attempt to make a complete move for the player playing side s. "Complete" means that
// the player sows the seeds from a hole and takes any additional turns required or
// completes a capture. Whenever the player gets an additional turn, you should display
// the board so someone looking at the screen can follow what's happening. If the move can
// be completed, return true; if not, because the move is not yet completed but side s has
// no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that
// opponent's pot and return false.
bool Game::move(Side s)
{
    Side endSide;
    int endHole;

    while (true)
    {
        // CHECK IF (Side s) HOLES ARE EMPTY
        bool noMoreBeans = true;
        // go through (Side s) holes
        for (int i = 1; i <= m_b.holes(); ++i)
        { // if no (Side s) holes with beans to sow
            if (m_b.beans(s, i) > 0)
            {
                noMoreBeans = false; // set no more beans to false
                break;
            }
        }

        // no more beans
        if (noMoreBeans)
        {
            // sweep OPPONENT's holes into OPPONENT's pot
            for (int i = 1; i <= m_b.holes(); ++i)
            {
                m_b.moveToPot(opponent(s), i, opponent(s));
            }
            display();

            return false;
        }
        // IF (Side s) HOLES ARE NOT EMPTY, CONTINUE
        else
        {
            int hole;
            // SOUTH
            if (s)
            {
                hole = m_south->chooseMove(m_b, s);
            }
            // NORTH
            else
            {
                hole = m_north->chooseMove(m_b, s);
            }

            // not successful sow
            if (m_b.sow(s, hole, endSide, endHole) == false)
            {
                return false;
            }
            // successful sow
            else
            {
                // SOUTH
                if (s)
                {
                    if (m_south->isInteractive() == false)
                    {
                        std::cout << m_south->name() << " sowed from their hole " << hole << std::endl;
                    }
                }
                // NORTH
                else
                {
                    if (m_north->isInteractive() == false)
                    {
                        std::cout << m_north->name() << " sowed from their hole " << hole << std::endl;
                    }
                }

                // landed in (Side s) pot
                if (endSide == s && endHole == 0)
                {
                    // player gets another turn, continue with while loop
                    display();
                }
                // did not land in (Side s) pot
                else
                { // check if there is a capture
                    // If the last bean was placed in one of the player's own holes
                    // AND it was empty just a moment before
                    // AND if the opponent's hole directly opposite from that hole is not empty
                    if ((endSide == s) && (m_b.beans(s, endHole) - 1 == 0) && (m_b.beans(opponent(s), endHole) != 0))
                    {
                        // then that last bean and all beans in the opponent's hole directly
                        // opposite from that hole are put into the player's pot, and the turn ends
                        // add to SOUTH pot
                        m_b.moveToPot(s, endHole, s);
                        m_b.moveToPot(opponent(s), endHole, s);
                    }

                    break; // end turn
                }
            }
        }
    }

    display();

    return true; // turn completed
}

// Play the game. Display the progress of the game in a manner of your choosing, provided
// that someone looking at the screen can follow what's happening. If neither player is
// interactive, then to keep the display from quickly scrolling through the whole game,
// it would be reasonable periodically to prompt the viewer to press ENTER to continue
// and not proceed until ENTER is pressed. (The ignore function for input streams is useful
// here.) Announce the winner at the end of the game. You can apportion to your liking the
// responsibility for displaying the board between this function and the move function.
void Game::play()
{
    bool moveBool;
    bool over = false;
    bool hasWinner;
    Side winner;

    Side currentSide = SOUTH;
    std::cout << "--------------------------" << std::endl;
    std::cout << "This is the intitial board" << std::endl;
    std::cout << "--------------------------" << std::endl;

    display();

    while (true)
    {
        // play game
        moveBool = move(currentSide);

        // if NOT INTERACTIVE
        if ((currentSide == SOUTH) && (m_south->isInteractive() == false))
        {
            // so plays dont scroll too fast
            std::cout << "Press ENTER to continue..." << std::endl;
            std::cin.get(); // Wait for the user to press ENTER
        }
        else if ((currentSide == NORTH) && (m_north->isInteractive() == false))
        {
            // so plays dont scroll too fast
            std::cout << "Press ENTER to continue..." << std::endl;
            std::cin.get(); // Wait for the user to press ENTER
        }

        if (!moveBool)
        {
            over = true;
        }

        status(over, hasWinner, winner);

        if (over)
        {
            if (hasWinner)
            {
                // set winner name
                std::string winnerName = "";
                (winner == SOUTH) ? winnerName = m_south->name() : winnerName = m_north->name();

                std::cout << "The winner is: " << winnerName << std::endl;
                display();
                break;
            }
            else
            {
                std::cout << "There is no winner. The game ended in a TIE." << std::endl;
                display();
                break;
            }
        }

        (currentSide == SOUTH) ? (currentSide = NORTH) : (currentSide = SOUTH); // alternate sides
    }
}

// Return the number of beans in the indicated hole or pot of the game's board, or −1 if
// the hole number is invalid. This function exists so that we and you can more easily test your program.
int Game::beans(Side s, int hole) const
{
    if (s)
    { // South
        return m_b.beans(SOUTH, hole);
    }
    else
    { // North
        return m_b.beans(NORTH, hole);
    }
}