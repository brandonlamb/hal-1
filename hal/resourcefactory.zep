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
    public static function fromJson(var text, int maxDepth = 0) -> <Hal\Resource>
    {
        var data, uri, link, rel, links, embed, href,
        childResource, hal, value, _data, _links, _embedded;

        let data = json_decode(text, true);

        if isset data["_links"]["self"]["href"] {
            let uri = data["_links"]["self"]["href"];
        } else {
            let uri = "";
        }

        // Loop through links but exclude "self"
        if isset data["_links"] {
            let _links = [];
            for rel, links in data["_links"] {
                if rel != "self" {
                    let _links[rel] = links;
                }
            }
        } else {
            let _links = [];
        }

        if isset data["_embedded"] {
            let _embedded = data["_embedded"];
        } else {
            let _embedded = [];
        }

        // Loop through data and exclude "_links" and "_embedded"
        let _data = [];
        for rel, links in data {
            if rel != "_links" && rel != "_embedded" {
                let _data[rel] = links;
            }
        }

        // Initialize new resource
        let hal = new Hal\Resource(uri, _data);

        // Loop through "_links" and add a new link to the hal resource
        for rel, links in _links {
            if !isset links[0] {
                let link = [links];
                let links = link;
            }

            if fetch value, links[0] {
                if typeof value != "array" {
                    let link = [links];
                    let links = link;
                }
            }

            for link in links {
                if isset link["href"] {
                    let href = link["href"];
                    let link["href"] = null;
                } else {
                    let href = "";
                }

                //if isset link["title"] {
                //    let link["title"] = null;
                //}

                hal->addLink(rel, href, link);
            }
        }

        if maxDepth > 0 {
            for rel, embed in _embedded {
                if typeof embed != "array" {
                    hal->addResource(rel, self::fromJson(json_encode(embed), maxDepth - 1));
                } else {
                    for childResource in embed {
                        hal->addResource(rel, self::fromJson(json_encode(childResource), maxDepth - 1));
                    }
                }
            }
        }

        return hal;
    }

    /**
     * Decode a application/hal+xml document into a Hal\Resource object.
     *
     * @param string text
     * @return Hal\Resource
     */
    public static function fromXml(var text) -> <Hal\Resource>
    {
        var data, children, link, links, links2, embedded, rel, hal, attributes, href;

        let data = new \SimpleXMLElement(text);
        let children = data->children();
        let links = clone children->link;
        let embedded = clone children->resource;

        unset(children->link);
        unset(children->resource);

        let hal = new Hal\Resource(data->attributes()->href, children->asXML());

        for links2 in links {
            if typeof links2 != "array" {
                let links2 = [links2];
            }

            for link in links {
                let attributes = link->attributes()->asXML();
                let attributes = attributes["@attributes"];
                let rel = attributes["rel"];
                let href = attributes["href"];
                unset(attributes["rel"]);
                unset(attributes["href"]);
                hal->addLink(rel, href, attributes);
            }
        }

        return hal;
    }
}
