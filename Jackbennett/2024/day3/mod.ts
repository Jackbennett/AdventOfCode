import { assertEquals } from "jsr:@std/assert";

const parse = (f:string, pattern: RegExp) => {
    const file = Deno.readTextFileSync(f)
    const matches = file.matchAll(pattern)
    return matches
}

const int = (n: string) => parseInt(n, 10) 

export function part1(){
    const data = parse('./input.txt', /mul\((\d+),(\d+)\)/g)
    let sum = 0
    for( const [_ins, a, b ] of data) {
        sum += int(a) * int(b)
    }
    return sum
}

Deno.test('Day 3 parts 1', () => {
    assertEquals(part1(), 164730528)
})

export function part2() {
    const data = parse('./input.txt', /(mul\((\d+),(\d+)\)|(do|don't)\(\))/g)
    let process = true
    let sum = 0
    for (const [ins, ...args] of data){
        switch(ins.split('(').at(0)) {
            case 'mul': {
                    const [_pattern, a,b] = args
                    sum += process ? int(a) * int(b) : 0
                    break;
                }
            case 'do':
                process = true
                break;
            case "don't":
                process = false
                break;
        }
    }
    return sum
}

Deno.test('Day 3 part 2', () => { 
    assertEquals(part2(), 70478672)
})

console.log(part2())