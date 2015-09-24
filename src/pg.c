#include "HOS.h"

uint32 *pd;
uint32 numPT,*numPG;
uint32 pmap[32768];
uint32 mp,mo;
uint32 *psrc,*psize,*fsrc,*fsize;
uint32 varnum,fnum;
uint32 pgnum;

extern void write_cr3();
extern void write_cr0();
extern uint32 read_cr0();
extern void flush_tlb();

uint32 fnumg()
{
    return fnum;
}

void init_pd()
{
	pd = (uint32 *) 0x9C000;
	uint32 *page_table = (uint32 *) 0x9D000, *ptw = (uint32 *) 0x9E000;
	uint32 address = 0;
	uint32 i;

	for (i=0; i < 1024; i++)
	{
		page_table[i] = address | 3;
		address = address + 4096;
	}
	for (i=0; i < 1024; i++)
	{
		ptw[i] = address | 3;
		address = address + 4096;
	}

	pd[0] = page_table;
	pd[0] = pd[0] | 3;
	pd[1] = ptw;
    pd[1] = pd[0] | 3;

	for(i = 2; i < 1024; i++)
	{
		pd[i] = 0 | 2;
	}

	write_cr3(pd);
    write_cr0(read_cr0() | 0x80000000);
    numPT=2;
}


void show_ftable()
{
	int i = 0;
	if (fnum == 0)
		printf ("\n\t ftable> No entries");
	//for (; i < fnum; i++)
//		printf ("\n\t ftable> Entry %i: %i (%i)", i, fsrc[i], fsize[i]);
	printf ("\n\t ftable> Number of entries: ");
	putch (48+fnum);
}

void init_pmap()
{
	int i = 0;
    pgnum=0;
    numPT++;
	uint32 *pt=(uint32 *)0x9E000;
	for(i=0;i<1024;i++)
        pt[i]= 0 | 2;
	pd[numPT]=pt;
	pd[numPT]|=3;
	flush_tlb();
	int pend = ((((uint32)&end) & 0xFFFFF000) + 0xB000) >> 12;
	for (;i < pend; i++)
		pmap[i] = 0xFFFFFFFF;
	for (i = pend; i < 32768; i++)
		pmap[i] = 0;
	psrc = ((((uint32)&end) & 0xFFFFF000) + 0x3000);
	psize = ((((uint32)&end) & 0xFFFFF000) + 0x5000);
	fsrc = ((((uint32)&end) & 0xFFFFF000) + 0x7000);
	fsize = ((((uint32)&end) & 0xFFFFF000) + 0x9000);
	varnum = 0;
	fnum = 0;
	for (i = 0; i < 0x2000; i++)
	{
		psrc[i] = 0;
		psize[i] = 0;
		fsrc[i] = 0;
		fsize[i] = 0;
	}
}

void init_malloc()
{
	uint32 i = 0;
	while ((pmap[i] & 0xFFFFFFFF) == 0xFFFFFFFF)
		i++;
	int j = 31;
	for (; j >= 0; j--)
		if (!((pmap[i] >> j) & 1))
		{
			pmap[i] = pmap[i] ^ (1 << j);
			mp = pgnum * 4096;
			uint32 * pt=(uint32 *) ((uint32)((uint32)pd[1]>>2)<<2);
            pt[pgnum] = (i*32 + (31 - j))*4096;
            pt[pgnum] |= 3;
            pgnum++;
            flush_tlb();
			break;
		}
	mo = 0;
}

void stroutine()
{
	int i;
	int j;
st_repeat:
	i = 0;
	j = 0;
	for (; i < fnum; i++)
	for (; j < fnum; j++)
	if (i != j)
	{
		uint32 esrc = fsize[i]+fsrc[i];
		if (esrc == fsrc[j])
		{
			fsize[i] += fsize[j];
			sh_left(fsrc+4*j, fnum-j);
			sh_left(fsize+4*j, fnum-j);
			fnum--;
			goto st_repeat;
		}
	}
}

void froutine(uint32 src, uint32 size)
{
	int i = 0;
	uint32 endsrc = src + size;
	for (; i < fnum; i++)
	{
		if (fsrc[i] == endsrc)
		{
			fsrc[i] = src;
			fsize[i] += size;
			stroutine();
			return;
		}
		else if (fsrc[i] + fsize[i] == src)
		{
			fsize[i] += size;
			stroutine();
			return;
		}
	}
	fsrc[fnum] = src;
	fsize[fnum] = size;
	fnum++;
}

void free (uint32 ptr)
{
	int j = 0;
	int i = 0;
	char *b = ptr;
	for (; i < varnum; i++)
		if (ptr == psrc[i])
		{
			for (; j < psize[i]; j++)
				b[j] = 0;
			froutine(ptr, psize[i]);
			sh_left(psrc+4*i, varnum - i);
			sh_left(psize+4*i, varnum - i);
			varnum--;
			break;
		}
}

uint32 malloc(int size)
{
	int i = 0;
	uint32 ptr;
	for (; i < fnum; i++)
		if (size == fsize[i])
		{
			ptr = fsrc[i];
			sh_left(fsrc + 4*i, fnum - i);
			sh_left(fsize + 4*i, fnum - i);
			fnum--;
			goto label_malloc;
		}
		else if (size < fsize[i])
		{
			ptr = fsrc[i];
			fsize[i] -= size;
			fsrc[i] += size;
			goto label_malloc;
		}
	if (size > 4095)
	{
		printf ("\n\t malloc> Error: allocate only under 4KB");
		return -1;
	}
	if (mo + size > 4095)
	{
		init_malloc();
	}
	ptr = mp + mo;
	mo += size;
label_malloc:
	psrc[varnum] = ptr;
	psize[varnum] = size;
	varnum++;
	return ptr;
}
uint32 apa;
void pg_install()
{
    init_pd();
    init_pmap();
	init_malloc();
	pd[1023]=(uint32)pd | 3;
}
