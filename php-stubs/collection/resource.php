<?php
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

use Hal\Resource;
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
    protected $data;

    /**
     * Constructor
     * @param array data
     */
    public function __construct() {}

    /**
     * Return the array of links
     * @return array
     */
    public function getData() {}

    /**
     * Retrieve a collection of resources by rel.
     *
     * @param string rel The resource relation required
     * @return array|bool Array of resources if found, otherwise false
     */
    public function get($rel) {}

    /**
     * Add a resource to the collection of resources
     *
     * @param string rel
     * @param Hal\Resource resource
     * @param bool multi
     */
    public function add($rel, Resource $resource, $multi = true) {}

    /**
     * Returns the number of annotations in the collection
     *
     * @return int
     */
    public function count() {}
}
