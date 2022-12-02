
import Foundation

class day1{
    var input_file:String
    var elves:Array<Array<Int>>
    var _sums:Array<Int>
    init(input_file:String){
        self.input_file = input_file
        self.elves = []
        self._sums = []
    }
    func open_input(){
        let file_contents = try! String(contentsOfFile: input_file)
        for group in file_contents.components(separatedBy: "\n\n"){
            elves.append(group.split(separator:"\n").map { Int($0)! })
        }
    }
    func sums(){
        open_input()
        for elf in elves{
            _sums.append(elf.reduce(0,+))
        }
    }
    func max()->Int{
        sums()
        let max = _sums.max()!
        return max
    }
    func topThree()->Int{
        return _sums.sorted().reversed()[...2].reduce(0,+)
    }
}
