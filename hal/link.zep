/**
 * This file is part of the Hal library
 *
 * (c) Ben Longden <ben@nocarrier.co.uk
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * @package Hal
 */

namespace Hal;

/**
 * Hal\Link
 * Represents a link in the _links property of a Hal\Resource
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */

class Link
{
    /**
     * The URI represented by this Hal\Link.
     *
     * @var string
     */
    protected uri;

    /**
     * Any attributes on this link.
     *
     * [
     *    'templated' => 0,
     *    'type' => 'application/hal+json',
     *    'deprecation' => 1,
     *    'name' => 'latest',
     *    'profile' => 'http://.../profile/order',
     *    'title' => 'The latest order',
     *    'hreflang' => 'en'
     * ]
     *
     * @var array
     */
    protected attributes;

    /**
     * Supported attributes in Hal (specification section 5).
     *
     * @param string uri The URI represented by this link.
     * @param array attributes Any additional attributes.
     */
    public function __construct(string! uri, var attributes = null)
    {
        var rel, attrib;

        let this->uri = uri;

        let this->attributes = [];
        if typeof attributes == "array" {
            for rel, attrib in attributes {
                if typeof attrib == "array" || attrib != null {
                    let this->attributes[rel] = attrib;
                }
            }
        }
    }

    /**
     * Return the URI from this link.
     *
     * @return string
     */
    public function getUri() -> string
    {
        return this->uri;
    }

    /**
     * Returns the attributes for this link.
     *
     * return array
     */
    public function getAttributes()
    {
        return this->attributes;
    }

    /**
     * The string representation of this link (the URI).
     *
     * return string
     */
    public function __toString() -> string
    {
        return this->uri;
    }
}
