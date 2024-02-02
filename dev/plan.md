# class descriptions

Server
- ?

Game  
- Move

Client  
- Game  
- ClientSideConnection ? (class olmak zorunda değil)

## Server

- ?

## Client

- main class
- has a Game object
- handles gui stuff
- keeps track of the score (optional)

## Game

- Game Mode
- handles internal logic
- Move head ptrs
- timers (optional)

## Move

- stores move data
- has a vector of forward pointers, and a back pointer
- Board after move

# details

- We are looking to have a `playing mode` and an `analysis mode` with seemless integration between them after the game is over.

## Client

- sdl2 stuff
	- needs a Board to display, pulled from the Game object

- new game
	- creates a new Game with an empty Move tree

- terminate game
	- terminates the Game

- load game
	- creates a Game object with a given Move object (or read from a file ?)

- go to analysis


## Game

- go to move
	- sets the board to the position after the given move
	- note that this needs to get input from the gui. thus, a (very smart) function from the Client class needs to call this.

- insert move
	- appends the Move tree with the given Move

- delete line
	- deletes a Move subtree

- extract game
	- extracts the Move tree into a file

## Move

- Board: array<char>
- forward_ptrs: array<Move*>
- back_ptr: Move*

## TODO
- Learn SDL2
- Learn socket programming with C++
- Import std-proj project structure
- Find a format for serializing games, i.e. saving games and vice versa, i.e. loading games.
- Development Order: Move -> Game -> Client, Server
