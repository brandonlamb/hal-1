
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ext.h"
#include "ext/standard/php_string.h"
#include "ext.h"

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/concat.h"

void zephir_concat_svsv(zval **result, const char *op1, zend_uint op1_len, zval *op2, const char *op3, zend_uint op3_len, zval *op4, int self_var TSRMLS_DC){

	zval result_copy, op2_copy, op4_copy;
	int use_copy = 0, use_copy2 = 0, use_copy4 = 0;
	uint offset = 0, length;

	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
		if (use_copy2) {
			op2 = &op2_copy;
		}
	}

	if (Z_TYPE_P(op4) != IS_STRING) {
		zend_make_printable_zval(op4, &op4_copy, &use_copy4);
		if (use_copy4) {
			op4 = &op4_copy;
		}
	}

	length = op1_len + Z_STRLEN_P(op2) + op3_len + Z_STRLEN_P(op4);
	if (self_var) {

		if (Z_TYPE_PP(result) != IS_STRING) {
			zend_make_printable_zval(*result, &result_copy, &use_copy);
			if (use_copy) {
				ZEPHIR_CPY_WRT_CTOR(*result, (&result_copy));
			}
		}

		offset = Z_STRLEN_PP(result);
		length += offset;
		Z_STRVAL_PP(result) = (char *) erealloc(Z_STRVAL_PP(result), length + 1);

	} else {
		Z_STRVAL_PP(result) = (char *) emalloc(length + 1);
	}

	memcpy(Z_STRVAL_PP(result) + offset, op1, op1_len);
	memcpy(Z_STRVAL_PP(result) + offset + op1_len, Z_STRVAL_P(op2), Z_STRLEN_P(op2));
	memcpy(Z_STRVAL_PP(result) + offset + op1_len + Z_STRLEN_P(op2), op3, op3_len);
	memcpy(Z_STRVAL_PP(result) + offset + op1_len + Z_STRLEN_P(op2) + op3_len, Z_STRVAL_P(op4), Z_STRLEN_P(op4));
	Z_STRVAL_PP(result)[length] = 0;
	Z_TYPE_PP(result) = IS_STRING;
	Z_STRLEN_PP(result) = length;

	if (use_copy2) {
		zval_dtor(op2);
	}

	if (use_copy4) {
		zval_dtor(op4);
	}

	if (use_copy) {
		zval_dtor(&result_copy);
	}

}

