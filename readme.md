I had less time to work on this one, so I did not test it well. It probably has
bugs. The idea is to implement a dynamic 1-D array using an array of pointers to
arrays of integers (C does not have generics). The idea is that each of the arrays
pointed at has its own index, indicating where the next element should go. If the
array gets full, a new pointer to array is with a size one greater than the previous
one. All the pointers from the previous array are copied, the new array is added
to this new array, and the old one is freed. The new array now contains the reference
to all other arrays.

This is a dynamic array. Traditionally, dynamic arrays are simple 1-D arrays with
extra space. The object keeps track of what where the next element goes and how
much space it has left. Once full, the array is copied, along with the new item,
into an array twice as big as the previous one. Doing the math, this means that
on average, each memory access is still in constant time. In practice, it means
that there are a few times when the computer freezes execution to perform this step.
After each resize, the freeze gets worse. The effects on memory can also be dramatic.
For an array that is full with 1 million elements, adding one element requires the
allocation of memory for 2 million elements, which is a rather drastic jump in memory
consumption. In the event where this array stops growing, all of this extra memory
will no be released for as long as the array is still in use.

The chain array solves all this issues at the expense of the access time. On average,
it takes longer to access a value, but the algorithm ameliorates it as much as possible
using a simple design (I came up with more complicated algorithms, but I haven't
implemented those yet). This chain array uses memory more efficiently, while trying
to keep access time as low as possible in the event of a resize.

Since only some of the arrays are modified in a resize, it should be possible to
access the others in a multithreaded fashion, freezing execution only when the
array pointer is updated. This is an added advantage that traditional dynamic
arrays do not have. 
