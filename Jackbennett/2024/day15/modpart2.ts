import { assertEquals } from "jsr:@std/assert";
import { Coordinate, Robot,sum } from "../util.ts";

const example = `##########
#..O..O.O#
#......O.#
#.OO..O.O#
#..O@..O.#
#O#..O...#
#O..O..O.#
#.OO.O.OO#
#....O...#
##########

<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^
vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v
><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<
<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^
^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><
^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^
>^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^
<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>
^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>
v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^`


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

class BoxL extends Tile {
    sym = '['
    sister() {
        return new Coordinate(this.p.x + 1, this.p.y)
    }
}
class BoxR extends Tile {
    sym = ']'
    sister(){
        return new Coordinate(this.p.x - 1, this.p.y)
    }
}
class Wall extends Tile {
    sym = '#'
}
class Space extends Tile {
    sym = '.'
}

type Direction = "v" | "<" | ">" | "^"

class WarehouseRobot extends Robot {
    sym = '@'
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
        case '[': return new BoxL(x,y)
        case ']': return new BoxR(x,y)
        case '#': return new Wall(x,y)
        case '.': return new Space(x,y)
        case '@': return new WarehouseRobot(new Coordinate(x,y), new Coordinate(1,1), 1)
        
        default:
            break;
    }
}

const parse = (f: string) => {
    const [warehouse, moves] = f.split(/\n\n/gm)

    const expanded = warehouse
    .replaceAll('.', '..')
    .replaceAll('#', '##')
    .replaceAll('O', '[]')
    .replaceAll('@', '@.')

    const grid_items = expanded
        .split('\n')
        .map((line, y) => ({ line: Array.from(line), y }))
        .flatMap((row) => {
            return row.line.map((char, x) => factory(char, x, row.y))
        })
        

    return {
        moves: Array.from(moves.replace(/\n/gm, '')) as Direction[],
        robot: grid_items.find(i => i instanceof WarehouseRobot)!,
        walls: grid_items.filter(i => i instanceof Wall),
        boxes: grid_items.filter(i => i instanceof BoxL || i instanceof BoxR),
        spaces: grid_items.filter(i => i instanceof Space),
    }
}

type Landscape = (Wall | BoxL | BoxR | Space)[]

class Grid {
    layout: Landscape
    constructor(public robot: WarehouseRobot, public state: Landscape ) {
        this.layout = state
    }
    look(d: Direction, as: Coordinate) {
        const dir = {
            '<' : () => this.layout.filter(i => i.p.y === as.y).filter(i => i.p.x < as.x).toSorted((a,b) => b.p.x - a.p.x),
            '>': () => this.layout.filter(i => i.p.y === as.y).filter(i => i.p.x > as.x).toSorted((a,b) => a.p.x - b.p.x),
            '^': () => this.layout.filter(i => i.p.x === as.x).filter(i => i.p.y < as.y).toSorted((a,b) => b.p.y - a.p.y),
            'v': () => this.layout.filter(i => i.p.x === as.x).filter(i => i.p.y > as.y).toSorted((a,b) => a.p.y - b.p.y),
        }
        if(!['<','>','^','v'].includes(d)){
            console.log(`parse error ${d}`)
        }
        const items = dir[d]()
        const space = items.filter(i => i instanceof Space)
        if(space.length === 0) return false
        return items
    }
    move(path: Landscape, as: Coordinate){

        let gap = path.findIndex(c => c instanceof Space)! // TS this fn never called without spaces.
        if(path.slice(0, gap).some(i => i instanceof Wall)) return
        const tmp_p = as
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

        as = remember_space
    }
    moveY(path: Landscape, as: Coordinate) {
        // look as all connected boxes,
        // get those spaces.
        // stop if any have none.
        let gap = path.findIndex(c => c instanceof Space)! // TS this fn never called without spaces.
        if(path.slice(0, gap).some(i => i instanceof Wall)) return
    }
    draw() {
        const arr: string[][] = [[]]
        this.layout.forEach(i => Array.isArray(arr[i.p.y]) ? arr[i.p.y][i.p.x] = i.sym : arr[i.p.y] = [i.sym])
        arr[this.robot.position.y][this.robot.position.x] = this.robot.sym
        return arr.map(y => y.join('')).join('\n')
    }
}

const part2 = ({moves, robot, ...state}: ReturnType<typeof parse>) => {
    const grid = new Grid(robot, Object.values(state).flatMap(i => i))

    moves.forEach(m => {
        if(['<','>'].includes(m)){
            const view = grid.look(m, grid.robot.position)
            if(view) grid.move(view, grid.robot.position)
        } else if(['^','v'].includes(m)) {
            const view = grid.look(m, grid.robot.position)
            if(view) {
                if(view[0] instanceof Space) return grid.move(view, grid.robot.position)

                // deal with the boxes....
                console.log(`${' '.repeat(grid.robot.position.x)}${m}\n${grid.draw()}`)
                debugger

                const boxView = view.filter(i => i instanceof BoxL || i instanceof BoxR).map(i => grid.look(m, i.sister()))
                // @ts-ignore: ts can't handle already checking every array for truthy and handing spaces above.
                if(boxView.every(i => i)) boxView.forEach(v => grid.move(v, v[0].sister()))
                console.log(`${' '.repeat(grid.robot.position.x)}${m}\n${grid.draw()}`)
                debugger
            }
        } else {
            throw new Error(`unknown move ${m}`)
        }
    })

    const scores = grid.layout.filter(i => i instanceof BoxL).map(b => 100* b.p.y + b.p.x)
    return scores.reduce(sum) 
}

Deno.test('day 15 larger example', () => {
    const larger = part2(parse(example))
    assertEquals(larger, 9021)
})

// Deno.test('day 15 part 2',  () => {
//     const answer = part2(parse(Deno.readTextFileSync('./input.txt')))
//     // assertEquals(answer, 2028)
// })

// const answer = part2(parse(Deno.readTextFileSync('./input.txt')))

// console.log(answer)