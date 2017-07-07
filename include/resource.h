/**
 * @file resource.h
 * @author Daniel Monzonís
 */

#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

/**
 * @brief Abstract class to load and hold resources in memory like textures,
 * fonts and sounds.
 *
 * ResourceHolder is a template for classes that manage external resources
 * like images or sound. It has methods to load resources from a path and to
 * get previously loaded resources with an identifier. Types using this template
 * prepared for use for all used resources are defined in @ref
 * resource_identifiers.h
 *
 * @tparam Resource The type of resource to load, for example, sf::Texture.
 * @tparam One of the identifier types defined in @ref resource_identifiers.h
 */
template <typename Resource, typename Identifier> class ResourceHolder {
 public:
    /**
     * @brief Load texture from a path and assign it to an identifier.
     *
     * It uses SFML's loadFromFile function.
     *
     * @param id Identifier to assign the resource to. The resource can
     * later be accessed using this identifier with Resource::get.
     * @param filename Path to the resource. It can be a relative or an
     * absolute path.
     */
    void load(Identifier id, const std::string &filename) {
        std::unique_ptr<Resource> res(new Resource());
        if (!res->loadFromFile(filename))
            throw std::runtime_error("ResourceHolder failed to load resource " +
                                     filename);
        insertResource(id, std::move(res));
    }

    /**
     * Returns a reference to the resource assigned to an identifier. Will
     * return an assertion error if the identifier is not associated with any
     * previously loaded resource.
     *
     * @param id Identifier associated with the resource to retrieve.
     *
     * @return Reference to the resource assigned to the identifier passed in
     * the argument.
     */
    Resource &get(Identifier id) {
        auto found = resourceMap.find(id);
        assert(found != resourceMap.end());
        return *found->second;
    }

    /**
      * Returns a constant reference to the resource assigned to an identifier.
      * Will return an assertion error if the identifier is not associated with
      * any previously loaded resource.
      *
      * @param id Identifier associated with the resource to retrieve.
      *
      * @return Constant reference to the resource assigned to the identifier
      * passed in the argument.
      */
    const Resource &get(Identifier id) const {
        auto found = resourceMap.find(id);
        assert(found != resourceMap.end());
        return *found->second;
    }

 private:
    void insertResource(Identifier id, std::unique_ptr<Resource> res) {
        auto inserted = resourceMap.insert(std::make_pair(id, std::move(res)));
        assert(inserted.second);
    }

 private:
    std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
};
