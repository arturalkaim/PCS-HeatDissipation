

initiation(p);
clock_t srt = clock(), diff;
time_t start, end;
double elapsed;
time(&start); 

run(p->maxiter,p->threshold, r, p->period);

time(&end);
elapsed = difftime(end, start);

diff = clock() - srt;

int msec = diff * 1000 / CLOCKS_PER_SEC;   
r->time = msec/1000.0;

printf("Time taken %f seconds %d milliseconds\n", msec/1000.0, msec%1000);
