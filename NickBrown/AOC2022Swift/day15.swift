//
//  day15.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 15/12/2022.
//

import Foundation

import QuartzCore

struct Sensor{
    let sx: Int
    let sy: Int
    let bx: Int
    let by: Int
    let distance: Int

    init(_ sensorData: [Int]){
        (self.sx, self.sy, self.bx, self.by) = (sensorData[0], sensorData[1], sensorData[2], sensorData[3])
        distance = abs(sx - bx) + abs(sy - by)
    }
    func pt1(_ row: Int)->ClosedRange<Int>?{
        let xdiff: Int = distance - abs(row - sy)
        if xdiff <= 0{
            return nil
        }
        return (sx-xdiff...sx+xdiff)
    }
    func pt2(_ row: Int)->[Int]?{
        let xdiff: Int = distance - abs(row - sy)
        if xdiff<=0{
            return nil
        }
        return [sx - xdiff, sx + xdiff]
    }
}

class Day15: AdventOfCodeDay{
    var sensors: [Sensor] = []
    var part1ans: Int = 0
    var beacons: [Int] = []
    var part2ans: Int = 0
    var rowCoverage: Set<Int> = []
    var sensorCoords: [Int] = []
    let searchSpace: Int = 4000000
    
    override init(_ input_filename: String, _ split: String) {
        super.init(input_filename, split)
        var sensors_ : [Sensor] = []
        for line in data{
            let split = line.components(separatedBy: ":").map { $0.components(separatedBy: ", ") }.map { [$0[0].components(separatedBy: "="), $0[1].components(separatedBy: "=")] }
            sensors_.append(Sensor([split[0][0][1], split[0][1][1], split[1][0][1], split[1][1][1]].map { Int($0)! }))
        }
        sensors = sensors_.sorted(by: {$0.sx < $1.sx})
        part1ans = part1(2000000)
    }
    func getNoBeaconPoints(_ row: Int)->[ClosedRange<Int>]{
        return sensors.compactMap{ $0.pt1(row) }
        
    }
    func part1(_ row: Int)->Int{
        rowCoverage.formUnion(getNoBeaconPoints(2000000).flatMap{$0})
        beacons = sensors.compactMap{ if $0.by == row{return $0.bx}else{return nil} }
        return rowCoverage.count - rowCoverage.intersection(beacons).count
    }
    func part2(){
        for row in 0...searchSpace{
            var coveredRange: [[Int]] = []
            for sensor in sensors{
                
                if sensor.pt2(row) == nil{
                    continue
                }
                else{
                    sensorCoords = sensor.pt2(row)!
                }
                if sensorCoords[0] > searchSpace || sensorCoords[1] < 0{
                    continue
                }
                if sensorCoords[0] < 0{
                    sensorCoords[0] = 0
                }
                if sensorCoords[1] > searchSpace{
                    sensorCoords[1] = searchSpace
                }
                if coveredRange == []{
                    coveredRange.append(sensorCoords)
                }
                else{
                    for i in 0..<coveredRange.count{
                        // sensor range already within covered range
                        if sensorCoords[0]>=coveredRange[i][0] && sensorCoords[1]<=coveredRange[i][1]{
                            continue
                        }
                        // create new range in covered range
                        else if sensorCoords[0] > coveredRange[i][1] || sensorCoords[1] < coveredRange[i][0]{
                            coveredRange.append(sensorCoords)
                        }
                        // extend left or right of covered range
                        else{
                            // extend left
                            if sensorCoords[0]<coveredRange[i][0]{
                                coveredRange[i][0] = sensorCoords[0]
                            }
                            // extend right
                            if sensorCoords[1]>coveredRange[i][1]{
                                coveredRange[i][1] = sensorCoords[1]
                            }
                        }
                    }
                }
            }
            let totalRange: [[Int]] = coveredRange.sorted(by: {$0[0]<$1[0]})
            var finalRange: [[Int]] = [totalRange[0]]
            for range in totalRange{
                if totalRange[0][1] - totalRange[0][0] == 4000000{
                    continue
                }
                if range[0] <= finalRange[0][1] + 1{
                    if range[1] > finalRange[0][1]{
                        finalRange[0][1] = range[1]
                    }
                }
                else{
                    part2ans = row + 4000000 * (finalRange[0][1] + 1)
                    return
                }
            }
        }
    }
}
