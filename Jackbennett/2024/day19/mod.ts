import { assertEquals, assertGreater } from "jsr:@std/assert";


const example = `r, wr, b, g, bwu, rb, gb, br

brwrr
bggr
gbbr
rrbgbr
ubwu
bwurrg
brgr
bbrgwb`

// const parse = (f: string) => {
//     const [options, requests] = f.split(/\n\n/)
//     const towels = new RegExp(options.split(', ').toSorted((a,b) => b.length - a.length).join('|'), 'g')
//     const plans = requests.split('\n')
//     return {towels, plans}
// }

const parse = (f: string) => {
    const [options, requests] = f.split(/\n\n/)
    // const towels = new RegExp(options.split(', ').toSorted((a,b) => b.length - a.length).join('|'), 'g')

    const groups = options.split(', ').reduce((acc, test) => {
        const t = acc.get(test.length)
        Array.isArray(t) ? t.push(test) : acc.set(test.length, [test])
        return acc
    }, new Map<number, string[]>())
    
    const towels: RegExp[] = []
    groups.forEach( (v) => {
        towels.push(new RegExp(v.join('|'), 'g'))
    })


    const plans = requests.split('\n')
    return {towels, plans}
}

const coverage = (range: string[], spans: {length: number, idx: number, ptrn: string}[]): boolean => {
    const accessed = Array.from(new Array(range.length), () => 0)
    const c = new Proxy(range, {
        get(target, p, _receiver) {
            if(typeof p === 'string'){
                const i = parseInt(p, 10)
                if(target.at(i)){
                    accessed[i] += 1
                }
            }
        }
    })
    spans.forEach(s => {
        for (let index = s.idx; index < s.idx + s.length; index++) {
            c[index];
            
        }
    })
    const test = accessed.every(i => i > 0)
    return test
}

const part1 = (inv: ReturnType<typeof parse>) => {
    let possible = 0
    const impossible = new Map<string, RegExpExecArray[]>
    for(const plan of inv.plans) {
        const test = inv.towels.flatMap( r => [...plan.matchAll(r)] )
        // const test = inv.towels.exec(plan)
        const forCoverage = test.map((t) => ({length: t[0].length, idx: t.index, ptrn: t[0]}))
        if(coverage(plan.split(''), forCoverage)) {
                possible += 1
                // console.log(`Possible: ${found}`)
            } else {
            impossible.set(plan, test)
            console.log(`${plan} not possible`)

        }
    }
    console.log(`${possible} / ${inv.plans.length} are possible.`)
    return possible
}

Deno.test('Day 19 example', () => {
    const inv = parse(example)

    const ans = part1(inv)
    assertEquals(ans, 5)
})

Deno.test('Day 19 part1', () => {
    const inv = parse(Deno.readTextFileSync('./input.txt'))

    const ans = part1(inv)
    assertGreater(ans, 331)
    assertGreater(ans, 338)
    assertGreater(ans, 340)
    // assertEquals(ans, 5)
})