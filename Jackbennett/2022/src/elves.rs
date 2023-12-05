use nom::{
    character::complete::digit1, character::complete::line_ending, combinator::map,
    combinator::map_res, multi::separated_list1, sequence::pair, IResult,
};
use std::str::FromStr;

pub fn parse_numbers(input: &str) -> IResult<&str, u32> {
    map_res(digit1, u32::from_str)(input)
}

#[derive(Debug, Eq, PartialEq, Clone)]
pub struct Elf {
    pub food: Vec<u32>,
}

impl Elf {
    pub fn parse(input: &str) -> IResult<&str, Self> {
        let parse_calories = separated_list1(line_ending, parse_numbers);

        map(parse_calories, |food| Elf { food })(input)
    }

    pub fn energy(&self) -> u32 {
        self.food.iter().sum()
    }
}

#[derive(Debug, Eq, PartialEq)]
pub struct Expedition {
    pub elves: Vec<Elf>,
}

impl Expedition {
    pub fn parse(input: &str) -> IResult<&str, Self> {
        let parse_elves = separated_list1(pair(line_ending, line_ending), Elf::parse);

        map(parse_elves, |elves| Expedition { elves })(input)
    }

    pub fn size(&self) -> usize {
        self.elves.len()
    }

    pub fn energy(&self) -> u32 {
        self.elves.iter().map(|e| e.energy()).sum()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_food() {
        let input = "1000\n2000\n3000\n".to_string();

        assert_eq!(
            Elf::parse(&input).unwrap(),
            (
                "\n",
                Elf {
                    food: vec![1000, 2000, 3000]
                }
            )
        )
    }

    #[test]
    fn test_parse_elf() {
        let input = "1000\n2000\n3000\n\n4000\n5000\n".to_string();

        let (remainder, elf) = Elf::parse(&input).unwrap();
        assert_eq!(
            elf,
            Elf {
                food: vec![1000, 2000, 3000]
            }
        );
        assert_eq!(remainder, "\n\n4000\n5000\n");
    }

    #[test]
    fn test_parse_elves() {
        let mock_input = "1000\n2000\n3000\n\n4000\n".to_string();

        let (remainder, expedition) = Expedition::parse(&mock_input).unwrap();
        assert_eq!(
            expedition,
            Expedition {
                elves: vec![
                    Elf {
                        food: vec![1000, 2000, 3000]
                    },
                    Elf { food: vec![4000] }
                ]
            }
        );
        assert_eq!(remainder, "\n");
        assert_eq!(expedition.size(), 2);
    }
}
