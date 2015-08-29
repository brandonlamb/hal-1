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

namespace Hal\Render;

use Hal\RenderInterface;

/**
 * Hal\Render\Json
 * Renders a Hal\Resource into an array that is valid for application/json+hal
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */

class Json implements RenderInterface
{
    /**
     * Render.
     *
     * @param Hal\Resource $resource
     * @param bool pretty
     * @return string
     */
    public function render($resource, $pretty = false) {}

    /**
     * Return an array (compatible with the hal+json format) representing the
     * complete response.
     *
     * @param Hal\Resource resource
     * @return array
     */
    protected function parseResource($resource) {}

    /**
     * Return an array (compatible with the hal+json format) representing
     * associated links.
     *
     * @param string uri
     * @param array links
     * @return array
     */
    protected function parseLinks($uri, $collection) {}

    /**
     * Return an array (compatible with the hal+json format) representing associated resources.
     *
     * [
     *   'rel1' => [res1, res2],
     *   'rel2' => [res1, res2],
     * ]
     *
     * @param mixed resources
     * @return array
     */
    protected function parseResources($resources) {}


    /**
     * Loop through array of resources and pase into array
     *
     * @param array resources
     * @return array
     */
    protected function arrayFromResources($resources) {}

    /**
     * Remove the @ prefix from keys that denotes an attribute in XML. This
     * cannot be represented in JSON, so it's effectively ignored.
     *
     * @param array data The array to strip @ from the keys.
     * @return array
     */
    protected function stripAttributeMarker($data) {}
}
