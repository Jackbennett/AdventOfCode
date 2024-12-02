import { distance } from "../day1/mod.ts"

const parse = (f: string) => {
  const txt = Deno.readTextFileSync(f);
  return txt.split("\n")
    .map((line) => line.split(" ").map((d) => parseInt(d, 10)));
};

function isLower(lvl: number[]){
    let last
    for(const n in lvl){
        n < last
        last = n
    }
}

enum Safety {
    Safe,
    Unsafe
}

const compare 

function ascending(prev, val, idx, arr){
    const peek = arr.at(idx + 1)
    if(peek){
        val > peek
        arr = []
    } else {

    }
    return prev
}


function asDistance(prev, val, idx, arr){
    const peek = arr.at(idx + 1)
    prev[idx] = peek ? distance(val, peek) : 0
    return prev
}

export function PoC() {
    const records = parse("./example.txt");
    
    const safety = Array.from(Array(records.length))
    records.forEach((levels, i) => {
        // direction check



        // distance check
        const distances = Array.from(Array(levels.length))
        levels.reduce(asDistance, distances)
        
        if(distances.every(d => d <=3)) {
            safety[i] = Safety.Safe
        } else {
            safety[i] = Safety.Unsafe
        }

    })

    // count safety.
    const safe = safety.filter(s => s === Safety.Safe).length
    return safe
}

console.log(PoC())
