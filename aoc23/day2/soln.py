def main():
  with open("input.txt", "r") as f:
    document: str = f.read()
  games: list[str] = document.splitlines()
  count:int = 0
  power:int = 0
  valid:dict[str, int] = {
    "red"  : 12,
    "green": 13,
    "blue" : 14,
  }
  for index, game in enumerate(games):
    lred:int = 0; lgreen:int = 0; lblue:int = 0
    yes:int | None = 1
    lc:list[str] = game.split(":")
    parts:list[str] = lc[-1].split(";")
    for part in parts:
      pairs = part.split(", ")
      for pair in pairs:
        pair = (pair.lstrip())
        num, color = pair.split(" ")
        if color == "red" and (lred == 0 or int(num) > lred): lred = int(num)
        elif color == "green" and (lgreen == 0 or int(num) > lgreen): lgreen = int(num)
        elif color == "blue" and (lblue == 0 or int(num) > lblue): lblue = int(num)
        if int(num) > valid.get(color, 0):
          yes = None
    if yes:
      count += index+1
    power += lred * lgreen * lblue
  print(count)
  print(power)

if __name__ == "__main__":
  main()
