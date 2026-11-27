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

main :: proc() {
	ensure(len(os.args) >= 2, "Please provide a filepath to a cnf file")
	cnf := read_dimacs_cnf_problem_file(os.args[1])
	solution := sat_solve(cnf)
	// write_dimacs_cnf_solution_file()
	if solution == nil { fmt.println("UNSAT") } else { fmt.println(solution) }
}

/* //////////////////////////////////////////////////////////////////////////////////////
// Begin utils
*///////////////////////////////////////////////////////////////////////////////////////

// read a dimacs cnf formatted file and return clauses from it
read_dimacs_cnf_problem_file :: proc(filepath: string) -> (formula: Formula = {}) {
	l := CNFLexer {
		filepath   = filepath,
		contents   = {},
		idx        = 0,
		newlines   = 0,
		vars       = 0,
		clauses    = 0,
		clause_idx = 0,
	}
	file_contents, file_read_err := os.read_entire_file_from_path(filepath, context.temp_allocator)
	ensure(file_read_err == nil, fmt.tprint("Error reading cnf file:", file_read_err))
	l.contents = file_contents

	// iterate over the file, c is a comment until newline, p is problem statement (p NUM_VARS NUM_CLAUSES), 0 marks clause end
	for {
		if l.idx == u32(len(l.contents)) { break }
		byte := l.contents[l.idx]
		switch byte {
		case 'c':
			for l.contents[l.idx] != '\n' { l.idx += 1 }
			cnf_lexer_consume_byte(&l, '\n') // consume \n
		case 'p':
			cnf_lexer_consume_byte(&l, 'p')
			cnf_lexer_skip_newlines_whitespace(&l)
			// have a consume bytes instead of just consume byte
			cnf_lexer_consume_byte(&l, 'c')
			cnf_lexer_consume_byte(&l, 'n')
			cnf_lexer_consume_byte(&l, 'f')
			cnf_lexer_skip_newlines_whitespace(&l)
			l.vars = u32(cnf_lexer_scan_int(&l))
			fmt.printfln("vars %d", l.vars)
			cnf_lexer_skip_newlines_whitespace(&l)
			l.clauses = u32(cnf_lexer_scan_int(&l))
			cnf_lexer_skip_newlines_whitespace(&l)
			fmt.printfln("vars %d clauses %d", l.vars, l.clauses)
		case '0' ..< '9':
			num := cnf_lexer_scan_int(&l)
			cnf_lexer_skip_newlines_whitespace(&l)
			for num != 0 {
				// append num to clause
				num = cnf_lexer_scan_int(&l)
			}
			cnf_lexer_consume_byte(&l, '0')
			l.clause_idx += 1
			cnf_lexer_skip_newlines_whitespace(&l)
		case: cnf_lexer_panic(&l, "Unexpected byte")
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
	filepath:   string,
	contents:   []byte,
	idx:        u32,
	newlines:   u32,
	vars:       u32,
	clauses:    u32,
	clause_idx: u32,
}

cnf_lexer_skip_newlines_whitespace :: #force_inline proc(l: ^CNFLexer) {
	c := l.contents[l.idx]
	for c == ' ' || c == '\n' || c == '\t' {
		l.idx += 1
		c = l.contents[l.idx]
	}
}

cnf_lexer_consume_byte :: #force_inline proc(l: ^CNFLexer, byte: byte) {
	if l.contents[l.idx] == byte { l.idx += 1 } else { cnf_lexer_panic(l, fmt.tprint("Unexpected byte", byte)) }
}

cnf_lexer_scan_int :: #force_inline proc(l: ^CNFLexer) -> int {
	string_start := l.idx
	for l.contents[l.idx] >= '0' && l.contents[l.idx] <= '9' { l.idx += 1 }
	string_end := l.idx
	num_string := string(l.contents[string_start:string_end])
	scanned_int, conv_ok := strconv.parse_int(s = num_string, base = 10)
	cnf_lexer_ensure(l, conv_ok, fmt.tprintf("Error converting string %s to num", num_string))
	l.idx += 1 // move past the int before returning
	return scanned_int
}

cnf_lexer_panic :: #force_inline proc(l: ^CNFLexer, msg: string) {
	panic(fmt.tprintf("%s at byte %d, line %d", msg, l.idx, l.newlines))
}

cnf_lexer_ensure :: #force_inline proc(l: ^CNFLexer, condition: bool, msg: string) {
	ensure(condition, fmt.tprintf("%s at byte %d, line %d", msg, l.idx, l.newlines))
}

/* //////////////////////////////////////////////////////////////////////////////////////
// End utils
*///////////////////////////////////////////////////////////////////////////////////////
