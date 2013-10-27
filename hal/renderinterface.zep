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
 * Hal\RenderInterface
 * The Hal Renderer Interface
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */

interface RenderInterface
{
    /**
     * Render the Hal resource in the appropriate form.
     *
     * Returns a string representation of the resource.
     *
     * @param Hal $resource
     * @param bool $pretty
     * @return string
     */
    public function render(<\Hal\Resource> resource, boolean pretty) -> string;
}
