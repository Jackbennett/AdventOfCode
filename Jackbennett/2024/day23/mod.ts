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

    return ln.map(s => {
        const [a, b] = s.split('-')
        return {
            edge: s,
            nodes: [a,b]
        }
    })
}

type NodeName = string

class Node {
    edge: Set<Node>  = new Set()
    #nextHop: Set<Node> = new Set()
    private static singletons = new Map<NodeName, Node>()
    get [Symbol.toStringTag]() {
        return this.name
    }
    constructor(public name: NodeName) {
        if (Node.singletons.has(name)) {
            return Node.singletons.get(name)!
        }
        Node.singletons.set(name, this)
    }

    addPeer(n: Node) {
        this.edge.add(n)
        const opposite = Node.singletons.get(n.name)
        opposite?.edge.add(this)
    }

    getPeer(): Set<Node>[] {
        const triplets: Set<Node>[] = []
        this.edge.forEach(e => {
            const score = e.edge.intersection(this.edge)
            for(const n of score) {
                if (n === this) continue
                const t = new Set([this, e, n])
                if(triplets.every( set => !set.isSubsetOf(t))) {
                    triplets.push(t)
                }
            }
        })
        return triplets
    }
    nextHop() {
        const aftePeer = new Set()
        this.edge.forEach(e =>{
            e.edge.forEach(n => {
                if (n === this) return // remove loops
                aftePeer.add(n)
            })
        })
        return aftePeer
    }
}

// class Triple {
//     edge: Set<Triple>
//     private static singletons = new Map<Triple, Triple>()
//     constructor(public a: Node, public b: Node, public c: Node) {
//         this.edge = new Set([a,b,c])
//         if (Triple.singletons.has(edge)) {
//             return Triple.singletons.get(edge)!
//         }
//         Triple.singletons.set(this.edge, this)
//     }
// }

class Loop {
    hop: Set<Node> = new Set()
    constructor(public start: Node, public end: Node) {
        if(!start.edge.has(end)){
        }
    }

    get distance() {
        return this.hop.size
    }
}

const net = (f:string) => {
    const edges = f.split('\n')

    const expanded = edges.flatMap(s => {
        const [a, b] = s.split('-')
        const node = new Node(a)
        node.addPeer(new Node(b))
        return new Loop(new Node(a), new Node(b))
    })
     return expanded
}

const graph = (f:string) => {
    const edges = f.split('\n')

    const expanded = edges.flatMap(s => {
        const [a, b] = s.split('-')
        const node = new Node(a)
        node.addPeer(new Node(b))
        return node
    })
     return expanded
}

const peerList = (d: ReturnType<typeof parse>) => {
    return d.reduce((acc, net) => {
        for(const node of net.nodes){
            const key = acc.get(node)
            const filter = new RegExp(`-?${node}-?`)
            const peer = net.edge.replace(filter, '')
            if(key){
                key.add(peer)
            } else {
                acc.set(node, new Set([node, peer]))
            }
        }
        return acc
    }, new Map<string, Set<string>>())
}

Deno.test('day 23 example', () => {
    const d = graph(example)

    const peers = d.flatMap(n => n.getPeer())
        .reduce<Set<Node>[]>((uniq, peers) => {
            if(uniq.every( set => !set.isSubsetOf(peers) )) {
                uniq.push(peers);
            }
            return uniq}, []
        )

    const withT = peers.filter(s => s.values().some(n => n.name.startsWith('t'))).length
    console.log(`Day 23 example ${withT}`)

})

Deno.test('day 23 Part 1', () => {
    const d = graph(Deno.readTextFileSync('./input.txt'))

    const ffirst = d.filter(n => n.name.startsWith('t')).flatMap(n => n.getPeer())
        .reduce<Set<Node>[]>((uniq, peers) => {
            if(uniq.every( set => !set.isSubsetOf(peers) )) {
                uniq.push(peers);
            }
            return uniq}, []
        )
    const all = d.flatMap(n => n.getPeer())
        .reduce<Set<Node>[]>((uniq, peers) => {
            if(uniq.every( set => !set.isSubsetOf(peers) )) {
                uniq.push(peers);
            }
            return uniq}, []
        )

    const tafter = all.filter(s => [...s].some(n => n.name.startsWith('t')))

    const inspect = new Set(tafter).difference(new Set(ffirst))
    const withT = ffirst
    console.log(`Day 23 part 1 ${withT.length}`)
    assertGreater(withT.length, 453)
    assertLess(withT.length, 1356)
    assertLess(withT.length, 1359)
})