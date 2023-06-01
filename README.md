# Files-on-pendrives
### Semester 2 - Algorithms and Data Structures
---
There are files on your disk. You have to copy as many files as possible into two pendrives. Files cannot be divided. Write a program that will select files. Your answer can be different from optimal result by 1.

#### Input
In the first line there are two numbers n p - number of files and pendrives' size.
In the next n lines there are two numbers id r - file identifier and file size.

#### Output
In the first line write a number - total number of copied files. In the next two lines write '1:' or '2:' with lists of copied file's identifiers. The lists should be sorted in descending order.

---

#### Example
Input:  
```
4 7  
323 1  
10 2  
87438 5  
99 6
```

Output:
```
3  
1: 323 10  
2: 87438  
```

or  

```
4  
1: 323 99  
2: 87438 10  
```

or  

```
3  
1: 323  
2: 87438 10  
```
