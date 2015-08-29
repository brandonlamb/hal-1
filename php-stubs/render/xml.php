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

use Hal\Resource;
use Hal\RenderInterface;
/**
 * Hal\Render\Xml
 * Renders a Hal\Resource into an xml string that is valid for application/xml+hal
 *
 * @package Hal\Render
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */

class Xml implements RenderInterface
{
    /**
     * Render.
     *
     * @param Hal\Resource resource
     * @param bool pretty
     * @return string
     */
    public function render(Resource $resource, $pretty) {}

    /**
     * parseLinks
     *
     * Add links in hal+xml format to a SimpleXmlElement object.
     *
     * @param \SimpleXmlElement doc
     * @param Hal\Collection\Link links
     * @return void
     */
    protected function parseLinks($doc, $collection) {}

    /**
     * arrayToXml
     *
     * @param array $data
     * @param \SimpleXmlElement element
     * @param mixed parent
     * @access protected
     * @return void
     */
    protected function arrayToXml($data, $element, $parent = null) {}

    /**
     * resourcesForXml
     *
     * Add resources in hal+xml format (identified by rel) to a
     * SimpleXmlElement object.
     *
     * @param \SimpleXmlElement doc
     * @param mixed rel
     * @param array resources
     */
    protected function resourcesForXml($doc, $rel, $resources) {}
}
