#include "Utilities/Memory/MemoryPoolSettings.h"
#include "Utilities/Properties/PropertyManager.h"

namespace Utilities
{
    namespace Memory
    {

        void MemoryPoolSettings::addOptionsTo(Properties::PropertyManager* const properties, const char* const sbasename) const
        {
            const std::string basename(DCHECK_NOTNULL(sbasename));

            po::options_description options(basename + " memory pool options");

            options.add_options()
            ((basename + ".memory.smallObjects.maxSize").c_str(), po::value<size_t > ()->default_value(smallObjectPoolSize), "Maximum size for the small object area")
            ((basename + ".memory.smallObjects.pageSize").c_str(), po::value<size_t > ()->default_value(smallObjectPageSize), "Page size for the small object area")
            ((basename + ".memory.smallObjects.blockSize").c_str(), po::value<size_t > ()->default_value(smallObjectBlockSize), "Block size for the small object area")

            ((basename + ".memory.mediumObjects.maxSize").c_str(), po::value<size_t > ()->default_value(mediumObjectPoolSize), "Maximum size for the medium object area")
            ((basename + ".memory.mediumObjects.pageSize").c_str(), po::value<size_t > ()->default_value(mediumObjectPageSize), "Page size for the medium object area")
            ((basename + ".memory.mediumObjects.blockSize").c_str(), po::value<size_t > ()->default_value(mediumObjectBlockSize), "Block size for the medium object area")

            ((basename + ".memory.largeObjects.maxSize").c_str(), po::value<size_t > ()->default_value(largeObjectPoolSize), "Maximum size for the large object area")
            ((basename + ".memory.largeObjects.pageSize").c_str(), po::value<size_t > ()->default_value(largeObjectPageSize), "Page size for the large object area")
            ((basename + ".memory.largeObjects.blockSize").c_str(), po::value<size_t > ()->default_value(largeObjectBlockSize), "Block size for the large object area");

            DCHECK_NOTNULL(properties)->addOptions(options);
        }

        const MemoryPoolSettings MemoryPoolSettings::loadFrom(const Properties::PropertyManager* const properties, const char* const sbasename)
        {
            //DCHECK_NE(properties, nullptr);
            const std::string basename(DCHECK_NOTNULL(sbasename));

            const size_t soMax = properties->get<size_t > ((basename + ".memory.smallObjects.maxSize").c_str());
            const size_t soPage = properties->get<size_t > ((basename + ".memory.smallObjects.pageSize").c_str());
            const size_t soBlock = properties->get<size_t > ((basename + ".memory.smallObjects.blockSize").c_str());

            const size_t moMax = properties->get<size_t > ((basename + ".memory.mediumObjects.maxSize").c_str());
            const size_t moPage = properties->get<size_t > ((basename + ".memory.mediumObjects.pageSize").c_str());
            const size_t moBlock = properties->get<size_t > ((basename + ".memory.mediumObjects.blockSize").c_str());

            const size_t loMax = properties->get<size_t > ((basename + ".memory.largeObjects.maxSize").c_str());
            const size_t loPage = properties->get<size_t > ((basename + ".memory.largeObjects.pageSize").c_str());
            const size_t loBlock = properties->get<size_t > ((basename + ".memory.largeObjects.blockSize").c_str());

            return MemoryPoolSettings(
                       soMax, soPage, soBlock,
                       moMax, moPage, moBlock,
                       loMax, loPage, loBlock);
        }

        MemoryPoolSettings::MemoryPoolSettings(const size_t smallObjectPoolSize,
                                               const size_t smallObjectPageSize,
                                               const size_t smallObjectBlockSize,
                                               const size_t mediumObjectPoolSize,
                                               const size_t mediumObjectPageSize,
                                               const size_t mediumObjectBlockSize,
                                               const size_t largeObjectPoolSize,
                                               const size_t largeObjectPageSize,
                                               const size_t largeObjectBlockSize)
            : smallObjectPoolSize(smallObjectPoolSize), smallObjectPageSize(smallObjectPageSize),
              smallObjectBlockSize(smallObjectBlockSize), mediumObjectPoolSize(mediumObjectPoolSize),
              mediumObjectPageSize(mediumObjectPageSize), mediumObjectBlockSize(mediumObjectBlockSize),
              largeObjectPoolSize(largeObjectPoolSize), largeObjectPageSize(largeObjectPageSize),
              largeObjectBlockSize(largeObjectBlockSize)
        {
            CHECK_GT(smallObjectBlockSize, 0);
            CHECK_GT(mediumObjectBlockSize, 0);
            CHECK_GT(largeObjectBlockSize, 0);

            CHECK_GT(smallObjectPageSize, smallObjectBlockSize);
            CHECK_GT(mediumObjectPageSize, mediumObjectBlockSize);
            CHECK_GT(largeObjectPageSize, largeObjectBlockSize);

            CHECK_GE(smallObjectPoolSize, smallObjectPageSize);
            CHECK_GE(mediumObjectPoolSize, mediumObjectPageSize);
            CHECK_GE(largeObjectPoolSize, largeObjectPageSize);
        }
    }
}
