#include "includes/morse_tree.h"
#include "includes/parse_input_str.h"
#include <string.h>
#include <stdio.h>
// Initialise a string of length 5 (unnecessarily large) for use in comparisons with any morse signal length
const char null_str[5] = "";

char binaryToLetter(struct node rootNode, char str[]) {
    // Temporary variable used in visiting the nodes on the tree.
    struct node currentNode = rootNode;

    // Invalid characters are checked for at this point to avoid needlessly visiting the tree.
    if(strcmp(str, "0011") == 0 || strcmp(str, "1110") == 0 ||strcmp(str, "1111") == 0 ||strcmp(str, "0101") == 0) {
        return '-';
    }

    // Loop through the tree for a definite count given by the length of the input string.
    for (int i = 0; i < strlen(str); i++) {   
        // Left child nodes represent dots as does an ASCII zero in the input string so the temporary
        // currentNode variable is set to its own left node.
        if (str[i] == '0') {
            currentNode = *currentNode.left;
        }
        // Right child nodes represent dashes as does ASCII one in the input string so currentNode is
        // set to its right node.
        else if (str[i] == '1') {
            currentNode = *currentNode.right;
        }
        // Null characters used to show end of input even within a longer string due to the requirement of
        // having a differing length depending on the character.
        else if (str[i] == '\0') {
            break;
        }
    }
    return currentNode.letter;
}