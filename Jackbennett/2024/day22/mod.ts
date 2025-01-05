import { assertEquals } from "jsr:@std/assert";
import { sum } from "../util.ts";

class PuchaseNumber {
    iter = 0
    value: bigint
    constructor( public iv: number) {
        this.value = BigInt(iv)
    }

    #mix(n: bigint) {
        this.value = n ^ this.value
    }
    #prune() {
        this.value = this.value % this.#const[16777216]
    }

    #const = {
        64: BigInt(64),
        32: BigInt(32),
        2048: BigInt(2048),
        16777216: BigInt(16777216)
    }
    rounds(count = 1) {
        for (let iter = 0; iter < count; iter++) {
            this.#mix(this.value * this.#const[64])
            this.#prune()
            this.#mix(this.value / this.#const[32])
            this.#prune()
            this.#mix(this.value * this.#const[2048])
            this.#prune()
            this.iter += 1
        }
    }
}

Deno.test('day 22 example', () => {
    const start = new PuchaseNumber(123)
    const check = [15887950,
        16495136,
        527345,
        704524,
        1553684,
        12683156,
        11100544,
        12249484,
        7753432,
        5908254,
    ].map(d => BigInt(d))
    const test: bigint[] = []
    for (let index = 1; index < 11; index++) {
        start.rounds(1)
        test.push(start.value)
        console.log(start.value)
    }
    assertEquals(test, check)
})

Deno.test('day 22 longer example', () => {
    const test = [
        1,10,100,2024
    ].map(t => new PuchaseNumber(t))

    test.forEach(pn => pn.rounds(2000))

    test.forEach(pn => console.log(`${pn.iv}: ${pn.value}`))

    const total = test.map(pn => parseInt(pn.value.toString(), 10)).reduce(sum)
    assertEquals(total, 37327623)
})

Deno.test('day 22 part 1', () => {
    const input = Deno.readTextFileSync('./input.txt')
        .split('\n')
        .map(ln => parseInt(ln, 10))
        .map(n => new PuchaseNumber(n))

    input.forEach(pn => pn.rounds(2000))

    const ans = input.reduce((acc, n) => acc += n.value, BigInt(0))
    console.log(ans)
    assertEquals(ans, 14476723788n)
})