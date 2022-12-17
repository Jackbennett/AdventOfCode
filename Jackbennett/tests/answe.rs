/// Final checks to hold answer for future refactoring.
pub use aoc::*;

#[test]
fn answer_day1() {
    let (part_1, part_2) = day1();
    assert_eq!(part_1, 71023);
    assert_eq!(part_2, 206289);
}

#[test]
fn answer_day2() {
    let (part_1, part_2) = day2();
    assert_eq!(part_1, 8890);
    assert_eq!(part_2, 10238);
}

#[test]
fn answer_day3() {
    let part_1 = day3();
    assert_eq!(part_1, 8088);
}

#[test]
fn answer_day4() {
    let (part_1, part_2) = day4();
    assert_eq!(part_1, 487);
    assert_eq!(part_2, 849);
}
