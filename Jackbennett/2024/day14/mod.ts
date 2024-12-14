import { assert, assertEquals } from 'jsr:@std/assert';
import { sum,parse } from '../util.ts'


const example = `p=0,4 v=3,-3
p=6,3 v=-1,-3
p=10,3 v=-1,2
p=2,0 v=2,-1
p=0,0 v=1,3
p=3,0 v=-2,-2
p=7,6 v=-1,-3
p=3,0 v=-1,-2
p=9,3 v=2,3
p=7,3 v=-1,2
p=2,4 v=2,-3
p=9,5 v=-3,-3`

class Coordinate {
    constructor(public x: number, public y: number) {}
}

const createRobot = (str: string) => {
    return parse(str).map((line, idx) => {
        const [p, v] = line.split(' ')
        let pos: Coordinate
        let vel: Coordinate
        {
            const [_orig, x, y] = p.match(/(-?\d+),(-?\d+)/) || []
            pos = new Coordinate(parseInt(x, 10), parseInt(y, 10))
        }
        {
            const [_orig, x, y] = v.match(/(-?\d+),(-?\d+)/) || []
            vel = new Coordinate(parseInt(x, 10), parseInt(y, 10))

        }
        return new Robot(pos, vel, idx)

    })
}

class Robot {
    constructor(public position: Coordinate, public speed: Coordinate, public serial: number) {}
    tick() {
        this.position.x += this.speed.x
        this.position.y += this.speed.y
    }
}
class Grid {
    robots: Robot[] = []
    constructor(public size: Coordinate) {}
    addRobot(r: Robot) {
        this.robots.push(r)
    }
    wrapLimits() {
        this.robots.forEach(r => {
            if(r.position.x >= this.size.x) {
                r.position.x -= this.size.x
            }
            if(r.position.y >= this.size.y) {
                r.position.y -= this.size.y
            }
            if(r.position.x < 0) {
                r.position.x += this.size.x
            }
            if(r.position.y < 0) {
                r.position.y += this.size.y
            }
        })
    }
    tick() {
        this.robots.forEach(r => r.tick())
        this.wrapLimits()

    }
    quadrantCount(){
        const mid_x = Math.floor(this.size.x / 2)
        const mid_y = Math.floor(this.size.y / 2)
        return [
            this.robots.filter(r => r.position.x < mid_x && r.position.y < mid_y).length,
            this.robots.filter(r => r.position.x > mid_x && r.position.y < mid_y).length,
            this.robots.filter(r => r.position.x < mid_x && r.position.y > mid_y).length,
            this.robots.filter(r => r.position.x > mid_x && r.position.y > mid_y).length,
        ]
    }
    order() {
        const screen = Array.from(new Array(this.size.y), () => Array.from(Array(this.size.x)).fill(0))
        const around = ({x, y}: Coordinate) => {
            const ym1 = screen.at(y > 0 ? y - 1: 0) // over is fine, this handles under index.
            const above = [ym1?.at(x > 0 ? x - 1: 0), ym1?.at(x), ym1?.at(x + 1)]
            const beside = [screen[y].at(x -1),screen[y].at(x + 1)]
            const under = [screen.at(y +1)?.at(x > 0 ? x - 1: 0),screen.at(y +1)?.at(x),screen.at(y +1)?.at(x+1)]
            const area = [above, beside, under]
            return {
                count: area.flatMap(d => d.map(x => x ? x : 0)).reduce(sum),
                area
            }
        }
        this.robots.forEach(({position: c}) => {
            screen[c.y][c.x] += 1
        })

        const busy = this.robots.map(({position: p}) => around(p)        )

        // const busy = new Map<string, number>()
        // for(let x = 1; x < this.size.x; x += 2) {
        //     for(let y = 1; y < this.size.y; y += 2) {
        //         if(!screen[y][x]) continue
        //         const above = [screen[y -1].at(x - 1), screen[y -1].at(x), screen[y -1].at(x + 1)]
        //         const here = [screen[y].at(x -1),screen[y].at(x + 1)]
        //         const below = [screen[y +1].at(x-1),screen[y +1].at(x),screen[y +1].at(x+1)]
        //         const n = [above, here, below].flatMap(d => d).reduce(sum)
        //         if(n) busy.set(`${x},${y}`, n)
        //     }
        // }
        return busy
    }
    #within(a: number, b: number, range: number = 1) {
        const t = Math.abs(b - a) < 1
        if(a === b) return true
        const lower = a - range
        const upper = a + range
        return b >= lower && b <= upper
    }
    nextTo(me: Robot){
        const neightbors = this.robots.filter(r => this.#within(me.position.x, r.position.x) && this.#within(me.position.y, r.position.y)).length
        return neightbors
    }
}

interface Part1 {
    time: number
    initial_robots: Robot[]
    bathroom: Coordinate
}

const day14 = {
    part1(opts: Part1, frame = (state: Grid, time: number) => {}) {
        const map = new Grid( opts.bathroom )
        map.robots = opts.initial_robots
        for (let s = 1; s < opts.time + 1; s += 1) {
            map.tick()
            frame(map, s)
        }

        return map.quadrantCount()
    }

}


Deno.test('day 14 example', () => {
    const robot_list = createRobot(example)
    const quads = day14.part1({
        time: 100,
        initial_robots: robot_list,
        bathroom: new Coordinate(11,7)
    })
    const safetyFactory = quads.reduce((acc, q) => acc * q)
    assertEquals(safetyFactory, 12)
})

// Deno.test('day 14 part 1', () => {
//     const robot_list = createRobot('./input.txt')
//     const safetyFactory = day14.part1({
//         time: 100,
//         initial_robots: robot_list,
//         bathroom: new Coordinate(101,103)
//     })
//     assertEquals(safetyFactory, 228410028)
// })

Deno.test('day 14 part 2', () => {
    const robot_list = createRobot('./input.txt')
    const encoder = new TextEncoder()
    let lowestZero: number = 100000000000000
    const _safetyFactory = day14.part1({
        time: 100000,
        initial_robots: robot_list,
        bathroom: new Coordinate(101,103)
    }, (m, s) => {

        if(s === 8258) { assert(true) }

        const order = m.order()
        const nbs = order.reduce((acc, nCount) => {
            acc.set(nCount.count, (acc.get(nCount.count) || 0) + 1)
            return acc
        }, new Map<number,number>())

        const zeros = nbs.get(0)
        
        if(zeros && (lowestZero > zeros)){
            lowestZero = zeros
            const coords = m.robots.map(r => r.position).sort(((a,b) => a.y - b.y))
            const screen = Array.from(new Array(m.size.y), () => Array.from(Array(m.size.x)).fill(' '))
            coords.forEach(c => {
                screen[c.y][c.x] = 'x'
            })
            const f = encoder.encode(screen.map(ln => ln.join('')).join('\n'))
            Deno.writeFileSync('./show.txt', f, {
                create: true,
            })
            console.log(`${s} seconds runtime`)
            console.log(nbs)
        }
})
    // 718 is too low
})