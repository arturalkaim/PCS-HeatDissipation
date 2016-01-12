//#include <omp.h>


double time, timeBefore, timeAfter, timeAuxBefore, timeAuxAfter;
//  left half is A[iBegin :iMiddle-1]
// right half is A[iMiddle:iEnd-1   ]
void TopDownMerge(int* A, int iBegin, int iMiddle, int iEnd, int* B) {
	int i0 = iBegin, i1 = iMiddle;

	// While there are elements in the left or right runs
	int j;

#pragma omp for //firstprivate(i0, i1)
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
#pragma omp for 
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
#pragma omp parallel
	{
//	#pragma omp sections 
//	{
		#pragma omp single
		{
//		printf("Num threads inside %d \n", omp_get_num_threads());
#pragma omp task //section 
		{
			TopDownSplitMerge(A, iBegin, iMiddle, B); // split / merge left
		}

#pragma omp task// section
		{
			TopDownSplitMerge(A, iMiddle, iEnd, B); // split / merge right half
		}
	
#pragma omp taskwait
}

    //timeAuxBefore = omp_get_wtime(); //get the time before the Sequential part

    TopDownMerge(A, iBegin, iMiddle, iEnd, B);  // merge the two half runs
	CopyArray(B, iBegin, iEnd, A);  // copy the merged runs back to A
}
	//timeAuxAfter = omp_get_wtime(); //compute the result



	//timeBefore += timeAuxAfter-timeAuxBefore;

}

/*void printTimeOutFile(double time){
	FILE *out;
	out = fopen("timeOut.out", "a");
	fprintf(out, "S %f\n", time);
	fclose(out);
}*/

void TopDownMergeSort(int* A, int* B, int n) {
	TopDownSplitMerge(A, 0, n, B);
}

void SortSeveral(int** A, int** B, int* n, int total){

	int i;
	timeBefore = omp_get_wtime();
//#pragma omp parallel for schedule(dynamic,1) //num_threads(4) //private(timeBefore, timeAfter, timeAuxBefore, timeAuxAfter, time)
	for(i=0; i < total; i++){
		TopDownMergeSort((A[i]), B[i], n[i]);
	}

		timeAfter = omp_get_wtime();

	//end = omp_get_wtime();
	time = timeAfter - timeBefore;
	printf("%f\n", time);
}
