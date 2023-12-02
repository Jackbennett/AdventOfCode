package trebuchet

import (
	"fmt"
	"regexp"
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
	var letters []byte
	for i := 0; i < len(dataline) && !firstDigitFound; i++ {
		if unicode.IsNumber(rune(dataline[i])) {
			firstDigitFound = true
			firstLastDigit = string(dataline[i])
		} else {
			letters = append(letters, dataline[i])
			word, success := findNumberWord(letters)
			if success {
				firstDigitFound = true
				firstLastDigit = word
			}
		}
	}
	letters = make([]byte, 0)
	secondDigitFound := false
	for j := len(dataline) - 1; j > -1 && !secondDigitFound; j-- {
		if unicode.IsNumber(rune(dataline[j])) {
			secondDigitFound = true
			firstLastDigit = firstLastDigit + string(dataline[j])
		} else {
			letters = append([]byte{dataline[j]}, letters...)
			word, success := findNumberWord(letters)
			if success {
				secondDigitFound = true
				firstLastDigit = firstLastDigit + word
			}
		}
	}
	s, err := strconv.Atoi(firstLastDigit)
	if err != nil {
		fmt.Println("Can't convert this to an int! " + firstLastDigit)
	} else {
		treb.RunningTotal += int64(s)
	}

}

func findNumberWord(letters []byte) (string, bool) {
	numbers := [9]string{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}
	for index, element := range numbers {
		re := regexp.MustCompile(`.?` + element + `.?`)
		if re.Match([]byte(string(letters))) {
			return fmt.Sprint(index + 1), true
		}
	}
	return "", false
}
