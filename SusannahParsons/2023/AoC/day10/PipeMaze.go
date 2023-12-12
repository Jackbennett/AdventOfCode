package pipeMaze

import (
	"AoC/helper"
	"fmt"
	"slices"
)

func getConnection(char rune) []helper.Direction {
	switch char {
	case '|':
		return []helper.Direction{helper.North, helper.South}
	case '-':
		return []helper.Direction{helper.East, helper.West}
	case 'L':
		return []helper.Direction{helper.North, helper.East}
	case 'J':
		return []helper.Direction{helper.North, helper.West}
	case '7':
		return []helper.Direction{helper.West, helper.South}
	case 'F':
		return []helper.Direction{helper.East, helper.South}
	}
	return []helper.Direction{}
}

type LoopEnd struct {
	from        helper.Direction
	currentTile *helper.Tile
}

func (loopend *LoopEnd) to() helper.Direction {
	if loopend.currentTile.Connected == nil || len(loopend.currentTile.Connected) == 0 {
		return *new(helper.Direction)
	}
	if loopend.currentTile.Connected[0] == loopend.from {
		return loopend.currentTile.Connected[1]
	} else {
		return loopend.currentTile.Connected[0]
	}
}

type PipeMaze struct {
	helper.FieldMap[helper.Tile]
	startTile *helper.Tile
}

func (maze *PipeMaze) ParseRow(line string, Yindex int) {
	for Xindex, char := range line {
		var newTile helper.Tile
		newTile.Symbol = char
		newTile.Connected = getConnection(char)
		var newCoord helper.Coordinate
		newCoord.X = Xindex
		newCoord.Y = Yindex
		newTile.Coord = newCoord
		maze.AddToMap(Xindex, Yindex, &newTile)
		if char == 'S' {
			maze.startTile = &newTile
		}
	}
}

func (maze *PipeMaze) FindMostDistantTile() {
	//Get the start tile. Start following the loop - get the first two loopends
	loopEnd1, loopEnd2 := maze.getFirstLoopEnds()
	for loopEnd1.currentTile.Coord != loopEnd2.currentTile.Coord {
		loopEnd1 = maze.getNextLoopEnd(loopEnd1)
		loopEnd2 = maze.getNextLoopEnd(loopEnd2)
	}
	fmt.Print(loopEnd1.currentTile.StepsFromS, " most steps from S\n")
}

func (maze *PipeMaze) getFirstLoopEnds() (LoopEnd, LoopEnd) {
	var loopEnd1 LoopEnd
	var loopEnd2 LoopEnd
	var Directions = []helper.Direction{
		helper.East,
		helper.North,
		helper.South,
		helper.West,
	}
	for _, direction := range Directions {
		adjacentTile, fetchSuccess := maze.GetAdjacentItem(maze.startTile.Coord, direction)
		if fetchSuccess {
			adjacentTile.StepsFromS = 1
			fromDirection := helper.OppositeDirectionMap[direction]
			if slices.Contains(adjacentTile.Connected, fromDirection) {
				//Connects to start tile
				if loopEnd1.currentTile == nil {
					loopEnd1.currentTile = adjacentTile
					loopEnd1.from = fromDirection
				} else {
					loopEnd2.currentTile = adjacentTile
					loopEnd2.from = fromDirection
					return loopEnd1, loopEnd2
				}

			}
		}
	}
	return loopEnd1, loopEnd2
}

func (maze *PipeMaze) getNextLoopEnd(previousLoopEnd LoopEnd) LoopEnd {
	var newLoop LoopEnd
	previousLoopTo := previousLoopEnd.to()
	adjacentTile, fetchSuccess := maze.GetAdjacentItem(previousLoopEnd.currentTile.Coord, previousLoopTo)
	if fetchSuccess {
		adjacentTile.StepsFromS = previousLoopEnd.currentTile.StepsFromS + 1
		newLoop.currentTile = adjacentTile
		newLoop.from = helper.OppositeDirectionMap[previousLoopTo]
	}
	return newLoop
}
