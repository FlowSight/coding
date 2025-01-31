### **TF-IDF Algorithm**
**TF-IDF (Term Frequency-Inverse Document Frequency)** is a statistical measure used in information retrieval and text mining to evaluate the importance of a word in a document relative to a collection of documents (corpus). It balances the frequency of a word in a document against how common the word is across all documents.

---

### **Concepts Behind TF-IDF**
1. **Term Frequency (TF)**:
   - Measures how often a term appears in a document.
   - Formula:
     \[
     TF(t, d) = \frac{\text{Number of times term } t \text{ appears in document } d}{\text{Total number of terms in document } d}
     \]
   - Normalizes term count so that longer documents do not unfairly dominate.

2. **Inverse Document Frequency (IDF)**:
   - Measures how important a term is. A term that appears in many documents has less discriminative power.
   - Formula:
     \[
     IDF(t, D) = \log \left(\frac{\text{Total number of documents } (N)}{\text{Number of documents containing term } t}\right)
     \]
   - Adding \(+1\) to the denominator avoids division by zero:
     \[
     IDF(t, D) = \log \left(\frac{N}{1 + \text{Number of documents containing term } t}\right)
     \]

3. **TF-IDF**:
   - Combines both measures:
     \[
     TF\text{-}IDF(t, d, D) = TF(t, d) \times IDF(t, D)
     \]
   - Highlights words that are frequent in a document but rare in the corpus.

---

### **Step-by-Step Example**

#### **Corpus**:
Let’s take a small corpus of 3 documents:

1. **Doc1**: "The cat sat on the mat."
2. **Doc2**: "The dog sat on the mat."
3. **Doc3**: "The cat chased the dog."

---

#### **Step 1: Preprocess the Text**
- Convert to lowercase.
- Remove punctuation.
- Tokenize (split into words).
- Resulting corpus:
  - Doc1: ["the", "cat", "sat", "on", "the", "mat"]
  - Doc2: ["the", "dog", "sat", "on", "the", "mat"]
  - Doc3: ["the", "cat", "chased", "the", "dog"]

---

#### **Step 2: Calculate Term Frequency (TF)**
For each term \( t \) in a document \( d \):
\[
TF(t, d) = \frac{\text{Number of occurrences of } t \text{ in } d}{\text{Total number of terms in } d}
\]

- **Doc1**:
  - Total terms = 6
  - \( TF(\text{the}) = \frac{2}{6} = 0.33 \)
  - \( TF(\text{cat}) = \frac{1}{6} = 0.17 \)
  - \( TF(\text{sat}) = \frac{1}{6} = 0.17 \)
  - \( TF(\text{on}) = \frac{1}{6} = 0.17 \)
  - \( TF(\text{mat}) = \frac{1}{6} = 0.17 \)

- Similarly, calculate for Doc2 and Doc3.

---

#### **Step 3: Calculate Inverse Document Frequency (IDF)**
For each term \( t \):
\[
IDF(t, D) = \log \left(\frac{N}{1 + \text{Number of documents containing } t}\right)
\]
Where \( N = 3 \) (total number of documents).

- **the**:
  - Appears in all 3 documents: \( IDF(\text{the}) = \log \left(\frac{3}{1 + 3}\right) = \log(0.75) = -0.124 \)
  - (Very low weight because it’s common across all documents.)
- **cat**:
  - Appears in 2 documents: \( IDF(\text{cat}) = \log \left(\frac{3}{1 + 2}\right) = \log(1) = 0 \)
- **sat**:
  - Appears in 2 documents: \( IDF(\text{sat}) = \log \left(\frac{3}{1 + 2}\right) = 0 \)
- **dog**:
  - Appears in 2 documents: \( IDF(\text{dog}) = \log(1) = 0 \)
- **mat**:
  - Appears in 2.

For unique words