package directions

import (
	"fmt"
	"strings"
)

type Directions struct {
	startNodes  []string
	turnPattern []int
	directions  map[string][]string
}

type PathDims struct {
	stepsToZ  int
	stepsLoop int
}

// greatest common divisor (GCD) via Euclidean algorithm
func GCD(a, b int) int {
	for b != 0 {
		t := b
		b = a % b
		a = t
	}
	return a
}

// find Least Common Multiple (LCM) via GCD
func LCM(a, b int, integers ...int) int {
	result := a * b / GCD(a, b)

	for i := 0; i < len(integers); i++ {
		result = LCM(result, integers[i])
	}

	return result
}

func (directions *Directions) FollowDirections() {
	// var zzzFound = false
	// var initialIndex = 0
	// var elementName = "AAA"//Part 1 only
	// var steps = 0
	var mapProgress = make(map[string]PathDims)
	for _, elementName := range directions.startNodes {
		var initialIndex = 0
		var steps = 0
		var currentElementName string = elementName
		for mapProgress[elementName].stepsLoop == 0 {
			leftOrRight := directions.turnPattern[initialIndex]
			currentElementName = directions.directions[currentElementName][leftOrRight]
			if strings.LastIndex(currentElementName, "Z") == (len(currentElementName) - 1) {
				currentProgress := mapProgress[elementName]
				if mapProgress[elementName].stepsToZ == 0 {
					currentProgress.stepsToZ = steps
					steps = 0
				} else {
					currentProgress.stepsLoop = steps
				}
				mapProgress[elementName] = currentProgress
			}
			steps++
			initialIndex++
			if initialIndex == len(directions.turnPattern) {
				initialIndex = 0
			}
		}
	}
	var firstProgressLoopsSteps = 0
	var LCMTally = 0
	for elementName, progress := range mapProgress {
		if firstProgressLoopsSteps == 0 {
			firstProgressLoopsSteps = progress.stepsLoop
		} else if LCMTally == 0 {
			LCMTally = LCM(firstProgressLoopsSteps, progress.stepsLoop)
		} else {
			LCMTally = LCM(LCMTally, progress.stepsLoop)
		}
		fmt.Print(elementName, " stepsToZ ", progress.stepsToZ, " loop ", progress.stepsLoop, "\n")
	}
	fmt.Print(LCMTally, " lowest common multiple\n")
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
	if strings.LastIndex(elementName, "A") == (len(elementName) - 1) {
		directions.startNodes = append(directions.startNodes, elementName)
	}
	directionsString := dataArray[1]
	directionsString = strings.Replace(directionsString, "(", "", 1)
	directionsString = strings.Replace(directionsString, ")", "", 1)
	elements := strings.Split(directionsString, ", ")
	if directions.directions == nil {
		directions.directions = make(map[string][]string)
	}
	directions.directions[elementName] = []string{elements[0], elements[1]}
}
