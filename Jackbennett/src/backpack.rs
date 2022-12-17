use nom::{
    character::complete::alpha1, character::complete::line_ending, multi::separated_list1, IResult,
};

pub fn parse_backback_contents(input: &str) -> IResult<&str, Vec<&str>> {
    separated_list1(line_ending, alpha1)(input)
}

pub fn find_common_item(input: &str) -> Option<char> {
    let mid = &input.len() / 2;
    let a = &input[..mid];
    let b = &input[mid..];
    let mut found: Vec<char> = Vec::new();
    for l in a.chars() {
        if b.contains(l) {
            found.push(l);
        }
    }
    for l in b.chars() {
        if a.contains(l) {
            found.push(l);
        }
    }
    if !found.is_empty() {
        Some(found[0])
    } else {
        None
    }
}

pub fn get_item_value(item: char) -> u32 {
    let i = item as u32;
    // mask the case-bit to calculate score.
    match i & 0b10_0000 {
        0b0 => i % 64 + 26,
        _ => i % 96,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_one_of() {
        let input = "abcdEFGHia\r\n";
        let (_, parsed_file) = parse_backback_contents(&input).unwrap();
        let found: Vec<char> = parsed_file
            .iter()
            .filter_map(|pack| find_common_item(pack))
            .collect();

        assert_eq!(found[0], 'a');
    }

    #[test]
    fn test_one_of_real() {
        let input = "mmbclcsDHCflDDlCrzzrDWjPJvjPvqJPjfpqZQdfWd\r\n";
        let (_, parsed_file) = parse_backback_contents(&input).unwrap();
        let found: Vec<char> = parsed_file
            .iter()
            .filter_map(|pack| find_common_item(pack))
            .collect();

        assert_eq!(found[0], 'f');
    }

    #[test]
    fn test_one_of_some() {
        let input = "abcdEFGHia\r\nKbcdEFGHiK\r\nabcdEFGHiz\r\n";
        let (_, parsed_file) = parse_backback_contents(&input).unwrap();
        let found: Vec<char> = parsed_file
            .iter()
            .filter_map(|pack| find_common_item(pack))
            .collect();
        assert_eq!(found[0], 'a');
        assert_eq!(found[1], 'K');
        assert_eq!(found.len(), 2);
    }

    #[test]
    fn test_parsed_score() {
        let lower_case = get_item_value('b');
        assert_eq!(lower_case, 2_u32);

        assert_eq!(get_item_value('a'), 1_u32);
        assert_eq!(get_item_value('Q'), 43_u32);
    }

    #[test]
    fn test_print_score_values() {
        let title_len = 14;

        print!("{text:padding$}", padding = title_len, text = "Lower Set:");
        let lower_set = 97..(97 + 26) as u32;
        for i in lower_set.clone() {
            let letter = char::from_u32(i);
            print!("{:>3} ", letter.unwrap());
        }
        println!();

        print!(
            "{text:padding$}",
            padding = title_len,
            text = "Code points:"
        );
        for x in lower_set.clone() {
            print!("{:>3} ", x as u32);
        }
        println!();

        print!("{text:padding$}", padding = title_len, text = "Score:");
        for x in lower_set {
            print!("{:>3} ", get_item_value(char::from_u32(x).unwrap()));
        }

        println!();
        println!();

        print!("{text:padding$}", padding = title_len, text = "Upper Set:");
        let upper_set = 65..(65 + 26) as u32;
        for i in upper_set.clone() {
            let letter = char::from_u32(i);
            print!("{:>3} ", letter.unwrap());
        }
        println!();
        print!(
            "{text:padding$}",
            padding = title_len,
            text = "Code points:"
        );
        for x in upper_set.clone() {
            print!("{:>3} ", x as u32);
        }
        println!();

        print!("{text:padding$}", padding = title_len, text = "Score:");
        for x in upper_set {
            print!("{:>3} ", get_item_value(char::from_u32(x).unwrap()));
        }
        println!();
    }
}
