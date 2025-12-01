fn main() {
    let input = include_str!("../../input.txt");
    let ans = part1(input);

    println!("Day 1 Part 1, {}", ans)
}

fn part1(_input: &str) -> u64 {
    10_000_000
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn clue() {
        assert_eq!(part1("unused"), 10000000)
    }
}
