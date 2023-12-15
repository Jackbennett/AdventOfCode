package obs

import (
	"AoC/helper"
	"fmt"
	"math"
	"slices"
)

type Observations struct {
	yMax             int
	xMax             int
	galaxies         []*helper.Space
	sumShortestPaths int64
}

func (obs *Observations) ParseRow(line string, yIndex int) {
	obs.yMax = yIndex
	for xIndex, item := range line {
		var newCoord helper.Coordinate
		newCoord.X = xIndex
		newCoord.Y = yIndex
		if xIndex > obs.xMax {
			obs.xMax = xIndex
		}
		if item == '#' {
			var newSpace helper.Space
			newSpace.Coord = newCoord
			newSpace.IsGalaxy = true
			obs.galaxies = append(obs.galaxies, &newSpace)
		}
	}
}

func (obs *Observations) Expand() {
	//Find columns to expand
	var colsToExpand []int
	slices.SortFunc(obs.galaxies, helper.SortSpaceByX)
	//Galaxies are now in order of x
	currentX := 0
	for _, galaxy := range obs.galaxies {
		for galaxy.Coord.X > currentX {
			colsToExpand = append(colsToExpand, currentX)
			currentX++
		}
		currentX = galaxy.Coord.X + 1
	}
	currentX = obs.galaxies[len(obs.galaxies)-1].Coord.X
	for currentX < obs.xMax {
		colsToExpand = append(colsToExpand, currentX)
		currentX++
	}

	//Find rows to expand
	var rowsToExpand []int
	slices.SortFunc(obs.galaxies, helper.SortSpaceByY)
	currentY := 0
	for _, galaxy := range obs.galaxies {
		for galaxy.Coord.Y > currentY {
			rowsToExpand = append(rowsToExpand, currentY)
			currentY++
		}
		currentY = galaxy.Coord.Y + 1
	}
	currentY = obs.galaxies[len(obs.galaxies)-1].Coord.Y
	for currentY < obs.yMax {
		rowsToExpand = append(rowsToExpand, currentY)
		currentY++
	}

	//Now insert the rows
	for rowInd := len(rowsToExpand) - 1; rowInd >= 0; rowInd-- {
		indexToAdd := rowsToExpand[rowInd] //Last ones first
		for galaxyIndex := range obs.galaxies {
			if obs.galaxies[galaxyIndex].Coord.Y > indexToAdd {
				// obs.galaxies[galaxyIndex].Coord.Y++ //Add one to row part 1
				obs.galaxies[galaxyIndex].Coord.Y = obs.galaxies[galaxyIndex].Coord.Y + 999999 //Add 1 million to row
			}
		}
	}

	slices.SortFunc(obs.galaxies, helper.SortSpaceByX)

	//Insert the columns
	for colInd := len(colsToExpand) - 1; colInd >= 0; colInd-- {
		indexToAdd := colsToExpand[colInd] //Last ones first
		for galaxyIndex := range obs.galaxies {
			if obs.galaxies[galaxyIndex].Coord.X > indexToAdd {
				// obs.galaxies[galaxyIndex].Coord.X++ //Add one to column part 1
				obs.galaxies[galaxyIndex].Coord.X = obs.galaxies[galaxyIndex].Coord.X + 999999 //Add 1 million to col
			}
		}
	}
}

func (obs *Observations) FindShortestPaths() {
	for firstIndex := range obs.galaxies {
		//Find the shortest path to all the remaining galaxies
		for secondIndex := firstIndex + 1; secondIndex < len(obs.galaxies); secondIndex++ {
			shortestPath := math.Abs(float64(obs.galaxies[firstIndex].Coord.X-obs.galaxies[secondIndex].Coord.X)) +
				math.Abs(float64(obs.galaxies[firstIndex].Coord.Y-obs.galaxies[secondIndex].Coord.Y))
			obs.sumShortestPaths += int64(shortestPath)
		}
	}
	fmt.Print(obs.sumShortestPaths, " sum shortest paths\n")
}
