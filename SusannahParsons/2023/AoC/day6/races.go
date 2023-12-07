package races

import (
	"AoC/helper"
	"fmt"
	"math"
	"strconv"
	"strings"
)

//Basically the product of splitting the race time and multiplying together must be greater than distance.
//Margin of error is the number in the range product1 to product2
//Want multiple of margins of error
/**
Time:      7  15   30
Distance:  9  40  200
**/

type Races struct {
	raceTime     []int
	raceDistance []int
	day2Time     int
	day2Distance int
}

func (races *Races) ParseRaces(line string) {
	if strings.Contains(line, "Time") {
		races.raceTime = helper.GetIntArrayFromStringList(strings.Trim(strings.Split(line, ":")[1], " "), " ")
		timeString := strings.ReplaceAll(strings.Trim(strings.Split(line, ":")[1], " "), " ", "")
		newTime, err := strconv.Atoi(timeString)
		if err != nil {
			fmt.Print("Couldn't convert string to int ", timeString, "\n")
		} else {
			races.day2Time = newTime
		}
	} else {
		races.raceDistance = helper.GetIntArrayFromStringList(strings.Trim(strings.Split(line, ":")[1], " "), " ")
		distanceString := strings.ReplaceAll(strings.Trim(strings.Split(line, ":")[1], " "), " ", "")
		newDistance, err := strconv.Atoi(distanceString)
		if err != nil {
			fmt.Print("Couldn't convert string to int ", distanceString, "\n")
		} else {
			races.day2Distance = newDistance
		}
	}
}

func (races *Races) FindMarginOfError() int64 {
	multipleMarginsError := int64(1)
	//Part 1
	// for i := range races.raceTime {
	// 	raceTime := races.raceTime[i]
	// 	raceDistance := races.raceDistance[i]
	//Part 2
	raceTime := races.day2Time
	raceDistance := races.day2Distance
	var minFactor int
	for timeFactor := 1; timeFactor < raceTime/2; timeFactor++ {
		if (timeFactor * (raceTime - timeFactor)) > raceDistance {
			minFactor = timeFactor
			break
		}
	}

	halfRaceTime := int(math.Round(float64(raceTime) / 2.0))
	marginOfError := (halfRaceTime - minFactor) * 2
	if math.Mod(float64(raceTime), 2) == 0 {
		//Even number, add 1
		marginOfError++
	}
	multipleMarginsError = multipleMarginsError * int64(marginOfError)
	return multipleMarginsError
}
