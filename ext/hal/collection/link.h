
extern zend_class_entry *hal_collection_link_ce;

ZEPHIR_INIT_CLASS(Hal_Collection_Link);

PHP_METHOD(Hal_Collection_Link, __construct);
PHP_METHOD(Hal_Collection_Link, getData);
PHP_METHOD(Hal_Collection_Link, get);
PHP_METHOD(Hal_Collection_Link, add);
PHP_METHOD(Hal_Collection_Link, count);

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_collection_link_get, 0, 0, 1)
	ZEND_ARG_INFO(0, rel)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_collection_link_add, 0, 0, 2)
	ZEND_ARG_INFO(0, rel)
	ZEND_ARG_INFO(0, link)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(hal_collection_link_method_entry) {
	PHP_ME(Hal_Collection_Link, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Hal_Collection_Link, getData, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Collection_Link, get, arginfo_hal_collection_link_get, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Collection_Link, add, arginfo_hal_collection_link_add, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Collection_Link, count, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
