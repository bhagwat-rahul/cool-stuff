let read_lines filename =
let ic = open_in filename in
let rec loop acc =
try
let line = input_line ic in
loop (line :: acc)
with End_of_file ->
close_in ic;
List.rev acc
in
loop []
