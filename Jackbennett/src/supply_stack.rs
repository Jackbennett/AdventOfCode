macro_rules! move_stack {
    // `$x` followed by at least one `$y,`
    (move $qty:literal from $a:literal to $b:literal) => {
        println!("{} more items in stack({}) from stack({})", $qty, $b, $a);
    };
}

#[test]
fn test_marco_dsl() {
    move_stack! {move 1 from 2 to 1};
}
