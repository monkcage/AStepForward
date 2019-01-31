#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

int main() 
{
	srand(time(NULL));
	TreeRoot root;
	rbtreeInit(&root);
	int arr[] = {582,295,924,240,453,252,457,191,996,252,462,299,245,244,767,998,329,201,124,751,920,734,534,74,673,479,183,349,153,714,91,735,9,367,328,814,971,137,5,967,389,819,267,987,415,386,337,744,939,461,495,211,196,382,638,221,213,173,922,366,887,14,454,248,733,134,62,705,271,419,24,12,238,643,351,653,381,689,750,672,502,597,884,698,979,522,271,193,695,194,911,935,560,717,183,293,851,246,350,474};
	for(int i = 0; i < 200; i++) {
		int r = rand() % 1000;
		printf("%d,", r);
		rbtreeValueInsert(&root, r);
	}
	printf("\n");

	rbtreeShow(&root, "4.dot");
#if 0
	rbtreeValueRemove(&root, 924);

	rbtreeShow(&root, "2.dot");

	rbtreeValueRemove(&root, 153);
	
	rbtreeShow(&root, "3.dot");
#endif
	return 0;
}
