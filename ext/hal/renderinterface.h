
extern zend_class_entry *hal_renderinterface_ce;

ZEPHIR_INIT_CLASS(Hal_RenderInterface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_renderinterface_render, 0, 0, 2)
	ZEND_ARG_INFO(0, resource)
	ZEND_ARG_INFO(0, pretty)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(hal_renderinterface_method_entry) {
	PHP_ABSTRACT_ME(Hal_RenderInterface, render, arginfo_hal_renderinterface_render)
	PHP_FE_END
};
