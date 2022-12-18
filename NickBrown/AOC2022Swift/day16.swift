//
//  day16.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 17/12/2022.
//

// one minute to open
// one minute to travel
// 30 minutes to play with


import Foundation

struct Valve{
    let name: String
    let flowRate: Int
    let downstreamValves: [String]
    var reductions: [Int] = []
    
    init(name: String, flowRate: Int, downstreamValves: [String]) {
        self.name = name
        self.flowRate = flowRate
        self.downstreamValves = downstreamValves
    }
}
struct Point{
    let minutes: Int
    let currentLocation: String
    var openValves: [String] = []
    let totalPressureReduction: Int
    
    init(minutes: Int, currentLocation: String, openValves: [String], totalPressureReduction: Int) {
        self.minutes = minutes
        self.currentLocation = currentLocation
        self.openValves = openValves
        self.totalPressureReduction = totalPressureReduction
    }
}

class Day16: AdventOfCodeDay{
    var timeRemaining: Int = 30
    var valves: [String: Valve] = [:]
    var pressureReduction: Int = 0
    override init(_ input_filename: String, _ split: String) {
        super.init(input_filename, split)
        for line in data{
            let split = line
                .replacing("Valve ", with: "")
                .replacing("valves ", with: "")
                .replacing("valve ", with: "")
                .replacing(" has flow rate", with: "")
                .replacing(" tunnels lead to ", with: "")
                .replacing(" tunnel leads to ", with: "")
                .components(separatedBy: ";")
                .flatMap({$0.components(separatedBy: "=")})
            valves[split[0]] = Valve(name: split[0], flowRate: Int(split[1])!, downstreamValves: split[2].components(separatedBy: ", ") )
        }
    }
    func part1()->Int{
        // create a queue of minutes, current valve, opened valves and total flow
        var Seen: Set<[String]> = []
        var startPoints = Queue<Point>()
        startPoints.enqueue(Point(minutes: 0, currentLocation: "AA", openValves: [], totalPressureReduction: 0))
        while !startPoints.isEmpty{
            let currentPoint = startPoints.dequeue()!
            if currentPoint.minutes == 30{
                pressureReduction = max(pressureReduction, currentPoint.totalPressureReduction)
                continue
            }
            if Seen.contains([[currentPoint.currentLocation], currentPoint.openValves].flatMap{$0}){
                continue
            }
            Seen.insert([[currentPoint.currentLocation], currentPoint.openValves].flatMap{$0})
            var total: Int = currentPoint.totalPressureReduction
            for valve in currentPoint.openValves{
                total += valves[valve]!.flowRate
            }
            
            if valves[currentPoint.currentLocation]!.flowRate != 0{
                if !currentPoint.openValves.contains(currentPoint.currentLocation){
                    var openValves_ = currentPoint.openValves
                    openValves_.append(currentPoint.currentLocation)
                    startPoints.enqueue(Point(minutes: currentPoint.minutes + 1, currentLocation: currentPoint.currentLocation, openValves: openValves_, totalPressureReduction: total))
                }
            }
            for valve in valves[currentPoint.currentLocation]!.downstreamValves{
                startPoints.enqueue(Point(minutes: currentPoint.minutes + 1, currentLocation: valve, openValves: currentPoint.openValves, totalPressureReduction: total))
            }
        }
        return pressureReduction
    }
}

