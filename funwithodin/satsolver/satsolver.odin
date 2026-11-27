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
		filepath = filepath,
		newlines = 1,
	}

	file_contents, file_read_err := os.read_entire_file_from_path(filepath, context.temp_allocator)
	ensure(file_read_err == nil, fmt.tprint("Error reading cnf file:", file_read_err))
	l.contents = file_contents

	clauses: [dynamic]Clause
	current: [dynamic]Lit
	defer delete(current)

	// c is a comment until newline, p is the problem line (p cnf VARS CLAUSES),
	// and 0 marks the end of a clause (not the end of a line).
	for !cnf_lexer_at_end(&l) {
		cnf_lexer_skip_whitespace(&l)
		if cnf_lexer_at_end(&l) { break }

		switch l.contents[l.idx] {
		case 'c', 'C': for !cnf_lexer_at_end(&l) && l.contents[l.idx] != '\n' {
					cnf_lexer_advance(&l)
				}
		case 'p', 'P':
			cnf_lexer_advance(&l) // consume 'p'
			cnf_lexer_skip_whitespace(&l)
			cnf_lexer_consume_byte(&l, 'c')
			cnf_lexer_consume_byte(&l, 'n')
			cnf_lexer_consume_byte(&l, 'f')
			l.vars = u32(cnf_lexer_scan_int(&l))
			l.clauses = u32(cnf_lexer_scan_int(&l))
		case:
			num := cnf_lexer_scan_int(&l)

			if num == 0 {
				clause := make([]Lit, len(current))
				copy(clause, current[:])
				append(&clauses, clause)
				clear(&current)
				l.clause_idx += 1
			} else {
				append(&current, Lit(num))
			}
		}
	}

	ensure(u32(len(clauses)) == l.clauses, fmt.tprintf("expected %d clauses, got %d", l.clauses, len(clauses)))

	formula = clauses[:]
	return
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

cnf_lexer_at_end :: #force_inline proc(l: ^CNFLexer) -> bool { return l.idx >= u32(len(l.contents)) }

cnf_lexer_skip_whitespace :: #force_inline proc(l: ^CNFLexer) {
	for !cnf_lexer_at_end(l) {
		switch l.contents[l.idx] {
		case ' ', '\t', '\r', '\n': cnf_lexer_advance(l)
		case: return
		}
	}
}

cnf_lexer_advance :: #force_inline proc(l: ^CNFLexer) {
	if cnf_lexer_at_end(l) { return }
	if l.contents[l.idx] == '\n' { l.newlines += 1 }
	l.idx += 1
}

cnf_lexer_consume_byte :: #force_inline proc(l: ^CNFLexer, expected_byte: byte) {
	curr_byte: byte
	if !cnf_lexer_at_end(l) { curr_byte = l.contents[l.idx] }
	if curr_byte == expected_byte { cnf_lexer_advance(l) } else {
		cnf_lexer_panic(l, fmt.tprintf("Found '%r' expected '%r'", rune(curr_byte), rune(expected_byte)))
	}
}

cnf_lexer_scan_int :: #force_inline proc(l: ^CNFLexer) -> int {
	cnf_lexer_skip_whitespace(l)

	string_start := l.idx
	if !cnf_lexer_at_end(l) && (l.contents[l.idx] == '-' || l.contents[l.idx] == '+') { cnf_lexer_advance(l) }

	digits_start := l.idx
	for !cnf_lexer_at_end(l) && l.contents[l.idx] >= '0' && l.contents[l.idx] <= '9' { cnf_lexer_advance(l) }
	cnf_lexer_ensure(l, l.idx > digits_start, "Expected digits")

	num_string := string(l.contents[string_start:l.idx])
	scanned_int, conv_ok := strconv.parse_int(s = num_string, base = 10)
	cnf_lexer_ensure(l, conv_ok, fmt.tprintf("Error converting string %s to num", num_string))
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
