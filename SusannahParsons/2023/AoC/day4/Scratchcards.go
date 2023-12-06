package scratchcards

import (
	"AoC/helper"
	"fmt"
	"slices"
	"strings"
)

type Scratchcard struct {
	winningNumbers      []int
	myNumbers           []int
	winningNumbersFound []int
	cardPoints          int
	copies              int
}

type CardPile struct {
	Cards       map[int]Scratchcard
	TotalPoints int64
}

func (cardpile *CardPile) ParseCards(line string, index int) {
	cardNumber := index + 1
	var newCard Scratchcard
	if cardpile.Cards[cardNumber].copies != 0 {
		newCard.copies = cardpile.Cards[cardNumber].copies + 1
	} else {
		newCard.copies = 1
	}
	s := strings.Split(strings.Split(line, ":")[1], "|")
	newCard.winningNumbers = helper.GetIntArrayFromStringList(strings.Trim(s[0], " "), " ")
	newCard.myNumbers = helper.GetIntArrayFromStringList(strings.Trim(s[1], " "), " ")
	var points = 0
	for _, winningNum := range newCard.winningNumbers {
		if slices.Contains(newCard.myNumbers, winningNum) {
			if points == 0 {
				points = 1
			} else {
				points = points * 2
			}
			newCard.winningNumbersFound = append(newCard.winningNumbersFound, winningNum)
		}
	}
	newCard.cardPoints = points
	cardpile.TotalPoints += int64(points)

	numberWinningNumbers := len(newCard.winningNumbersFound)
	for i := 0; i < newCard.copies; i++ {
		cardpile.copyCards(cardNumber, numberWinningNumbers)
	}

	cardpile.Cards[cardNumber] = newCard
}

func (cardpile *CardPile) copyCards(cardNumber int, numberWinningNumbers int) {
	startCardNumber := cardNumber + 1
	endCardNumber := numberWinningNumbers + cardNumber
	for copyCardNumber := startCardNumber; copyCardNumber <= endCardNumber; copyCardNumber++ {
		if cardpile.Cards[copyCardNumber].copies != 0 {
			//Card exists
			cardToCopy := cardpile.Cards[copyCardNumber]
			cardToCopy.copies++
			cardpile.Cards[copyCardNumber] = cardToCopy
		} else {
			//No card exists
			var newCopyCard Scratchcard
			newCopyCard.copies = 1
			cardpile.Cards[copyCardNumber] = newCopyCard
		}
	}
}

func (cardpile *CardPile) CountCards() {
	var totalCards int64 = 0
	for _, card := range cardpile.Cards {
		// fmt.Printf("There are %d copies of card %d\n", card.copies, cardNumber)
		totalCards += int64(card.copies)
	}
	fmt.Printf("Total cards %d\n", totalCards)
}
