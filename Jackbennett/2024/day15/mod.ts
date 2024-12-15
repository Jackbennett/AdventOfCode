import { assertEquals } from "jsr:@std/assert";
import { Coordinate, Robot,sum } from "../util.ts";

const example = `########
#..O.O.#
##@.O..#
#...O..#
#.#.O..#
#...O..#
#......#
########

<^^>>>vv<v>>v<<`


// grab matching groups in order
// get start point
// remove spaces behind robot in group dircetion
// stopp at walls, ignore rest of group

class Tile {
    p: Coordinate
    constructor(x: number, y: number) {
        this.p = new Coordinate(x,y)
    }
}

class Box extends Tile {}
class Wall extends Tile {}
class Space extends Tile {}

type Direction = "v" | "<" | ">" | "^"

class WarehouseRobot extends Robot {
    directions = {
        '<': () => this.position.add({'x': -1 }),
        '>': () => this.position.add({'x': 1 }),
        '^': () => this.position.add({'y': 1 }),
        'v': () => this.position.add({'y': -1 }),
    }
    op(char: Direction) {
        return this.directions[char]()
    }
}

function factory (char: string, x: number, y: number){
    switch (char) {
        case 'O': return new Box(x,y)
        case '#': return new Wall(x,y)
        case '.': return new Space(x,y)
        case '@': return new WarehouseRobot(new Coordinate(x,y), new Coordinate(1,1), 1)
        
        default:
            break;
    }
}

const parse = (f: string) => {
    const [warehouse, moves] = f.split(/\n\n/gm)

    const grid_items = warehouse.split('\n')
        .map((line, y) => ({ line: Array.from(line), y }))
        .flatMap((row) => {
            return row.line.map((char, x) => factory(char, x, row.y))
        })
        

    return {
        moves: Array.from(moves.replace(/\n/gm, '')) as Direction[],
        robot: grid_items.find(i => i instanceof WarehouseRobot)!,
        walls: grid_items.filter(i => i instanceof Wall),
        boxes: grid_items.filter(i => i instanceof Box),
        spaces: grid_items.filter(i => i instanceof Space),
    }
}

type Landscape = (Wall | Box | Space)[]

class Grid {
    layout: Landscape
    constructor(public robot: WarehouseRobot, public state: Landscape ) {
        this.layout = state
    }
    look(d: Direction) {
        const dir = {
            '<' : () => this.layout.filter(i => i.p.y === this.robot.position.y).filter(i => i.p.x < this.robot.position.x).toSorted((a,b) => b.p.x - a.p.x),
            '>': () => this.layout.filter(i => i.p.y === this.robot.position.y).filter(i => i.p.x > this.robot.position.x).toSorted((a,b) => a.p.x - b.p.x),
            '^': () => this.layout.filter(i => i.p.x === this.robot.position.x).filter(i => i.p.y < this.robot.position.y).toSorted((a,b) => b.p.y - a.p.y),
            'v': () => this.layout.filter(i => i.p.x === this.robot.position.x).filter(i => i.p.y > this.robot.position.y).toSorted((a,b) => a.p.y - b.p.y),
        }
        if(!['<','>','^','v'].includes(d)){
            console.log(d)
        }
        const items = dir[d]()
        const space = items.filter(i => i instanceof Space)
        if(space.length === 0) return false
        return items
    }
    move(path: Landscape, _spaces: number){

        let gap = path.findIndex(c => c instanceof Space)! // TS this fn never called without spaces.
        if(path.slice(0, gap).some(i => i instanceof Wall)) return
        const tmp_p = this.robot.position
        const toMove = this.layout.findIndex(c => c.p.is(path[gap].p))

        let remember_space = this.layout[toMove].p
        this.layout[toMove].p = tmp_p

        while(gap > 0) {
            gap -= 1
            const toMove = this.layout.findIndex(c => c.p.is(path[gap].p))
            const next_time = this.layout[toMove].p
            this.layout[toMove].p = remember_space
            remember_space = next_time
        }

        this.robot.position = remember_space

    }
}

const part1 = ({moves, robot, ...state}: ReturnType<typeof parse>) => {
    const grid = new Grid(robot, Object.values(state).flatMap(i => i))

    moves.forEach(m => {
        const view = grid.look(m)
        if(view) {
            grid.move(view, 1)
        }
    })

    const scores = grid.layout.filter(i => i instanceof Box).map(b => 100* b.p.y + b.p.x)
    return scores.reduce(sum) 
}

Deno.test('day 15 small example', () => {
    const small = part1(parse(example))
    assertEquals(small, 2028)
})

Deno.test('day 15 part 1',  () => {
    const answer = part1(parse(Deno.readTextFileSync('./input.txt')))
    assertEquals(answer, 1371036)
})

const answer = part1(parse(Deno.readTextFileSync('./input.txt')))

console.log(answer)