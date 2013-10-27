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
 * Hal\Collection\Link
 * Provides storage of arrays of Hal\Link objects
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */

class Link implements \Countable
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
     * Retrieve a link from the container by rel. Also resolve any curie links if they are set.
     *
     * @param string rel The link relation required
     * @return array|bool Link if found, therwise false
     */
    public function get(string rel)
    {
        var prefix, link, shortRel, attrs, curie;

        // If the relation exists in the container, return it
        if fetch link, this->data[rel] {
            return link;
        }

        // If the curies key exists, loop through each key
        if isset this->data["curies"] {
            for link in this->data["curies"] {
                let prefix = strstr(link->getUri(), "{rel}", true);

                if strpos(rel, prefix) == 0 {
                    // looks like it is
                    let shortRel = substr(rel, strlen(prefix));
                    let attrs = link->getAttributes();
                    if isset attrs["name"] {
                        let curie = attrs["name"] . ":" . shortRel;
                        if isset this->data[curie] {
                            return this->data[curie];
                        }
                    }
                }
            }
        }

        return false;
    }

    /**
     * Add a value to an offset
     *
     * @param string rel
     * @param Hal\Link link
     */
    public function add(string rel, <Hal\Link> link) -> void
    {
        var value;
        if fetch value, this->data[rel] {
            let value[] = link;
            let this->data[rel] = value;
        } else {
            let this->data[rel] = [link];
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
