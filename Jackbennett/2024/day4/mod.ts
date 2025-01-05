import { assertEquals } from "jsr:@std/assert/equals";

const parse = (f: string) => {
    return Deno.readTextFileSync(f).split('\n')
}

const sumFn = (acc: number, val: number, _idx: number, _acc: number[]) => acc + val 

const example = (d: ReturnType<typeof parse>) => {
    // rows
    const rows = d.map(r => countPattern(r)).reduce(sumFn)
    // columns
    let columns = 0
    for (let i = 0; i < d[0].length; i += 1){
        columns += countPattern(d.map(d => d[i]).join(''))
    }
    // diagonals
    let diagonals = 0
    for (let offset=0;  offset < d.length; offset += 1){
        {
            const line: string[] = []
            // todo move the diagonals agross to make lines to match on.
            for (let i = 0; i < d[0].length - offset; i += 1){
                line.push(d[i][i + offset])
            }
            if(line.length < 3) continue
            diagonals += countPattern(line.join(''))
        }
        if(offset > 0){ // skips above 0,0 diagonal
            const line: string[] = []
            // todo move the diagonals agross to make lines to match on.
            for (let i = 0; i < d[0].length - offset; i += 1){
                line.push(d[i][i - offset])
            }
            if(line.length < 3) continue
            diagonals += countPattern(line.join(''))
        }
        {
            const line: string[] = []
            // todo move the diagonals agross to make lines to match on.
            for (let i = 0; i < d[0].length - offset; i += 1){
                const rtl = (d[0].length - 1) - i + offset
                line.push(d[i][rtl])
            }
            if(line.length < 3) continue
            diagonals += countPattern(line.join(''))
        }
        if(offset > 0){ // skips above 0,0 diagonal
            const line: string[] = []
            // todo move the diagonals agross to make lines to match on.
            for (let i = 0; i < d[0].length - offset; i += 1){
                const rtl = (d[0].length - 1) - i - offset
                line.push(d[i][rtl])
            }
            if(line.length < 3) continue
            diagonals += countPattern(line.join(''))
        }

    }

    return [rows, columns, diagonals].reduce(sumFn)
}

const countPattern = (input: string) => {
    const pattern = /(?=XMAS|SAMX)/g
    const found = [...input.matchAll(pattern)]
    return found.length
}

Deno.test('example', () => {
    assertEquals(example(parse('./example.txt')), 18)
})


Deno.test('Day 4 part 1', () => {
    assertEquals(example(parse('./input.txt')), 18)
})
