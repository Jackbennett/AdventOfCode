// You can edit this code!
// Click here and start typing.
package main

import (
	"AoC/trebuchet"
	"fmt"
)

func main() {
	var treb1 trebuchet.Trebuchet
	var data = returnFileContentsArray("trebuchet/input.txt")
	for _, s := range data {
		treb1.AddCalibration(s)
	}
	fmt.Print(treb1.RunningTotal, " total.\n")
}
