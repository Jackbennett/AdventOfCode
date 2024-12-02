
// const kv = Deno.openKv()

// enum DayPart {
//     One,
//     Two
// }

// interface Progress {
//     day: number,
//     progress?: DayPart
// }

const parse = async (path: string) => {
    const f = (await Deno.readTextFile(path)).split('\n')
    const id = new Array(f.length)
    const dist = new Array(f.length)
    for (const [idx, line] of f.entries()) {
        const [a, b] = line.split(/\s+/)
        id[idx] = parseInt(a, 10)
        dist[idx] = parseInt(b, 10)
    }
    return [id,dist]
}

// function testDay(number: number) {
//     const fn = import(`day${number}/mod.ts`)
// }

// for(const d of Array.from(Array(24))){
//     testDay(d)
// }
// const progress = kv.list<number>({prefix: 'days'})
// Math.max(progress)

function now(){
    const done = Array.from(Deno.readDirSync(import.meta.dirname || './'))
    .filter(n => n.isDirectory)
    .filter(n => n.name.startsWith('day'))
    .map( n => {
        const [_drop, num] = n.name.split('day')
        return parseInt(num, 10)
    })
    const fn = import(`day${Math.max(...done)}/mod.ts`)
    fn()
}

now()