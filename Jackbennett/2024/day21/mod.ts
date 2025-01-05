import { assertEquals } from "jsr:@std/assert/equals";
import { sum } from "../util.ts";
import { AStarFinder } from "npm:astar-typescript";

const example = `029A
980A
179A
456A
379A`

const example_answer = `
029A: <vA<AA>>^AvAA<^A>A<v<A>>^AvA^A<vA>^A<v<A>^A>AAvA^A<v<A>A>^AAAvA<^A>A
980A: <v<A>>^AAAvA^A<vA<AA>>^AvAA<^A>A<v<A>A>^AAAvA<^A>A<vA>^A<A>A
179A: <v<A>>^A<vA<A>>^AAvAA<^A>A<v<A>>^AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A
456A: <v<A>>^AA<vA<A>>^AAvAA<^A>A<vA>^A<A>A<vA>^A<A>A<v<A>A>^AAvA<^A>A
379A: <v<A>>^AvA^A<vA<AA>>^AAvA<^A>AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A`

const input = `803A
528A
586A
341A
319A`


const keypad = {
    number: [
        ['7','8','9'],
        ['4','5','6'],
        ['1','2','3'],
        ['#','0','A']
    ],
    // +---+---+---+
    // | 7 | 8 | 9 |
    // +---+---+---+
    // | 4 | 5 | 6 |
    // +---+---+---+
    // | 1 | 2 | 3 |
    // +---+---+---+
    //     | 0 | A |
    //     +---+---+
    directional: [
        ['#', '^', 'A'],
        ['<', 'v', '>']
    ]
    //     +---+---+
    //     | ^ | A |
    // +---+---+---+
    // | < | v | > |
    // +---+---+---+
    //     +---+---+
    //     | ^ | A |
    // +---+---+---+
    // | < | v | > |
    // +---+---+---+
    //     +---+---+
    //     | ^ | A |
    // +---+---+---+
    // | < | v | > |
    // +---+---+---+


}

const shortestPath = (code: string) => {
    const seq = code.split('')

}

const parseCode = (code: string) => {
    const [_orig, num] = code.match(/\d+/) || []

    return parseInt(num, 10) // will throw if no num
}


const part1 = (f: string) => {
    const codepad = f.split('\n')

    const total = codepad.map(d =>
    ({
        pathlength: shortestPath(d),
        number: parseCode(d)
    })
    ).map( ({pathlength, number}) => pathlength * number )
    .reduce(sum)

    return total
}

Deno.test('day 21 example', () => {
    const ans = part1(example)

    assertEquals(ans, 126384)
})