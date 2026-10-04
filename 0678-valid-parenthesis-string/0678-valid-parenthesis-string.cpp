class Solution {
public:
    bool checkValidString(string s) {
        int minOpen = 0;
        int maxOpen = 0;

        for (char ch : s) {
            if (ch == '(') {
                minOpen++;
                maxOpen++;
            }
            else if (ch == ')') {
                minOpen--;
                maxOpen--;
            }
            else { 
                minOpen--;
                maxOpen++; 
            }

            if (maxOpen < 0) {
                return false;
            }


            minOpen = max(minOpen, 0);
        }

        return minOpen == 0;
    }
};