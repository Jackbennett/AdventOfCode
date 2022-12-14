////
////  day13.swift
////  AOC2022Swift
////
////  Created by Nick Brown on 13/12/2022.
////
//
//import Foundation
//
//class Day13{
//    let Packets: [String]
//    var Correct: Int = 0
//
//    init(filename: String){
//        let file_contents: String = try! String(contentsOfFile: filename)
//        let file_contents: String = try! String(contentsOfFile: filename)
//        let file_contents: String = try! String(contentsOfFile: filename)
//        Packets = file_contents.components(separatedBy: "\n\n")
//
//        let JSONData = Packets[0].components(separatedBy: "\n")[0].data(using: .utf8)!
//        let decoded = try! JSONDecoder().decode(from: JSONData)
////        CheckPairOrder()
//    }
////    func CheckPairOrder(){
////        for packet in Packets{
////            let p = packet.components(separatedBy: "\n")
////            Correct += ComparePackets(packet1: p[0], packet2: p[1])
////        }
////    }
////    // returns 1 for correct or 0 for incorrect
////    func ComparePackets(packet1: String, packet2: String)->Int{
////        var level1 = 0
////        var level2 = 0
////        for char in packet1{
////            print(char)
////        }
////        return 1
////    }
////    func CheckChars(char: Character, level: inout Int, char2: Character, level2: inout Int){
////        switch (char, char2){
////        case ("[",: level += 1
////        case "]": level -= 1
////        }
////
////    }
//}
//
//
