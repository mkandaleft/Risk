# Risk
The project is organized as such:
- src folder for .cpp source code files
- include for all .h header files
- AllHeaders.h contains all header files to avoid redundancy (If you add a header file, please include it here also)
- obj folder is for compiled code
- Driver contains main(), maybe we can also put it in src/
- testing is for testing files, not sure yet how to use it
- myprogram is executable file

The Hand, Order, OrderList and Territory classes are practice versions to test Player class, feel free to change them. For any questions, let me (Mark) know (:

For now we will work with PULL and branching to avoid conflicts.

Here is the procedure as a reminder:
1) Checkout to main branch (Go to main branch)
2) Do Git PULL (Takes content of main branch and puts it in local copy of main)
3) Do Git CHECKOUT to new branch (Creates copy of main branch)
4) Work on changes and commit
5) PUSH changes (Puts content of changed local copy onto branch)
6) Do PULL REQUEST on Github (Checks for conflicts & requests review before merging back to main)
7) Delete branch (Avoids not working starting from main)
