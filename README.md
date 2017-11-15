# Simple Spell Checker Using A Hash Table

This program first reads words from a dictionary file, and inserts them into a hash table.

The dictionary file consists of a list of 62,454 correctly spelled lowercase words, separated by whitespace. The words are inserted into the hash table, with each bucket growing dynamically as necessary to hold all of the incoming data.

After the reading of the dictionary file is complete, the program prompts the user for input. After input is obtained, each word that the user enteres into the program is looked up within the hash table to see if it exists. If the user entered word exists within the hash table, then that word is spelled correctly. If not, a list of possible suggested spelling corrections is displayed to the screen.

