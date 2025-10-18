/*
Multi line comments in mzn are like C
% Single line comments start with a percent and go till eol
Programs are declarative, and you don't really need to declare vars before using them.
Order doesn't matter
*/

var 1..3: x; % means that x could be anything between 1 - 3

% all ranges in mzn inclusive of both bounds no exclusive ranges

var 1..4: y; % y anything between 1 - 4
constraint x+y > 2; % x+y needs to be greater than 2
constraint x-y < 1; % x-y needs to be less than 1
solve satisfy; % provide answers for the given constraints (possible vals of x & y in this case)

