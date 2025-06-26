# Given two sequences X = x1, x2 ... xm and Y = y1, y2 ... yn, find a maximum-length sequence Z = z1, z2 ... zk such that:
# Z is a subsequence of X, and Z is a subsequence of Y
# Note: once you use up an element in a sequence you can't reuse

def lcs() -> list[str]:
	x:list[str] = list[str](input("enter 1st sequence\n"))
	y:list[str] = list[str](input("enter 2nd sequence\n"))
	print(x, "\n")
	print(y, "\n")
	lcs:list[str] = x + y # TODO: get actual lcs
	return lcs


def main ():
	print ("Result: ", lcs())

if __name__ == "__main__":
    main()
