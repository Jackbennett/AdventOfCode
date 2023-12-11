// You can edit this code!
// Click here and start typing.
package main

import (
	sensor "AoC/day9"
	"fmt"
)

func main() {
	var data = returnFileContentsArray("day9/input.txt")
	//Day 9
	var report sensor.Report
	for _, s := range data {
		report.ParseHistories(s)
	}
	fmt.Print(report.SumPredictions, " sum predictions\n")
	fmt.Print(report.SumReversePredictions, " sum reverse predictions\n")

	//Day 8
	// var directions directions.Directions
	// for _, s := range data {
	// 	directions.ParseDirections(s)
	// }
	// directions.FollowDirections()

	// //Day 7
	// var game camelcards.Game
	// for _, s := range data {
	// 	game.ParseHand(s)
	// }
	// game.FindWinnings()

	//Day 6
	// var races races.Races
	// for _, s := range data {
	// 	races.ParseRaces(s)
	// }
	// multipleMarinsOfError := races.FindMarginOfError()
	// fmt.Print(multipleMarinsOfError, " multiple margins of error\n")

	//Day 5
	// var almanac almanac.Almanac
	// for _, s := range data {
	// 	almanac.ParseAlmanac(s)
	// }
	// lowestLoc := almanac.FindLocations()
	// fmt.Print(lowestLoc, " lowest location\n")

	//Day 4
	// var cardPile scratchcard.CardPile
	// cardPile.Cards = make(map[int]scratchcard.Scratchcard)
	// for i, s := range data {
	// 	cardPile.ParseCards(s, i)
	// }
	// fmt.Print(cardPile.TotalPoints, " total.\n")
	// cardPile.CountCards()

	//Day 3
	// var engine engine.Engine
	// for i, s := range data {
	// 	engine.AddLine(s, i)
	// }
	// engine.FindPartNumbers()
	// fmt.Print(engine.TotalPartNumber, " total.\n")
	// engine.FindGearRatios()
	// fmt.Print(engine.SumGearRatios, " sum gear ratios\n")
	//Day 2
	// var games cubes.Games
	// for _, s := range data {
	// 	games.ParseGame(s, 12, 14, 13)
	// }
	// fmt.Print(games.SumPossibleIds, " total.\n")
	// fmt.Print(games.SumPower, " sum powers\n")

	//Day 1
	// var treb1 trebuchet.Trebuchet
	// for _, s := range data {
	// 	treb1.AddCalibration(s)
	// }
	// fmt.Print(treb1.RunningTotal, " total.\n")
}
