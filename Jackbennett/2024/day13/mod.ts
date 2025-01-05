import { Coordinate } from "../util.ts";

const example = `Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

Button A: X+26, Y+66
Button B: X+67, Y+21
Prize: X=12748, Y=12176

Button A: X+17, Y+86
Button B: X+84, Y+37
Prize: X=7870, Y=6450

Button A: X+69, Y+23
Button B: X+27, Y+71
Prize: X=18641, Y=10279`

function primeFactors(n: number) {
    const factors = [];
    let divisor = 2;
  
    while (n >= 2) {
      if (n % divisor == 0) {
        factors.push(divisor);
        n = n / divisor;
      } else {
        divisor++;
      }
    }
    return factors;
  }


const impossible = () => {
    const Ax = 26
    const Bx = 67

    const Px = 12748

    const answer = [
        primeFactors(Ax),
        primeFactors(Bx),
        primeFactors(Px)
    ]
    console.table(answer)
}

const one = (a:number,b:number,p:number) => {

    return[
        primeFactors(a),
        primeFactors(b),
        primeFactors(a+b),
        primeFactors(p)
    ]
}

class A extends Coordinate{}
class B extends Coordinate{}

const pathing = (start: Coordinate, finish: Coordinate, ...directions: Coordinate[]) => {
    const taken: Coordinate[]  = []
    let pos = start

    function* path(){

    }

    function* move(from: Coordinate, step: A | B) {
        for(const track of directions) {
            const ok = yield move(from.add(step), track)
            if(ok) {
                taken.push(step)
            }
        }
        switch(from.compare(from)) {
            case (-1): return false
            case(0): return true
        }
    }

    while(pos < finish){
        if(pos === finish) return taken
        pos = move()
    }
}

Deno.test('day 13 example', () => {

    const attempt = pathing(new Coordinate(0,0), new Coordinate(8400,5400), new A(94,34), new B(22,67))

    {
        const A = one(94,22,8400)
        const B = one(34,67,5400)
        console.log(A)
        console.log(B)
    }
    {
        const A = one(26,66,12748)
        const B = one(67,27,12176)
        console.log(A)
        console.log(B)
    }
    console.log('watch')
})