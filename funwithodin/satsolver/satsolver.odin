package satsolver

import "core:fmt"
import "core:os"

// each value is a var and its - is its negation/inverse
// clause is just array of lits + array len (for now, can be more later) (everything in this array is or'ed)
Lit :: distinct i32
Clause :: []Lit
CNF :: []Clause // everything in this array is and'ed
Solution :: []bool

SampleCNF: CNF : {{322, 4343, 4542}, {1234, 56454}, {4542, -4343}}

main :: proc() {
	ensure(len(os.args) >= 2, "Please provide a filepath to a cnf file")
	cnf := read_cnf_from_dimacs_cnf_file(os.args[1])
	solution := sat_solve(cnf)
	if solution == nil {fmt.println("UNSAT")} else {fmt.println(solution)}
}

// read a dimacs cnf formatted file and return clauses from it
read_cnf_from_dimacs_cnf_file :: proc(filepath: string) -> (cnf: CNF = {}) {
	cnf_contents, file_read_err := os.read_entire_file_from_path(filepath, context.temp_allocator)
	ensure(file_read_err == nil, fmt.tprint("Error reading cnf file:", file_read_err))

	cnf_convert: for byte in cnf_contents {
		switch byte {
		case 'c', 'C': // this is a comment skip it
		case 'p', 'P': // this is the problem line (how many vars, how many clauses)
		case: // file contents
		}
	}
	return cnf
}

sat_solve :: proc(cnf: CNF) -> (solution: Solution = nil) {
	return solution
}
