//
//  day6.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 06/12/2022.
//

import Foundation

func open_file(input_file:String)->[Character]{
    let file_contents: String = try! String(contentsOfFile: input_file)
    let data = Array(file_contents)
    return data
}

func day6(input_file:String, num_digits:Int)->Int{ // num digits 4 or 14 for parts 1 and 2
    let data = open_file(input_file: input_file)
    for i in (num_digits-1..<data.count){
        if Set(data[i-(num_digits-1)...i]).count == num_digits{
            return i + 1
        }
    }
    return 0
}
