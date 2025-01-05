import { Coordinate } from "../util.ts";

const example = `....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...`

class Map {

}

const parse = (f: string) => {
    const grid = f.split('\n').map(l => Array.from(l))
    const guard = grid.flatMap((l, y) => l.map( (i, x) => i === '^' ? new Coordinate(x,y): undefined)).find(d => d)
    console.log(guard)
    return [grid, guard]
}

Deno.test('example', () => {
    const [grid, guard] = parse(example)

    function* turns(grid: string[][]) {
        let next = grid[y-1][x]
        while next
    }

    let steps = 0
    grid[guard.y][guard.x]
})