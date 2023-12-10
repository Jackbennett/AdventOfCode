package camelcards

import (
	"bytes"
	"cmp"
	"fmt"
	"regexp"
	"slices"
	"strconv"
	"strings"
)

var CARDSTRENGTH = []byte{'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'}

var FIVEOFAKIND = 7
var FOUROFAKIND = 6
var FULLHOUSE = 5
var THREEOFAKIND = 4
var TWOPAIR = 3
var ONEPAIR = 2
var HIGHCARD = 1

type Hand struct {
	hand     []byte
	handtype int
	bid      int
}

type Game struct {
	hands []Hand
}

func compareHand(a, b Hand) int {
	if n := cmp.Compare(a.handtype, b.handtype); n != 0 {
		return n
	}
	// If handtypes are equal, order by strength
	for i := range a.hand {
		if m := cmp.Compare(bytes.Index(CARDSTRENGTH, []byte{b.hand[i]}), bytes.Index(CARDSTRENGTH, []byte{a.hand[i]})); m != 0 {
			return m
		}
	}
	//Strength is equal too, these are the same
	return 0
}

func (game *Game) FindWinnings() {
	slices.SortFunc(game.hands, compareHand)
	var totalWinnings int = 0
	for rank := 1; rank <= len(game.hands); rank++ {
		totalWinnings += rank * game.hands[rank-1].bid
	}
	fmt.Print(totalWinnings, " total winnings\n")
}

func (game *Game) ParseHand(line string) {
	var hand Hand
	dataArray := strings.Split(line, " ")
	hand.hand = []byte(dataArray[0])
	bid, err := strconv.Atoi(dataArray[1])
	if err != nil {
		fmt.Print("Can't convert string to int ", dataArray[1])
	} else {
		hand.bid = bid
	}
	hand.getType()
	game.hands = append(game.hands, hand)
}

func (hand *Hand) getType() {
	var threesFound int = 0
	var pairsFound int = 0
	var fiveOfAKindFound bool = false
	var fourOfAKindFound bool = false
	for _, cardLetter := range CARDSTRENGTH {
		cardLetterRegExp := regexp.MustCompile(string(cardLetter))
		matches := len(cardLetterRegExp.FindAllStringIndex(string(hand.hand), -1))
		if matches == 5 {
			fiveOfAKindFound = true
			break
		} else if matches == 4 {
			fourOfAKindFound = true
			break
		} else if matches == 3 {
			threesFound++
		} else if matches == 2 {
			pairsFound++
		}
	}
	if fiveOfAKindFound {
		hand.handtype = FIVEOFAKIND
	} else if fourOfAKindFound {
		hand.handtype = FOUROFAKIND
	} else if threesFound == 1 && pairsFound == 1 {
		hand.handtype = FULLHOUSE
	} else if threesFound == 1 && pairsFound == 0 {
		hand.handtype = THREEOFAKIND
	} else if threesFound == 0 && pairsFound == 2 {
		hand.handtype = TWOPAIR
	} else if threesFound == 0 && pairsFound == 1 {
		hand.handtype = ONEPAIR
	} else if threesFound == 0 && pairsFound == 0 {
		hand.handtype = HIGHCARD
	}
}
