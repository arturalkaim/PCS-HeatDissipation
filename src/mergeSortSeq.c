//#include <omp.h>


//  left half is A[iBegin :iMiddle-1]
// right half is A[iMiddle:iEnd-1   ]
void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd, int* B)
{
    int i0 = iBegin, i1 = iMiddle;

    // While there are elements in the left or right runs
    int j;
//#pragma omp parallel for firstprivate(i0, i1)
    for (j = iBegin; j < iEnd; j++) {
        // If left run head exists and is <= existing right run head.
        if (i0 < iMiddle && (i1 >= iEnd || A[i0] <= A[i1])){
            B[j] = A[i0];
            i0 = i0 + 1;
        }
        else{
            B[j] = A[i1];
            i1 = i1 + 1; }
    }

}

void CopyArray(int* B, int iBegin, int iEnd,int* A)
{
	int k;
    for(k = iBegin; k < iEnd; k++)
        A[k] = B[k];
}


void TopDownSplitMergeNew(int* A, int iBegin, int iEnd, int* B){
	if(iEnd - iBegin < 2)                       // if run size == 1
	        return;                                 //   consider it sorted
	    // recursively split runs into two halves until run size == 1,
	    // then merge them and return back up the call chain
	    int iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point, it keeps the lower, doesn't round up
	    TopDownSplitMergeNew(A, iBegin,  iMiddle, B);  // split / merge left  half
	    TopDownSplitMergeNew(A, iMiddle,    iEnd, B);  // split / merge right half
	    TopDownMerge(A, iBegin, iMiddle, iEnd, B);  // merge the two half runs
	    CopyArray(B, iBegin, iEnd, A);              // copy the merged runs back to A
}

// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set)
void TopDownSplitMerge(int* A, int iBegin, int iEnd, int* B)
{
    if(iEnd - iBegin < 2)                       // if run size == 1
        return;                                 //   consider it sorted
    // recursively split runs into two halves until run size == 1,
    // then merge them and return back up the call chain
    int iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point, it keeps the lower, doesn't round up
	#pragma omp parallel sections
    {
    	//printf("%d \n", omp_get_num_threads());
		#pragma omp section
    	{
    TopDownSplitMergeNew(A, iBegin,  iMiddle, B);  // split / merge left  half
    	}
		#pragma omp section
    	{
    TopDownSplitMergeNew(A, iMiddle,    iEnd, B);  // split / merge right half
    	}
    }

    TopDownMerge(A, iBegin, iMiddle, iEnd, B);  // merge the two half runs
    CopyArray(B, iBegin, iEnd, A);              // copy the merged runs back to A
}


void TopDownMergeSort(int* A,int* B,int n)
{

    TopDownSplitMerge(A, 0, n, B);
}



