# Given two sequences X = x1, x2 ... xm and Y = y1, y2 ... yn, find a maximum-length sequence Z = z1, z2 ... zk such that:
# Z is a subsequence of X, and Z is a subsequence of Y
# Note: once you use up an element in a sequence you can't reuse

def lcs() -> list[str]:
	x:list[str] = list[str](input("enter 1st sequence\n"))
	y:list[str] = list[str](input("enter 2nd sequence\n"))
	z:list[str] = [] # TODO: get actual lcs
	print(x, "\n")
	print(y, "\n")
	# Let's first get all common elements since the longest possible sequence can be that
	# We just don't know if that *is* the longest sequence due to order
	xset:set[str] = set[str](x)
	yset:set[str] = set[str](y)
	lps:set[str] = xset & yset
	lpslen:int = len(lps)
	z = lcs_recursive(x,y)
	print("uniques in x: ", xset)
	print("uniques in y: ", yset)
	print("unique in xy: ", lps)
	print("max soln len: ", lpslen)
	return z

def lcs_recursive(x: list[str], y: list[str]) -> list[str]:
  if not x or not y:
      return []
  if x[-1] == y[-1]:
      return lcs_recursive(x[:-1], y[:-1]) + [x[-1]]
  else:
      left = lcs_recursive(x[:-1], y)
      right = lcs_recursive(x, y[:-1])
      return left if len(left) > len(right) else right

def main ():
	print ("Soln: ", len(lcs()))

if __name__ == "__main__":
    main()
