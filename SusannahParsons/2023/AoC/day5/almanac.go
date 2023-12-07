package almanac

import (
	"AoC/helper"
	"strings"
)

type FoodMap struct {
	complete               bool
	sourceToDestinationMap [][]int
	destination            string
}

type Almanac struct {
	FoodMaps map[string]FoodMap
	Seeds    []int
}

func (almanac *Almanac) findOpenMapKey() string {
	for key, value := range almanac.FoodMaps {
		if !value.complete {
			return key
		}
	}
	return ""
}

func (almanac *Almanac) ParseAlmanac(line string) {
	if almanac.FoodMaps == nil {
		//Initialise almanac
		almanac.FoodMaps = make(map[string]FoodMap)
	}
	if strings.Contains(line, "seeds") {
		almanac.Seeds = helper.GetIntArrayFromStringList(strings.Trim(strings.Split(line, ":")[1], " "), " ")
	} else if strings.Contains(line, ":") {

		//Complete any old maps.
		oldMapKey := almanac.findOpenMapKey()
		if oldMapKey != "" {
			oldMap := almanac.FoodMaps[oldMapKey]
			oldMap.complete = true
			almanac.FoodMaps[oldMapKey] = oldMap
		}

		//Start of a mapping. Initialise new foodmap.
		var newFoodMap FoodMap
		sourceToDestination := strings.Split(strings.Split(line, " ")[0], "-")
		newFoodMap.destination = sourceToDestination[2]
		almanac.FoodMaps[sourceToDestination[0]] = newFoodMap
	} else if line == "" {
	} else {
		//Mapping line
		//Find the unfinished map
		mapKey := almanac.findOpenMapKey()
		currentMap := almanac.FoodMaps[mapKey]
		mappingLine := helper.GetIntArrayFromStringList(line, " ")
		currentMap.sourceToDestinationMap = append(currentMap.sourceToDestinationMap, mappingLine)
		almanac.FoodMaps[mapKey] = currentMap
	}
}

func (almanac *Almanac) FindLocations() int {
	var lowestLoc int
	//Part 1
	//for _, seed := range almanac.Seeds {
	//Part 2
	for i := 0; i < len(almanac.Seeds); i = i + 2 {
		seedStartRange1 := almanac.Seeds[i]
		seedRange1Length := almanac.Seeds[i+1]
		for seed := seedStartRange1; seed < seedStartRange1+seedRange1Length; seed++ {
			location := almanac.findLocation("seed", seed)
			if lowestLoc == 0 {
				lowestLoc = location
			}
			if location < lowestLoc {
				lowestLoc = location
			}
		}
	}
	return lowestLoc
}

func (almanac *Almanac) findLocation(sourceString string, sourceNumber int) int {
	destination := almanac.FoodMaps[sourceString].destination
	var destinationNumber int
	for _, rangeMap := range almanac.FoodMaps[sourceString].sourceToDestinationMap {
		destinationStart := rangeMap[0]
		sourceStart := rangeMap[1]
		rangeLength := rangeMap[2]
		sourceEnd := sourceStart + rangeLength - 1
		if sourceNumber >= sourceStart && sourceNumber <= sourceEnd {
			indexSource := sourceNumber - sourceStart
			destinationNumber = destinationStart + indexSource
			break
		}
	}
	if destinationNumber == 0 {
		destinationNumber = sourceNumber
	}
	if destination != "location" {
		return almanac.findLocation(destination, destinationNumber)
	} else {
		return destinationNumber
	}
}
