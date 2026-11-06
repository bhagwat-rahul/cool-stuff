-- print hello world
def main : IO Unit := IO.println "Hello, world!"

-- define a func
def add1 (n : Nat) : Nat := n + 1

-- evaluate expression output
#eval add1 7
