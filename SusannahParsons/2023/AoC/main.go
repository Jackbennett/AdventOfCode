// You can edit this code!
// Click here and start typing.
package main

import (
	cubes "AoC/day2"
	"fmt"
)

func main() {

	var data = returnFileContentsArray("day2/input.txt")
	var games cubes.Games
	for _, s := range data {
		games.ParseGame(s, 12, 14, 13)
	}
	fmt.Print(games.SumPossibleIds, " total.\n")
	// var treb1 trebuchet.Trebuchet
	// for _, s := range data {
	// 	treb1.AddCalibration(s)
	// }
	// fmt.Print(treb1.RunningTotal, " total.\n")
}
