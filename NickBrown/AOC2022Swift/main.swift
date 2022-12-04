//
//  main.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 01/12/2022.
//
// REPL available at https://replit.com/@nickbrown1987/AdventOfCode22

import Foundation
import QuartzCore

let start = CACurrentMediaTime()

func day_1(){
    let a = day1(input_file:"/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/day1.txt")
    print("Day 1 Part 1: \(a.max())")
    print("Day 1 Part 2: \(a.topThree())")
}
day_1()
let day1finish = CACurrentMediaTime()
print("Day 1 execution time: \(day1finish - start)")

func day_2(){
    let b = Day2(input_file:"/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/day2.txt")
    b.open_input()
    print("Day 2 Part 1: \(b.pt1())")
    print("Day 2 Part 2: \(b.pt2())")
}
day_2()
let day2finish = CACurrentMediaTime()
print("Day 2 execution time: \(day2finish - day1finish)")

func day_3(){
    let c = Day3(filename: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/day3.txt")
    print("Day 3 Part 1: \(c.sumOfPriorities)")
    c.threeElves()
    print("Day 3 Part 2: \(c.secondSum)")
}
day_3()
let day3finish = CACurrentMediaTime()
print("Day 3 execution time: \(day3finish - day2finish)")

func day_4(){
    let d = Day4(input_file_: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/day4.txt")
    print("Day 4 Part 1: \(d.overlaps)")
    print("Day 4 Part 2: \(d.pt2)")
}
 day_4()
let day4finish = CACurrentMediaTime()
print("Day 4 execution time: \(day4finish - day3finish)")
