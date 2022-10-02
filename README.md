# Quad-Tree
Quad Tree structure for storing binary sparse images


Supported operations:
* quad tree(int n): a constructor that initializes to a matrix of size 2n ×2n with all
pixels 0. The value of n will be at most 20, and is called the height of the quad tree.
* ~quad tree() : the destructor that destroys the tree.
* quad tree(quad tree const &Q) : copy constructor.
* void set(int x1, int y1, int x2, int y2, int b) : set all pixels in the sub-matrix with rows x1 to x2 and columns y1 to y2 (inclusive) to the value b. It is assumed that 0 ≤ x1 ≤ x2 < 2n and 0 ≤ y1 ≤ y2 < 2n, if the tree has height n.
* int get(int x1, int y1) const : return the value of the pixel (x1,y1).
* int size() const : return the height n.
* void overlap(quad tree const &Q): the new value of the matrix is the pixel-wise boolean OR with the matrix corresponding to Q. It can be assumed that Q has the same height as the image to which the operation is applied.
* void intersect(quad tree &Q) : same as the previous except that the boolean
AND of the two images is computed.
* void complement() : complement all the entries in the matrix.
* void resize(int m): Change the size of the matrix to 2m × 2m. This is done as follows. If m ≥ n, replace each pixel of the original image by a 2m−n × 2m−n matrix with all values equal to the original pixel. If m < n, divide the matrix into 2m × 2m submatrices, each of size 2n−m ×2n−m, and replace each submatrix by a pixel whose value occurs more often in the submatrix. If equal, choose 1.
* void extract(int x1, int y1, int m) : the new value is the 2m ×2m submatrix with rows from x1 to x1+2m − 1 and columns y1 to y1 + 2m − 1. It can be assumed that the submatrix is well-defined.
