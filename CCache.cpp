/* 
 * File:   CCache.cpp
 * Author: romanius
 * 
 * Created on 1 Апрель 2013 г., 14:45
 */

#include "main.h"
#include "CCache.h"

CCache::CCache()
{
    this->Load();
    
    //fclose(this->f);
}

void CCache::Load()
{
    if(this->f != NULL)
        fclose(this->f);
    
    bzero(&this->file_header, sizeof(this->file_header));
    
    this->f = fopen(CACHE_FILE, "rb"); 
    
    if(this->f == NULL)
    {
        this->cleanCache();
        this->Save();
    }  
    
    int readBytes = fread(&this->file_header, sizeof(this->file_header), 1, this->f);
    
    if(readBytes != sizeof(this->file_header))
    {
        this->cleanCache();
        this->Save();
    }
    
    if(this->file_header.header != CACHE_HEADER || this->file_header.version != CACHE_VERSION || this->file_header.os != CACHE_OS || this->file_header.number <= 0)
    {
        this->cleanCache();
        this->Save();
    }
    
    
    
    /*if(this->file_header.number > 0)
    {
        this->file_data = new data[this->file_header.number];
    
        for(int i = 0; i < this->file_header.number; i++, this->file_data++)
        {
            data tmp;
            fread(&tmp, sizeof(tmp), 1, this->f);

            this->file_data[i] = tmp;
        }
    }*/
    
    fclose(this->f);
}

unsigned long CCache::Find(unsigned short mask)
{
    for(int i = 0; i < this->file_header.number; i++)
        if(this->file_data[i].mask == mask)
            return this->file_data[i].addr;
    
    return NULL;
}

void CCache::Add(unsigned short mask, unsigned long addr)
{
    data tmp;
    
    tmp.mask = mask;
    tmp.addr = addr;
    
    this->file_data[this->file_header.number] = tmp;
            
    this->file_header.number++;
    
    this->Save();
}

CCache::CCache(const CCache& orig)
{
}

CCache::~CCache()
{
    fclose(this->f);
}

void CCache::cleanCache()
{
    this->file_header.header = CACHE_HEADER;
    this->file_header.version = CACHE_VERSION;
    this->file_header.os = CACHE_OS;
    this->file_header.number = 0;
}

void CCache::Save()
{
    if(this->f != NULL)
        fclose(this->f);
    
    this->f= fopen(CACHE_FILE, "wb");
    
    fwrite(&this->file_header, sizeof(this->file_header), 1, this->f);
    
    /*if(this->file_header.number > 0)
        for(int i = 0; i < this->file_header.number; i++, this->file_data++)
            fwrite(&this->file_data[i], sizeof(data), 1, this->f);
    */
    fflush(this->f);
    fclose(this->f);
}

