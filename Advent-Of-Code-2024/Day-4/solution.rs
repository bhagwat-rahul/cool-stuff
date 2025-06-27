use std::fs;

fn main() {
    let pattern = "XMAS";
    let reversed: String = pattern.chars().rev().collect();
    let filename = "input.txt";
    let mut count = 0;
    println!("Checking for pattern {} in filename: {}", pattern, filename);
    let contents = fs::read_to_string(filename).expect("Something went wrong reading the file");
    let lines = contents.lines().count();
    let llen = contents.lines().next().map(|line| line.len()).unwrap_or(0);
    println!("{} lines with length {}", lines, llen);
    let grid: Vec<Vec<char>> = contents
        .lines()
        .map(|line| line.chars().collect())
        .collect();
    let fwd = contents.matches(pattern).count();
    let bwd = contents.matches(&reversed).count();
    let vert = vert(&grid, lines, llen);
    let diag = diag(&grid, lines, llen);
    count = count + fwd + bwd + vert + diag;
    println!(
        "Pattern '{}' occurred {} times, {} forwards, {} backwards, {} vertical, {} diagonal",
        pattern, count, fwd, bwd, vert, diag
    );
}

fn vert(grid: &Vec<Vec<char>>, lines: usize, llen: usize) -> usize {
    let mut vert = 0;
    for i in 0..lines - 3 {
        for j in 0..llen {
            if grid[i][j] == 'X'
                && grid[i + 1][j] == 'M'
                && grid[i + 2][j] == 'A'
                && grid[i + 3][j] == 'S'
            {
                vert += 1;
            }
            if grid[i][j] == 'S'
                && grid[i + 1][j] == 'A'
                && grid[i + 2][j] == 'M'
                && grid[i + 3][j] == 'X'
            {
                vert += 1;
            }
        }
    }
    return vert;
}

fn diag(grid: &Vec<Vec<char>>, lines: usize, llen: usize) -> usize {
    let mut diag = 0;
    for i in 0..lines - 3 {
        for j in 0..llen - 3 {
            if grid[i][j] == 'X'
                && grid[i + 1][j + 1] == 'M'
                && grid[i + 2][j + 2] == 'A'
                && grid[i + 3][j + 3] == 'S'
            {
                diag += 1;
            }
            if grid[i][j] == 'S'
                && grid[i + 1][j + 1] == 'A'
                && grid[i + 2][j + 2] == 'M'
                && grid[i + 3][j + 3] == 'X'
            {
                diag += 1;
            }
        }
    }
    for i in 0..lines - 3 {
        for j in 3..llen {
            if grid[i][j] == 'X'
                && grid[i + 1][j - 1] == 'M'
                && grid[i + 2][j - 2] == 'A'
                && grid[i + 3][j - 3] == 'S'
            {
                diag += 1;
            }
            if grid[i][j] == 'S'
                && grid[i + 1][j - 1] == 'A'
                && grid[i + 2][j - 2] == 'M'
                && grid[i + 3][j - 3] == 'X'
            {
                diag += 1;
            }
        }
    }
    return diag;
}
