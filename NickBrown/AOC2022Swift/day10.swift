//
//  day10.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 09/12/2022.
//

import Foundation

var instructions_: [String] = []
var x: Int = 1
var signalStrengthSum: Int = 0
var cycleCount: Int = 1
var CRTCursor: Int = 0
var answer2: String = ""

func day10(file10: String)->(Int, String){
    open_file(filename10: file10)
    sumSignalStrengths()
    return (signalStrengthSum, answer2)
}


func open_file(filename10:String){
    let file_contents: String = try! String(contentsOfFile: filename10)
    instructions_ = file_contents.components(separatedBy: "\n")
}

func sumSignalStrengths(){
    for j in 0..<instructions_.count{
        cycleCount += 1
        getScore()
        drawPixel()
        let instruction = instructions_[j].components(separatedBy: " ")
        if instruction.count == 2{
            drawPixel()
            x += Int(instruction[1])!
            cycleCount += 1
            getScore()
            
        }
    }
}

func getScore(){
    if (cycleCount - 20) % 40 == 0 && cycleCount < 221{
        signalStrengthSum += cycleCount * x
    }
}

func drawPixel(){
    if x - 1 <= CRTCursor && CRTCursor <= x + 1{
        answer2 += "#"
    }
    else{
        answer2 += " "
    }
    if CRTCursor % 40 == 0 && CRTCursor != 0{
        answer2 += "\n"
        CRTCursor = 0
    }
    CRTCursor += 1
}

