//
//  main.cpp
//  Checkers
//
//  Created by Justin Bushue on 4/25/20.
//  Copyright © 2020 Justin Bushue. All rights reserved.
//

/*
 Checkers is a game played on a board checkered with squares of two colors.
 
 Two players compete in checkers to have the last piece on the board.
 
 The game pieces in checkers — which you can also call checkers — are usually red and black.
 
 Players move diagonally on the board, trying to reach the opposite side where their pieces
 can be "kinged," or doubled, giving them more powers.
 
 On the way, a player attempts to jump over her opponent's pieces and capture them.
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string blackSquare = "_", whiteCircle = "x", whiteSquare = " ", blackCircle = "o", whiteKing = "X", blackKing = "O"; //These values will be used all throughout the program

void cls() // Function to clear the screen to have a nice output to the screen
{
	system("cls||clear");
	return;
}

class RecentMoves // Using a stack to keep track of each of the players moves.
{
private:
	struct node
	{
		string value;
		node* next;
		
		node(string value, node* next = nullptr)
		{
			this->value = value;
			this->next = next;
		}
	};
	node* top;
	
public:
	RecentMoves()
	{
		top = nullptr;
	}
	~RecentMoves()
	{
		while(!isEmpty())
			pop();
	}
	
	void clear()
	{
		while(!isEmpty())
			pop();
	}
	
	void push(string str)
	{
		top = new node(str, top);
	}
	string pop()
	{
		
		string str = top->value;
		cout << str << endl;
		node* temp = top;
		top = top->next;
		delete temp;
		return str;
	}
	bool isEmpty()
	{
		if(top == nullptr)
			return true;
		else
			return false;
	}
	
};

class Piece //This base class is the foundation for each type of board object. I.E. white squares, black squares, white circles, black circles.
{
private:
	string color;
	int xcoord , ycoord;
	bool isKing = false;
	
public:
	
	Piece() {}
	Piece(string color, int xcoord, int ycoord, bool isKing)
	{
		this->xcoord = xcoord;
		this->ycoord = ycoord;
		this->color = color;
		this->isKing = isKing;
	}
	string getColor()
	{
		return color;
	}
	void setColor(string color)
	{
		this->color = color;
	}
	
	int getXCoord()
	{
		return xcoord;
	}
	void setXCoord(int xcoord)
	{
		this->xcoord = xcoord;
	}
	
	int getYCoord()
	{
		return ycoord;
	}
	void setYCoord(int ycoord)
	{
		this->ycoord = ycoord;
	}
	
	virtual void setKing(bool isKing)
	{
		this->isKing = isKing;
	}
	
	bool getIsKing()
	{
		return isKing;
	}
	string toString()
	{
		return color;
	}
};

class BlackSquare : public Piece // Derived class of the Piece class
{
public:
	BlackSquare()
	{
		setColor(blackSquare);
	}
};

class WhiteSquare : public Piece // Derived class of the Piece class
{
public:
	WhiteSquare()
	{
		setColor(whiteSquare);
	}
};

class BlackPiece : public Piece // Derived class of the Piece class
{
public:
	BlackPiece()
	{
		setColor(blackCircle);
	}
	void setKing(bool isKing)
	{
		setColor(blackKing);
		Piece::setKing(isKing);
	}
	BlackPiece(string color, bool isKing)
	{
		Piece::setColor(color);
		Piece::setKing(isKing);
	}
};

class WhitePiece : public Piece // Derived class of the Piece class
{
public:
	WhitePiece()
	{
		setColor(whiteCircle);
	}
	WhitePiece(string color, bool isKing)
	{
		Piece::setColor(color);
		Piece::setKing(isKing);
	}
	void setKing(bool isKing)
	{
		setColor(whiteKing);
		Piece::setKing(isKing);
	}
};

class Board // This class handles the creation of the board to play on as well as putting the checkers in their proper places.
{
public:
	Piece* board[8][8]; // The board is made up of an array of Piece object pointers.
	
	Board()
	{
		initializeBlankBoard(); // When the board object is instanciated it will fill in the array with the white and black squares.
	}
	void initializeBlankBoard() // In this function I am using %2 to determine if the row or column is even or odd to know which color square to use.
	{
		for(int row = 0 ; row < 8 ; row++)
		{
			for(int col = 0 ; col < 8 ; col++)
			{
				if(row % 2 == 0)
				{
					if(col % 2 == 0)
					{
						board[row][col] = new WhiteSquare;
					}
					else
					{
						board[row][col] = new BlackSquare;
					}
				}
				else if(row % 2 != 0)
				{
					if(col % 2 == 0)
					{
						board[row][col] = new BlackSquare;
					}
					else
					{
						board[row][col] = new WhiteSquare;
					}
				}
			}
		}
	}
	void printBoardNoGuide() // This function isn't called in the final program but was used to make debugging easier.
	{
		for(int row = 0 ; row < 8 ; row++)
		{
			for(int col = 0 ; col < 8 ; col++)
			{
				cout << board[row][col]->toString() << ' ';
			}
			cout << endl;
		}
	}
	void InitialPosBoard() // This function put each kind of checker on the board at their proper locations.
	{
		for(int row = 0 ; row < 3 ; row++)
		{
			for(int col = 0 ; col < 8 ; col++)
			{
				if(board[row][col]->getColor() == blackSquare)
				{
					delete board[row][col]; // Since I filled the board array with white and black square objects I have to delete the one where I am placing a checker piece.
					board[row][col] = new BlackPiece; // Filling in the empty index with a new BlackPiece object.
				}
			}
		}
		for(int row = 5 ; row < 8 ; row++)
		{
			for(int col = 0 ; col < 8 ; col++)
			{
				if(board[row][col]->getColor() == blackSquare)
				{
					delete board[row][col];
					board[row][col] = new WhitePiece;
				}
			}
		}
	}
	void printBoard() // This function simply prints out the board with the number guides.
	{
		cout << "------------------" << endl;
		cout << "|0 1 2 3 4 5 6 7 |" << endl;
		cout << "|----------------|---|" << endl;
		for(int row = 0 ; row < 8 ; row++)
		{
			cout << "|" ;
			for(int col = 0 ; col < 8 ; col++)
			{
				cout << board[row][col]->toString() << ' ';
			}
			cout << "| " << row << " |" << endl;
		}
		cout << "|----------------|---|" << endl << endl;
	}
	Piece* getPieceAt(int row, int col) // This function will let us recieve the pointer of the object that is stored in the board at the particular coordinates.
	{
		return board[row][col];
	}
};

class Checkers // This is the game driver class that houses the functions for movement as well as checking to see if the game is over as well as a few other tasks.
{
private:
	
	Board b; //Instancing a board object.
	RecentMoves white, black; // Instancing 2 stacks one for each players moves.
	
public:
	
	Checkers()
	{
		b.InitialPosBoard(); // Since the board will be just black and white squares from the constructor of the board class we will need to call the function to put the checker pieces in place.
	}
	
	void endGameWhite() // This function calls the function that loops the function pop() in the stack.
	{
		white.clear();
	}
	void endGameBlack()
	{
		black.clear();
	}
	
	bool moveWhiteForward(int fromRow, int fromCol, bool isLeft) // This function does all the checking of if the checker piece selected can move to the selected spot as well as actually "moving" the piece if it can.
	{
		int toRow = fromRow - 1, jumpRow = toRow - 1;
		ostringstream sstream;
		
		if(fromRow == 0)
			return false;
		
		if(b.getPieceAt(fromRow, fromCol)->getColor() == whiteCircle || b.getPieceAt(fromRow, fromCol)->getColor() == whiteKing) // If the player selected a white piece
		{
			if(isLeft && fromCol != 0) //If they selected to go forward and to the left as well as guarding against going out of bounds of the array.
			{
				int toCol = fromCol - 1, jumpCol = toCol - 1;
				
				if(b.getPieceAt(toRow, toCol)->getColor() == blackCircle || b.getPieceAt(toRow, toCol)->getColor() == blackKing) //JUMPING! If the place they are moving to is a black piece
				{
					if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackSquare) // JUMPING! If the place they are jumping to is a black square
					{
						if(b.getPieceAt(fromRow, fromCol)->getIsKing() == true) // If the piece that is being moved is a king it will create a new king piece object at the destination
						{
							delete b.getPieceAt(jumpRow, jumpCol);
							b.board[jumpRow][jumpCol] = new WhitePiece(whiteKing,true); // Calling the overload constructor to ensure the piece will be a king.
						}
						else // If the piece is not a king then it will do a regular piece at the destination.
						{
							delete b.getPieceAt(jumpRow, jumpCol);
							b.board[jumpRow][jumpCol] = new WhitePiece;
						}
						delete b.getPieceAt(fromRow, fromCol); // Deleting the source of the movement
						b.board[fromRow][fromCol] = new BlackSquare; // Creating a new black square to replace the old piece
						delete b.getPieceAt(toRow, toCol); // Deleting the first diaginal piece which would be the opposing players piece
						b.board[toRow][toCol] = new BlackSquare; // Creating a new black square to replace the old piece
						
						sstream << fromRow << ":" << fromCol << " to " << jumpRow << ":" << jumpCol; // Putting the information of the jump/move to a string stream to better format.
						white.push(sstream.str()); // Pushing the string streams string version to the stack.
						
						if(b.getPieceAt(jumpRow, jumpCol)->getColor() == whiteKing)
							kingMultiJump(jumpRow, jumpCol, whiteKing);
						else
							multiJump(jumpRow,jumpCol,whiteCircle);
						
						if(jumpRow == 0 && b.getPieceAt(jumpRow, jumpCol)->getIsKing() != true) // This is checking for if a piece jumps/moves to the further row so that piece can be kinged.
						{
							cls();
							string cont;
							cout << jumpRow << ":" << jumpCol << " You're piece was kinged by this jump!!\nPress any key and enter to continue: ";
							cin >> cont;
							b.getPieceAt(jumpRow, jumpCol)->setKing(true);
						}
						return true;
					}
				}
				if(b.getPieceAt(toRow, toCol)->getColor() == blackSquare) //If moving to a black square
				{
					if(b.getPieceAt(fromRow, fromCol)->getIsKing() == true) // If the piece that is being moved is a king it will create a new king piece object at the destination
					{
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new WhitePiece(whiteKing,true);
					}
					else
					{
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new WhitePiece;
					}
					delete b.getPieceAt(fromRow, fromCol); // Deleting the source of the movement
					b.board[fromRow][fromCol] = new BlackSquare; // Deleting the first diaginal piece
					
					sstream << fromRow << ":" << fromCol << " to " << toRow << ":" << toCol;
					white.push(sstream.str());
					if(toRow == 0 && b.getPieceAt(toRow, toCol)->getIsKing() != true)
					{
						cls();
						string cont;
						cout << toRow << ":" << toCol << " You're piece was kinged by this move!!\nPress any key and enter to continue: ";
						cin >> cont;
						b.getPieceAt(toRow, toCol)->setKing(true);
					}
					return true;
				}
			}
			if((!isLeft) && fromCol != 7) //If they select to go forward and to the right the rest of this function almost identical to the first part with exception to values of toCol, jumpCol
			{
				int toCol = fromCol + 1, jumpCol = toCol + 1;
				
				if(b.getPieceAt(toRow, toCol)->getColor() == blackCircle || b.getPieceAt(toRow, toCol)->getColor() == blackKing) //JUMPING!
				{
					if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackSquare) //Jumping!
					{
						if(b.getPieceAt(fromRow, fromCol)->getIsKing() == true)
						{
							delete b.getPieceAt(jumpRow, jumpCol);
							b.board[jumpRow][jumpCol] = new WhitePiece(whiteKing,true);
						}
						else
						{
							delete b.getPieceAt(jumpRow, jumpCol);
							b.board[jumpRow][jumpCol] = new WhitePiece;
						}
						delete b.getPieceAt(fromRow, fromCol);
						b.board[fromRow][fromCol] = new BlackSquare;
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackSquare;
						sstream << fromRow << ":" << fromCol << " to " << jumpRow << ":" << jumpCol;
						white.push(sstream.str());
						
						if(b.getPieceAt(jumpRow, jumpCol)->getColor() == whiteKing)
							kingMultiJump(jumpRow, jumpCol, whiteKing);
						else
							multiJump(jumpRow,jumpCol,whiteCircle);
						if(jumpRow == 0 && b.getPieceAt(jumpRow, jumpCol)->getIsKing() != true)
						{
							cls();
							string cont;
							cout << jumpRow << ":" << jumpCol << " You're piece was kinged by this jump!!\nPress any key and enter to continue: ";
							cin >> cont;
							b.getPieceAt(jumpRow, jumpCol)->setKing(true);
						}
						return true;
					}
				}
				if(b.getPieceAt(toRow, toCol)->getColor() == blackSquare) //If moving to a black square
				{
					if(b.getPieceAt(fromRow, fromCol)->getIsKing() == true)
					{
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new WhitePiece(whiteKing,true);
					}
					else
					{
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new WhitePiece;
					}
					delete b.getPieceAt(fromRow, fromCol);
					b.board[fromRow][fromCol] = new BlackSquare;
					sstream << fromRow << ":" << fromCol << " to " << toRow << ":" << toCol;
					white.push(sstream.str());
					if(toRow == 0 && b.getPieceAt(toRow, toCol)->getIsKing() != true)
					{
						cls();
						string cont;
						cout << toRow << ":" << toCol << " You're piece was kinged by this move!!\nPress any key and enter to continue: ";
						cin >> cont;
						b.getPieceAt(toRow, toCol)->setKing(true);
					}
					return true;
				}
			}
		}
		return false;
	}
	
	bool moveWhiteBackward(int fromRow, int fromCol, bool isLeft) // This function is used only after a piece has been kinged and their are moving backwards.
	{
		/*
		 This function is a more similar to the blackMoveForward function rather than the whiteMoveForward function
		 because white moving back is the same as black moving forward.
		 Of course there are differences such as which checker pieces to check for and
		 since we already know the checker is going to be a king e only have to do a check
		 at the beginning of the function just to make sure the user didn't bug their way in.
		 */
		int toRow = fromRow + 1, jumpRow = toRow + 1;
		ostringstream sstream;
		
		if(b.getPieceAt(fromRow, fromCol)->getColor() == whiteKing) // If the player selected a white piece
		{
			if(isLeft && fromCol != 0) //If they selected to go forward and to the left
			{
				int toCol = fromCol - 1, jumpCol = toCol - 1;
				
				if((b.getPieceAt(toRow, toCol)->getColor() == blackCircle || b.getPieceAt(toRow, toCol)->getColor() == blackKing)) //JUMPING! If the place they are moving to is a black piece
				{
					if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackSquare) // JUMPING! If the place they are jumping to is a black square
					{
						delete b.getPieceAt(fromRow, fromCol);
						b.board[fromRow][fromCol] = new BlackSquare;
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackSquare;
						delete b.getPieceAt(jumpRow, jumpCol);
						b.board[jumpRow][jumpCol] = new WhitePiece(whiteKing, true);
						sstream << fromRow << ":" << fromCol << " to " << jumpRow << ":" << jumpCol;
						white.push(sstream.str());
						kingMultiJump(jumpRow, jumpCol, whiteKing);
						
						return true;
					}
				}
				else if(b.getPieceAt(toRow, toCol)->getColor() == blackSquare) //If moving to a black square
				{
					delete b.getPieceAt(fromRow, fromCol);
					b.board[fromRow][fromCol] = new BlackSquare;
					delete b.getPieceAt(toRow, toCol);
					b.board[toRow][toCol] = new WhitePiece(whiteKing, true);
					sstream << fromRow << ":" << fromCol << " to " << toRow << ":" << toCol;
					white.push(sstream.str());
					return true;
				}
			}
			else if(!isLeft && fromCol != 7) //If they select to go forward and to the right
			{
				int toCol = fromCol + 1, jumpCol = toCol + 1;
				
				if((b.getPieceAt(toRow, toCol)->getColor() == blackCircle || b.getPieceAt(toRow, toCol)->getColor() == blackKing)) //JUMPING!
				{
					if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackSquare) //Jumping!
					{
						delete b.getPieceAt(fromRow, fromCol);
						b.board[fromRow][fromCol] = new BlackSquare;
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackSquare;
						delete b.getPieceAt(jumpRow, jumpCol);
						b.board[jumpRow][jumpCol] = new WhitePiece(whiteKing, true);
						sstream << fromRow << ":" << fromCol << " to " << jumpRow << ":" << jumpCol;
						white.push(sstream.str());
						return true;
					}
				}
				if(b.getPieceAt(toRow, toCol)->getColor() == blackSquare) //If moving to a black square
				{
					delete b.getPieceAt(fromRow, fromCol);
					b.board[fromRow][fromCol] = new BlackSquare;
					delete b.getPieceAt(toRow, toCol);
					b.board[toRow][toCol] = new WhitePiece(whiteKing, true);
					sstream << fromRow << ":" << fromCol << " to " << (fromRow - 1) << ":" << (fromCol - 1 );
					white.push(sstream.str());
					return true;
				}
			}
		}
		return false;
	}
	
	bool cheatMenu() // What is a game if there are no cheats :)
	{
		cls();
		int choice = 0;
		do
		{
			cout << "Welcome to the cheat menu!\nPlease select the option you would like to use." << endl;
			cout << "1. Delete all white pieces." << endl;
			cout << "2. Delete all black pieces." << endl;
			cout << "3. Make white all kings. " << endl;
			cout << "4. Make black all kings. " << endl;
			cout << "5. Delete piece at location. " << endl;
			cout << "6. Nevermind -_-" << endl;
			cout << "Your choice: ";
			cin >> choice;
		}while(choice <= 0 && choice > 5 );
		
		switch(choice)
		{
			case 1:
			{
				for(int row = 0 ; row < 8 ; row++)
				{
					for(int col = 0 ; col < 8 ; col++)
					{
						if(b.getPieceAt(row, col)->getColor() == whiteCircle || b.getPieceAt(row, col)->getColor() == whiteKing)
						{
							delete b.getPieceAt(row, col);
							b.board[row][col] = new BlackSquare;
						}
					}
					
				}
				return true;
			}
			case 2:
			{
				for(int row = 0 ; row < 8 ; row++)
				{
					for(int col = 0 ; col < 8 ; col++)
					{
						if(b.getPieceAt(row, col)->getColor() == blackCircle || b.getPieceAt(row, col)->getColor() == blackKing)
						{
							delete b.getPieceAt(row, col);
							b.board[row][col] = new BlackSquare;
						}
					}
					
				}
				return true;
			}
			case 3:
			{
				for(int row = 0 ; row < 8 ; row++)
				{
					for(int col = 0 ; col < 8 ; col++)
					{
						if(b.getPieceAt(row, col)->getColor() == whiteCircle)
						{
							delete b.getPieceAt(row, col);
							b.board[row][col] = new WhitePiece(whiteKing, true);
						}
					}
					
				}
				return true;
			}
			case 4:
			{
				for(int row = 0 ; row < 8 ; row++)
				{
					for(int col = 0 ; col < 8 ; col++)
					{
						if(b.getPieceAt(row, col)->getColor() == blackCircle)
						{
							delete b.getPieceAt(row, col);
							b.board[row][col] = new BlackPiece(blackKing, true);
						}
					}
					
				}
				return true;
			}
			case 5:
			{
			again:
				int row = 0, col = 0;
				char agn = '\0';
				b.printBoard();
				cout << "Row: ";
				cin >> row;
				cout << "Column: ";
				cin >> col;
				delete b.getPieceAt(row, col);
				b.board[row][col] = new BlackSquare;
				cout << "Again? (y/n): ";
				cin >> agn;
				if(agn == 'y' || agn == 'Y')
					goto again;
				break;
			}
			case 6:
			{
				cout << "You're still a cheater..."<<endl;
				return true;
			}
			default:
			{
				cout << "If you can't follow directions just don't even try to cheat... cheater..." << endl;
			}
		}
		return true;
	}
	
	
	bool moveBlackForward(int fromRow, int fromCol, bool isLeft)
	{
		int toRow = fromRow + 1, jumpRow = toRow + 1;
		ostringstream sstream;
		
		if(fromRow == 7)
			return false;
		
		if(b.getPieceAt(fromRow, fromCol)->getColor() == blackCircle || b.getPieceAt(fromRow, fromCol)->getColor() == blackKing) // If the player selected a black piece
		{
			if(isLeft && fromCol != 0) //If they selected to go forward and to the left
			{
				int toCol = fromCol - 1, jumpCol = toCol - 1;
				
				if(b.getPieceAt(toRow, toCol)->getColor() == whiteCircle || b.getPieceAt(toRow, toCol)->getColor() == whiteKing) //JUMPING! If the place they are moving to is a white piece
				{
					if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackSquare) // JUMPING! If the place they are jumping to is a black square
					{
						if(b.getPieceAt(fromRow, fromCol)->getIsKing() == true)
						{
							delete b.getPieceAt(jumpRow, jumpCol);
							b.board[jumpRow][jumpCol] = new BlackPiece(blackKing,true);
						}
						else
						{
							delete b.getPieceAt(jumpRow, jumpCol);
							b.board[jumpRow][jumpCol] = new BlackPiece;
						}
						delete b.getPieceAt(fromRow, fromCol);
						b.board[fromRow][fromCol] = new BlackSquare;
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackSquare;
						sstream << fromRow << ":" << fromCol << " to " << jumpRow << ":" << jumpCol;
						black.push(sstream.str());
						
						if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackKing)
							kingMultiJump(jumpRow, jumpCol, blackKing);
						else
							multiJump(jumpRow,jumpCol,blackCircle);
						
						if(jumpRow == 7 && b.getPieceAt(jumpRow, jumpCol)->getIsKing() != true)
						{
							cls();
							string cont;
							cout << jumpRow << ":" << jumpCol << " You're piece was kinged by this jump!!\nPress any key and enter to continue: ";
							cin >> cont;
							b.getPieceAt(jumpRow, jumpCol)->setKing(true);
						}
						return true;
					}
				}
				else if(b.getPieceAt(toRow, toCol)->getColor() == blackSquare) //If moving to a black square
				{
					if(b.getPieceAt(fromRow, fromCol)->getIsKing() == true)
					{
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackPiece(blackKing,true);
					}
					else
					{
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackPiece;
					}
					delete b.getPieceAt(fromRow, fromCol);
					b.board[fromRow][fromCol] = new BlackSquare;
					sstream << fromRow << ":" << fromCol << " to " << toRow << ":" << toCol;
					black.push(sstream.str());
					if(toRow == 7 && b.getPieceAt(toRow, toCol)->getIsKing() != true)
					{
						cls();
						string cont;
						cout << toRow << ":" << toCol << " You're piece was kinged by this move!!\nPress any key and enter to continue: ";
						cin >> cont;
						b.getPieceAt(toRow, toCol)->setKing(true);
					}
					return true;
				}
			}
			else if(!isLeft && fromCol != 7) //If they select to go forward and to the right
			{
				int toCol = fromCol + 1, jumpCol = toCol + 1;
				
				if(b.getPieceAt(toRow, toCol)->getColor() == whiteCircle || b.getPieceAt(toRow, toCol)->getColor() == whiteKing) //JUMPING!
				{
					if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackSquare) //Jumping!
					{
						if(b.getPieceAt(fromRow, fromCol)->getIsKing() == true)
						{
							delete b.getPieceAt(jumpRow, jumpCol);
							b.board[jumpRow][jumpCol] = new BlackPiece(blackKing,true);
						}
						else
						{
							delete b.getPieceAt(jumpRow, jumpCol);
							b.board[jumpRow][jumpCol] = new BlackPiece;
						}
						delete b.getPieceAt(fromRow, fromCol);
						b.board[fromRow][fromCol] = new BlackSquare;
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackSquare;
						
						sstream << fromRow << ":" << fromCol << " to " << jumpRow << ":" << jumpCol;
						black.push(sstream.str());
						
						if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackKing)
							kingMultiJump(jumpRow, jumpCol, blackKing);
						else
							multiJump(jumpRow,jumpCol,blackCircle);
						
						if(jumpRow == 7 && b.getPieceAt(jumpRow, jumpCol)->getIsKing() != true)
						{
							cls();
							string cont;
							cout << jumpRow << ":" << jumpCol << " You're piece was kinged by this jump!!\nPress any key and enter to continue: ";
							cin >> cont;
							b.getPieceAt(jumpRow, jumpCol)->setKing(true);
						}
						return true;
					}
				}
				if(b.getPieceAt(toRow, toCol)->getColor() == blackSquare) //If moving to a black square
				{
					if(b.getPieceAt(fromRow, fromCol)->getIsKing() == true)
					{
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackPiece(blackKing,true);
					}
					else
					{
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackPiece;
					}
					delete b.getPieceAt(fromRow, fromCol);
					b.board[fromRow][fromCol] = new BlackSquare;
					
					sstream << fromRow << ":" << fromCol << " to " << (fromRow - 1) << ":" << (fromCol - 1 );
					black.push(sstream.str());
					if(toRow == 7 && b.getPieceAt(toRow, toCol)->getIsKing() != true)
					{
						cls();
						string cont;
						cout << toRow << ":" << toCol << " You're piece was kinged by this move!!\nPress any key and enter to continue: ";
						cin >> cont;
						b.getPieceAt(toRow, toCol)->setKing(true);
					}
					return true;
				}
			}
		}
		return false;
	}
	
	bool moveBlackBackward(int fromRow, int fromCol, bool isLeft)
	{
		int toRow = fromRow -1, jumpRow = toRow - 1;
		ostringstream sstream;
		
		if(b.getPieceAt(fromRow, fromCol)->getColor() == blackKing) // If the player selected a white piece
		{
			if(isLeft && fromCol != 0) //If they selected to go forward and to the left
			{
				int toCol = fromCol - 1, jumpCol = toCol - 1;
				
				if((b.getPieceAt(toRow, toCol)->getColor() == whiteCircle || b.getPieceAt(toRow, toCol)->getColor() == whiteKing)) //JUMPING! If the place they are moving to is a black piece
				{
					if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackSquare) // JUMPING! If the place they are jumping to is a black square
					{
						delete b.getPieceAt(fromRow, fromCol);
						b.board[fromRow][fromCol] = new BlackSquare;
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackSquare;
						delete b.getPieceAt(jumpRow, jumpCol);
						b.board[jumpRow][jumpCol] = new BlackPiece(blackKing,true);
						sstream << fromRow << ":" << fromCol << " to " << ((fromRow - 1) - 1) << ":" << ((fromCol - 1 ) - 1);
						black.push(sstream.str());
						kingMultiJump(jumpRow, jumpCol, blackKing);
						return true;
					}
				}
				if(b.getPieceAt(toRow, toCol)->getColor() == blackSquare) //If moving to a black square
				{
					delete b.getPieceAt(fromRow, fromCol);
					b.board[fromRow][fromCol] = new BlackSquare;
					delete b.getPieceAt(toRow, toCol);
					b.board[toRow][toCol] = new BlackPiece(blackKing,true);
					sstream << fromRow << ":" << fromCol << " to " << (fromRow - 1) << ":" << (fromCol - 1 );
					black.push(sstream.str());
					return true;
				}
			}
			else if(!isLeft && fromCol != 7) //If they select to go forward and to the right
			{
				int toCol = fromCol + 1, jumpCol = toCol + 1;
				
				if((b.getPieceAt(toRow, toCol)->getColor() == whiteCircle || b.getPieceAt(toRow, toCol)->getColor() == whiteKing)) //JUMPING!
				{
					if(b.getPieceAt(jumpRow, jumpCol)->getColor() == blackSquare) //Jumping!
					{
						delete b.getPieceAt(fromRow, fromCol);
						b.board[fromRow][fromCol] = new BlackSquare;
						delete b.getPieceAt(toRow, toCol);
						b.board[toRow][toCol] = new BlackSquare;
						delete b.getPieceAt(jumpRow, jumpCol);
						b.board[jumpRow][jumpCol] = new BlackPiece(blackKing,true);
						sstream << fromRow << ":" << fromCol << " to " << jumpRow << ":" << jumpCol;
						black.push(sstream.str());
						kingMultiJump(jumpRow, jumpCol, blackKing);
						return true;
					}
				}
				else if(b.getPieceAt(toRow, toCol)->getColor() == blackSquare) //If moving to a black square
				{
					delete b.getPieceAt(fromRow, fromCol);
					b.board[fromRow][fromCol] = new BlackSquare;
					delete b.getPieceAt(toRow, toCol);
					b.board[toRow][toCol] = new BlackPiece(blackKing,true);
					sstream << fromRow << ":" << fromCol << " to " << toRow << ":" << toCol;
					black.push(sstream.str());
					
					return true;
				}
			}
		}
		return false;
	}
	
	void printBoard()
	{
		b.printBoard();
	}
	bool checkIfFinished(bool &whiteIsWinner) // This function checks to see if there are no more of a players pieces on the board.
	{
		/*
		 I'm returning a boolean value as well accepting a boolean value.
		 What I am returning determines if the game is over.
		 What I'm getting passed by referance is which player won.
		 */
		int blackCount = 0, whiteCount = 0;
		for(int row = 0 ; row < 8 ; row++)
		{
			for(int col = 0 ; col < 8 ; col++)
			{
				if(b.getPieceAt(row, col)->getColor() == blackCircle || b.getPieceAt(row, col)->getColor() == blackKing)
					blackCount++;
				
				else if(b.getPieceAt(row, col)->getColor() == whiteCircle || b.getPieceAt(row, col)->getColor() == whiteKing)
					whiteCount++;
			}
		}
		
		if(blackCount >= 1 && whiteCount == 0)
		{
			whiteIsWinner = false;
			return true;
		}
		else if(whiteCount >= 1 && blackCount == 0)
		{
			whiteIsWinner = true;
			return true;
		}
		else
			return false;
	}
	
	bool checkIfKing(int x , int y) // Simple check if the coords passed are a king piece.
	{
		return b.getPieceAt(x, y)->getIsKing();
	}
	
	void multiJump(int row, int col, string color)
	{
		/*
		 This function is essentially the same as either of the move forward functions.
		 The main difference is that it is set up to accept either white or black pieces.
		 Another difference is the use of recursion to check for another multijump.
		 */
		string opColor, opKing, colorKing;
		int rowLimit, leftColLimit = 1, rightColLimit = 6, nextRow, jumpRow, leftNextCol, leftJumpCol, rightJumpCol, rightNextCol;
		if(color == whiteCircle)
		{
			opColor = blackCircle;
			opKing = blackKing;
			colorKing = whiteKing;
			rowLimit = 1;
			if(row <= rowLimit)
				return;
		}
		else
		{
			opColor = whiteCircle;
			opKing = whiteKing;
			colorKing = blackKing;
			rowLimit = 6;
			if(row >= rowLimit)
				return;
		}
		
		
		ostringstream sstream;
		
		if(col > leftColLimit) // Jumping to the left
		{
			
			if(color == whiteCircle)
			{
				nextRow = row - 1;
				jumpRow = nextRow - 1;
				leftNextCol = col - 1;
				leftJumpCol = leftNextCol - 1;
			}
			else
			{
				nextRow = row + 1;
				jumpRow = nextRow + 1;
				leftNextCol = col - 1;
				leftJumpCol = leftNextCol - 1;
			}
			
			if(b.getPieceAt(nextRow, leftNextCol)->getColor() == opColor || b.getPieceAt(nextRow, leftNextCol)->getColor() == opKing)
			{
				
				if(b.getPieceAt(jumpRow, leftJumpCol)->getColor() == blackSquare)
				{
					
					delete b.getPieceAt(row, col); // Deleting the source of the movement
					b.board[row][col] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(nextRow, leftNextCol); // Deleting the first diaginal piece which would be the opposing players piece
					b.board[nextRow][leftNextCol] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(jumpRow, leftJumpCol);
					if(color == whiteCircle)
					{
						if(jumpRow != 0)
							b.board[jumpRow][leftJumpCol] = new WhitePiece;
						else
							b.board[jumpRow][leftJumpCol] = new WhitePiece(whiteKing, true);
					}
					else
					{
						if(jumpRow != 7)
							b.board[jumpRow][leftJumpCol] = new BlackPiece;
						else
							b.board[jumpRow][leftJumpCol] = new BlackPiece(blackKing, true);
					}
					sstream << row << ":" << col << " to " << jumpRow << ":" << leftJumpCol;
					if(color == whiteCircle)
						white.push(sstream.str()); // Pushing the string streams string version to the stack.
					else
						black.push(sstream.str());
					if(color == whiteCircle)
					{
						row -= 2;
						col -= 2;
					}
					else
					{
						row += 2;
						col -= 2;
					}
					if((color == whiteCircle && row ==  0) || (color == blackCircle && row == 7))
						kingMultiJump(row, col, color);
					else if((color == whiteCircle && row !=  0) || (color == blackCircle && row != 7))
						multiJump(row, col, color);
				}
			}
		}
		
		if(col < rightColLimit) //Checking if there is a jump to the right
		{
			if(color == whiteCircle)
			{
				nextRow = row - 1;
				jumpRow = nextRow-  1;
				rightNextCol = col + 1;
				rightJumpCol = rightNextCol + 1;
			}
			else
			{
				nextRow = row + 1;
				jumpRow = nextRow + 1;
				rightNextCol = col + 1;
				rightJumpCol = rightNextCol + 1;
			}
			
			if(b.getPieceAt(nextRow, rightNextCol)->getColor() == opColor || b.getPieceAt(nextRow, rightNextCol)->getColor() == opKing)
			{
				if(b.getPieceAt(jumpRow, rightJumpCol)->getColor() == blackSquare)
				{
					
					delete b.getPieceAt(row, col); // Deleting the source of the movement
					b.board[row][col] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(nextRow, rightNextCol); // Deleting the first diaginal piece which would be the opposing players piece
					b.board[nextRow][rightNextCol] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(jumpRow, rightJumpCol);
					if(color == whiteCircle)
					{
						if(jumpRow != 0)
							b.board[jumpRow][rightJumpCol] = new WhitePiece;
						else
							b.board[jumpRow][rightJumpCol] = new WhitePiece(whiteKing, true);
					}
					else
					{
						if(jumpRow != 7)
							b.board[jumpRow][rightJumpCol] = new BlackPiece;
						else
							b.board[jumpRow][rightJumpCol] = new BlackPiece(blackKing, true);
					}
					sstream << row << ":" << col << " to " << jumpRow << ":" << rightJumpCol;
					if(color == whiteCircle)
						white.push(sstream.str()); // Pushing the string streams string version to the stack.
					else
						black.push(sstream.str());
					if(color == whiteCircle)
					{
						row -= 2;
						col -= 2;
					}
					else
					{
						row += 2;
						col -= 2;
						
						if((color == whiteCircle && row ==  0) || (color == blackCircle && row == 7))
							kingMultiJump(row, col, color);
						else if((color == whiteCircle && row !=  0) || (color == blackCircle && row != 7))
							multiJump(row, col, color);
					}
				}
			}
		}
	}
	void kingMultiJump(int row, int col, string color)
	{
		/*
		 This function is essentially the forward and backward functions all combined.
		 The main difference is that it is set up to accept either white or black pieces.
		 Another difference is the use of recursion to check for another multijump.
		 Since Kings can move forward and backward I had to check all 4 of the directions
		 it could move.
		 */
		
		string opColor, opKing;
		int lowerRowLimit = 1, upperRowLimit = 6, leftColLimit = 1, rightColLimit = 6, nextLowerRow, nextUpperRow, jumpLowerRow, jumpUpperRow, leftNextCol, leftJumpCol, rightJumpCol, rightNextCol;
		if(color == whiteKing)
		{
			opColor = blackCircle;
			opKing = blackKing;
		}
		else if(color == blackKing)
		{
			opColor = whiteCircle;
			opKing = whiteKing;
		}
		
		ostringstream sstream;
		
		if(col > leftColLimit) // Jumping to the lower left
		{
			if(row <= lowerRowLimit)
				return;
			
			
			nextLowerRow = row - 1;
			jumpLowerRow = nextLowerRow - 1;
			leftNextCol = col - 1;
			leftJumpCol = leftNextCol - 1;
			
			if(b.getPieceAt(nextLowerRow, leftNextCol)->getColor() == opColor || b.getPieceAt(nextLowerRow, leftNextCol)->getColor() == opKing)
			{
				
				if(b.getPieceAt(jumpLowerRow, leftJumpCol)->getColor() == blackSquare)
				{
					
					delete b.getPieceAt(row, col); // Deleting the source of the movement
					b.board[row][col] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(nextLowerRow, leftNextCol); // Deleting the first diaginal piece which would be the opposing players piece
					b.board[nextLowerRow][leftNextCol] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(jumpLowerRow, leftJumpCol);
					if(color == whiteKing)
					{
						
						b.board[jumpLowerRow][leftJumpCol] = new WhitePiece(whiteKing, true);
					}
					else if(color == blackKing)
					{
						if(jumpLowerRow != 7)
							b.board[jumpLowerRow][leftJumpCol] = new BlackPiece;
						else
							b.board[jumpLowerRow][leftJumpCol] = new BlackPiece(blackKing, true);
					}
					sstream << row << ":" << col << " to " << jumpLowerRow << ":" << leftJumpCol;
					if(color == whiteCircle)
						white.push(sstream.str()); // Pushing the string streams string version to the stack.
					else
						black.push(sstream.str());
					
					row -= 2;
					col -= 2;
					
					kingMultiJump(row, col, color);
					
					
				}
				
			}
		}
		
		if(col < rightColLimit) //Checking if there is a jump to the lower right
		{
			if(row <= lowerRowLimit)
				return;
			
			
			nextLowerRow = row - 1;
			jumpLowerRow = nextLowerRow-  1;
			rightNextCol = col + 1;
			rightJumpCol = rightNextCol + 1;
			
			if(b.getPieceAt(nextLowerRow, rightNextCol)->getColor() == opColor || b.getPieceAt(nextLowerRow, rightNextCol)->getColor() == opKing)
			{
				
				if(b.getPieceAt(jumpLowerRow, rightJumpCol)->getColor() == blackSquare)
				{
					
					delete b.getPieceAt(row, col); // Deleting the source of the movement
					b.board[row][col] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(nextLowerRow, rightNextCol); // Deleting the first diaginal piece which would be the opposing players piece
					b.board[nextLowerRow][rightNextCol] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(jumpLowerRow, rightJumpCol);
					if(color == whiteKing)
					{
						b.board[jumpLowerRow][rightJumpCol] = new WhitePiece(whiteKing, true);
					}
					else if(color == blackKing)
					{
						b.board[jumpLowerRow][rightJumpCol] = new BlackPiece(blackKing, true);
					}
					sstream << row << ":" << col << " to " << jumpLowerRow << ":" << rightJumpCol;
					if(color == whiteKing)
						white.push(sstream.str()); // Pushing the string streams string version to the stack.
					else if(color == blackKing)
						black.push(sstream.str());
					
					row -= 2;
					col += 2;
					
					kingMultiJump(row, col, color);
					
					
				}
				
			}
		}
		if(col > leftColLimit) // Jumping to the upper left
		{
			if(row >= upperRowLimit)
				return;
			
			
			nextUpperRow = row + 1;
			jumpUpperRow = nextUpperRow + 1;
			leftNextCol = col - 1;
			leftJumpCol = leftNextCol - 1;
			
			if(b.getPieceAt(nextUpperRow, leftNextCol)->getColor() == opColor || b.getPieceAt(nextUpperRow, leftNextCol)->getColor() == opKing)
			{
				
				if(b.getPieceAt(jumpUpperRow, leftJumpCol)->getColor() == blackSquare)
				{
					
					delete b.getPieceAt(row, col); // Deleting the source of the movement
					b.board[row][col] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(nextUpperRow, leftNextCol); // Deleting the first diaginal piece which would be the opposing players piece
					b.board[nextUpperRow][leftNextCol] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(jumpUpperRow, leftJumpCol);
					if(color == whiteKing)
					{
						b.board[jumpUpperRow][leftJumpCol] = new WhitePiece(whiteKing, true);
					}
					else if(color == blackKing)
					{
						b.board[jumpUpperRow][leftJumpCol] = new BlackPiece(blackKing, true);
					}
					sstream << row << ":" << col << " to " << jumpUpperRow << ":" << leftJumpCol;
					if(color == whiteKing)
						white.push(sstream.str()); // Pushing the string streams string version to the stack.
					else if(color == blackKing)
						black.push(sstream.str());
					
					row += 2;
					col -= 2;
					
					kingMultiJump(row, col, color);
					
				}
			}
		}
		if(col < rightColLimit) //Checking if there is a jump to the upper right
		{
			if(row >= upperRowLimit)
				return;
			
			
			nextUpperRow = row + 1;
			jumpUpperRow = nextUpperRow +  1;
			rightNextCol = col + 1;
			rightJumpCol = rightNextCol + 1;
			
			if(b.getPieceAt(nextUpperRow, rightNextCol)->getColor() == opColor || b.getPieceAt(nextUpperRow, rightNextCol)->getColor() == opKing)
			{
				
				if(b.getPieceAt(jumpUpperRow, rightJumpCol)->getColor() == blackSquare)
				{
					
					delete b.getPieceAt(row, col); // Deleting the source of the movement
					b.board[row][col] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(nextUpperRow, rightNextCol); // Deleting the first diaginal piece which would be the opposing players piece
					b.board[nextUpperRow][rightNextCol] = new BlackSquare; // Creating a new black square to replace the old piece
					delete b.getPieceAt(jumpUpperRow, rightJumpCol);
					if(color == whiteKing)
					{
						b.board[jumpUpperRow][rightJumpCol] = new WhitePiece(whiteKing, true);
					}
					else if(color == blackKing)
					{
						b.board[jumpUpperRow][rightJumpCol] = new BlackPiece(blackKing, true);
					}
					sstream << row << ":" << col << " to " << jumpUpperRow << ":" << rightJumpCol;
					if(color == whiteKing)
						white.push(sstream.str()); // Pushing the string streams string version to the stack.
					else if(color == blackKing)
						black.push(sstream.str());
					
					row += 2;
					col += 2;
					
					kingMultiJump(row, col, color);
				}
			}
		}
	}
};


int main()
{
	Checkers game;
	bool isGood = false, whiteIsWinner, whiteCheated = false, blackCheated = false;
	
	do
	{
		int whiteRow = 0, whiteCol = 0, blackRow = 0, blackCol = 0;
		char wLR = '\0', bLR = '\0', wFB = 'F', bFB = 'F';
		bool whiteLR = false, blackLR = false;
		
	whiteCheat: // After white player cheats they'll be given a turn to move
		do
		{
			game.printBoard(); // Printing to the board before each players turn so they have an updated board to look at
			if(whiteCheated) // If the white player goes to the cheat menu this will be displayed before they put in their move
				cout << "cheater... or debugger..." << endl;
			do {
				cout << "X: Select a piece to move!\nRow: ";
				cin >> whiteRow;
				while(cin.fail()) // Input validation to ensure the user doesn't crash the program but inputing something that isn't expected.
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					game.printBoard();
					cout<<"X: Select a piece to move!\nRow: ";
					cin>>whiteRow;
				}
				if(whiteRow == 2131995) // To access the cheat menu the user enters my birthday into the row column
				{
					whiteCheated = game.cheatMenu();
					goto whiteCheat;
				}
			}while(whiteRow < 0 || whiteRow >= 8); // Input validation so the user into able to continue with an invalid value
			do {
				cout << "Column: ";
				cin >> whiteCol;
				while(cin.fail()) // Input validation for the column input
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					game.printBoard();
					cout<<"X: Select a piece to move!\nRow: "<< whiteRow << endl;
					cout<<"Column: ";
					cin>>whiteCol;
				}
			}while(whiteCol < 0 || whiteCol >= 8); // Ensuring only able to continue with a valid value
			
			if(game.checkIfKing(whiteRow, whiteCol)) // If the selected piece is a king than it will also ask them if they want to move forward or back
			{
				do
				{
					cout << "Move forward (F) or backward (B): ";
					cin >> wFB;
				}while(wFB != 'F' && wFB != 'f' && wFB != 'B' && wFB != 'b');
				
				do{
					cout << "Move left (L) or right (R): ";
					cin >> wLR;
				}while(wLR != 'L' && wLR != 'R' && wLR != 'l' && wLR != 'r');
				
				if(wLR == 'l' || wLR == 'L')
					whiteLR = true;
				else
					whiteLR = false;
				
				if(wFB == 'F' || wFB == 'f')
					isGood = game.moveWhiteForward(whiteRow, whiteCol, whiteLR);
				else
					isGood = game.moveWhiteBackward(whiteRow, whiteCol, whiteLR);
				
				if(!isGood)
				{
					cout << "Press ENTER to continue...";
					cin.clear();
					cin.sync();
					cin.get();
					cls();
				}
			}
			else // If they aren't a king piece than it just asks if they want to move to the left or right.
			{
				do{
					cout << "Move left (L) or right (R): ";
					cin >> wLR;
				}while(wLR != 'L' && wLR != 'R' && wLR != 'l' && wLR != 'r');
				
				if(wLR == 'l' || wLR == 'L')
					whiteLR = true;
				else
					whiteLR = false;
				
				isGood = game.moveWhiteForward(whiteRow, whiteCol, whiteLR);
				
				if(!isGood)
				{
					cout << "Press ENTER to continue...";
					cin.clear();
					cin.sync();
					cin.get();
					cls();
				}
			}
			
		}while(!isGood);
		
		/*
		 If the function determines there is no more of either given type
		 of piece than it will return true. The arguement that is passed
		 determines who is the winner. If it is true than white is the
		 winner. If it is false, black is the winner.
		 */
		
		if(game.checkIfFinished(whiteIsWinner))
			break;
		
		/*
		 This next section is essentially the same as the white players
		 input above with the exception of it being for the black player
		 */
	blackCheat:
		do
		{
			game.printBoard();
			if(blackCheated)
				cout << "cheater... or debugger..." << endl;
			do {
				cout << "O: Move a piece!\nRow: ";
				cin >> blackRow;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					game.printBoard();
					cout << "O: Select a piece to move!\nRow: ";
					cin>>blackRow;
				}
				if(blackRow == 2131995)
				{
					blackCheated = game.cheatMenu();
					goto blackCheat;
				}
			}while(blackRow < 0 || blackRow >= 8);
			do {
				cout << "Column: ";
				cin >> blackCol;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					game.printBoard();
					cout << "O: Select a piece to move!\nRow: " << blackRow << endl;
					cout << "Column: ";
					cin>>blackCol;
				}
			}while(blackCol < 0 || blackCol >= 8);
			
			if(game.checkIfKing(blackRow, blackCol))
			{
				do
				{
					cout << "Move forward (F) or backward (B): ";
					cin >> bFB;
				}while(bFB != 'F' && bFB != 'f' && bFB != 'B' && bFB != 'b');
				
				do{
					cout << "Move left (L) or right (R): ";
					cin >> bLR;
				}while(bLR != 'L' && bLR != 'R' && bLR != 'l' && bLR != 'r');
				
				if(bLR == 'l' || bLR == 'L')
					blackLR = true;
				else
					blackLR = false;
				
				if(bFB == 'F' || bFB == 'f')
					isGood = game.moveBlackForward(blackRow, blackCol, blackLR);
				else
					isGood = game.moveBlackBackward(blackRow, blackCol, blackLR);
				
				if(!isGood)
				{
					cout << "Press ENTER to continue...";
					cin.clear();
					cin.sync();
					cin.get();
					cls();
				}
			}
			else
			{
				do{
					cout << "Move left (L) or right (R): ";
					cin >> bLR;
				}while(bLR != 'L' && bLR != 'R' && bLR != 'l' && bLR != 'r');
				
				if(bLR == 'l' || bLR == 'L')
					blackLR = true;
				else
					blackLR = false;
				
				isGood = game.moveBlackForward(blackRow, blackCol, blackLR);
				
				if(!isGood)
				{
					cout << "Press ENTER to continue...";
					cin.clear();
					cin.sync();
					cin.get();
					cls();
				}
			}
			
		}while(!isGood);
		if(game.checkIfFinished(whiteIsWinner))
			break;
	}while(1);
	
	if(whiteIsWinner) // This is the final display depending on who won and lost.
	{
		cls();
		cout << "Congrats White (x) Player! You have won!\n\nThese are all of the moves you made!" << endl;
		game.endGameWhite(); // This function calls the function that calls the function that clears and displays the winners moves.
	}
	else
	{
		cls();
		cout << "Congrats Black (o) Player! You have won!\n\nThese are all of the moves you made!" << endl;
		game.endGameBlack();
	}
	return 0;
}

