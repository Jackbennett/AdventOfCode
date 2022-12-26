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

#[test]
fn answer_day5() {
    let part_1 = day5();
    // TODO: Refactor day1 answer to repeatedly get day 2.
    assert_ne!(part_1, "LLWJRBHVZ".to_owned()); // oops this is part 2 - this is wrong - you didn't move 1 stack item at a time.
    assert_eq!(part_1, "MQSHJMWNH".to_owned()); // part one by rev() the Drain iterator
}
