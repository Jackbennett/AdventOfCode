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

public struct Queue<T> {
  fileprivate var array: [T?] = [T?]()
  fileprivate var head: Int = 0
  
  public var isEmpty: Bool {
    return count == 0
  }

  public var count: Int {
    return array.count - head
  }
  
  public mutating func enqueue(_ element: T) {
    array.append(element)
  }
  
  public mutating func dequeue() -> T? {
    guard head < array.count, let element: T = array[head] else { return nil }

    array[head] = nil
    head += 1

    let percentage: Double = Double(head)/Double(array.count)
    if array.count > 50 && percentage > 0.25 {
      array.removeFirst(head)
      head = 0
    }
    
    return element
  }
  
  public var front: T? {
    if isEmpty {
      return nil
    } else {
      return array[head]
    }
  }
}