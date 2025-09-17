# Advanced Algorithms: Practical II  
**Deadline:** Monday, September 22, 23:59  
**Course code:** WBCS052-05  

---

## Problem 2A: Comparing Grades (25 points)

At the University of Gralgingen, there is a course called *Trivial Algorithms*, taught by professor Maestro.  
At the end of the course, all **n** students of the course have to take a written exam. Students may leave the exam hall at any time — as long as they do not want to change their answers anymore.

After the exam, professor Maestro uploads the grades of the students to *LightSpace*. All students can see:
- Their own grade  
- The grades of all other students  
- Information about when each student left the exam hall  

Subsequently, the students start comparing their results.

---

### Definitions

For each student *i* (1 ≤ i ≤ n):
- You are given the grade `gᵢ`  
- You are given `lᵢ`, the number of students who were still in the exam hall when student *i* left  

We say that **student *i* respects student *j*** if and only if:
- Student *j*’s grade `gⱼ` is at least `G` points higher than student *i*’s grade `gᵢ`  
- Student *i* left the exam hall later than student *j*  

Formally:  
```
gᵢ + G ≤ gⱼ  and  lᵢ < lⱼ
```

---

### Task

Determine how many other students each student respects.

---

### Input

- The first line of the input contains the integers `n` and `G`.  
- Then follow `n` lines, the *i*th of which contains the integers `gᵢ` and `lᵢ`.  

**Example input:**
```
7 15
46 2
108 0
32 3
42 6
67 4
84 5
14 1
```

---

### Output

For each student *i*, print a line containing **one number**:  
the number of students that this student respects.

**Correct output for the example above:**
```
2
0
2
0
1
0
5
```

---

### Explanation of Example

- Students 1 and 3 both respect two students: students 5 and 6.  
- Student 5 respects one student: student 6.  
- Student 7 respects all five students who left the exam hall before student 7 did.  
- Students 2, 4, and 6 do not respect any other student.  

---

### Details and Constraints

- `1 ≤ n ≤ 200 000`  
- `1 ≤ G ≤ 10⁸`  
- `−10⁸ ≤ gᵢ ≤ 10⁸`  
- `0 ≤ lᵢ < n`  
- All students leave the exam hall at a different time (`lᵢ ≠ lⱼ` if *i ≠ j*)  
- **CPU time limit:** 1 second per test case  
- **Memory limit:** 256 MiB per test case  

---

### Hint

- Consider **merge sort**.
