use nom::{
    character::complete::alpha1, character::complete::line_ending, multi::separated_list1, IResult,
};

pub fn parse_backback_contents(input: &str) -> IResult<&str, Vec<&str>> {
    separated_list1(line_ending, alpha1)(input)
}

pub fn find_common_item(input: &str) -> char {
    let mid = &input.len() / 2;
    let a = &input[..mid];
    let b = &input[mid..];
    let first: Vec<char> = a.chars().take_while(|&l| b.contains(l)).collect();
    if first.is_empty() {
        let second: Vec<char> = b.chars().take_while(|&l| a.contains(l)).collect();
        second[0]
    } else {
        first[0]
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_one_of() {
        let input = "abcdEFGHia\r\n";
        let parsed_file = parse_backback_contents(input);
        let mut found = Vec::new();
        match parsed_file {
            Ok((_, file)) => {
                for line in file {
                    found.push(find_common_item(line));
                }
            }
            Err(_) => todo!(),
        };
        assert_eq!(found[0], 'a');
    }
}
