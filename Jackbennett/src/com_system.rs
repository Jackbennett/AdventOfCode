use nom::IResult;

trait ComSystem {
    fn start_of_packet(input: &str) -> usize;
}

// struct Device {

// }

// impl ComSystem for Device {
//   /// first four characters that are all different

// }

fn start_of_packet(input: &str) -> IResult<&str, usize> {
    let (rest, search_pattern) = nom::bytes::complete::take(4_usize)(input)?;
    let
}

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
