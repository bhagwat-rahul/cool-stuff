def main():
  with open("sample.txt", "r") as f:
    input: str = f.read()

  lines:list[str] = input.splitlines()
  steps:int = 0
  for i in range (len(input)):
    ...

def getNeighbors(i, j):
  return [
    [i - 1, j],      # top
    [i + 1, j],      # bottom
    [i, j - 1],      # left
    [i, j + 1],      # right
  ]

if __name__ == "__main__":
  main()
