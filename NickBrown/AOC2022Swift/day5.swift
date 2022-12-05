//
//  day5.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 05/12/2022.
//

import Foundation

class Day5{
    let input_file:String
    var data:[String]
    var stacks:[[Character]]
    var startingStacks:[[Character]]
    var numberOfStacks:Int
    var stackPositions:[Int]
    var pt1:String
    var pt2:String
    var start2:Int
    
    init(filename:String){
        input_file = filename
        data = []
        stacks = []
        startingStacks = []
        numberOfStacks = 0
        stackPositions = []
        pt1 = ""
        pt2 = ""
        start2 = 0
        open_file()
        buildStacks()
        processData1()
        processData2()
    }
    
    func open_file(){
        let file_contents: String = try! String(contentsOfFile: input_file)
        data = file_contents.components(separatedBy: "\n")
        numberOfStacks = data[0].count / 4 + 1
        for i in stride(from: 1, to: numberOfStacks * numberOfStacks + 1, by: 4){
            stackPositions.append(i)
        }
    }
    
    func buildStacks(){
        stacks = []
        for _ in (0..<numberOfStacks){
            stacks.append([])
        }
    }
    
    func fillInitialStacks()->Int{
        var i = 0
        while data[i].count == data[0].count{
            for j in (0..<numberOfStacks){
                let container = data[i][stackPositions[j]]
                if container != " "{
                    stacks[j].append(data[i][stackPositions[j]])
                }
            }
            i += 1
        }
        for stack in (0..<stacks.count){
            stacks[stack].removeLast()
        }
        return i
    }
    
    func processData1(){
        var i = fillInitialStacks()
        startingStacks = stacks
        start2 = i
        i+=1
        var instruction:[String]
        while i<data.count{
            instruction = data[i].components(separatedBy: " ")
            for _ in (0..<Int(instruction[1])!){
                moveContainer(from: Int(instruction[3])!-1, to: Int(instruction[5])!-1)
            }
            i+=1
        }
        for stack in stacks{
            if stack.count>0{
                pt1 += String(stack[0])
            }
        }
    }
    
    func processData2(){
        stacks = startingStacks
        var i = start2
        i+=1
        var instruction:[String]
        while i<data.count{
            instruction = data[i].components(separatedBy: " ")
            moveContainers(from: Int(instruction[3])!-1, to: Int(instruction[5])!-1, many: Int(instruction[1])!)
            i+=1
        }
        for stack in stacks{
            if stack.count>0{
                pt2 += String(stack[0])
            }
        }
    }
    
    func moveContainer(from:Int, to:Int){
        stacks[to].insert(stacks[from].removeFirst(), at: 0)
    }
    
    func moveContainers(from:Int, to:Int, many:Int){
        stacks[to].insert(contentsOf: stacks[from][0..<many], at: 0)
        stacks[from].removeFirst(many)
    }
}





