export const sum = (acc: number, val: number) => acc + val

export const parse = (f:string): string[] => {
    const txt = f.includes('\n') ? f : Deno.readTextFileSync(f)
    return txt.split('\n')
}

export const toSplitNumber = (list: string, on= ' ') => list.split(on).filter(d => !!d).map(d => parseInt(d, 10))

export class Coordinate {
    constructor(public x: number, public y: number) {}
    add({x = this.x, y = this.y}: Coordinate | {x?: number, y: number} | {x: number, y?: number}) {
        return new Coordinate(this.x + x, this.y + y)
    }
    is(to: Coordinate): boolean {
        return this.compare(to) === 0
    }
    compare(to: Coordinate) {
        if(this.x > to.x || this.y > to.y) return 1
        if(this.x < to.x || this.y < to.y) return -1
        if(this.x === to.x && this.y === to.y) return 0
        if(this.x > to.x && this.y > to.y) return 1
        if(this.x < to.x && this.y < to.y) return -1
        return -1
    }
}

export class Robot {
    constructor(public position: Coordinate, public speed: Coordinate, public serial: number) {}
    tick() {
        this.position.x += this.speed.x
        this.position.y += this.speed.y
    }
}