import { assertEquals, assertGreater } from "jsr:@std/assert";
import { Coordinate } from "../util.ts"
import { AStarFinder } from 'npm:astar-typescript';

const example = `###############
#...#...#.....#
#.#.#.#.#.###.#
#S#...#.#.#...#
#######.#.#.###
#######.#.#...#
#######.#.###.#
###..E#...#...#
###.#######.###
#...###...#...#
#.#####.#.###.#
#.#...#.#.#...#
#.#.#.#.#.#.###
#...#...#...###
###############`

class Wall extends Coordinate { static sym = '#'}
class Space extends Coordinate { static sym = '.'}
class Start extends Coordinate { static sym = 'S'}
class End extends Coordinate { static sym = 'E'}


class Grid {
    readonly layout: Coordinate[]
    pov = new Coordinate(0,0)
    constructor(public state: Coordinate[], public size: Coordinate) {
        this.layout = state
    }
    get start(): Start{
        return this.layout.find(i => i instanceof Start) || (() => {throw new Error('No start point')})()
    }
    get end(): End{
        return this.layout.find(i => i instanceof End) || (() => {throw new Error('No end point')})()
    }
    look(as: Coordinate, from: Coordinate, distance = 1) {
        return [
            as.add({x: distance}),
            as.add({x: -distance}),
            as.add({y: distance}),
            as.add({y: -distance}),          
        ].filter(p => !p.is(from))
    }
    matrix(without?: Coordinate) {
        const arr: number[][] = Array.from( Array(this.size.y), () =>  Array.from(Array(this.size.x), () => 0))
        const some = this.layout.filter(i => i instanceof Wall)
        
        some.forEach(i => arr[i.y][i.x] = 1)

        if(without) {
            arr[without.y][without.y] = 0
        }

        return arr
    }
    draw() {
        const rows = Math.max(...this.layout.map(i => i.y))
        const cols = Math.max(...this.layout.map(i => i.x))
        const arr: string[][] = Array.from( Array(rows + 1), () =>  Array.from(Array(cols +1), () => '.'))
        
        // @ts-ignore
        this.layout.forEach(i => arr[i.y][i.x] = Object.hasOwn(i, 'sym') ? i.sym : '.')
        return arr
    }
    paint(map: ReturnType<typeof this.draw>) {
        console.log(map.map(i => i.join('')).join('\n'))
    }

}



const parse = (f: string): [Coordinate[], Coordinate] => {
    const blocks = {
        [Wall.sym]: Wall,
        [Space.sym]: Space,
        [Start.sym]: Start,
        [End.sym]: End
    }
    const lines = f.split('\n')
    const size = new Coordinate(
        lines[0].length,
        lines.length
    )
    const layout =  lines
        .flatMap((ln, y) => ln.split('').map((char, x ) => new blocks[char](x, y)))
    return [layout, size]
} 

const part1 = ([layout, size]: ReturnType<typeof parse>) => {
    const map = new Grid(layout, size)

    const algo = new AStarFinder({
        grid: {
            matrix: map.matrix()
        },
        diagonalAllowed: false,
        includeEndNode: true,
        includeStartNode: true
    })

    const baseline = algo.findPath(map.start, map.end)

    let underLimit = 0

    // remove perimiter we can't stepping through anyway
    const innerWalls = map.layout.filter(i => i instanceof Wall)
        .filter(w => w.x !== 0)
        .filter(w => w.y !== 0)
        .filter(w => w.x !== map.size.x -1)
        .filter(w => w.y !== map.size.y -1)

    const routes = innerWalls.forEach(wall => {
        const toggle = algo.getGrid().getNodeAt(wall)
        toggle.setIsWalkable(true)
        const path = algo.findPath(map.start, map.end)
        toggle.setIsWalkable(false)

        if(path.length < (baseline.length - 99)) {
            underLimit += 1
        }
        return {time: path.length, wall}
        // return {path, wall}
    })

    return {
        routes,
        baseline,
        underLimit
    }
}


// Deno.test('Day 20 example', () =>{
//     const input = parse(example)

//     const {routes, baseline} = part1(input)

//     const shorter = routes.filter(r => r.path.length < (baseline.length))

//     const exampleCheck = shorter.reduce((acc, val) => {
//         acc.set(baseline.length - val.path.length,  (acc.get(baseline.length - val.path.length) || 0) + 1)
//         return acc
//     }, new Map())
    
//     console.log(exampleCheck)
// })


Deno.test('Day 20 part 1', () =>{
    const input = parse(Deno.readTextFileSync('./input.txt'))

    const {underLimit} = part1(input)

    assertGreater(underLimit, 1478) // < 100 rule missed equality
    assertEquals(underLimit, 1502)
    console.log(underLimit)
})

