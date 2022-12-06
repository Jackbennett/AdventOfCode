//
//  day6.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 06/12/2022.
//

import Foundation

func open_file(input_file:String)->[String.SubSequence]{
    let file_contents: String = try! String(contentsOfFile: input_file)
    let data = file_contents.split(separator: "")
    return data
}
func day6(input_file:String, num_digits:Int)->Int{
    let data = open_file(input_file: input_file)
    for i in (num_digits-1..<data.count){
        if Set(data[i-(num_digits-1)...i]).count == num_digits{
            return i + 1
        }
    }
    return 0
}
