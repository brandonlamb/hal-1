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

namespace Hal\Tests;

use Hal;

/**
 * ResourceTest
 *
 * @package Hal
 * @subpackage Tests
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
class ResourceTest extends \PHPUnit_Framework_TestCase
{
    public $uri;
    public $data;

    public function setUp()
    {
        $this->uri = 'http://example.com/v1/example';
        $this->data = [
            'name' => 'Example Name',
            'number' => 12345,
        ];
    }

    /**
     * @covers \Hal\Resource::__construct
     * @covers \Hal\Resource::getUri
     * @covers \Hal\Resource::getData
     */
    public function testConstruct()
    {
        $res = new Hal\Resource();
        $this->assertEmpty($res->getUri());
        $this->assertEmpty($res->getData());

        $res = new Hal\Resource($this->uri);
        $this->assertEquals($this->uri, $res->getUri());

        $res = new Hal\Resource($this->uri, $this->data);
        $this->assertEquals($this->uri, $res->getUri());
        $this->assertEquals($this->data, $res->getData());
    }

    /**
     * @covers Hal\Resource::addLink
     * @covers Hal\Resource::getLink
     */
    public function testGetLinkByRelation()
    {
        $x = new Hal\Resource('/orders');
        $x->addLink('test', '/test/orders');

        $links = $x->getLink('test');
        $this->assertEquals('/test/orders', $links[0]);
    }

    /**
     * @covers Hal\Resource::addCurie
     * @covers Hal\Resource::addLink
     * @covers Hal\Resource::getLink
     */
    public function testGetLinkByCurieRelation()
    {
        $x = new Hal\Resource('/orders');
        $x->addCurie('acme', 'http://docs.acme.com/relations/{rel}');
        $x->addLink('acme:test', '/widgets');

        $links = $x->getLink('http://docs.acme.com/relations/test');
        $this->assertEquals('/widgets', $links[0]);
    }

    /**
     * @covers Hal\Resource::getLink
     */
    public function testGetLinkReturnsFalseOnFailure()
    {
        $x = new Hal\Resource('/orders');
        $this->assertFalse($x->getLink('test'));
    }
}
