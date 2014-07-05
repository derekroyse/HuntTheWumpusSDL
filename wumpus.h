#ifndef WUMPUS_H
#define WUMPUS_H
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int XSIZE = 5;
const int YSIZE = 5;


/************************************************
Room class

Member functions:
    Room()          Initializes a Room with all values = 0
    setAdjacent()   Determines and assigns all 4 adjacent values
                    Sets adjacent value to 0 if non-existant.
    setID()         Sets the Room's ID attribute
    setPit()        Sets the Room's isPit attribute
    setBat()        Sets the Room's isBat attribute
    setWumpus()     Sets the Room's isWumpus attribute
    setPlayer()     Sets the Room's isPlayer attribute
    setArrow()      Sets the Room's hasArrow attribute

    getID()         Returns the Room's ID
    getPit()        Returns whether or not the room has a pit
    getBat()        Returns whether or not the room has a bat
    getWumpus()     Returns whether or not the room has a Wumpus
    getPlayer()     Returns whether or not the room contains the player
    getArrow()      Returns whether or not the room contains an arrow
    getAdjacent1()  Returns the ID of the room to the West (left) of the calling room
    getAdjacent2()  Returns the ID of the room to the East (right) of the calling room
    getAdjacent3()  Returns the ID of the room to the North (above) of the calling room
    getAdjacent4()  Returns the ID of the room to the South (below) of the calling room
*************************************************/
class Room
{
    private:
        int id;
        bool isPit;
        bool isBat;
        bool isWumpus;
        bool isPlayer;
        bool hasArrow;

        // West/East/North/South
        int adjacent1;
        int adjacent2;
        int adjacent3;
        int adjacent4;

    public:
        // Default constructor initializes all attributes to 0.
        Room()
        {
            id = 0;
            isPit = 0;
            isBat = 0;
            isWumpus = 0;
            isPlayer = 0;
            hasArrow = 0;

            // West/East/North/South
            adjacent1 = 0;
            adjacent2 = 0;
            adjacent3 = 0;
            adjacent4 = 0;
        }

        // Dynamically determines and assigns adjacent rooms.
        void setAdjacent(int number, int target)
        {
            switch (number)
                {
                    case 1:
                        adjacent1 = target;
                        break;
                    case 2:
                        adjacent2 = target;
                        break;
                    case 3:
                        adjacent3 = target;
                        break;
                    case 4:
                        adjacent4 = target;
                        break;
                }
        }

        // All methods beyond this point are simnple setters and getters.
        void setID(int input)
        {
            id = input;
        }

        int getID()
        {
            return id;
        }

        int getPit()
        {
            return isPit;
        }

        int getBat()
        {
            return isBat;
        }

        int getWumpus()
        {
            return isWumpus;
        }

        int getPlayer()
        {
            return isPlayer;
        }

        int getArrow()
        {
            return hasArrow;
        }

        void setPit(int input)
        {
            isPit = input;
        }

        void setBat(int input)
        {
            isBat = input;
        }

        void setWumpus(int input)
        {
            isWumpus = input;
        }

        void setPlayer(int input)
        {
            isPlayer = input;
        }

        void setArrow(int input)
        {
            hasArrow = input;
        }

        int getAdjacent1()
        {
            return adjacent1;
        }

        int getAdjacent2()
        {
            return adjacent2;
        }

        int getAdjacent3()
        {
            return adjacent3;
        }

        int getAdjacent4()
        {
            return adjacent4;
        }

};

/************************************************
Board class

Member functions:
    Board()          Initializes a board with an empty array.
    generateBoard()  Generates a new array of empty rooms, and establishes adjacencies.
    populateBoard()  Randomly assigns hazards and creatures to rooms.
    printBoard()     Prints the board to the screen.
*************************************************/
class Board
{
  private:
  public:
    Room array[XSIZE][YSIZE];
    Board() {}

    // Fills a board's array with empty Rooms and assigns their adjacent Rooms.
    // Also initializes all attributes to properly reset the board for a new game.
    void generateBoard()
    {
        int x = 1;
        for (int i = 0; i < XSIZE; i++)
            for (int j = 0; j < YSIZE; j++)
            {
                array[i][j].setID(x);
                array[i][j].setPlayer(0);
                array[i][j].setWumpus(0);
                array[i][j].setArrow(0);
                array[i][j].setPit(0);
                array[i][j].setBat(0);
                x++;
            }

    // If the adjacent room is out of bounds, set it to zero, otherwise, set it to the adjacent room.
        for (int i = 0; i < XSIZE; i++)
            for (int j = 0; j < YSIZE; j++)
            {

                if (j != 0)
                    array[i][j].setAdjacent(1, array[i][j-1].getID());
                if (j != YSIZE-1)
                    array[i][j].setAdjacent(2, array[i][j+1].getID());
                if (i != 0)
                    array[i][j].setAdjacent(3, array[i-1][j].getID());
                if (i != XSIZE-1)
                    array[i][j].setAdjacent(4, array[i+1][j].getID());

            }
    }

    // Creates one pit, bat, and arrow randomly on the board.
    // Also randomly spawns the player and the wumpus.
    void populateBoard()
    {
        int x;
        int y;
        int counter = 0;
        x = rand() % XSIZE;
        y = rand() % YSIZE;

        while (counter < 5)
        {
            if(array[x][y].getBat() == 0 && array[x][y].getWumpus() == 0 &&
               array[x][y].getPit() == 0 && array[x][y].getPlayer() == 0 && array[x][y].getArrow() == 0)
            {
                switch (counter)
                {
                    case 0:
                        array[x][y].setPit(1);
                        break;
                    case 1:
                        array[x][y].setBat(1);
                        break;
                    case 2:
                        array[x][y].setPlayer(1);
                        break;
                    case 3:
                        array[x][y].setWumpus(1);
                        break;
                    case 4:
                        array[x][y].setArrow(1);
                        break;
                }
                counter++;
            }
            else
            {
                x = rand() % XSIZE;
                y = rand() % YSIZE;
            }
        }
    };

    // Displays the board (mainly for testing).
    void printBoard()
    {
    for (int i = 0; i < XSIZE; i++)
        {
            for (int j = 0; j < YSIZE; j++)
            {
               if (array[i][j].getArrow() == 1)
                    cout << "A ";
               else if (array[i][j].getBat() == 1)
                    cout << "B ";
               else if (array[i][j].getPlayer() == 1)
                    cout << "X ";
               else if (array[i][j].getWumpus() == 1)
                    cout << "W ";
               else if (array[i][j].getPit() == 1)
                    cout << "P ";
               else
                    cout << "- ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
};

/************************************************
Player class

Member functions:
    Player()            Initializes a player with 5 arrows (default)
    move()              Moves the player in a cardinal direction.
    shoot()             Shoots an arrow in a cardinal direction.
    displayWarnings()   Display warnings about any hazards adjacent to the player.
    displayActions()    Display the directions in which the player may move and if they can shoot.
    updateLocation()    Update the player's location attribute.
    getArrows()         Return the player's number of arrows.
    batTeleport()       The bat teleports the player to a random unoccupied room.
*************************************************/
class Player
{
    private:
       Room location;
       int arrows;
    public:
        Player()
        {
            arrows = 5;
        }

	// Move player to destination, detect destination Room attributes and respond accordingly.
    std::string move(int input, Board &board){
		std::string returnString = "";
        // Target = destination Room.
        // x + y = destination Room coordinates.

        int target;
        int y;
        int x;

        // Choose a destination based on player input.
        switch (input)
        {
            case 'W':
            case 'w':
            {
				returnString = "You moved West.";
                target = location.getAdjacent1();
                break;
            }
            case 'E':
            case 'e':
            {
				returnString = "You moved East.";
                target = location.getAdjacent2();
                break;
            }
            case 'N':
            case 'n':
            {
				returnString = "You moved North.";
                target = location.getAdjacent3();
                break;
            }
            case 'S':
            case 's':
            {
				returnString = "You moved South.";
                target = location.getAdjacent4();
                break;
            }
        }

        // If the player chose to move in a direction that has no adjacent room,
        // control returns to main.
        if (target == 0)
        {
			returnString = "You cannot move in that direction!";
			return returnString;
			//return 0;
        }

        // Assign destination coordinates
        for (int a = 0; a < XSIZE; a++)
        {
            for (int b = 0; b < YSIZE; b++)
            {
                if (board.array[a][b].getID() == target)
                {
                    x = a;
                    y = b;
                }
            }
        }

        // Move player to destination, detect destination Room attributes and respond accordingly.
            for (int i = 0; i < XSIZE; i++)
            {
                for (int j = 0; j < YSIZE; j++)
                {
                    if (board.array[i][j].getPlayer() == 1)
                    {
                        board.array[i][j].setPlayer(0);
                        if (board.array[x][y].getPit() == 1)
                        {
							returnString += "YOU FELL IN A PIT!";
                            //return 1;
                        }

                        else if (board.array[x][y].getArrow() == 1)
                        {
							returnString += "YOU FOUND AN ARROW!";
                            board.array[x][y].setArrow(0);
                            board.array[x][y].setPlayer(1);
                            arrows++;
                            //return 0;
                        }
                        else if (board.array[x][y].getBat() == 1)
                        {
                            board.array[i][j].setPlayer(1);
							returnString += "A Superbat has taken you to an unknown location in the cavern!";
                            this -> batTeleport(board);
                        }
                        else if (board.array[x][y].getWumpus() == 1)
                        {
							returnString += "You stumbled upon a Wumpus and were prompty eaten by him.";
                            //cout << "GAME OVER" << endl;
                            //return 1;
                        }
                        else
                        {
                            board.array[x][y].setPlayer(1);
                            //return 0;
                        }
                    }
                }
            }

			return returnString;
	} // end move method


    bool shoot(char input, Board board)
    {
        int x;
        int y;
        int high;
        int low;

        // Search for player coordinates.
        for (int a = 0; a < XSIZE; a++)
        {
            for (int b = 0; b < YSIZE; b++)
            {
                if (board.array[a][b].getPlayer() == 1)
                {
                    x = a;
                    y = b;
                }
            }
        }

        // Fire an arrow into the appropriate room given player input.
        // If the Wumpus is killed a 1 is returned to the main() sentinel
        // which ends the game. Otherwise the game continues (minus one arrow).
        switch (input)
        {
            case 'W':
            case 'w':
                arrows--;
                    for (int j = 0; j < y; j++)
                    {
                        if (board.array[x][j].getWumpus() == 1)
                        {
                            cout << "You killed the Wumpus!" << endl;
                            return 1;
                        }
                    }
                cout << "You missed!" << endl;
                return 0;
                break;
            case 'E':
            case 'e':
                arrows--;
                    for (int j = y+1; j < YSIZE; j++)
                        if (board.array[x][j].getWumpus() == 1)
                        {
                            cout << "You killed the Wumpus!" << endl;
                            return 1;
                        }
                cout << "You missed!" << endl;
                return 0;
                break;;
            case 'N':
            case 'n':
                arrows--;
                for (int i = 0; i < x; i++)
                        if (board.array[i][y].getWumpus() == 1)
                        {
                            cout << "You killed the Wumpus!" << endl;
                            return 1;
                        }
                cout << "You missed!" << endl;
                return 0;
                break;
            case 'S':
            case 's':
                arrows--;
                for (int i = x+1; i < XSIZE; i++)
                        if (board.array[i][y].getWumpus() == 1)
                        {
                            cout << "You killed the Wumpus!" << endl;
                            return 1;
                        }
                cout << "You missed!" << endl;
                return 0;
                break;
            default:
                cout << "Invalid input!" << endl;
                return 0;
        }
    }

    // Displays which directions the player can move in and
    // whether or not they can shoot.
    std::string displayActions1()
    {
		std::string returnString = "You can move in the following directions:";

        if (location.getAdjacent1() != 0)
            returnString += " (W)est";
        if (location.getAdjacent2() != 0)
			returnString += " (E)ast";
        if (location.getAdjacent3() != 0)
			returnString += " (N)orth";
        if (location.getAdjacent4() != 0)
			returnString += " (S)outh";

		return returnString;
    }

	std::string displayActions2()
	{
		std::string returnString;

		if (arrows > 0)
			returnString += "You also have arrows and may shoot!";

		return returnString;

	}

    // Displays warnings if any of the player's adjacent rooms
    // contains a bat.
    std::string displayBatWarning(Board board)
    {
		std::string returnString = "";

        int adj1 = location.getAdjacent1();
        int adj2 = location.getAdjacent2();
        int adj3 = location.getAdjacent3();
        int adj4 = location.getAdjacent4();

        // Searches the board for all player-adjacent Rooms. If any contain hazards
        // a warning is displayed.
            for (int i = 0; i < XSIZE; i++)
                {
                    for (int j = 0; j < YSIZE; j++)
                    {
                        if (board.array[i][j].getID() == adj1 || board.array[i][j].getID() == adj2 ||
                            board.array[i][j].getID() == adj3 || board.array[i][j].getID() == adj4)
                        {
							if (board.array[i][j].getBat() == 1)
								returnString += "You hear a soft screeching.";
                        }

                    }
                }

			return returnString;
    }

	// Displays warnings if any of the player's adjacent rooms
	// contains a Wumpus.
	std::string displayWumpusWarning(Board board)
	{
		std::string returnString = "";

		int adj1 = location.getAdjacent1();
		int adj2 = location.getAdjacent2();
		int adj3 = location.getAdjacent3();
		int adj4 = location.getAdjacent4();

		// Searches the board for all player-adjacent Rooms. If any contain hazards
		// a warning is displayed.
		for (int i = 0; i < XSIZE; i++)
		{
			for (int j = 0; j < YSIZE; j++)
			{
				if (board.array[i][j].getID() == adj1 || board.array[i][j].getID() == adj2 ||
					board.array[i][j].getID() == adj3 || board.array[i][j].getID() == adj4)
				{
					if (board.array[i][j].getWumpus() == 1)
						returnString += "You detect a musky scent.";
				}

			}
		}

		return returnString;
	}

	// Displays warnings if any of the player's adjacent rooms
	// contains a pit.
	std::string displayPitWarning(Board board)
	{
		std::string returnString = "";

		int adj1 = location.getAdjacent1();
		int adj2 = location.getAdjacent2();
		int adj3 = location.getAdjacent3();
		int adj4 = location.getAdjacent4();

		// Searches the board for all player-adjacent Rooms. If any contain hazards
		// a warning is displayed.
		for (int i = 0; i < XSIZE; i++)
		{
			for (int j = 0; j < YSIZE; j++)
			{
				if (board.array[i][j].getID() == adj1 || board.array[i][j].getID() == adj2 ||
					board.array[i][j].getID() == adj3 || board.array[i][j].getID() == adj4)
				{
					if (board.array[i][j].getPit() == 1)
						returnString += "You feel a chilly draft.";
				}

			}
		}

		return returnString;
	}

    // Updates the Player's location attribute.
    void updateLocation(Board &board)
    {
        for (int i = 0; i < XSIZE; i++)
        {
            for (int j = 0; j < YSIZE; j++)
            {
                if (board.array[i][j].getPlayer() == 1)
                    location = board.array[i][j];
            }
        }

    }

    int getArrows()
        {
            return arrows;
        }

    void batTeleport(Board &board)
    {
        int x = rand() % XSIZE;
        int y = rand() % YSIZE;
        int playerx = 0;
        int playery = 0;
        bool sentinel = 0;

        // Determine player's coordinates.
        for (int i = 0; i < XSIZE; i++)
            for (int j = 0; j < YSIZE; j++)
                if (board.array[i][j].getPlayer() == 1)
                {
                    playerx = i;
                    playery = j;
                }

        // If the random Room is empty, drop the player;
        // If the random Room is occupied, generate new random coordinates
        // and repeat.
        while (sentinel == 0)
        {
            if(board.array[x][y].getBat() == 0 && board.array[x][y].getWumpus() == 0 &&
               board.array[x][y].getPit() == 0 && board.array[x][y].getPlayer() == 0 &&
               board.array[x][y].getArrow() == 0)
            {
               board.array[playerx][playery].setPlayer(0);
               board.array[x][y].setPlayer(1);
               sentinel++;
            }
            else
            {
                x = rand() % XSIZE;
                y = rand() % YSIZE;
            }
        }

    }
};

/************************************************
Wumpus class

Member functions:
    Wumpus()            Initializes a Wumpus
    move()              Moves the Wumpus in a cardinal direction.
    updateLocation()    Update the Wumpus' location attribute.
*************************************************/
class Wumpus
{
    private:
       Room location;
    public:
        Wumpus()
        {
        }

        // Move Wumpus.
        bool move(Board &board)
        {
            // Target = destination Room.
            // x + y = destination Room coordinates.

            int target = 0;
            int random = rand() % 4;
            int y;
            int x;

            // Randomly choose a destination.
            while (target == 0)
            {
                random = rand() % 4;
                switch (random)
                {
                    case 0:
                    {
                        target = location.getAdjacent1();
                        break;
                    }
                    case 1:
                    {
                        target = location.getAdjacent2();
                        break;
                    }
                    case 2:
                    {
                        target = location.getAdjacent3();
                        break;
                    }
                    case 3:
                    {
                        target = location.getAdjacent4();
                        break;
                    }
                }
            }


            // Assign destination coordinates
            for (int a = 0; a < XSIZE; a++)
            {
                for (int b = 0; b < YSIZE; b++)
                {
                    if (board.array[a][b].getID() == target)
                    {
                        x = a;
                        y = b;
                    }
                }
            }

            // Move wumpus to destination, detect destination Room attributes and respond accordingly.
                for (int i = 0; i < XSIZE; i++)
                {
                    for (int j = 0; j < YSIZE; j++)
                    {
                        if (board.array[i][j].getWumpus() == 1)
                        {
                            board.array[i][j].setWumpus(0);
                            if (board.array[x][y].getPlayer() == 1)
                            {
                                cout << "The Wumpus found you!" << endl;
                                return 1;
                            }
                            else
                            {
                                cout << "You hear the Wumpus moving around..." << endl;
                                board.array[x][y].setWumpus(1);
                                return 0;
                            }
                        }
                    }
                }
        } // end move method

    // Updates the Wumpus's location attribute.
    void updateLocation(Board &board)
    {
        for (int i = 0; i < XSIZE; i++)
        {
            for (int j = 0; j < YSIZE; j++)
            {
                if (board.array[i][j].getWumpus() == 1)
                    location = board.array[i][j];
            }
        }

    }
};

#endif
