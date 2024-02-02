# class descriptions

## Game

- main class
- has a Board object (maybe multiple Boards?)
- handles gui stuff
- keeps track of the score (optional)

## Board

- handles internal logic
- stores the game state
- has a tree of Move objects
- timers (optional)

## Move

- stores move data
- has a vector of forward pointers, and a back pointer


# details

## Game

- sdl2 stuff

- new game
	- creates an empty Board

- terminate game
	- send the Board into oblivion

- load game
	- creates a Board with the provided Move tree


## Board

- go to move
	- sets the board to the position after the given move

- insert move
	- appends the Move tree with the given Move

- delete line
	- deletes a Move subtree

- extract game
	- extracts the Move tree into a file

## Move
