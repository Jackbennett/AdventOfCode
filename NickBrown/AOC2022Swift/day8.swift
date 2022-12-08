//
//  day8.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 08/12/2022.
//

import Foundation

var forest: [[Int]] = []
var visibleTreeCount: Int = 0
var highestScenicScore: Int = 0

func day8(input_file:String)->[Int]{
    open_file(filename_: input_file)
    findVisibleTrees()
    return [visibleTreeCount, highestScenicScore]
}

func open_file(filename_:String){
    let file_contents: String = try! String(contentsOfFile: filename_)
    let lines:[String] = file_contents.components(separatedBy: "\n")
    for line in lines{
        forest.append(line.split(separator: "").map { Int($0)! })
        
    }
}

func findVisibleTrees(){
    let height = forest.count
    let width = forest[0].count
    visibleTreeCount += (height+width) * 2 - 4
    for i in (1..<height-1){
        for j in (1..<width-1){
            getScenicScore(i: i, j: j, height: height, width: width)
            if forest[i][0...j-1].max()! < forest[i][j]{
                visibleTreeCount += 1
            }
            else if forest[i][j+1...width-1].max()! < forest[i][j]{
                visibleTreeCount += 1
            }
            else {
                var verticalLine: [Int] = []
                for k in (0..<height){
                    verticalLine.append(forest[k][j])
                }
                if verticalLine[0..<i].max()! < forest[i][j]{
                    visibleTreeCount += 1
                }
                else if verticalLine[i+1..<height].max()! < forest[i][j]{
                    visibleTreeCount += 1
                }
            }
        }
    }
    
    // get the scenic score for round the outside, as these were not checked in the visible loops
    for row in 0..<height{
        getScenicScore(i: row, j: 0, height: height, width: width)
        getScenicScore(i: row, j: width-1, height: height, width: width)
    }
    for column in 1..<width-1{
        getScenicScore(i: 0, j: column, height: height, width: width)
        getScenicScore(i: height-1, j: column, height: height, width: width)
    }
    
}
func getScenicScore(i:Int, j:Int, height:Int, width:Int){
    var thisScenicScore: Int = 0
    var up:Int = 0, down:Int = 0, left:Int = 0, right:Int = 0
    for k in (0..<i).reversed(){
        if forest[k][j] < forest[i][j]{
            up += 1
        }
        else if forest[k][j] >= forest[i][j]{
            up += 1
            break
        }
        else{
            break
        }
    }
    for k in (i+1..<height){
        if forest[k][j] < forest[i][j]{
            down += 1
        }
        else if forest[k][j] >= forest[i][j]{
            down += 1
            break
        }
        else{
            break
        }
    }
    for k in (0..<j).reversed(){
        if forest[i][k] < forest[i][j]{
            left += 1
        }
        else if forest[i][k] >= forest[i][j]{
            left += 1
            break
        }
        else{
            break
        }
    }
    for k in (j+1..<width){
        if forest[i][k] < forest[i][j]{
            right += 1
        }
        else if forest[i][k] >= forest[i][j]{
            right += 1
            break
        }
        else{
            break
        }
    }
    thisScenicScore = up * down * left * right
    if thisScenicScore > highestScenicScore{
        highestScenicScore = thisScenicScore
    }
}
