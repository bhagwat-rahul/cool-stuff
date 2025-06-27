use std::fs;

fn checkdiags(contents: &str, pattern: &str, lines: usize, llen: usize) -> usize {
    return llen;
}

fn checkvert(contents: &str, pattern: &str, lines: usize, llen: usize) -> usize {
    return llen;
}

fn main() {
    let pattern = "XMAS";
    let reversed: String = pattern.chars().rev().collect();
    let filename = "sample.txt";
    println!("Checking for pattern {} in filename: {}", pattern, filename);
    let contents = fs::read_to_string(filename).expect("Something went wrong reading the file");
    let lines = contents.chars().filter(|&c| c == '\n').count();
    let llen = contents.lines().next().map(|line| line.len()).unwrap_or(0);
    let mut count = 0;
    let fwd = contents.matches(pattern).count();
    let bwd = contents.matches(&reversed).count();
    let diag = checkdiags(&contents, pattern, lines, llen);
    let vert = checkvert(&contents, pattern, lines, llen);
    count = count + fwd + bwd + diag + vert;
    println!("Pattern '{}' occurred {} times", pattern, count);
}
