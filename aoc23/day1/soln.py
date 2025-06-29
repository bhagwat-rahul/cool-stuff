def main():
  count: int = 0
  nums: dict[str, int] = {
    "zero": 0,
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
    "six": 6,
    "seven": 7,
    "eight": 8,
    "nine": 9,
  }
  with open("input.txt", "r") as f:
    document: str = f.read()
  lines: list[str] = document.splitlines()
  for line in lines:
    digits: list[int] = []; i:int = 0;
    for i in range (len(line)):
      if line[i].isdigit():
        digits.append(int(line[i]))
      for word, value in nums.items():
        if line[i:i + len(word)] == word:
          digits.append(value)
    if digits:
      count += digits[0] * 10 + digits[-1]
  print("result is:", count)

if __name__ == "__main__":
  main()
