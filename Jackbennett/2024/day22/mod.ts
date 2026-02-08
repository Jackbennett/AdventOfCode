import { assertEquals } from "jsr:@std/assert";
import { sum } from "../util.ts";
import { LimitedTransformStream } from "https://deno.land/std@0.224.0/streams/mod.ts";
import { assertFp } from "jsr:@std/internal@^1.0.5/diff";

class PuchaseNumber {
    private _iter = 0;
    public get iter() {
      return this._iter;
    }
    public set iter(value) {
      this._iter = value;
    }
    value: bigint
    constructor( public iv: number) {
        this.value = BigInt(iv)
    }

    #mix(n: bigint) {
        this.value = n ^ this.value
    }
    #prune() {
        this.value = this.value % PuchaseNumber.#const[16777216]
    }

    static #const = {
        64: BigInt(64),
        32: BigInt(32),
        2048: BigInt(2048),
        16777216: BigInt(16777216)
    }
    rounds(count = 1) {
        for (let iter = 0; iter < count; iter++) {
            this.#mix(this.value * PuchaseNumber.#const[64])
            this.#prune()
            this.#mix(this.value / PuchaseNumber.#const[32])
            this.#prune()
            this.#mix(this.value * PuchaseNumber.#const[2048])
            this.#prune()
            this.iter += 1
        }
    }
}

type quad = [number, number, number, number]

interface BuySelector{
    seq: quad,
    value: number,
}

class BanannaPrice extends PuchaseNumber {
    history: [number,number][] = []
    constructor(props: PuchaseNumber['iv']) {
        super(props)
        this.history.push([this.getPrice(this.value), 0])
    }
    getPrice(v: bigint | number) {
        return parseInt(v.toString().at(-1) || '0', 10)
    }
    override set iter(_n: number){
        super.iter += 1
        const last = this.history.at(-1)![0]
        const now = this.getPrice(this.value)
        this.history.push([now, now - last])
    }
    sequenceOf(pattern: [number,number,number,number]){
        // TODO
    }
    *window(size = 4) {
        let i = 0
        while(i <= this.history.length - size) {
            const w = this.history.slice(i, i + size)
            if(w[size-1][0] > 0) {
                yield {
                    seq: w.map(iW=> iW[1]) as quad,
                    price: w[size-1][0]
                }
            }
            i += 1
        }

        // const windowed = Array.from(
        //     this.history,
        //     () => 
        // )

        // /// unique possible quads.
        // return this.history
        //     .filter((_, idx, arry) => idx < (arry.length - size))
        //     .map((entry, idx, arry) => {
        //         return [
        //             entry[1],
        //             arry[idx + 1][1],
        //             arry[idx + 2][1],
        //             arry[idx + 3][1],
        //         ] as quad
        //     }).reduce<BuySelector[]>((acc, val, _i, all) =>{

        //         acc.push({
        //             seq: val,
        //             occurances: 1,
        //             value: all[val[3]]
        //         })

        //         return acc
        //     }
        //     , [])
    }
}


// Deno.test('day 22 example', () => {
//     const start = new PuchaseNumber(123)
//     const check = [15887950,
//         16495136,
//         527345,
//         704524,
//         1553684,
//         12683156,
//         11100544,
//         12249484,
//         7753432,
//         5908254,
//     ].map(d => BigInt(d))
//     const test: bigint[] = []
//     for (let index = 1; index < 11; index++) {
//         start.rounds(1)
//         test.push(start.value)
//         console.log(start.value)
//     }
//     assertEquals(test, check)
// })

// Deno.test('day 22 longer example', () => {
//     const test = [
//         1,10,100,2024
//     ].map(t => new PuchaseNumber(t))

//     test.forEach(pn => pn.rounds(2000))

//     test.forEach(pn => console.log(`${pn.iv}: ${pn.value}`))

//     const total = test.map(pn => parseInt(pn.value.toString(), 10)).reduce(sum)
//     assertEquals(total, 37327623)
// })

const parse = (f:string) => {
    return Deno.readTextFileSync(f)
    .split('\n')
    .map(ln => parseInt(ln, 10))
}

// Deno.test('day 22 part 1', () => {
//     const input = parse('./input.txt')
//         .map(n => new PuchaseNumber(n))

//     input.forEach(pn => pn.rounds(2000))

//     const ans = input.reduce((acc, n) => acc += n.value, BigInt(0))
//     console.log(ans)
//     assertEquals(ans, 14476723788n)
// })

class Stat {
    static PatternList = new Map<string, Stat>()
    count: number
    constructor(public pattern: quad, public price: number  ) {
        this.count = 1
        const exists = Stat.PatternList.get(pattern.toString()) 
        if(exists) {
            exists.count += 1
            return exists
        }
        Stat.PatternList.set(pattern.toString(), this)
    }
    value() {
        return this.count * this.price
    }
    matched() {
        this.count += 1
    }
}

Deno.test('Day 22 part 2', () => {
    // const input = parse('./input.txt')
    const input = [1,
        2,
        3,
        2024]
    .map(n => new BanannaPrice(n))

    // get all 2000 numbers with their price & difference.
    input.forEach(n => n.rounds(2000))
    // get each price differece per round.
    // find the most common sequence of 4 differences.
    const windows = input.map(i => [...i.window()].map((w) => new Stat(w.seq, w.price)))

    const common = windows.filter(s => s.count > 1).sort((a,b) => b.count - a.count)
    
    // .reduce((acc, buyList) => {
    //     const common = new Map()
    //     const lst = [...buyList]
    //     let upper = 0
    //     for(const opt of buyList) {
    //         if(upper > Math.max(...common.values())) {
    //             common.set(opt.seq, opt.price)
    //             upper = opt.price
    //         }
    //     }
    //     // val.forEach((q) => {
    //     //     const key = q.toString()
    //     //     const count =  acc.get(key)
    //     //     count ? acc.set(key, count + 1) : acc.set(key, 1)
    //     // })
    //     return acc
    // }, new Map<string, number>())
    debugger
    // get the price of the 4th item
    // sum 

    // check if there's another 4-len sequences per buyer that'd net higher prices if not more buyers.
})


// .reduce<BuySelector[]>((acc, val, _i, all) =>{
//         acc.push({
//             seq: val,
//             occurances: 1,
//             value: all[val[3]]
//         })

//         return acc
//     }
//     , [])