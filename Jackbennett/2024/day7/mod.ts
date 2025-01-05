import { assertGreater, assertEquals } from "jsr:@std/assert";


const example = `190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20`

const sum = (acc: number, val: number) => acc + val

interface Question {
    input: number[]
    answer: number
}


const parse = (f:string): Question[] => {
    const all = f.split('\n')

    return all.map(line => {
        const [answer, input] = line.split(':')
        return {
            answer: parseInt(answer, 10),
            input: input.split(' ').filter(d => !!d).map(d => parseInt(d, 10))
        }
    })   
}

interface Operators {[index: string]: (x: number,y: number) => number}

const checkPossible = (check: Question, possible: Operators) => {
    let isSolved = false
    let answer: string[] | undefined
    const branch = (progress: number, options: number[], used: string[] = []) => {
        const [a, ...input] = options
        for (const [op, fn] of Object.entries(possible)) {
            if(isSolved) return answer
            const history = Array.from(used)
            history.push(op)
            const guess = fn(progress, a)
            // console.log(`branch ${check.answer}: ${history} -> ${guess}`)
            if(guess === check.answer){
                isSolved = true
                answer = history
                return history
            } else if (input.length > 0){
                branch(guess, input, history)
            }
        }
        return answer
    }

    const [start, ...rest] = check.input
    const equation = branch(start, rest)

    return {
        equation,
        ...check
    }


}


const part1 = (d: ReturnType<typeof parse>) => {
    const ops: Operators = {
        '+': (a,b) => a + b,
        '*': (a,b) => a * b
    }

    const answers = d.map(x => checkPossible(x, ops))
    const correct = answers.filter(x => Array.isArray(x.equation))
    const incorrect = answers.filter(x => x.equation === undefined)
    const _removed_high = incorrect.filter(x => x.input.reduce( (t,v) => v===1 ? t + v : t * v, 0 ) < x.answer) // largest op can't get big enough
    const _removed_low = incorrect.filter(x => x.input.reduce(sum, 0) > x.answer) // smallest op can't be low enough
    return correct.map(x => x.answer).reduce(sum, 0)
}

// Deno.test('day 7 example', () => {
//     const d = parse(example)
//     console.log(d)
//     const a = part1(d)
//     console.log(a)
//     assertEquals(a, 3749)
// })

// Deno.test('day 7 mul first edge case', () => {
//     const d = parse(`10: 3 3 1`)
//     console.log(d)
//     const a = part1(d)
//     console.log(a)
//     assertEquals(a, 10)
// })

// Deno.test('day 7 part 1', () => {
//     const d = parse(Deno.readTextFileSync("./input.txt"))
//     const a = part1(d)
//     console.log(a)
//     assertGreater(a, 247970890361)
//     assertEquals(a, 5512534574980)
// })

const part2 = (d: ReturnType<typeof parse>) => {
    const ops: Operators = {
        '+': (a,b) => a + b,
        '*': (a,b) => a * b,
        '||': (a,b) => parseInt(`${a}${b}`)
    }

    const answers = d.map(x => checkPossible(x, ops))
    const correct = answers.filter(x => Array.isArray(x.equation))
    const incorrect = answers.filter(x => x.equation === undefined)
    const _removed_high = incorrect.filter(x => x.input.reduce( (t,v) => v===1 ? t + v : t * v, 0 ) < x.answer) // largest op can't get big enough
    const _removed_low = incorrect.filter(x => x.input.reduce(sum, 0) > x.answer) // smallest op can't be low enough
    return correct.map(x => x.answer).reduce(sum, 0)
}

Deno.test('day 7 example', () => {
    const d = parse(example)
    console.log(d)
    const a = part2(d)
    console.log(a)
    assertEquals(a, 11387)
})

Deno.test('day 7 part 2', () => {
    const d = parse(Deno.readTextFileSync("./input.txt"))
    console.log(d)
    const a = part2(d)
    console.log(a)
    assertEquals(a, 328790210468594)
})
