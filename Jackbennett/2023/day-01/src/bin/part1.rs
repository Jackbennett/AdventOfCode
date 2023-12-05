fn main() {
    let input = include_str!("../../input.txt");
    let output = answer(input);
    dbg!(output);
    #[cfg(feature = "answer")]
    assert_eq!(output, 55712);
}

fn answer(input: &str) -> u64 {
    // sum
    // input.lines().fold(0, |acc, line| acc + decode_line(line))
    input.lines().map(|line| decode_line(line)).sum()
}

fn decode_line(line: &str) -> u64 {
    let a = line.chars().find_map(|f| f.to_digit(10)).unwrap_or(0);
    let b = line.chars().rev().find_map(|f| f.to_digit(10)).unwrap_or(0);
    vec![a, b]
        .iter()
        .fold(0, |acc, digit| acc * 10 + digit)
        .into()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_input_reference() {
        let input = "1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet
";
        assert_eq!(answer(input), 142)
    }
    #[test]
    fn test_line_parse() {
        let input = "a1b2c3d4e5f";
        assert_eq!(decode_line(input), 15)
    }
}
