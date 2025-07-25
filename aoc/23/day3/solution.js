let inputfile = Bun.file("input.txt");
const input = await inputfile.text();
let lines = input.split("\n");
lines.pop();
let count = 0;
let digitinfo = [];
let gearinfo = [];
let gcount = 0;
let nums = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"];
for (let i = 0; i < lines.length; i++) {
  for (let j = 0; j < lines[i].length; j++) {
    if (lines[i][j] == "*") {
      gearinfo.push({ i: i, j: j });
    }
    if (nums.includes(lines[i][j])) {
      let buffer = "";
      while (nums.includes(lines[i][j])) {
        buffer += lines[i][j];
        j++;
      }
      digitinfo.push({ i: i, j: j - buffer.length, num: buffer, valid: 0 });
      j--;
    }
  }
}
for (let x = 0; x < digitinfo.length; x++) {
  const { i, j, num } = digitinfo[x];
  let foundSymbol = false;
  for (let offset = 0; offset < num.length; offset++) {
    const ci = i;
    const cj = j + offset;
    for (const [ni, nj] of getNeighbors(ci, cj)) {
      if (isSymbol(ni, nj)) {
        digitinfo[x].valid = 1;
        foundSymbol = true;
        break;
      }
    }
    if (foundSymbol) break;
  }
}
for (let gear in gearinfo) {
  const gi = gearinfo[gear].i;
  const gj = gearinfo[gear].j;
  gcount += gearRatio(gi, gj);
}
let validSum = digitinfo
  .filter((d) => d.valid)
  .reduce((acc, d) => acc + parseInt(d.num), 0);
console.log(validSum);
console.log(gcount);

function getNeighbors(i, j) {
  return [
    [i - 1, j], // top
    [i + 1, j], // bottom
    [i, j - 1], // left
    [i, j + 1], // right
    [i - 1, j - 1], // top-left
    [i - 1, j + 1], // top-right
    [i + 1, j - 1], // bottom-left
    [i + 1, j + 1], // bottom-right
  ];
}

function isSymbol(i, j) {
  if (i < 0 || j < 0 || i >= lines.length || j >= lines[i].length) return false;
  const ch = lines[i][j];
  return ch !== "." && !nums.includes(ch);
}

function gearRatio(i, j) {
  const touching = digitinfo
    .filter((d) =>
      getNeighbors(i, j).some(
        ([ni, nj]) => d.i === ni && nj >= d.j && nj < d.j + d.num.length,
      ),
    )
    .map((d) => parseInt(d.num));
  return touching.length === 2 ? touching[0] * touching[1] : 0;
}
