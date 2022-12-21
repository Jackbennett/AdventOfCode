//
//  day21.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 21/12/2022.
//

import Foundation

class Day21: AdventOfCodeDay{
    var Monkeys: [String: [String]] = [:]
    
    override init(_ input_filename: String, _ split: String) {
        super.init(input_filename, split)
        for line in data{
            let splitLine = line.components(separatedBy: ": ")
            Monkeys[splitLine[0]] = splitLine[1].components(separatedBy: " ")
        }
    }
    
    func part1()->Int{
        return Int(calcMonkeyValue("root"))
    }
    func calcMonkeyValue(_ MonkeyName: String)->Double{
        let monkey = Monkeys[MonkeyName]
        if monkey?.count == 1{
            return Double(monkey![0])!
        }
        else{
            switch monkey![1]{
            case "*": return calcMonkeyValue(monkey![0]) * calcMonkeyValue(monkey![2])
            case "+": return calcMonkeyValue(monkey![0]) + calcMonkeyValue(monkey![2])
            case "-": return calcMonkeyValue(monkey![0]) - calcMonkeyValue(monkey![2])
            case "/": return calcMonkeyValue(monkey![0]) / calcMonkeyValue(monkey![2])
            default: return 0
            }
        }
    }
    func part2()->Int{
        let monkey = Monkeys["root"]
        var humanMax: Double = 1.3e17
        var humanMin: Double = -1 * humanMax
        Monkeys["humn"] = [String(humanMin)]
        let minError = calcMonkeyValue(monkey![2]) - calcMonkeyValue(monkey![0])
        if minError > 0{
            (humanMin, humanMax) = (humanMax, humanMin)
        }
        var actualError: Double = 1
        while actualError != 0{
            let val: Double = (humanMin + humanMax) / 2
            Monkeys["humn"] = [String(val)]
            actualError = calcMonkeyValue(monkey![2]) - calcMonkeyValue(monkey![0])
            if actualError < 0{
                humanMin = val
            }
            else{
                humanMax = val
            }
        }
        return Int(Double(Monkeys["humn"]![0])!)
    }
}
