# Albert plugin: Docs

## Features

- Search offline documentation and open it in your browser.
- Choose from dozens of ready-to-use offline docsets from Zeal/Dash.
- Custom docsets are read from `$APP_DATA_DIR/docs/custom_docsets`

## Notes

Due to licensing the distribution on macOS is explicitly forbidden.

## Use with custom docsets

In addition to the list of docsets [published by Dash][official], this plugin
supports loading custom docsets. You can see [this page][generating] for
official documentation on how to create a docset. For example, you can use
[doc2dash][] to create a docset for a Python project with Sphinx documentation:

``` sh
# Install doc2dash
pip install doc2dash
# or
uv tool install doc2dash

# Build HTML docs according to your project's documentation. For example:
sphinx-build docs docs/_html

# Use doc2dash to convert to a Dash docset:
doc2dash docs/_html
# This should create a directory named $SOMETHING.docset.

# Copy an icon (a 128x128 png file is ideal) into the directory:
cp icon.png $SOMETHING.docset/icon.png

# The resulting docset directory can be copied to your albert custom_docsets dir
mkdir -p ~/.local/share/albert/docs/custom_docsets
cp $SOMETHING.docset ~/.local/share/albert/docs/custom_docsets/
```

Finally, activate Albert and restart it. On relaunch, Albert will discover the
custom docset and you should be able to search its headings and open it in your
web browser.

[official]: https://kapeli.com/dash#docsets
[generating]: https://kapeli.com/docsets
[doc2dash]: https://github.com/hynek/doc2dash
