// You can edit this code!
// Click here and start typing.
package main

import (
	scratchcard "AoC/day4"
	"fmt"
)

func main() {
	var data = returnFileContentsArray("day4/input.txt")
	//Day 4
	var cardPile scratchcard.CardPile
	cardPile.Cards = make(map[int]scratchcard.Scratchcard)
	for i, s := range data {
		cardPile.ParseCards(s, i)
	}
	fmt.Print(cardPile.TotalPoints, " total.\n")
	cardPile.CountCards()

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
