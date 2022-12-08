//
//  day7.swift
//  AOC2022Swift
//
//  Created by Nick Brown on 07/12/2022.
//

import Foundation

class day7{
    let root: directory
    var data:[String] = []
    var currentDirectory: directory
    var sizes: [Int] = []
    var ans1: Int = 0
    var ans2: Int = 0
    let input_file: String
    let totalSpace: Int = 70000000
    let initialFreeSpace: Int = 30000000
    var currentSizeSum: Int = 0
    
    init(input_file: String){
        self.root = directory(name: "root")
        self.currentDirectory = self.root
        self.input_file = input_file
    }
    
    func pt1()->Int{
        open_file()
        processTerminal()
        calcSizes(start: root)
        for size in sizes{
            currentSizeSum += size
            if size<=100000{
                ans1 += size
            }
        }
        return ans1
    }
    func pt2()->Int{
        let freeSpaceNeeded = ((totalSpace - root.size) - initialFreeSpace) * -1
        var candidates:[Int] = []
        for size in sizes{
            if size > freeSpaceNeeded{
                candidates.append(size)
            }
        }
        return candidates.min()!
    }
    
    func open_file(){
        let file_contents: String = try! String(contentsOfFile: input_file)
        data = file_contents.components(separatedBy: "\n")
        
    }
    
    func processTerminal(){
        for i in (0..<data.count){
            if data[i].starts(with: "$ cd"){
                changeDirectory(command: data[i])
            }
            if data[i].starts(with: "$ ls"){
                var commands: [String] = []
                var j = i + 1
                while j<data.count && !data[j].starts(with: "$"){
                    commands.append(data[j])
                    j+=1
                }
                listContents(commands: commands)
            }
        }
    }
    
    func calcSizes(start: directory){
        sizes.append(start.size)
        for dir in start.subdirectories{
            calcSizes(start: dir)
        }
    }
    
    func changeDirectory(command:String){
        let command:[String] = command.components(separatedBy: " ")
        if command[2] == "/"{
            currentDirectory = root
        }
        else if command[2] == ".."{
            
            currentDirectory = currentDirectory.parent!
        }
        else{
            var subdirs: [String] = []
            for dir in currentDirectory.subdirectories{
                subdirs.append(dir.name)
            }
            if !subdirs.contains(command[2]){
                let new_dir: directory = directory(name: command[2], parent: currentDirectory)
                currentDirectory.subdirectories.append(new_dir)
                self.currentDirectory = new_dir
            }
            else{
                for dir in currentDirectory.subdirectories{
                    if dir.name == command[2]{
                        currentDirectory = dir
                    }
                }
            }
        }
    }
    
    func listContents(commands:[String]){
        for command in commands{
            let command_: [String] = command.components(separatedBy: " ")
            if command_[0] == "dir"{
                currentDirectory.subdirectories.append(directory(name: command_[1], parent: currentDirectory))
            }
            else{
                currentDirectory.files.append(file(name: command_[1], size: Int(command_[0])!, parent: currentDirectory))
            }
        }
    }
}

class directory{
    let name: String
    var subdirectories: [directory]
    var files: [file]
    var parent: directory?
    var size: Int{
        var size = 0
        for file in files{
            size+=file.size
        }
        for directory in subdirectories{
            size+=directory.size
        }
        return size
    }
    init(name:String, parent: directory? = nil){
        self.name = name
        self.subdirectories = []
        self.files = []
        self.parent = parent
    }
    
}
struct file{
    let name: String
    let size: Int
    let parent: directory
    
    init(name: String, size: Int, parent: directory){
        self.name = name
        self.size = size
        self.parent = parent
    }
}
