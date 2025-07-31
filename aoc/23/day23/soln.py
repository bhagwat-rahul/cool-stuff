def main():
  with open("sample.txt", "r") as f:
    input: str = f.read()
  lines:list[str] = input.splitlines()
  steps:int = 0

def dfs(x:int = 0, y:int = 0, steps:int = 0):
  ...

if __name__ == "__main__":
  main()
