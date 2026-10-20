package majority_inverter_graph

// Convert a graph of boolean logic to a graph containing only MAJ(a,b,c) (if 2 of 3 are 1 then out is 1) and inverter (NOT)

/*
Properties of a mig are:-
1. Commutative: MAJ(x,y,z) = MAJ(y,x,z) // permute
2. Majority: MAJ(x,x,y) = x  // if 2 same, 3rd don't care
3. Associativity: MAJ(x,y,MAJ(u,v,x')) = MAJ(x,y,MAJ(u,v,y')) // Relevance
4. Distributive: MAJ(x,y,z) = MAJ( MAJ(x,y,0), MAJ(x,y,1), z )
*/

// Very prone to SIMD parallelism since you can bitpack things and just do shuffles and compares, etc.
