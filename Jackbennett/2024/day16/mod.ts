import { assertEquals } from "jsr:@std/assert";
import { Coordinate, Robot,sum } from "../util.ts";
import { AStarFinder } from 'npm:astar-typescript';

const example = `###############
#.......#....E#
#.#.###.#.###.#
#.....#.#...#.#
#.###.#####.#.#
#.#.#.......#.#
#.#.#####.###.#
#...........#.#
###.#.#####.#.#
#...#.....#.#.#
#.#.#.###.#.#.#
#.....#...#.#.#
#.###.#.#.#.#.#
#S..#.....#...#
###############`


class Wall extends Coordinate { sym = '#'}
class Space extends Coordinate { sym = '.'}
class Start extends Coordinate { sym = 'S'}
class End extends Coordinate { sym = 'E'}

type Direction = "v" | "<" | ">" | "^"

function factory (char: string, x: number, y: number){
    switch (char) {
        case '#': return new Wall(x,y)
        case '.': return new Space(x,y)
        case 'S': return new Start(x,y)
        case 'E': return new End(x,y)
    }
    throw new Error('parsing failed')
}

const parse = (f: string) => {
    const maze = f.split('\n')

    const grid_items = maze
        .map((line, y) => ({ line: Array.from(line), y }))
        .flatMap((row) => {
            return row.line.map((char, x) => factory(char, x, row.y))
        })
    
    return grid_items
}

class Grid {
    layout: Coordinate[]
    pov = new Coordinate(0,0)
    constructor(public state: Coordinate[] ) {
        this.layout = state
    }
    look(d: Direction, from: Coordinate) {
        const dir = {
            '<' : () => this.layout.filter(i => i.y === from.y).filter(i => i.x < from.x).toSorted((a,b) => b.x - a.x),
            '>': () => this.layout.filter(i => i.y === from.y).filter(i => i.x > from.x).toSorted((a,b) => a.x - b.x),
            '^': () => this.layout.filter(i => i.x === from.x).filter(i => i.y < from.y).toSorted((a,b) => b.y - a.y),
            'v': () => this.layout.filter(i => i.x === from.x).filter(i => i.y > from.y).toSorted((a,b) => a.y - b.y),
        }
        if(!['<','>','^','v'].includes(d)){
            console.log(d)
            throw new Error(`invalid direction ${d}`);
            
        }
        const items = dir[d]()
        const space = items.filter(i => i instanceof Space)
        if(space.length === 0) return false
        return items
    }
    get start(): Start{
        return this.layout.find(i => i instanceof Start) || (() => {throw new Error('No start point')})()
    }
    get end(): End{
        return this.layout.find(i => i instanceof End) || (() => {throw new Error('No end point')})()
    }
    matrix() {
        const rows = Math.max(...this.layout.map(i => i.y))
        const cols = Math.max(...this.layout.map(i => i.x))
        const arr: number[][] = Array.from( Array(rows + 1), () =>  Array.from(Array(cols +1), () => 0))
        const some = this.layout.filter(i => i instanceof Wall)
        
        some.forEach(i => arr[i.y][i.x] = 1)
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

Deno.test('example', () => {
    const d = parse(example)
    const maze = new Grid(d)

    const pathing = new AStarFinder({
        grid: {
            matrix: maze.matrix(),
        },
        diagonalAllowed: false,
        includeStartNode: false,
    })
    const route = pathing.findPath(maze.start, maze.end)

    const map = maze.draw()
    route.forEach(p => map[p[1]][p[0]] = '0')
    const score = route.reduce((acc, node, idx, arr) => {
        const turn90 = 1000
        const forward = 1
        const [x,y] = node
        if (arr.at(idx + 1)) {
            const [x1,y1] = arr[idx+1]
            /// aStar finds shorted but not least turns :/....
        }
        acc
    }, 0)
    console.log(score)
    
})