import Foundation

// returns the entire input file as an array of its lines as strings
func openInputFile(input_file: String)->Array<Substring>{
    let contents = try! String(contentsOfFile: input_file)
    let lines = contents.split(separator: "\n")
    
    return lines
}

extension StringProtocol {
    subscript(offset: Int) -> Character {
        return self[index(startIndex, offsetBy: offset)]
    }
}