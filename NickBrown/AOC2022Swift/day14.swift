//
//  day14.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 14/12/2022.
//

import Foundation

class Day14{
    let lines: [String]
    var lineStart: [Int] = []
    var lineEnd: [Int] = []
    var Rocks: Set<[Int]> = []
    var newPos: [Int] = []
    var lowestRock: Int
    var sandCountpt1: Int = 0
    var sandCountpt2: Int = 0
    
    init(filename: String){
        lines = try! String(contentsOfFile: filename).components(separatedBy: "\n")
        
        for l: String in lines{
            let line: [[Int]] = l.components(separatedBy: " -> ").map { $0.components(separatedBy: ",").map {Int($0)!} }
            for i: Int in 0..<(line.count-1){
                if line[i][0] > line[i + 1][0] || line[i][1] > line[i + 1][1]{
                    lineStart = line[i + 1]
                    lineEnd = line[i]
                }
                else{
                    lineStart = line[i]
                    lineEnd = line[i+1]
                }
                
                // x's are equal, vertical line
                if lineStart[0] == lineEnd[0]{
                    for j: Int in lineStart[1]...lineEnd[1]{
                        Rocks.insert([lineStart[0], j])
                    }
                }
                
                else{
                    for j: Int in lineStart[0]...lineEnd[0]{
                        Rocks.insert([j, lineStart[1]])
                    }
                }
            }
        }
        lowestRock = Rocks.compactMap { Int($0[1]) }.max()!
        newPos = dropSand()
        while newPos[0] != -1{
            newPos = dropSand(posFrom: newPos)
        }
        lowestRock += 2
        sandCountpt2 += sandCountpt1
        newPos = dropSand()
        while newPos[0] != -1 && !Rocks.contains([500,0]){
            newPos = dropSand(partTwo: true, posFrom: newPos)
        }
    }
    
    func dropSand(partTwo: Bool = false, posFrom: [Int] = [500, 0])->[Int]{
        if !partTwo && posFrom[1] >= lowestRock{
            // sand is falling to infinity
            newPos = [-1, 0]
            return newPos
        }
        if partTwo && posFrom[1] == lowestRock - 1{
            Rocks.insert(posFrom)
            sandCountpt2 += 1
            newPos = [500, 0]
            return newPos
        }
        // can move down?
        newPos = [posFrom[0], posFrom[1] + 1]
        if !Rocks.contains(newPos){
            return newPos
        }
        // can move diagonally down and left
        newPos = [posFrom[0] - 1, posFrom[1] + 1]
        if !Rocks.contains(newPos){
            return newPos
        }
        // can move diagonally down and right
        newPos = [posFrom[0] + 1, posFrom[1] + 1]
        if !Rocks.contains(newPos){
            return newPos
        }
        else{
            Rocks.insert(posFrom)
            if !partTwo{
                sandCountpt1 += 1
            }
            else{
                sandCountpt2 += 1
            }
            newPos = [500, 0]
            return newPos
        }
    }
}

