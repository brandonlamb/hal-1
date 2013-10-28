<?php
/**
 * This file is part of the Hal library
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * @package Hal
 */

namespace Hal\Tests;

use Hal;

/**
 * LinkTest
 *
 * @package Hal
 * @subpackage Tests
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
class JsonTest extends \PHPUnit_Framework_TestCase
{
    public $uri;
    public $attribs;

    /**
     * setup for tests
     */
    public function setUp()
    {
        $this->uri = '/example';
        $this->attribs = [
            'one' => 1,
            'two' => 2,
        ];
    }

    /**
     * Test instantiating with no params
     *
     * @covers \Hal\Link::__construct
     */
    public function testConstructNoParams()
    {
        try {
            $hal = new Hal\Link();
            $e = null;
        } catch (\BadMethodCallException $e) {
        }
        $this->assertInstanceOf('\BadMethodCallException', $e);
    }

    /**
     * Test instantiating with proper parameters
     *
     * @covers \Hal\Link::__construct
     */
    public function testConstruct()
    {
        $hal = new Hal\Link($this->uri);
        $this->assertInstanceOf('Hal\Link', $hal);

        $hal = new Hal\Link($this->uri, $this->attribs);
        $this->assertInstanceOf('Hal\Link', $hal);

        // Cant pass a non-string
        $e = null;
        try {
            $hal = new Hal\Link([]);
        } catch (\InvalidArgumentException $e) {
        }
        $this->assertInstanceOf('\InvalidArgumentException', $e);

        // Cant pass a non-string
        $e = null;
        try {
            $hal = new Hal\Link(null);
        } catch (\InvalidArgumentException $e) {
        }
        $this->assertInstanceOf('\InvalidArgumentException', $e);
    }

    /**
     * Test fetching uri
     *
     * @covers \Hal\Link::getUri
     */
    public function testGetUri()
    {
        $hal = new Hal\Link($this->uri, $this->attribs);
        $this->assertEquals($this->uri, $hal->getUri());

        $hal = new Hal\Link($this->uri);
        $this->assertEquals($this->uri, $hal->getUri());
    }

    /**
     * Test fetching uri via magic toString
     *
     * @covers \Hal\Link::__toString
     */
    public function testToString()
    {
        $hal = new Hal\Link($this->uri);
        $this->assertEquals($this->uri, $hal->__toString());

        $hal = new Hal\Link($this->uri);
        $this->assertEquals($this->uri, (string) $hal);
    }

    /**
     * Test fetching attributes
     *
     * @covers \Hal\Link::getAttributes
     */
    public function testGetAttributes()
    {
        $hal = new Hal\Link($this->uri, $this->attribs);
        $attribs = $hal->getAttributes();

        $this->assertEquals($this->attribs, $attribs);
        $this->assertEquals($this->attribs['one'], $attribs['one']);
    }
}
