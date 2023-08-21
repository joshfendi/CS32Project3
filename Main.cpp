#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Game.h"

using namespace std;

int main()
{
    int number_of_holes = 6;
    int beans_per_hole = 4;

    Board myBoard(number_of_holes, beans_per_hole);

    HumanPlayer player1("Human 1");

// Player 2
   SmartPlayer player2("Smart Player");
//  BadPlayer player2("Bad Player");
//  HumanPlayer player2("Human 2");

    

    Game my_game(myBoard, &player1, &player2);
    my_game.play();
}







// // 1
// #include "Board.h"
// // #include "Board.cpp"
// 	#include "Side.h"

// 	#include <iostream>
// 	#include <cassert>
// 	using namespace std;

// 	void doBoardTests()
// 	{
// 	    Board b(3, 2);

// 	    assert(
//         b.holes() == 3  
//         &&  b.totalBeans() == 12  
//         && b.beans(SOUTH, POT) == 0  
//         &&  
//         b.beansInPlay(SOUTH) == 6
//         );

// 	    b.setBeans(SOUTH, 1, 1);
// 	    b.moveToPot(SOUTH, 2, SOUTH);

// 	    assert(b.totalBeans() == 11  
//         &&  b.beans(SOUTH, 1) == 1  
//         &&  b.beans(SOUTH, 2) == 0  
//         &&  b.beans(SOUTH, POT) == 2  
//         &&  b.beansInPlay(SOUTH) == 3
//         );

// 	    Side es;
// 	    int eh;

// 	    b.sow(SOUTH, 3, es, eh);

// 	    assert(es == NORTH  
//         &&  eh == 3
//         &&  b.beans(SOUTH, 3) == 0
//         &&  b.beans(NORTH, 3) == 3  
//         &&  b.beans(SOUTH, POT) == 3  
//         &&  b.beansInPlay(SOUTH) == 1  
//         &&  b.beansInPlay(NORTH) == 7
//         );
// 	}

// 	int main()
// 	{
// 	    doBoardTests();
// 	    cout << "Passed all tests" << endl;
// 	}








// // 2
// #include "Player.h"
// #include "Player.cpp"
// 	#include "Board.h"
//     #include "Board.cpp"
// 	#include "Side.h"
// 	#include <iostream>
// 	#include <cassert>
// 	using namespace std;

// 	void doPlayerTests()
// 	{
// 	    HumanPlayer hp("Marge");
// 	    assert(hp.name() == "Marge"  &&  hp.isInteractive());
// 	    BadPlayer bp("Homer");
// 	    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
// 	    SmartPlayer sp("Lisa");
// 	    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
// 	    Board b(3, 2);
// 	    b.setBeans(SOUTH, 2, 0);
// 	    cout << "=========" << endl;
// 	    int n = hp.chooseMove(b, SOUTH);
// 	    cout << "=========" << endl;
// 	    assert(n == 1  ||  n == 3);
// 	    n = bp.chooseMove(b, SOUTH);
// 	    assert(n == 1  ||  n == 3);
// 	    n = sp.chooseMove(b, SOUTH);
// 	    assert(n == 1  ||  n == 3);
// 	}

// 	int main()
// 	{
// 	    doPlayerTests();
// 	    cout << "Passed all tests" << endl;
// 	}







// // 3
// #include "Game.h"
// #include "Game.cpp"
// 	#include "Player.h"
//     #include "Player.cpp"
// 	#include "Board.h"
//     #include "Board.cpp"
// 	#include "Side.h"
// 	#include <iostream>
// 	#include <cassert>
// 	using namespace std;

// 	void doGameTests()
// 	{
// 	    BadPlayer bp1("Bart");
// 	    BadPlayer bp2("Homer");
// 	    Board b(3, 0);
// 	    b.setBeans(SOUTH, 1, 2);
// 	    b.setBeans(NORTH, 2, 1);
// 	    b.setBeans(NORTH, 3, 2);
// 	    Game g(b, &bp1, &bp2);
// 	    bool over;
// 	    bool hasWinner;
// 	    Side winner;
// 	      //    Homer
// 	      //   0  1  2
// 	      // 0         0
// 	      //   2  0  0
// 	      //    Bart
// 	    g.status(over, hasWinner, winner);
// 	    assert(
//             !over 
//             && g.beans(NORTH, POT) == 0 
//             && g.beans(SOUTH, POT) == 0 
//             && g.beans(NORTH, 1) == 0 
//             && g.beans(NORTH, 2) == 1 
//             && g.beans(NORTH, 3) == 2 
//             && g.beans(SOUTH, 1) == 2 
//             && g.beans(SOUTH, 2) == 0 
//             && g.beans(SOUTH, 3) == 0
//         );

// 	    g.move(SOUTH);
// 	      //   0  1  0
// 	      // 0         3
// 	      //   0  1  0
// 	    g.status(over, hasWinner, winner);
// 	    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
// 		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
// 		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

// 	    g.move(NORTH);
// 	      //   1  0  0
// 	      // 0         3
// 	      //   0  1  0
// 	    g.status(over, hasWinner, winner);
// 	    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
// 		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
// 		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

// 	    g.move(SOUTH);
// 	      //   1  0  0
// 	      // 0         3
// 	      //   0  0  1
// 	    g.status(over, hasWinner, winner);
// 	    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
// 		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
// 		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

// 	    g.move(NORTH);
// 	      //   0  0  0
// 	      // 1         4
// 	      //   0  0  0
        
// 	    g.status(over, hasWinner, winner);

// 	    assert(
//             over 
//         && g.beans(NORTH, POT) == 1 
//         && g.beans(SOUTH, POT) == 4 
//         && g.beans(NORTH, 1) == 0 
//         && g.beans(NORTH, 2) == 0 
//         && g.beans(NORTH, 3) == 0 
//         && g.beans(SOUTH, 1) == 0 
//         && g.beans(SOUTH, 2) == 0 
//         && g.beans(SOUTH, 3) == 0
//         );
// 	    assert(hasWinner && winner == SOUTH);
// 	}

// 	int main()
// 	{
// 	    doGameTests();
// 	    cout << "Passed all tests" << endl;
// 	}

