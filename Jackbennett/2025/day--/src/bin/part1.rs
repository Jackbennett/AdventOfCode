fn main() {
    let input = include_str!("../../input.txt");
    let ans = challenge(input);

    println!("Day 3 Part 1, {}", ans)
}

fn parse(i: &str) -> Vec<u64> {
    todo!()
}

fn challenge(input: &str) -> u64 {
    let maybe = parse(input);

    todo!()
}

#[cfg(test)]
mod tests {
    use super::*;
    const EXAMPLE: &str = "";

    #[test]
    fn check() {}

    #[test]
    fn clue() {
        assert_eq!(challenge(EXAMPLE), todo!("challenge example input"))
    }
}
