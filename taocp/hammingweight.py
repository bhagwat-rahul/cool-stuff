# Count the number of 1s in the binary representation of an int

def count_ones(n: int) -> int:
	count:int = 0
	num = bin(n)
	print(n, " in binary is ", num)
	for i in range (2, len(num)):
		if (int(num[i]) == 1):
			count = count + 1
	return count

def main():
	x:int = int(input("what number?\n"))
	print(count_ones(x), " ones in binary format of ", x)

if __name__ == "__main__":
	main()
