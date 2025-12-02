fn main() {
    let input = include_str!("../../input.txt");
    let ans = part1(input);

    println!("Day 1 Part 1, {}", ans)
}

#[derive(Debug, Copy, Clone, PartialEq)] // Add these derives for easier use
struct Dial {
    indicator: i32,
    min: i32,
    max: i32,
}

impl Dial {
    fn add(&mut self, amount: i32) {
        self.indicator = (self.indicator + amount).rem_euclid(self.size());
    }
    fn sub(&mut self, amount: i32) {
        self.indicator = (self.indicator - amount).rem_euclid(self.size());
    }
    fn size(self) -> i32 {
        self.max - self.min
    }
    fn into(self) -> i32 {
        self.indicator
    }
}

fn rotate(cmd: &str, start: &i32) -> i32 {
    let clicks = cmd[1..].parse::<i32>().unwrap();
    let mut dial = Dial {
        indicator: *start,
        min: 0,
        max: 100,
    };
    // println!("{:?}", dial);
    if cmd.starts_with('L') {
        dial.sub(clicks)
    } else if cmd.starts_with('R') {
        dial.add(clicks);
    } else {
        panic!()
    }
    dial.into()
}

fn part1(input: &str) -> u64 {
    let mut indicator = 50;
    let mut zeros = 0;

    for s in input.lines() {
        indicator = rotate(s, &indicator);
        if indicator == 0 {
            zeros += 1
        }
    }

    zeros
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
        assert_eq!(rotate("L10", &5), 95);
        assert_eq!(rotate("R5", &95), 0);
        assert_eq!(rotate("R48", &52), 0);
    }

    #[test]
    fn clue() {
        let mut pos = 50;
        println!("The dial starts by pointing at {}", pos);
        for ln in EXAMPLE.lines() {
            pos = rotate(ln, &pos);
            println!("The dial is rotated {} to point at {}", ln, pos);
        }
    }
}
