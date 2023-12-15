package helper

import (
	"cmp"
	"fmt"
	"strconv"
	"strings"
)

type Direction int64

var OppositeDirectionMap = map[Direction]Direction{
	North: South,
	South: North,
	East:  West,
	West:  East,
}

const (
	North Direction = iota
	South
	East
	West
)

func (s Direction) String() string {
	switch s {
	case North:
		return "North"
	case South:
		return "South"
	case East:
		return "East"
	case West:
		return "West"
	}
	return "unknown"
}

type Coordinate struct {
	X int
	Y int
}

func SortSpaceByX(a, b *Space) int {
	if n := cmp.Compare(a.Coord.X, b.Coord.X); n != 0 {
		return n
	}
	// If names are equal, order by age
	return cmp.Compare(a.Coord.Y, b.Coord.Y)
}

func SortSpaceByY(a, b *Space) int {
	if n := cmp.Compare(a.Coord.Y, b.Coord.Y); n != 0 {
		return n
	}
	// If names are equal, order by age
	return cmp.Compare(a.Coord.X, b.Coord.X)
}

type Space struct {
	IsGalaxy bool
	Coord    Coordinate
}

type Tile struct {
	Symbol     rune
	Connected  []Direction
	StepsFromS int
	Coord      Coordinate
	PartOfLoop bool
}

type mappableItem interface {
	Tile | Space
}

type FieldMap[T mappableItem] struct {
	FieldMap map[int]map[int]*T
}

func (field *FieldMap[T]) AddToMap(x int, y int, item *T) {
	if field.FieldMap == nil {
		field.FieldMap = make(map[int]map[int]*T)
	}
	if field.FieldMap[x] == nil {
		field.FieldMap[x] = make(map[int]*T)
	}
	field.FieldMap[x][y] = item
}

func (field *FieldMap[T]) GetItem(coord Coordinate) *T {
	return field.FieldMap[coord.X][coord.Y]
}

func (field *FieldMap[T]) GetAdjacentItem(coord Coordinate, direction Direction) (*T, bool) {
	if direction == North {
		return field.getItemToNorth(coord)
	} else if direction == South {
		return field.getItemToSouth(coord)
	} else if direction == East {
		return field.getItemToEast(coord)
	} else {
		return field.getItemToWest(coord)
	}
}

func (field *FieldMap[T]) getItemToNorth(coord Coordinate) (*T, bool) {
	if coord.Y-1 >= 0 {
		return field.FieldMap[coord.X][coord.Y-1], true
	} else {
		var zeroT T
		return &zeroT, false
	}
}

func (field *FieldMap[T]) getItemToSouth(coord Coordinate) (*T, bool) {
	if coord.Y+1 < len(field.FieldMap[coord.X]) {
		return field.FieldMap[coord.X][coord.Y+1], true
	} else {
		var zeroT T
		return &zeroT, false
	}
}

func (field *FieldMap[T]) getItemToEast(coord Coordinate) (*T, bool) {
	if coord.X+1 < len(field.FieldMap) {
		return field.FieldMap[coord.X+1][coord.Y], true
	} else {
		var zeroT T
		return &zeroT, false
	}
}

func (field *FieldMap[T]) getItemToWest(coord Coordinate) (*T, bool) {
	if coord.X-1 >= 0 {
		return field.FieldMap[coord.X-1][coord.Y], true
	} else {
		var zeroT T
		return &zeroT, false
	}
}

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

var PRIME_NUMBERS = []int{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327}
