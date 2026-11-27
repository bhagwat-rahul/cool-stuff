/* SAT solver for CNF (conjunctive normal form) sat solving
// this has variables (allowed symbols Ai ... An), literals (instances of vars with polarity i.e. negation)
// Clauses (literal's or'ed together), and Formula's (Clauses And'ed together)
// Usually formatted according to the DIMACS spec (competition format)
*/
package satsolver

import "core:fmt"
import "core:mem"
import "core:mem/virtual"
import "core:os"
import "core:strconv"

Lit :: distinct i32 // i32 so we can account for negation (a diff way instead of using lower bit for neg'd or not)
Clause :: []Lit // everything in this array is or'ed
Formula :: []Clause // everything in this array is and'ed
Solution :: []bool

sat_solve :: proc(formula: Formula) -> (solution: Solution = nil) {
	return solution
}

main :: proc() -> int {
	ensure(len(os.args) >= 2, "Please provide a filepath to a cnf file")
	cnf := read_dimacs_cnf_problem_file(os.args[1])
	solution := sat_solve(cnf)
	if solution == nil {
		fmt.println("UNSAT")
		return 20
	} else {
		fmt.println(solution)
		return 10
	}
	return 0 // 0 is unknown (1 or other non-zero is error, out of memory etc.)
}

/* //////////////////////////////////////////////////////////////////////////////////////
// Begin utils
*///////////////////////////////////////////////////////////////////////////////////////

// read a dimacs cnf formatted file and return clauses from it
read_dimacs_cnf_problem_file :: proc(filepath: string) -> (formula: Formula = {}) {
	l := CNFLexer {
		filepath = filepath,
		contents = {},
		idx      = 0,
		newlines = 0,
	}
	file_contents, file_read_err := os.read_entire_file_from_path(filepath, context.temp_allocator)
	ensure(file_read_err == nil, fmt.tprint("Error reading cnf file:", file_read_err))
	l.contents = file_contents

	// iterate over the file, c is a comment until newline, p is problem statement (p NUM_VARS NUM_CLAUSES), 0 marks clause end
	for {
		byte := l.contents[l.idx]
		switch byte {
		case 'c':
			for l.contents[l.idx] != '\n' { l.idx += 1 }
			l.idx += 1 // consume \n
		case 'p':
			cnf_lexer_skip_newlines_whitespace(&l)
			vars: int = cnf_lexer_scan_int(&l)
			cnf_lexer_skip_newlines_whitespace(&l)
			clauses: int = cnf_lexer_scan_int(&l)
			cnf_lexer_skip_newlines_whitespace(&l)
		case '0' ..< '9':
			num := cnf_lexer_scan_int(&l)
			for num != 0 {
				// append num to clause
				num = cnf_lexer_scan_int(&l)
			}
		case: panic("Unexpected byte")
		}
	}

	return formula
}

// write out solution in DIMACS output format (sat competition format)
write_dimacs_cnf_solution_file :: proc(filepath: string, solution: Solution) -> (err: os.Error = nil) {
	file_bytes: []byte
	// TODO(rahul): construct solution into bytes for streamout
	err = os.write_entire_file_from_bytes(filepath, file_bytes)
	return err
}

CNFLexer :: struct {
	filepath: string,
	contents: []byte,
	idx:      u32,
	newlines: u32,
}

cnf_lexer_skip_newlines_whitespace :: #force_inline proc(l: ^CNFLexer) {
	c := l.contents[l.idx]
	for c == ' ' || c == '\n' || c == '\t' { l.idx += 1 }
}

cnf_lexer_consume_byte :: #force_inline proc(l: ^CNFLexer, byte: byte) {
	if l.contents[l.idx] == byte { l.idx += 1 } else { panic("Unexpected byte") }
}

cnf_lexer_scan_int :: #force_inline proc(l: ^CNFLexer) -> int {
	string_start := l.idx
	for l.contents[l.idx] != ' ' { l.idx += 1 }
	string_end := l.idx
	scanned_int, int_err := strconv.parse_int(s = string(l.contents[string_start:string_end]), base = 10)
	ensure(int_err == false, "Error converting vars string to vars num")
	return scanned_int
}

/* //////////////////////////////////////////////////////////////////////////////////////
// End utils
*///////////////////////////////////////////////////////////////////////////////////////
