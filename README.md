Hal
=============

This is a library for creating documents in the [application/hal+json and application/hal+xml][1] hypermedia formats

It requires PHP 5.5 or later.

```php
<?php

use Hal;

$hal = new Hal\Resource('/orders');
$hal->addLink('next', '/orders?page=2');
$hal->addLink('search', '/orders?id={order_id}');

$resource = new Hal\Resource(
    '/orders/123',
    ]
        'total' => 30.00,
        'currency' => 'USD',
    ]
);

$resource->addLink('customer', '/customer/bob', ['title' => 'Bob Jones <bob@jones.com>']);
$hal->addResource('order', $resource);
```

## Rendering API

This is still under consideration. There seems to be a few different ways with pros/cons to each

```php
// Method 1 - Hal\Resource has a helper method for each render type
echo $hal->asJson();
echo $hal->asXml();

// Method 2 - Hal\Resource accepts a render type via setRenderer
$hal->setRenderer(new Hal\Render\Json);
echo $hal->render();

// Method 3 - Creation and call of render is done outside of Hal\Resource
$renderer = new Hal\Renderer\Json;
echo $renderer->render($hal);
//-- OR --//
echo new Hal\Render\Json()->render($hal);
```

## Installation

Hal is provided as a PHP c extension. Go into the ext directory and run the install script.
This essentially runs the commands below which will install a hal.so in your php extensions directory.


```bash
phpize --silent
./configure --silent --enable-hal
make --silent && make --silent install
```

## License

Hal is licensed under the MIT license.

[1]: http://tools.ietf.org/html/draft-kelly-json-hal-05
