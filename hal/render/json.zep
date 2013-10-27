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
 * Hal\Render\Json
 * Renders a Hal\Resource into an array that is valid for application/json+hal
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */

class Json implements Hal\RenderInterface
{
    /**
     * Render.
     *
     * @param Hal\Resource $resource
     * @param bool pretty
     * @return string
     */
    public function render(<Hal\Resource> resource, boolean pretty)
    {
        var data;
        int options = 0;

        if version_compare(PHP_VERSION, "5.4.0") >= 0 && pretty {
            //let options = JSON_UNESCAPED_SLASHES | JSON_PRETTY_PRINT;
            let options = JSON_PRETTY_PRINT;
        }

        let data = json_encode(this->parseResource(resource), options);
        return data;
    }

    /**
     * Return an array (compatible with the hal+json format) representing the
     * complete response.
     *
     * @param Hal\Resource resource
     * @return array
     */
    protected function parseResource(<Hal\Resource> resource)
    {
        var data, links, resources;

        if resource == null {
            return [];
        }

        let data = this->stripAttributeMarker(resource->getData());

        let links = this->parseLinks(resource->getUri(), resource->getLinks());
        if count(links) > 0 {
            let data["_links"] = links;
        }

        let resources = this->parseResources(resource->getResources());
        if count(resources) > 0 {
            let data["_embedded"] = resources;
        }

        return data;
    }

    /**
     * Return an array (compatible with the hal+json format) representing
     * associated links.
     *
     * @param string uri
     * @param array links
     * @return array
     */
    protected function parseLinks(string uri, <Hal\Collection\Link> container)
    {
        var data, rel, link, links, attribute, attributes, item, value;

        let data = [];

        if uri != "" {
            let data["self"] = ["href": uri];
        }

        for rel, links in container->getData() {
            if count(links) == 1 && rel != "curies" {
                let data[rel] = ["href": links[0]->getUri()];

                for attribute, value in links[0]->getAttributes() {
                    let attributes = data[rel];
                    let attributes[attribute] = value;
                    let data[rel] = attributes;
                }
            } else {
                let data[rel] = [];
                for link in links {
                    let item = ["href": link->getUri()];
                    for attribute, value in link->getAttributes() {
                        let item[attribute] = value;
                    }

                    if fetch value, data[rel] {
                        let value[] = item;
                        let data[rel] = value;
                    } else {
                        let data[rel] = [item];
                    }
                }
            }
        }

        return data;
    }

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
    protected function parseResources(<Hal\Collection\Resource> resources)
    {
        var data, rel;
        let data = [];
        for rel, resources in resources->getData() {
            let data[rel] = this->arrayFromResources(resources);
        }

        return data;
    }

    /**
     * Loop through array of resources and pase into array
     *
     * @param array resources
     * @return array
     */
    protected function arrayFromResources(var resources)
    {
        var data, resource, res;
        let data = [];

        for resource in resources {
            let res = this->parseResource(resource);
            if count(res) > 0 {
                let data[] = res;
            }
        }

        return data;
    }

    /**
     * Remove the @ prefix from keys that denotes an attribute in XML. This
     * cannot be represented in JSON, so it's effectively ignored.
     *
     * @param array data The array to strip @ from the keys.
     * @return array
     */
    protected function stripAttributeMarker(var data)
    {
        var key, value;

        if typeof data != "array" {
            let data = [];
        }

        for key, value in data {
            if substr(key, 0, 5) == "@xml:" {
                let data[substr(key, 5)] = value;
                unset(data[key]);
            } else {
                if substr(key, 0, 1) == "@" {
                    let data[substr(key, 1)] = value;
                    unset (data[key]);
                }
            }

            if typeof value == "array" {
                let data[key] = this->stripAttributeMarker(value);
            }
        }

        return data;
    }
}
