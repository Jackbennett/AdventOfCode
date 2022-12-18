//
//  day18.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 18/12/2022.
//

import Foundation


struct Cube: Hashable{
    let x: Int
    let y: Int
    let z: Int
    
    init(_ x: Int, _ y: Int, _ z: Int) {
        self.x = x
        self.y = y
        self.z = z
    }
    var xyz: (Int, Int, Int){
        return (x, y, z)
    }
    func hash(into hasher: inout Hasher) {
        hasher.combine("\(xyz)")
    }
}

class Day18: AdventOfCodeDay{
    var cubes: [Cube] = []
    var Structure: Set<Cube> = []
    var SurfaceArea: Int = 6
    let adjacents = [
        (1, 0, 0),
        (-1, 0, 0),
        (0, 1, 0),
        (0, -1, 0),
        (0, 0, 1),
        (0, 0, -1)
    ]
    
    override init(_ input_filename: String, _ split: String) {
        super.init(input_filename, split)
        for line in data{
            let cube_ = line.components(separatedBy: ",").map{Int($0)!}
            cubes.append(Cube(cube_[0], cube_[1], cube_[2]))
        }
    }
    func part1()->Int{
        for i in 1..<cubes.count{
            Structure.insert(cubes[i - 1])
            SurfaceArea += 6
            for adjacent in adjacents {
                if Structure.contains(Cube(cubes[i].x + adjacent.0, cubes[i].y + adjacent.1, cubes[i].z + adjacent.2)){
                    SurfaceArea -= 2
                }
            }
        }
        return SurfaceArea
    }
}

