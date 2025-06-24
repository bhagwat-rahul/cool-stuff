def josephus (n: int, k: int) -> int:
	people = list(range(n))
	while len(people) > 1:
		for i in range (0,len(people)):
			if (i % k == 0):
				people.pop(i)
				print ("removing ", i)
				n = n - 1

def main ():
	peoplenum = int(input("how many people?\n"))
	knum      = int(input("remove at what offset?\n"))
	josephus(n = peoplenum, k = knum)

if __name__ == "__main__":
    main()

