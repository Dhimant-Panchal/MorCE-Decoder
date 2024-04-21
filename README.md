**Overview**

Morse code is a character encoding scheme that encodes text characters as sequences of two values dot (.) and dash (-). We have implemented this data by representing them in a binary tree structure. In a binary tree structure, each node has at most 2 children, referred to as the left child and the right child. In the tree, each node stores the value of an English alphabet letter and data pointers to children’s nodes. We can extract a letter value by accessing its node i.e., by traversing through the binary tree, treating the left branch as a dot, and the right branch as a dash.
  
In our project, the files morse_tree.c and morse_tree.h are responsible for the creation of this data structure and the population of node’s data. 

The files seven_segment.h and seven_segment.c provide a function “seven_segment_show()” which accepts an integer input and displays a corresponding value mapped to that integer on the seven-segment display.

The files parse_input_str.c and parse_input_str.h contain a key function called "binaryToLetter()." This function takes a string of 0s and 1s as input, representing Morse code dots and dashes.Its primary purpose is to return an English alphabet letter.
During execution, the function interprets 0s as dots and 1s as dashes. The input string guides the function's traversal through a binary tree structure. At each step, encountering 0 leads to a move to the left child node, while a 1 prompts a move to the right child node. When the end of the string is reached, the function stops and returns the character value stored in the final node of the binary tree. As an illustrative example, if the function is given the input "0010," it logically translates to "..-." in Morse code, ultimately returning the letter "F."
 
In the file main.c, the main function serves as the core of the program. It utilizes a character array buffer to store 0s and 1s in string format. It starts by displaying a welcome message.
Within an infinite loop, the function continually monitors button presses. Upon detecting a button press, the program calculates the press duration. If the press duration is less than 250ms, a "0" (dot) is added to the buffer. For a duration between 250ms and 400ms, a "1" (dash) is appended, and the corresponding dot or dash is momentarily displayed on the seven-segment display, reflecting the addition to the buffer. If the button is held for over 700ms, an error message is displayed, and the buffer is cleared to receive new inputs.
When the buffer reaches its capacity or there is no button press for 700ms, the "seven_segment_show()" function is invoked. It uses the value derived from offsetting the result of "binaryToLetter()" to display the corresponding English alphabet letter on the seven-segment display. After the display, the buffer is reset, ready to accept new inputs.
During testing, our project consistently displays the appropriate letter for any letter morse code input. Invalid inputs are handled (i.e. empty nodes on the tree like “..--" cause a dash to be shown on the display).

**Challenges Faced**

These are the challenges we faced when developing our project – which we then solved eventually.
•	We initially faced problems with sharing and editing multiple files at a time, so we solved those problems by implementing git version control.
•	When a button was pressed too quickly with little click time, it caused a debounce registering 2 inputs into the buffer. We addressed this by filtering out clicks with a click time under 1ms.
•	Pressing the button while measuring time of no button press caused only to get out of non-click loop, which did not trigger start of time measurement of click time. We solved this problem by introducing state variables.
