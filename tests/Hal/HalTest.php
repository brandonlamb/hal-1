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
 * HalTest
 *
 * @package Hal
 * @subpackage Tests
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
class HalTest extends \PHPUnit_Framework_TestCase
{
    public function testHalJsonResponseAllowsNoSelfLink()
    {
        $hal = new Hal\Resource();
        $this->assertEquals('[]', $hal->asJson());
    }

    public function testHalResponseReturnsSelfLinkJson()
    {
        $hal = new Hal\Resource('http://example.com/');
        $this->assertEquals('{"_links":{"self":{"href":"http:\/\/example.com\/"}}}', $hal->asJson());
    }

    public function testAddLinkJsonResponse()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->addLink('test', '/test/1');

        $result = json_decode($hal->asJson());
        $this->assertInstanceOf('StdClass', $result->_links->test);
        $this->assertEquals('/test/1', $result->_links->test->href);
    }

    public function testResourceJsonResponse()
    {
        $hal = new Hal\Resource('http://example.com/');
        $res = new Hal\Resource('/resource/1', array('field1' => 'value1', 'field2' => 'value2'));
        $hal->addResource('resource', $res);

        $resource = json_decode($hal->asJson());
        $this->assertInstanceOf('StdClass', $resource->_embedded);
        $this->assertInternalType('array', $resource->_embedded->resource);
        $this->assertEquals($resource->_embedded->resource[0]->_links->self->href, '/resource/1');
        $this->assertEquals($resource->_embedded->resource[0]->field1, 'value1');
        $this->assertEquals($resource->_embedded->resource[0]->field2, 'value2');
    }

    public function testEmbeddedResourceInResourceJsonResponse()
    {
        $hal = new Hal\Resource('http://example.com/');
        $res = new Hal\Resource('/resource/1', array('field1' => 'value1', 'field2' => 'value2'));
        $res->addResource(
            'item',
            new Hal\Resource(
                '/resource/1/item/1',
                array(
                    'itemField1' => 'itemValue1'
                )
            )
        );

        $hal->addResource('resource', $res);
        $result = json_decode($hal->asJson());
        $this->assertInternalType('array', $result->_embedded->resource[0]->_embedded->item);
        $this->assertEquals('/resource/1/item/1', $result->_embedded->resource[0]->_embedded->item[0]->_links->self->href);
        $this->assertEquals('itemValue1', $result->_embedded->resource[0]->_embedded->item[0]->itemField1);
    }

    public function testAddingDataToRootResource()
    {
        $hal = new Hal\Resource(
            '/root',
            array(
                'firstname' => 'Ben',
                'surname' => 'Longden'
            )
        );

        $result = json_decode($hal->asJson(true));
        $this->assertEquals('Ben', $result->firstname);
        $this->assertEquals('Longden', $result->surname);
    }

    public function testAddArrayOfLinksInJson()
    {
        $hal = new Hal\Resource('/');
        $hal->addLink('members', '/member/1');
        $hal->addLink('members', '/member/2');

        $result = json_decode($hal->asJson());
        $this->assertEquals('/member/1', $result->_links->members[0]->href);
        $this->assertEquals('/member/2', $result->_links->members[1]->href);
    }

    public function testLinkAttributesInJson()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->addLink('test', '/test/{?id}', array(
            'anchor' => '#foo',
            'rev' => 'canonical',
            'hreflang' => 'en',
            'media' => 'screen',
            'type' => 'text/html',
            'templated' => 'true',
            'name' => 'ex',
            'title' => 'My Test'
        ));

        $result = json_decode($hal->asJson());
        $this->assertEquals('#foo', $result->_links->test->anchor);
        $this->assertEquals('canonical', $result->_links->test->rev);
        $this->assertEquals('en', $result->_links->test->hreflang);
        $this->assertEquals('screen', $result->_links->test->media);
        $this->assertEquals('text/html', $result->_links->test->type);
        $this->assertEquals('true', $result->_links->test->templated);
        $this->assertEquals('ex', $result->_links->test->name);
        $this->assertEquals('My Test', $result->_links->test->title);
    }

    public function testLinkAttributesInJsonWithArrayOfLinks()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->addLink('test', '/test/{?id}', array(
            'anchor' => '#foo1',
            'rev' => 'canonical1',
            'hreflang' => 'en1',
            'media' => 'screen1',
            'type' => 'text/html1',
            'templated' => 'true1',
            'name' => 'ex1',
        ));
        $hal->addLink('test', '/test/{?id}', array(
            'anchor' => '#foo2',
            'rev' => 'canonical2',
            'hreflang' => 'en2',
            'media' => 'screen2',
            'type' => 'text/html2',
            'templated' => 'true2',
            'name' => 'ex2',
        ));

        $result = json_decode($hal->asJson());
        $i = 1;
        foreach ($result->_links->test as $testLink) {
            $this->assertEquals('#foo' . $i, $testLink->anchor);
            $this->assertEquals('canonical' . $i, $testLink->rev);
            $this->assertEquals('en' . $i, $testLink->hreflang);
            $this->assertEquals('screen' . $i, $testLink->media);
            $this->assertEquals('text/html' . $i, $testLink->type);
            $this->assertEquals('true' . $i, $testLink->templated);
            $this->assertEquals('ex' . $i, $testLink->name);
            $i++;
        }
    }

    public function testMinimalHalJsonDecoding()
    {
        $sample = '{"_links":{"self":{"href":"http:\/\/example.com\/"}}}';
        $hal = Hal\Resource::fromJson($sample);
        $this->assertEquals($sample, $hal->asJson());
    }

    public function testHalJsonDecodeWithData()
    {
        $sample = '{"_links":{"self":{"href":"http:\/\/example.com\/"}},"key":"value"}';
        $data = Hal\Resource::fromJson($sample)->getData();
        $this->assertEquals('value', $data['key']);
    }

    public function testHalJsonDecodeWithLinks()
    {
        $x = new Hal\Resource('/test', array('name' => "Ben Longden"));
        $x->addLink('a', '/a');
        $y = Hal\Resource::fromJson($x->asJson());

        $this->assertEquals($x->asJson(true), $y->asJson(true));
    }

    /**
     * @todo uncomment xml stuff
     */
    public function testBooleanOutput()
    {
        $hal = new Hal\Resource('/', array(
            'foo' => true,
            'bar' => false
        ));

#        $xml = new \SimpleXMLElement($hal->asXml());
#        $this->assertSame('1', (string)$xml->foo);
#        $this->assertSame('0', (string)$xml->bar);

        $json = json_decode($hal->asJson());
        $this->assertTrue($json->foo);
        $this->assertFalse($json->bar);
    }

    public function testAddCurieConformsToSpecification()
    {
        $x = new Hal\Resource('/orders');
        $x->addCurie('acme', 'http://docs.acme.com/relations/{rel}');
        $obj = json_decode($x->asJson());
        $this->assertInternalType('array', $obj->_links->curies);
        $this->assertTrue($obj->_links->curies[0]->templated);
        $this->assertEquals('acme', $obj->_links->curies[0]->name);
        $this->assertEquals('http://docs.acme.com/relations/{rel}', $obj->_links->curies[0]->href);
    }

    public function testGetLinkByRelation()
    {
        $x = new Hal\Resource('/orders');
        $x->addLink('test', '/test/orders');

        $links = $x->getLink('test');
        $this->assertEquals('/test/orders', $links[0]);
    }

    public function testGetLinkByCurieRelation()
    {
        $x = new Hal\Resource('/orders');
        $x->addCurie('acme', 'http://docs.acme.com/relations/{rel}');
        $x->addLink('acme:test', '/widgets');

        $links = $x->getLink('http://docs.acme.com/relations/test');
        $this->assertEquals('/widgets', $links[0]);
    }

    public function testGetLinkReturnsFalseOnFailure()
    {
        $x = new Hal\Resource('/orders');
        $this->assertFalse($x->getLink('test'));
    }

    public function testJSONEmptyEmbeddedCollection(){
        $x = new Hal\Resource();
        $x->addResource('collection', new Hal\Resource());

        $this->assertEquals('{"_embedded":{"collection":[]}}', $x->asJson());
    }

    public function testLinksWithAttributesUnserialiseCorrectlyJson()
    {
        $x = new Hal\Resource('/');
        $x->addCurie('x:test', 'http://test');

        $this->assertEquals($x->asJson(), Hal\Resource::fromJson($x->asJson())->asJson());
    }

    public function testResourceWithNullSelfLinkRendersLinksInJson()
    {
        $x = new Hal\Resource(null);
        $x->addLink('testrel', 'http://test');
        $data = json_decode($x->asJson());
        $this->assertEquals('http://test', $data->_links->testrel->href);
    }
}
