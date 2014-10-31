


   initiation(p);
clock_t start = clock(), diff;
    
    run(p->maxiter,p->threshold, r, p->period);

 

diff = clock() - start;

int msec = diff * 1000 / CLOCKS_PER_SEC;   
r->time = msec/1000.0;

printf("Time taken %f seconds %d milliseconds\n", msec/1000.0, msec%1000);
