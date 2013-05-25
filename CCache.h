/* 
 * File:   CCache.h
 * Author: romanius
 *
 * Created on 1 Апрель 2013 г., 14:45
 */

#ifndef CCACHE_H
#define	CCACHE_H

#define CACHE_FILE    ".rncache"
#define CACHE_HEADER  0xDEADBEEF
#define CACHE_VERSION 1
#ifdef LINUX
  #define CACHE_OS    0
#else
  #define CACHE_OS    1
#endif

class CCache 
{
public:
    CCache();
    CCache(const CCache& orig);
    virtual ~CCache();
    
    void Load();
    void Save();
    unsigned long Find(unsigned short mask);
    void Add(unsigned short mask, unsigned long addr);
private:
    void cleanCache();
    
    FILE *f;
    
    struct __file_header
    {
        unsigned int  header;
        unsigned char version;
        unsigned char os;
        unsigned char number;
    } file_header;
    
    struct data
    {
        unsigned short mask;
        unsigned long  addr;
    };
    
    data *file_data;

};

#endif	/* CCACHE_H */

