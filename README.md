Instructions
This signature assignment is a  group project. Teamwork and collaboration will be essential in completing this assignment. Students should try to form their own team.  All team members must remain engaged and actively participate in the group meetings and communications while contributing  to the design and implementation of the solution. Each group must consist of no more than three members. You may contact other classmates and form your own three member group. Otherwise, your instructor will assign students to groups. One team member should act as a lead and inform the instructor of the formation of the group. In this Signature Assignment, you will demonstrate your mastery of C++ concepts covered in the course. (100 points for the programming) 

Please note that each member will be peer evaluated by the other team members according to the following team building criteria . The average peer evaluation scores from the other team members will be used as your teamwork grade. (50 points for peer evaluation). 


Problem:

Develop code for classes to read and analyze binary data. 

Write a function named selection_sort() which takes two parameters, a integer pointer and an integer size.  Add code to implement a selection sort algorithm.  Add any needed functions to support the selection sort. 

Write a helper function named binary_search that takes three parameters, the first is an integer array, the second is the searched for value, and the third is the array size.  This function calls the recursive function and passes the array, the search value, the starting index, and the last index. 

Write a recursive function named binary_search_recursive() which takes four parameters passed from the helper function.  The first is an integer pointer representing the array of values, the second is an integer representing the value to be searched for, the third is an integer for the starting index, and the fourth is an integer for the ending index. 

Add a new class named SearchAnalyzer which subclasses Analyzer and implements the analyze() method.  Use the override keyword appropriately.  The constructor should first call the selection_sort() function, passing the integer array and the size.  In the analyze() method, generate 100 random integer values in the range of 0 to 999 and use the binary_search() function to see if that value exists in the data.  Count the number of found values and return the count in a std::string. 

Modify the StatisticsAnalyzer analyze() method to call the selection_sort() function.  Alter the computation of the minimum and maximum values considering that the array is sorted.  Add functionality to implement the median and mode averages using the sorted data.  The median is the exact middle value (if there are an odd number of elements) and the mean of the two middle values (if there are an even number of elements).  The mode is the most frequently occurring value; if more than one value occurs with this frequency, pick the first one. 

Write and debug the above parts ensuring that each part works, that it compiles with no errors or warnings, and that the results look like the Part4 output.  Note: your values will vary, although most of the results should be similar. 

Use these function and class headers: 

Function and class declarations in C++ including binary_search_recursive, binary_search, createBinaryFile, selection_sort, and writeBinary functions, followed by the BinaryReader class with methods to read and retrieve binary file data.

C++ class definitions for Analyzer and DuplicatesAnalyzer. Analyzer includes a constructor, destructor, cloneValues method, and a pure virtual analyze method. DuplicatesAnalyzer inherits from Analyzer and overrides the analyze method.

C++ class declarations for MissingAnalyzer, SearchAnalyzer, and StatisticsAnalyzer. Each class includes a constructor and overrides the analyze method inherited from a base class
