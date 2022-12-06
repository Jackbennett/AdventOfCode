use std::{fs, path};

pub mod elves;
pub mod rps_tournament;

fn main() {
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

    let file_rps_tourny = fs::read_to_string(path::Path::new("./input/Rock_Paper_Scissors.txt"))
        .expect("Missing Day 2 Input File");

    println!();

    let (_, tournament) = rps_tournament::parse_tournament(&file_rps_tourny).unwrap();

    let total_to_plan: usize = tournament.iter().map(|t| t.score()).sum();

    println!(
        "(Day 2a) Tournament Scores: {} if all goes to plan",
        total_to_plan
    );

    let (_, prediction) = rps_tournament::parse_prediction(&file_rps_tourny).unwrap();
    let total_predicted: usize = prediction.iter().map(|t| t.score()).sum();
    println!(
        "(Day 2b) Predicted outcome scores: {} if all goes to plan",
        total_predicted
    );
}
