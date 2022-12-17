//
//  day11.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 11/12/2022.
//

import Foundation

class Monkey{
    var items: [Int] = []
    let monkeyInput: String
    let operation: [String]
    var worryMultiplier: Int
    let worryIsSelf: Bool
    var worryLevel: Int = 0
    let worryOperator: Character
    let trueReceiver: Int
    let falseReceiver: Int
    let testDivisor: Int
    var inspections: Int = 0
    
    init(monkeyInput: String){
        self.monkeyInput = monkeyInput
        let lines = monkeyInput.components(separatedBy: "\n")
        items = lines[1].components(separatedBy: ":")[1].components(separatedBy: ",").map { Int($0[String.Index(utf16Offset: 1, in: $0)..<$0.endIndex])! }
        
        trueReceiver = Int(lines[4].components(separatedBy: " ")[9])!
        
        falseReceiver = Int(lines[5].components(separatedBy: " ")[9])!
        
        testDivisor = Int(lines[3].components(separatedBy: " ")[5])!
        
        operation = lines[2].components(separatedBy: " ")
        
        if operation[7] == "old"{
            worryIsSelf = true
            worryMultiplier = 0
        }
        else{
            worryMultiplier = Int(operation[7])!
            worryIsSelf = false
        }
        worryOperator = Character(operation[6])
    }
}

class day11{
    var Monkeys: [Monkey] = []
    var part2Monkeys: [Monkey] = []
    let input_file: String
    let data: [String]
    var receiver: Int = 0
    var worryLevelDivider: Int = 3
    var divisors: [Int] = []
    var reducerModulo: Int = 1
    
    init(input_file: String){
        self.input_file = input_file
        let file_contents: String = try! String(contentsOfFile: input_file)
        data = file_contents.components(separatedBy: "\n\n")
        for block in data{
            let a = Monkey(monkeyInput: block)
            Monkeys.append(a)
            part2Monkeys.append(Monkey(monkeyInput: block))
            reducerModulo *= a.testDivisor
        }
    }
    
    func part1()->Int{
        for _ in 0..<20{
            OneRound(part2: false)
        }
        return getMonkeyBusiness()
    }
    
    func part2()->Int{
        Monkeys = part2Monkeys
        worryLevelDivider = 1
        for _ in 0..<10_000{
            OneRound(part2: true)
        }
        return getMonkeyBusiness()
    }
    
    func getMonkeyBusiness()->Int{
        var inspections: [Int] = []
        for monkey in Monkeys{
            inspections.append(monkey.inspections)
        }
        inspections.sort()
        return inspections.reversed()[0] * inspections.reversed()[1]
    }
    
    func OneRound(part2: Bool){
        for monkey in Monkeys{
            for item in monkey.items{
                if monkey.worryIsSelf{
                    monkey.worryMultiplier = item
                }
                switch monkey.worryOperator{
                case "*": monkey.worryLevel = (item * monkey.worryMultiplier) / worryLevelDivider
                case "+": monkey.worryLevel = (item + monkey.worryMultiplier) / worryLevelDivider
                default: print("Error in monkey operation")
                }
                if part2{
                    monkey.worryLevel = monkey.worryLevel % reducerModulo
                }
                if monkey.worryLevel % monkey.testDivisor == 0{
                    receiver = monkey.trueReceiver
                }
                else{
                    receiver = monkey.falseReceiver
                }
            Monkeys[receiver].items.append(monkey.worryLevel)
            monkey.inspections += 1
            }
            monkey.items = []
        }
    }
}

