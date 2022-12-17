// not using macros at the moment
// #[macro_use]
// extern crate nom;

use std::{fs, path};

mod backpack;
mod elves;
mod rps_tournament;
mod supply_stack;
mod task_section;

type OneStar = u32;
type TwoStar = (u32, u32);

pub fn day5() {
    let _stacks =
        fs::read_to_string("./input/Elf_Supply_Stacks.txt").expect("Missing Day 5 input file");
}

pub fn day4() -> TwoStar {
    let section_list = fs::read_to_string(path::Path::new("./input/Elf_Section_Assignment.txt"))
        .expect("Missing Day 4 Input File");
    let (_, sections) =
        task_section::parse(&section_list).expect("Parsing error within file format");
    let contained_pairs: u32 = sections
        .iter()
        .filter(|range| task_section::subrange(range))
        .count()
        .try_into()
        .unwrap();
    println!(
        "(Day 4a) {} assignments where one range fully contains the other",
        contained_pairs
    );

    let overlapped_pairs: u32 = sections
        .iter()
        .filter(|asignment| task_section::overlap_range(asignment))
        .count()
        .try_into()
        .unwrap();
    println!(
        "(Day 4b) {} assignments where any overlaps the other",
        overlapped_pairs
    );

    (contained_pairs, overlapped_pairs)
}

pub fn day3() -> OneStar {
    let rucksack_audit = fs::read_to_string(path::Path::new("./input/Elf_Rucksack_Contents.txt"))
        .expect("Missing Day 3 Input File");
    let (_, contents) = backpack::parse_backback_contents(&rucksack_audit).unwrap();
    let duplicates: Vec<u32> = contents
        .iter()
        .filter_map(|pack| backpack::find_common_item(pack))
        .map(|item| backpack::get_item_value(item))
        .collect();

    let score: u32 = duplicates.iter().sum();
    println!(
        "(Day 3a) {} Total priority of duplicate items in Elves rucksacks",
        score
    );

    score
}

pub fn day2() -> TwoStar {
    let file_rps_tourny = fs::read_to_string(path::Path::new("./input/Rock_Paper_Scissors.txt"))
        .expect("Missing Day 2 Input File");

    let (_, tournament) = rps_tournament::parse_tournament(&file_rps_tourny).unwrap();

    let total_to_plan: u32 = tournament.iter().map(|t| t.score()).sum();

    println!(
        "(Day 2a) Tournament Scores: {} if all goes to plan",
        total_to_plan
    );

    let (_, prediction) = rps_tournament::parse_prediction(&file_rps_tourny).unwrap();
    let total_predicted: u32 = prediction.iter().map(|t| t.score()).sum();
    println!(
        "(Day 2b) Predicted outcome scores: {} if all goes to plan",
        total_predicted
    );

    (total_to_plan, total_predicted)
}

pub fn day1() -> TwoStar {
    let file = fs::read_to_string(path::Path::new("./input/Elf_Calories.txt"))
        .expect("text input file should exist");

    let (_, mut expedition) = elves::Expedition::parse(&file).unwrap();

    // Summary information
    println!(
        "Expedition Size: {s}, carrying a total of {e} calories",
        s = expedition.size(),
        e = expedition.energy()
    );

    // Find the Elf carrying the most Calories
    let most_calories = expedition
        .elves
        .iter()
        .map(|e| e.energy())
        .max()
        .unwrap_or(0);
    println!(
        "(Day 1a) {} is the most Calories carried by any single Elf",
        most_calories
    );

    expedition.elves.sort_by(|a, b| b.energy().cmp(&a.energy()));
    let top_3_calories = expedition.elves[0..3]
        .iter()
        .fold(0, |acc, elf| acc + elf.energy());

    println!(
        "(Day 1b) {} Calories carried by the top 3 elves, each being;",
        top_3_calories
    );

    for count in 0..3 {
        println!(
            "\t{}. {} Calories",
            count + 1,
            expedition.elves[count].energy()
        );
    }

    (most_calories, top_3_calories)
}
