import { assert, assertEquals } from "jsr:@std/assert";

const parse = (f: string) => {
  const txt = Deno.readTextFileSync(f);
  return txt.split("\n")
    .filter(line => line.length)
    .map((line) => line.split(" ").map((d) => parseInt(d, 10)));
};


enum Safety {
    Safe,
    Unsafe
}

const up = (val: number, idx: number, arr: number[]) => {
    if (idx === 0)
        return true
    return val > arr[idx - 1]
}
const down = (val: number, idx: number, arr: number[]) => {
    if (idx === 0)
        return true
    return val < arr[idx - 1]
}

function asDistance(prev: number[], val: number, idx: number, arr: number[]){
    const peek = arr.at(idx + 1)
    if (peek === undefined) return prev
    prev.push(val - peek)
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

interface Counter {pos: number, neg: number}

export function Part2(f: string) {
    const records = parse(f);
    
    const safety = Array.from(Array(records.length))
    records.forEach((levels, i) => {

        // distance check
        const distances: number[] = levels.reduce(asDistance, [])
        const getSign = (n:number) => n >= 0 ? 'pos' : 'neg'
        const reduceSigns = (count: Counter, sign: ReturnType<typeof getSign>) => { sign === 'pos' ? count.pos +=1 : count.neg += 1; return count }

        const logic = {
            tooFar: (d:number) => Math.abs(d) > 3,
            duplicate: (d: number) => d === 0,
        }
        const rules = [
            // distance
            (l: number[]) => l.filter(logic.tooFar).length,
            // repeated
            (l: number[]) => l.filter(logic.duplicate).length,
            // direction
            (l: number[]) => {
                const signs = l.map(d => getSign(d)).reduce(reduceSigns, {pos: 0, neg: 0})
                return Math.min(...Object.values(signs))
            }
        ]

        const checks = rules.map(fn => fn(distances))
        if (checks.reduce((acc, d) => acc + d, 0) === 0){
            safety[i] = Safety.Safe
            return
        }
        if(checks[2] > 1) {
            safety[i] = Safety.Unsafe
            return
        }
        let fixCount = 0
        for(const fn of Object.values(logic)) {
            const problem = distances.findIndex(fn)
            if(problem >= 0){
                const retry = levels.toSpliced(problem + 1, 1) // problem is the idx of the distance between levels.
                const reDistance: number[] = retry.reduce(asDistance, [])
                const stillProblem = reDistance.findIndex(fn)
                if (stillProblem >= 0) {
                    safety[i] = Safety.Unsafe
                    return
                }
                fixCount += 1
            }
        }
        if(fixCount > 1) {
            safety[i] = Safety.Unsafe
            return
        }
        // rise/falling
        const signs = distances.map(d => getSign(d)).reduce(reduceSigns, {pos: 0, neg: 0})
        const rising = (d: number) => getSign(d) === 'pos'
        const falling = (d: number) => getSign(d) === 'neg'

        if(signs.pos === 1) {
            const problem = distances.findIndex(rising)
            const fixed = levels.toSpliced(problem +1 , 1)
            const redistance = fixed.reduce(asDistance, [])
            const signs = redistance.map(d => getSign(d)).reduce(reduceSigns, {pos: 0, neg: 0})
            if(signs.pos > 0) {
                safety[i] = Safety.Unsafe
            }
            fixCount += 1
        }

        if(signs.neg === 1) {
            const problem = distances.findIndex(falling)
            const fixed = levels.toSpliced(problem +1 , 1)
            const redistance = fixed.reduce(asDistance, [])
            const signs = redistance.map(d => getSign(d)).reduce(reduceSigns, {pos: 0, neg: 0})
            if(signs.neg > 0) {
                safety[i] = Safety.Unsafe
            }
            fixCount += 1
        }
        if(fixCount > 1) {
            safety[i] = Safety.Unsafe
            return
        }

        safety[i] = Safety.Safe
    
        console.log(`${i + 1}   ${safety[i]}   ${checks.join('_')}   ${distances.join(' ')}   ${levels.join(' ')}`)
    })

    // count safety.
    const safe = safety.filter(s => s === Safety.Safe).length
    return safe
}

// 665 too high

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
    // const ans  = Part2("./example.txt")
    const ans  = Part2("./input.txt")
    console.log(`Day 2 Part 2 ${ans}`) // 551 incorrect
    assert(ans !== 535)
    assert(ans !== 551)
    return ans
}

Deno.test('Day 2 part 2', () => {
    const ans = Part2('./example.txt')
    assertEquals(ans, 4)
})

part2()

