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
 * Hal\Resource
 * The Hal resource document class
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */

abstract class ResourceFactory
{
    /**
     * Decode a application/hal+json document into a Hal\Resource object.
     *
     * @param string text
     * @param int maxDepth
     * @return Hal\Resource
     */
    public static function fromJson($text, $maxDepth = 0) {}
}
