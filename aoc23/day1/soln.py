def main():
  count:int = 0
  with open("input.txt", "r") as f:
    document: str = f.read()
  lines:list[str] = document.splitlines()
  for line in lines:
    d1:int|None = None; d2:int|None = None;
    for letter in line:
      if letter.isdigit():
        if d1 is not None:
          d2 = int(letter)
        else:
          d1 = int(letter)
    if d1 is not None and d2 is not None:
       count+= d1*10+d2
    if d1 is not None  and  d2 is None:
       count+= d1*10+d1

  print("result is:", count)

if __name__ == "__main__":
	main()
