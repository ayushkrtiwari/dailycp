// It's important that you first understand the quadratic method for counting inversions. 
// For each element, look at all the previous elements and 
// count the number that are greater than the current element. Add this to your answer.

// So, we are using the Fenwick tree to keep track of what numbers we have seen already, 
// where a 1 indicates seen, and 0 indicates not seen. 
// At each element, we can tell the number of greater elements that came before it 
// by querying the sum of the range a[i] to n. This is the first line you referenced. 
// Then, we want to say that we've seen a[i], 
// so we update that to 1 and continue for the rest of the array.
// ____________________________________________________________________________________________

// Fenwick Tree stores sum or product.
// But can be used to do multiple things: Min Query, Inversion Cnt, ...