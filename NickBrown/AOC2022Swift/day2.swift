//
//  day2.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 02/12/2022.
//
import Foundation

class Day2{
    let rps = ["X": 1, "Y": 2, "Z": 3]
    let rps2 = ["X": 0, "Y": 3, "Z": 6]
    let rpsmap = ["A":"X", "B":"Y", "C":"Z"]
    let WIN: Int = 6
    let DRAW: Int = 3
    let LOSE: Int = 0
    var data: Array<Array<String>>
    let input_file: String

    init(input_file:String){
        self.input_file = input_file
        self.data = []
        
    }
    func open_input(){
        let file_contents = try! String(contentsOfFile: input_file)
        for line in file_contents.components(separatedBy: "\n"){
            data.append(line.components(separatedBy: " "))
        }
    }
    func pt1()->Int {
        var score: Int = 0
        for plays in data{
            score += rps[plays[1]]!
            if (plays[1] == "X" && plays[0] == "A") || (plays[1] == "Y" && plays[0] == "B") || (plays[1] == "Z" && plays[0] == "C"){
                score += DRAW
            }
            else if (plays[1] == "X" && plays[0] == "C") || (plays[1] == "Y" && plays[0] == "A") || (plays[1] == "Z" && plays[0] == "B"){
                score += WIN
            }
        }
        return score
    }

    func pt2()->Int{
        var score: Int = 0
        for plays in data{
            score += rps2[plays[1]]!
            if plays[1] == "Z"{
                if plays[0] == "A"{
                    score += rps["Y"]!
                }
                else if plays[0] == "B"{
                    score += rps["Z"]!
                }
                else if plays[0] == "C"{
                    score += rps["X"]!
                }
            }
            else if plays[1] == "Y"{
                score += rps[rpsmap[plays[0]]!]!
            }
            else{
                if plays[0] == "A"{
                    score += rps["Z"]!
                }
                else if plays[0] == "B"{
                    score += rps["X"]!
                }
                else if plays[0] == "C"{
                    score += rps["Y"]!
                }
            }
        }
        return score
    }
}

