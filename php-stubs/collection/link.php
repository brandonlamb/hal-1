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

use Hal\Link;
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
     * Retrieve a link from the container by rel. Also resolve any curie links if they are set.
     *
     * @param string rel The link relation required
     * @return array|bool Link if found, therwise false
     */
    public function get($rel) {}

    /**
     * Add a value to an offset
     *
     * @param string rel
     * @param Hal\Link link
     */
    public function add($rel, Link $link) {}

    /**
     * Returns the number of annotations in the collection
     *
     * @return int
     */
    public function count() {}
}
