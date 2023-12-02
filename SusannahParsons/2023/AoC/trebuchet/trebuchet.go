package trebuchet

import (
	"fmt"
	"strconv"
	"unicode"
)

type Trebuchet struct {
	RunningTotal int64
}

func (treb *Trebuchet) AddCalibration(dataline string) {
	var firstLastDigit string
	//Iterate forwards to find first digit
	firstDigitFound := false
	for i := 0; i < len(dataline) && !firstDigitFound; i++ {
		if unicode.IsNumber(rune(dataline[i])) {
			firstDigitFound = true
			firstLastDigit = string(dataline[i])
		}

	}
	secondDigitFound := false
	for j := len(dataline) - 1; j > -1 && !secondDigitFound; j-- {
		if unicode.IsNumber(rune(dataline[j])) {
			secondDigitFound = true
			firstLastDigit = firstLastDigit + string(dataline[j])
		}
	}
	s, err := strconv.Atoi(firstLastDigit)
	if err != nil {
		fmt.Println("Can't convert this to an int!")
	} else {
		treb.RunningTotal += int64(s)
	}

}
