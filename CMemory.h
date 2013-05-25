/* 
 * File:   CMemory.h
 * Author: romanius
 *
 * Created on 1 Апрель 2013 г., 16:44
 */

#ifndef CMEMORY_H
#define	CMEMORY_H


class CMemory {
public:
    CMemory();
    CMemory(const CMemory& orig);
    
    void PrintInfo();
    
    bool Find();
    bool Setup();
    
    virtual ~CMemory();
private:
    
    void *findAddr;
    
    void *startAddr;
    size_t findLen;
    
    int searchTime;
    
    unsigned char *memmem(unsigned char *haystack, size_t hlen, unsigned char *needle, size_t nlen);
    void getBounds();
    bool unlockMemory(void *startAddr, size_t *size);
    //bool setupHook();
    
    static bool __hooked_function();

};

#endif	/* CMEMORY_H */

