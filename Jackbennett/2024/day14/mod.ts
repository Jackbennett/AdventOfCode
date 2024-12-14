import { assertEquals } from 'jsr:@std/assert';
import { toSplitNumber,parse } from '../util.ts'
import { TextLineStream } from "https://deno.land/std/streams/mod.ts";

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
        let [p, v] = line.split(' ')
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
}

interface Part1 {
    time: number
    initial_robots: Robot[]
    bathroom: Coordinate
}

const day14 = {
    part1(opts: Part1) {
        const map = new Grid( opts.bathroom )
        map.robots = opts.initial_robots
        for (let s = 1; s < opts.time + 1; s += 1) {
            map.tick()
            console.log(s)
        }

        const quads = map.quadrantCount()

        return quads.reduce((acc, q) => acc * q)
    }

}


Deno.test('day 14 example', () => {
    const robot_list = createRobot(example)
    const safetyFactory = day14.part1({
        time: 100,
        initial_robots: robot_list,
        bathroom: new Coordinate(11,7)
    })
    assertEquals(safetyFactory, 12)
})

Deno.test('day 14 part 1', () => {
    const robot_list = createRobot('./input.txt')
    const safetyFactory = day14.part1({
        time: 100,
        initial_robots: robot_list,
        bathroom: new Coordinate(101,103)
    })
    assertEquals(safetyFactory, 228410028)
})
