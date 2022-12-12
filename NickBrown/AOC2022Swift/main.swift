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
    let a = day1(input_file:"/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day1.txt")
    print("Day 1 Part 1: \(a.max())")
    print("Day 1 Part 2: \(a.topThree())")
}
day_1()
let day1finish = CACurrentMediaTime()
print("Day 1 execution time: \(day1finish - start)")

func day_2(){
    let b = Day2(input_file:"/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day2.txt")
    b.open_input()
    print("Day 2 Part 1: \(b.pt1())")
    print("Day 2 Part 2: \(b.pt2())")
}
day_2()
let day2finish = CACurrentMediaTime()
print("Day 2 execution time: \(day2finish - day1finish)")

func day_3(){
    let c = Day3(filename: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day3.txt")
    print("Day 3 Part 1: \(c.sumOfPriorities)")
    c.threeElves()
    print("Day 3 Part 2: \(c.secondSum)")
}
day_3()
let day3finish = CACurrentMediaTime()
print("Day 3 execution time: \(day3finish - day2finish)")

func day_4(){
    let d = Day4(input_file_: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day4.txt")
    print("Day 4 Part 1: \(d.overlaps)")
    print("Day 4 Part 2: \(d.pt2)")
}
day_4()
let day4finish = CACurrentMediaTime()
print("Day 4 execution time: \(day4finish - day3finish)")

func day_5(){
    let e = Day5(filename: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day5.txt")
    print("Day 5 Part 1: \(e.pt1)")
    print("Day 5 Part 2: \(e.pt2)")
}
 day_5()
let day5finish = CACurrentMediaTime()
print("Day 5 execution time: \(day5finish - day4finish)")

func day_6(){
    print("Day 6 Part 1: \(day6(input_file: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day6.txt", num_digits: 4))")
    print("Day 6 Part 2: \(day6(input_file: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day6.txt", num_digits: 14))")
}
 day_6()
let day6finish = CACurrentMediaTime()
print("Day 6 execution time: \(day6finish - day5finish)")

func day_7(){
    let f = day7(input_file: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day7.txt")
    print("Day 7 Part 1: \(f.pt1())")
    print("Day 7 Part 2: \(f.pt2())")
}
 day_7()
let day7finish = CACurrentMediaTime()
print("Day 7 execution time: \(day7finish - day6finish)")

func day_8(){
    let g = day8(input_file: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day8.txt")
        print("Day 8 Part 1: \(g[0])")
        print("Day 8 Part 2: \(g[1])")
}
 day_8()
let day8finish = CACurrentMediaTime()
print("Day 8 execution time: \(day8finish - day7finish)")

func day_9(){
    let h = day9(input_file: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day9.txt")
        print("Day 9 Part 1: \(h[0])")
        print("Day 9 Part 2: \(h[1])")
}
 day_9()
let day9finish = CACurrentMediaTime()
print("Day 9 execution time: \(day9finish - day8finish)")

func day_10(){
    let i = day10(file10: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day10.txt")
    print("Day 10 Part 1: \(i.0)")
    print("Day 10 Part 2:\n\n\(i.1)\n")
}
 day_10()
let day10finish = CACurrentMediaTime()
print("Day 10 execution time: \(day10finish - day9finish)")

func day_11(){
    let j = day11(input_file: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day11.txt")
    print("Day 11 Part 1: \(j.part1())")
    print("Day 11 Part 2: \(j.part2())")
}
day_11()
let day11finish = CACurrentMediaTime()
print("Day 11 execution time: \(day11finish - day10finish)")

func day_12(){
    let k = Day12(input_file: "/Users/Nick/Documents/GitHub/AdventOfCode/NickBrown/AOC2022Swift/inputs/day12.txt")
    print("Day 12 Part 1: \(k.part1())")
    print("Day 12 Part 2: \(k.part2())")
}
day_12()
let day12finish = CACurrentMediaTime()
print("Day 12 execution time: \(day12finish - day11finish)")
