def main():
  with open("input.txt", "r") as f:
    document: str = f.read()
  games: list[str] = document.splitlines()
  count:int = 0
  valid:dict[str, int] = {
    "red"  : 12,
    "green": 13,
    "blue" : 14,
  }
  for index, game in enumerate(games):
    yes:int | None = 1
    lc:list[str] = game.split(":")
    parts:list[str] = lc[-1].split(";")
    for part in parts:
      pairs = part.split(", ")
      for pair in pairs:
        pair = (pair.lstrip())
        num, color = pair.split(" ")
        if int(num) > valid.get(color, 0):
          yes = None
    if yes:
      count += index+1
  print(count)

if __name__ == "__main__":
  main()
