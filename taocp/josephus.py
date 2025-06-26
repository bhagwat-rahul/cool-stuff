# n people are standing in a circle, numbered 0 to n-1.
# Starting at person 0, every k-th person is eliminated (counting wraps around the circle).
# The process repeats until only one person remains.
# Goal: Find the index (0-based) of the survivor.

def josephus () -> int:
	n:int = int(input("total people?\n"))
	k:int = int(input("removal offset?\n"))
	people: list[int] = list(range(n))
	lastpopped:int = 0
	while len(people) > 1:
		popthis:int = (k + lastpopped - 1) % len(people)
		people.pop(popthis)
		lastpopped = popthis
	return people[0]

def main ():
	print ("Result: ", josephus())

if __name__ == "__main__":
    main()
