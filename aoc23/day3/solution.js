let inputfile = Bun.file("input.txt");
const input = await inputfile.text();
let lines = input.split("\n");
lines.pop();
let count = 0;
let digitinfo = [];
let nums = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"];
for (let i = 0; i < lines.length; i++) {
  for (let j = 0; j < lines[i].length; j++) {
    if (nums.includes(lines[i][j])) {
      let buffer = "";
      while (nums.includes(lines[i][j])) {
        buffer += lines[i][j];
        j++;
      }
      digitinfo.push({ i: i, j: j - buffer.length, num: buffer, valid: 0 });
    }
  }
}
// Function to check bounds and whether a character is a symbol
function isSymbol(i, j) {
  if (i < 0 || j < 0 || i >= lines.length || j >= lines[i].length) return false;
  const ch = lines[i][j];
  return ch !== "." && !nums.includes(ch);
}

// Now check validity
for (let x = 0; x < digitinfo.length; x++) {
  const { i, j, num } = digitinfo[x];
  let foundSymbol = false;

  for (let offset = 0; offset < num.length; offset++) {
    const ci = i;
    const cj = j + offset;

    const neighbors = [
      [ci - 1, cj], // top
      [ci + 1, cj], // bottom
      [ci, cj - 1], // left
      [ci, cj + 1], // right
      [ci - 1, cj - 1], // top-left
      [ci - 1, cj + 1], // top-right
      [ci + 1, cj - 1], // bottom-left
      [ci + 1, cj + 1], // bottom-right
    ];

    for (const [ni, nj] of neighbors) {
      if (isSymbol(ni, nj)) {
        digitinfo[x].valid = 1;
        foundSymbol = true;
        break;
      }
    }
    if (foundSymbol) break;
  }
}

let validSum = digitinfo
  .filter((d) => d.valid)
  .reduce((acc, d) => acc + Number(d.num), 0);
console.log(validSum);
