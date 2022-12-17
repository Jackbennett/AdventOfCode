import Foundation

// returns the entire input file as an array of its lines as strings
func openInputFile(input_file: String)->Array<Substring>{
    let contents: String = try! String(contentsOfFile: input_file)
    let lines: [String.SubSequence] = contents.split(separator: "\n")
    
    return lines
}

extension StringProtocol {
    subscript(offset: Int) -> Character {
        return self[index(startIndex, offsetBy: offset)]
    }
}

class AdventOfCodeDay{
    let data: [String]
    init(_ input_filename: String, _ split: String){
        let file_contents: String = try! String(contentsOfFile: input_filename)
        data = file_contents.components(separatedBy: split)
    }
}
