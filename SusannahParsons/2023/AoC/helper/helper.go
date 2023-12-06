package helper

import (
	"fmt"
	"strconv"
	"strings"
)

func GetIntArrayFromStringList(stringlist string, delimiter string) []int {
	var intArray []int
	stringArray := strings.Split(strings.Trim(stringlist, " "), delimiter)
	for _, numberString := range stringArray {
		if numberString == "" {
			continue
		}
		newNumber, err := strconv.Atoi(strings.Trim(numberString, " "))
		if err != nil {
			fmt.Println("Can't convert this to an int! '" + numberString + "'")
		} else {
			intArray = append(intArray, newNumber)
		}
	}
	return intArray
}
