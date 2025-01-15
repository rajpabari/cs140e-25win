// we went to measure the overhead of a mul instruction:
// 1. read clock at address 0x20003004
// 2. do the multiply
// 3. read clock at address 0x20003004
// 4. write the diff.
//
// what happens?
int mul(int *time, int a, int b) {
    unsigned start = *(volatile unsigned *) 0x20003004;

asm volatile ("" : : : "memory");

	int c = a * b;

asm volatile ("" : : : "memory");
    unsigned end = *(volatile unsigned *) 0x20003004;

	*time = end - start;
	return c;
}
