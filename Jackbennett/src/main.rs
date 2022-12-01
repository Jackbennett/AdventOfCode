use std::{cmp::Ordering, path::Path, fs, env};

// enum Bearing{
//     INCREASING,
//     DECREASING,
// }

// fn get_bearing(val: i32) -> Option(bearing){
//     if let mut last = val;
//     match last_val {
//         None => None,
//         Some(i32) =>
//         last_val.cmp(&val)
//     }
// }

fn get_bearing(last: i32, current: i32) -> Ordering {
    last.cmp(&current)
}

fn main() {
    let pwd = env::current_dir().expect("Permission error");
    println!("pwd:\n{}", pwd.display());
    let file  = fs::read_to_string(Path::new("./input/1/measurements.txt"))
            .expect("text input file should exist");
    let mut measurements  = file.lines()
            .filter_map(|str| str.parse::<u32>().ok());

    for n in 0..5 {
        println!("Measurement ({n}): {}", measurements.next().unwrap());
    }
        println!("...Top 5");
    // let read_iter = readings.into_iter().tuple_windows().map((||) get_bearing);

    println!("Hello, world!");
}

// #[test]
// fn known_increasing() {
// const readings: [i32; 10] = [199, 200, 208, 210, 200, 207,240, 269,260,263];
//     readings.map(f)
// }

#[test]
fn tuples(){
    let mut iter = 1..5;

    assert_eq!(Some((1, 2)), iter.next_tuple());
    assert_eq!(Some((2, 3)), iter.next_tuple());
}
