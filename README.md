# String Pattern Matching Algorithm

This program has been developed as part of my B.Sc in Software Engineering program at Jerusalem College of Engineering.

## Background
String pattern matching algorithms are very useful for several purposes, like simple search for a pattern in a text or looking for attacks with predefined signatures.
We will implement a dictionary-matching algorithm that locates elements of a finite set of strings (the "dictionary") within an input text. It matches all patterns "at once", so the complexity of the algorithm is linear in the length of the patterns plus the length of the searched text plus the number of output matches. 
Since all matches are found, there can be a quadratic number of matches if every substring matches (e.g. dictionary = a, aa, aaa, aaaa and input string is aaaa).

The algorithm matches multiple patterns simultaneously, by first constructing a Deterministic Finite Automaton (DFA) representing the patterns set, and then, with this DFA on its disposal, processing the text in a single pass.
Specifically, the DFA construction is done in two phases. First, the algorithm builds a DFA of the patterns set: All the patterns are added from the root as chains, where each state corresponds to one symbol. When patterns share a common prefix, they also share the corresponding set of states in the DFA. 
The edges of the first phase are called forward transitions.  
The edges of the second phase are called failure transitions. These edges deal with situations where, given an input symbol b and a state s, there is no forward transition from s using b. In such a case, the DFA should follow the failure transition to some state s' and take a forward transition from there. This process is repeated until a forward transition is found.

The following DFA was constructed for patterns set {E, BE, BD, BCD, CDBCAB, BCAA}. Solid black edges are forward transitions while red scattered edges are failure transitions. 
L(s) - the label of a state s, is the concatenation of symbols along the path from the root to s.  
d(s) - the depth of a state s, is the length of the label L(s). 
The failure transition from s is always to a state s', whose label L(s') is the longest suffix of L(s) among all other DFA states. 
The DFA is traversed starting from root. When the traversal goes through an accepting state, it indicates that some patterns are a suffix of the input; one of these patterns always corresponds to the label of the accepting state.
Finally, we denote by scan(s,b), the AC procedure when reading input symbol b while in state s; namely, transiting to a new state s' after traversing failure transitions and a forward transition as necessary, and reporting matched patterns in case s'.output != emptyset. scan(s,b) returns the new state s' as an output. 


## The Program
The algorithm operation:
Let K={y1, y2,…,yk}  be a finite set of strings which we shall call keywords and let x be an arbitrary string which we shall call the text string. 

### The behavior of the pattern matching machine is dictated by three functions: 
1.	a goto function g - maps a pair consisting of a state and an input symbol into a state or the message fail.
2.	a failure function f - maps a state into a state, and is consulted whenever the goto function reports fail.
3.	an output function output - associating a set of keyword (possibly empty) with every state.

### Constructing the FSM:
1.	Determine the states and the goto function
2.	Compute the failure function
3.	Output function start at first step, complete at the second step

### Determine the states and the goto function
Input: set of keywords K={y1, y2,…,yk}  
Output: the goto function g

### Compute the failure function
Input: goto function g, and output function output.
Output: failure function f and output function.

### Searching for patterns in a given text.
Input: The DFA, text, 
Output: positions of all matchs, Ptterns and output state. 

### Printing to stdout
While constructing the tree:
  Each time you create new state in the FSM print: "Allocating state i\n"
  Each time you create an edge for the goto function from state i to state j in the FSM print: "i -> a -> j\n", where 'a' is the character that generate this edge. 
  Each time you create an edge for the failure function from state i to state j in the FSM print: "Setting f(i) = j\n"

While searching for patterns in a given text:
For each matched pattern print
  "Pattern: yi, start at: k, ends at: m, accepting state = i"
Where yi  is the matched pattern, k is its start position in the text, m is its end position in the text and i is the index of the accepting state.
