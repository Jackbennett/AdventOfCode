export const sum = (acc: number, val: number) => acc + val

export const parse = (f:string): string[] => {
    const txt = f.includes('\n') ? f : Deno.readTextFileSync(f)
    return txt.split('\n')
}

export const toSplitNumber = (list: string, on= ' ') => list.split(on).filter(d => !!d).map(d => parseInt(d, 10))
