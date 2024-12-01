
import { assert, assertEquals } from "jsr:@std/assert";


const parse = async (path: string) => {
    const f = (await Deno.readTextFile(path)).split('\n')
    const id = new Array(f.length)
    const dist = new Array(f.length)
    for (const [idx, line] of f.entries()) {
        const [a, b] = line.split(/\s+/)
        id[idx] = parseInt(a, 10)
        dist[idx] = parseInt(b, 10)
    }
    return [id,dist]
}

const distance = (a: number, b: number) => Math.abs(b - a)
Deno.test('distance', () => {
    assertEquals(distance(1, 3), 2)
    assertEquals(distance(2, 3), 1)
    assertEquals(distance(3, 3), 0)
    assertEquals(distance(3, 4), 1)
    assertEquals(distance(3, 5), 2)
    assertEquals(distance(9, 4), 5)
})

Deno.test('answer', () => {
    // parse example
    // sort lists A and B smallest first (a==locationID)
    // get distances
    // sum distance == answer

})

Deno.test('example', async () => {
    const [ a, b ] = await parse('./example.txt')
    assert(Array.isArray(a))
    assert(Array.isArray(b))
    a.sort()
    b.sort()
    const r = a.map( (n, i) => distance(n, b[i]) )
    const sum = r.reduce((acc, val) => acc + val, 0)
    assertEquals(sum, 11)
})

export async function day1a() {
    const [ a, b ] = await parse('./input.txt')
    a.sort()
    b.sort()
    const r = a.map( (n, i) => distance(n, b[i]) )
    return r.reduce((acc, val) => acc + val, 0)
}

Deno.test('day 1 answer', async () => {
    const answer = await day1a()
    assertEquals(answer, 2904518)
})

console.log(await day1a()) // 

export async function day1b() {
    const [ a, b ] = await parse('./input.txt')

    const map = b.reduce((acc: { [index: number]: number }, val) => {
        acc[val] = Object.hasOwn(acc, val) ? acc[val] + 1 : 1
        return acc
    }, {})

    const dist = a.filter(val => Object.hasOwn(b, val)).map((val) => val * map[val] )
    const ans = dist.reduce((acc, val) => acc + val, 0)
    console.log(ans)
}

await day1b()
