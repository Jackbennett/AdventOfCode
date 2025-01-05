import { assertGreater, assertLess } from "jsr:@std/assert";

const example = `kh-tc
qp-kh
de-cg
ka-co
yn-aq
qp-ub
cg-tb
vc-aq
tb-ka
wh-tc
yn-cg
kh-ub
ta-co
de-co
tc-td
tb-wq
wh-td
ta-ka
td-qp
aq-cg
wq-ub
ub-vc
de-ta
wq-aq
wq-vc
wh-yn
ka-de
kh-ta
co-tc
wh-qp
tb-vc
td-yn`

const parse = (f:string) => {
    const ln = f.split('\n')

    const nodes = ln.reduce((all, route) => {
        const [a, b] = route.split('-')
        
        all.add(a)
        all.add(b)

        return all
    }, new Set<string>())

    const edges = ln.map(s => s.split('-'))

    return {
        nodes, edges
    }
}


Deno.test('day 23 example', () => {
    const d = parse(example)

    const t = [...d.nodes].filter(n => n.startsWith('t'))

    const interestedRotues = t.flatMap(pc => d.edges.filter(r => r.includes(pc)))

    const conn  = new Map<string, string[]>()
    t.forEach(pc =>{
        const map = d.edges.filter(route => route.includes(pc)).map(route => {
            const end = route.find(r => r != pc)!
            const peers = d.edges.filter(route => route.includes(end)).map(other => {
                return other.find(n => n !== end)
            })
        })
        conn.set(pc, map)
    })

    const tripled = interestedRotues.reduce((_a, route) => {
        const [from,to] = route
        const allFrom = d.edges.filter(e => e.includes(from))
        const allTo   = d.edges.filter(e => e.includes(to  ))
        return route
    })

    console.log(`Day 23 example ${1}`)

})

// Deno.test('day 23 Part 1', () => {
//     const d = graph(Deno.readTextFileSync('./input.txt'))

//     const ffirst = d.filter(n => n.name.startsWith('t')).flatMap(n => n.getPeer())
//         .reduce<Set<Node>[]>((uniq, peers) => {
//             if(uniq.every( set => !set.isSubsetOf(peers) )) {
//                 uniq.push(peers);
//             }
//             return uniq}, []
//         )
//     const all = d.flatMap(n => n.getPeer())
//         .reduce<Set<Node>[]>((uniq, peers) => {
//             if(uniq.every( set => !set.isSubsetOf(peers) )) {
//                 uniq.push(peers);
//             }
//             return uniq}, []
//         )

//     const tafter = all.filter(s => [...s].some(n => n.name.startsWith('t')))

//     const inspect = new Set(tafter).difference(new Set(ffirst))
//     const withT = ffirst
//     console.log(`Day 23 part 1 ${withT.length}`)
//     assertGreater(withT.length, 453)
//     assertLess(withT.length, 1356)
//     assertLess(withT.length, 1359)
// })