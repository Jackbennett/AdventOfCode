use nom::{
    bytes::complete::tag, character::complete::digit1, combinator::map_res, sequence::preceded,
    IResult,
};

pub type Stacks = Vec<Vec<char>>;

#[derive(Debug, PartialEq)]
pub struct DSLMove {
    quantity: usize,
    from: usize,
    to: usize,
}

impl DSLMove {
    fn move_instruction(input: &str) -> IResult<&str, usize> {
        preceded(tag("move "), map_res(digit1, str::parse))(input)
    }
    fn from_instruction(input: &str) -> IResult<&str, usize> {
        preceded(tag(" from "), map_res(digit1, str::parse))(input)
    }
    fn to_instruction(input: &str) -> IResult<&str, usize> {
        preceded(tag(" to "), map_res(digit1, str::parse))(input)
    }

    /// parses key information from: move 3 from 5 to 2
    pub fn parse(input: &str) -> IResult<&str, Self> {
        let (stacks, qty) = Self::move_instruction(input)?;
        let (rest, from) = Self::from_instruction(stacks)?;
        let (none, to) = Self::to_instruction(rest)?;
        Ok((
            none,
            DSLMove {
                quantity: qty,
                // Fix index off-by-one from name that is number
                from: from - 1,
                to: to - 1,
            },
        ))
    }
}

/// Move an amount from the end of one array onto the end of another
pub fn stack_operation(stacks: &mut Stacks, operation: Vec<DSLMove>) {
    for op in operation {
        let drain_start_idx = stacks[op.from].len() - op.quantity;
        let from: Vec<char> = stacks[op.from].drain(drain_start_idx..).rev().collect();
        stacks[op.to].extend(from);
    }
}

pub mod parse {
    use nom::{
        bytes::complete::take_until, character::complete::line_ending, multi::separated_list1,
        IResult,
    };

    /// Finds first instruction and retuns those listed with the context above it.
    fn split_moves_from_context(input: &str) -> IResult<&str, &str> {
        take_until("move")(input)
    }

    pub fn find_instruction<T>(
        input: &str,
        parser: fn(&str) -> IResult<&str, T>,
    ) -> IResult<&str, Vec<T>> {
        match split_moves_from_context(input) {
            Ok((moves, _preset)) => separated_list1(line_ending, parser)(moves),
            Err(err) => Err(err),
        }
    }

    //// I can't figure enough nom/rust to parse this.
    //// TODO;
    ////     Take whole string until row of stack id
    ////     Use id location in string as column for each stack item
    ////     append to stack id each item found at column index.
    // pub fn stack_hints(input: &str) {
    //     // -> IResult<&str, Vec<&str>>
    //     let (moves, (preset, index)) = pair(many1(alt((alpha1, space0)), stack_index))(input);

    //     println!("{:?}\r\n\r\n{:?}\r\n{}", preset, index, moves.len())
    //     // let line = preceded(space1, stack_item)(input);
    // }

    // pub fn stack_index(input: &str) -> IResult<&str, Vec<usize>> {
    //     many1(preceded(space1, map_res(digit1, str::parse)))(input)
    // }
}

// fn parse_stack(input: &str) -> IResult<&str, Vec<usize>> {
//     //     [D]
//     // [N] [C]
//     // [Z] [M] [P]
//     //  1   2   3
//     let populated: Stacks = Vec::new();

//     let (_, preset) = many_till(parse::stack_item, nom::combinator::line_ending);

//     // let stack_buffer = nom::bytes::complete::take_till(parse::stack_index)(input);

//     // for stack in stack_index {
//     //     populated[stack] = Vec::new();
//     //     populated[stack].push(stacks.slice_index(stack))
//     // }

//     // stack_index_parser
// }

pub fn get_stack_preset() -> Stacks {
    vec![
        vec!['B', 'W', 'N'],
        vec!['L', 'Z', 'S', 'P', 'T', 'D', 'M', 'B'],
        vec!['Q', 'H', 'Z', 'W', 'R'],
        vec!['W', 'D', 'V', 'J', 'Z', 'R'],
        vec!['S', 'H', 'M', 'B'],
        vec!['L', 'G', 'N', 'J', 'H', 'V', 'P', 'B'],
        vec!['J', 'Q', 'Z', 'F', 'H', 'D', 'L', 'S'],
        vec!['W', 'S', 'F', 'J', 'G', 'Q', 'B'],
        vec!['Z', 'W', 'M', 'S', 'C', 'D', 'J'],
    ]
}

#[cfg(test)]
mod tests_supply_stacks {
    use super::*;

    fn _get_stack_preset() -> Stacks {
        //     [D]
        // [N] [C]
        // [Z] [M] [P]
        //  1   2   3
        vec![vec!['Z', 'N'], vec!['M', 'C', 'D'], vec!['P']]
    }

    #[test]
    fn test_move_parse() {
        let (nothing, dsl) = DSLMove::parse("move 1 from 9 to 2").unwrap();
        assert_eq!(nothing, "");
        assert_eq!(
            dsl,
            DSLMove {
                quantity: 1,
                from: 8,
                to: 1,
            }
        )
    }
}
