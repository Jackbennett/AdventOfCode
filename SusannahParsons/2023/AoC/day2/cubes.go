package cubes

import (
	"fmt"
	"strconv"
	"strings"
)

type Games struct {
	SumPossibleIds int
}

func (games *Games) ParseGame(dataline string, maxRed int, maxBlue int, maxGreen int) {
	maxColours := make(map[string]int)
	maxColours["red"] = maxRed
	maxColours["blue"] = maxBlue
	maxColours["green"] = maxGreen
	s := strings.Split(dataline, ":")
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

}
