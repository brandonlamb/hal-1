
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/hash.h"
#include "kernel/operators.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"


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
 * Hal\Link
 * Represents a link in the _links property of a Hal\Resource
 *
 * @package Hal
 * @author Ben Longden <ben@nocarrier.co.uk>
 * @author Brandon Lamb <brandon@brandonlamb.com>
 */
ZEPHIR_INIT_CLASS(Hal_Link) {

	ZEPHIR_REGISTER_CLASS(Hal, Link, hal, link, hal_link_method_entry, 0);

/**
     * The URI represented by this Hal\Link.
     *
     * @var string
     */
	zend_declare_property_null(hal_link_ce, SL("uri"), ZEND_ACC_PROTECTED TSRMLS_CC);
/**
     * Any attributes on this link.
     *
     * [
     *    'templated' => 0,
     *    'type' => 'application/hal+json',
     *    'deprecation' => 1,
     *    'name' => 'latest',
     *    'profile' => 'http://.../profile/order',
     *    'title' => 'The latest order',
     *    'hreflang' => 'en'
     * ]
     *
     * @var array
     */
	zend_declare_property_null(hal_link_ce, SL("attributes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Supported attributes in Hal (specification section 5).
 *
 * @param string uri The URI represented by this link.
 * @param array attributes Any additional attributes.
 */
PHP_METHOD(Hal_Link, __construct) {

	HashTable *_2;
	HashPosition _1;
	zval *uri_param = NULL, *attributes = NULL, *rel = NULL, *attrib = NULL, *_0, **_3;
	zval *uri = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &uri_param, &attributes);

		if (Z_TYPE_P(uri_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'uri' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		uri = uri_param;

	if (!attributes) {
		attributes = ZEPHIR_GLOBAL(global_null);
	}


	zephir_update_property_this(this_ptr, SL("uri"), uri TSRMLS_CC);
	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("attributes"), _0 TSRMLS_CC);
	if ((Z_TYPE_P(attributes) == IS_ARRAY)) {
		zephir_is_iterable(attributes, &_2, &_1, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
			; zend_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HMKEY(rel, _2, _1);
			ZEPHIR_GET_HVALUE(attrib, _3);
			if (((Z_TYPE_P(attrib) == IS_ARRAY) || (Z_TYPE_P(attrib) != IS_NULL))) {
				zephir_update_property_array(this_ptr, SL("attributes"), rel, attrib TSRMLS_CC);
			}
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the URI from this link.
 *
 * @return string
 */
PHP_METHOD(Hal_Link, getUri) {


	RETURN_MEMBER(this_ptr, "uri");

}

/**
 * Returns the attributes for this link.
 *
 * return array
 */
PHP_METHOD(Hal_Link, getAttributes) {


	RETURN_MEMBER(this_ptr, "attributes");

}

/**
 * The string representation of this link (the URI).
 *
 * return string
 */
PHP_METHOD(Hal_Link, __toString) {


	RETURN_MEMBER(this_ptr, "uri");

}

