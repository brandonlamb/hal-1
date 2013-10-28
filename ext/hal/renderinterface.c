
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


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
/**
 * Hal\RenderInterface
 * The Hal Renderer Interface
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
ZEPHIR_INIT_CLASS(Hal_RenderInterface) {

	ZEPHIR_REGISTER_INTERFACE(Hal, RenderInterface, hal, renderinterface, hal_renderinterface_method_entry);


	return SUCCESS;

}

/**
 * Render the Hal resource in the appropriate form.
 *
 * Returns a string representation of the resource.
 *
 * @param Hal $resource
 * @param bool $pretty
 * @return string
 */
ZEPHIR_DOC_METHOD(Hal_RenderInterface, render);

