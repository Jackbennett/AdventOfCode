//
//  day4.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 04/12/2022.
//

import Foundation

class Day4{
    var data:Array<Array<Set<Int>>>
    var input_file:String
    var overlaps: Int
    var pt2: Int
    
    init(input_file_:String){
        data = []
        input_file = input_file_
        overlaps = 0
        pt2 = 0
        open_input()
        checkOverlaps()
    }
    func open_input(){
        let file_contents = try! String(contentsOfFile: input_file)
        for group in file_contents.components(separatedBy: "\n"){
            let ranges = group.components(separatedBy: ",")
            data.append([Set(Range(Int(ranges[0].components(separatedBy: "-")[0])!...Int(ranges[0].components(separatedBy: "-")[1])!)),Set(Range(Int(ranges[1].components(separatedBy: "-")[0])!...Int(ranges[1].components(separatedBy: "-")[1])!))])
        }
    }
    func checkOverlaps(){
        for sets in data{
            if sets[0].isSubset(of: sets[1]) || sets[1].isSubset(of: sets[0]){
                overlaps += 1
            }
            if sets[0].intersection(sets[1]) != []{
                pt2 += 1
            }
        }
    }
}
