# estimate_pi
Estimates pi by simulating dart board tosses

By Ryder Dale Walton
Solves problem 5.2 from Introduction to Parallel Programming by Peter Pacheco
The solution works. I did not do extensive robustness testing, so there are no issues that I am aware of outside of the obvious. 
Some obvious issues include: 
1. I did not add extensive error checking on the input, so I know if the user inputs a valuable other 
an integer, the program will error out.
2. I know that OpenMP is defined on my computer, so I did not surround it with preprocessor checks. This could cause a portability problem.
I tested in a Windows 10 environment using CLion.
