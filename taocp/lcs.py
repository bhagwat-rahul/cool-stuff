# Given two sequences X = x1, x2 ... xm and Y = y1, y2 ... yn, find a maximum-length sequence Z = z1, z2 ... zk such that:
# Z is a subsequence of X, and Z is a subsequence of Y
# Note: once you use up an element in a sequence at an index you can't reuse (unless appears multiple times in both)

def lcs() -> list[str]:
	x:list[str] = list[str](input("1st sequence\n"))
	y:list[str] = list[str](input("2nd sequence\n"))
	result: list[str] = []
	m, n = len(x), len(y)
	dp: list[list[int]] = [[0] * (n + 1) for _ in range(m + 1)]
	for i in range(1, m + 1):
		for j in range(1, n + 1):
			if x[i - 1] == y[j - 1]:
				dp[i][j] = dp[i - 1][j - 1] + 1
			else:
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

	p, q = m, n
	while p > 0 and q > 0:
		if x[p - 1] == y[q - 1]:
			result.append(x[p - 1])
			p -= 1
			q -= 1
		elif dp[p - 1][q] >= dp[p][q - 1]:
			p -= 1
		else:
			q -= 1

	return result[::-1]

def main ():
	print ("soln: ", len(lcs()))

if __name__ == "__main__":
    main()
