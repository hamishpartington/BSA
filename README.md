# Binary Sparse Arrays (BSA)

This was the second piece of coursework for my C module for my Computer Science MSc. The task was to implemement a binary sparse array (BSA) abstract data type (ADT).

## Extension

For the extension I focussed on making the BSA alternative more memory efficient when assigning to high indexes without compromising on speed too much. I kept the BSA structure broadly the same but changed the structure which the array of pointers point towards.

They pointed to a meta_tree structure which contained a pointer to the top of a tree structure, the max_index of the tree and the number of nodes in the tree

Rather than sparse arrays I have sparse trees. Although the getting, setting, and deleting data will be  longer for non-sparse data, for sparse data, performance shouldnt take too much of a hit, as the tree's should not have loads of levels to search through. 

For the given programs, sieve.c, fibmemo and isfactorial, run times and memory allocation were as follows.

![image](https://github.com/hamishpartington/BSA/assets/97231049/f933970e-1530-458e-8571-e8a74f2fd5fa)

This demonstrates that my extension is much more memory effcient when assigning values to high indexes when data is more sparsely allocated. 

Gets and sets will take longer though with O(log n) complexity versus essentially O(1) complexity for the binary sparse array (with just a little overhead for calculating the rownumber).

There are a lot of gets and sets in the sieve and fibmemo programs so, my extension will not perform well when the MAX is increased, as the data is not allocated in a sparse way but rather allocated and then deleted for sieve and allocated at every index up to the max for fibmemo, my extension is not an improvement on the standard bsa for these programs. Also, as sets happen at every index, each of the trees essentially becomes a linked list with no left nodes, so setting, getting and deleting becomes 0(n) complexity for these programs. Also, memory savings are not seen as data is allocated at every index rather than sparsely.

However, for isfactorial, the data is only very sparsely allocated. With set only being called for each factorial. This means that my extension program
does not suffer as before with no real time cost for sets versus the standard bsa. As factorials are being generated and data is being assigned to factorial 
indexes, a lot less memory is needed for the extension as it only needs to allocate 1 node of a tree for a large index, rather than a large array which will be mostly empty.

## Mark

I recieved a distinction for this assignment with a mark of 74.
