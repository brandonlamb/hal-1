/**
 * This file is part of the Hal library
 *
 * (c) Ben Longden <ben@nocarrier.co.uk
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * @package Nocarrier
 */

namespace Hal\Collection;

/**
 * Hal\Collection\Resource
 * Provides storage of arrays of Hal\Resource objects
 *
 * @package Hal
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */

class Resource implements \Countable
{
    /**
     * @var array
     */
    protected data;

    /**
     * Constructor
     * @param array data
     */
    public function __construct()
    {
        let this->data = [];
    }

    /**
     * Return the array of links
     * @return array
     */
    public function getData()
    {
        return this->data;
    }

    /**
     * Retrieve a collection of resources by rel.
     *
     * @param string rel The resource relation required
     * @return array|bool Array of resources if found, otherwise false
     */
    public function get(string rel)
    {
        var resources;

        // If the relation exists in the container, return it
        if fetch resources, this->data[rel] {
            return resources;
        }

        return false;
    }

    /**
     * Add a resource to the collection of resources
     *
     * @param string rel
     * @param Hal\Resource resource
     * @param bool multi
     */
    public function add(string rel, <Hal\Resource> resource, boolean multi = true) -> void
    {
        var value;

        // If setting an array element and the rel exists, add to the array
        if multi == true && fetch value, this->data[rel] {
            let value[] = resource;
            let this->data[rel] = value;
        } else {
            if multi == true {
                // Adding an an array of resources and did not already exist, add new array with resource
                let this->data[rel] = [resource];
            } else {
                // Adding a single resource
                let this->data[rel] = resource;
            }
        }
    }

    /**
     * Returns the number of annotations in the collection
     *
     * @return int
     */
    public function count() -> int
    {
        return count(this->data);
    }
}
