import { assertEquals } from "jsr:@std/assert";
import { distance } from "../day1/mod.ts"

const parse = (f: string) => {
  const txt = Deno.readTextFileSync(f);
  return txt.split("\n")
    .map((line) => line.split(" ").map((d) => parseInt(d, 10)));
};


enum Safety {
    Safe,
    Unsafe
}

const up = (val, idx, arr) => {
    if (idx === 0)
        return true
    return val > arr[idx - 1]
}
const down = (val, idx, arr) => {
    if (idx === 0)
        return true
    return val < arr[idx - 1]
}

type everyFn = (...p: Parameters<Array<number[]>["every"]>) => boolean
function trap(fn: (...p: Parameters<everyFn>) => boolean) {
    let trap: boolean = false
    return (...args: Parameters<everyFn>) => {
        const check = fn(...args)
        if(check === false && trap === true) {
            trap = true
            return check
        } else {
            return check
        }
    }
}


function asDistance(prev, val, idx, arr){
    const peek = arr.at(idx + 1)
    prev[idx] = peek ? distance(val, peek) : 0
    return prev
}

export function PoC(f: string) {
    const records = parse(f);
    
    const safety = Array.from(Array(records.length))
    records.forEach((levels, i) => {
        // direction check
        if (! (levels.every(up) || levels.every(down))){
            safety[i] = Safety.Unsafe
            return
        }

        // distance check
        const distances = Array.from(Array(levels.length))
        levels.reduce(asDistance, distances)
        
        if(distances.every(d => d <=3)) {
            safety[i] = Safety.Safe
        } else {
            safety[i] = Safety.Unsafe
        }

    })

    // count safety.
    const safe = safety.filter(s => s === Safety.Safe).length
    return safe
}

export function Part2(f: string) {
    const records = parse(f);
    
    const safety = Array.from(Array(records.length))
    records.forEach((levels, i) => {
        // direction check
        const tripup = trap(up)
        const tripdownup = trap(down)
        if (! (levels.every(tripup) || levels.every(tripdownup))){
            safety[i] = Safety.Unsafe
            return
        }

        // distance check
        const distances = Array.from(Array(levels.length))
        levels.reduce(asDistance, distances)
        
        if(distances.every(d => d <=3)) {
            safety[i] = Safety.Safe
        } else {
            safety[i] = Safety.Unsafe
        }

    })

    // count safety.
    const safe = safety.filter(s => s === Safety.Safe).length
    return safe
}


Deno.test('PoC', () => {
    const ans  = PoC("./example.txt")
    assertEquals(ans, 2)
    console.log(ans)
})

const part1 = () => {
    const ans  = PoC("./input.txt")
    console.log(ans)
    return ans
}

Deno.test('Day 2 part 1', () => {
    const ans = part1()
    assertEquals(ans, 510)
})
// Deno.test('Day 2 part 2', () => {
    //     const ans = part1()
    //     assertEquals(ans, 510)
    // })
    
const part2 = () => {
    const ans  = Part2("./input.txt")
    console.log(ans)
    return ans
}

part2()

