import { assertEquals } from "jsr:@std/assert";
import { Coordinate, toSplitNumber } from "../util.ts";
import { AStarFinder } from 'npm:astar-typescript';



class Corroupted extends Coordinate {}
class Start extends Coordinate {}
class End extends Coordinate {}

const example = `5,4
4,2
4,5
3,0
2,1
6,3
2,4
1,5
0,6
3,3
2,6
5,1
1,2
5,5
2,5
6,5
1,4
0,4
6,4
1,1
6,1
1,0
0,5
1,6
2,0`

class Grid {
    layout: Coordinate[]
    pov = new Coordinate(0,0)
    constructor(public state: Coordinate[] ) {
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
    matrix(upto:number) {
        const arr: number[][] = Array.from( Array(this.end.y+1), () =>  Array.from(Array(this.end.x+1), () => 0))
        const some = this.layout.filter(i => i instanceof Corroupted).slice(0, upto)
        
        some.forEach(i => arr[i.y][i.x] = 1)
        return arr
    }
}

Deno.test('day 18 example', () => {
    let end = 0
    const corouptingMemory = Array.from(example.split('\n'), ln => {
        const [x,y,_] = toSplitNumber(ln, ',')
        // get max (bottom right?)
        const biggest = Math.max(x,y)
        if(end < biggest) end = biggest
        return new Corroupted(x,y)
    })

    const grid = new Grid([new Start(0,0),  new End(end,end) ,...corouptingMemory])


    const aStarInstance = new AStarFinder({
        grid: {
          matrix: grid.matrix(12)
        },
        diagonalAllowed: false,
        includeStartNode: false,
      });
    const path = aStarInstance.findPath(grid.start, grid.end);
    console.log(path.length)
    assertEquals(path.length, 22)
})

Deno.test('day 18 part 1', () => {
    let end = 0
    const corouptingMemory = Array.from(Deno.readTextFileSync('./input.txt').split('\n'), ln => {
        const [x,y,_] = toSplitNumber(ln, ',')
        // get max (bottom right?)
        const biggest = Math.max(x,y)
        if(end < biggest) end = biggest
        return new Corroupted(x,y)
    })

    const grid = new Grid([new Start(0,0),  new End(end,end) ,...corouptingMemory])


    const aStarInstance = new AStarFinder({
        grid: {
          matrix: grid.matrix(1024)
        },
        diagonalAllowed: false,
        includeStartNode: false,
      });
    const path = aStarInstance.findPath(grid.start, grid.end);
    console.log(path.length)
})

Deno.test('day 18 part 2', () => {
    let end = 0
    const corouptingMemory = Array.from(Deno.readTextFileSync('./input.txt').split('\n'), ln => {
        const [x,y,_] = toSplitNumber(ln, ',')
        // get max (bottom right?)
        const biggest = Math.max(x,y)
        if(end < biggest) end = biggest
        return new Corroupted(x,y)
    })

    const grid = new Grid([new Start(0,0),  new End(end,end) ,...corouptingMemory])

    const max = corouptingMemory.length

    const route = (limit: number) => {
        const aStarInstance = new AStarFinder({
            grid: {
                matrix: grid.matrix(limit)
            },
            diagonalAllowed: false,
            includeStartNode: false,
        });
        const path = aStarInstance.findPath(grid.start, grid.end);
        return path.length
    }

    let noReturn: Coordinate = new Coordinate(0, 0)
    for (let index = max / 2; index < max; index++) {
        const path = route(index);
        if(path === 0) break;
        noReturn = corouptingMemory[index]
    }

    console.log(`${noReturn.x}, ${noReturn.y}`)

    assertEquals(noReturn.x, 6)
    assertEquals(noReturn.y, 36)
})