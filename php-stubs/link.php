<?php
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
    protected $uri;

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
    protected $attributes;

    /**
     * Supported attributes in Hal (specification section 5).
     *
     * @param string uri The URI represented by this link.
     * @param array attributes Any additional attributes.
     */
    public function __construct($uri, $attributes = null) {}

    /**
     * Return the URI from this link.
     *
     * @return string
     */
    public function getUri() {}

    /**
     * Returns the attributes for this link.
     *
     * return array
     */
    public function getAttributes() {}

    /**
     * The string representation of this link (the URI).
     *
     * return string
     */
    public function __toString() {}
}
