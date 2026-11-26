package satsolver

Lit :: distinct i32 // each value is a var and its - is its negation/inverse

Clause :: []Lit // clause is just array of lits + array len (for now, can be more later) (everything in this array is or'ed)

CNF :: struct {
	num_vars, num_clauses: u32,
	clauses:               []Clause, // everything in this array is and'ed
}

Solution :: []bool

main :: proc() {
	// fmt.println("What's the clause?")
	// a := read_clause()
	solution: Solution = sat_solve(a, b)
}

sat_solve :: proc(a, b: string) -> (solution: Solution) {
	return solution
}
