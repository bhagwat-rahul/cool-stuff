# n people are standing in a circle, numbered 0 to n-1.
# Starting at person 0, every k-th person is eliminated (counting wraps around the circle).
# The process repeats until only one person remains.
# Goal: Find the index (0-based) of the survivor.

def josephus () -> int:
	n:int = int(input("total people?\n"))
	k:int = int(input("removal offset?\n"))
	people:list[int] = list(range(0, n))
	while len(people) != 1:
		if (k < len(people)):
			print("TODO: Handle case where k less than num")
		else:
			people.pop(k)

	return people[0]

def main ():
	print ("Result: ", josephus())

if __name__ == "__main__":
    main()
