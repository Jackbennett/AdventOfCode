import { assertEquals } from "jsr:@std/assert";

const parse = (f:string) => {
    const barrelData = f.split('\n\n')

    const keys: Set<number>[] = []
    const locks: Set<number>[] = []

    const typeIDLength = 5
    const lockSize = new Set(Array.from(Array(barrelData[0].replaceAll('\n', '').length - typeIDLength*2), (_, i) => i))

    barrelData.forEach(b => {
        const barrel = b.replaceAll('\n', '').slice(typeIDLength, -typeIDLength)
        const shape = [...barrel.matchAll(/#/g).map(m => m.index)]
        if(b.startsWith('#####')) {
            locks.push(new Set(shape))
        } else {
            keys.push(new Set(shape))
        }
    })

    return {keys, locks, lockSize}
}

const example = `#####
.####
.####
.####
.#.#.
.#...
.....

#####
##.##
.#.##
...##
...#.
...#.
.....

.....
#....
#....
#...#
#.#.#
#.###
#####

.....
.....
#.#..
###..
###.#
###.#
#####

.....
.....
.....
#....
#.#..
#.#.#
#####`
const matchedExample = `#####
.####
.####
.####
.#.#.
.#...
.....

.....
.....
.....
#....
#.#..
#.#.#
#####`


Deno.test('Day 25 Part 1', () => {
    const d = parse(Deno.readTextFileSync('./input.txt'))
    // const d = parse(example)

    const count = d.locks.reduce<[Set<number>, Set<number>][]>((pair, l) => {
        d.keys.filter( k => k.isDisjointFrom(l))
            .forEach(k => {
                pair.push([l,k])
            })
        return pair
    }, [])

    console.log(`keys that match locks: ${count.length} `)

    assertEquals(count.length, 2835)
})