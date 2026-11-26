package satsolver

// each value is a var and its - is its negation/inverse
// clause is just array of lits + array len (for now, can be more later) (everything in this array is or'ed)
Clause :: []distinct i32 // []Lit where Lit is distinct i32
CNF :: []Clause // everything in this array is and'ed
Solution :: []bool

main :: proc() {
	// fmt.println("What's the clause?")
	cnf: CNF
	// cnf = read_clause()
	solution: Solution = sat_solve(cnf)
	if solution == nil {fmt.println("UNSAT")} else {fmt.println(solution)}
}

sat_solve :: proc(cnf: CNF) -> (solution: Solution) {
	return solution
}
