
    // ❌ Invalid character literals
    // Lexer should catch these errors!
    char f = '';        // Empty char literal (INVALID)
    char g = 'AB';      // Too many characters in char literal (INVALID)
    char h = '\xZZ';    // Invalid hex escape sequence (INVALID)
    char i = ' ';       // Space is valid, but test handling

    // ❌ Invalid string literals

    //--------- These Error need to be checked one on one
    string invalid2 = "String with invalid escape \q"; // Unknown escape sequence (INVALID)
    string invalid3 = "This contains a backslash at the end \ "; // Missing escape sequence (INVALID)
    
    
    
    //----------------- These Error need to be checked one on one
    // Wrong Multiline String can disrupt many things(lineNo) - so we will test this alone
    
    string invalid4 = "Line break 
    inside string";  
    // Newline inside string without raw literal (INVALID)
    


    // string invalid5 = "Mismatched \"quotes'; // Mixed quote styles (INVALID)
    // string invalid1 = "Unclosed string;   // Missing closing quote (INVALID)
