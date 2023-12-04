package cubes

import (
	"fmt"
	"strconv"
	"strings"
)

type Games struct {
	SumPossibleIds int
	SumPower       int
}

type Game struct {
	maxActualColours map[string]int
}

func (games *Games) ParseGame(dataline string, maxRed int, maxBlue int, maxGreen int) {
	maxColours := make(map[string]int)
	maxColours["red"] = maxRed
	maxColours["blue"] = maxBlue
	maxColours["green"] = maxGreen
	s := strings.Split(dataline, ":")
	var newGame Game
	newGame.maxActualColours = make(map[string]int)
	newGame.maxActualColours["red"] = 0
	newGame.maxActualColours["green"] = 0
	newGame.maxActualColours["blue"] = 0
	gameTitle := s[0]
	gameContent := s[1]
	s = strings.Fields(gameTitle)
	gameid, err := strconv.Atoi(s[1])
	if err != nil {
		fmt.Println("Can't convert this to an int! " + s[1])
	} else {
		possible := true
		handfuls := strings.Split(gameContent, ";")
		for _, handful := range handfuls {
			cubeDatas := strings.Split(handful, ",")
			for _, cubeData := range cubeDatas {
				colourNumberSplit := strings.Fields(cubeData)
				cubeNumber, err := strconv.Atoi(colourNumberSplit[0])
				if err != nil {
					fmt.Println("Can't convert this to an int! " + colourNumberSplit[0])
				} else {
					if newGame.maxActualColours[colourNumberSplit[1]] < cubeNumber {
						newGame.maxActualColours[colourNumberSplit[1]] = cubeNumber
					}
					if maxColours[colourNumberSplit[1]] < cubeNumber {
						possible = false
					}
				}
			}
		}
		if possible {
			games.SumPossibleIds += gameid
		}
	}
	power := newGame.maxActualColours["red"] * newGame.maxActualColours["blue"] * newGame.maxActualColours["green"]
	games.SumPower += power
}
