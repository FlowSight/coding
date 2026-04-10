

### 📌 Problem Statement

You are given two APIs:

### 1. `read()`

* thread safe
* Reads data from a very large CSV (or Excel) file.
* Returns **one row at a time**, till \n
* In some variations, it may return `(row_id, row_data)`.

---

### 2. `write()`

* Takes a rows and writes them to a target file.
* Each call to `write()` produces output in the format:

  ```
  header
  row1
  footer
  ```
* The API is **thread-safe** and guarantees:

  * Each call is **atomic**
  * No interleaving between concurrent writes
    (i.e., output will always be `header…footer`, `header…footer`, etc.)

---

### 🎯 Objective

Design a system to **copy data from the source file to the target file** efficiently.

---

### ⚙️ Constraints / Follow-ups

The interviewer may introduce these variations:

1. **Ordering**

   * What if output **must preserve the original row order**?
   * What if ordering **does not matter**?

2. **Batching**

   * How do you decide batch size?
   * What if rows are of **uneven sizes (skew)**?

3. **Memory constraints**

   * File is very large — cannot fit in memory
   * how to limit mem usage

4. **Large rows**

   * What if a single row is extremely large (e.g., GBs)?

5. **API limitations**

   * `read()` may or may not be thread-safe
   * You **cannot modify the APIs**

6. **Fairness / throughput**

   * How do you maximize throughput while maintaining correctness?


