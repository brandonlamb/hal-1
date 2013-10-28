
extern zend_class_entry *hal_render_xml_ce;

ZEPHIR_INIT_CLASS(Hal_Render_Xml);

PHP_METHOD(Hal_Render_Xml, render);
PHP_METHOD(Hal_Render_Xml, parseLinks);
PHP_METHOD(Hal_Render_Xml, arrayToXml);
PHP_METHOD(Hal_Render_Xml, resourcesForXml);

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_xml_render, 0, 0, 2)
	ZEND_ARG_INFO(0, resource)
	ZEND_ARG_INFO(0, pretty)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_xml_parselinks, 0, 0, 2)
	ZEND_ARG_INFO(0, doc)
	ZEND_ARG_INFO(0, collection)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_xml_arraytoxml, 0, 0, 2)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, element)
	ZEND_ARG_INFO(0, parent)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hal_render_xml_resourcesforxml, 0, 0, 3)
	ZEND_ARG_INFO(0, doc)
	ZEND_ARG_INFO(0, rel)
	ZEND_ARG_INFO(0, resources)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(hal_render_xml_method_entry) {
	PHP_ME(Hal_Render_Xml, render, arginfo_hal_render_xml_render, ZEND_ACC_PUBLIC)
	PHP_ME(Hal_Render_Xml, parseLinks, arginfo_hal_render_xml_parselinks, ZEND_ACC_PROTECTED)
	PHP_ME(Hal_Render_Xml, arrayToXml, arginfo_hal_render_xml_arraytoxml, ZEND_ACC_PROTECTED)
	PHP_ME(Hal_Render_Xml, resourcesForXml, arginfo_hal_render_xml_resourcesforxml, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
