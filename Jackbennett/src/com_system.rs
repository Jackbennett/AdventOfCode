use itertools::Itertools;
use nom::{
    InputIter,
    bytes::complete::{tag, take_until}, character::complete::alpha1, combinator::peek,
    error::ErrorKind::TakeUntil, error::ParseError, Err::Failure, IResult,
};

trait ComSystem {
    fn start_of_packet(input: &str) -> usize;
}

// struct Device {

// }

// impl ComSystem for Device {
//   /// first four characters that are all different

// }

fn start_of_packet(input: &str) -> IResult<&str, usize> {
    let (mut _remaining, mut raw_packet) = peek(alpha1)(input)?;
    // let (rest, search_pattern) = take(4_usize)(raw_packet)?;

    let mut found_start: bool;
    let mut iter = raw_packet.as_bytes().windows(4);
    let start_packet = loop {
        match iter.next() {
            Some(window) => {
                if window.iter().all_unique() {
                    break window
                }
            },
            None => Err(Failure(nom::error::Error {
                input: "wat",
                code: TakeUntil,
            })),
        }
    }

    (start_packet, 4)


    // let mut iter =
    // peek(input) // peek the input until start of packet found
}

// fn packet(input: &str) -> IResult<&str, &str> {
//     let (start, position) = start_of_packet(input)?;
//     take_until(start)(input)
// }


#[test]
fn test_start_of_packet() {
    let input = "mjqjpqmgbljsphdztnvjfqwrcgsmlb".to_owned();

    let (frame, start) = start_of_packet(&input).unwrap();

    assert_eq!(
        start, 7,
        "index of first 4 characters without repeat after \"jpqm\""
    );
    assert_eq!(
        frame, "gbljsphdztnvjfqwrcgsmlb",
        "Input contents after the start was detarmined"
    );
}

#[test]
fn test_many_start_of_packet() {
    let (_, start) = start_of_packet("bvwbjplbgvbhsrlpgdmjqwftvncz").unwrap();
    assert_eq!(start, 5);
    let (_, start) = start_of_packet("nppdvjthqldpwncqszvftbrmjlhg").unwrap();
    assert_eq!(start, 6);
    let (_, start) = start_of_packet("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg").unwrap();
    assert_eq!(start, 10);
    let (_, start) = start_of_packet("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw").unwrap();
    assert_eq!(start, 11);
}
