//
//  day9.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 09/12/2022.
//

import Foundation

func day9(input_file: String)->[Int]{
    open_file(filename9: input_file)
    makeNine()
    processInstructions()
    return [nineKnots[0].history.count, nineKnots[8].history.count]
}

struct ropeKnot{
    var x: Int = 0
    var y: Int = 0
    var history: Set<Array<Int>> = [[0,0]]
}
var head: ropeKnot = ropeKnot()

var nineKnots: [ropeKnot] = []
func makeNine(){
    for _ in 0..<9{
        nineKnots.append(ropeKnot())
    }
}

var instructions: [[Character: Int]] = []

func open_file(filename9:String){
    let file_contents: String = try! String(contentsOfFile: filename9)
    let lines:[String] = file_contents.components(separatedBy: "\n")
    for line in lines{
        instructions.append([Character(String(line.split(separator: " ")[0])): Int(line.split(separator: " ")[1])!])
    }
}

func processInstructions(){
    for instruction in instructions{
        let direction = Array(instruction.keys)[0]
        let amount = instruction[direction]!
        for _ in 0..<amount{
            moveHead(direction: direction)
        }
    }
}

func moveHead(direction: Character){
    switch direction{
    case "R": head.x += 1
    case "L": head.x -= 1
    case "U": head.y += 1
    case "D": head.y -= 1
    default: print("invalid direction detected")
    }
    head.history.insert([head.x, head.y])
    moveFollower(leader: head, follower: &nineKnots[0])
    for i in 1..<9{
        moveFollower(leader: nineKnots[i-1], follower: &nineKnots[i])
    }
}

func moveFollower(leader: ropeKnot, follower: inout ropeKnot){
    // var follower = follower
    let xdiff = leader.x - follower.x
    let ydiff = leader.y - follower.y
    let axdiff = abs(xdiff)
    let aydiff = abs(ydiff)

    if axdiff <= 1 && aydiff <= 1{
        // touching diagonally
        return
    }
    else if axdiff * aydiff > 1{
        // diagonal move needed
        follower.x += (xdiff / axdiff)
        follower.y += (ydiff / aydiff)
        follower.history.insert([follower.x, follower.y])
        return
    }
    else if axdiff > 0{
        follower.x += (xdiff / axdiff)
        follower.history.insert([follower.x, follower.y])
        return
    }
    else{
        follower.y += (ydiff / aydiff)
        follower.history.insert([follower.x, follower.y])
        return
    }
}
