<?php
/**
 * This file is part of the Hal library
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * @package Hal
 */

namespace Hal\Tests\Collection;

use Hal;

/**
 * LinkTest
 *
 * @package Hal
 * @subpackage Tests\Collection
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
class LinkTest extends \PHPUnit_Framework_TestCase
{
    public $uri;
    public $attribs;

    /**
     * setup for tests
     */
    public function setUp()
    {
    }

    /**
     * Test instantiating a collection
     *
     * @covers \Hal\Collection\Link::__construct
     * @covers \Hal\Collection\Link::count
     */
    public function testConstructParams()
    {
        $collection = new Hal\Collection\Link();
        $this->assertEmpty($collection->getData());
        $this->assertEquals(0, count($collection));
        $this->assertEquals(0, $collection->count());

        $collection = new Hal\Collection\Link([]);
        $this->assertEmpty($collection->getData());

        $collection = new Hal\Collection\Link(null);
        $this->assertEmpty($collection->getData());

        $collection = new Hal\Collection\Link();
        $collection->add('pass', new Hal\Link('/example'));
        $this->assertEquals(1, count($collection));
        $this->assertEquals(1, $collection->count());
    }

    /**
     * Test getting a link
     *
     * @covers \Hal\Collection\Link::add
     * @covers \Hal\Collection\Link::getData
     */
    public function testAdd()
    {
        $collection = new Hal\Collection\Link();
        $collection->add('pass', new Hal\Link('/example'));
        $this->assertArrayHasKey('pass', $collection->getData());

        // Must pass a Hal\Link to add()
        $collection = new Hal\Collection\Link();
        $e = null;
        try {
            $collection->add('pass');
        } catch (\BadMethodCallException $e) {
        }
        $this->assertInstanceOf('\BadMethodCallException', $e);
    }

    /**
     * Test getting a link by relation
     *
     * @covers \Hal\Collection\Link::get
     * @covers \Hal\Collection\Link::add
     */
    public function testGet()
    {
        $collection = new Hal\Collection\Link();
        $this->assertFalse($collection->get('fail'));

        $collection->add('pass', new Hal\Link('/example'));
        $link = $collection->get('pass');
        $this->assertInstanceOf('Hal\\Link', $link[0]);
    }

    /**
     * Test setting a curie link
     *
     * @covers \Hal\Collection\Link::add
     * @covers \Hal\Collection\Link::get
     */
    public function testAddCurie()
    {
        $collection = new Hal\Collection\Link();
        $collection->add('curies', new Hal\Link('http://docs.acme.com/relations/{rel}', ['name' => 'acme', 'templated' => true]));
        $collection->add('acme:test', new Hal\Link('/widgets'));

        $this->assertArrayHasKey('curies', $collection->getData());
        $links = $collection->get('http://docs.acme.com/relations/test');
        $this->assertEquals('/widgets', $links[0]);
    }
}
