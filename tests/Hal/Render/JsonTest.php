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

namespace Hal\Tests\Render;

use Hal;

/**
 * HalTest
 *
 * @package Hal
 * @subpackage Tests
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
class JsonTest extends \PHPUnit_Framework_TestCase
{
    /**
     * Test rendering of essentially a blank Hal resource
     *
     * @covers \Hal\Resource::render
     */
    public function testHalJsonResponseAllowsNoSelfLink()
    {
        $hal = new Hal\Resource();
        $this->assertEquals('[]', $hal->render());
    }

    /**
     *
     * @covers \Hal\Resource::render
     */
    public function testHalResponseReturnsSelfLinkJson()
    {
        $hal = new Hal\Resource('http://example.com/');
        $this->assertEquals('{"_links":{"self":{"href":"http:\/\/example.com\/"}}}', $hal->render());
    }

    public function testHalResponseReturnsSelfLinkXml()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->setRenderer(new Hal\Render\Xml());
        $this->assertEquals("<?xml version=\"1.0\"?>\n<resource href=\"http://example.com/\"/>\n", $hal->render());
    }

    public function testAddLinkJsonResponse()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->addLink('test', '/test/1');

        $result = json_decode($hal->render());
        $this->assertInstanceOf('StdClass', $result->_links->test);
        $this->assertEquals('/test/1', $result->_links->test->href);
    }

    public function testAddLinkXmlResponse()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->setRenderer(new Hal\Render\Xml());
        $hal->addLink('test', '/test/1');

        $result = new \SimpleXmlElement($hal->render());
        $data = $result->link->attributes();
        $this->assertEquals('test', $data['rel']);
        $this->assertEquals('/test/1', $data['href']);
    }

    public function testXmlPrettyPrintResponse()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->setRenderer(new Hal\Render\Xml());
        $hal->addLink('test', '/test/1');

        $response = <<<EOD
<?xml version="1.0"?>
<resource href="http://example.com/">
  <link rel="test" href="/test/1"/>
</resource>

EOD;
        $this->assertEquals($response, $hal->render(true));
    }

    public function testResourceJsonResponse()
    {
        $hal = new Hal\Resource('http://example.com/');
        $res = new Hal\Resource('/resource/1', array('field1' => 'value1', 'field2' => 'value2'));
        $hal->addResource('resource', $res);

        $resource = json_decode($hal->render());
        $this->assertInstanceOf('StdClass', $resource->_embedded);
        $this->assertInternalType('array', $resource->_embedded->resource);
        $this->assertEquals($resource->_embedded->resource[0]->_links->self->href, '/resource/1');
        $this->assertEquals($resource->_embedded->resource[0]->field1, 'value1');
        $this->assertEquals($resource->_embedded->resource[0]->field2, 'value2');
    }

    public function testResourceXmlResponse()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->setRenderer(new Hal\Render\Xml());
        $res = new Hal\Resource('/resource/1', array('field1' => 'value1', 'field2' => 'value2'));
        $hal->addResource('resource', $res);

        $result = new \SimpleXmlElement($hal->render());
        $this->assertEquals('/resource/1', $result->resource->attributes()->href);
        $this->assertEquals('value1', $result->resource->field1);
        $this->assertEquals('value2', $result->resource->field2);
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
        $result = json_decode($hal->render());
        $this->assertInternalType('array', $result->_embedded->resource[0]->_embedded->item);
        $this->assertEquals('/resource/1/item/1', $result->_embedded->resource[0]->_embedded->item[0]->_links->self->href);
        $this->assertEquals('itemValue1', $result->_embedded->resource[0]->_embedded->item[0]->itemField1);
    }

    public function testEmbeddedResourceInResourceXmlResponse()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->setRenderer(new Hal\Render\Xml());
        $res = new Hal\Resource('/resource/1', array('field1' => 'value1', 'field2' => 'value2'));
        $res->addResource(
            'item',
            new Hal\Resource(
                '/resource/1/item/1',
                array(
                    'items' => array(
                        array(
                            'itemField1' => 'itemValue1'
                        )
                    )
                )
            )
        );

        $hal->addResource('resource', $res);
        $result = new \SimpleXmlElement($hal->render());
        $this->assertEquals('item', $result->resource->resource->attributes()->rel);
        $this->assertEquals('/resource/1/item/1', $result->resource->resource->attributes()->href);
        $this->assertEquals('itemValue1', $result->resource->resource->items[0]->itemField1);
    }

    public function testResourceWithListRendersCorrectlyInXmlResponse()
    {
        $hal = new Hal\Resource('/orders');
        $hal->setRenderer(new Hal\Render\Xml());
        $hal->addLink('next', '/orders?page=2');
        $hal->addLink('search', '/orders?id={order_id}');

        $resource = new Hal\Resource(
            '/orders/123',
            array(
                'tests' => array(
                    array(
                        'total' => 30.00,
                        'currency' => 'USD'
                    ),
                    array(
                        'total' => 40.00,
                        'currency' => 'GBP'
                    )
                )
            )
        );
        $resource->addLink('customer', '/customer/bob');
        $hal->addResource('order', $resource);
        $result = new \SimpleXmlElement($hal->render());
        $this->assertEquals(30, (string)$result->resource->tests[0]->total);
        $this->assertEquals('USD', (string)$result->resource->tests[0]->currency);
        $this->assertEquals(40, (string)$result->resource->tests[1]->total);
        $this->assertEquals('GBP', (string)$result->resource->tests[1]->currency);
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

        $result = json_decode($hal->render(true));
        $this->assertEquals('Ben', $result->firstname);
        $this->assertEquals('Longden', $result->surname);
    }

    public function testAddArrayOfLinksInJson()
    {
        $hal = new Hal\Resource('/');
        $hal->addLink('members', '/member/1');
        $hal->addLink('members', '/member/2');

        $result = json_decode($hal->render());
        $this->assertEquals('/member/1', $result->_links->members[0]->href);
        $this->assertEquals('/member/2', $result->_links->members[1]->href);
    }

    public function testAddArrayOfLinksInXml()
    {
        $hal = new Hal\Resource('/');
        $hal->setRenderer(new Hal\Render\Xml());
        $hal->addLink('members', '/member/1');
        $hal->addLink('members', '/member/2');
        $result = new \SimpleXmlElement($hal->render());
        $this->assertEquals('members', $result->link[0]->attributes()->rel);
        $this->assertEquals('members', $result->link[1]->attributes()->rel);
        $this->assertEquals('/member/1', $result->link[0]->attributes()->href);
        $this->assertEquals('/member/2', $result->link[1]->attributes()->href);
    }

    public function testAttributesInXmlRepresentation()
    {
        $hal = new Hal\Resource(
            '/',
            array(
                'error' => array(
                    '@id' => 6,
                    '@xml:lang' => 'en',
                    'message' => 'This is a message'
                )
            )
        );
        $hal->setRenderer(new Hal\Render\Xml());

        $xml = new \SimpleXMLElement($hal->render());
        $this->assertEquals(6, (string)$xml->error->attributes()->id);
        $this->assertEquals('en', (string)$xml->error->attributes()->lang);
        $this->assertEquals('This is a message', (string)$xml->error->message);

        $hal->setRenderer(new Hal\Render\Json());
        $json = json_decode($hal->render(true));
        $this->assertEquals(6, $json->error->id);
        $this->assertEquals('en', $json->error->lang);
        $this->assertEquals('This is a message', $json->error->message);
    }

    /**
     * @covers \Hal\Hal\Resource::addLink
     * @covers \Hal\HalJsonRenderer::linksForJson
     */
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

        $result = json_decode($hal->render());
        $this->assertEquals('#foo', $result->_links->test->anchor);
        $this->assertEquals('canonical', $result->_links->test->rev);
        $this->assertEquals('en', $result->_links->test->hreflang);
        $this->assertEquals('screen', $result->_links->test->media);
        $this->assertEquals('text/html', $result->_links->test->type);
        $this->assertEquals('true', $result->_links->test->templated);
        $this->assertEquals('ex', $result->_links->test->name);
        $this->assertEquals('My Test', $result->_links->test->title);
    }

    /**
     * @covers \Hal\HalJsonRenderer::linksForJson
     * Provided for code coverage
     */
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

        $result = json_decode($hal->render());
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

    /**
     * @covers \Hal\Hal\Resource::addLink
     * @covers \Hal\HalXmlRenderer::linksForXml
     */
    public function testLinkAttributesInXml()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->setRenderer(new Hal\Render\Xml());
        $hal->addLink('test', '/test/{?id}', array(
            'anchor' => '#foo',
            'rev' => 'canonical',
            'hreflang' => 'en',
            'media' => 'screen',
            'type' => 'text/html',
            'templated' => 'true',
            'name' => 'ex',
        ));

        $result = new \SimpleXmlElement($hal->render());
        $data = $result->link->attributes();
        $this->assertEquals('#foo', $data['anchor']);
        $this->assertEquals('canonical', $data['rev']);
        $this->assertEquals('en', $data['hreflang']);
        $this->assertEquals('screen', $data['media']);
        $this->assertEquals('text/html', $data['type']);
        $this->assertEquals('true', $data['templated']);
        $this->assertEquals('ex', $data['name']);
    }

    /**
     * @covers \Hal\HalXmlRenderer::linksForXml
     * Provided for code coverage.
     */
    public function testLinkAttributesInXmlWithArrayOfLinks()
    {
        $hal = new Hal\Resource('http://example.com/');
        $hal->setRenderer(new Hal\Render\Xml());
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

        $result = new \SimpleXmlElement($hal->render());
        $i = 1;
        foreach ($result->link as $link) {
            $data = $link->attributes();
            $this->assertEquals('#foo' . $i, $data['anchor']);
            $this->assertEquals('canonical' . $i, $data['rev']);
            $this->assertEquals('en' . $i, $data['hreflang']);
            $this->assertEquals('screen' . $i, $data['media']);
            $this->assertEquals('text/html' . $i, $data['type']);
            $this->assertEquals('true' . $i, $data['templated']);
            $this->assertEquals('ex' . $i, $data['name']);
            $i++;
        }
    }

    public function testNumericKeysUseParentAsXmlElementName()
    {
        $hal = new Hal\Resource('/', array(
            'foo' => array(
                'bar',
                'baz',
            ),
        ));
        $hal->setRenderer(new Hal\Render\Xml());

        $result = new \SimpleXmlElement($hal->render());

        $this->assertEquals('bar', $result->foo[0]);
        $this->assertEquals('baz', $result->foo[1]);

        $json = json_decode($hal->render(), true);

        $this->assertEquals(array('bar', 'baz'), $json['foo']);
    }

    public function testMinimalHalJsonDecoding()
    {
        $sample = '{"_links":{"self":{"href":"http:\/\/example.com\/"}}}';
        $hal = Hal\Resource::fromJson($sample);
        $this->assertEquals($sample, $hal->render());
    }

    public function testHalJsonDecodeWithData()
    {
        $sample = '{"_links":{"self":{"href":"http:\/\/example.com\/"}},"key":"value"}';
        $data = Hal\Resource::fromJson($sample)->getData();
        $this->assertEquals('value', $data['key']);
    }

    public function testMinimalHalXmlDecoding()
    {
        $sample = "<?xml version=\"1.0\"?>\n<resource href=\"http://example.com/\"/>\n";
        $hal = Hal\Resource::fromXml($sample);
        $hal->setRenderer(new Hal\Render\Xml());
        $this->assertEquals($sample, $hal->render());
    }

    public function testHalXmlDecodeWithData()
    {
        $sample = "<?xml version=\"1.0\"?>\n<resource href=\"http://example.com/\"><key>value</key></resource>\n";
        $data = Hal\Resource::fromXml($sample)->getData();
        $this->assertEquals('value', $data['key']);
    }

    public function testHalJsonDecodeWithLinks()
    {
        $x = new Hal\Resource('/test', array('name' => "Ben Longden"));
        $x->addLink('a', '/a');
        $y = Hal\Resource::fromJson($x->render());

        $this->assertEquals($x->render(true), $y->render(true));
    }

    public function testHalXmlDecodeWithLinks()
    {
        $hal = new Hal\Resource('/test', array('name' => "Ben Longden"));
        $hal->setRenderer(new Hal\Render\Xml());
        $hal->addLink('a', '/a');
        $y = Hal\Resource::fromXml($hal->render());
        $this->assertEquals($hal->render(), $y->render());
    }

    public function testHalXmlEntitySetWhenValueSpecifiedInData()
    {
        $hal = new Hal\Resource('/', array('x' => array('value' => 'test')));
        $hal->setRenderer(new Hal\Render\Xml());

        $xml = new \SimpleXMLElement($hal->render());
        $this->assertEquals('test', (string)$xml->x);
    }

    public function testHalXmlEntitySetWhenValueSpecifiedInMultiData()
    {
        $hal = new Hal\Resource('/', array('x' => array('key' => 'test', 'value' => 'test')));
        $hal->setRenderer(new Hal\Render\Xml());

        $xml = new \SimpleXMLElement($hal->render());
        $this->assertEquals('test', (string)$xml->x->key);
        $this->assertEquals('test', (string)$xml->x->value);
    }
    public function testBooleanOutput()
    {
        $hal = new Hal\Resource('/', array(
            'foo' => true,
            'bar' => false
        ));
        $hal->setRenderer(new Hal\Render\Xml());

        $xml = new \SimpleXMLElement($hal->render());
        $this->assertSame('1', (string)$xml->foo);
        $this->assertSame('0', (string)$xml->bar);

        $hal->setRenderer(new Hal\Render\Json());
        $json = json_decode($hal->render());
        $this->assertTrue($json->foo);
        $this->assertFalse($json->bar);
    }

    public function testAddCurieConformsToSpecification()
    {
        $x = new Hal\Resource('/orders');
        $x->addCurie('acme', 'http://docs.acme.com/relations/{rel}');
        $obj = json_decode($x->render());
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
        $x->addResource('collection');

        $this->assertEquals('{"_embedded":{"collection":[]}}', $x->render());
    }

    public function testXMLEmptyEmbeddedCollection(){
        $hal = new Hal\Resource();
        $hal->setRenderer(new Hal\Render\Xml());
        $hal->addResource('collection');
        $response = <<<EOD
<?xml version="1.0"?>
<resource><resource rel="collection"/></resource>

EOD;
        $this->assertEquals($response, $hal->render());
    }

    public function testLinksWithAttributesUnserialiseCorrectlyJson()
    {
        $x = new Hal\Resource('/');
        $x->addCurie('x:test', 'http://test');

        $this->assertEquals($x->render(), Hal\Resource::fromJson($x->render())->render());
    }

    public function testLinksWithAttributesUnserialiseCorrectlyXml()
    {
        $hal = new Hal\Resource('/');
        $hal->setRenderer(new Hal\Render\Xml());
        $hal->addCurie('x:test', 'http://test');

        $this->assertEquals($hal->render(), Hal\Resource::fromXml($hal->render())->render());
    }

    public function testResourceWithNullSelfLinkRendersLinksInJson()
    {
        $x = new Hal\Resource(null);
        $x->addLink('testrel', 'http://test');
        $data = json_decode($x->render());
        $this->assertEquals('http://test', $data->_links->testrel->href);
    }
}
