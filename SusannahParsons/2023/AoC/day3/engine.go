package engine

import (
	"fmt"
	"regexp"
	"strconv"
	"unicode"
)

type Coordinate struct {
	x int
	y int
}

type EnginePart struct {
	content []byte
	start   Coordinate
	end     Coordinate
}

type Symbol struct {
	x int
	y int
}

type Engine struct {
	Parts           []EnginePart
	Symbols         []Symbol
	PartNumbers     []EnginePart
	TotalPartNumber int64
}

func (eng *Engine) AddLine(line string, y int) {
	for x := 0; x < len(line); x++ {
		if unicode.IsNumber(rune(line[x])) {
			var newPart EnginePart
			var partContent []byte
			var startPart Coordinate
			startPart.x = x
			startPart.y = y
			var endPart Coordinate
			endPart.y = y
			for unicode.IsNumber(rune(line[x])) {
				partContent = append(partContent, line[x])
				endPart.x = x
				x++
				if x == len(line) {
					break
				}
			}
			newPart.content = partContent
			newPart.start = startPart
			newPart.end = endPart
			eng.Parts = append(eng.Parts, newPart)
		}
		if x == len(line) {
			break
		}
		re := regexp.MustCompile(`\.`)
		if !re.MatchString(string(line[x])) {
			//Found symbol
			var newSymbol Symbol
			newSymbol.x = x
			newSymbol.y = y
			eng.Symbols = append(eng.Symbols, newSymbol)
		}
	}
}

func (eng *Engine) FindPartNumbers() {
	for _, part := range eng.Parts {
		//Need to know if symbol is anywhere within (x-1, y-1) to (x+1, y+1) of the part
		var minX = part.start.x - 1
		var minY = part.start.y - 1
		var maxX = part.end.x + 1
		var maxY = part.end.y + 1
		//Iterate symbols, if one is adjacent, this is a partnumber
		for _, symbol := range eng.Symbols {
			if symbol.x >= minX && symbol.x <= maxX && symbol.y >= minY && symbol.y <= maxY {
				//This is a part number
				eng.PartNumbers = append(eng.PartNumbers, part)
				partNum, err := strconv.Atoi(string(part.content))
				if err != nil {
					fmt.Println("Can't convert this to an int! " + string(part.content))
				} else {
					eng.TotalPartNumber += int64(partNum)
				}
				break
			}
		}
	}
}
