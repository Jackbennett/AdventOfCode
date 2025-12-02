fn main() {
    let input = include_str!("../../input.txt");
    let ans = challenge(input);

    println!("Day 2 Part 2, {}", ans)
}

fn parse(i: &str) -> Vec<u64> {
    let r: Vec<u64> = i
        .split(',')
        .map(|range| {
            range
                .split('-')
                .map(|s| s.parse::<u64>().unwrap())
                .collect()
        })
        .flat_map(|range: Vec<u64>| range[0]..=range[1])
        .collect();

    r
}

fn check_invalid(id: &str) -> Option<u64> {
    if id.len() <= 1 {
        return None;
    }
    let mut size = id.len() / 2;

    while size > 0 {
        let compare: Vec<char> = id.chars().collect();
        // println!("compare {:?} with {}", &compare[..size], id);
        if compare.chunks(size).all(|c| *c == compare[..size]) {
            return Some(id.parse::<u64>().unwrap());
        }
        size -= 1;
    }

    None
}

fn challenge(input: &str) -> u64 {
    let maybe_ids = parse(input);

    let invalids: u64 = maybe_ids
        .iter()
        .filter_map(|v| check_invalid(&v.to_string()))
        .sum();

    invalids
}

#[cfg(test)]
mod tests {
    use super::*;
    const EXAMPLE: &str = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";

    #[test]
    fn expect_found() {
        assert_eq!(check_invalid("11"), Some(11));
        assert_eq!(check_invalid("22"), Some(22));
        assert_eq!(check_invalid("1010"), Some(1010));
        assert_eq!(check_invalid("1188511885"), Some(1188511885));
        assert_eq!(check_invalid("222222"), Some(222222));
        assert_eq!(check_invalid("446446"), Some(446446));
        assert_eq!(check_invalid("38593859"), Some(38593859));
    }

    #[test]
    fn expect_empty() {
        // assert_eq!(parse().iter().map(|v| check_invalid(&v.to_string())), None)
    }

    #[test]
    fn expect_many() {
        let seq = parse("11-22");
        println!("{:?}", seq);
        assert_eq!(
            seq.into_iter()
                .filter_map(|v| check_invalid(&v.to_string()))
                .collect::<Vec<u64>>(),
            vec![11, 22]
        )
    }

    #[test]
    fn expect_many_more() {
        let seq = parse("96-115");
        println!("{:?}", seq);
        assert_eq!(
            seq.into_iter()
                .filter_map(|v| check_invalid(&v.to_string()))
                .collect::<Vec<u64>>(),
            vec![99, 111]
        )
    }

    #[test]
    fn splits() {
        let seq = parse("998-1012");

        println!("{:?}", seq);

        let a: Vec<u64> = seq
            .iter()
            .filter_map(|v| check_invalid(&v.to_string()))
            .collect();

        println!("{:?}", a);

        assert_eq!(a.iter().sum::<u64>(), 2009)
    }

    #[test]
    fn clue() {
        assert_eq!(challenge(EXAMPLE), 4174379265)
    }
}
