#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void load(Identifier id, const std::string &filename)
    {
        std::unique_ptr<Resource> res(new Resource());
        if (!res->loadFromFile(filename))
            throw std::runtime_error("ResourceHolder failed to load resource " + filename);
        insertResource(id, std::move(res));
    }

    Resource& get(Identifier id)
    {
        auto found = resourceMap.find(id);
        assert(found != resourceMap.end());
        return *found->second;
    }

    const Resource& get(Identifier id) const
    {
        auto found = resourceMap.find(id);
        assert(found != resourceMap.end());
        return *found->second;
    }

private:
    void insertResource(Identifier id, std::unique_ptr<Resource> res)
    {
        auto inserted = resourceMap.insert(std::make_pair(id, std::move(res)));
        assert(inserted.second);
    }

private:
    std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
};

