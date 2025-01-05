import { assert, AssertionError, assertEquals } from "jsr:@std/assert";

const example = `Register A: 729
Register B: 0
Register C: 0

Program: 0,1,5,4,3,0`

const input = `Register A: 59590048
Register B: 0
Register C: 0

Program: 2,4,1,5,7,5,0,3,1,6,4,3,5,5,3,0`



class Computer{
    program: number[] = []
    out: number[] = []
    skip_clock = false
    ip = 0
    constructor(public A: number, public B: number , public C: number) {}
    setProgram(program: number[]) {
        this.program = program
    }
    clock() {
        if(this.skip_clock) {
            this.skip_clock = false
            return
        }
        this.ip += 2
    }
    c_op = [
        () => 0,
        () => 1,
        () => 2,
        () => 3,
        () => this.A,
        () => this.B,
        () => this.C,
        () => {throw new Error('reserved')},
    ]
    opcode = [
        /// 0 adv 
        (operand: number) => {this.A = Math.trunc(this.A / Math.pow(2, this.c_op[operand]()))}, // powers 1, 2 4 or 8ths
        /// 1 bxl
        (operand: number) => {this.B = this.B ^ operand}, // self or zero?
        /// 2 bst
        (operand: number) => {this.B = this.c_op[operand]() % 8},
        /// 3 jnz
        (operand: number) => {
            if(this.A === 0) return
            this.ip = operand
            this.skip_clock = true
        },
        /// 4 bxc
        (_operand: number) => {this.B = this.B ^ this.C},
        /// 5 out
        (operand: number) => this.out.push(this.c_op[operand]() % 8),
        /// 6 bdv
        (operand: number) => {this.B = Math.trunc(this.A / Math.pow(2, this.c_op[operand]()))},
        /// 7 cdv
        (operand: number) => {this.C = Math.trunc(this.A / Math.pow(2, this.c_op[operand]()))},
    ]
    run() {
        while(this.ip < this.program.length) {
            const [op, arg] = this.program.slice(this.ip, this.ip + 2)
            // if(!Object.hasOwn(this.opcode, op)){
            //     throw new Error(`Unkown opcode ${op}`)
            // }
            // if(!Object.hasOwn(this.operand, arg)){
            //     throw new Error(`Unkown operand ${arg}`)
            // }
            this.opcode[op](arg)
            this.clock()
        }
        return this.out
    }
    reset(A:number, B:number, C:number) {
        this.A = A
        this.B = B
        this.C = C
        this.ip = 0
        this.skip_clock = false
        this.out = []
    }
}


Deno.test('day 17 example', () => {
    const c  = new Computer(729, 0, 0)

    c.setProgram([0,1,5,4,3,0])

    c.run()

    assertEquals(c.out, [4,6,3,5,6,3,5,2,1,0])
})

Deno.test('day 17 ex 1', () => {
    const c = new Computer(0, 0, 9)
    c.setProgram([2,6])
    c.run()
    assertEquals(c.B, 1)
})
Deno.test('day 17 ex 2', () => {
    const c = new Computer(10, 0, 0)
    c.setProgram([5,0,5,1,5,4])
    c.run()
    assertEquals(c.out, [0,1,2])
})
Deno.test('day 17 ex 3', () => {
    const c = new Computer(2024, 0, 0)
    c.setProgram([0,1,5,4,3,0])
    c.run()
    assertEquals(c.out, [4,2,5,6,7,7,7,7,3,1,0])
    assertEquals(c.A, 0)
})
Deno.test('day 17 ex 4', () => {
    const c = new Computer(0, 29, 0)
    c.setProgram([1,7])
    c.run()
    assertEquals(c.B, 26)
})
Deno.test('day 17 ex 5', () => {
    const c = new Computer(0, 2024, 43690)
    c.setProgram([4,0])
    c.run()
    assertEquals(c.B, 44354)
})


Deno.test('day 17 part 1', () => {
    const c  = new Computer(59590048, 0, 0)

    c.setProgram([2,4,1,5,7,5,0,3,1,6,4,3,5,5,3,0])

    c.run()

    console.log(c.out.join(','))

    assertEquals(c.out, [6,5,7,4,5,7,3,1,0])

    //     6,5,7,4,5,7,3,1,0
    // not 6,2,5,4,1,1,7,7,0
    // assertEquals(c.out, [1])
})

Deno.test('day 17 part 2 example', () => {
    const c = new Computer(117440, 0, 0)
    c.setProgram([0,3,5,4,3,0])
    c.run()
    console.log(c.out)
    assert(true)
})

// 00110000 00110011 00110101 00110100 00110011 00110000
// 00110001 00110001 00110111 00110100 00110100 00110000

Deno.test('day 17 part 2', () => {
    const startNum = 59_590_048
    const expectProgram = [2,4,1,5,7,5,0,3,1,6,4,3,5,5,3,0]
    let searchFrom = 103_411_368 // 59_590_048 // up to searchFrom 278_753_152
    const c  = new Computer(searchFrom, 0, 0)
    c.setProgram(expectProgram)

    while(searchFrom < searchFrom * 2){
        try{
            c.run()
            assertEquals(c.out, expectProgram)
            console.log(searchFrom)
        } catch(err) {
            if(err instanceof AssertionError) {
                // searchFrom % 8 === 0 ? searchFrom -= 2 :  searchFrom -= 1
                searchFrom += 8
                c.reset(searchFrom, 0, 0)
                if(searchFrom % (8 * 10_000) === 0) console.log(`try ${searchFrom}`)
            } else {
                throw err
            }
        }
    }
    

})