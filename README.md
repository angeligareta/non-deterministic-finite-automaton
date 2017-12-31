# Non-Deterministic Finite Automaton
Implementation of a NFA in C++. As opposed to a DFA, where of its transitions is uniquely determined by its source state and input symbol and
reading an input symbol is required for each state transition. The NFA does not obey these restrictions.

The program can read, and show a NFA. Besides it can show the dead states, see if the NFA is a DFA and analyze a string to see if it belongs to the DFA.

## Author
Ángel Luis Igareta Herráiz

## INDEX
* [Usage](#usage)
* [License](#license)

## Usage
To start the program first you have to compile the source with MakeFile. After that you can start it executing:

```
.bin/nfa
```
Once the program is started it will show a menu with 6 options:

    ⬤ Option 0: Exit
    ⬤ Option 1: Read NFA 
    ⬤ Option 2: Show NFA
    ⬤ Option 3: Show death states
    ⬤ Option 4: Is DFA?
    ⬤ Option 5: Analyze String
    
Finally in the test folder there is an example of NFA syntax.

## License
The Mit License.
