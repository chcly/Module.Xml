# Xml

Is a simple XML parser.

## Testing

The Test directory is setup to work with [googletest](https://github.com/google/googletest).

## Building

![A1](https://github.com/chcly/Module.Xml/actions/workflows/build-linux.yml/badge.svg)
![A2](https://github.com/chcly/Module.Xml/actions/workflows/build-windows.yml/badge.svg)

```sh
mkdir build
cd build
cmake .. -DXml_BUILD_TEST=ON -DXml_AUTO_RUN_TEST=ON
make
```

### Optional defines

| Option                 | Description                                          | Default |
| :--------------------- | :--------------------------------------------------- | :-----: |
| Xml_BUILD_TEST         | Build the unit test program.                         |   ON    |
| Xml_AUTO_RUN_TEST      | Automatically run the test program.                  |   OFF   |
| Xml_USE_STATIC_RUNTIME | Build with the MultiThreaded(Debug) runtime library. |   ON    |
