//
//  day12.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 12/12/2022.
//

import Foundation

struct Start{
    let position: [Int]
    let distance: Int
}

class Day12{
    var Grid: [[Character]] = []
    let data: [String]
    var starts = Queue<Start>()
    var Part1Start: Start = Start(position: [0, 0], distance: 0)
    var Seen: Set<[Int]> = []
    var part2starts: [Start] = []
    let moves = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    var end: Start = Start(position: [0, 0], distance: 0)
    
    init(input_file: String){
        let file_contents: String = try! String(contentsOfFile: input_file)
        data = file_contents.components(separatedBy: "\n")
        for i in 0..<data.count{
            Grid.append([])
            for j in 0..<data[0].count{
                if data[i][j] == "S"{
                    Part1Start = Start(position: [i, j], distance: 0)
                    Grid[i].append("a")
                }
                else if data[i][j] == "E"{
                    end = Start(position: [i, j], distance: 0)
                    Grid[i].append("z")
                }
                else{
                    Grid[i].append(data[i][j])
                    if Grid[i][j] == "a"{
                        part2starts.append(Start(position: [i, j], distance: 0))
                    }
                }
            }
        }
    }
    func part1()->Int{
        return Search(start_point: Part1Start)
    }
    func part2()->Int{
        var distances: [Int] = []
        for beginning in part2starts{
            Seen = []
            distances.append(Search(start_point: beginning))
        }
        return distances.min()!
    }
    func Search(start_point: Start)->Int{
        starts = Queue<Start>()
        starts.enqueue(start_point)
        while !starts.isEmpty{
            let point = starts.dequeue()!
            if point.position == end.position{
                return point.distance
            }
            if Seen.contains(point.position){
                continue
            }
            Seen.insert(point.position)
            
            for move in moves{
                if (0 <= point.position[0] + move.0 &&
                    point.position[0] + move.0 < Grid.count &&
                    0 <= point.position[1] + move.1 &&
                    point.position[1] + move.1 < Grid[0].count &&
                    (getIntFromChar(char: Grid[point.position[0] + move.0][point.position[1] + move.1]) - getIntFromChar(char: Grid[point.position[0]][point.position[1]])) <= 1){
                    starts.enqueue(Start(position: [point.position[0] + move.0, point.position[1] + move.1], distance: point.distance + 1))
                }
            }
        }
        return Grid.count * Grid.count
    }
}
