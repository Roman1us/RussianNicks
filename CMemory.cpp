/* 
 * File:   CMemory.cpp
 * Author: romanius
 * 
 * Created on 1 Апрель 2013 г., 16:44
 */

#include "main.h"
#include "CMemory.h"

CMemory::CMemory()
{
    unsigned char findFunction[] = 
    /*{
        0x8B, 0x4C, 0x24, 0x04, 0x8A, 0x01, 0x84, 0xC0, 0x74,
        0x4A, 0x8D, 0x9B, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x30,
        0x7C, 0x04, 0x3C, 0x39, 0x7E, 0x34, 0x3C, 0x41, 0x7C,
        0x04, 0x3C, 0x5A, 0x7E, 0x2C, 0x3C, 0x61, 0x7C, 0x04,
        0x3C, 0x7A, 0x7E, 0x24, 0x3C, 0x5D, 0x74, 0x20, 0x3C,
        0x5B, 0x74, 0x1C, 0x3C, 0x5F, 0x74, 0x18, 0x3C, 0x24,
        0x74, 0x14, 0x3C, 0x3D, 0x74, 0x10, 0x3C, 0x28, 0x74,
        0x0C, 0x3C, 0x29, 0x74, 0x08, 0x3C, 0x40, 0x74, 0x04,
        0x3C, 0x2E, 0x75, 0x0B, 0x8A, 0x41, 0x01, 0x41, 0x84,
        0xC0, 0x75, 0xBC, 0x32, 0xC0, 0xC3, 0xB0, 0x01, 0xC3
    };*/
    {
        0x55, 0x89, 0xE5, 0x53, 0x8B, 0x5D, 0x08, 0x0F, 0xB6, 
        0x0B, 0x84, 0xC9, 0x74, 0x5A, 0x66, 0x90, 0x88, 0xC8, 
        0x2C, 0x30, 0x3C, 0x09, 0x88, 0xC8, 0x0F, 0x96, 0xC2, 
        0x2C, 0x41, 0x3C, 0x19, 0x0F, 0x96, 0xC0, 0x08, 0xC2, 
        0x75, 0x3A, 0x88, 0xC8, 0x2C, 0x61, 0x3C, 0x19, 0x76, 
        0x32, 0x80, 0xF9, 0x5D, 0x74, 0x2D, 0x80, 0xF9, 0x5B, 
        0x74, 0x28, 0x80, 0xF9, 0x5F, 0x74, 0x23, 0x80, 0xF9, 
        0x24, 0x74, 0x1E, 0x80, 0xF9, 0x3D, 0x74, 0x19, 0x80, 
        0xF9, 0x28, 0x74, 0x14, 0x80, 0xF9, 0x29, 0x74, 0x0F, 
        0x80, 0xF9, 0x40, 0x74, 0x0A, 0x80, 0xF9, 0x2E, 0x75, 
        0x12, 0x90, 0x8D, 0x74, 0x26, 0x00, 0x43, 0x0F, 0xB6, 
        0x0B, 0x84, 0xC9, 0x75, 0xA8, 0x5B, 0x31, 0xC0, 0x5D, 
        0xC3, 0x5B, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x5D, 0xC3
    };


    
    this->getBounds();
    
    this->findAddr = (unsigned char *)this->memmem((unsigned char *)this->startAddr, this->findLen, findFunction, sizeof(findFunction));
}

CMemory::CMemory(const CMemory& orig)
{
}

CMemory::~CMemory()
{
}

void CMemory::PrintInfo()
{
    PRINT_FUNCTION("-> Russian nicks plugin status:\n");
    PRINT_FUNCTION("\t-> Start find from %10p\n", this->startAddr);
    PRINT_FUNCTION("\t-> Find length %x bytes\n", this->findLen);
    PRINT_FUNCTION("\t-> Funtion address we find: %10p\n", this->findAddr);
    PRINT_FUNCTION("-> Time for searching: %dms\n", this->searchTime);
}

unsigned char *CMemory::memmem(unsigned char *haystack, size_t hlen, unsigned char *needle, size_t nlen)
{
    size_t scan = 0;
    size_t bad_char_skip[UCHAR_MAX + 1]; /* Officially called:
                                          * bad character shift */
 
    /* Sanity checks on the parameters */
    if (nlen <= 0 || !haystack || !needle)
        return NULL;
 
    /* ---- Preprocess ---- */
    /* Initialize the table to default value */
    /* When a character is encountered that does not occur
     * in the needle, we can safely skip ahead for the whole
     * length of the needle.
     */
    for (scan = 0; scan <= UCHAR_MAX; scan = scan + 1)
        bad_char_skip[scan] = nlen;
 
    /* C arrays have the first byte at [0], therefore:
     * [nlen - 1] is the last byte of the array. */
    size_t last = nlen - 1;
 
    /* Then populate it with the analysis of the needle */
    for (scan = 0; scan < last; scan = scan + 1)
        bad_char_skip[needle[scan]] = last - scan;
 
    /* ---- Do the matching ---- */
 
    /* Search the haystack, while the needle can still be within it. */
    while (hlen >= nlen)
    {
        /* scan from the end of the needle */
        for (scan = last; haystack[scan] == needle[scan]; scan = scan - 1)
            if (scan == 0) /* If the first byte matches, we've found it. */
                return haystack;
 
        /* otherwise, we need to skip some bytes and start again.
           Note that here we are getting the skip value based on the last byte
           of needle, no matter where we didn't match. So if needle is: "abcd"
           then we are skipping based on 'd' and that value will be 4, and
           for "abcdd" we again skip on 'd' but the value will be only 1.
           The alternative of pretending that the mismatched character was
           the last character is slower in the normal case (E.g. finding
           "abcd" in "...azcd..." gives 4 by using 'd' but only
           4-2==2 using 'z'. */
        hlen     -= bad_char_skip[haystack[last]];
        haystack += bad_char_skip[haystack[last]];
    }
 
    return NULL;
}

void CMemory::getBounds()
{
#ifdef LINUX    
    this->startAddr = (void *)0x8048000;//&__executable_start;
    this->findLen = (size_t)0xFFFFFF;//(&__etext - 0x8048000);
#else
    MODULEINFO mi;
	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &mi, sizeof(mi));

	this->findLen = (size_t)mi.SizeOfImage;
#endif
}

