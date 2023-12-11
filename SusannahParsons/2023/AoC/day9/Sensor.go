package sensor

import (
	"AoC/helper"
)

type History struct {
	sequences [][]int
}

type Report struct {
	histories      []History
	SumPredictions int
}

func (report *Report) ParseHistories(line string) {
	var newHistory History
	var firstSequence = helper.GetIntArrayFromStringList(line, " ")
	newHistory.sequences = append(newHistory.sequences, firstSequence)
	prediction := newHistory.getPrediction()
	report.SumPredictions += prediction
	report.histories = append(report.histories, newHistory)
}

func (history History) getPrediction() int {
	lastSequence := history.sequences[len(history.sequences)-1]
	var sequenceDifferences []int
	currentInt := lastSequence[0]
	var allZero = true
	for index := 1; index < len(lastSequence); index++ {
		newInt := lastSequence[index] - currentInt
		if !(newInt == 0) {
			allZero = false
		}
		sequenceDifferences = append(sequenceDifferences, newInt)
		currentInt = lastSequence[index]
	}
	history.sequences = append(history.sequences, sequenceDifferences)
	if !allZero {
		return history.getPrediction()
	} else {
		//Iterate the sequences upwards and get prediction to return
		extrapolation := 0
		zeroSequence := history.sequences[len(history.sequences)-1]
		zeroSequence = append(zeroSequence, extrapolation)
		history.sequences[len(history.sequences)-1] = zeroSequence
		for j := len(history.sequences) - 2; j >= 0; j-- {
			nextSequence := history.sequences[j]
			lastValue := nextSequence[len(nextSequence)-1]
			extrapolation += lastValue
			nextSequence = append(nextSequence, extrapolation)
			history.sequences[j] = nextSequence
		}
		return extrapolation
	}
}
