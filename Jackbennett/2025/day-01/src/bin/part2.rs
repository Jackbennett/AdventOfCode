fn main() {
    let input = include_str!("../../input.txt");
    let ans = part2(input);

    println!("Day 1 Part 2, {}", ans)
}

#[derive(Debug, Copy, Clone, PartialEq)] // Add these derives for easier use
struct Dial {
    indicator: i32,
    min: i32,
    max: i32,
    clocked: i32,
    crossed: i32,
}

impl Dial {
    fn add(&mut self, amount: i32) {
        self.clocked = amount / self.size();
        let new = (self.indicator + amount).rem_euclid(self.size());
        if new <= self.indicator && new != 0 {
            self.crossed = 1;
        }
        self.indicator = new
    }
    fn sub(&mut self, amount: i32) {
        self.clocked = amount / self.size();
        let new: i32 = (self.indicator - amount).rem_euclid(self.size());
        if new >= self.indicator && self.indicator != 0 {
            self.crossed = 1;
        }
        self.indicator = new
    }
    fn size(self) -> i32 {
        self.max - self.min
    }
    fn into(self) -> i32 {
        self.indicator
    }
}

fn rotate(cmd: &str, start: &i32) -> Dial {
    let clicks = cmd[1..].parse::<i32>().unwrap();
    let mut dial = Dial {
        indicator: *start,
        min: 0,
        max: 100,
        crossed: 0,
        clocked: 0,
    };
    // println!("{:?}", dial);
    if cmd.starts_with('L') {
        dial.sub(clicks)
    } else if cmd.starts_with('R') {
        dial.add(clicks);
    } else {
        panic!()
    }
    dial
}

fn part2(input: &str) -> i32 {
    let mut indicator = 50;
    let mut zeros = 0;
    let mut revolutons = 0;
    let mut crosses = 0;

    for s in input.lines() {
        let spin = rotate(s, &indicator);
        revolutons += spin.clocked;
        crosses += spin.crossed;
        indicator = spin.into();
        if indicator == 0 {
            zeros += 1;
        }
    }

    zeros + revolutons + crosses
}

#[cfg(test)]
mod tests {
    use super::*;
    const EXAMPLE: &str = "L68
L30
R48
L5
R60
L55
L1
L99
R14
L82";

    #[test]
    fn wrapping() {
        let d = rotate("L68", &50);
        assert_eq!(d.indicator, 82);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 1);
        let d = rotate("L30", &d.indicator);
        assert_eq!(d.indicator, 52);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 0);
        let d = rotate("R48", &d.indicator);
        assert_eq!(d.indicator, 0);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 0);
        let d = rotate("L5", &d.indicator);
        assert_eq!(d.indicator, 95);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 0);
        let d = rotate("R60", &d.indicator);
        assert_eq!(d.indicator, 55);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 1);
        let d = rotate("L55", &d.indicator);
        assert_eq!(d.indicator, 0);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 0);
        let d = rotate("L1", &d.indicator);
        assert_eq!(d.indicator, 99);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 0);
        let d = rotate("L99", &d.indicator);
        assert_eq!(d.indicator, 0);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 0);
        let d = rotate("R14", &d.indicator);
        assert_eq!(d.indicator, 14);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 0);
        let d = rotate("L82", &d.indicator);
        assert_eq!(d.indicator, 32);
        assert_eq!(d.clocked, 0);
        assert_eq!(d.crossed, 1);
    }

    #[test]
    fn clue() {
        let mut pos = 50;
        println!("The dial starts by pointing at {}", pos);
        for ln in EXAMPLE.lines() {
            pos = rotate(ln, &pos).into();
            println!("The dial is rotated {} to point at {}", ln, pos);
        }
    }
}
