/* 
 * File:   VertexFormat.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 9:42 PM
 */

#ifndef GRAPHICS_VERTEXFORMAT_H
#define	GRAPHICS_VERTEXFORMAT_H

#include <cstddef>

namespace Graphics
{

    class VertexFormat
    {
    public:
        VertexFormat(const size_t vertexSize = 0,
                     const ptrdiff_t positionOffset = 0, const size_t positionSize = 0,
                     const ptrdiff_t texCoordOffset = 0, const size_t texCoordSize = 0,
                     const ptrdiff_t normalOffset = 0, const size_t normalSize = 0,
                     const ptrdiff_t tangentOffset = 0, const size_t tangentSize = 0,
                     const ptrdiff_t bitangentOffset = 0, const size_t bitangentSize = 0);

        ~VertexFormat();

        size_t getVertexSize() const;

        ptrdiff_t getPositionOffset() const;
        size_t getPositionSize() const;

        bool hasTexCoords() const;
        ptrdiff_t getTexCoordOffset() const;
        size_t getTexCoordSize() const;

        bool hasNormal() const;
        ptrdiff_t getNormalOffset() const;
        size_t getNormalSize() const;

        bool hasTangent() const;
        ptrdiff_t getTangentOffset() const;
        size_t getTangentSize() const;

        bool hasBitangent() const;
        ptrdiff_t getBitangentOffset() const;
        size_t getBitangentSize() const;

        template<typename VertexType>
        static VertexFormat forTexturedVertex()
        {
            return VertexFormat(sizeof (VertexType),
                                offsetof(VertexType, position), sizeof (VertexType::position),
                                offsetof(VertexType, texcoords), sizeof (VertexType::texcoords));
        }

        template<typename VertexType>
        static VertexFormat forTexturedVertexWithNormal()
        {
            return VertexFormat(sizeof (VertexType),
                                offsetof(VertexType, position), sizeof (VertexType::position),
                                offsetof(VertexType, texcoords), sizeof (VertexType::texcoords),
                                offsetof(VertexType, normal), sizeof (VertexType::normal));
        }

        template<typename VertexType>
        static VertexFormat forTNBT()
        {
            return VertexFormat(sizeof (VertexType),
                                offsetof(VertexType, position), sizeof (VertexType::position),
                                offsetof(VertexType, texcoords), sizeof (VertexType::texcoords),
                                offsetof(VertexType, normal), sizeof (VertexType::normal),
                                offsetof(VertexType, tangent), sizeof (VertexType::tangent),
                                offsetof(VertexType, bitangent), sizeof (VertexType::bitangent));
        }

    private:
        // NOTE: cannot make member variables constant because of assignment
        size_t vertexSize;

        ptrdiff_t positionOffset;
        size_t positionSize;

        ptrdiff_t texCoordOffset;
        size_t texCoordSize;

        ptrdiff_t normalOffset;
        size_t normalSize;

        ptrdiff_t tangentOffset;
        size_t tangentSize;

        ptrdiff_t bitangentOffset;
        size_t bitangentSize;
    };
}

#endif	/* GRAPHICS_VERTEXFORMAT_H */

