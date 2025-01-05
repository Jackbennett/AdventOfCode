import { assertGreater, assertEquals } from "jsr:@std/assert";


const example = `47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47`

interface Rule {
    page: number,
    before: number
}

const parse = (f:string) => {
    const all = f.split('\n')
    const cut = all.findIndex((val) => val === '')
    const orderRule = (r: string): Rule => {
        const [x, y] = r.split('|')
        return {page: parseInt(x, 10), before: parseInt(y, 10)}
    }
    return {
        pageOrder: all.slice(0,cut).map(rule => orderRule(rule)),
        updateList: all.slice(cut + 1).map(list => list.split(',').map(s => parseInt(s, 10)))
    }
}

const checkRule = (list: number[], rule: Rule) => {
    const a = list.indexOf(rule.page)
    const b = list.indexOf(rule.before)
    return a < b
}

const getRules = (list: number[], rules: Rule[]) => list.flatMap((val => rules.filter(r => r.page === val && list.includes(r.before))))

const checkPrintOrder = (list: number[], rules: Rule[]): boolean => {
    const has = getRules(list, rules)
    
    return has.every(r => checkRule(list, r))
}

const middle = (list: number[]) => list[Math.floor(list.length / 2)]

const sum = (acc: number, val: number) => acc + val

const part1 = (d: ReturnType<typeof parse>) => {
    const ok = d.updateList.filter(x => checkPrintOrder(x, d.pageOrder))
    const answers = ok.map(list => middle(list))
    return answers.reduce(sum)
}

Deno.test('example', () => {
    const d = parse(example)
    console.log(d)
    const a = part1(d)
    console.log(a)
})

Deno.test('day 5 part 1', () => {
    const d = parse(Deno.readTextFileSync("Jackbennett/2024/day5/input.txt"))
    const a = part1(d)
    console.log(a)
    assertEquals(a, 4569)
})

const reOrderPages = (list: number[], rules: Rule[]) => {
    const applicable = getRules(list, rules)
    applicable.sort((a,b) => b.page - a.page )
    const checks = applicable.map(r => checkRule(list, r))

    const toFix = applicable.filter(r => ! checkRule(list, r))
    const rearranged = toFix.reduce((moved, rule, idx, arr) => {
        const what = moved.indexOf(rule.before)
        moved.splice(what, 1)
        const where = moved.indexOf(rule.page)
        moved.splice(where + 1, 0, rule.before)
        return moved
    }, Array.from(list))

    const rechecks = applicable.map(r => checkRule(rearranged, r))
    if(rechecks.some(r => r === false)) { console.warn(`${list} didn't reorder correctly`)}


    // const rearranged = applicable.reduceRight((acc, rule, idx, arr) => {
    //     const p_idx = acc.indexOf(rule.page)
    //     if (p_idx === 0) return acc
    //     acc.splice(p_idx, 1)
    //     acc.unshift(rule.page)
    //     return acc
    // }, Array.from(list))
    return rearranged
}

const part2 = (d: ReturnType<typeof parse>) => {

    const fix = (l: number[][]) => {
        const toFix = l.filter(x => ! checkPrintOrder(x, d.pageOrder))
        const fixed = toFix.map(list => reOrderPages(list, d.pageOrder))
        const ok = fixed.filter(x => checkPrintOrder(x, d.pageOrder))
        const broken = fixed.filter(x => ! checkPrintOrder(x, d.pageOrder))
        return [ok, broken]
    }
    const limit = 30
    let count = 0
    const recurse = (l: number[][]): number[][] => {
        if(count > limit) {throw new Error('too much!')}
        count += 1
        
        const [ok, bad] = fix(l)
        if(bad.length === 0) {
            return ok
        } else {
            return [...ok, ...recurse(bad)]
        }
        
    }
    const allfixed = recurse(d.updateList)
    
    console.log(`recursion count ${count} under limit ${limit}`)
    return allfixed.map(list => middle(list)).reduce(sum)

}

Deno.test('day 5 part 2 example', () => {
    const d = parse(example)
    const a = part2(d)
    console.log(a)
    assertEquals(a, 123)
})

Deno.test('day 5 part 2', () => {
    const d = parse(Deno.readTextFileSync("./input.txt"))
    const a = part2(d)
    console.log(a)
    assertGreater(a, 276)
    assertEquals(a, 6456)
})