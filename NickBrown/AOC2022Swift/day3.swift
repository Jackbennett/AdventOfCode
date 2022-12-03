//
//  day3.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 03/12/2022.
//

import Foundation

func getIntFromChar(char:Character)->Int{
    if char.isLowercase{
        return Int(char.asciiValue!) - 96
    }
    else{
        return Int(char.asciiValue!) - 38
    }
}

class Day3{
    var input_file: String
    var data: Array<String>
    var sumOfPriorities: Int
    var secondSum: Int
    var backpacks: Array<Rucksack>
    init(filename: String){
        input_file = filename
        data = []
        backpacks = []
        sumOfPriorities = 0
        secondSum = 0
        open_input()
        fill_rucksacks()
    }
    func open_input(){
        let file_contents = try! String(contentsOfFile: input_file)
        for group in file_contents.components(separatedBy: "\n"){
            data.append(group)
        }
    }
    func fill_rucksacks(){
        for line in data{
            let a = Rucksack(inputString: line)
            backpacks.append(a)
            sumOfPriorities += a.getPriorityScore()
        }
    }
    func threeElves(){
        for i in stride(from: backpacks.startIndex, to: backpacks.endIndex, by: 3){
            for num in backpacks[i].backPackContents{
                if (backpacks[i+1].backPackContents.contains(num) && backpacks[i+2].backPackContents.contains(num)){
                    secondSum += num
                break
                }
            }
        }
    }
}

class Rucksack{
    let backPackContents:Array<Int>
    init(inputString:String){
        backPackContents = Array(inputString).map(getIntFromChar(char:))
    }
    
    func getPriorityScore()->Int{
        let halfStringLength: Int = backPackContents.count / 2
        for i in backPackContents[0...halfStringLength]{
            if backPackContents[halfStringLength...].contains(i){
                return i
                }
            }
        return 0
        }
}



