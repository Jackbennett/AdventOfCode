import { assertEquals, assertGreater } from 'jsr:@std/assert';
import { toSplitNumber, sum } from '../util.ts'
import { TextLineStream } from "https://deno.land/std/streams/mod.ts";

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

const cache = new Map<string, number>()

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
        return input.flatMap(this.part1)
    },
    part1(d: number) {return (this.rules[0](d) || this.rules[1](d) || this.rules[2](d)) as number | number[]},
    part2(d: number, blinks: number): number {
        const decrement = blinks - 1
        const cckey = [decrement, d].join('-')
        
        const stones = this.part1(d)

        if(decrement === 0) return Array.isArray(stones) ? 2 : 1

        const cached = cache.get(cckey)
        if(cached) return cached

        if(Array.isArray(stones)) {
            const a = this.part2(stones[0], decrement)
            const b = this.part2(stones[1], decrement)
            const chain_sum = a+b
            cache.set(cckey, chain_sum)
            return chain_sum
        } 

        return this.part2(stones, decrement)
    }
    // async part2(index: number) {
    //     let stoneCount = 0
    //     const state = await Deno.open(`./state.${index}.txt`)
    //     const output = await Deno.open(`./state.${index+1}.txt`, {
    //         create: true,
    //         write: true,
    //         truncate: true,
    //       })
    //     state.readable
    //     .pipeThrough(new TextDecoderStream())
    //     .pipeThrough(new TextLineStream())
    //     .pipeThrough((n) => {
    //         const ans = this.part1(n)
    //         stoneCount += Array.isArray(ans) ? ans.length : 1
    //         return Array.isArray(ans) ? ans.join('\n') : ans
    //     )
    //     .pipeTo(output.writable)

    //     return stoneCount
    // }
}

// Deno.test('Day 11 example', () => {
//     const stones = toSplitNumber(example)
//     const answer = part1.run(stones)
//     console.log(answer)
//     const check = toSplitNumber('1 2024 1 0 9 9 2021976')
//     check.forEach((val, idx) =>{
//         assertEquals(answer[idx], val)
//     }
//     )
// })

Deno.test('Day 11 part 1', () => {
    /// How many stones will you have after blinking 25 times?
    const stones = toSplitNumber(`3279 998884 1832781 517 8 18864 28 0`)
    let answer = stones
    for(let count = 0; count < 25; count += 1){
        answer = part1.run(answer)
    }
    console.log(answer.length)
    assertEquals(answer.length, 218956)
})

Deno.test('Day 11 part 2', () => {
    /// How many stones will you have after blinking 75 times?

    const stones = toSplitNumber(`3279 998884 1832781 517 8 18864 28 0`)
    console.time()
    const items = stones.map( s =>{
        console.timeStamp()
        console.log(`getting ${s}`)
        const v = part1.part2(s, 75)
        console.log(`\t counted as ${v}`)
        return v
    }
    )
    const total = items.reduce(sum)
    console.timeEnd()
    console.log(total)
    assertEquals(total, 259593838049805)
})