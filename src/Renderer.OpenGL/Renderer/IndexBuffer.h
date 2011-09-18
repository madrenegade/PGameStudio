/* 
 * File:   IndexBuffer.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:35 PM
 */

#ifndef RENDERER_INDEXBUFFER_H
#define	RENDERER_INDEXBUFFER_H

#include <boost/shared_array.hpp>

namespace Renderer
{

    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();
        
        void setData(const boost::shared_array<unsigned short>& data, unsigned int numIndexes);
        
        unsigned int getID() const;
        unsigned int getNumIndexes() const;
        
    private:
        unsigned int id;
        unsigned int numIndexes;
    };
}

#endif	/* RENDERER_INDEXBUFFER_H */

