//#include <omp.h>


double time, timeBefore, timeAfter, timeAuxBefore, timeAuxAfter;
//  left half is A[iBegin :iMiddle-1]
// right half is A[iMiddle:iEnd-1   ]
void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd, int* B) {
	int i0 = iBegin, i1 = iMiddle;

	// While there are elements in the left or right runs
	int j;

#pragma omp parallel for firstprivate(i0, i1)
	for (j = iBegin; j < iEnd; j++) {
		// If left run head exists and is <= existing right run head.
		if (i0 < iMiddle && (i1 >= iEnd || A[i0] <= A[i1])) {
			B[j] = A[i0];
			i0 = i0 + 1;
		} else {
			B[j] = A[i1];
			i1 = i1 + 1;
		}
	}

}

void CopyArray(int* B, int iBegin, int iEnd, int* A) {
	int k;
#pragma omp parallel for
	for (k = iBegin; k < iEnd; k++)
		A[k] = B[k];
}


// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set)
void TopDownSplitMerge(int* A, int iBegin, int iEnd, int* B) {
	if (iEnd - iBegin < 2)                       // if run size == 1
		return;                                 //   consider it sorted
	// recursively split runs into two halves until run size == 1,
	// then merge them and return back up the call chain
	int iMiddle = (iEnd + iBegin) / 2; // iMiddle = mid point, it keeps the lower, doesn't round up
#pragma omp parallel sections num_threads(2)
	{
//		printf("Num threads inside %d \n", omp_get_num_threads());
#pragma omp section
		{
			TopDownSplitMerge(A, iBegin, iMiddle, B); // split / merge left
		}

#pragma omp section
		{
			TopDownSplitMerge(A, iMiddle, iEnd, B); // split / merge right half
		}
	}


    timeAuxBefore = omp_get_wtime(); //get the time before the Sequential part

    TopDownMerge(A, iBegin, iMiddle, iEnd, B);  // merge the two half runs
	CopyArray(B, iBegin, iEnd, A);  // copy the merged runs back to A

	timeAuxAfter = omp_get_wtime(); //compute the result



	timeBefore += timeAuxAfter-timeAuxBefore;

}

/*void printTimeOutFile(double time){
	FILE *out;
	out = fopen("timeOut.out", "a");
	fprintf(out, "S %f\n", time);
	fclose(out);
}*/

void TopDownMergeSort(int* A, int* B, int n) {
	//printf("NUM THREADS %d\n", omp_get_num_threads());
	//start = -omp_get_wtime();
	timeBefore = omp_get_wtime();
	TopDownSplitMerge(A, 0, n, B);
	timeAfter = omp_get_wtime();

	//end = omp_get_wtime();
	time = timeAfter - timeBefore;
	printf("%f\n", time);
	//printTimeOutFile(end - start);


void SortSeveral(int* A, int* B, int* n, int total){

	int i;
#pragma omp parallel for
	for(i=0; i < total; i++){
		TopDownMergeSort(A[i], B[i], n[i]);

	}
}
