import { assertEquals } from 'jsr:@std/assert';
import { toSplitNumber } from '../util.ts'

const example = `0 1 10 99 999`

const cut = (n: number) => {
    const s = `${n}`
    const mid = Math.abs(s.length / 2)
    return toSplitNumber(`${s.slice(0, mid)} ${s.slice(mid)}`)
}

Deno.test('day 7 cut', () => {
    const [left,right] = cut(1000)
    assertEquals(left, 10)
    assertEquals(right, 0)
})

const part1 = {
    rules: [
        //     If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
        (stone: number) => {
            if(stone === 0) return 1
        },
        // If the stone is engraved with a number that has an even number of digits, it is replaced by two stones.
        // The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone.
        // (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
        (stone: number) => {
            if(`${stone}`.length % 2  === 0) return cut(stone)
        },
        // If none of the other rules apply, the stone is replaced by a new stone;
        // the old stone's number multiplied by 2024 is engraved on the new stone.
        (stone: number) => stone * 2024
    ],
    run(input: number[]): number[] {
        return input.flatMap((d => this.rules[0](d) || this.rules[1](d) || this.rules[2](d))) as number[]
    }
}

Deno.test('Day 11 example', () => {
    const stones = toSplitNumber(example)
    const answer = part1.run(stones)
    console.log(answer)
    const check = toSplitNumber('1 2024 1 0 9 9 2021976')
    check.forEach((val, idx) =>{
        assertEquals(answer[idx], val)
    }
    )
})

// Deno.test('Day 11 part 1', () => {
//     /// How many stones will you have after blinking 25 times?
//     const stones = toSplitNumber(`3279 998884 1832781 517 8 18864 28 0`)
//     let answer = stones
//     for(let count = 0; count < 25; count += 1){
//         answer = part1.run(answer)
//     }
//     console.log(answer.length)
// })

Deno.test('Day 11 part 2', () => {
    /// How many stones will you have after blinking 25 times?
    const stones = toSplitNumber(`3279 998884 1832781 517 8 18864 28 0`)
    let answer = stones
    console.time('part2')
    for(let count = 0; count < 75; count += 1){
        answer = part1.run(answer)
        console.timeLog('part2', count, answer.length, Deno.memoryUsage())

    }
    console.timeEnd('part2')
    console.log(answer.length)
})