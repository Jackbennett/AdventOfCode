package directions

import (
	"fmt"
	"strings"
)

type Directions struct {
	turnPattern []int
	directions  map[string][]string
}

func (directions *Directions) FollowDirections() {
	var zzzFound = false
	var initialIndex = 0
	var elementName = "AAA"
	var steps = 0
	for !zzzFound {
		leftOrRight := directions.turnPattern[initialIndex]
		elementName = directions.directions[elementName][leftOrRight]
		zzzFound = elementName == "ZZZ"
		steps++
		initialIndex++
		if initialIndex == len(directions.turnPattern) {
			initialIndex = 0
		}
	}
	fmt.Print("Finding zzz took steps ", steps, "\n")
}

func (directions *Directions) ParseDirections(line string) {
	if len(directions.turnPattern) == 0 {
		for _, char := range line {
			if char == 'L' {
				directions.turnPattern = append(directions.turnPattern, 0)
			} else {
				directions.turnPattern = append(directions.turnPattern, 1)
			}
		}
		return
	}
	if line == "" {
		return
	}

	dataArray := strings.Split(line, " = ")
	elementName := dataArray[0]
	directionsString := dataArray[1]
	directionsString = strings.Replace(directionsString, "(", "", 1)
	directionsString = strings.Replace(directionsString, ")", "", 1)
	elements := strings.Split(directionsString, ", ")
	if directions.directions == nil {
		directions.directions = make(map[string][]string)
	}
	directions.directions[elementName] = []string{elements[0], elements[1]}
}
