use nom::{
    branch::alt, bytes::complete::tag, character::complete::line_ending, combinator::map,
    multi::separated_list1, sequence::separated_pair, IResult,
};
use std::cmp::Ordering;

#[derive(Eq, PartialEq, PartialOrd, Debug, Clone, Copy)]
pub enum Rps {
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3,
}

impl Ord for Rps {
    fn cmp(&self, other: &Self) -> Ordering {
        match (self, other) {
            (Rps::ROCK, Rps::PAPER) => Ordering::Less,
            (Rps::ROCK, Rps::ROCK) => Ordering::Equal,
            (Rps::ROCK, Rps::SCISSORS) => Ordering::Greater,
            (Rps::PAPER, Rps::PAPER) => Ordering::Equal,
            (Rps::PAPER, Rps::ROCK) => Ordering::Greater,
            (Rps::PAPER, Rps::SCISSORS) => Ordering::Less,
            (Rps::SCISSORS, Rps::PAPER) => Ordering::Greater,
            (Rps::SCISSORS, Rps::ROCK) => Ordering::Less,
            (Rps::SCISSORS, Rps::SCISSORS) => Ordering::Equal,
        }
    }
} // TODO fix compare to understand Rock/paper/scissors not just gt/tf enum value.

#[derive(Eq, PartialEq, Ord, PartialOrd, Clone, Copy, Debug)]
pub enum Result {
    LOSS = 0,
    DRAW = 3,
    WIN = 6,
}

#[derive(PartialEq, Debug)]
pub struct Round {
    opponent: Rps,
    choice: Rps,
}

impl Round {
    pub fn parse(s: &str) -> IResult<&str, Self> {
        let turn = |input| {
            alt((
                map(alt((tag("A"), tag("X"))), |_| Rps::ROCK),
                map(alt((tag("B"), tag("Y"))), |_| Rps::PAPER),
                map(alt((tag("C"), tag("Z"))), |_| Rps::SCISSORS),
            ))(input)
        };

        map(
            separated_pair(turn, tag(" "), turn),
            |(opponent, choice)| Self { choice, opponent },
        )(s)
    }
    pub fn result(&self) -> Result {
        match self.choice.cmp(&self.opponent) {
            Ordering::Greater => Result::WIN,
            Ordering::Equal => Result::DRAW,
            Ordering::Less => Result::LOSS,
        }
    }
    pub fn score(&self) -> u32 {
        self.choice as u32 + self.result() as u32
    }
}

pub struct Predict {
    opponent: Rps,
    target: Result,
}
impl Predict {
    pub fn parse(s: &str) -> IResult<&str, Self> {
        let turn = |input| {
            alt((
                map(tag("A"), |_| Rps::ROCK),
                map(tag("B"), |_| Rps::PAPER),
                map(tag("C"), |_| Rps::SCISSORS),
            ))(input)
        };
        let result = |input| {
            alt((
                map(tag("X"), |_| Result::LOSS),
                map(tag("Y"), |_| Result::DRAW),
                map(tag("Z"), |_| Result::WIN),
            ))(input)
        };

        map(
            separated_pair(turn, tag(" "), result),
            |(opponent, target)| Self { opponent, target },
        )(s)
    }
    pub fn choice(&self) -> Rps {
        match self.target {
            Result::DRAW => self.opponent,
            Result::LOSS => match self.opponent {
                Rps::ROCK => Rps::SCISSORS,
                Rps::PAPER => Rps::ROCK,
                Rps::SCISSORS => Rps::PAPER,
            },
            Result::WIN => match self.opponent {
                Rps::ROCK => Rps::PAPER,
                Rps::PAPER => Rps::SCISSORS,
                Rps::SCISSORS => Rps::ROCK,
            },
        }
    }
    pub fn score(&self) -> u32 {
        self.choice() as u32 + self.target as u32
    }
}

pub fn parse_tournament(input: &str) -> IResult<&str, Vec<Round>> {
    separated_list1(line_ending, Round::parse)(input)
}

pub fn parse_prediction(input: &str) -> IResult<&str, Vec<Predict>> {
    separated_list1(line_ending, Predict::parse)(input)
}

#[cfg(test)]
mod tests_moves {
    use super::*;

    #[test]
    fn test_outcome() {
        let input = "A X\r\nB X\r\nC Z\r\n";

        let (_remaining, tournament) = parse_tournament(input).unwrap();

        assert_eq!(tournament.len(), 3);
        assert_eq!(tournament[0].opponent, Rps::ROCK);
        assert_eq!(tournament[0].choice, Rps::ROCK);
        // assert_eq!(tournament.1.sum(), 3);
    }
    #[test]
    fn test_score_draw() {
        let input = "A X\r\n";

        let (_remaining, tournament) = parse_tournament(input).unwrap();

        assert_eq!(tournament.len(), 1);

        assert_eq!(tournament[0].choice, Rps::ROCK);
        assert_eq!(tournament[0].result(), Result::DRAW);
        assert_eq!(tournament[0].score(), 4); // 1(Rock) + 3(Draw) = 4
    }
    #[test]
    fn test_score_loss() {
        let input = "A Z\r\n";

        let (_remaining, tournament) = parse_tournament(input).unwrap();

        assert_eq!(tournament.len(), 1);

        assert_eq!(tournament[0].choice, Rps::SCISSORS);
        assert_eq!(tournament[0].result(), Result::LOSS);
        assert_eq!(tournament[0].score(), 3); // 3(Scissors) + 0(Draw) = 3
    }
    #[test]
    fn test_score_win() {
        let input = "A Y\r\n";

        let (_remaining, tournament) = parse_tournament(input).unwrap();

        assert_eq!(tournament.len(), 1);

        assert_eq!(tournament[0].choice, Rps::PAPER);
        assert_eq!(tournament[0].result(), Result::WIN);
        assert_eq!(tournament[0].score(), 8); // 2(Paper) + 6(win) = 8
    }
}

#[cfg(test)]
mod tests_prediction {
    use super::*;

    #[test]
    fn test_prediction() {
        let input = "A X\r\n";

        let (_remaining, prediction) = parse_prediction(input).unwrap();

        assert_eq!(prediction.len(), 1);

        assert_eq!(prediction[0].opponent, Rps::ROCK);
        assert_eq!(prediction[0].target, Result::LOSS);
        assert_eq!(prediction[0].choice(), Rps::SCISSORS);
        assert_eq!(prediction[0].score(), 3); // 3(Scissors) + 0(Loss) = 3
    }
}
