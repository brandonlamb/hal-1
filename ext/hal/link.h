
extern zend_class_entry *hal_link_ce;

ZEPHIR_INIT_CLASS(Hal_Link);

PHP_METHOD(Hal_Link, __construct);
PHP_METHOD(Hal_Link, getUri);
PHP_METHOD(Hal_Link, getAttributes);
PHP_METHOD(Hal_Link, __toString);

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_link___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, uri)
	ZEND_ARG_INFO(0, attributes)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(hal_link_method_entry) {
	PHP_ME(Hal_Link, __construct, arginfo_hal_link___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Hal_Link, getUri, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Link, getAttributes, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Link, __toString, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
