#include <unistd.h>
#include <stdio.h>

int main() {

	printf("_SC_PHYS_PAGES: %ld\n", sysconf(_SC_PHYS_PAGES));
	printf("_SC_AVPHYS_PAGES: %ld\n", sysconf(_SC_AVPHYS_PAGES));
	printf("_SC_PAGESIZE: %ld\n", sysconf(_SC_PAGESIZE));

	printf("-----------------------------------------------\n");

	printf("MEMORY: %ld\n", sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE));
	printf("FREE: %ld\n", sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE));
	printf("USED: %ld\n", ((sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE)) - (sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE)))/ (1024 * 1024));

}
