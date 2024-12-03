import { assertEquals } from "jsr:@std/assert";

const parse = (f:string) => {
    const file = Deno.readTextFileSync(f)
    const matches = file.matchAll(/mul\((\d+),(\d+)\)/g)
    return matches
}

const int = (n: string) => parseInt(n, 10) 

export function part1(){
    const data = parse('./input.txt')
    let sum = 0
    for( const [_ins, a, b ] of data) {
        sum += int(a) * int(b)
    }
    return sum
}

Deno.test('Day 3 parts 1', () => {
    assertEquals(part1(), 164730528)
})


console.log(part1())