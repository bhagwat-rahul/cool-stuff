let inputfile = Bun.file("input.txt");
const input = await inputfile.text();
let lines = input.split("\n");
lines.pop();
let count = 0;
let digitinfo = [];
for (let i = 0; i < lines.length; i++) {
  for (let j = 0; j < lines[i].length; j++) {
    let nums = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"];
    let valid = 0;
    if (nums.includes(lines[i][j])) {
      let buffer = "";
      while (nums.includes(lines[i][j])) {
        buffer += lines[i][j];
        j++;
      }
      digitinfo.push({ i: i, j: j - buffer.length, num: buffer, valid: 1 });
    }
  }
}
for (let x = 0; x < digitinfo.length; x++) {
  for (let z = 0; z <= digitinfo[x].num.length; z++) {
    console.log("checking", lines[digitinfo[x].i][digitinfo[x].j]);
    // TODO: if any checks fail mark as invalid
  }
}
// console.log(digitinfo);
