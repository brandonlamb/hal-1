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

/**
 * Hal\Render\Xml
 * Renders a Hal\Resource into an xml string that is valid for application/xml+hal
 *
 * @package Hal\Render
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */

class Xml implements Hal\RenderInterface
{
    /**
     * Render.
     *
     * @param Hal\Resource resource
     * @param bool pretty
     * @return string
     */
    public function render(<Hal\Resource> resource, boolean pretty)
    {
        var doc, dom, ownerDocument, uri, rel, resources;

        let doc = new \SimpleXMLElement("<resource></resource>");
        let uri = resource->getUri();
        if typeof uri != "null" {
            doc->addAttribute("href", resource->getUri());
        }

        this->linksForXml(doc, resource->getLinks());
        this->arrayToXml(resource->getData(), doc);

        for rel, resources in resource->getResources() {
            this->resourcesForXml(doc, rel, resources);
        }

        let dom = dom_import_simplexml(doc);
        if pretty {
            let ownerDocument = dom->ownerDocument;
            let ownerDocument->preserveWhiteSpace = false;
            let ownerDocument->formatOutput = true;
        }

        return dom->ownerDocument->saveXML();
    }

    /**
     * linksForXml
     *
     * Add links in hal+xml format to a SimpleXmlElement object.
     *
     * @param \SimpleXmlElement doc
     * @param Hal\Collection\Link links
     * @return void
     */
    protected function linksForXml(<\SimpleXmlElement> doc, <Hal\Collection\Link> links)
    {
        var rel, link, element, attribute, value;

        for rel, links in links {
            for link in links {
                let element = doc->addChild("link");
                element->addAttribute("rel", rel);
                element->addAttribute("href", link->getUri());

                for attribute, value in link->getAttributes() {
                    element->addAttribute(attribute, value);
                }
            }
        }
    }

    /**
     * arrayToXml
     *
     * @param array $data
     * @param \SimpleXmlElement element
     * @param mixed parent
     * @access protected
     * @return void
     */
    protected function arrayToXml(var data, <\SimpleXmlElement> element, var parent = null)
    {
        var key, value, subnode;

        for key, value in data {
            if typeof value == "array" {
                if !is_numeric(key) {
                    if count(value) > 0 && isset value[0] {
                        this->arrayToXml(value, element, key);
                    } else {
                        let subnode = element->addChild(key);
                        this->arrayToXml(value, subnode, key);
                    }
                } else {
                    let subnode = element->addChild(parent);
                    this->arrayToXml(value, subnode, parent);
                }
            } else {
                if !is_numeric(key) {
                    if substr(key, 0, 1) == "@" {
                        element->addAttribute(substr(key, 1), value);
                    } else {
                        if key == "value" && count(data) == 1 {
                            //let element->{0} = value;
                        } else {
                            if is_bool(value) {
                                element->addChild(key, intval(value));
                            } else {
                                element->addChild(key, htmlspecialchars(value, ENT_QUOTES));
                            }
                        }
                    }
                } else {
                    element->addChild(parent, htmlspecialchars(value, ENT_QUOTES));
                }
            }
        }
    }

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
    protected function resourcesForXml(<\SimpleXmlElement> doc, var rel, var resources)
    {
        var resource, innerRel, innerRes, uri, element;

        for resource in resources {
            let element = doc->addChild("resource");
            element->addAttribute("rel", rel);

            if (resource) {
                let uri = resource->getUri();
                if typeof uri != "null" {
                    element->addAttribute("href", resource->getUri());
                }

                this->linksForXml(element, resource->getLinks());

                for innerRel, innerRes in resource->getResources() {
                    this->resourcesForXml(element, innerRel, innerRes);
                }

                this->arrayToXml(resource->getData(), element);
            }
        }
    }
}
