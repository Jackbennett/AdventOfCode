use nom::{
    bytes::complete::tag,
    character::complete::{digit1, line_ending},
    combinator::map,
    combinator::map_res,
    multi::separated_list1,
    sequence::separated_pair,
    IResult,
};
use std::ops::RangeInclusive;
use std::str;
type Assignment = (RangeInclusive<i32>, RangeInclusive<i32>);

pub fn parse(input: &str) -> IResult<&str, Vec<Assignment>> {
    let parse_section = |x| {
        map(
            separated_pair(
                map_res(digit1, str::parse),
                tag("-"),
                map_res(digit1, str::parse),
            ),
            |(s, e)| RangeInclusive::new(s, e),
        )(x)
    };

    let line = separated_pair(parse_section, tag(","), parse_section);

    separated_list1(line_ending, line)(input)
}

pub fn subrange((a, b): &Assignment) -> bool {
    a.contains(&b.start()) && a.contains(&b.end()) || b.contains(&a.start()) && b.contains(&a.end())
}
pub fn overlap_range((a, b): &Assignment) -> bool {
    a.contains(&b.start()) || a.contains(&b.end()) || b.contains(&a.start()) || b.contains(&a.end())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse() {
        let input = "2-4,6-8\r\n2-3,4-5\r\n2-8,3-7\r\n";
        let (_, data) = parse(&input).unwrap();
        assert_eq!(
            data,
            vec![((2..=4), (6..=8)), ((2..=3), (4..=5)), ((2..=8), (3..=7))]
        );
    }

    #[test]
    fn test_found_subrange() {
        let in_range: Assignment = ((2..=8), (3..=7));
        assert!(subrange(&in_range));

        let out_range: Assignment = ((5..=7), (7..=9));
        assert!(!subrange(&out_range));

        let out_start_range: Assignment = ((11..=50), (4..=49));
        assert_eq!(subrange(&out_start_range), false);

        let match_range: Assignment = ((59..=97), (60..=60));
        assert!(subrange(&match_range));
    }

    #[test]
    fn test_overlap() {
        let a = ((5..=89), (2..=2));
        assert!(!overlap_range(&a), "range {:?} should be false", a);
        assert!(!overlap_range(&((2..=2), (5..=5))));
        assert!(overlap_range(&((5..=89), (5..=5))));
        assert!(overlap_range(&((5..=5), (5..=89))));
    }
}
